#ifndef QTESTMODEL_H
#define QTESTMODEL_H

#include <QtTest/QTest>

class TestTeamModel : public QObject
{
    Q_OBJECT

private slots:
    void testCreation_data();
    void testCreation();
    void testAdding_data();
    void testAdding();

};

#endif // QTESTMODEL_H
