#pragma once

#include "scrapers/movie/MovieScrapeJob.h"

#include <QJsonDocument>

namespace mediaelch {
namespace scraper {

class ThePornDbApi;

class ThePornDbMovieScrapeJob : public MovieScrapeJob
{
    Q_OBJECT

public:
    ThePornDbMovieScrapeJob(ThePornDbApi& api, Config _config, QObject* parent = nullptr);
    ~ThePornDbMovieScrapeJob() override = default;

    void doStart() override;

private:
    void parseAndAssignInfos(const QJsonDocument& json);

private:
    ThePornDbApi& m_api;
};

} // namespace scraper
} // namespace mediaelch
