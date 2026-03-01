#include <QApplication>
#include <ctime>
#include <cstdlib>
#include "MainWindow.h" // Подключаем обертку вместо GameWidget

int main(int argc, char *argv[]) {
    // Твой рандом остается
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    QApplication app(argc, argv);

    // Создаем главное окно, которое внутри себя содержит меню и игру
    MainWindow window;
    window.setWindowTitle("Qt Tetris");
    window.resize(400, 600); // Подбери размер под Тетрис
    window.show();

    return app.exec();
}
