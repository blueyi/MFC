#ifndef __IENUM_ITERATOR__
#define __IENUM_ITERATOR__
///////////////////////////////////////////////////////////////////////////////
//
// File           : $Workfile:   IEnumIterator.hpp  $
// Version        : $Revision:   1.5  $
// Function       : 
//
// Author         : $Author:   len  $
// Date           : $Date:   Oct 25 1998 20:51:20  $
//
// Notes          : 
//
// Modifications  :
//
// $Log:   G:/Documents/JetByte/Source/JetByteTools/COMTools/PVCS/IEnumIterator.hpv  $
// 
//    Rev 1.5   Oct 25 1998 20:51:20   len
// Bug fixes and Lint changes.
// 
//    Rev 1.4   Sep 16 1998 07:41:54   len
// 
//    Rev 1.3   Aug 30 1998 16:25:34   len
// 
//    Rev 1.2   Aug 28 1998 07:33:04   len
// 
//    Rev 1.1   Jun 06 1998 07:56:20   Len
// 
//    Rev 1.0   May 18 1998 07:34:46   Len
// Initial revision.
// 
///////////////////////////////////////////////////////////////////////////////
//
// Copyright 1998 JetByte Limited.
//
// JetByte Limited grants you ("Licensee") a non-exclusive, royalty free, 
// licence to use, modify and redistribute this software in source and binary 
// code form, provided that i) this copyright notice and licence appear on all 
// copies of the software; and ii) Licensee does not utilize the software in a 
// manner which is disparaging to JetByte Limited.
//
// This software is provided "AS IS," without a warranty of any kind. ALL
// EXPRESS OR IMPLIED CONDITIONS, REPRESENTATIONS AND WARRANTIES, INCLUDING 
// ANY IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
// OR NON-INFRINGEMENT, ARE HEREBY EXCLUDED. JETBYTE LIMITED AND ITS LICENSORS 
// SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF 
// USING, MODIFYING OR DISTRIBUTING THE SOFTWARE OR ITS DERIVATIVES. IN NO 
// EVENT WILL JETBYTE LIMITED BE LIABLE FOR ANY LOST REVENUE, PROFIT OR DATA, 
// OR FOR DIRECT, INDIRECT, SPECIAL, CONSEQUENTIAL, INCIDENTAL OR PUNITIVE 
// DAMAGES, HOWEVER CAUSED AND REGARDLESS OF THE THEORY OF LIABILITY, ARISING 
// OUT OF THE USE OF OR INABILITY TO USE SOFTWARE, EVEN IF JETBYTE LIMITED 
// HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
//
// This software is not designed or intended for use in on-line control of
// aircraft, air traffic, aircraft navigation or aircraft communications; or in
// the design, construction, operation or maintenance of any nuclear
// facility. Licensee represents and warrants that it will not use or
// redistribute the Software for such purposes.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __COM_EXCEPTION__
#include "ComException.hpp"
#endif

#ifndef __COM_UTILS__
#include "ComUtils.hpp"
#endif

///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

namespace JetByteTools {

///////////////////////////////////////////////////////////////////////////////
// Templates defined in this file...
///////////////////////////////////////////////////////////////////////////////

template <class T, class I, class E> class IEnumIterator;

template <class T, class E> class TCache;

///////////////////////////////////////////////////////////////////////////////
// TCache
//
// A template cache to manage the "read ahead" buffer used by IEnumIterator 
// so that we can call the underlying interface pointer's Next() function for
// multiple items...
///////////////////////////////////////////////////////////////////////////////

template <class T, class E>
class TCache
{
	public :

		TCache(unsigned long size = 1);				// Create a cache of a specific  
																// size 
		~TCache();

		void ResizeCache(unsigned long newSize);	// Change size of cache, safe to
																// use even if cache has items
																// in it and you're making it
																// smaller...
		
		void EmptyCache();								// empties the cache and destroys
																// items.
		
		E *GetCache() const;								// Returns pointer to the cache
		
		unsigned long GetSize() const;				// Returns size of cache

		void FillCache(unsigned long numItems);	// Set cache as having x items

		const E &GetCurrent() const;					// Get current item

		bool Next();										// Step to next item, Destroy
																// last item, return true if the
																// cache is not now empty

		unsigned long Skip(unsigned long numToSkip);		// Skip numToSkip items or
																		// to end of cache, return
																		// number actually skipped

