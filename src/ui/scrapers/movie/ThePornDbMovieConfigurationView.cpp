#include "ui/scrapers/movie/ThePornDbMovieConfigurationView.h"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

namespace mediaelch {
namespace scraper {

ThePornDbMovieConfigurationView::ThePornDbMovieConfigurationView(ThePornDbMovieConfiguration& settings, QWidget* parent) :
    QWidget(parent), m_settings(settings)
{
    m_apiKeyEdit = new QLineEdit(this);
    m_apiKeyEdit->setText(m_settings.apiKey());

    auto* layout = new QGridLayout(this);
    layout->addWidget(new QLabel(tr("API Key")), 0, 0);
    layout->addWidget(m_apiKeyEdit, 0, 1);
    layout->setColumnStretch(2, 1);
    layout->setContentsMargins(12, 0, 12, 12);

    connect(m_apiKeyEdit, &QLineEdit::textEdited, this, [this]() { m_settings.setApiKey(m_apiKeyEdit->text()); });
    connect(&m_settings, &ThePornDbMovieConfiguration::apiKeyChanged, this, [this](const QString& value) {
        const bool blocked = m_apiKeyEdit->blockSignals(true);
        m_apiKeyEdit->setText(value);
        m_apiKeyEdit->blockSignals(blocked);
    });
}

} // namespace scraper
} // namespace mediaelch
