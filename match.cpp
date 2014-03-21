#include "match.h"

#include <QVariantList>

Match::Match(const Team &first, const Team &second)
{
  mState = PENDING;

  mMatch.first = first;
  mMatch.second = second;
}

QPair<Team, Team> Match::teams() const
{
  return mMatch;
}

void Match::changeToPlaying()
{
  mState = PLAYING;
}

void Match::changeToFinished( bool firstWin )
{
  mState = FINISHED;
  mFirstWin = firstWin;
}

Team Match::getWinner() const
{
  return mFirstWin ? mMatch.first : mMatch.second;
}


