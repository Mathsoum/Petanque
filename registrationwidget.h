#ifndef REGISTRATIONWIDGET_H
#define REGISTRATIONWIDGET_H

#include "team.h"

#include <QWidget>

class QTableView;

namespace Ui {
class RegistrationWidget;
}

class RegistrationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationWidget(QWidget *parent = 0);
    ~RegistrationWidget();

    QTableView *getTeamView();

public slots:
    void addNewTeamSlot();
    void deleteTeamSlot();
    void editTeamSlot();

private:
    Ui::RegistrationWidget *ui;
};

#endif // REGISTRATIONWIDGET_H
