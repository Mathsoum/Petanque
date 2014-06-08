#ifndef REGISTRATIONWIDGET_H
#define REGISTRATIONWIDGET_H

#include "team.h"

#include <QWidget>

class MainWindow;
class QTableView;

namespace Ui {
class RegistrationWidget;
}

class RegistrationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationWidget(MainWindow* mainWindow, QWidget *parent = 0);
    ~RegistrationWidget();

    QTableView *getTeamView();

private slots:
    void addNewTeamSlot(const Team& newTeam);
    void deleteTeamSlot();
    void editTeamSlot(const Team& team);

private:
    Ui::RegistrationWidget *ui;

    MainWindow* parent;
};

#endif // REGISTRATIONWIDGET_H
