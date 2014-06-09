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
    ui->firstTeamRadioButton->setAutoExclusive(false);
    ui->firstTeamRadioButton->setChecked(false);
    ui->firstTeamRadioButton->setAutoExclusive(true);
    ui->secondTeamRadioButton->setText( secondTeamName );
    ui->secondTeamRadioButton->setAutoExclusive(false);
    ui->secondTeamRadioButton->setChecked(false);
    ui->secondTeamRadioButton->setAutoExclusive(true);
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

void FourMatchesContestWidget::setUpWinnerFromSubmitButtonSlot()
{
    Match* selectedMatch = mFourMatchesContest->getCurrentMatchModel()->getRawData().at(
      ui->firstMatchTableView->selectionModel()->currentIndex().row()
    );
    mFourMatchesContest->getCurrentMatchModel()->setFinished( selectedMatch, ui->firstTeamRadioButton->isChecked() );

}
