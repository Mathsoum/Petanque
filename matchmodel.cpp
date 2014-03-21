#include "matchmodel.h"

#include "teammodel.h"
#include "util.h"

#include <QBrush>

MatchModel::MatchModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

int MatchModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid()) {
        return 0;
    }
    return 2;
}

int MatchModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid()) {
        return 0;
    }
    return mMatchList.size();
}

QVariant MatchModel::data(const QModelIndex &index, int role) const
{
    switch( role ) {
      case Qt::DisplayRole:
        return QVariant( index.column() == 0 ?
                           mMatchList.at( index.row() ).teams().first.getName()
                         : mMatchList.at( index.row() ).teams().second.getName() );
        break;
      case Qt::BackgroundRole:
        if( data( index, Qt::DisplayRole ).toString().isEmpty() ) {
          return QVariant( QBrush( Qt::Dense5Pattern ) );
        }
        break;
      case Qt::ForegroundRole:
        if( mMatchList.at( index.row() ).isFinished() ) {
          ( QVariant( mMatchList.at( index.row() ).getWinner() ) ==  data( index, Qt::DisplayRole )) ? QVariant( Qt::darkGreen ) : QVariant( Qt::red );
        }
      case Qt::TextAlignmentRole:
        return QVariant( Qt::AlignCenter );
    }

    return QVariant();
}

QModelIndex MatchModel::index(int row, int column, const QModelIndex &) const
{
    return createIndex(row, column);
}

QModelIndex MatchModel::parent(const QModelIndex &) const
{
  return QModelIndex();
}

void MatchModel::generateMatchList(TeamModel *teams, const QList<Match> &alreadyPlayed )
{
  bool firstGeneration = alreadyPlayed.isEmpty();

  QList<Team> teamsList = teams->getRawData();

  Util<Team>::shuffle( &teamsList );

  for(int i = 0; i < teamsList.size()-1; i+=2) {
      mMatchList.append( Match( teamsList.at( i ), teamsList.at( i + 1 ) ) );
  }
  if(teamsList.size() % 2 != 0) {
      mMatchList.append( Match( teamsList.back(), Team() ) );
  }

  beginInsertRows(QModelIndex(), 0, mMatchList.size() - 1);
}
