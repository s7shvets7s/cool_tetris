#include <QApplication>
#include <ctime>
#include <cstdlib>
#include "MainWindow.h"
#include "network_manager.h"

int main(int argc, char *argv[]) {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("aRecll");
    QCoreApplication::setApplicationName("cool_tetris");
    NetworkManager::instance().setServerAddress("127.0.0.1", 5000);

        // Подключение для отладки
    QObject::connect(&NetworkManager::instance(), &NetworkManager::sendSuccess,
                     [](){ qDebug() << "Статистика отправлена!"; });
    QObject::connect(&NetworkManager::instance(), &NetworkManager::sendError,
                     [](const QString& err){ qDebug() << "Ошибка отправки:" << err; });
    MainWindow window;

#ifdef Q_OS_ANDROID
    window.showMaximized();
#elif defined(Q_OS_IOS)
    window.showFullScreen();
#else

    window.resize(400, 700);
    window.show();
#endif

    return app.exec();
}
