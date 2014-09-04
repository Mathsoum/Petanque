#include "fm_team.h"

FM_Team::FM_Team()
{
    mMatchCount = 0;
    mWinByPhase.insert(0, false);
    mWinByPhase.insert(1, false);
    mWinByPhase.insert(2, false);
    mWinByPhase.insert(3, false);
}

int FM_Team::getWinCount() const
{
    int count = 0;
    Q_FOREACH(int phase, mWinByPhase.keys()) {
        if (mWinByPhase.value(phase)) {
            ++count;
        }
    }

    return count;
}

bool FM_Team::hasWin(int phase) const
{
    return mWinByPhase.value(phase);
}
