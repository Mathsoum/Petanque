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

  Match( const Team& first = Team(), const Team& second = Team() );

  QPair<Team,Team> teams() const;

  void changeToPlaying();
  void changeToFinished( bool firstWin );

  Team getWinner() const;
  inline bool isFinished() const { return mFirstWin; }

private:
  QPair<Team,Team> mMatch;
  State mState;
  bool mFirstWin;
};

#endif // MATCH_H
