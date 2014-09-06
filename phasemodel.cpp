#include "phasemodel.h"

#include <QBrush>
#include <QDebug>
#include <QList>

PhaseModel::PhaseModel(int maxCount, QObject *parent) :
    QAbstractItemModel(parent)
{
    mMaxCount = maxCount;
    for(int i = 0; i < mMaxCount; ++i) {
        mTeamList.append(NULL);
    }
}

int PhaseModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 2;
}

int PhaseModel::rowCount(const QModelIndex &/*parent*/) const
{
    return mMaxCount / 2 + mMaxCount % 2;
}

QVariant PhaseModel::data(const QModelIndex &index, int role) const
{
    qDebug() << "Data";
    int listIndex = index.row() * 2 + index.column() % 2;
    switch(role) {
    case Qt::DisplayRole:
        if(mTeamList.size() == listIndex) {
            return QVariant("");
        } else {
            return mTeamList.at(listIndex) != NULL ? mTeamList.at(listIndex)->getName() : QVariant();
        }
        break;
    case Qt::TextAlignmentRole:
        return QVariant(Qt::AlignCenter);
        break;
    case Qt::BackgroundRole:
      if(mTeamList.size() == listIndex) {
        return QVariant(QBrush(Qt::Dense5Pattern));
      } else {
          if (mTeamList.at(listIndex) != NULL && mTeamList.at(listIndex)->hasPlayed(mCurrentPhase)) {
              return mTeamList.at(listIndex)->hasWin(mCurrentPhase) ?
                            QBrush(QColor(105, 220, 140), Qt::Dense6Pattern)
                          : QBrush(QColor(255, 128, 128), Qt::Dense6Pattern);
          }
      }
      break;
    }

    return QVariant();
}

QModelIndex PhaseModel::index(int row, int column, const QModelIndex &/*parent*/) const
{
    return createIndex(row, column);
}

QModelIndex PhaseModel::parent(const QModelIndex &/*child*/) const
{
    return QModelIndex();
}

bool PhaseModel::addTeam(FM_Team *team)
{
    if (mMaxCount == mTeamList.size()) {
        return false;
    }
    beginInsertRows(QModelIndex(), mTeamList.size(), mTeamList.size());
    mTeamList.append(team);
    mMaxCount++;
    endInsertRows();
    return true;
}

FM_Team *PhaseModel::getTeam(const QModelIndex &index)
{
    return mTeamList.at(index.row() * 2 + index.column() % 2);
}
