#ifndef CONTEST_H
#define CONTEST_H

#include <QObject>
#include <QHash>
#include <QList>

#include "match.h"

class MatchModel;
class Phase;

class FourMatchesContest : public QObject
{
  Q_OBJECT
public:

  enum State {
    NOT_STARTED_YET = 0,
    FIRST_GAME      = 1,
    SECOND_GAME     = 2,
    THIRD_GAME      = 3,
    FOURTH_GAME     = 4
  };

  enum WinCount {
      NONE  = 0,
      ONE   = 1,
      TWO   = 2,
      THREE = 3,
      FOUR  = 4
  };

  FourMatchesContest(QObject *parent = 0);
  ~FourMatchesContest();

  MatchModel *getCurrentMatchModel() const;
  QList<MatchModel *> getMatchModelList() const;

  void initContest( void );

  void addMatchToCurrentPhase(const Team &initialTeam, const Team &teamAvailable);
  int currentPhase() const;

  void setParticipants(QList<Team*> teamList);

public slots:
  void nextState();

private:
  void generateNextMatchList();
  QList<Team> teamsAvailableToPlayAgainst(const Team &team, const QList<Team> &teamsToPlayAgainst );
  QList<Team> getTeamsAlreadyBeenExempt() const;

private:
  QList<Phase*> phaseList;
  QList<Team*> participants;





  State mState;

  QHash<WinCount, QList<Team> > teamAgainstWinCountMap;

  MatchModel* mFirstPhase;
  MatchModel* mSecondPhase;
  MatchModel* mThirdPhase;
  MatchModel* mFourthPhase;
};

#endif // CONTEST_H
