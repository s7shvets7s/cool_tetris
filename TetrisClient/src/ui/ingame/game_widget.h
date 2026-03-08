#ifndef GAME_WIDGET_H
#define GAME_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include "fild_widget.h"
#include "next_pieces_widget.h"
#include "poket_piece_widget.h"
#include "score_widget.h"
#include "pause_widget.h"
#include "game_over_widget.h"
#include <QStackedLayout>

class GameWidget : public QWidget
{
    Q_OBJECT
public:
     GameWidget(QWidget *parent = nullptr);


    FildWidget* fildWidget;



    void setFocus(Qt::FocusReason reason = Qt::OtherFocusReason);
private:
    QHBoxLayout *hLayout ;
    QVBoxLayout *lefVLayout;
    QVBoxLayout *midVLayout;
    QVBoxLayout *rightVLayout;
    QStackedWidget *stackedWidget;

    QWidget *gameLayer;
    NextPiecesWidget *nextWidget ;
    PoketPieceWidget *poketPieceWodget;
    ScoreWidget *scoreWidget;


    PauseWidget* pauseWidget;
    GameOverWidget* gameOverWidget;
public slots:
    void pauseOff();
    void pauseOn();
    void restart();
    void showGameOver();

signals:
    void escapePressed();
    void gameEnd();
};

#endif // GAME_WIDGET_H
