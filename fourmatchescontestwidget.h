#ifndef FOURMATCHESCONTESTWIDGET_H
#define FOURMATCHESCONTESTWIDGET_H

#include <QWidget>

class QTableView;
class FourMatchesContest;
class Match;

namespace Ui {
class FourMatchesContestWidget;
}

class FourMatchesContestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FourMatchesContestWidget(QWidget *parent = 0);
    ~FourMatchesContestWidget();

    QList<QTableView*> getTableViewList() const;
public slots:
    void setSubmitScoreButtonStateSlot();
    void teamViewSelectionChanged(const QModelIndex &selectedIndex);
    void setUpWinnerSlot();
    void setUpWinnerFromSubmitButtonSlot();

private:
    void configGui();
    void prepareTableView(QTableView *tableViewToPrepare);
    Match *getCurrentSelectedMatch(QTableView *tableView);

private:
    Ui::FourMatchesContestWidget *ui;

    FourMatchesContest* mFourMatchesContest;
};

#endif // FOURMATCHESCONTESTWIDGET_H
