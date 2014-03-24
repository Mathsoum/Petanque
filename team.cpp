#include "team.h"

#include <QHash>

Team::Team(const QString& name, const QString& club)
{
  mName = name;
  mClub = club;
}

QString Team::getName() const
{
  return mName;
}

QString Team::getClub() const
{
  return mClub;
}

bool operator==( const Team& one, const Team& other ) {
  return one.getName() == other.getName() && one.getClub() == other.getClub();
}

uint qHash(const Team &team)
{
  return qHash( team.getName() ) ^ qHash( team.getClub() );
}

QDataStream &operator<<(QDataStream &out, const Team &team)
{
  out << team.getName();
  return out;
}


