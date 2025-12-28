#include "scrapers/movie/theporndb/ThePornDbMovieScrapeJob.h"

#include "data/movie/Movie.h"
#include "scrapers/movie/theporndb/ThePornDbApi.h"

#include <QDate>
#include <QJsonArray>
#include <QJsonObject>
#include <chrono>

namespace mediaelch {
namespace scraper {

ThePornDbMovieScrapeJob::ThePornDbMovieScrapeJob(ThePornDbApi& api, MovieScrapeJob::Config _config, QObject* parent) :
    MovieScrapeJob(std::move(_config), parent), m_api{api}
{
}

void ThePornDbMovieScrapeJob::doStart()
{
    m_api.loadMovie(config().identifier.str(), [this](QJsonDocument json, ScraperError error) {
        if (!error.hasError()) {
            parseAndAssignInfos(json);
        } else {
            setScraperError(error);
        }

        emitFinished();
    });
}

void ThePornDbMovieScrapeJob::parseAndAssignInfos(const QJsonDocument& json)
{
    QJsonObject movieObj = json.object();
    if (movieObj.value("data").isObject()) {
        movieObj = movieObj.value("data").toObject();
    }

    const QString title = movieObj.value("title").toString(movieObj.value("name").toString());
    if (!title.isEmpty()) {
        m_movie->setTitle(title);
    }

    const QString summary = movieObj.value("description").toString(movieObj.value("synopsis").toString());
    if (!summary.isEmpty()) {
        m_movie->setOverview(summary);
    }

    const QString releaseDate = movieObj.value("release_date").toString(movieObj.value("date").toString());
    if (!releaseDate.isEmpty()) {
        m_movie->setReleased(QDate::fromString(releaseDate, "yyyy-MM-dd"));
    }

    const QString durationStr = movieObj.value("runtime").toString(movieObj.value("duration").toString());
    if (!durationStr.isEmpty()) {
        bool ok = false;
        int minutes = durationStr.toInt(&ok);
        if (ok) {
            m_movie->setRuntime(std::chrono::minutes(minutes));
        }
    }

    if (movieObj.contains("rating")) {
        Rating rating;
        rating.source = "theporndb";
        rating.maxRating = 10;
        rating.rating = movieObj.value("rating").toDouble();
        m_movie->ratings().addRating(rating);
    }

    if (movieObj.value("tags").isArray()) {
        const auto tags = movieObj.value("tags").toArray();
        for (const auto& tag : tags) {
            m_movie->addGenre(tag.toString());
        }
    }

    if (movieObj.value("studios").isArray()) {
        const auto studios = movieObj.value("studios").toArray();
        for (const auto& studio : studios) {
            m_movie->addStudio(studio.toString());
        }
    } else if (movieObj.contains("studio")) {
        m_movie->addStudio(movieObj.value("studio").toString());
    }

    if (movieObj.value("performers").isArray()) {
        m_movie->setActors({});
        const auto actors = movieObj.value("performers").toArray();
        for (const auto& performer : actors) {
            const auto performerObj = performer.toObject();
            Actor actor;
            actor.name = performerObj.value("name").toString();
            actor.role = performerObj.value("character").toString();
            actor.thumb = performerObj.value("image").toString();
            if (!actor.name.isEmpty()) {
                m_movie->addActor(actor);
            }
        }
    }

    if (movieObj.value("posters").isArray()) {
        const auto posters = movieObj.value("posters").toArray();
        for (const auto& posterItem : posters) {
            const QString url = posterItem.toString();
            if (url.isEmpty()) {
                continue;
            }
            Poster poster;
            poster.originalUrl = url;
            poster.thumbUrl = url;
            m_movie->images().addPoster(poster, m_movie->images().posters().isEmpty());
        }
    } else if (!movieObj.value("poster").toString().isEmpty()) {
        Poster poster;
        poster.originalUrl = movieObj.value("poster").toString();
        poster.thumbUrl = poster.originalUrl;
        m_movie->images().addPoster(poster, true);
    }

    if (movieObj.value("backdrops").isArray()) {
        const auto backdrops = movieObj.value("backdrops").toArray();
        for (const auto& backdropItem : backdrops) {
            const QString url = backdropItem.toString();
            if (url.isEmpty()) {
                continue;
            }
            Poster backdrop;
            backdrop.originalUrl = url;
            backdrop.thumbUrl = url;
            m_movie->images().addBackdrop(backdrop);
        }
    } else if (!movieObj.value("backdrop").toString().isEmpty()) {
        Poster backdrop;
        backdrop.originalUrl = movieObj.value("backdrop").toString();
        backdrop.thumbUrl = backdrop.originalUrl;
        m_movie->images().addBackdrop(backdrop);
    }
}

} // namespace scraper
} // namespace mediaelch
