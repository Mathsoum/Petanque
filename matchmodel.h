#ifndef MATCHMODEL_H
#define MATCHMODEL_H

#include <QAbstractItemModel>

#include "match.h"

class TeamModel;
class QAction;

class MatchModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit MatchModel(QObject *parent = 0);
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

    inline QList<Match*> getRawData() const { return mMatchList; }

    bool exists( const Match &match ) const;
    void addMatch( Match *match );
    void setFinished(Match *match, bool firstWins );
    int notFinishedYet() const;

private:
    QList<Match*> mMatchList;

};

#endif // MATCHMODEL_H
