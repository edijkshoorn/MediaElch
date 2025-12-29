#include "scrapers/movie/theporndb/ThePornDbApi.h"

#include "network/NetworkRequest.h"
#include "scrapers/movie/theporndb/ThePornDbMovieConfiguration.h"

#include <QJsonParseError>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>
#include <QUrlQuery>

namespace {

QUrl makeApiUrl(const QString& suffix, const QUrlQuery& query)
{
    QUrl url(QStringLiteral("https://api.theporndb.net/%1").arg(suffix));
    QUrlQuery fullQuery(query);
    url.setQuery(fullQuery);
    return url;
}

} // namespace

namespace mediaelch {
namespace scraper {

ThePornDbApi::ThePornDbApi(ThePornDbMovieConfiguration& settings, QObject* parent) :
    QObject(parent), m_settings(settings)
{
}

void ThePornDbApi::initialize()
{
    m_isInitialized = !m_settings.apiKey().isEmpty();
}

bool ThePornDbApi::isInitialized() const
{
    return m_isInitialized;
}

void ThePornDbApi::searchMovies(const QString& query, ApiCallback callback)
{
    QUrlQuery q;
    q.addQueryItem(QStringLiteral("query"), query);
    sendGetRequest(makeApiUrl(QStringLiteral("movies"), q), std::move(callback));
}

void ThePornDbApi::loadMovie(const QString& identifier, ApiCallback callback)
{
    sendGetRequest(makeApiUrl(QStringLiteral("movies/%1").arg(identifier), {}), std::move(callback));
}

void ThePornDbApi::sendGetRequest(const QUrl& url, ApiCallback callback)
{
    QNetworkRequest request = makeAuthorizedRequest(url);

    if (m_network.cache().hasValidElement(request)) {
        QTimer::singleShot(0, this, [cb = std::move(callback), element = m_network.cache().getElement(request)]() {
            cb(QJsonDocument::fromJson(element.toUtf8()), {});
        });
        return;
    }

    QNetworkReply* reply = m_network.getWithWatcher(request);
    connect(reply, &QNetworkReply::finished, this, [reply, cb = std::move(callback), request, this]() {
        auto dls = makeDeleteLaterScope(reply);

        QString data;
        if (reply->error() == QNetworkReply::NoError) {
            data = QString::fromUtf8(reply->readAll());
        }

        QJsonParseError parseError{};
        QJsonDocument json;
        if (!data.isEmpty()) {
            json = QJsonDocument::fromJson(data.toUtf8(), &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                m_network.cache().addElement(request, data);
            }
        }

        ScraperError error = makeScraperError(data, *reply, parseError);
        cb(json, error);
    });
}

QNetworkRequest ThePornDbApi::makeAuthorizedRequest(const QUrl& url) const
{
    QNetworkRequest request = mediaelch::network::jsonRequestWithDefaults(url);
    if (!m_settings.apiKey().isEmpty()) {
        request.setRawHeader("X-API-Key", m_settings.apiKey().toUtf8());
    }
    return request;
}

} // namespace scraper
} // namespace mediaelch
