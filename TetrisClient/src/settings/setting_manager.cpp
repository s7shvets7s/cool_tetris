#include "setting_manager.h"

SettingsManager::SettingsManager(QObject *parent) : QObject{parent}
{

    m_settings = new QSettings(this);

    m_MaxScore=0;
     m_totalyCoutLines=0;
     m_nickname="гость";
     m_countGames=0;
}

int SettingsManager::getCountGames() const
{
    return m_countGames;
}

void SettingsManager::updateCountGames()
{
    m_countGames ++;
}

bool SettingsManager::updateMaxScore(int score)
{
    if (score > m_MaxScore) {
        m_MaxScore = score;
        emit scoresChanged();
        return true;
    }
    return false;
}


SettingsManager &SettingsManager::instance()
{
    static SettingsManager instance;
    return instance;
}

void SettingsManager::loadSettings()
{
    m_nickname = m_settings->value("player/name", "Игрок").toString();
    m_MaxScore = m_settings->value("game/bestScore", 0).toInt();
    m_totalyCoutLines= m_settings->value("game/totalyCoutLines",0).toInt();;
    // m_soundVolume = m_settings->value("audio/volume", 70).toInt();
    emit settingsReaded();

}

void SettingsManager::saveSettings()
{
    m_settings->setValue("player/name", m_nickname);
    m_settings->setValue("game/bestScore", m_MaxScore);
    m_settings->setValue("game/totalyCoutLines", m_totalyCoutLines);
    //  m_settings->setValue("audio/volume", m_soundVolume);
    m_settings->sync();
}



int SettingsManager::totalyCoutLines() const
{
    return m_totalyCoutLines;
}

void SettingsManager::updateTotalyCoutLines(int oneGameTotalyCoutLines)
{
    m_totalyCoutLines += oneGameTotalyCoutLines;
    emit scoresChanged();
}

QString SettingsManager::nickname() const
{
    return m_nickname;
}

void SettingsManager::updateNickname(const QString &newNickname)
{
    m_nickname = newNickname;
}
