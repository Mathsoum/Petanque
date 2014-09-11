#ifndef CONTEST_H
#define CONTEST_H

#include <QObject>

#include "match.h"
#include "fm_team.h"

class PhaseModel;

//TODO Get rid of all the MatchModels for PhaseModels.
// It's a start over, let's get messy !
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

  PhaseModel *getPhaseModel(int phase = 0, int winCount = 0) const;

  void initContest( void );
  void setFinished(int phase, FM_Team *winner, FM_Team *looser);

private:
  void addTeamToFirstPhase(const FM_Team& team);

private:
  State mState;

  PhaseModel* mFirstPhase;

  PhaseModel* mSecondPhaseOneWin;
  PhaseModel* mSecondPhaseNoWin;

  PhaseModel* mThirdPhaseTwoWin;
  PhaseModel* mThirdPhaseOneWin;
  PhaseModel* mThirdPhaseNoWin;

  PhaseModel* mFourthPhaseThreeWin;
  PhaseModel* mFourthPhaseTwoWin;
  PhaseModel* mFourthPhaseOneWin;
  PhaseModel* mFourthPhaseNoWin;
};

#endif // CONTEST_H
