#include "fm_team.h"

#include <QHash>
#include <QDebug>

FM_Team::FM_Team(const QString &name, const QString &club) : Team(name, club)
{
    mMatchCount = 0;
    mWinByPhase.insert(0, false);
    mWinByPhase.insert(1, false);
    mWinByPhase.insert(2, false);
    mWinByPhase.insert(3, false);

    mPlayedByPhase.insert(0, false);
    mPlayedByPhase.insert(1, false);
    mPlayedByPhase.insert(2, false);
    mPlayedByPhase.insert(3, false);
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

bool FM_Team::hasPlayed(int phase) const
{
    return mPlayedByPhase.value(phase);
}

void FM_Team::setWinForPhase(int phase)
{
    mPlayedByPhase.insert(phase, true);
    mWinByPhase.insert(phase, true);
}

void FM_Team::setLoseForPhase(int phase)
{
    mPlayedByPhase.insert(phase, true);
    mWinByPhase.insert(phase, false);
}

bool operator==( const FM_Team& one, const FM_Team& other ) {
  return one.getName() == other.getName()
          && one.getClub() == other.getClub()
          && one.getWinCount() == other.getWinCount();
}

uint qHash(const FM_Team &team)
{
  return qHash(team.getName()) ^ qHash(team.getClub());
}

QDataStream &operator<<(QDataStream &out, const FM_Team &team)
{
  out << team.getName();
  return out;
}
