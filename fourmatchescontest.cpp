#include "fourmatchescontest.h"
#include "util.h"

#include "matchmodel.h"
#include "teammodel.h"

#include <QDebug>

FourMatchesContest::FourMatchesContest(QObject *)
{
  mState = NOT_STARTED_YET;

  mFirstPhase = NULL;
  mSecondPhaseOneWin = NULL;
  mThirdPhaseTwoWin = NULL;
  mFourthPhaseThreeWin = NULL;
}

FourMatchesContest::~FourMatchesContest()
{
  switch( mState ) {
    case NOT_STARTED_YET:
      break;
    case FOURTH_GAME:
      delete mFourthPhaseThreeWin;
    case THIRD_GAME:
      delete mThirdPhaseTwoWin;
    case SECOND_GAME:
      delete mSecondPhaseOneWin;
    case FIRST_GAME:
      delete mFirstPhase;
      break;
  }

}

MatchModel *FourMatchesContest::getCurrentMatchModel() const
{
    switch( mState ) {
        case NOT_STARTED_YET:
            return NULL;
            break;
        case FIRST_GAME:
            return mFirstPhase;
            break;
        case SECOND_GAME:
            return mSecondPhaseOneWin;
            break;
        case THIRD_GAME:
            return mThirdPhaseTwoWin;
            break;
        case FOURTH_GAME:
            return mFourthPhaseThreeWin;
            break;
        default:
            return NULL;
    }
}

void FourMatchesContest::initContest()
{
    nextState();
}

void FourMatchesContest::addMatchToFirstPhase(const Team &firstTeam, const Team &secondTeam)
{
    mFirstPhase->addMatch(new Match(firstTeam, secondTeam));
}

void FourMatchesContest::nextState()
{
    int teamCount = TeamModel::getInstance()->getRawData().count();
  switch( mState ) {
    case NOT_STARTED_YET:
      mFirstPhase = new MatchModel(teamCount);
      generateFirstMatchList();
      mState = FIRST_GAME;
      break;
    case FIRST_GAME:
      mSecondPhaseOneWin = new MatchModel(teamCount / 2 + teamCount % 2);
      mSecondPhaseNoWin = new MatchModel(teamCount / 2);
      generateNextMatchList();
      mState = SECOND_GAME;
      break;
    case SECOND_GAME:
      mThirdPhaseTwoWin = new MatchModel(teamCount / 4 + teamCount % 2);
      mThirdPhaseOneWin = new MatchModel(teamCount / 2);
      mThirdPhaseNoWin = new MatchModel(teamCount / 4);
      generateNextMatchList();
      mState = THIRD_GAME;
      break;
    case THIRD_GAME:
      mFourthPhaseThreeWin = new MatchModel(teamCount / 8);
      mFourthPhaseTwoWin = new MatchModel((3 * teamCount) / 8);
      mFourthPhaseOneWin = new MatchModel((3 * teamCount) / 8);
      mFourthPhaseNoWin = new MatchModel(teamCount / 8);
      generateNextMatchList();
      mState = FOURTH_GAME;
      break;
    case FOURTH_GAME:
      // Unreachable
      break;
    }
}

void FourMatchesContest::addMatchToCurrentPhase(const Team& initialTeam, const Team& teamAvailable)
{
    switch( mState ) {
    case NOT_STARTED_YET:
        mFirstPhase->addMatch( new Match( initialTeam, teamAvailable ) );
      break;
    case FIRST_GAME:
        mSecondPhaseOneWin->addMatch( new Match( initialTeam, teamAvailable ) );
      break;
    case SECOND_GAME:
        mThirdPhaseTwoWin->addMatch( new Match( initialTeam, teamAvailable ) );
      break;
    case THIRD_GAME:
        mFourthPhaseThreeWin->addMatch( new Match( initialTeam, teamAvailable ) );
      break;
    case FOURTH_GAME:
      // Unreachable
      break;
    }
}

int FourMatchesContest::currentPhase() const
{
    return mState;
}

bool FourMatchesContest::isCurrentPhaseOver() const
{
    switch( mState ) {
        case FIRST_GAME:
            return mFirstPhase->notFinishedYet() == 0;
            break;
        case SECOND_GAME:
            return mSecondPhaseOneWin->notFinishedYet() == 0;
            break;
        case THIRD_GAME:
            return mThirdPhaseTwoWin->notFinishedYet() == 0;
            break;
        case FOURTH_GAME:
            return mFourthPhaseThreeWin->notFinishedYet() == 0;
            break;
        default:
            //Unreachable
            return false;
            break;
        }
}

bool category(const Team& team, int category) {
    return false;
}

/* TODO Old system. Random generation of matches.
 *
 * Should generate next matches regarding previous team victories
 */
