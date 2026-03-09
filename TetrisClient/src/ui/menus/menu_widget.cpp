#include "menu_widget.h"
#include "setting_manager.h"
#include <QString>
#include <Qstyle>

MenuWidget::MenuWidget(QWidget *parent)
    : QWidget{parent}
{

    mainLayout = new QVBoxLayout(this);
    settingsLayout=new QHBoxLayout();
    mainLayout->addLayout(settingsLayout);

    //mainLayout
//////////////////////////////////////////////////////////////////////////////////////////////////
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


     mainLayout->addWidget(title);
     mainLayout->addStretch();
    mainLayout->addWidget(bestScoreTitle);
    mainLayout->addWidget(totalLinesTitle);

     mainLayout->addWidget(btnStart);
     mainLayout->addWidget(btnExit);
     mainLayout->addStretch();

     connect(btnStart, &QPushButton::clicked, this, &MenuWidget::onStartClicked);
     connect(btnExit, &QPushButton::clicked, this, &MenuWidget::onExitClicked);


     connect(&SettingsManager::instance(), &SettingsManager::scoresChanged,
             this, &MenuWidget::updateBestScore);
     connect(&SettingsManager::instance(), &SettingsManager::scoresChanged,
             this, &MenuWidget::updateTotalLines);
//////////////////////////////////////////////////////////////////////////////////////////////////

     //settingsLayout
//////////////////////////////////////////////////////////////////////////////////////////////////
     btnSettings = new QPushButton();
     btnUser = new QPushButton();
     btnStatistic = new QPushButton();
     QIcon settingsIcon(":/settings_icon.svg");
     QIcon userIcon(":/user_icon.svg");
     QIcon statisticIcon(":/statistic_icon.svg");


    btnSettings->setIcon(settingsIcon);
    btnUser->setIcon(userIcon);
    btnStatistic->setIcon(statisticIcon);

    //btnSettings->setBaseSize(40,40);
    btnSettings->setFixedSize(40,40);
    btnUser->setFixedSize(40,40);
    btnStatistic->setFixedSize(40,40);
    settingsLayout->addWidget(btnSettings);
    settingsLayout->addWidget(btnUser);
    settingsLayout->addWidget(btnStatistic);
    settingsLayout->setAlignment(Qt::AlignTop);
    //settingsLayout










////////////////////////////////////////////////////////////////////////////////////

}

void MenuWidget::updateBestScore() {
    bestScoreTitle->setText("BEST SCORE: " + QString::number(SettingsManager::instance().getMaxScore()));
}

void MenuWidget::updateTotalLines() {
    totalLinesTitle->setText("ЛИНИИ: " + QString::number(SettingsManager::instance().totalyCoutLines()));
}
