#include "fourmatchescontest.h"
#include "util.h"

#include "matchmodel.h"
#include "phasemodel.h"
#include "teammodel.h"

#include <QDebug>

FourMatchesContest::FourMatchesContest(QObject *)
{
  mState = NOT_STARTED_YET;

  int teamCount = TeamModel::getInstance()->getRawData().size();
  qDebug() << "Team count : " << teamCount;

  int n0 = teamCount;
  mFirstPhase = new PhaseModel(n0, 0);

  int n11 = (n0 / 2) + (n0 % 2);
  int n10 = (n0 / 2);
  mSecondPhaseOneWin = new PhaseModel(n11, 1);
  mSecondPhaseNoWin = new PhaseModel(n10, 1);

  int n22 = (n11 / 2) + (n11 % 2);
  int n21 = (n11 / 2) + (n10 / 2) + (n10 % 2);
  int n20 = (n10 / 2);
  mThirdPhaseTwoWin = new PhaseModel(n22, 2);
  mThirdPhaseOneWin = new PhaseModel(n21, 2);
  mThirdPhaseNoWin = new PhaseModel(n20, 2);

  int n33 = (n22 / 2) + (n22 % 2);
  int n32 = (n22 / 2) + (n21 / 2);
  n32 +=  + (n32 % 2);
  int n31 = (n21 / 2) + (n20 / 2);
  n31 -=  + (n31 % 2);
  int n30 = (n20 / 2);
  mFourthPhaseThreeWin = new PhaseModel(n33, 3);
  mFourthPhaseTwoWin = new PhaseModel(n32, 3);
  mFourthPhaseOneWin = new PhaseModel(n31, 3);
  mFourthPhaseNoWin = new PhaseModel(n30, 3);
}

FourMatchesContest::~FourMatchesContest()
{
    delete mFirstPhase;

    delete mSecondPhaseNoWin;
    delete mSecondPhaseOneWin;

    delete mThirdPhaseNoWin;
    delete mThirdPhaseOneWin;
    delete mThirdPhaseTwoWin;

    delete mFourthPhaseNoWin;
    delete mFourthPhaseOneWin;
    delete mFourthPhaseTwoWin;
    delete mFourthPhaseThreeWin;
}

void FourMatchesContest::initContest()
{
    QList<Team> teamList = TeamModel::getInstance()->getRawData();
    Util<Team>::shuffle(&teamList);

    while(!teamList.isEmpty()) {
        addTeamToFirstPhase(FM_Team(teamList.at(0).getName(), teamList.at(0).getClub()));
        teamList.removeFirst();
    }
}

void FourMatchesContest::setFinished(int phase, FM_Team* winner, FM_Team* loser)
{
    if (loser == NULL) {
        setExempt(phase, winner);
    } else {
        qDebug() << "Set finished";
        winner->setWinForPhase(phase);
        loser->setLoseForPhase(phase);

        switch(phase) {
        case 0:
            qDebug() << "Phase 0";
            mSecondPhaseOneWin->addTeam(winner);
            mSecondPhaseNoWin->addTeam(loser);
            break;
        case 1:
            qDebug() << "Phase 1";
            if(winner->getWinCount() == 1) {
                mThirdPhaseOneWin->addTeam(winner);
                mThirdPhaseNoWin->addTeam(loser);
            } else {
                mThirdPhaseTwoWin->addTeam(winner);
                mThirdPhaseOneWin->addTeam(loser);
            }
            break;
        case 2:
            qDebug() << "Phase 2";
            if (winner->getWinCount() == 1) {
                mFourthPhaseOneWin->addTeam(winner);
                mFourthPhaseNoWin->addTeam(loser);
            } else if (winner->getWinCount() == 2) {
                mFourthPhaseTwoWin->addTeam(winner);
                mFourthPhaseOneWin->addTeam(loser);
            } else {
                mFourthPhaseThreeWin->addTeam(winner);
                mFourthPhaseTwoWin->addTeam(loser);
            }
            break;
        case 3:
            qDebug() << "Phase 3";
            break;
        }
    }
}

void FourMatchesContest::setExempt(int phase, FM_Team *exemptTeam)
{
    qDebug() << "Set exempt";
    switch(phase) {
    case 0:
        qDebug() << "Phase 0";
        mSecondPhaseOneWin->addTeam(exemptTeam);
        break;
    case 1:
        qDebug() << "Phase 1";
        if(exemptTeam->getWinCount() == 1) {
            mThirdPhaseOneWin->addTeam(exemptTeam);
        } else {
            mThirdPhaseTwoWin->addTeam(exemptTeam);
        }
        break;
    case 2:
        qDebug() << "Phase 2";
        if (exemptTeam->getWinCount() == 1) {
            mFourthPhaseOneWin->addTeam(exemptTeam);
        } else if (exemptTeam->getWinCount() == 2) {
            mFourthPhaseTwoWin->addTeam(exemptTeam);
        } else {
            mFourthPhaseThreeWin->addTeam(exemptTeam);
        }
        break;
    case 3:
        qDebug() << "Phase 3";
        break;
    }
}

void FourMatchesContest::addTeamToFirstPhase(const FM_Team &team)
{
    FM_Team* newTeam = new FM_Team(team.getName(), team.getClub());
    mFirstPhase->addTeam(newTeam);
    if (newTeam->hasWin(0)) {
        setExempt(0, newTeam);
    }
}

PhaseModel *FourMatchesContest::getPhaseModel(int phase, int winCount) const
{
    switch(phase) {
    case 0:
        return mFirstPhase;
        break;
    case 1:
        return (winCount == 0 ? mSecondPhaseNoWin : mSecondPhaseOneWin);
        break;
    case 2:
        return (winCount == 0 ? mThirdPhaseNoWin : (winCount == 1 ? mThirdPhaseOneWin : mThirdPhaseTwoWin));
        break;
    case 3:
        return (winCount == 0 ? mFourthPhaseNoWin : (winCount == 1 ? mFourthPhaseOneWin :
                                                                    (winCount == 2 ? mFourthPhaseTwoWin : mFourthPhaseThreeWin)));
        break;
    }

    return NULL;
}