		bool IsEmpty() const;							// Does the cache have items?

      TCache(const TCache<T,E> &rhs);					// Copy
      TCache &operator=(const TCache<T,E> &rhs);	// Assign


	private :

		E *CopyCache() const;						

		static E *CopyCache(
			E *pCache, 
			unsigned long current, 
			unsigned long cached, 
			unsigned long newSize);

		void Destroy();

		void DestroyItem(E item);

		mutable E *m_pCache;								// Mutable to allow for lazy
																// creation

		unsigned long m_current;						// current item in cache
		unsigned long m_cached;							// number of items in cache
		unsigned long m_size;							// logical size of cache
		mutable unsigned long m_allocatedSize;		// physical size of cache
};

///////////////////////////////////////////////////////////////////////////////
// IEnumIterator<T,I,E>
///////////////////////////////////////////////////////////////////////////////

template <class T, class I, class E> 
class IEnumIterator
{

	friend class TCache<T,E>;

   public :

      class NullIterator {};				// Exception thrown if you dereference
													// an invalid iterator

      virtual ~IEnumIterator();

      IEnumIterator<T,I,E> &operator++();

#ifdef IENUM_ITERATOR_USE_POST_INC		// Protect from indavertant use of 
													// expensive post inc

      IEnumIterator<T,I,E> operator++(int);

#endif // IENUM_ITERATOR_USE_POST_INC

      bool operator!=(const IEnumIterator<T,I,E> &rhs);
      bool operator==(const IEnumIterator<T,I,E> &rhs);

      operator E() const;					// Access enumerated item

		void SetCacheSize(					// Change read ahead for I->Next()
			unsigned long max);

		void Reset();							// Reset iterator to start of sequence

		unsigned long Skip(					// Skip x items, returns number skipped
			unsigned long numToSkip);

		static const T &End();				// Generic End of sequence iterator

   protected :       
         
      IEnumIterator(I *pIEnum, unsigned long max = 64);

      const E &Enumerated() const;

      IEnumIterator(const IEnumIterator<T,I,E> &rhs);
      IEnumIterator &operator=(const IEnumIterator<T,I,E> &rhs);

   private :

      void Advance();						
      void CheckValid() const;
		void CheckPrimed() const;

		// Function called to destroy each item in the cache
		// Defaults to doing nothing
		virtual void Destroy(E /*item*/) const { }

		// Function called to copy each item in the cache
		// Defaults to returning the item supplied 
		
		virtual E Copy(E item) const { return item; }

      mutable I *m_pIEnum;

		mutable bool m_bAtEnd;
		mutable bool m_bNotPrimed;

		TCache<T,E> m_cache;
		
		// Interface for our friend TCache<E>
		
