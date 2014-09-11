#include "phasemodel.h"

#include <QBrush>
#include <QDebug>
#include <QList>

PhaseModel::PhaseModel(int maxCount, int phase, QObject *parent) :
    QAbstractItemModel(parent)
{
    mMaxCount = maxCount;
    mTeamCount = 0;
    mCurrentPhase = phase;
    for(int i = 0; i < mMaxCount; ++i) {
        mTeamList.append(NULL);
    }

//    qDebug() << "PhaseModel // Team count : " << mTeamCount;
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
    int listIndex = index.row() * 2 + index.column() % 2;

//    qDebug() << "Data #" << mCurrentPhase << " : Row = " << index.row() << "; Col = " << index.column() << "; Role = " << role;
    switch(role) {
    case Qt::DisplayRole:
        if(listIndex >= mMaxCount) {
            return QString("Empty cell");
        } else {
            return mTeamList.at(listIndex) != NULL ? mTeamList.at(listIndex)->getName() : QString("NULL");
        }
        break;
    case Qt::TextAlignmentRole:
        return QVariant(Qt::AlignCenter);
        break;
    case Qt::BackgroundRole:
      if(listIndex >= mMaxCount) {
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

bool PhaseModel::addTeam(FM_Team* team)
{
    if (mMaxCount == mTeamCount) {
        return false;
    }

    if (!mTeamList.contains(team)) {
        beginInsertRows(QModelIndex(), mTeamList.size(), mTeamList.size());
        mTeamList.replace(mTeamCount, team);
//      qDebug() << "Team #" << mTeamCount << "added : " << team->getName();
        mTeamCount++;
        endInsertRows();
    }

    return true;
}

FM_Team *PhaseModel::getTeam(const QModelIndex &index)
{
    int listIndex = index.row() * 2 + index.column() % 2;
    return listIndex >= mTeamCount ? NULL : mTeamList.at(listIndex);
}
