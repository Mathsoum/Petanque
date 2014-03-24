#include "match.h"

#include <QVariantList>

Match::Match(const Team &first, const Team &second)
{
  mState = PENDING;

  mMatch.first = first;
  mMatch.second = second;
  mWinner = NONE;

  if( second == Team() ) {
    mState = FINISHED;
    mWinner = FIRST;
  }
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
  mWinner = firstWin ? FIRST : SECOND;
}

Team Match::getWinner() const
{
  return mWinner == NONE ? Team() : mWinner == FIRST ? mMatch.first : mMatch.second;
}

bool operator==( const Match &one, const Match &other ) {
    return (one.teams().first == other.teams().first || one.teams().first == other.teams().second)
            && (one.teams().second == other.teams().first || one.teams().second == other.teams().second) ;
}

