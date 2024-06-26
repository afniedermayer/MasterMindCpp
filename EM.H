// em.h - header for extended master mind
// November 10, 1995
// by Andreas Niedermayer

#include "mstr.h"

extern "C" {
#include <math.h>
#include <assert.h>
}

#include <iostream.h>

/* definition of class emL, a class derived from "guess" which enables
** putting the structures into a linked list
*/

class emL : public guess         // extended mastermind linked list
{
	emL *next;              // pointer to next member of list
  public:
	emL(void)  { next = 0; }    // default constructor
	emL(emL** PHeadOfList) { next = 0; LinkTo(PHeadOfList); }
	emL(emL** PHeadOfList, long PosNum) { next = 0; LinkTo(PHeadOfList);
			SetPos(PosNum); }
	emL(int* array, int nbl, int nwh);
	void LinkTo(emL** PHeadOfList);       // link to a list
	long NumberOfPos() { return pow(COLNUM,PLANUM); }// number of possibilities
	emL& SetPos(long PosNum);           // set a possibility by using a long
	emL* GetNext() { return next; }     // return pointer to next in chain
	int operator>=(const emL& Other);   // is this possible if Other has been guessed
	int HowMany();                      // count the number of successors
	int operator<=(const emL& OtherL); // same as >= but with OtherList
	emL& operator=(const emL& Other);
	void DestroySuc();
	friend ostream& operator<<(ostream&, emL&);
};

/* definition of class FreqL, a Frequency List
*/

class FreqL          // Frequency List for master mind answers
{
	long *Table;      // pointer to table
	int Length;       // length of table
  public:
	FreqL();     // default constructor
	void IncrP(int bl, int wh)     // record possibility
		 {  Table[  ((PLANUM-bl)*(PLANUM+1-bl))/2  +  wh  ]++; }
	void Clear();
	double InfoValue();           // calculate information value of table
	int AllBlacks() { return Table[0] > 0; }  // returns not 0 if possible
	~FreqL() { delete [] Table; }  // default destructor
};
