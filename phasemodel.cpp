#include "phasemodel.h"

#include <QBrush>

PhaseModel::PhaseModel(int currentPhase, int maxCount, QObject *parent) :
    QAbstractItemModel(parent)
{
    mMaxCount = maxCount;
    for(int i = 0; i < mMaxCount; ++i) {
        mTeamList.append(NULL);
    }
}

int PhaseModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

int PhaseModel::rowCount(const QModelIndex &parent) const
{
    return mMaxCount;
}

QVariant PhaseModel::data(const QModelIndex &index, int role) const
{
    FM_Team* team = mTeamList.at(index.row() * 2 + index.column() % 2);
    if (team == NULL) {
        return QVariant();
    }

    switch(role) {
    case Qt::DisplayRole:
        return QVariant(team->getName());
        break;
    case Qt::BackgroundRole:
        if(team->hasWin(mCurrentPhase)) {
            return QBrush(Qt::green, Qt::Dense5Pattern);
        } else {
            return QBrush(Qt::red, Qt::Dense5Pattern);
        }
        break;
    }

    return QVariant();
}

QModelIndex PhaseModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row, column);
}

QModelIndex PhaseModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}
