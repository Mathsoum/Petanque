#include "fourmatchescontestwidget.h"
#include "ui_fourmatchescontestwidget.h"

FourMatchesContestWidget::FourMatchesContestWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FourMatchesContestWidget)
{
    ui->setupUi(this);
}

FourMatchesContestWidget::~FourMatchesContestWidget()
{
    delete ui;
}
