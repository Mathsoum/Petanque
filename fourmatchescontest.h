#ifndef CONTEST_H
#define CONTEST_H

#include <QObject>

#include "match.h"

class MatchModel;

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

  FourMatchesContest(QObject *parent = 0);
  ~FourMatchesContest();

  MatchModel *getCurrentMatchModel() const;
  QList<MatchModel *> getMatchModelList() const;

  void initContest( void );

  void addMatchToFirstPhase(const Team &firstTeam, const Team &secondTeam);
  void addMatchToCurrentPhase(const Team &initialTeam, const Team &teamAvailable);
  int currentPhase() const;

  bool isCurrentPhaseOver() const;

public slots:
  void nextState();

private:
  void generateNextMatchList();
  void generateFirstMatchList();

  QList<Team> teamsAvailableToPlayAgainst(const Team &team, const QList<Team> &teamsToPlayAgainst );
  QList<Team> getTeamsAlreadyBeenExempt() const;

private:
  State mState;

  MatchModel* mFirstPhase;

  MatchModel* mSecondPhaseOneWin;
  MatchModel* mSecondPhaseNoWin;

  MatchModel* mThirdPhaseTwoWin;
  MatchModel* mThirdPhaseOneWin;
  MatchModel* mThirdPhaseNoWin;

  MatchModel* mFourthPhaseThreeWin;
  MatchModel* mFourthPhaseTwoWin;
  MatchModel* mFourthPhaseOneWin;
  MatchModel* mFourthPhaseNoWin;
};

#endif // CONTEST_H
