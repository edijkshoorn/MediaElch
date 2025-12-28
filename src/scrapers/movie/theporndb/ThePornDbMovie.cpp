#include "scrapers/movie/theporndb/ThePornDbMovie.h"

#include "log/Log.h"
#include "scrapers/movie/theporndb/ThePornDbMovieConfiguration.h"
#include "scrapers/movie/theporndb/ThePornDbMovieScrapeJob.h"
#include "scrapers/movie/theporndb/ThePornDbMovieSearchJob.h"

namespace mediaelch {
namespace scraper {

ThePornDbMovie::ThePornDbMovie(ThePornDbMovieConfiguration& settings, QObject* parent) :
    MovieScraper(parent), m_settings{settings}, m_api{settings}, m_scraperNativelySupports{MovieScraperInfo::Title,
                                                                                           MovieScraperInfo::Tagline,
                                                                                           MovieScraperInfo::Rating,
                                                                                           MovieScraperInfo::Released,
                                                                                           MovieScraperInfo::Runtime,
                                                                                           MovieScraperInfo::Overview,
                                                                                           MovieScraperInfo::Poster,
                                                                                           MovieScraperInfo::Backdrop,
                                                                                           MovieScraperInfo::Actors,
                                                                                           MovieScraperInfo::Genres,
                                                                                           MovieScraperInfo::Studios}
{
    m_meta.identifier = ID;
    m_meta.name = "ThePornDB";
    m_meta.description = tr("ThePornDB provides community curated metadata for adult movies.");
    m_meta.website = "https://theporndb.net";
    m_meta.supportedDetails = m_scraperNativelySupports;
    m_meta.defaultLocale = m_settings.language();
    m_meta.isAdult = true;

    initialize();
}

ThePornDbMovie::~ThePornDbMovie() = default;

const MovieScraper::ScraperMeta& ThePornDbMovie::meta() const
{
    return m_meta;
}

void ThePornDbMovie::initialize()
{
    m_api.initialize();
}

bool ThePornDbMovie::isInitialized() const
{
    return m_api.isInitialized();
}

MovieSearchJob* ThePornDbMovie::search(MovieSearchJob::Config config)
{
    return new ThePornDbMovieSearchJob(m_api, std::move(config), this);
}

MovieScrapeJob* ThePornDbMovie::loadMovie(MovieScrapeJob::Config config)
{
    return new ThePornDbMovieScrapeJob(m_api, std::move(config), this);
}

QSet<MovieScraperInfo> ThePornDbMovie::scraperNativelySupports()
{
    return m_scraperNativelySupports;
}

void ThePornDbMovie::changeLanguage(mediaelch::Locale locale)
{
    Q_UNUSED(locale);
    qCInfo(generic) << "[ThePornDB] Language cannot be changed for this scraper.";
}

} // namespace scraper
} // namespace mediaelch
