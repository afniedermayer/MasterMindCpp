// mstr.cc - methods for programs in connection with master mind
// 30.10.95 Andreas Niedermayer
// updated November 17, 1995
// updated November 26, 1995

#include "mstr.h"

extern "C" {
#include <stdlib.h>
}

void guess::compare(const guess *frgn)  // pointer to foreign class
{
  int i,j;

  int ha[PLANUM];   // ha: helping array
  int hs[PLANUM];   // hs: second helping array

  wh=0;             // set back the number of whites
  bl=0;             // and blacks to zero
  for(i=0; i<PLANUM; i++)    // copy the two combinations to helping arrays
	 if( (ha[i]=frgn->gu[i]) == (hs[i]=gu[i]) ) // if two colors at the
	 {                            // same position are equal
			bl++;                   // set a black stick
			ha[i]=-1;               // and don't forget two disable double
			hs[i]=-2;               // counting of a color
	 }
  for(i=0; i<PLANUM; i++)        // search for same colors at different
	 for(j=0; j<PLANUM; j++)      // places with two counters: i, j
		if( ha[i] == hs[j] )       // if two colors are the same
		{
			wh++;                   // set a white stick
			ha[i]=-1;               // disable double recognition
			hs[j]=-2;               // of a pair
		}
}

void guess::choose(void)   // set colors to a random value
{
  int i;
  for(i=0; i<PLANUM; i++)
	 gu[i] = rand() % COLNUM;
}














































































