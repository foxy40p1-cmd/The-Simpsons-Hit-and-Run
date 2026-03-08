#ifndef __FIXED_ARRAY_H__
#define __FIXED_ARRAY_H__

#include <p3d/p3dtypes.hpp>
#include <raddebug.hpp>
#include <memory/srrmemory.h>

template <class T> class FixedArray
{
public:
   
   /////////////////////////////////////////
   // Constructors/Destructors
   /////////////////////////////////////////
   ~FixedArray()
   {
      Clear();
   }

   FixedArray() : mpData(NULL)
   {
   }

   FixedArray( int iSize ) : mpData(NULL)
   {
      Allocate( iSize );
   }


   /////////////////////////////////////////
   // Main Methods
   /////////////////////////////////////////
   T& operator[]( int iIndex )
   {
      rAssert( (iIndex < this->mSize) && (iIndex > -1) );
      return this->mpData[iIndex];
   }

   void Allocate( int iSize )
   {
      this->Clear();
      this->mSize = iSize;

#ifdef RAD_GAMECUBE
      //HeapMgr()->PushHeap( GMA_GC_VMM );
#endif

      this->mpData = new T[this->mSize];

#ifdef RAD_GAMECUBE
      //HeapMgr()->PopHeap( GMA_GC_VMM );
#endif

      rAssert(this->mSize>0);
      rAssert(this->mpData!=NULL);
   }

   void Clear()
   {
      if( this->mpData != NULL )
      {
         delete[] this->mpData;
         this->mpData = NULL;
      }
   }

   bool IsSetUp()
   {
      if( mpData == NULL )
         return false;
      else
         return true;
   }

   /////////////////////////////////////////
   // Data
   /////////////////////////////////////////
   int mSize;
   T*  mpData;

protected:

private:
   /////////////////////////////////////////
   // Currently Disallowed Functions 
   //    -Not implemented
   //    -Not accessible
   //    -Use will error at Compile
   /////////////////////////////////////////
   FixedArray( const FixedArray& iSource );
   FixedArray& operator=( const FixedArray& iSource );

};


#endif