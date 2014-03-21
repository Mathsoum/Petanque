#include "testteammodel.h"

#include "teammodel.h"

void TestTeamModel::testCreation_data()
{
    QTest::addColumn<TeamModel*>("model");
    QTest::addColumn<int>("result");

    TeamModel* model = new TeamModel;

    QTest::newRow("row") << model << 0;
    QTest::newRow("column") << model << 0;
}

void TestTeamModel::testCreation()
{
    QFETCH(TeamModel*, model);
    QFETCH(int, result);

    QCOMPARE(model->rowCount(), 0);
    QCOMPARE(model->columnCount(), 0);
}

void TestTeamModel::testAdding_data()
{

}

void TestTeamModel::testAdding()
{

}

QTEST_MAIN(TestTeamModel)
