#ifndef MATCH_H
#define MATCH_H

#include <QString>
#include <QPair>
#include <team.h>

class Match
{
public:
  enum State {
    PENDING,
    PLAYING,
    FINISHED
  };

  enum Winner {
    NONE,
    FIRST,
    SECOND
  };

  Match( const Team& first = Team(), const Team& second = Team() );

  QPair<Team,Team> teams() const;

  void changeToPlaying();
  void changeToFinished( bool firstWin );

  Team getWinner() const;
  inline bool isFinished() const { return mState == FINISHED; }

private:
  QPair<Team,Team> mMatch;
  State mState;
  Winner mWinner;
};

bool operator==( const Match &one, const Match &other );

#endif // MATCH_H
