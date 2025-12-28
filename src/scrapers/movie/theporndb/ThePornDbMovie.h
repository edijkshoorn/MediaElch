#pragma once

#include "scrapers/movie/MovieScraper.h"
#include "scrapers/movie/theporndb/ThePornDbApi.h"

#include <QObject>

namespace mediaelch {
namespace scraper {

class ThePornDbMovieConfiguration;

class ThePornDbMovie final : public MovieScraper
{
    Q_OBJECT

public:
    static constexpr const char* ID = "theporndb";

public:
    explicit ThePornDbMovie(ThePornDbMovieConfiguration& settings, QObject* parent = nullptr);
    ~ThePornDbMovie() override;

    const ScraperMeta& meta() const override;

    void initialize() override;
    bool isInitialized() const override;

    ELCH_NODISCARD MovieSearchJob* search(MovieSearchJob::Config config) override;
    ELCH_NODISCARD MovieScrapeJob* loadMovie(MovieScrapeJob::Config config) override;

public:
    QSet<MovieScraperInfo> scraperNativelySupports() override;
    void changeLanguage(mediaelch::Locale locale) override;

private:
    ThePornDbMovieConfiguration& m_settings;
    ThePornDbApi m_api;
    ScraperMeta m_meta;
    QSet<MovieScraperInfo> m_scraperNativelySupports;
};

} // namespace scraper
} // namespace mediaelch
