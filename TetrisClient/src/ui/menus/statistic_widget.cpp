#include "statistic_widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

StatisticWidget::StatisticWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

void StatisticWidget::setupUi() {
    auto *layout = new QVBoxLayout(this);

    QString btnStyle = "QPushButton { font-size: 20px; padding: 10px; background: #333; color: white; border-radius: 5px; }"
                       "QPushButton:hover { background: #555; }";

    m_titleLabel = new QLabel("STATISTICS");
    m_titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; background: transparent;");
    m_titleLabel->setAlignment(Qt::AlignCenter);

    m_backButton = new QPushButton("Back");
    m_backButton->setStyleSheet("font-size: 14px; padding: 8px; background: #555; color: white; border-radius: 5px;");

    layout->addWidget(m_titleLabel);
    layout->addStretch();
    layout->addWidget(m_backButton);

    connect(m_backButton, &QPushButton::clicked, this, &StatisticWidget::backClicked);
}
