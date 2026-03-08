#ifndef SETTING_MANAGER_H
#define SETTING_MANAGER_H

#include <QObject>
#include <QSettings>
class SettingsManager: public QObject
{
    Q_OBJECT
public:
    static SettingsManager& instance();
    int getMaxScore() const {return m_MaxScore;}

    void loadSettings();
    void saveSettings();

    int totalyCoutLines() const;
    void updateTotalyCoutLines(int oneGameTotalyCoutLines);
    QString nickname() const;



    void updateNickname(const QString &newNickname);

    bool updateMaxScore(int score);
    void updateCountGames();
    int getCountGames() const;

signals:
    void  settingsReaded();
    void  scoresChanged();
private:
     explicit SettingsManager(QObject *parent = nullptr);
    QSettings* m_settings;
    int m_MaxScore;
    int m_totalyCoutLines;
    int m_countGames;
    QString m_nickname;

};

#endif // SETTING_MANAGER_H
