#include "teammodel.h"

#include <QModelIndex>
#include <QDebug>

TeamModel* TeamModel::mInstance = NULL;

TeamModel::TeamModel(QObject *parent) :
    QAbstractItemModel(parent)
{

}

TeamModel *TeamModel::getInstance()
{
    if(mInstance == NULL) {
        mInstance = new TeamModel;
    }
    return mInstance;
}

int TeamModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid()) {
        return 0;
    }

    return 2;
}

int TeamModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid()) {
        return 0;
    }

    return mTeamList.size();
}

QVariant TeamModel::data(const QModelIndex &index, int role) const
{
  switch( role ) {
    case Qt::DisplayRole:
      if( index.column() == 0 ) {
        return QVariant( mTeamList.at( index.row() ).getName() );
      } else {
        return QVariant( mTeamList.at( index.row() ).getClub() );
      }
      break;
    case Qt::TextAlignmentRole:
      return QVariant( Qt::AlignCenter );
      break;
  }

  return QVariant();
}

bool TeamModel::setData( const QModelIndex &index, const QVariant &value, int role )
{
  if( !index.isValid() ) {
    return false;
  }
  if( index.column() == 0 ) {
    Team buff = mTeamList.at( index.row() );
    buff.setName( value.toString() );
    mTeamList.replace( index.row(), buff );
  } else {
      Team buff = mTeamList.at( index.row() );
      buff.setClub( value.toString() );
      mTeamList.replace( index.row(), buff );
  }
  return true;
}

QVariant TeamModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  switch(orientation) {
    case Qt::Horizontal:
      if( role == Qt::DisplayRole ) {
        return QVariant( section == 0 ? QString::fromUtf8( "Nom équipe" ) : "Nom club" );
      }
      break;
    case Qt::Vertical:
      return QAbstractItemModel::headerData(section, orientation, role);
      break;
  }

  return QVariant();
}

QModelIndex TeamModel::index(int row, int column, const QModelIndex &) const
{
    return createIndex(row, column);
}

QModelIndex TeamModel::parent(const QModelIndex &) const
{
    return QModelIndex();
}

void TeamModel::addTeam(const Team &team)
{
    beginInsertRows(QModelIndex(), mTeamList.size(), mTeamList.size());
    mTeamList.push_back( team );
    endInsertRows();
}

QList<Team> TeamModel::getRawData() const
{
    return mTeamList;
}
