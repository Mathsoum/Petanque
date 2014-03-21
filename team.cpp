#include "team.h"

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
