#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "teammodel.h"
#include "matchmodel.h"
#include "dialogteam.h"
#include "contest.h"

#include <QListView>
#include <QDialog>
#include <QDebug>
#include <QAction>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  QMenu* menu = menuBar()->addMenu("Action");
  mGenerateMatchesAction = menu->addAction("Générer matchs");
  mAddNewTeamAction = menu->addAction("Ajouter équipe");

  mGenerateMatchesAction->setStatusTip("Génère des matchs à partir de la liste des équipes.");
  connect(mGenerateMatchesAction, SIGNAL(triggered()), this, SLOT(slotGenerateMatches()));

  mAddNewTeamAction->setStatusTip("Ajoute une équipe à la liste des équipes.");
  connect(mAddNewTeamAction, SIGNAL(triggered()), this, SLOT(slotAddNewTeam()));

  TeamModel* model = TeamModel::getInstance();
  ui->tableView->setModel(model);
  ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->tableView->setColumnWidth(0, 200);
  ui->tableView->setColumnWidth(1, 200);

  createTestModel(model);
}

void MainWindow::createTestModel(TeamModel* model)
{
  model->addTeam(Team("A"));
  model->addTeam(Team("D"));
  model->addTeam(Team("B"));
  model->addTeam(Team("C"));
  model->addTeam(Team("R"));
  model->addTeam(Team("Z"));
  model->addTeam(Team("E"));
  model->addTeam(Team("T"));
  model->addTeam(Team("S"));
  model->addTeam(Team("Q"));
  model->addTeam(Team("F"));
  model->addTeam(Team("G"));
  model->addTeam(Team("H"));
  model->addTeam(Team("Y"));
  model->addTeam(Team("J"));
  model->addTeam(Team("U"));
  model->addTeam(Team("I"));
  model->addTeam(Team("K"));
  model->addTeam(Team("L"));
  model->addTeam(Team("O"));
  model->addTeam(Team("V"));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::slotGenerateMatches()
{
  mContest = new Contest();
  mNextContestStateAction = menuBar()->addMenu("Concours")->addAction("Phase suivante");
  connect( mNextContestStateAction, SIGNAL(triggered()), mContest, SLOT(nextState()) );

  mContest->initContest();

  ui->tableView->setModel( mContest->getCurrentMatchModel() );
  mGenerateMatchesAction->setEnabled(false);
  mAddNewTeamAction->setEnabled(false);
}

void MainWindow::slotAddNewTeam()
{
  DialogTeam team;
  if(team.exec() == QDialog::Accepted) {
    qDebug() << "Nouvelle équipe" << team.getName();
    TeamModel::getInstance()->addTeam( Team( team.getName() ) );
  }
}
