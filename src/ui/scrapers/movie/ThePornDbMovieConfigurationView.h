#pragma once

#include "scrapers/movie/theporndb/ThePornDbMovieConfiguration.h"

#include <QWidget>

class QLineEdit;

namespace mediaelch {
namespace scraper {

class ThePornDbMovieConfigurationView : public QWidget
{
    Q_OBJECT

public:
    explicit ThePornDbMovieConfigurationView(ThePornDbMovieConfiguration& settings, QWidget* parent = nullptr);
    ~ThePornDbMovieConfigurationView() override = default;

private:
    ThePornDbMovieConfiguration& m_settings;
    QLineEdit* m_apiKeyEdit{nullptr};
};

} // namespace scraper
} // namespace mediaelch
