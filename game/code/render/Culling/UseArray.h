#ifndef __USE_ARRAY_H__
#define __USE_ARRAY_H__

#include <p3d/p3dtypes.hpp>
#include <raddebug.hpp>

#ifndef TOOLS
#include <memory/srrmemory.h>
#endif

template <class T> class UseArray
{
public:
   
   /////////////////////////////////////////
   // Constructors/Destructors
   /////////////////////////////////////////
   ~UseArray()
   {
      Clear();
   }

   UseArray() : mpData(NULL), mUseSize(0)
   {
   }

   UseArray( int iSize ) : mpData(NULL)
   {
      Allocate( iSize );
   }


   /////////////////////////////////////////
   // Main Methods
   /////////////////////////////////////////
   void Init( int iIndex, T& irVal )
   {
      rAssert( (iIndex>=this->mUseSize)&&(iIndex<this->mSize) );
      this->mUseSize = iIndex+1;
      this->mpData[iIndex] = irVal;
   }

   void ClearUse()
   {
      rAssert(this->IsSetUp());
      this->mUseSize = 0;
   }

   void Add( T& irVal )
   {
      rAssert(this->mUseSize<this->mSize);
      this->mpData[this->mUseSize] = irVal;
      this->mUseSize++;
   }

   T& operator[]( int iIndex )
   {
      rAssert( (iIndex < this->mUseSize) && (iIndex > -1));
      return this->mpData[iIndex];
   }

   void Allocate( int iSize )
   {
      this->Clear();
      this->mSize = iSize;
#ifdef RAD_GAMECUBE
      HeapMgr()->PushHeap( GMA_GC_VMM );
#endif

      this->mpData = new T[this->mSize];

#ifdef RAD_GAMECUBE
      HeapMgr()->PopHeap( GMA_GC_VMM );
#endif
      rAssert(iSize>0);
      rAssert(this->mpData!=NULL);
      this->mUseSize = 0;
   }

   void Clear()
   {
      if( this->mpData != NULL )
      {
         delete[] this->mpData;
      }
      this->mpData = NULL;
      this->mUseSize = 0;
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
   int mUseSize;

protected:

private:
   /////////////////////////////////////////
   // Currently Disallowed Functions 
   //    -Not implemented
   //    -Not accessible
   //    -Use will error at Compile
   /////////////////////////////////////////
   UseArray( const UseArray& iSource );
   UseArray& operator=( const UseArray& iSource );

};

#endif