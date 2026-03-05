#ifndef SCORE_WIDGET_H
#define SCORE_WIDGET_H
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include "game_logic.h"
class ScoreWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScoreWidget(const GameLogic &game, QWidget *parent = nullptr):m_game(game){
        layout = new QHBoxLayout(this);


        labelTitle = new QLabel("SCORE:", this);
        labelScore = new QLabel("000000", this);

        game.getScore();
        this->setStyleSheet(
            "ScoreWidget { background-color: #2c3e50; border-radius: 10px; padding: 5px; }"
            "QLabel { color: white; font-weight: bold; font-family: 'Segoe UI', sans-serif; font-size: 18px; }"
            "#ScoreValue { color: #f1c40f; font-size: 22px; }"
            );

        labelScore->setObjectName("ScoreValue");

        layout->addWidget(labelTitle);
        layout->addSpacing(10);
        layout->addWidget(labelScore);
        layout->addStretch();
    }
protected:
    void paintEvent(QPaintEvent *) override {
        labelScore->setText(QString("%1").arg(m_game.getScore(), 10, 10, QChar('0')));
    }
signals:
private:
    const GameLogic &m_game;
    QHBoxLayout *layout;
    QLabel* labelTitle;
    QLabel* labelScore;
};

#endif // SCORE_WIDGET_H
