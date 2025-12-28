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

    ELCH_NODISCARD Locale language() override;
    void setLanguage(const Locale& value) override;

public:
    ELCH_NODISCARD QString apiKey();
    void setApiKey(const QString& value);

signals:
    void languageChanged(mediaelch::Locale language);
    void apiKeyChanged(QString apiKey);
};

} // namespace scraper
} // namespace mediaelch