void FourMatchesContest::generateNextMatchList()
{
    QList<Team> teamsList = TeamModel::getInstance()->getRawData();

    Util<Team>::shuffle( &teamsList );
    //qDebug() << "Is teamsList.size() even ? " << (teamsList.size() % 2 == 0);

    if(teamsList.size() % 2 != 0 && mState != NOT_STARTED_YET) {
        QList<Team> mustPlay = getTeamsAlreadyBeenExempt();
    //      qDebug() << "Must play :";
    //      Q_FOREACH(Team team, mustPlay) {
    //          qDebug() << team.getName();
    //      }
    //      qDebug() << "";

        while( !mustPlay.isEmpty() ) {
            QList<Team> teamsAvailable = teamsAvailableToPlayAgainst( mustPlay.first(), teamsList );
            //qDebug() << "New match " << teamsList.first().getName() << " vs " << teamsAvailable.first().getName();
            addMatchToCurrentPhase( mustPlay.first(), teamsAvailable.first() );
            teamsList.removeOne( mustPlay.first() );
            teamsList.removeOne( teamsAvailable.first() );
            mustPlay.removeFirst();
      }
    }

    while(!teamsList.isEmpty()) {
        //qDebug() << " >> teamsList.size() == " << teamsList.size();
        if(teamsList.size() > 1) {
            QList<Team> teamsAvailable = teamsAvailableToPlayAgainst( teamsList.first(), teamsList );
            //qDebug() << "New match " << teamsList.first().getName() << " vs " << teamsAvailable.first().getName();
            addMatchToCurrentPhase( teamsList.first(), teamsAvailable.first() );
            teamsList.removeFirst();
            teamsList.removeOne( teamsAvailable.first() );
        } else if(teamsList.size() == 1) {
            //qDebug() << "Generate last match with " << teamsList.first().getName();
            addMatchToCurrentPhase( teamsList.first(), Team() );
            teamsList.removeFirst();
        }
    }
}

void FourMatchesContest::generateFirstMatchList()
{
    QList<Team> teamList = TeamModel::getInstance()->getRawData();
    Util<Team>::shuffle(&teamList);

    while(!teamList.isEmpty()) {
        if(teamList.size() == 1) {
            addMatchToFirstPhase(teamList.first(), Team());
            teamList.removeFirst();
        } else {
            addMatchToFirstPhase(teamList.at(0), teamList.at(1));
            teamList.removeFirst();
            teamList.removeFirst();
        }
    }
}

QList<Team> FourMatchesContest::teamsAvailableToPlayAgainst(const Team& team, const QList<Team> &teamsToPlayAgainst )
{
  QList<Team> ret = teamsToPlayAgainst.mid(1);

    for(int i = 0; i < ret.size(); ++i) {
        Team currentTeam = ret.at( i );
        if(currentTeam == team) continue;

        bool alreadyExists = false;
        if (mFirstPhase != NULL) {
          alreadyExists |= mFirstPhase->exists( Match( team, currentTeam ) )
                          || mFirstPhase->exists( Match( currentTeam, team ) );
        }
        if (mSecondPhaseOneWin != NULL) {
          alreadyExists |= mSecondPhaseOneWin->exists( Match( team, currentTeam ) )
                          || mSecondPhaseOneWin->exists( Match( currentTeam, team ) );
        }
        if (mThirdPhaseTwoWin != NULL) {
          alreadyExists |= mThirdPhaseTwoWin->exists( Match( team, currentTeam ) )
                          || mThirdPhaseTwoWin->exists( Match( currentTeam, team ) );
        }
        if (mFourthPhaseThreeWin != NULL) {
          alreadyExists |= mFourthPhaseThreeWin->exists( Match( team, currentTeam ) )
                          || mFourthPhaseThreeWin->exists( Match( currentTeam, team ) );
        }

        if ( alreadyExists ) {
          ret.removeAt( i );
          --i;
        }
    }
    return ret;
}

QList<Team> FourMatchesContest::getTeamsAlreadyBeenExempt() const
{
  QSet<Team> ret;

  if ( mFirstPhase != NULL && !mFirstPhase->getRawData().isEmpty() ) {
    ret.insert( mFirstPhase->getRawData().last()->teams().first );
  }
  if ( mSecondPhaseOneWin != NULL && !mSecondPhaseOneWin->getRawData().isEmpty() ) {
    ret.insert( mSecondPhaseOneWin->getRawData().last()->teams().first );
  }
  if ( mThirdPhaseTwoWin != NULL && !mThirdPhaseTwoWin->getRawData().isEmpty() ) {
    ret.insert( mThirdPhaseTwoWin->getRawData().last()->teams().first );
  }
  if ( mFourthPhaseThreeWin != NULL && !mFourthPhaseThreeWin->getRawData().isEmpty() ) {
    ret.insert( mFourthPhaseThreeWin->getRawData().last()->teams().first );
  }

  return ret.toList();
}



QList<MatchModel *> FourMatchesContest::getMatchModelList() const
{
  QList<MatchModel *> list;
  list << mFirstPhase << mSecondPhaseOneWin << mThirdPhaseTwoWin << mFourthPhaseThreeWin;
  return list;
}
