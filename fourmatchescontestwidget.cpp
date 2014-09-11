#include "fourmatchescontestwidget.h"
#include "ui_fourmatchescontestwidget.h"

#include "fourmatchescontest.h"
#include "matchmodel.h"
#include "phasemodel.h"
#include "setupwinnerdialog.h"

#include <QDebug>

void FourMatchesContestWidget::setupFirstPhaseView()
{
    ui->firstMatchTableView->setModel( mFourMatchesContest->getPhaseModel(0, 0) );
    connect(ui->firstMatchTableView->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            SLOT(firstViewSelected()));
}

void FourMatchesContestWidget::setupSecondPhase()
{
    ui->secondMatchTableViewNoWin->setModel( mFourMatchesContest->getPhaseModel(1, 0) );
    ui->secondMatchTableViewOneWin->setModel( mFourMatchesContest->getPhaseModel(1, 1) );
    connect(ui->secondMatchTableViewNoWin->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            SLOT(secondViewNoWinSelected()));
    connect(ui->secondMatchTableViewOneWin->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            SLOT(secondViewOneWinSelected()));
}

void FourMatchesContestWidget::setupThirdPhase()
{
    ui->thirdMatchTableViewNoWin->setModel( mFourMatchesContest->getPhaseModel(2, 0) );
    ui->thirdMatchTableViewOneWin->setModel( mFourMatchesContest->getPhaseModel(2, 1) );
    ui->thirdMatchTableViewTwoWin->setModel( mFourMatchesContest->getPhaseModel(2, 2) );
    connect(ui->thirdMatchTableViewNoWin->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            SLOT(thirdViewNoWinSelected()));
    connect(ui->thirdMatchTableViewOneWin->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            SLOT(thirdViewOneWinSelected()));
    connect(ui->thirdMatchTableViewTwoWin->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            SLOT(thirdViewTwoWinSelected()));
}

void FourMatchesContestWidget::setupFourthPhase()
{
    ui->fourthMatchTableViewNoWin->setModel( mFourMatchesContest->getPhaseModel(3, 0) );
    ui->fourthMatchTableViewOneWin->setModel( mFourMatchesContest->getPhaseModel(3, 1) );
    ui->fourthMatchTableViewTwoWin->setModel( mFourMatchesContest->getPhaseModel(3, 2) );
    ui->fourthMatchTableViewThreeWin->setModel( mFourMatchesContest->getPhaseModel(3, 3) );
    connect(ui->fourthMatchTableViewNoWin->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            SLOT(fourthViewNoWinSelected()));
    connect(ui->fourthMatchTableViewOneWin->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            SLOT(fourthViewOneWinSelected()));
    connect(ui->fourthMatchTableViewTwoWin->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            SLOT(fourthViewTwoWinSelected()));
    connect(ui->fourthMatchTableViewThreeWin->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            SLOT(fourthViewThreeWinSelected()));
}

FourMatchesContestWidget::FourMatchesContestWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FourMatchesContestWidget)
{
  ui->setupUi(this);

  mFourMatchesContest = new FourMatchesContest();
  mFourMatchesContest->initContest();

  setupFirstPhaseView();
  setupSecondPhase();
  setupThirdPhase();
  setupFourthPhase();

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

    connect(ui->firstTeamRadioButton, SIGNAL(toggled(bool)), SLOT(setSubmitScoreButtonStateSlot()));
    connect(ui->secondTeamRadioButton, SIGNAL(toggled(bool)), SLOT(setSubmitScoreButtonStateSlot()));
    connect(ui->submitScoreButton, SIGNAL(clicked()), SLOT(setUpWinnerFromSubmitButtonSlot()));
}

FourMatchesContestWidget::~FourMatchesContestWidget()
{
  delete ui;
}

