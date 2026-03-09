#ifndef MENU_WIDGET_H
#define MENU_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MenuWidget(QWidget *parent = nullptr);

signals:
    void onStartClicked();
    void onExitClicked();
private slots:
    void updateBestScore();
    void updateTotalLines();

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *settingsLayout;


    ////////////////////
    QPushButton *btnStart;
    QPushButton *btnExit;
    QLabel *title;
    QLabel *bestScoreTitle;
    QLabel *totalLinesTitle;
    ////////////////////



    ///////////////////////
    QPushButton *btnSettings;
    QPushButton *btnUser;
    QPushButton *btnStatistic;
    ///////////////////////
};

#endif // MENU_WIDGET_H
