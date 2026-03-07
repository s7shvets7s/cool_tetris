#include "menu_widget.h"

MenuWidget::MenuWidget(QWidget *parent)
    : QWidget{parent}
{
    layout = new QVBoxLayout(this);
    title = new QLabel("QT TETRIS");
    title->setStyleSheet("font-size: 40px; font-weight: bold; margin-bottom: 20px;");
    title->setAlignment(Qt::AlignCenter);

    btnStart = new QPushButton("ИГРАТЬ");
    btnExit = new QPushButton("ВЫХОД");


    QString btnStyle = "QPushButton { font-size: 20px; padding: 10px; background: #333; color: white; border-radius: 5px; }"
                       "QPushButton:hover { background: #555; }";
    btnStart->setStyleSheet(btnStyle);
    btnExit->setStyleSheet(btnStyle);

    layout->addStretch();
    layout->addWidget(title);
    layout->addWidget(btnStart);
    layout->addWidget(btnExit);
    layout->addStretch();
    layout->setAlignment(Qt::AlignCenter);


    connect(btnStart, &QPushButton::clicked, this, &MenuWidget::onStartClicked);
    connect(btnExit, &QPushButton::clicked, this, &MenuWidget::onExitClicked);

}
