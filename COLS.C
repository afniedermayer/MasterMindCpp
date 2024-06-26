// 30.10.95 by Andreas Niedermayer
// color handling

#include "mstr.h"
extern "C" {
#include <ctype.h>
}

struct cltb {
  char abr;   /* abbreviation of the name of the color */
  char *nam;  /* name of the color */
} coltab[] = { {'w', "white"}, {'b', "black"}, {'r', "red"},
				{'g', "green"}, {'e', "empty"}, {'y', "yellow"}, {'u', "blue"} };
/* { {'w', "white"}, {'b', "black"}, {'r', "red"},
				{'g', "green"}, {'o', "brown"}, {'y', "yellow"} }; */
char *givename(int num)
{
  return(coltab[num].nam);
}

char giveabr(int num)
{
  return(coltab[num].abr);
}

int givenum(char c)
{
  int i;

  for(i=0; i<COLNUM; i++)
    if( coltab[i].abr == tolower(c) )
      return(i);
  return(-1);
}

