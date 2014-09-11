#ifndef FOURMATCHESCONTESTWIDGET_H
#define FOURMATCHESCONTESTWIDGET_H

#include <QWidget>
#include <QTableView>

class QTableView;
class FourMatchesContest;
class FM_Team;

namespace Ui {
class FourMatchesContestWidget;
}

class FourMatchesContestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FourMatchesContestWidget(QWidget *parent = 0);
    ~FourMatchesContestWidget();

    FourMatchesContest* getContest() const;

    void setupFirstPhaseView();
    void setupSecondPhase();
    void setupThirdPhase();
    void setupFourthPhase();
public slots:
    void setSubmitScoreButtonStateSlot();
    void teamViewSelectionChanged(const QModelIndex &selectedIndex);
    void setUpWinnerSlot();
    void setUpWinnerFromSubmitButtonSlot();

private slots:
    void firstViewSelected();

    void secondViewOneWinSelected();
    void secondViewNoWinSelected();

    void thirdViewTwoWinSelected();
    void thirdViewOneWinSelected();
    void thirdViewNoWinSelected();

    void fourthViewThreeWinSelected();
    void fourthViewTwoWinSelected();
    void fourthViewOneWinSelected();
    void fourthViewNoWinSelected();

signals:
    void currentPhaseOver();

private:
    void configGui();
    void prepareTableView(QTableView *tableViewToPrepare);
    QVector<FM_Team *> getSelectedMatch() const;

private:
    Ui::FourMatchesContestWidget *ui;

    FourMatchesContest* mFourMatchesContest;

    QTableView* mCurrentSelectedView;
    int mCurrentSelectedPhase;
};

#endif // FOURMATCHESCONTESTWIDGET_H
