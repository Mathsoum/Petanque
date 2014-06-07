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
    NOT_STARTED_YET,
    FIRST_GAME,
    SECOND_GAME,
    THIRD_GAME,
    FOURTH_GAME,
  };

  FourMatchesContest(QObject *parent = 0);
  ~FourMatchesContest();

  MatchModel *getCurrentMatchModel() const;
  QList<MatchModel *> getMatchModelList() const;

  void initContest( void );

  QList<Match> getWinners( MatchModel* model );
  QList<Match> getLoosers( MatchModel* model );

  void addMatchToCurrentPhase(const Team &initialTeam, const Team &teamAvailable);
public slots:
  void nextState();

private:
  void generateNextMatchList();
  QList<Team> teamsAvailableToPlayAgainst(const Team &team, const QList<Team> &teamsToPlayAgainst );
  QList<Team> getTeamsAlreadyBeenExempt() const;

private:
  State mState;

  MatchModel* mFirstPhase;
  MatchModel* mSecondPhase;
  MatchModel* mThirdPhase;
  MatchModel* mFourthPhase;
};

#endif // CONTEST_H
