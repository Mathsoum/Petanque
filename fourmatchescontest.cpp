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

  mFirstPhase = new PhaseModel(teamCount);

  mSecondPhaseNoWin = new PhaseModel((teamCount / 2) + teamCount % 2);
  mSecondPhaseOneWin = new PhaseModel(teamCount / 2);

  mThirdPhaseNoWin = new PhaseModel((teamCount / 4) + teamCount % 2);
  mThirdPhaseOneWin = new PhaseModel(teamCount / 2);
  mThirdPhaseTwoWin = new PhaseModel(teamCount / 4);

  mFourthPhaseNoWin = new PhaseModel((teamCount / 8) + teamCount % 2);
  mFourthPhaseOneWin = new PhaseModel((3*teamCount) / 8);
  mFourthPhaseTwoWin = new PhaseModel((3*teamCount) / 8);
  mFourthPhaseThreeWin = new PhaseModel(teamCount / 8);
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
        addTeamToFirstPhase(new FM_Team(teamList.at(0).getName(), teamList.at(0).getClub()));
        teamList.removeFirst();
    }
}

void FourMatchesContest::setFinished(int phase, FM_Team* winner, FM_Team* loser)
{
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

void FourMatchesContest::addTeamToFirstPhase(FM_Team* team)
{
    mFirstPhase->addTeam(team);
}

PhaseModel *FourMatchesContest::getPhaseModel(int phase, int winCount) const
{
    qDebug() << "Get phase model";
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
