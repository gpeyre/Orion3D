/*---------------------------------------------------------------------*/
/*                         OR_Vector_Template.h                        */
/*---------------------------------------------------------------------*/
/* a vector template, ie. an array of dynamic size.                    */            
/*---------------------------------------------------------------------*/

/** \file 
	Contains the definition of a vector template, ie. an array of dynamic size.
	\author Gabriel.
**/

#ifndef _OR_VECTOR_TEMPLATE_H_
#define _OR_VECTOR_TEMPLATE_H_

#include "../configuration/OR_Config.h"

namespace OR
{
	
/*---------------------------------------------------------------------*/
/*                   class OR_BasicVector_Template                     */
/*---------------------------------------------------------------------*/
/* a simple vector template.                                           */
/*---------------------------------------------------------------------*/

/// a simple vector template.
/**
	This is a lightweight base class for containers. By default, it does not
	preallocate any memory.  It contains all the basic functionality of the derived 
	OR_Vector_Template class, but none of the gimmicks.
	\author Gabriel
*/

template<class T>
class ORION3D_API OR_BasicVector_Template
{
protected:
	/** length of the vector */
	OR_I32 count;
	/** the maximum size of the vector (current limit, automatically modified !) */
	OR_I32 limit;
	/** the number of elements added each time the upper bound is exceeded */
	OR_I32 threshold;
	/** the array of T datas */
	T* root;
public:
	/** Initialize object to hold initially 'ilimit' elements, and increase
		storage by 'ithreshold' each time the upper bound is exceeded. */
	OR_BasicVector_Template (OR_I32 ilimit = 0, OR_I32 ithreshold = 0)
	{
		count = 0;
		limit = (ilimit > 0 ? ilimit : 0);
		threshold = (ithreshold > 0 ? ithreshold : 16);
		if (limit != 0)
			root = (T*)malloc (limit * sizeof(T));
	}
  
	/** Destroy the container but NONE of the objects to which it points. */
	virtual ~OR_BasicVector_Template()
	{
		if (root) free (root);
	}

	/** Get a reference to n-th element */
	OR_INLINE
	T& operator [] (OR_I32 n)
	{
		OR_ASSERT (n >= 0);
		if (n >= count)
			SetLength (n + 1);
		return (root [n]);
	}
	/** Same but doesn't call SetLength () in the event n is out of bounds */
	OR_INLINE
	T& operator [] (OR_I32 n) const
	{
		OR_ASSERT (n >= 0);
		OR_ASSERT (n < count);
		return (root [n]);
	}
	/** Same but in function form */
	OR_INLINE
	T& Get (OR_I32 n) const
	{
		OR_ASSERT (n >= 0);
		OR_ASSERT (n < count);
		return (root [n]);
	}

	/** Set vector length to n */
	void SetLength (OR_I32 n)
	{
		count = n;
		if (n > limit || (limit > threshold && n < limit - threshold))
		{
			n = ((n + threshold - 1) / threshold) * threshold;
			if (!n)
			{
				if (root)
				free (root);
				root = NULL;
			}
			else if (root == 0)
				root = (T*) malloc(n * sizeof(T));
			else
				root = (T*) realloc(root, n * sizeof(T));
			limit = n;
		}
	}

	/** Query vector length */
	inline OR_I32 GetLength () const
	{
		return (count);
	}
	/** Query vector limit */
	inline OR_I32 GetLimit () const
	{
		return (limit);
	}

	/** Delete element number 'n' from vector (attention: non virtual!) */
	OR_Bool Delete (OR_I32 n)
	{
		if (n >= 0 && n < count)
		{
			const OR_I32 ncount = count - 1;
			const OR_I32 nmove = ncount - n;
			if (nmove > 0)
				memmove (&root [n], &root [n + 1], nmove * sizeof (T));
			SetLength (ncount);
			return true;
		}
		else
			return false;
	}

	/** Exchange two elements in array */
	inline void Exchange (OR_I32 n1, OR_I32 n2)
	{
		T tmp = root [n1];
		root [n1] = root [n2];
		root [n2] = tmp;
	}
	/** Find a element in array and return its index (or -1 if not found) */
	OR_I32 Find (T which) const
	{
		for (OR_I32 i = 0; i < GetLength(); i++)
		if (root [i] == which)
			return i;
		return -1;
	}
	/** Push a element on 'top' of vector */
	inline OR_I32 Push (T what)
	{
		SetLength (count + 1);
		root [count - 1] = what;
		return (count - 1);
	}
	/** Pop a element from vector 'top' */
	inline T Pop ()
	{
		T ret = root [count - 1];
		SetLength (count - 1);
		return (ret);
	}

