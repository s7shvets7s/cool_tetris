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


private:


    QVBoxLayout *layout;
    QPushButton *btnStart;
    QPushButton *btnExit ;
    QLabel *title;
};

#endif // MENU_WIDGET_H
