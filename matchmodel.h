#ifndef MATCHMODEL_H
#define MATCHMODEL_H

#include <QAbstractItemModel>
#include <stdexcept>

#include "match.h"

class TeamModel;
class QAction;

class MatchModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit MatchModel(int maxMatchCount = 0, int winCount = 0, QObject *parent = 0);
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

    inline QList<Match*> getRawData() const { return mMatchList; }

    bool exists( const Match &match ) const;
    bool isMatchListFull() const;
    void addMatch( Match *match ) throw(std::logic_error);
    void setFinished(Match *match, bool firstWins );
    int notFinishedYet() const;

private:
    QList<Match*> mMatchList;
    int mMaxMatchCount;
    int mWinCount;
};

#endif // MATCHMODEL_H
