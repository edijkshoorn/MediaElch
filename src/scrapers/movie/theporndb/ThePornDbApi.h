#pragma once

#include "network/NetworkManager.h"
#include "scrapers/ScraperError.h"

#include <QJsonDocument>
#include <QObject>
#include <QUrl>
#include <functional>

namespace mediaelch {
namespace scraper {

class ThePornDbMovieConfiguration;

class ThePornDbApi : public QObject
{
    Q_OBJECT

public:
    using ApiCallback = std::function<void(QJsonDocument, ScraperError)>;

public:
    explicit ThePornDbApi(const ThePornDbMovieConfiguration& settings, QObject* parent = nullptr);
    ~ThePornDbApi() override = default;

    void initialize();
    bool isInitialized() const;

public:
    void searchMovies(const QString& query, ApiCallback callback);
    void loadMovie(const QString& identifier, ApiCallback callback);

private:
    void sendGetRequest(const QUrl& url, ApiCallback callback);
    QNetworkRequest makeAuthorizedRequest(const QUrl& url) const;

private:
    const ThePornDbMovieConfiguration& m_settings;
    mediaelch::network::NetworkManager m_network;
    bool m_isInitialized{false};
};

} // namespace scraper
} // namespace mediaelch
