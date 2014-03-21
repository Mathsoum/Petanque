#include "contest.h"

#include "matchmodel.h"
#include "teammodel.h"

Contest::Contest(QObject *)
{
  mState = FIRST_GAME;
}

Contest::~Contest()
{
  switch( mState ) {
    case FOURTH_GAME:
      delete mFourthPhase;
    case THIRD_GAME:
      delete mThirdPhase;
    case SECOND_GAME:
      delete mSecondPhase;
    case FIRST_GAME:
      delete mFirstPhase;

  }

}

MatchModel *Contest::getCurrentMatchModel() const
{
  switch( mState ) {
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
  mFirstPhase = new MatchModel;
  mFirstPhase->generateMatchList( TeamModel::getInstance() );
}

void Contest::nextState()
{
  switch( mState ) {
    case FIRST_GAME:
      mState = SECOND_GAME;
      mSecondPhase = new MatchModel;
      break;
    case SECOND_GAME:
      mState = THIRD_GAME;
      mThirdPhase = new MatchModel;
      break;
    case THIRD_GAME:
      mState = FOURTH_GAME;
      mFourthPhase = new MatchModel;
      break;
    case FOURTH_GAME:
      // Should not go there
      break;
    }
}

QList<Match> Contest::getWinners( MatchModel *model )
{
  return QList<Match>();
}

QList<Match> Contest::getLoosers( MatchModel *model )
{
  return QList<Match>();
}
