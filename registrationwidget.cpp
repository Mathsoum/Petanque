#include "registrationwidget.h"
#include "ui_registrationwidget.h"

#include "teammodel.h"
#include "dialogteam.h"

RegistrationWidget::RegistrationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationWidget)
{
    ui->setupUi(this);

    connect(ui->addTeamButton, SIGNAL(clicked()), this, SLOT(addNewTeamSlot()));
    connect(ui->deleteTeamButton, SIGNAL(clicked()), this, SLOT(deleteTeamSlot()));
    connect(ui->editTeamButton, SIGNAL(clicked()), this, SLOT(editTeamSlot()));
}

RegistrationWidget::~RegistrationWidget()
{
    delete ui;
}

QTableView *RegistrationWidget::getTeamView()
{
    return ui->teamView;
}

void RegistrationWidget::addNewTeamSlot()
{
    DialogTeam team;
    if( team.exec() == QDialog::Accepted ) {
      TeamModel::getInstance()->addTeam( Team( team.getName(), team.getClub() ) );
    }
}

void RegistrationWidget::deleteTeamSlot()
{
    QModelIndex selection = ui->teamView->currentIndex();
    QModelIndex firstColumn = TeamModel::getInstance()->index(selection.row(), 0);
    QModelIndex secondColumn = TeamModel::getInstance()->index(selection.row(), 1);
    Team team(
        TeamModel::getInstance()->data(firstColumn).toString(),
        TeamModel::getInstance()->data(secondColumn).toString()
    );
    TeamModel::getInstance()->removeTeam(team);
}

void RegistrationWidget::editTeamSlot()
{
    QModelIndex selection = ui->teamView->currentIndex();
    QModelIndex teamNameIndex = TeamModel::getInstance()->index( selection.row(), 0 );
    QModelIndex clubNameIndex = TeamModel::getInstance()->index( selection.row(), 1 );
    DialogTeam team(
        TeamModel::getInstance()->data( teamNameIndex ).toString(),
        TeamModel::getInstance()->data( clubNameIndex ).toString()
    );

    if( team.exec() == QDialog::Accepted ) {
        TeamModel::getInstance()->setData( teamNameIndex, team.getName() );
        TeamModel::getInstance()->setData( clubNameIndex, team.getClub() );
    }
}
