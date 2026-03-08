#ifndef __RESERVE_ARRAY_H__
#define __RESERVE_ARRAY_H__

#ifndef TOOLS
#include <memory/srrmemory.h>
#endif

template <class T> class ReserveArray
{
public:
   
   /////////////////////////////////////////
   // Constructors/Destructors
   /////////////////////////////////////////
   ~ReserveArray()
   {
      Clear();
   }

   ReserveArray() : mUseSize(0), mpData(NULL)
   {
   }

   ReserveArray( int iSize ) : mUseSize(0), mpData(NULL)
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

   void Use( int iIndex )
   {
      rAssert( (iIndex>=this->mUseSize)&&(iIndex<this->mSize) );
      this->mUseSize = iIndex+1;
   }

   void AddUse( int iCountSize )
   {
      rAssert( (iCountSize+this->mUseSize)<=this->mSize );
      this->mUseSize += iCountSize;
   }

   void Add( T& irVal )
   {
      rAssert(this->mUseSize<this->mSize);
      this->mpData[this->mUseSize] = irVal;
      this->mUseSize++;
   }

   T& operator[]( int iIndex )
   {
      rAssert( (iIndex < mUseSize) && (iIndex > -1));
      return mpData[iIndex];
   }

   void Reserve( int iCount )
   {
      // UseSize is used during the 
      // unallocated state to count the reservations
      rAssert( !this->IsSetUp() );
      this->mUseSize += iCount;
   }

   void Allocate()
   {
      rAssert( !this->IsSetUp() );
      if( this->mUseSize == 0 )
      {
         this->mSize = this->mUseSize;
         this->mpData = NULL;
      }
      else
      {
         this->mSize = this->mUseSize;

#ifdef RAD_GAMECUBE
         HeapMgr()->PushHeap( GMA_GC_VMM );
#endif

         this->mpData = new T[this->mSize];
         rAssert(this->mSize>0);
         rAssert(this->mpData!=NULL);

#ifdef RAD_GAMECUBE
         HeapMgr()->PopHeap( GMA_GC_VMM );
#endif

         this->mUseSize = 0;
      }
   }

   void Allocate( int iSize )
   {
      rAssert( this->mUseSize == 0 );
      //TODO: wha?
      if( !this->IsSetUp() )
         iSize += this->mUseSize;
      this->Clear();
      this->mSize = iSize;

#ifdef RAD_GAMECUBE
      HeapMgr()->PushHeap( GMA_GC_VMM );
#endif

      this->mpData = new T[this->mSize];
      rAssert(this->mSize>0);
      rAssert(this->mpData!=NULL);

#ifdef RAD_GAMECUBE
      HeapMgr()->PopHeap( GMA_GC_VMM );
#endif

   }

   void Clear()
   {
      if( mpData != NULL )
      {
         delete[] mpData;
      }
      mpData = NULL;
      mUseSize = 0;
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
   int mUseSize;
   T*  mpData;

protected:

private:
   /////////////////////////////////////////
   // Currently Disallowed Functions 
   //    -Not implemented
   //    -Not accessible
   //    -Use will error at Compile
   /////////////////////////////////////////
   ReserveArray( const ReserveArray& iSource );
   ReserveArray& operator=( const ReserveArray& iSource );

};

#endif