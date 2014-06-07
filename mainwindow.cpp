#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "teammodel.h"
#include "matchmodel.h"
#include "dialogteam.h"
#include "setupwinnerdialog.h"
#include "contest.h"
#include "registrationwidget.h"

#include <QListView>
#include <QDialog>
#include <QDebug>
#include <QAction>
#include <QMenu>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi( this );

  QMenu* menu = menuBar()->addMenu( "Action" );
  mGenerateMatchesAction = menu->addAction( QString::fromUtf8( "Générer matchs" ) );
  mAddNewTeamAction = menu->addAction( QString::fromUtf8( "Ajouter équipe" ) );
  mEditTeamAction = menu->addAction( QString::fromUtf8( "Editer équipe" ) );

  mGenerateMatchesAction->setStatusTip( QString::fromUtf8( "Génère des matchs à partir de la liste des équipes." ) );
  connect( mGenerateMatchesAction, SIGNAL(triggered()), this, SLOT(generateMatchesSlot()) );

  mAddNewTeamAction->setStatusTip( QString::fromUtf8( "Ajoute une équipe à la liste des équipes." ) );
  connect( mAddNewTeamAction, SIGNAL(triggered()), this, SLOT(addNewTeamSlot()) );

  mEditTeamAction->setStatusTip( QString::fromUtf8( "Modifier les données d'une équipe." ) );
  connect( mEditTeamAction, SIGNAL(triggered()), this, SLOT(editTeamSlot()) );

  mRegistrationWidget = new RegistrationWidget(this);
  setCentralWidget(mRegistrationWidget);

  TeamModel* model = TeamModel::getInstance();
  mRegistrationWidget->getTeamView()->setModel( model );
  mRegistrationWidget->getTeamView()->setSelectionBehavior( QAbstractItemView::SelectRows );
  mRegistrationWidget->getTeamView()->setSelectionMode( QAbstractItemView::SingleSelection );
  mRegistrationWidget->getTeamView()->setColumnWidth( 0, 200 );
  mRegistrationWidget->getTeamView()->setColumnWidth( 1, 200 );

  createTestModel( model, false );
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::generateMatchesSlot()
{
  mGenerateMatchesAction->setEnabled( false );
  mAddNewTeamAction->setEnabled( false );
  mEditTeamAction->setEnabled( false );

  mContest = new Contest();
  mContest->initContest();
  mRegistrationWidget->getTeamView()->setModel( mContest->getCurrentMatchModel() );

  QMenu* contestMenu = menuBar()->addMenu( "Concours" );
  mNextContestStateAction = contestMenu->addAction( "Phase suivante" );
  mNextContestStateAction->setEnabled( false );
  connect( mNextContestStateAction, SIGNAL( triggered() ), this, SLOT( nextPhaseSlot() ) );
  connect( mContest->getCurrentMatchModel(), SIGNAL( dataChanged( QModelIndex, QModelIndex ) ),
           this, SLOT( activeNextPhaseActionSlot() ) );


  mSetUpWinnerAction = contestMenu->addAction( "Saisir gagnant..." );
  mSetUpWinnerAction->setEnabled(false);
  connect( mSetUpWinnerAction, SIGNAL( triggered() ), this, SLOT( setUpWinnerSlot() ) );
  connect( mRegistrationWidget->getTeamView()->selectionModel(),
           SIGNAL( currentRowChanged( QModelIndex, QModelIndex ) ),
           this,
           SLOT( activeSetUpWinnerActionSlot( QModelIndex ) ) );
}

void MainWindow::addNewTeamSlot()
{
  DialogTeam team;
  if( team.exec() == QDialog::Accepted ) {
    TeamModel::getInstance()->addTeam( Team( team.getName() ) );
  }
}

void MainWindow::deleteTeamSlot()
{
}

void MainWindow::editTeamSlot()
{
  QModelIndex selection = mRegistrationWidget->getTeamView()->currentIndex();
  QModelIndex firstCol = TeamModel::getInstance()->index( selection.row(), 0 );
  QModelIndex secondCol = TeamModel::getInstance()->index( selection.row(), 1 );
  DialogTeam team( TeamModel::getInstance()->data( firstCol ).toString(), TeamModel::getInstance()->data( secondCol ).toString() );
  if( team.exec() == QDialog::Accepted ) {
      TeamModel::getInstance()->setData( firstCol, team.getName() );
      TeamModel::getInstance()->setData( secondCol, team.getClub() );
  }
}

void MainWindow::activeEditTeamSlot( const QModelIndex& index  )
{
  mEditTeamAction->setEnabled( index.isValid() );
}

void MainWindow::nextPhaseSlot()
{
  mContest->nextState();
  mRegistrationWidget->getTeamView()->setModel( mContest->getCurrentMatchModel() );
  connect( mContest->getCurrentMatchModel(), SIGNAL( dataChanged( QModelIndex, QModelIndex ) ),
           this, SLOT( activeNextPhaseActionSlot() ) );
}

void MainWindow::activeNextPhaseActionSlot()
{
  bool finished = mContest->getCurrentMatchModel()->notFinishedYet() == 0;
  mNextContestStateAction->setEnabled( finished );
}

void MainWindow::setUpWinnerSlot()
{
  SetUpWinnerDialog dialog;
  Match* selectedMatch = mContest->getCurrentMatchModel()->getRawData().at( mRegistrationWidget->getTeamView()->selectionModel()->currentIndex().row() );
  dialog.setMatch( selectedMatch );

  if( dialog.exec() == QDialog::Accepted ) {
    mContest->getCurrentMatchModel()->setFinished( selectedMatch, dialog.firstWins() );
  }
}

void MainWindow::activeSetUpWinnerActionSlot( const QModelIndex& index )
{
  mSetUpWinnerAction->setEnabled( index.isValid() );
}

void MainWindow::createTestModel( TeamModel* model, bool even )
{
  model->addTeam( Team( "A" ) );
  model->addTeam( Team( "D" ) );
  model->addTeam( Team( "B" ) );
  model->addTeam( Team( "C" ) );
  model->addTeam( Team( "R" ) );
  model->addTeam( Team( "Z" ) );
  model->addTeam( Team( "E" ) );
  model->addTeam( Team( "T" ) );
  model->addTeam( Team( "S" ) );
  model->addTeam( Team( "Q" ) );
  model->addTeam( Team( "F" ) );
  model->addTeam( Team( "G" ) );
  model->addTeam( Team( "H" ) );
  model->addTeam( Team( "Y" ) );
  model->addTeam( Team( "J" ) );
  model->addTeam( Team( "U" ) );
  model->addTeam( Team( "I" ) );
  model->addTeam( Team( "K" ) );
  model->addTeam( Team( "L" ) );
  model->addTeam( Team( "O" ) );
  if( !even ) {
    model->addTeam( Team("V") );
  }
}