	/** Insert element 'Item' before element 'n' */
	OR_Bool Insert (OR_I32 n, T Item)
	{
		if (n <= count)
		{
			SetLength (count + 1); // Increments 'count' as a side-effect.
			const OR_I32 nmove = (count - n - 1);
			if (nmove > 0)
				memmove (&root [n + 1], &root [n], nmove * sizeof (T));
			root [n] = Item;
		    return true;
		}
		else
			return false;
	}
};

/*---------------------------------------------------------------------*/
/*                   class OR_Vector_Template                          */
/*---------------------------------------------------------------------*/
/* a vector template.                                                  */
/*---------------------------------------------------------------------*/

/// a vector template.
/**
	OR_Vector_Template is an template class which can hold an unlimited array
	of specified <T> data. Since this is a basic object, it does
	not presume anything about its elements, so FreeItem() is
	effectively a no-op. If you want vector elements to free automatically
	occupied memory upon vector destruction you should create a derived
	class which should provide its own FreeItem() method (see csStrVector
	for a example).

	Note that FreeItem() returns a boolean value which is the success
	status. This is used in Delete() and DeleteAll() to decide whenever
	an element can be really deleted - if the element has a good reason to
	stay 'sticky' it can return false from FreeItem().
*/

template<class T>
class OR_Vector_Template : public OR_BasicVector_Template<T>
{
public:
	/** Constructor : Initialize object to hold initially 'ilimit' elements,
		and increase storage by 'ithreshold' each time the upper bound is exceeded. */
	OR_Vector_Template (OR_I32 ilimit = 8, OR_I32 ithreshold = 16) 
    : OR_BasicVector_Template<T>(ilimit, ithreshold) {}

	/** Destroy the vector object. */
	virtual ~OR_Vector_Template () {}

	/** Find a element by key (using CompareKey method) */
	OR_I32 FindKey (T Key, OR_I32 Mode = 0) const
	{
		for (OR_I32 i = 0; i < GetLength(); i++)
		if (CompareKey (root [i], Key, Mode) == 0)
			return i;
		return -1;
	}
	/** Find a element in a SORTED array by key (using CompareKey method) */
	OR_I32 FindSortedKey (void* Key, OR_I32 Mode = 0) const
	{
		OR_I32 l = 0, r = GetLength() - 1;
		while (l <= r)
		{
			OR_I32 m = (l + r) / 2;
			OR_I32 cmp = CompareKey (root [m], Key, Mode);

			if (cmp == 0)
				return m;
			else if (cmp < 0)
				l = m + 1;
			else
				r = m - 1;
		}
		return -1;
	}

	/** Partially sort the array */
	void QuickSort (OR_I32 Left, OR_I32 Right, OR_I32 Mode = 0)
	{
	recurse:
		OR_I32 i = Left, j = Right;
		OR_I32 x = (Left + Right) / 2;
		do
		{
			while ((i != x) && (Compare (Get (i), Get (x), Mode) < 0))
				i++;
			while ((j != x) && (Compare (Get (j), Get (x), Mode) > 0))
				j--;
		    if (i < j)
			{
				Exchange (i, j);
				if (x == i)
					x = j;
				else if (x == j)
					x = i;
			}
			if (i <= j)
			{
				i++;
				if (j > Left)
					j--;
			}
		} while (i <= j);

		if (j - Left < Right - i)
		{
			if (Left < j)
				QuickSort (Left, j, Mode);
		    if (i < Right)
			{
				Left = i;
				goto recurse;
		    }
		}
		else
		{
			if (i < Right)
				QuickSort (i, Right, Mode);
		    if (Left < j)
			{
				Right = j;
				goto recurse;
		    }
		}
	}
	/** Same but for all elements */
	void QuickSort (OR_I32 Mode = 0)
	{
		if (count > 0)
			QuickSort (0, count - 1, Mode);
	}

	/** Delete element number 'n' from vector */
	OR_Bool Delete (OR_I32 n)
	{
		if (n >= 0 && n < count)
		{
			if (!FreeItem (root [n]))
				return false;
		    return OR_BasicVector_Template<T>::Delete(n);
		}
		else
			return false;
	}
	/** Replace n-th item with another (free previous value) */
	OR_Bool Replace (OR_I32 n, T what)
	{
		if (n < count)
		{
			if (!FreeItem (root [n]))
				return false;
			root [n] = what;
		    return true;
		}
		else
			return false;
	}
	/** Delete all elements */
	void DeleteAll ()
	{
		OR_I32 idx;
		for (idx = count - 1; idx >= 0; idx--)
			if (!FreeItem (root [idx]))
			break;
		SetLength (idx + 1);
		while (idx >= 0)
			Delete (idx--);
	}

	/** Insert element 'Item' so that array remains sorted (assumes its already) */
	OR_I32 InsertSorted (T Item, OR_I32 *oEqual = NULL, OR_I32 Mode = 0)
	{
		OR_I32 m = 0, l = 0, r = GetLength () - 1;
		while (l <= r)
		{
			m = (l + r) / 2;
			OR_I32 cmp = Compare (root [m], Item, Mode);

			if (cmp == 0)
			{
				if (oEqual) *oEqual = m;
				Insert (++m, Item);
				return m;
			}
			else if (cmp < 0)
				l = m + 1;
			else
				r = m - 1;
		}
		if (r == m)
			m++;
		Insert (m, Item);
		if (oEqual) *oEqual = -1;
		return m;
	}


	/* virtual functions **************************************************************/
	/** Tells if an element should be destroyed. By default, always says 'yes!'.
		Should be overload if you want to destroy object when the array is cleared. */
	virtual OR_Bool FreeItem (T Item)
	{
		return true;
	}
	/** Compare two array elements in given Mode : should be overloaded !! */
	virtual OR_I32 Compare (T Item1, T Item2, OR_I32 Mode) const
	{
		return 0;
	}
	/** Compare entry with a key; for OR_Vector_Template just compare (OR_I32)Key vs (OR_I32)Item */
	virtual OR_I32 CompareKey (T Item, void* Key, OR_I32 Mode) const
	{
		return 0;
	}
};




} // namespace OR

#endif /* #ifndef _OR_VECTOR_TEMPLATE_H_ */

///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//                           END OF FILE                                     //
///////////////////////////////////////////////////////////////////////////////