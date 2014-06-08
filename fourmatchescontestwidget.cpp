#include "fourmatchescontestwidget.h"
#include "ui_fourmatchescontestwidget.h"

FourMatchesContestWidget::FourMatchesContestWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FourMatchesContestWidget)
{
  ui->setupUi(this);

  ui->tableView->verticalHeader()->hide();
  ui->tableView->horizontalHeader()->hide();
  ui->tableView->setSelectionBehavior( QAbstractItemView::SelectRows );
  ui->tableView->setSelectionMode( QAbstractItemView::SingleSelection );

  ui->tableView_2->verticalHeader()->hide();
  ui->tableView_2->horizontalHeader()->hide();
  ui->tableView_2->setSelectionBehavior( QAbstractItemView::SelectRows );
  ui->tableView_2->setSelectionMode( QAbstractItemView::SingleSelection );

  ui->tableView_3->verticalHeader()->hide();
  ui->tableView_3->horizontalHeader()->hide();
  ui->tableView_3->setSelectionBehavior( QAbstractItemView::SelectRows );
  ui->tableView_3->setSelectionMode( QAbstractItemView::SingleSelection );

  ui->tableView_4->verticalHeader()->hide();
  ui->tableView_4->horizontalHeader()->hide();
  ui->tableView_4->setSelectionBehavior( QAbstractItemView::SelectRows );
  ui->tableView_4->setSelectionMode( QAbstractItemView::SingleSelection );
}

FourMatchesContestWidget::~FourMatchesContestWidget()
{
  delete ui;
}

QList<QTableView*> FourMatchesContestWidget::getTableViewList() const
{
  QList<QTableView*> list;
  list << ui->tableView << ui->tableView_2 << ui->tableView_3 << ui->tableView_4;
  return list;
}
