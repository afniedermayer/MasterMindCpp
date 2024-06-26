/* MSTR.H - header for programs in connection with master mind */

/* Objects in mastermind games
   COLNUM number of colors
   PLANUM number of places 
*/

#define COLNUM 7
#define PLANUM 4

class guess {
 public:
  void compare(const guess *frgn);    /* compare */
  int numblacks() const { return bl; }
							 /* give back the number of blacks or whites */
  int numwhites() const { return wh; }
  void choose();                /* make choice */
  int getcolor(int place) const { return gu[place]; }
							 /* give color of a place */
  void setcolor(int place, int colr) { gu[place] = colr; }
							 /* setcolor on a certain place */
  void setwhites(int num)  { wh = num; }
  void setblacks(int num)  { bl = num; }

  int gu[PLANUM];              /* guesses */
  int bl;                      /* black (number) */
  int wh;                      /* white */
};

