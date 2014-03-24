#include "dialogteam.h"
#include "ui_dialogteam.h"

#include <QPushButton>

DialogTeam::DialogTeam(const QString &name, const QString &club, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogTeam)
{
  ui->setupUi(this);
  ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

  ui->nameEdit->setText( name );
  ui->clubEdit->setText( club );

  connect(ui->nameEdit, SIGNAL(textEdited(QString)), this, SLOT(nameIsModified(QString)));
}

DialogTeam::~DialogTeam()
{
  delete ui;
}

QString DialogTeam::getName() const
{
  return ui->nameEdit->text();
}

QString DialogTeam::getClub() const
{
  return ui->clubEdit->text().isEmpty() ? "Non homogène" : ui->clubEdit->text();
}

void DialogTeam::nameIsModified(const QString &)
{
  ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled( !getName().isEmpty() );
}

