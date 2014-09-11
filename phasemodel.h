#ifndef PHASEMODEL_H
#define PHASEMODEL_H

#include "fm_team.h"

#include <QAbstractItemModel>

class PhaseModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit PhaseModel(int maxCount = 0, int phase = 0, QObject *parent = 0);

    int columnCount(const QModelIndex &) const;
    int rowCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;

    QModelIndex index(int row, int column, const QModelIndex &) const;
    QModelIndex parent(const QModelIndex &) const;

    bool addTeam(FM_Team* team);
    FM_Team *getTeam(const QModelIndex& index);
signals:

public slots:

private:
    QList<FM_Team*> mTeamList;
    int mMaxCount;
    int mTeamCount;
    int mCurrentPhase;
};

#endif // PHASEMODEL_H
