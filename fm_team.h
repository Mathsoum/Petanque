#ifndef FM_TEAM_H
#define FM_TEAM_H

#include <QMap>

#include "team.h"

class FM_Team : public Team
{
public:
    FM_Team(const QString& name = "", const QString& club = NON_HOMOGENE);

    int getWinCount(void) const;
    bool hasWin(int phase) const;
    bool hasPlayed(int phase) const;

    void setWinForPhase(int phase);
    void setLoseForPhase(int phase);

private:
    QMap<int, bool> mPlayedByPhase;
    QMap<int, bool> mWinByPhase;
    int mMatchCount;
};

QDataStream &operator<<(QDataStream& out, const FM_Team& team);
bool operator==( const FM_Team& one, const FM_Team& other );
uint qHash(const FM_Team &team);

#endif // FM_TEAM_H
