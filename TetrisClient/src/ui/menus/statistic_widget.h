#ifndef STATISTIC_WIDGET_H
#define STATISTIC_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class StatisticWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StatisticWidget(QWidget *parent = nullptr);

signals:
    void backClicked();

private:
    void setupUi();

    QLabel* m_titleLabel = nullptr;
    QPushButton* m_backButton = nullptr;
};

#endif // STATISTIC_WIDGET_H
