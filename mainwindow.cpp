#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "teammodel.h"
#include "matchmodel.h"
#include "dialogteam.h"
#include "fourmatchescontest.h"
#include "registrationwidget.h"
#include "fourmatchescontestwidget.h"

#include <QListView>
#include <QDialog>
#include <QDebug>
#include <QAction>
#include <QMenu>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableView>

void MainWindow::setUpMenuAndConnect()
{
    mActionMenu = menuBar()->addMenu( "Action" );
    mGenerateMatchesAction = mActionMenu->addAction( QString::fromUtf8( "Générer matchs" ) );

    mTeamMenu = menuBar()->addMenu( "Équipe" );
    mAddNewTeamAction = mTeamMenu->addAction( QString::fromUtf8( "Ajouter équipe" ) );
    mDeleteTeamAction = mTeamMenu->addAction( QString::fromUtf8( "Supprimer équipe" ) );
    mEditTeamAction = mTeamMenu->addAction( QString::fromUtf8( "Éditer équipe" ) );

    mGenerateMatchesAction->setStatusTip( QString::fromUtf8( "Génère des matchs à partir de la liste des équipes." ) );
    connect( mGenerateMatchesAction, SIGNAL(triggered()), this, SLOT(generateMatchesSlot()) );

    mAddNewTeamAction->setStatusTip( QString::fromUtf8( "Ajoute une équipe à la liste des équipes." ) );
    connect( mAddNewTeamAction, SIGNAL(triggered()), mRegistrationWidget, SLOT(addNewTeamSlot()) );

    mDeleteTeamAction->setStatusTip( QString::fromUtf8( "Supprimer l'équipe sélectionnée." ) );
    connect( mDeleteTeamAction, SIGNAL(triggered()), mRegistrationWidget, SLOT(deleteTeamSlot()) );

    mEditTeamAction->setStatusTip( QString::fromUtf8( "Modifier les données de l'équipe sélectionnée." ) );
    connect( mEditTeamAction, SIGNAL(triggered()), mRegistrationWidget, SLOT(editTeamSlot()) );
}

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi( this );

  TeamModel* model = TeamModel::getInstance();
  createTestModel( model, false );

  mRegistrationWidget = new RegistrationWidget(this);
  mRegistrationWidget->setModel( model );
  setCentralWidget(mRegistrationWidget);
  resize(mRegistrationWidget->size());

  setUpMenuAndConnect();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::generateMatchesSlot()
{
  mGenerateMatchesAction->setEnabled( false );
  menuBar()->removeAction(mTeamMenu->menuAction());

  mFourMatchesContestWidget = new FourMatchesContestWidget(this);
  setCentralWidget( mFourMatchesContestWidget );
  resize( mFourMatchesContestWidget->size() );

  QMenu* contestMenu = menuBar()->addMenu( "Concours" );
  mNextContestStateAction = contestMenu->addAction( "Phase suivante" );
  mNextContestStateAction->setEnabled( false );

  mSetUpWinnerAction = contestMenu->addAction( "Saisir gagnant..." );
  mSetUpWinnerAction->setEnabled(false);
  connect( mSetUpWinnerAction, SIGNAL( triggered() ), this, SLOT( setUpWinnerSlot() ) );
}

void MainWindow::activeEditTeamSlot( const QModelIndex& index  )
{
  mEditTeamAction->setEnabled( index.isValid() );
}

void MainWindow::setUpWinnerSlot()
{
    mFourMatchesContestWidget->setUpWinnerSlot();
}

void MainWindow::activeSetUpWinnerActionSlot( const QModelIndex& index )
{
  mSetUpWinnerAction->setEnabled( index.isValid() );
}

void MainWindow::createTestModel( TeamModel* model, bool even )
{
    for(int i = 0; i < (even ? 100 : 101); ++i) {
        model->addTeam( QString('A' + rand()%26) );
    }
}

