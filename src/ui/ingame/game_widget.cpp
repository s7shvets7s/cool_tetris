#include "game_widget.h"



GameWidget::GameWidget(QWidget *parent)
    : QWidget{parent}
{

    hLayout = new QHBoxLayout(this);

    lefVLayout=new QVBoxLayout();
    midVLayout=new QVBoxLayout();
    rightVLayout=new QVBoxLayout();

    fildWidget = new FildWidget (this);
    scoreWidget =new ScoreWidget(fildWidget->getLogic(),this);
    nextWidget = new NextPiecesWidget(fildWidget->getLogic(), this);
    poketPieceWodget= new PoketPieceWidget(fildWidget->getLogic(), this);



    lefVLayout->addWidget(poketPieceWodget,0,Qt::AlignTop);
    midVLayout->addWidget(scoreWidget);
    midVLayout->addWidget(fildWidget);
    rightVLayout->addWidget(nextWidget,0,Qt::AlignTop);



    hLayout->addLayout(lefVLayout);

    hLayout->addLayout(midVLayout);
    hLayout->addLayout(rightVLayout);
    // hLayout->addWidget(poketPieceWodget, 0, Qt::AlignTop);
    // hLayout->addWidget(fildWidget);
    // hLayout->addWidget(nextWidget, 0, Qt::AlignTop);


connect(&fildWidget->getLogic(), &GameLogic::nextPiecesChanged, nextWidget, QOverload<>::of(&NextPiecesWidget::update));
connect(&fildWidget->getLogic(), &GameLogic::pocketChanged, poketPieceWodget, QOverload<>::of(&PoketPieceWidget::update));
connect(&fildWidget->getLogic(), &GameLogic::scoreChanged, scoreWidget, QOverload<>::of(&ScoreWidget::update));

connect(fildWidget, &FildWidget::escapePressed, this, &GameWidget::escapePressed);



}
void GameWidget::setFocus(Qt::FocusReason reason) {

    fildWidget->setFocus(reason);
}
