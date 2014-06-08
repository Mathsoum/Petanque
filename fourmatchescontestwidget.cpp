#include "fourmatchescontestwidget.h"
#include "ui_fourmatchescontestwidget.h"

FourMatchesContestWidget::FourMatchesContestWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FourMatchesContestWidget)
{
  ui->setupUi(this);

  ui->firstMatchTableView->verticalHeader()->hide();
  ui->firstMatchTableView->horizontalHeader()->hide();
  ui->firstMatchTableView->setSelectionBehavior( QAbstractItemView::SelectRows );
  ui->firstMatchTableView->setSelectionMode( QAbstractItemView::SingleSelection );

  ui->secondMatchTableView->verticalHeader()->hide();
  ui->secondMatchTableView->horizontalHeader()->hide();
  ui->secondMatchTableView->setSelectionBehavior( QAbstractItemView::SelectRows );
  ui->secondMatchTableView->setSelectionMode( QAbstractItemView::SingleSelection );

  ui->thirdMatchTableView->verticalHeader()->hide();
  ui->thirdMatchTableView->horizontalHeader()->hide();
  ui->thirdMatchTableView->setSelectionBehavior( QAbstractItemView::SelectRows );
  ui->thirdMatchTableView->setSelectionMode( QAbstractItemView::SingleSelection );

  ui->fourthMatchTableView->verticalHeader()->hide();
  ui->fourthMatchTableView->horizontalHeader()->hide();
  ui->fourthMatchTableView->setSelectionBehavior( QAbstractItemView::SelectRows );
  ui->fourthMatchTableView->setSelectionMode( QAbstractItemView::SingleSelection );
}

FourMatchesContestWidget::~FourMatchesContestWidget()
{
  delete ui;
}

QList<QTableView*> FourMatchesContestWidget::getTableViewList() const
{
  QList<QTableView*> list;
  list << ui->firstMatchTableView << ui->secondMatchTableView << ui->thirdMatchTableView << ui->fourthMatchTableView;
  return list;
}
