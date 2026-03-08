#include "menu_widget.h"
#include "setting_manager.h"
#include <QString>

MenuWidget::MenuWidget(QWidget *parent)
    : QWidget{parent}
{
    layout = new QVBoxLayout(this);


    bestScoreTitle = new QLabel("BEST SCORE: " + QString::number(SettingsManager::instance().getMaxScore()));
    bestScoreTitle->setStyleSheet("font-size: 36px; font-weight: bold; margin-bottom: 10px;");
    bestScoreTitle->setAlignment(Qt::AlignCenter);


    totalLinesTitle = new QLabel("ЛИНИИ: " + QString::number(SettingsManager::instance().totalyCoutLines()));
    totalLinesTitle->setStyleSheet("font-size: 20px; font-weight: bold; margin-bottom: 20px; color: #aaaaaa;");
    totalLinesTitle->setAlignment(Qt::AlignCenter);


    title = new QLabel("QT TETRIS");
    title->setStyleSheet("font-size: 40px; font-weight: bold; margin-bottom: 20px;");
    title->setAlignment(Qt::AlignCenter);


    btnStart = new QPushButton("ИГРАТЬ");
    btnExit = new QPushButton("ВЫХОД");

    QString btnStyle = "QPushButton { font-size: 20px; padding: 10px; background: #333; color: white; border-radius: 5px; }"
                       "QPushButton:hover { background: #555; }";
    btnStart->setStyleSheet(btnStyle);
    btnExit->setStyleSheet(btnStyle);


    layout->addWidget(bestScoreTitle);
    layout->addWidget(totalLinesTitle);
    layout->addStretch();
    layout->addWidget(title);
    layout->addWidget(btnStart);
    layout->addWidget(btnExit);
    layout->addStretch();

    connect(btnStart, &QPushButton::clicked, this, &MenuWidget::onStartClicked);
    connect(btnExit, &QPushButton::clicked, this, &MenuWidget::onExitClicked);


    connect(&SettingsManager::instance(), &SettingsManager::scoresChanged,
            this, &MenuWidget::updateBestScore);
    connect(&SettingsManager::instance(), &SettingsManager::scoresChanged,
            this, &MenuWidget::updateTotalLines);
}

void MenuWidget::updateBestScore() {
    bestScoreTitle->setText("BEST SCORE: " + QString::number(SettingsManager::instance().getMaxScore()));
}

void MenuWidget::updateTotalLines() {
    totalLinesTitle->setText("ЛИНИИ: " + QString::number(SettingsManager::instance().totalyCoutLines()));
}
