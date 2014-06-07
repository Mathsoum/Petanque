#include "registrationwidget.h"
#include "ui_registrationwidget.h"

#include "mainwindow.h"

RegistrationWidget::RegistrationWidget(MainWindow *mainWindow, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationWidget)
{
    ui->setupUi(this);

    connect(ui->addTeamButton, SIGNAL(clicked()), mainWindow, SLOT(addNewTeamSlot()));
    connect(ui->deleteTeamButton, SIGNAL(clicked()), mainWindow, SLOT(deleteTeamSlot()));
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
