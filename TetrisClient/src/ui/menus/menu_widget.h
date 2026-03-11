#ifndef MENU_WIDGET_H
#define MENU_WIDGET_H

#include <QWidget>


class QStackedWidget;
class QLabel;
class AuthForm;

class MenuWidget : public QWidget {
    Q_OBJECT
public:
    explicit MenuWidget(QWidget *parent = nullptr);

signals:
    void onStartClicked();
    void onExitClicked();
    void onAuthCompleted(const QString& nickname);

private slots:
    void updateBestScore();
    void updateTotalLines();
    void onUserClicked();
    void onAuthBack();
    void onAuthDone(const QString& nickname);

private:

    void setupUi();
    QWidget* createMainMenu();
    QWidget* createAuthFormPage();
    void updateNicknameUI(const QString& nickname);


    QStackedWidget *m_stackedWidget = nullptr;
    QLabel *m_bestScoreTitle = nullptr;
    QLabel *m_totalLinesTitle = nullptr;
    QLabel *m_nicknameLabel = nullptr;
    AuthForm *m_authForm = nullptr;
};

#endif // MENU_WIDGET_H
