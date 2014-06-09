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

  configGui();

  mFourMatchesContest = new FourMatchesContest();
  mFourMatchesContest->initContest();

  ui->firstMatchTableView->setModel( mFourMatchesContest->getCurrentMatchModel() );

  connect(ui->firstMatchTableView->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
          SLOT(teamViewSelectionChanged(QModelIndex)));
}

void FourMatchesContestWidget::prepareTableView(QTableView* tableViewToPrepare)
{
    tableViewToPrepare->verticalHeader()->hide();
    tableViewToPrepare->horizontalHeader()->hide();
    tableViewToPrepare->setSelectionBehavior( QAbstractItemView::SelectRows );
    tableViewToPrepare->setSelectionMode( QAbstractItemView::SingleSelection );
}

void FourMatchesContestWidget::configGui()
{
    prepareTableView(ui->firstMatchTableView);
    prepareTableView(ui->secondMatchTableView);
    prepareTableView(ui->thirdMatchTableView);
    prepareTableView(ui->fourthMatchTableView);

    ui->submitScoreButton->setEnabled(false);

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
  list << ui->firstMatchTableView << ui->secondMatchTableView << ui->thirdMatchTableView << ui->fourthMatchTableView;
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

Match* FourMatchesContestWidget::getCurrentSelectedMatch(QTableView* tableView)
{
    return mFourMatchesContest->getCurrentMatchModel()->getRawData().at(
      tableView->selectionModel()->currentIndex().row()
    );
}

void FourMatchesContestWidget::setUpWinnerSlot()
{
    SetUpWinnerDialog dialog;
    Match* selectedMatch = getCurrentSelectedMatch(ui->firstMatchTableView);
    dialog.setMatch( selectedMatch );

    if( dialog.exec() == QDialog::Accepted ) {
      mFourMatchesContest->getCurrentMatchModel()->setFinished( selectedMatch, dialog.firstWins() );
    }
}

void FourMatchesContestWidget::setUpWinnerFromSubmitButtonSlot()
{
    Match* selectedMatch = getCurrentSelectedMatch(ui->firstMatchTableView);
    mFourMatchesContest->getCurrentMatchModel()->setFinished( selectedMatch, ui->firstTeamRadioButton->isChecked() );
}
