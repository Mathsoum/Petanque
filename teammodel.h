#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include "team.h"

#include <QAbstractItemModel>

class TeamModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    static TeamModel *getInstance();

    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

    void addTeam(const Team& team);
    void removeTeam(const Team& team);
    QList<Team> getRawData() const;

private:
    explicit TeamModel(QObject *parent = 0);

private:
    QList<Team> mTeamList;
    static TeamModel *mInstance;

};

#endif // PLAYERMODEL_H
