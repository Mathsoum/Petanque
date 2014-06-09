#include "match.h"

#include <QVariantList>

Match::Match(const Team &first, const Team &second)
{
  mState = PENDING;

  players.first = first;
  players.second = second;
  mWinner = NONE;

  if( second == Team() ) {
    mState = FINISHED;
    mWinner = FIRST;
  }
}

QPair<Team, Team> Match::players() const
{
  return players;
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
  return mWinner == NONE ? Team() : mWinner == FIRST ? players.first : players.second;
}

bool operator==( const Match &one, const Match &other ) {
    return (one.players().first == other.players().first || one.players().first == other.players().second)
            && (one.players().second == other.players().first || one.players().second == other.players().second) ;
}

