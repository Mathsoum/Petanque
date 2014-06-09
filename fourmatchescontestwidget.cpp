#include "fourmatchescontestwidget.h"
#include "ui_fourmatchescontestwidget.h"

#include "fourmatchescontest.h"
#include "matchmodel.h"
#include "setupwinnerdialog.h"

FourMatchesContestWidget::FourMatchesContestWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FourMatchesContestWidget)
{
  ui->setupUi(this);

  configGui();

  mFourMatchesContest = new FourMatchesContest();
  mFourMatchesContest->initContest();

  ui->firstMatchTableView->setModel( mFourMatchesContest->getCurrentMatchModel() );
}

void FourMatchesContestWidget::configGui()
{
    ui->firstMatchTableView->verticalHeader()->hide();
    ui->firstMatchTableView->horizontalHeader()->hide();
    ui->firstMatchTableView->setSelectionBehavior( QAbstractItemView::SelectRows );
    ui->firstMatchTableView->setSelectionMode( QAbstractItemView::SingleSelection );

    ui->secondMatchTableView->verticalHeader()->hide();
    ui->secondMatchTableView->horizontalHeader()->hide();
    ui->secondMatchTableView->setSelectionBehavior( QAbstractItemView::SelectRows );
    ui->secondMatchTableView->setSelectionMode( QAbstractItemView::SingleSelection );

    ui->thirdMatchTableView->verticalHeader()->hide();
    ui->thirdMatchTableView->horizontalHeader()->hide();
    ui->thirdMatchTableView->setSelectionBehavior( QAbstractItemView::SelectRows );
    ui->thirdMatchTableView->setSelectionMode( QAbstractItemView::SingleSelection );

    ui->fourthMatchTableView->verticalHeader()->hide();
    ui->fourthMatchTableView->horizontalHeader()->hide();
    ui->fourthMatchTableView->setSelectionBehavior( QAbstractItemView::SelectRows );
    ui->fourthMatchTableView->setSelectionMode( QAbstractItemView::SingleSelection );

    ui->submitScoreButton->setEnabled(false);

    connect(ui->firstTeamRadioButton, SIGNAL(clicked()), SLOT(teamRadioSelectionChanged()));
    connect(ui->secondTeamRadioButton, SIGNAL(clicked()), SLOT(teamRadioSelectionChanged()));
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

void FourMatchesContestWidget::teamRadioSelectionChanged()
{
    ui->submitScoreButton->setEnabled(
        ui->firstTeamRadioButton->isChecked() || ui->secondTeamRadioButton->isChecked()
    );
}

void FourMatchesContestWidget::teamViewSelectionChanged()
{
    ui->firstTeamRadioButton->setChecked(false);
    ui->secondTeamRadioButton->setChecked(false);
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
    }
}
