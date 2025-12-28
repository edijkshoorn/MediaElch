#include "scrapers/movie/theporndb/ThePornDbMovieSearchJob.h"

#include "scrapers/movie/theporndb/ThePornDbApi.h"

#include <QDate>
#include <QJsonArray>

namespace mediaelch {
namespace scraper {

ThePornDbMovieSearchJob::ThePornDbMovieSearchJob(ThePornDbApi& api, MovieSearchJob::Config _config, QObject* parent) :
    MovieSearchJob(_config, parent), m_api{api}
{
}

void ThePornDbMovieSearchJob::doStart()
{
    QString trimmed = QString(config().query).trimmed();
    if (trimmed.isEmpty()) {
        emitFinished();
        return;
    }

    m_api.searchMovies(trimmed, [this](QJsonDocument json, ScraperError error) {
        if (error.hasError()) {
            setScraperError(error);
        } else {
            parseSearch(json.object());
        }
        emitFinished();
    });
}

void ThePornDbMovieSearchJob::parseSearch(const QJsonObject& json)
{
    auto parseMovie = [this](const QJsonObject& movieObj) {
        MovieSearchJob::Result result;
        const QString identifier = movieObj.value("id").toString();
        if (identifier.isEmpty()) {
            return;
        }
        result.identifier = MovieIdentifier(identifier);
        result.title = movieObj.value("title").toString();
        if (result.title.isEmpty()) {
            result.title = movieObj.value("name").toString();
        }
        const QString releaseDate = movieObj.value("release_date").toString(movieObj.value("date").toString());
        if (!releaseDate.isEmpty()) {
            result.released = QDate::fromString(releaseDate, "yyyy-MM-dd");
        }
        m_results.append(result);
    };

    if (json.value("data").isArray()) {
        const auto results = json.value("data").toArray();
        for (const auto& entry : results) {
            parseMovie(entry.toObject());
        }
    } else if (json.value("results").isArray()) {
        const auto results = json.value("results").toArray();
        for (const auto& entry : results) {
            parseMovie(entry.toObject());
        }
    } else if (json.contains("id")) {
        parseMovie(json);
    }
}

} // namespace scraper
} // namespace mediaelch
