#ifndef FOURMATCHESCONTESTWIDGET_H
#define FOURMATCHESCONTESTWIDGET_H

#include <QWidget>

class QTableView;

namespace Ui {
class FourMatchesContestWidget;
}

class FourMatchesContestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FourMatchesContestWidget(QWidget *parent = 0);
    ~FourMatchesContestWidget();

    QList<QTableView*> getTableViewList() const;

public slots:
    void teamRadioSelctionChanged();
    void teamViewSelectionChanged();

private:
    Ui::FourMatchesContestWidget *ui;
};

#endif // FOURMATCHESCONTESTWIDGET_H
