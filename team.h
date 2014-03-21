#ifndef TEAM_H
#define TEAM_H

#include <QString>

const QString NON_HOMOGENE = QString::fromUtf8("Non homogène");

class Team
{
public:
    Team(const QString& name = "", const QString& club = NON_HOMOGENE);

    QString getName() const;
    QString getClub() const;

private:
    QString mName;
    QString mClub;

};

#endif // TEAM_H