		static void DestroyItem(E item); 
		static E CopyItem(E item); 
};

///////////////////////////////////////////////////////////////////////////////
// Implement TCache
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction
///////////////////////////////////////////////////////////////////////////////

template <class T, class E>
TCache<T,E>::TCache(
	unsigned long size /* = 1 */)
	:	m_pCache(0),
		m_current(0),
		m_cached(0),
		m_size(size),
		m_allocatedSize(0)
{
	// Nothing to do. We dont allocate the cache at this point, the client 
	// is likely to change the size before use, so we will wait until either
	// the size changes or we attempt to use the cache before we allocate.
}

template <class T, class E>
TCache<T,E>::TCache(const TCache<T,E> &rhs)
	:	m_pCache(rhs.CopyCache()),
		m_current(rhs.m_current),
		m_cached(rhs.m_cached),
		m_size(rhs.m_size),
		m_allocatedSize(rhs.m_allocatedSize)
{

}

template <class T, class E>
TCache<T,E>::~TCache()
{
	Destroy();			// Call Destroy to Destroy each item remaining in the 
							// cache and then delete the cache itself...
}

template <class T, class E>
TCache<T,E> &TCache<T,E>::operator=(const TCache<T,E> &rhs)
{
	if (this != &rhs)
	{
		E *pNewCache = rhs.CopyCache();

		Destroy();		// Call Destroy to Destroy each item remaining in the 
							// cache and then delete the cache itself...
		
		m_pCache = pNewCache;		
	
		m_current = rhs.m_current;
		m_cached = rhs.m_cached;
		m_size = rhs.m_size;
		m_allocatedSize = rhs.m_allocatedSize;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Cache management
///////////////////////////////////////////////////////////////////////////////

template <class T, class E>
void TCache<T,E>::ResizeCache(unsigned long newSize)
{
	if (newSize > m_allocatedSize)
	{
		// Making cache physically bigger...

		E *pNewCache = CopyCache(m_pCache, m_current, m_cached, newSize);

		Destroy();		// Call Destroy to Destroy each item remaining in the 
							// cache and then delete the cache itself...

		m_pCache = pNewCache;

		m_allocatedSize = newSize;
		m_size = newSize;
	}
	else 
	{
		// Cache is physically big enough, adjust logical size
		m_size = newSize;
	}
}

template <class T, class E>
void TCache<T,E>::EmptyCache()
{
	while (!IsEmpty())
	{
		Next();
	}

	m_cached = 0;
	m_current = 0;
}

template <class T, class E>
void TCache<T,E>::FillCache(unsigned long numItems)
{
	// Cache items are inserted by calling GetCache and writing to the
	// pointer returned...

	// This just sets the counter...

	m_cached = numItems;
}

template <class T, class E>
E *TCache<T,E>::GetCache() const
{
	if (m_allocatedSize == 0 && m_size != 0)
	{
		// Lazy cache creation, if we still don't have one, create it now, 
		// just before first use...

		m_pCache = new E[m_size];

		m_allocatedSize = m_size;
	}

	// Could throw an exception if the cache is 0 size?
	// We could paramaterise ourself on an exception type to
	// throw in this circumstance...

//	if (IsEmpty())
//	{
//		throw E;
//	}

	return m_pCache;
}

template <class T, class E>
unsigned long TCache<T,E>::GetSize() const
{
	return m_size;
}

template <class T, class E>
const E &TCache<T,E>::GetCurrent() const
{
	// We could paramaterise ourself on an exception type to
	// throw in this circumstance...

//	if (IsEmpty())
//	{
//		throw E;
//	}

	return m_pCache[m_current];
}

template <class T, class E>
bool TCache<T,E>::IsEmpty() const
{
	return (m_cached == 0 || m_current >= m_cached);
}

template <class T, class E>
bool TCache<T,E>::Next()
{
	bool ok = false;

	if (++m_current < m_cached)
	{
		ok = true;
	}

	if (m_current <= m_cached)
	{
		// Destroy the item we just stepped past...
		// Including the last item...

		DestroyItem(m_pCache[m_current -1]);
	}

	return ok;
}

template <class T, class E>
unsigned long TCache<T,E>::Skip(unsigned long numToSkip)
{
	unsigned long numSkipped = 0;

	while(!IsEmpty() && numSkipped < numToSkip)
	{
		Next();
		numSkipped++;
	}

	return numSkipped;
}

template <class T, class E>
void TCache<T,E>::Destroy()
{
	EmptyCache();

	delete [] m_pCache;
}

template <class T, class E>
void TCache<T,E>::DestroyItem(E item)
{
	// It's easier to place the replacable code for destroying an 
	// item in the iterator.... So, we'll call a private static member function
	// on our iterator to destroy it
	
	T::DestroyItem(item);
}


template <class T, class E>
E *TCache<T,E>::CopyCache() const
{
	return CopyCache(m_pCache, m_current, m_cached, m_allocatedSize);
}

template <class T, class E>
E *TCache<T,E>::CopyCache(
	E *pCache, 
	unsigned long current, 
	unsigned long cached, 
	unsigned long newSize)
{
	E *pNewCache = 0;
	
	if (newSize)
	{
		pNewCache = new E[newSize];

		// Only copy the valid area of the cache...

		for (unsigned long i = current; i < cached; i++)
		{
			pNewCache[i] = T::CopyItem(pCache[i]);
		}
	}
	
	return pNewCache;
}

///////////////////////////////////////////////////////////////////////////////
// Implement IEnumIterator
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction
///////////////////////////////////////////////////////////////////////////////

template <class T, class I, class E> 
IEnumIterator<T,I,E>::IEnumIterator(I *pIEnum, unsigned long max /* = 1 */)
   :	m_pIEnum(SafeAddRef(pIEnum)),
		m_cache(max),
		m_bAtEnd(false),
		m_bNotPrimed(true)
{
	if (!m_pIEnum)
	{
		m_bAtEnd = true;
		m_bNotPrimed = false;
	}
}

template <class T, class I, class E> 
IEnumIterator<T,I,E>::IEnumIterator(const IEnumIterator<T,I,E> &rhs)
	:	m_pIEnum(0),
		m_cache(rhs.m_cache),
		m_bAtEnd(rhs.m_bAtEnd),
		m_bNotPrimed(rhs.m_bNotPrimed)
{
   if (rhs.m_pIEnum)
   {
      HRESULT hr = rhs.m_pIEnum->Clone(&m_pIEnum);

      if (FAILED(hr))
      {
         throw CComException(_T("IEnumIterator<T,I,E>::IEnumIterator()"), hr);
      }
   }
}

template <class T, class I, class E> 
IEnumIterator<T,I,E>::~IEnumIterator()
{
	m_pIEnum = SafeRelease(m_pIEnum);
}

template <class T, class I, class E> 
IEnumIterator<T,I,E> &IEnumIterator<T,I,E>::operator=(const IEnumIterator<T,I,E> &rhs)
{
   if (this != &rhs)
   {
      if (rhs.m_pIEnum)
      {
         I *pNewEnum = 0;

         HRESULT hr = rhs.m_pIEnum->Clone(&pNewEnum);

         if (SUCCEEDED(hr))
         {
            m_pIEnum->Release();

            m_pIEnum = pNewEnum;

				m_cache = rhs.m_cache;
			}
         else
         {
            throw CComException("IEnumIterator<T,I,E>::operator=", hr);
         }
      }
      else
      {
         m_pIEnum = 0;
      }

		m_bAtEnd = rhs.m_bAtEnd;
		m_bNotPrimed = rhs.m_bNotPrimed;
   }

   return *this;
}

///////////////////////////////////////////////////////////////////////////////
// Iteration
///////////////////////////////////////////////////////////////////////////////

template <class T, class I, class E> 
IEnumIterator<T,I,E> &IEnumIterator<T,I,E>::operator++()
{
	// Since we no longer call advance in the ctor we must 
	// make sure it's been called once to make the first item
	// valid before we advance away from the first item,
	// It's messier but at least we don't have a fully primed 
	// iterator to copy around straight after construction...

	CheckPrimed();

   Advance();

   return *this;
}

#ifdef IENUM_ITERATOR_USE_POST_INC

template <class T, class I, class E> 
IEnumIterator<T,I,E> IEnumIterator<T,I,E>::operator++(int)
{
	// Since we no longer call advance in the ctor we must 
	// make sure it's been called once to make the first item
	// valid before we advance away from the first item,
	// It's messier but at least we don't have a fully primed 
	// iterator to copy around straight after construction...

	CheckPrimed();

   T oldValue = *this;

   Advance();

   return oldValue;
}

#endif // IENUM_ITERATOR_USE_POST_INC

template <class T, class I, class E> 
bool IEnumIterator<T,I,E>::operator!=(const IEnumIterator<T,I,E> &rhs)
{
   // defer to operator==
   return !(*this == rhs);
}

template <class T, class I, class E> 
bool IEnumIterator<T,I,E>::operator==(const IEnumIterator<T,I,E> &rhs)
{
	// Since we no longer call advance in the ctor we must 
	// make sure it's been called once to make the first item
	// valid before we access it for the first time.
	// It's messier but at least we don't have a fully primed 
	// iterator to copy around straight after construction...

	CheckPrimed();

	// should compare contents of Enumerated?
   return ((m_pIEnum == rhs.m_pIEnum && (true)) || 
		      m_bAtEnd && m_cache.IsEmpty() && 
				rhs.m_bAtEnd && rhs.m_cache.IsEmpty());
}

template <class T, class I, class E> 
const T &IEnumIterator<T,I,E>::End()
{
	static T End(0,0);

	return End;
}

template <class T, class I, class E> 
void IEnumIterator<T,I,E>::Reset()
{
	if (m_pIEnum)
	{
		HRESULT hr = m_pIEnum->Reset();

		if (S_OK != hr)
		{
			throw CComException(_T("IEnumIterator<T,I,E>::Reset()"), hr);
		}
	
		m_bAtEnd = false;

		m_cache.EmptyCache();

		m_bNotPrimed = true;
	}
}

template <class T, class I, class E> 
unsigned long IEnumIterator<T,I,E>::Skip(unsigned long numToSkip)
{
	unsigned long numSkipped = 0;

   if (m_pIEnum)
   {
		numSkipped = m_cache.Skip(numToSkip);

		if (numSkipped != numToSkip)
		{
			// Even after skipping all entries in the cache, we still must
			// skip more...

			if (S_OK == m_pIEnum->Skip(numToSkip - numSkipped))
			{
				numSkipped = numToSkip;
			}
			else
			{
				// That's all folks...

				m_bAtEnd = true;
			}
		
			// cache is empty now, but we'll leave priming it until we need
			// to access it...

			m_bNotPrimed = true;
		}
	}

	return numSkipped;
}

///////////////////////////////////////////////////////////////////////////////
// Access to what we're enumerating...
///////////////////////////////////////////////////////////////////////////////

template <class T, class I, class E> 
const E &IEnumIterator<T,I,E>::Enumerated() const
{
	// Since we no longer call advance in the ctor we must 
	// make sure it's been called once to make the first item
	// valid before we access it for the first time.
	// It's messier but at least we don't have a fully primed 
	// iterator to copy around straight after construction...

	CheckPrimed();

	CheckValid();

   return m_cache.GetCurrent();
}

template <class T, class I, class E> 
IEnumIterator<T,I,E>::operator E() const
{
   return Enumerated();
}

///////////////////////////////////////////////////////////////////////////////
// Helper function for cache management
///////////////////////////////////////////////////////////////////////////////

template <class T, class I, class E> 
void IEnumIterator<T,I,E>::SetCacheSize(unsigned long max)
{
	m_cache.ResizeCache(max);
}

///////////////////////////////////////////////////////////////////////////////
// Helper function for operator ++
///////////////////////////////////////////////////////////////////////////////

template <class T, class I, class E> 
void IEnumIterator<T,I,E>::Advance()
{
   if (m_pIEnum)
   {
		if (!m_cache.Next() && !m_bAtEnd)
		{
			// Grab some more elements and cache them...

			m_cache.EmptyCache();

			unsigned long cached = 0;

			HRESULT hr = m_pIEnum->Next(m_cache.GetSize(), m_cache.GetCache(), &cached);

			m_cache.FillCache(cached);

			if (S_FALSE == hr)
			{
				m_bAtEnd = true;
			}
			else if (S_OK != hr)
			{
				throw CComException(_T("IEnumIterator<T,I,E>::Advance()"), hr);
			}
		}
   }
}

template <class T, class I, class E> 
void IEnumIterator<T,I,E>::CheckValid() const
{
   if (!m_pIEnum || m_cache.IsEmpty())
   {
		// Can't dereference an "End" iterator.
      throw NullIterator();
   }
}

template <class T, class I, class E> 
void IEnumIterator<T,I,E>::CheckPrimed() const
{
	// Since we no longer call advance in the ctor we must 
	// make sure it's been called once to make the first item
	// valid before we advance away from the first item, or
	// access it for the first time. 

	// It's messier but at least we don't have a fully primed 
	// iterator to copy around straight after construction...

	if (m_bNotPrimed)
	{
		// Even though everything is mutable, we still can't call 
		// Advance() as it's a non-const member function. We could
		// declare it as const (which seems wrong, it's not) or
		// we can cheat like this... We'll cheat for now...

	   const_cast<IEnumIterator<T,I,E>*>(this)->Advance();
		
		m_bNotPrimed = false;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Interface for TCache<T,E>
///////////////////////////////////////////////////////////////////////////////

template <class T, class I, class E> 
void IEnumIterator<T,I,E>::DestroyItem(E item)
{
	// Jump through hoops...

	// Access an object known to exist.
	// through a pointer to its base class (us)
	
	const IEnumIterator<T,I,E> *pB = &End();

	// As we can't call a private member function of another class
	// but we can call one of ours... (and it's virtual)

	pB->Destroy(item);
}

template <class T, class I, class E> 
E IEnumIterator<T,I,E>::CopyItem(E item)
{
	// Jump through hoops...

	// Access an object known to exist.
	// through a pointer to its base class (us)
	
	const IEnumIterator<T,I,E> *pB = &End();

	// As we can't call a private member function of another class
	// but we can call one of ours... (and it's virtual)

	return pB->Copy(item);
}


///////////////////////////////////////////////////////////////////////////////
// Namespace: JetByteTools
///////////////////////////////////////////////////////////////////////////////

} // End of namespace JetByteTools 

#endif // __IENUM_ITERATOR__

///////////////////////////////////////////////////////////////////////////////
// End of file
///////////////////////////////////////////////////////////////////////////////
