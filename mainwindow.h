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

private slots:
  void slotGenerateMatches();
  void slotAddNewTeam();
  void slotEditTeam();
  void slotActiveEditTeam(const QModelIndex &index);
  void slotNextPhase();
  void slotActiveNextPhaseAction();
  void slotSetUpWinner();
  void slotActiveSetUpWinnerAction( const QModelIndex &index );

private:
  void createTestModel(TeamModel* model);

private:
  Ui::MainWindow *ui;
  QString mNewTeamName;
  Contest* mContest;

  QAction* mGenerateMatchesAction;
  QAction* mAddNewTeamAction;
  QAction* mEditTeamAction;
  QAction* mNextContestStateAction;
  QAction* mSetUpWinnerAction;
};

#endif // MAINWINDOW_H
