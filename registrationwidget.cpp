#include "registrationwidget.h"
#include "ui_registrationwidget.h"
#include "teammodel.h"
<<<<<<< HEAD
#include "dialogteam.h"
=======
>>>>>>> 0ee3580adb7d2f443528b05ff53f39757ffbe3c9

#include "mainwindow.h"

RegistrationWidget::RegistrationWidget(MainWindow *mainWindow, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationWidget)
{
    ui->setupUi(this);

<<<<<<< HEAD
    connect(ui->addTeamButton, SIGNAL(clicked()), this, SLOT(addNewTeamSlot()));
=======
    connect(ui->addTeamButton, SIGNAL(clicked()), mainWindow, SLOT(addNewTeamSlot()));
>>>>>>> 0ee3580adb7d2f443528b05ff53f39757ffbe3c9
    connect(ui->deleteTeamButton, SIGNAL(clicked()), this, SLOT(deleteTeamSlot()));
    connect(ui->editTeamButton, SIGNAL(clicked()), mainWindow, SLOT(editTeamSlot()));
}

RegistrationWidget::~RegistrationWidget()
{
    delete ui;
}

QTableView *RegistrationWidget::getTeamView()
{
    return ui->teamView;
}

<<<<<<< HEAD
void RegistrationWidget::addNewTeamSlot()
{
    DialogTeam team;
    if( team.exec() == QDialog::Accepted ) {
      TeamModel::getInstance()->addTeam( Team( team.getName(), team.getClub() ) );
    }
=======
void RegistrationWidget::addNewTeamSlot(const Team &newTeam)
{
>>>>>>> 0ee3580adb7d2f443528b05ff53f39757ffbe3c9
}

void RegistrationWidget::deleteTeamSlot()
{
    QModelIndex firstColumn = TeamModel::getInstance()->index(ui->teamView->currentIndex().row(), 0);
    QModelIndex secondColumn = TeamModel::getInstance()->index(ui->teamView->currentIndex().row(), 1);
    Team team(
        TeamModel::getInstance()->data(firstColumn).toString(),
        TeamModel::getInstance()->data(secondColumn).toString()
    );
    TeamModel::getInstance()->removeTeam(team);
}

void RegistrationWidget::editTeamSlot(const Team &team)
{
}
