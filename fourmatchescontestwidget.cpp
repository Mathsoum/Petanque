#include "fourmatchescontestwidget.h"
#include "ui_fourmatchescontestwidget.h"

#include "fourmatchescontest.h"
#include "matchmodel.h"
#include "setupwinnerdialog.h"

#include <QDebug>

FourMatchesContestWidget::FourMatchesContestWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FourMatchesContestWidget)
{
  ui->setupUi(this);


  mFourMatchesContest = new FourMatchesContest();
  mFourMatchesContest->initContest();

  ui->firstMatchTableView->setModel( mFourMatchesContest->getCurrentMatchModel() );

  configGui();

  connect(this, SIGNAL(currentPhaseOver()), mFourMatchesContest, SLOT(nextState()));
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

void FourMatchesContestWidget::configGui()
{
    prepareTableView(ui->firstMatchTableView);

//    prepareTableView(ui->secondMatchTableViewNoWin);
//    prepareTableView(ui->secondMatchTableViewOneWin);

//    prepareTableView(ui->thirdMatchTableViewNoWin);
//    prepareTableView(ui->thirdMatchTableViewOneWin);
//    prepareTableView(ui->thirdMatchTableViewTwoWin);

//    prepareTableView(ui->fourthMatchTableViewNoWin);
//    prepareTableView(ui->fourthMatchTableViewOneWin);
//    prepareTableView(ui->fourthMatchTableViewTwoWin);
//    prepareTableView(ui->fourthMatchTableViewThreeWin);

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
    QModelIndex firstTeamIndex = ui->firstMatchTableView->model()->index(selectedIndex.row(), 0);
    QModelIndex secondTeamIndex = ui->firstMatchTableView->model()->index(selectedIndex.row(), 1);

    QString firstTeamName = ui->firstMatchTableView->model()->data(firstTeamIndex).toString();
    QString secondTeamName = ui->firstMatchTableView->model()->data(secondTeamIndex).toString();

    ui->firstTeamRadioButton->setText( firstTeamName );
    ui->secondTeamRadioButton->setText( secondTeamName );

    Match* selectedMatch = mFourMatchesContest->getCurrentMatchModel()->getRawData().at(
      ui->firstMatchTableView->selectionModel()->currentIndex().row()
    );

    if(selectedMatch->isFinished()) {
        bool firstWins = selectedMatch->getWinner().getName() == firstTeamName;
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
    SetUpWinnerDialog dialog;
    Match* selectedMatch = mFourMatchesContest->getCurrentMatchModel()->getRawData().at(
      ui->firstMatchTableView->selectionModel()->currentIndex().row()
    );
    dialog.setMatch( selectedMatch );

    if( dialog.exec() == QDialog::Accepted ) {
      mFourMatchesContest->getCurrentMatchModel()->setFinished( selectedMatch, dialog.firstWins() );
      if( mFourMatchesContest->isCurrentPhaseOver() ) {
          emit currentPhaseOver();
          ui->secondMatchTableViewNoWin->setModel( mFourMatchesContest->getCurrentMatchModel() );
      }
    }
}

void FourMatchesContestWidget::setUpWinnerFromSubmitButtonSlot()
{
//    mCurrentSecetedView->model()->data(
//        mCurrentSecetedView->selectionModel()->currentIndex()
//    );
//    mFourMatchesContest->getCurrentMatchModel()->setFinished(
//                selectedMatch, ui->firstTeamRadioButton->isChecked() );
//    if( mFourMatchesContest->isCurrentPhaseOver() ) {
//        emit currentPhaseOver();
//        ui->secondMatchTableViewNoWin->setModel( mFourMatchesContest->getCurrentMatchModel() );
//    }

}

void FourMatchesContestWidget::firstViewSelected()
{
    mCurrentSecetedView = ui->firstMatchTableView;
}

void FourMatchesContestWidget::secondViewOneWinSelected()
{
    mCurrentSecetedView = ui->secondMatchTableViewOneWin;
}

void FourMatchesContestWidget::secondViewNoWinSelected()
{
    mCurrentSecetedView = ui->secondMatchTableViewNoWin;
}

void FourMatchesContestWidget::thirdViewTwoWinSelected()
{
    mCurrentSecetedView = ui->thirdMatchTableViewTwoWin;
}

void FourMatchesContestWidget::thirdViewOneWinSelected()
{
    mCurrentSecetedView = ui->thirdMatchTableViewOneWin;
}

void FourMatchesContestWidget::thirdViewNoWinSelected()
{
    mCurrentSecetedView = ui->thirdMatchTableViewNoWin;
}

void FourMatchesContestWidget::fourthViewThreeWinSelected()
{
    mCurrentSecetedView = ui->fourthMatchTableViewThreeWin;
}

void FourMatchesContestWidget::fourthViewTwoWinSelected()
{
    mCurrentSecetedView = ui->fourthMatchTableViewTwoWin;
}

void FourMatchesContestWidget::fourthViewOneWinSelected()
{
    mCurrentSecetedView = ui->fourthMatchTableViewOneWin;
}

void FourMatchesContestWidget::fourthViewNoWinSelected()
{
    mCurrentSecetedView = ui->fourthMatchTableViewNoWin;
}
