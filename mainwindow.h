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

    void setUpMenuAndConnect();
private slots:
  void generateMatchesSlot();
  void activeEditTeamSlot( const QModelIndex &index );
  void setUpWinnerSlot();
  void activeSetUpWinnerActionSlot( const QModelIndex &index );

private:
  void createTestModel( TeamModel* model, bool even );

private:
  Ui::MainWindow *ui;
  RegistrationWidget* mRegistrationWidget;
  FourMatchesContestWidget* mFourMatchesContestWidget;

  QString mNewTeamName;
  FourMatchesContest* mFourMatchesContest;

  QMenu* mActionMenu;
  QMenu* mTeamMenu;

  QAction* mGenerateMatchesAction;
  QAction* mAddNewTeamAction;
  QAction* mDeleteTeamAction;
  QAction* mEditTeamAction;
  QAction* mNextContestStateAction;
  QAction* mSetUpWinnerAction;
};

#endif // MAINWINDOW_H
