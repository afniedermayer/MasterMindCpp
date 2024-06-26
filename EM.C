// em.c - extended mastermind functions
// November 10, 1995
// by Andreas Niedermayer
// updated November 17, 1995
// updated November 26, 1995
// files to be linked to:  mstr.cc
// needed header files:    em.h  mstr.h

#include "em.h"

extern "C" {
#include <assert.h>
}

////////////////////////////////////////////////////////////////////////////
/// methods handling emL, a list of guesses and answers derived from "guess"
////////////////////////////////////////////////////////////////////////////

emL& emL::SetPos(long PosNum)   // set colors belonging to Possibility Number
{
	for(int i = 0; i<PLANUM; i++)
	{
		setcolor(i, PosNum % long(COLNUM) );
		PosNum /= COLNUM;
	}
	return *this;
}

void emL::LinkTo(emL** PHeadOfList)   // link an object to a list pointed to
{                                     // by PHeadOfList
	if( *PHeadOfList == 0 )    // if list is empty
		*PHeadOfList = this;    // record this as first entry
	else{
		for(emL* ce = *PHeadOfList; ce->next != 0; ce = ce->next); // find end
		ce->next = this;                // append this to the end of the list
	}
}

emL::emL(int* array, int nbl, int nwh)
{     // construct emL with int[](colors), number of whites and blacks given
	for(int i = 0; i<PLANUM; i++)
		setcolor(i, array[i]);
	setblacks(nbl);
	setwhites(nwh);
	next = 0;
}

int emL::operator>=(const emL& Other)  // can this be true if Other has
{                                      // been guessed? no == 0
	compare(&Other);  // make a comparison with Other

	return ( numblacks() == Other.numblacks() )  &&
			 ( numwhites() == Other.numwhites() );
}

int emL::operator<=(const emL& OtherL) // does OtherList allow this?
{                         // look at all successors of OtherL
	for(const emL* ce = &OtherL;  ce != 0;  ce = ce->next)
		if( !(*this >= *ce) )    // if there's only one contradiction
			return 0;             // then return no (=0)
	return -1;           // if no contradiction has been found: yes
}

int emL::HowMany()     // return number of successors
{
	emL* ce = this;
	for(int i = 0 ;  ce->next != 0;  i++, ce = ce->next);

	return i;
}

emL& emL::operator=(const emL& Other)  // copy one class to another
{
	for(int i=0; i<PLANUM; i++)         // copy colors
		setcolor(i, Other.getcolor(i));
	setwhites( Other.numwhites() );     // copy whites
	setblacks( Other.numblacks() );     //      and blacks

	return *this;
}

void emL::DestroySuc()         // destroy all successors and class itself
{
	for( emL* ClDe = this; ClDe != 0; ) // Class to be Destroyed
	{
		emL* PtoN = ClDe->next;          // store address of next
		delete ClDe;                     // delete class
		ClDe = PtoN;                     // go to next
	}
}

ostream& operator<<(ostream& os, emL& e)
{                 // method for printing a emL class (rather for debugging)
	os << "\nguesses: ";
	for(int i = 0; i<PLANUM; i++)
		os << e.gu[i] << ' ';
	os << "\nBlacks: " << e.bl << " Whites: " << e.wh
		<< "\nNext: " << long(e.next);
	return os;
}

//////////////////////////////////////////////////////////////////////////
// methods handling FreqL, a Frequency List that count possible responses
// and calcutes with their help the information value of a question
//////////////////////////////////////////////////////////////////////////

FreqL::FreqL()      // construct class
{
	Length = (PLANUM * (PLANUM+3)) / 2  +  1;  // calculate Length
	Table = new long[Length];     // make place for Table
	assert( Table != 0 );         // is there an error ?
	Clear();
}

double FreqL::InfoValue()
{
	double dr = 0;    // double return value
	double ntot = 0;  // number of all possibities involved
	int lc;           // was long counter, now only integer

	for(lc = 0;  lc<Length; ntot += Table[lc++])
		if( Table[lc] > 1L )
			dr -= double(Table[lc]) * log(double(Table[lc]));

	return (ntot>0) ? ( (dr/ntot+log(ntot)) / log(2.0) ) : 0 ;
}                // return solution of information formula

void FreqL::Clear()      // Clear all fields of a frequency list
{
	for(int i = 0; i<Length; i++)   // take each field
		Table[i] = 0L;               // and clear it
}
