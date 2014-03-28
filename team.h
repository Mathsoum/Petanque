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

    void setName( const QString &name );
    void setClub( const QString &club );

private:
    QString mName;
    QString mClub;

};

QDataStream &operator<<(QDataStream& out, const Team& team);
bool operator==( const Team& one, const Team& other );
uint qHash(const Team& team);

#endif // TEAM_H
