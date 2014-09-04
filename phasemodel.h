#ifndef PHASEMODEL_H
#define PHASEMODEL_H

#include <QAbstractItemModel>

#include "fm_team.h"

class PhaseModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit PhaseModel(int currentPhase, int maxCount, QObject *parent = 0);

    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;


signals:

public slots:

private:
    QList<FM_Team*> mTeamList;
    int mMaxCount;
    int mCurrentPhase;


};

#endif // PHASEMODEL_H
