#ifndef DIALOGTEAM_H
#define DIALOGTEAM_H

#include <QDialog>

namespace Ui {
  class DialogTeam;
}

class DialogTeam : public QDialog
{
  Q_OBJECT

public:
  explicit DialogTeam(const QString &name = "", const QString &club = "", QWidget *parent = 0);
  ~DialogTeam();

  QString getName() const;
  QString getClub() const;

private slots:
  void nameIsModified(const QString &text);

private:
  Ui::DialogTeam *ui;
};

#endif // DIALOGTEAM_H
