// COMP1511 18s2 -- a Set ADT
// Don't modify this file!

#ifndef _SET_H_
#define _SET_H_

#include <stdbool.h>

// Define a new `Set` type.
typedef struct _set *Set;

// Define an `item` type.  `Set` manipulates `item`s.
typedef int item;

// Create a new `Set`.
Set newSet(void);

// Release all resources associated with a `Set`.
void destroySet(Set);

// Add an `item` to the `Set`.
void setAdd(Set s, item item);

// Remove an `item` from the `Set`.
void setRemove(Set s, item item);

// Does the `Set` contain this `item`?
bool setContains(Set s, item item);

// How many items are in the `Set`?
int setSize(Set s);

// Take the union of two sets(a â?ª b).
Set setUnion(Set a, Set b);

// Take the intersection of two sets(a â?© b).
Set setIntersection(Set a, Set b);

// Is `a` a subset of `b`(a â?? b)?
bool setSubset(Set a, Set b);

// Is `a` equal to `b`(where a â?? b and b â?? a, a == b).
bool setEqual(Set a, Set b);

#endif // !defined(_SET_H_)
