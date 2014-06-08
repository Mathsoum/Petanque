#include "registrationwidget.h"
#include "ui_registrationwidget.h"
#include "teammodel.h"

#include "mainwindow.h"

RegistrationWidget::RegistrationWidget(MainWindow *mainWindow, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationWidget)
{
    ui->setupUi(this);

    connect(ui->addTeamButton, SIGNAL(clicked()), mainWindow, SLOT(addNewTeamSlot()));
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

void RegistrationWidget::addNewTeamSlot(const Team &newTeam)
{
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