FourMatchesContest *FourMatchesContestWidget::getContest() const
{
    return mFourMatchesContest;
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
    QModelIndex firstTeamIndex = mCurrentSelectedView->model()->index(selectedIndex.row(), 0);
    QModelIndex secondTeamIndex = mCurrentSelectedView->model()->index(selectedIndex.row(), 1);

    FM_Team* firstSelectedTeam = ((PhaseModel*)mCurrentSelectedView->model())->getTeam(firstTeamIndex);
    FM_Team* secondSelectedTeam = ((PhaseModel*)mCurrentSelectedView->model())->getTeam(secondTeamIndex);

    QString firstRadioText = firstSelectedTeam != NULL ? firstSelectedTeam->getName() : "No Team";
    QString secondRadioText = secondSelectedTeam != NULL ? secondSelectedTeam->getName() : "No Team";

    ui->firstTeamRadioButton->setText( firstRadioText );
    ui->secondTeamRadioButton->setText( secondRadioText );

    ui->firstTeamRadioButton->setEnabled(firstSelectedTeam != NULL);
    ui->secondTeamRadioButton->setEnabled(secondSelectedTeam != NULL);

    if (firstSelectedTeam != NULL) {
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
    qDebug() << "First view selected";
    mCurrentSelectedView = ui->firstMatchTableView;
    mCurrentSelectedPhase = 0;

    ui->secondMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->secondMatchTableViewOneWin->selectionModel()->clearSelection();

    ui->thirdMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->thirdMatchTableViewOneWin->selectionModel()->clearSelection();
    ui->thirdMatchTableViewTwoWin->selectionModel()->clearSelection();

    ui->fourthMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewOneWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewTwoWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewThreeWin->selectionModel()->clearSelection();
}

void FourMatchesContestWidget::secondViewOneWinSelected()
{
    qDebug() << "Second One view selected";
    mCurrentSelectedView = ui->secondMatchTableViewOneWin;
    mCurrentSelectedPhase = 1;

    ui->firstMatchTableView->selectionModel()->clearSelection();

    ui->secondMatchTableViewNoWin->selectionModel()->clearSelection();

    ui->thirdMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->thirdMatchTableViewOneWin->selectionModel()->clearSelection();
    ui->thirdMatchTableViewTwoWin->selectionModel()->clearSelection();

    ui->fourthMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewOneWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewTwoWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewThreeWin->selectionModel()->clearSelection();
}

void FourMatchesContestWidget::secondViewNoWinSelected()
{
    qDebug() << "Second No view selected";
    mCurrentSelectedView = ui->secondMatchTableViewNoWin;
    mCurrentSelectedPhase = 1;

    ui->firstMatchTableView->selectionModel()->clearSelection();

    ui->secondMatchTableViewOneWin->selectionModel()->clearSelection();

    ui->thirdMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->thirdMatchTableViewOneWin->selectionModel()->clearSelection();
    ui->thirdMatchTableViewTwoWin->selectionModel()->clearSelection();

    ui->fourthMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewOneWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewTwoWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewThreeWin->selectionModel()->clearSelection();
}

void FourMatchesContestWidget::thirdViewTwoWinSelected()
{
    qDebug() << "Third Two view selected";
    mCurrentSelectedView = ui->thirdMatchTableViewTwoWin;
    mCurrentSelectedPhase = 2;

    ui->firstMatchTableView->selectionModel()->clearSelection();

    ui->secondMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->secondMatchTableViewOneWin->selectionModel()->clearSelection();

    ui->thirdMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->thirdMatchTableViewOneWin->selectionModel()->clearSelection();

    ui->fourthMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewOneWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewTwoWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewThreeWin->selectionModel()->clearSelection();
}

void FourMatchesContestWidget::thirdViewOneWinSelected()
{
    qDebug() << "Third one view selected";
    mCurrentSelectedView = ui->thirdMatchTableViewOneWin;
    mCurrentSelectedPhase = 2;

    ui->firstMatchTableView->selectionModel()->clearSelection();

    ui->secondMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->secondMatchTableViewOneWin->selectionModel()->clearSelection();

    ui->thirdMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->thirdMatchTableViewTwoWin->selectionModel()->clearSelection();

    ui->fourthMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewOneWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewTwoWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewThreeWin->selectionModel()->clearSelection();
}

void FourMatchesContestWidget::thirdViewNoWinSelected()
{
    qDebug() << "Third no view selected";
    mCurrentSelectedView = ui->thirdMatchTableViewNoWin;
    mCurrentSelectedPhase = 2;

    ui->firstMatchTableView->selectionModel()->clearSelection();

    ui->secondMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->secondMatchTableViewOneWin->selectionModel()->clearSelection();

    ui->thirdMatchTableViewOneWin->selectionModel()->clearSelection();
    ui->thirdMatchTableViewTwoWin->selectionModel()->clearSelection();

    ui->fourthMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewOneWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewTwoWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewThreeWin->selectionModel()->clearSelection();
}

void FourMatchesContestWidget::fourthViewThreeWinSelected()
{
    qDebug() << "Forth three view selected";
    mCurrentSelectedView = ui->fourthMatchTableViewThreeWin;
    mCurrentSelectedPhase = 3;

    ui->firstMatchTableView->selectionModel()->clearSelection();

    ui->secondMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->secondMatchTableViewOneWin->selectionModel()->clearSelection();

    ui->thirdMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->thirdMatchTableViewOneWin->selectionModel()->clearSelection();
    ui->thirdMatchTableViewTwoWin->selectionModel()->clearSelection();

    ui->fourthMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewOneWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewTwoWin->selectionModel()->clearSelection();
}

void FourMatchesContestWidget::fourthViewTwoWinSelected()
{
    qDebug() << "Forth two view selected";
    mCurrentSelectedView = ui->fourthMatchTableViewTwoWin;
    mCurrentSelectedPhase = 3;

    ui->firstMatchTableView->selectionModel()->clearSelection();

    ui->secondMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->secondMatchTableViewOneWin->selectionModel()->clearSelection();

    ui->thirdMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->thirdMatchTableViewOneWin->selectionModel()->clearSelection();
    ui->thirdMatchTableViewTwoWin->selectionModel()->clearSelection();

    ui->fourthMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewOneWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewThreeWin->selectionModel()->clearSelection();
}

void FourMatchesContestWidget::fourthViewOneWinSelected()
{
    qDebug() << "Forth one view selected";
    mCurrentSelectedView = ui->fourthMatchTableViewOneWin;
    mCurrentSelectedPhase = 3;

    ui->firstMatchTableView->selectionModel()->clearSelection();

    ui->secondMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->secondMatchTableViewOneWin->selectionModel()->clearSelection();

    ui->thirdMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->thirdMatchTableViewOneWin->selectionModel()->clearSelection();
    ui->thirdMatchTableViewTwoWin->selectionModel()->clearSelection();

    ui->fourthMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewTwoWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewThreeWin->selectionModel()->clearSelection();
}

void FourMatchesContestWidget::fourthViewNoWinSelected()
{
    qDebug() << "Forth no view selected";
    mCurrentSelectedView = ui->fourthMatchTableViewNoWin;
    mCurrentSelectedPhase = 3;

    ui->firstMatchTableView->selectionModel()->clearSelection();

    ui->secondMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->secondMatchTableViewOneWin->selectionModel()->clearSelection();

    ui->thirdMatchTableViewNoWin->selectionModel()->clearSelection();
    ui->thirdMatchTableViewOneWin->selectionModel()->clearSelection();
    ui->thirdMatchTableViewTwoWin->selectionModel()->clearSelection();

    ui->fourthMatchTableViewOneWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewTwoWin->selectionModel()->clearSelection();
    ui->fourthMatchTableViewThreeWin->selectionModel()->clearSelection();
}
