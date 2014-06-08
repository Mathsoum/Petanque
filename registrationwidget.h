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

<<<<<<< HEAD
public slots:
    void addNewTeamSlot();
=======
private slots:
    void addNewTeamSlot(const Team& newTeam);
>>>>>>> 0ee3580adb7d2f443528b05ff53f39757ffbe3c9
    void deleteTeamSlot();
    void editTeamSlot(const Team& team);

private:
    Ui::RegistrationWidget *ui;

    MainWindow* parent;
};

#endif // REGISTRATIONWIDGET_H
