#ifndef SETTING_WIDGET_H
#define SETTING_WIDGET_H

#include <QWidget>
#include <QPushButton>
class setting_widget : public QWidget
{
    Q_OBJECT
public:
    explicit setting_widget(QWidget *parent = nullptr);

private:
    QPushButton* backButton;
signals:
};

#endif // SETTING_WIDGET_H
