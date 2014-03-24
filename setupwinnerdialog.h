#ifndef SETUPWINNERDIALOG_H
#define SETUPWINNERDIALOG_H

#include <QDialog>

#include "match.h"

namespace Ui {
class SetUpWinnerDialog;
}

class SetUpWinnerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetUpWinnerDialog(QWidget *parent = 0);
    ~SetUpWinnerDialog();

    void setMatch( Match *match );
    bool firstWins() const;

private slots:
    void slotTeamSelected();

private:
    Ui::SetUpWinnerDialog *ui;
};

#endif // SETUPWINNERDIALOG_H
