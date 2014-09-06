#include "fourmatchescontestwidget.h"
#include "ui_fourmatchescontestwidget.h"

#include "fourmatchescontest.h"
#include "matchmodel.h"
#include "phasemodel.h"
#include "setupwinnerdialog.h"

#include <QDebug>

FourMatchesContestWidget::FourMatchesContestWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FourMatchesContestWidget)
{
  ui->setupUi(this);

  mFourMatchesContest = new FourMatchesContest();
  mFourMatchesContest->initContest();

  ui->firstMatchTableView->setModel( mFourMatchesContest->getPhaseModel(0, 0) );

  ui->secondMatchTableViewNoWin->setModel( mFourMatchesContest->getPhaseModel(1, 0) );
  ui->secondMatchTableViewOneWin->setModel( mFourMatchesContest->getPhaseModel(1, 1) );

  ui->thirdMatchTableViewNoWin->setModel( mFourMatchesContest->getPhaseModel(2, 0) );
  ui->thirdMatchTableViewOneWin->setModel( mFourMatchesContest->getPhaseModel(2, 1) );
  ui->thirdMatchTableViewTwoWin->setModel( mFourMatchesContest->getPhaseModel(2, 2) );

  ui->fourthMatchTableViewNoWin->setModel( mFourMatchesContest->getPhaseModel(3, 0) );
  ui->fourthMatchTableViewOneWin->setModel( mFourMatchesContest->getPhaseModel(3, 1) );
  ui->fourthMatchTableViewTwoWin->setModel( mFourMatchesContest->getPhaseModel(3, 2) );
  ui->fourthMatchTableViewThreeWin->setModel( mFourMatchesContest->getPhaseModel(3, 3) );

  configGui();
}

void FourMatchesContestWidget::prepareTableView(QTableView* tableViewToPrepare)
{
    tableViewToPrepare->verticalHeader()->hide();
    tableViewToPrepare->horizontalHeader()->hide();
    tableViewToPrepare->setSelectionBehavior( QAbstractItemView::SelectRows );
    tableViewToPrepare->setSelectionMode( QAbstractItemView::SingleSelection );

    connect(tableViewToPrepare->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            SLOT(teamViewSelectionChanged(QModelIndex)));
}

QVector<FM_Team *> FourMatchesContestWidget::getSelectedMatch() const
{
    QModelIndex selectedIndex = mCurrentSelectedView->selectionModel()->currentIndex();
    QModelIndex firstTeamIndex = mCurrentSelectedView->model()->index(selectedIndex.row(), 0);
    QModelIndex secondTeamIndex = mCurrentSelectedView->model()->index(selectedIndex.row(), 1);

    FM_Team* firstTeam = ((PhaseModel*)mCurrentSelectedView->model())->getTeam(firstTeamIndex);
    FM_Team* secondTeam = ((PhaseModel*)mCurrentSelectedView->model())->getTeam(secondTeamIndex);

    QVector<FM_Team *> ret;
    ret << firstTeam << secondTeam;

    return ret;
}

void FourMatchesContestWidget::configGui()
{
    prepareTableView(ui->firstMatchTableView);

    prepareTableView(ui->secondMatchTableViewNoWin);
    prepareTableView(ui->secondMatchTableViewOneWin);

    prepareTableView(ui->thirdMatchTableViewNoWin);
    prepareTableView(ui->thirdMatchTableViewOneWin);
    prepareTableView(ui->thirdMatchTableViewTwoWin);

    prepareTableView(ui->fourthMatchTableViewNoWin);
    prepareTableView(ui->fourthMatchTableViewOneWin);
    prepareTableView(ui->fourthMatchTableViewTwoWin);
    prepareTableView(ui->fourthMatchTableViewThreeWin);

    ui->submitScoreButton->setEnabled(false);

    connect(ui->firstMatchTableView->selectionModel(),
            SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            SLOT(firstViewSelected()));

    connect(ui->firstTeamRadioButton, SIGNAL(toggled(bool)), SLOT(setSubmitScoreButtonStateSlot()));
    connect(ui->secondTeamRadioButton, SIGNAL(toggled(bool)), SLOT(setSubmitScoreButtonStateSlot()));
    connect(ui->submitScoreButton, SIGNAL(clicked()), SLOT(setUpWinnerFromSubmitButtonSlot()));
}

FourMatchesContestWidget::~FourMatchesContestWidget()
{
  delete ui;
}

QList<QTableView*> FourMatchesContestWidget::getTableViewList() const
{
  QList<QTableView*> list;
  list << ui->firstMatchTableView << ui->secondMatchTableViewNoWin << ui->thirdMatchTableViewNoWin << ui->fourthMatchTableViewNoWin;
  return list;
}

void FourMatchesContestWidget::setSubmitScoreButtonStateSlot()
{
    ui->submitScoreButton->setEnabled(
        ui->firstTeamRadioButton->isChecked() || ui->secondTeamRadioButton->isChecked()
    );
}

