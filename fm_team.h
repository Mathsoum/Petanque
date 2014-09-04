#ifndef FM_TEAM_H
#define FM_TEAM_H

#include <QMap>

#include "team.h"

class FM_Team : public Team
{
public:
    FM_Team();

    int getWinCount(void) const;
    bool hasWin(int phase) const;

private:
    QMap<int, bool> mWinByPhase;
    int mMatchCount;
};

#endif // FM_TEAM_H
