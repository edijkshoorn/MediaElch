#include "scrapers/movie/theporndb/ThePornDbMovieConfiguration.h"

#include "scrapers/movie/theporndb/ThePornDbMovie.h"

namespace {

static constexpr char moduleName[] = "scrapers";
static const Settings::Key KEY_SCRAPERS_API_KEY(moduleName, "Scrapers/theporndb/apiKey");

} // namespace

namespace mediaelch {
namespace scraper {

ThePornDbMovieConfiguration::ThePornDbMovieConfiguration(Settings& settings, QObject* parent) :
    QObject(parent), ScraperConfiguration(QString(ThePornDbMovie::ID), settings)
{
    settings.onSettingChanged(KEY_SCRAPERS_API_KEY, this, [this]() { emit apiKeyChanged(apiKey()); });
}

void ThePornDbMovieConfiguration::init()
{
    settings().setDefaultValue(KEY_SCRAPERS_API_KEY, QString());
}

QString ThePornDbMovieConfiguration::apiKey() const
{
    return settings().value(KEY_SCRAPERS_API_KEY).toString();
}

void ThePornDbMovieConfiguration::setApiKey(const QString& value)
{
    settings().setValue(KEY_SCRAPERS_API_KEY, value.trimmed());
}

} // namespace scraper
} // namespace mediaelch
