#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QSet>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include "game_logic.h"
#include <QElapsedTimer>

class FildWidget : public QWidget {
    Q_OBJECT
public:
    FildWidget(QWidget *parent = nullptr);
    const GameLogic& getLogic() const { return m_game; }
    GameLogic& getLogic() { return m_game; }


protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

public slots:
    void gameStep();
    void restart();
signals:
    void escapePressed();
    void gameEnd();

private:
    GameLogic m_game;
    QSet<int> pressedKeys;
    QTimer *inputTimer;
    int CELL_SIZE;
    void processInput();
    QElapsedTimer rotateTimer;
    const int ROTATE_COOLDOWN = 200;

public:
    void setInputTimerEnabled(bool enabled);
};

#endif
