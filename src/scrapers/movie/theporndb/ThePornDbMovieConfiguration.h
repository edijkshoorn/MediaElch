#pragma once

#include "data/Locale.h"
#include "scrapers/ScraperConfiguration.h"
#include "settings/Settings.h"
#include "utils/Meta.h"

namespace mediaelch {
namespace scraper {

class ThePornDbMovieConfiguration : public QObject, public ScraperConfiguration
{
    Q_OBJECT

public:
    explicit ThePornDbMovieConfiguration(Settings& settings, QObject* parent = nullptr);
    ~ThePornDbMovieConfiguration() override = default;

    void init() override;

public:
    ELCH_NODISCARD QString apiKey() const;
    void setApiKey(const QString& value);

signals:
    void apiKeyChanged(QString apiKey);
};

} // namespace scraper
} // namespace mediaelch
