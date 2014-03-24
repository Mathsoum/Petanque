#include "setupwinnerdialog.h"
#include "ui_setupwinnerdialog.h"

#include <QPushButton>

SetUpWinnerDialog::SetUpWinnerDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SetUpWinnerDialog)
{
  ui->setupUi(this);
  connect( ui->firstTeamRadio, SIGNAL( clicked() ), this, SLOT( slotTeamSelected() ) );
  connect( ui->secondTeamRadio, SIGNAL( clicked() ), this, SLOT( slotTeamSelected() ) );
}

SetUpWinnerDialog::~SetUpWinnerDialog()
{
  delete ui;
}

void SetUpWinnerDialog::setMatch( Match *match )
{
  ui->firstTeamRadio->setText( match->teams().first.getName() );
  ui->secondTeamRadio->setText( match->teams().second.getName() );
  if( match->isFinished() ) {
    if( match->getWinner() == match->teams().first ) {
      ui->firstTeamRadio->setChecked( true );
    } else {
      ui->secondTeamRadio->setChecked( true );
    }
  }
}

bool SetUpWinnerDialog::firstWins() const
{
  return ui->firstTeamRadio->isChecked();
}

void SetUpWinnerDialog::slotTeamSelected()
{
  ui->buttonBox->button( QDialogButtonBox::Ok )
          ->setEnabled( ui->firstTeamRadio->isChecked()
                        || ui->secondTeamRadio->isChecked() );
}
