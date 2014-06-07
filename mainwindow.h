#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QModelIndex;
class TeamModel;
class FourMatchesContest;
class RegistrationWidget;
class FourMatchesContestWidget;

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
  void generateMatchesSlot();
  void addNewTeamSlot();
  void deleteTeamSlot();
  void editTeamSlot();
  void activeEditTeamSlot( const QModelIndex &index );
  void nextPhaseSlot();
  void activeNextPhaseActionSlot();
  void setUpWinnerSlot();
  void activeSetUpWinnerActionSlot( const QModelIndex &index );

private:
  void createTestModel( TeamModel* model, bool even );

private:
  Ui::MainWindow *ui;
  RegistrationWidget* mRegistrationWidget;
  FourMatchesContestWidget* mFourMatchesContestWidget;

  QString mNewTeamName;
  FourMatchesContest* mContest;

  QAction* mGenerateMatchesAction;
  QAction* mAddNewTeamAction;
  QAction* mEditTeamAction;
  QAction* mNextContestStateAction;
  QAction* mSetUpWinnerAction;
};

#endif // MAINWINDOW_H
