#pragma once

#include "scrapers/movie/MovieSearchJob.h"

#include <QJsonObject>

namespace mediaelch {
namespace scraper {

class ThePornDbApi;

class ThePornDbMovieSearchJob : public MovieSearchJob
{
    Q_OBJECT

public:
    explicit ThePornDbMovieSearchJob(ThePornDbApi& api, MovieSearchJob::Config _config, QObject* parent = nullptr);
    ~ThePornDbMovieSearchJob() override = default;

    void doStart() override;

private:
    void parseSearch(const QJsonObject& json);

private:
    ThePornDbApi& m_api;
};

} // namespace scraper
} // namespace mediaelch
