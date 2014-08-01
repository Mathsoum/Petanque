#include "fourmatchescontest.h"
#include "util.h"

#include "matchmodel.h"
#include "teammodel.h"

#include <QDebug>

FourMatchesContest::FourMatchesContest(QObject *)
{
  mState = NOT_STARTED_YET;

  mFirstPhase = NULL;
  mSecondPhase = NULL;
  mThirdPhase = NULL;
  mFourthPhase = NULL;
}

FourMatchesContest::~FourMatchesContest()
{
  switch( mState ) {
    case NOT_STARTED_YET:
      break;
    case FOURTH_GAME:
      delete mFourthPhase;
    case THIRD_GAME:
      delete mThirdPhase;
    case SECOND_GAME:
      delete mSecondPhase;
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
            return mSecondPhase;
            break;
        case THIRD_GAME:
            return mThirdPhase;
            break;
        case FOURTH_GAME:
            return mFourthPhase;
            break;
        default:
            return NULL;
    }
}

void FourMatchesContest::initContest()
{
    nextState();
}

void FourMatchesContest::nextState()
{
  switch( mState ) {
    case NOT_STARTED_YET:
      mFirstPhase = new MatchModel();
      generateNextMatchList();
      mState = FIRST_GAME;
      break;
    case FIRST_GAME:
      mSecondPhase = new MatchModel();
      generateNextMatchList();
      mState = SECOND_GAME;
      break;
    case SECOND_GAME:
      mThirdPhase = new MatchModel();
      generateNextMatchList();
      mState = THIRD_GAME;
      break;
    case THIRD_GAME:
      mFourthPhase = new MatchModel();
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
        mSecondPhase->addMatch( new Match( initialTeam, teamAvailable ) );
      break;
    case SECOND_GAME:
        mThirdPhase->addMatch( new Match( initialTeam, teamAvailable ) );
      break;
    case THIRD_GAME:
        mFourthPhase->addMatch( new Match( initialTeam, teamAvailable ) );
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
            return mSecondPhase->notFinishedYet() == 0;
            break;
        case THIRD_GAME:
            return mThirdPhase->notFinishedYet() == 0;
            break;
        case FOURTH_GAME:
            return mFourthPhase->notFinishedYet() == 0;
            break;
        default:
            //Unreachable
            return false;
            break;
        }
}

/* TODO Old system. Random generation of matches.
 *
 * Should generate next matches on the fly !
 * Even over few next phases
 */
void FourMatchesContest::generateNextMatchList()
{
  QList<Team> teamsList = TeamModel::getInstance()->getRawData();

  Util<Team>::shuffle( &teamsList );
  //qDebug() << "Is teamsList.size() even ? " << (teamsList.size() % 2 == 0);

  if( teamsList.size() % 2 != 0 && mState != NOT_STARTED_YET) {
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

  while( !teamsList.isEmpty() ) {
    //qDebug() << " >> teamsList.size() == " << teamsList.size();
    if( teamsList.size() > 1 ) {
      QList<Team> teamsAvailable = teamsAvailableToPlayAgainst( teamsList.first(), teamsList );
      //qDebug() << "New match " << teamsList.first().getName() << " vs " << teamsAvailable.first().getName();
      addMatchToCurrentPhase( teamsList.first(), teamsAvailable.first() );
      teamsList.removeFirst();
      teamsList.removeOne( teamsAvailable.first() );
    } else if( teamsList.size() == 1 ) {
        //qDebug() << "Generate last match with " << teamsList.first().getName();
        addMatchToCurrentPhase( teamsList.first(), Team() );
        teamsList.removeFirst();
    }
  }
}

QList<Team> FourMatchesContest::teamsAvailableToPlayAgainst(const Team& team, const QList<Team> &teamsToPlayAgainst )
{
  QList<Team> ret = teamsToPlayAgainst.mid( 1 );

    for( int i = 0; i < ret.size(); ++i ) {
        Team currentTeam = ret.at( i );
        if( currentTeam == team ) continue;

        bool alreadyExists = false;
        if ( mFirstPhase != NULL ) {
          alreadyExists |= mFirstPhase->exists( Match( team, currentTeam ) )
                          || mFirstPhase->exists( Match( currentTeam, team ) );
        }
        if ( mSecondPhase != NULL ) {
          alreadyExists |= mSecondPhase->exists( Match( team, currentTeam ) )
                          || mSecondPhase->exists( Match( currentTeam, team ) );
        }
        if ( mThirdPhase != NULL ) {
          alreadyExists |= mThirdPhase->exists( Match( team, currentTeam ) )
                          || mThirdPhase->exists( Match( currentTeam, team ) );
        }
        if ( mFourthPhase != NULL ) {
          alreadyExists |= mFourthPhase->exists( Match( team, currentTeam ) )
                          || mFourthPhase->exists( Match( currentTeam, team ) );
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
  if ( mSecondPhase != NULL && !mSecondPhase->getRawData().isEmpty() ) {
    ret.insert( mSecondPhase->getRawData().last()->teams().first );
  }
  if ( mThirdPhase != NULL && !mThirdPhase->getRawData().isEmpty() ) {
    ret.insert( mThirdPhase->getRawData().last()->teams().first );
  }
  if ( mFourthPhase != NULL && !mFourthPhase->getRawData().isEmpty() ) {
    ret.insert( mFourthPhase->getRawData().last()->teams().first );
  }

  return ret.toList();
}



QList<MatchModel *> FourMatchesContest::getMatchModelList() const
{
  QList<MatchModel *> list;
  list << mFirstPhase << mSecondPhase << mThirdPhase << mFourthPhase;
  return list;
}
