#include "matchmodel.h"

#include "teammodel.h"

#include <QBrush>
#include <QDebug>
#include <QFont>

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
                       mMatchList.at( index.row() )->players().first.getName()
                     : mMatchList.at( index.row() )->players().second.getName() );
    break;
  case Qt::BackgroundRole:
    if( data( index, Qt::DisplayRole ).toString().isEmpty() ) {
      return QVariant( QBrush( Qt::Dense5Pattern ) );
    } else if( mMatchList.at( index.row() )->isFinished() ) {
      return ( mMatchList.at( index.row() )->getWinner().getName() == data( index, Qt::DisplayRole )) ?
                    QBrush( QColor(105, 220, 140), Qt::Dense6Pattern )
                  : QBrush( QColor(255, 128, 128), Qt::Dense6Pattern );
    }
    break;
  case Qt::FontRole:
    {
      QFont font;
      font.setBold( mMatchList.at( index.row() )->isFinished() );
      return font;
      break;
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

bool MatchModel::exists(const Match &match) const
{
  bool exists = false;
  for( QList<Match*>::const_iterator it = mMatchList.constBegin(); it != mMatchList.constEnd() && !exists; it++ ) {
    exists |= ( *( *it ) == match );
  }
  return exists;
}

void MatchModel::addMatch( Match *match )
{
  beginInsertRows( QModelIndex(), mMatchList.size(), mMatchList.size());
  mMatchList.append( match );
  //qDebug() << "matchList.size() == " << mMatchList.size();
  endInsertRows();
}

void MatchModel::setFinished( Match* match, bool firstWins )
{
  match->changeToFinished( firstWins );
  emit dataChanged( index( mMatchList.indexOf( match ), 0 ), index( mMatchList.indexOf( match ), 1 ) );
}

int MatchModel::notFinishedYet() const
{
  int count = mMatchList.size();
  Q_FOREACH( Match* match, mMatchList ) {
    if( match->isFinished() ) --count;
  }
  return count;
}
