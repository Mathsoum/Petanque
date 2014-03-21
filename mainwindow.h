#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class TeamModel;
class Contest;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

public slots:
  void slotGenerateMatches();
  void slotAddNewTeam();

private:
  void createTestModel(TeamModel* model);

private:
  Ui::MainWindow *ui;
  QString mNewTeamName;
  Contest* mContest;

  QAction* mGenerateMatchesAction;
  QAction* mAddNewTeamAction;
  QAction* mNextContestStateAction;
};

#endif // MAINWINDOW_H
