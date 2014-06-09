#ifndef PHASE_H
#define PHASE_H

#include <QList>

class Match;

class Phase
{
public:
    Phase();

private:
    QList<Match*> matchList;
};

#endif // PHASE_H