void FourMatchesContestWidget::teamViewSelectionChanged(const QModelIndex& selectedIndex)
{
    qDebug() << "Team selection changed";
    QModelIndex firstTeamIndex = ui->firstMatchTableView->model()->index(selectedIndex.row(), 0);
    QModelIndex secondTeamIndex = ui->firstMatchTableView->model()->index(selectedIndex.row(), 1);

    QString firstTeamName = ui->firstMatchTableView->model()->data(firstTeamIndex).toString();
    QString secondTeamName = ui->firstMatchTableView->model()->data(secondTeamIndex).toString();

    ui->firstTeamRadioButton->setText( firstTeamName );
    ui->secondTeamRadioButton->setText( secondTeamName );

    FM_Team* firstSelectedTeam = ((PhaseModel*)mCurrentSelectedView->model())->getTeam(firstTeamIndex);

    if(firstSelectedTeam->hasPlayed(mCurrentSelectedPhase)) {
        bool firstWins = firstSelectedTeam->hasWin(mCurrentSelectedPhase);
        ui->firstTeamRadioButton->setChecked(firstWins);
        ui->secondTeamRadioButton->setChecked(!firstWins);
    } else {
        ui->firstTeamRadioButton->setAutoExclusive(false);
        ui->firstTeamRadioButton->setChecked(false);
        ui->firstTeamRadioButton->setAutoExclusive(true);
        ui->secondTeamRadioButton->setAutoExclusive(false);
        ui->secondTeamRadioButton->setChecked(false);
        ui->secondTeamRadioButton->setAutoExclusive(true);
    }
}

void FourMatchesContestWidget::setUpWinnerSlot()
{
    qDebug() << "Set up winner slot";
//    SetUpWinnerDialog dialog;
//    Match* selectedMatch = mFourMatchesContest->getCurrentMatchModel()->getRawData().at(
//      ui->firstMatchTableView->selectionModel()->currentIndex().row()
//    );
//    dialog.setMatch( selectedMatch );

//    if( dialog.exec() == QDialog::Accepted ) {
//      mFourMatchesContest->getCurrentMatchModel()->setFinished( selectedMatch, dialog.firstWins() );
//      if( mFourMatchesContest->isCurrentPhaseOver() ) {
//          emit currentPhaseOver();
//          ui->secondMatchTableViewNoWin->setModel( mFourMatchesContest->getCurrentMatchModel() );
//      }
//    }
}

void FourMatchesContestWidget::setUpWinnerFromSubmitButtonSlot()
{
    qDebug() << "Set up winner from submit button slot";
    QVector<FM_Team*> match = getSelectedMatch();
    if (ui->firstTeamRadioButton->isChecked()) {
        mFourMatchesContest->setFinished(mCurrentSelectedPhase, match.at(0), match.at(1));
    } else {
        mFourMatchesContest->setFinished(mCurrentSelectedPhase, match.at(1), match.at(0));
    }

}

void FourMatchesContestWidget::firstViewSelected()
{
    mCurrentSelectedView = ui->firstMatchTableView;
    mCurrentSelectedPhase = 0;
}

void FourMatchesContestWidget::secondViewOneWinSelected()
{
    mCurrentSelectedView = ui->secondMatchTableViewOneWin;
    mCurrentSelectedPhase = 1;
}

void FourMatchesContestWidget::secondViewNoWinSelected()
{
    mCurrentSelectedView = ui->secondMatchTableViewNoWin;
    mCurrentSelectedPhase = 1;
}

void FourMatchesContestWidget::thirdViewTwoWinSelected()
{
    mCurrentSelectedView = ui->thirdMatchTableViewTwoWin;
    mCurrentSelectedPhase = 2;
}

void FourMatchesContestWidget::thirdViewOneWinSelected()
{
    mCurrentSelectedView = ui->thirdMatchTableViewOneWin;
    mCurrentSelectedPhase = 2;
}

void FourMatchesContestWidget::thirdViewNoWinSelected()
{
    mCurrentSelectedView = ui->thirdMatchTableViewNoWin;
    mCurrentSelectedPhase = 2;
}

void FourMatchesContestWidget::fourthViewThreeWinSelected()
{
    mCurrentSelectedView = ui->fourthMatchTableViewThreeWin;
    mCurrentSelectedPhase = 3;
}

void FourMatchesContestWidget::fourthViewTwoWinSelected()
{
    mCurrentSelectedView = ui->fourthMatchTableViewTwoWin;
    mCurrentSelectedPhase = 3;
}

void FourMatchesContestWidget::fourthViewOneWinSelected()
{
    mCurrentSelectedView = ui->fourthMatchTableViewOneWin;
    mCurrentSelectedPhase = 3;
}

void FourMatchesContestWidget::fourthViewNoWinSelected()
{
    mCurrentSelectedView = ui->fourthMatchTableViewNoWin;
    mCurrentSelectedPhase = 3;
}
