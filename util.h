#ifndef UTIL_H
#define UTIL_H

#include <cstdlib>
#include <ctime>
#include <QList>

template<typename T>
class Util
{
public:
  static void shuffle( QList<T>* list )
  {
      srand( time(NULL) );
      for( int i = list->size()-1; i >= 0; --i ) {
          int j = rand() % ( i + 1 );
          T temp = list->at( j );
          list->replace( j, list->at( i ) );
          list->replace( i, temp );
      }
  }
};


#endif // UTIL_H
