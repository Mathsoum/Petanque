#include "contest.h"
#include "util.h"

#include "matchmodel.h"
#include "teammodel.h"

#include <QDebug>

Contest::Contest(QObject *)
{
  mState = NOT_STARTED_YET;

  mFirstPhase = NULL;
  mSecondPhase = NULL;
  mThirdPhase = NULL;
  mFourthPhase = NULL;
}

Contest::~Contest()
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

MatchModel *Contest::getCurrentMatchModel() const
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
    default: // FOURTH_GAME
      return mFourthPhase;
      break;
    }
}

void Contest::initContest()
{
    nextState();
}

QList<Match> Contest::getWinners( MatchModel *model )
{
  return QList<Match>();
}

QList<Match> Contest::getLoosers( MatchModel *model )
{
  return QList<Match>();
}

void Contest::nextState()
{
  switch( mState ) {
    case NOT_STARTED_YET:
      mFirstPhase = new MatchModel();
      generateNextMatchList();
      mState = FIRST_GAME;
      break;
    case FIRST_GAME:
      mSecondPhase = new MatchModel;
      generateNextMatchList();
      mState = SECOND_GAME;
      break;
    case SECOND_GAME:
      mThirdPhase = new MatchModel;
      generateNextMatchList();
      mState = THIRD_GAME;
      break;
    case THIRD_GAME:
      mFourthPhase = new MatchModel;
      generateNextMatchList();
      mState = FOURTH_GAME;
      break;
    case FOURTH_GAME:
      // Should not go there
      break;
    }
}

void Contest::addMatchToCurrentPhase(const Team& initialTeam, const Team& teamAvailable)
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

void Contest::generateNextMatchList()
{
  QList<Team> teamsList = TeamModel::getInstance()->getRawData();

  Util<Team>::shuffle( &teamsList );
  //qDebug() << "Is teamsList.size() even ? " << (teamsList.size() % 2 == 0);

  if( teamsList.size() % 2 != 0 && mState != NOT_STARTED_YET) {
      QList<Team> mustPlay = getTeamsAlreadyBeenExempt();
      //qDebug() << "Must play :";
      Q_FOREACH(Team team, mustPlay) {
          //qDebug() << team.getName();
      }
      //qDebug() << "";

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

QList<Team> Contest::teamsAvailableToPlayAgainst(const Team& team, const QList<Team> &teamsToPlayAgainst )
{
  QList<Team> ret = teamsToPlayAgainst.mid( 1 );

  for( int i = 0; i < ret.size(); ++i ) {
    if( ret.at( i ) == team ) continue;

    bool alreadyExists = false;
    if ( mFirstPhase != NULL ) {
      alreadyExists |= mFirstPhase->exists( Match( team, ret.at( i ) ) )
                      || mFirstPhase->exists( Match( ret.at( i ), team ) );
    }
    if ( mSecondPhase != NULL ) {
      alreadyExists |= mSecondPhase->exists( Match( team, ret.at( i ) ) )
                      || mSecondPhase->exists( Match( ret.at( i ), team ) );
    }
    if ( mThirdPhase != NULL ) {
      alreadyExists |= mThirdPhase->exists( Match( team, ret.at( i ) ) )
                      || mThirdPhase->exists( Match( ret.at( i ), team ) );
    }
    if ( mFourthPhase != NULL ) {
      alreadyExists |= mFourthPhase->exists( Match( team, ret.at( i ) ) )
                      || mFourthPhase->exists( Match( ret.at( i ), team ) );
    }

    if ( alreadyExists ) {
      ret.removeAt( i );
      --i;
    }
  }
  return ret;
}

QList<Team> Contest::getTeamsAlreadyBeenExempt() const
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

