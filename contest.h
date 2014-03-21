#ifndef CONTEST_H
#define CONTEST_H

#include <QObject>

#include "match.h"

class MatchModel;

class Contest : public QObject
{
  Q_OBJECT
public:

  enum State {
    FIRST_GAME,
    SECOND_GAME,
    THIRD_GAME,
    FOURTH_GAME,
  };

  Contest(QObject *parent = 0);
  ~Contest();

  MatchModel *getCurrentMatchModel() const;

  void initContest( void );

public slots:
  void nextState();
  QList<Match> getWinners( MatchModel* model );
  QList<Match> getLoosers( MatchModel* model );


private:
  State mState;

  MatchModel* mFirstPhase;
  MatchModel* mSecondPhase;
  MatchModel* mThirdPhase;
  MatchModel* mFourthPhase;
};

#endif // CONTEST_H
