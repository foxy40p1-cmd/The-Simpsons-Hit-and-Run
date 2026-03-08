#ifndef __SWAP_ARRAY_H__
#define __SWAP_ARRAY_H__

#include <p3d/p3dtypes.hpp>

#ifndef TOOLS
//#include "../../memory/srrmemory.h"
#endif

#define ASSSERT(s) rTuneAssert(s)

template <class T> class SwapArray
{
public:
   
   /////////////////////////////////////////
   // Constructors/Destructors
   /////////////////////////////////////////
   ~SwapArray()
   {
      Clear();
   }

   SwapArray() : mUseSize(0), mpData(NULL)
   {
   }

   SwapArray( int iSize ) : 
    mUseSize(0),
    mpData(NULL)
   {
      Allocate( iSize );
   }


   /////////////////////////////////////////
   // Main Methods
   /////////////////////////////////////////
   void Remove( int iIndex )
   {
      //A pointer safe swap-out
      ASSSERT( (iIndex<this->mUseSize) );
      this->mSwapT = this->mpData[iIndex]; 
      this->mpData[iIndex] = this->mpData[this->mUseSize-1];
      this->mpData[this->mUseSize-1] = this->mSwapT;
      this->mUseSize--;
   }

   void RemoveKeepOrder( int iIndex )
   {
      //A pointer safe swap-out
      ASSSERT( (iIndex<this->mUseSize) );
      this->mSwapT = this->mpData[iIndex]; 
      while(iIndex<this->mUseSize-1)
      {
          this->mpData[iIndex] = this->mpData[iIndex+1];
          iIndex++;
      }
      this->mpData[this->mUseSize-1] = this->mSwapT;
      this->mUseSize--;
   }

   void Swap( int iIndex1, int iIndex2 )
   {
      //A pointer safe swap-out
      ASSSERT( (iIndex1<this->mUseSize) && (iIndex2<this->mUseSize) );
      this->mSwapT = this->mpData[iIndex1]; 
      this->mpData[iIndex1] = this->mpData[iIndex2];
      this->mpData[iIndex2] = this->mSwapT;
   }

   void Init( int iIndex, T& irVal )
   {
      ASSSERT( (iIndex>=this->mUseSize)&&(iIndex<this->mSize) );
      this->mUseSize = iIndex+1;
      this->mpData[iIndex] = irVal;
   }

   void ClearUse()
   {
      ASSSERT(this->IsSetUp());
      this->mUseSize = 0;
   }

   void Use( int iIndex )
   {
      ASSSERT( (iIndex>=this->mUseSize)&&(iIndex<this->mSize) );
      this->mUseSize = iIndex+1;
   }

   void AddUse( int iCountSize )
   {
      ASSSERT( (iCountSize+this->mUseSize)<=this->mSize );
      this->mUseSize += iCountSize;
   }

   void Add( T& irVal )
   {
      ASSSERT(this->mUseSize<this->mSize);
      this->mpData[this->mUseSize] = irVal;
      this->mUseSize++;
   }

   void Add( const T& irVal )
   {
      ASSSERT(this->mUseSize<this->mSize);
      this->mpData[this->mUseSize] = irVal;
      this->mUseSize++;
   }

   T& operator[]( int iIndex )
   {
      ASSSERT( (iIndex < this->mUseSize) && (iIndex > -1));
      return this->mpData[iIndex];
   }
   
   const T& operator[]( int iIndex )const
   {
      ASSSERT( (iIndex < this->mUseSize) && (iIndex > -1));
      return this->mpData[iIndex];
   }

   void Reserve( int iCount )
   {
      // UseSize is used during the 
      // unallocated state to count the reservations
      ASSSERT( !this->IsSetUp() );
      this->mUseSize += iCount;
   }

   void Allocate()
   {
      ASSSERT( !this->IsSetUp() );
      if( this->mUseSize == 0 )
      {
         this->mSize = this->mUseSize;
         this->mpData = NULL;
      }
      else
      {
         this->mSize = this->mUseSize;
         this->mpData = new T[this->mSize];
         ASSSERT(this->mSize>0);
         ASSSERT(this->mpData!=NULL);
         this->mUseSize = 0;
      }
   }

   void Allocate( int iSize )
   {
      ASSSERT( this->mUseSize == 0 );
      //TODO: wha?
      if( !this->IsSetUp() )
         iSize += this->mUseSize;
      this->Clear();
      this->mSize = iSize;
      this->mpData = new T[this->mSize];
      ASSSERT(this->mSize>0);
      ASSSERT(this->mpData!=NULL);
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
   int mUseSize;
   T*  mpData;
   T   mSwapT;
   
protected:

private:
   /////////////////////////////////////////
   // Currently Disallowed Functions 
   //    -Not implemented
   //    -Not accessible
   //    -Use will error at Compile
   /////////////////////////////////////////
   SwapArray( const SwapArray& iSource );
   SwapArray& operator=( const SwapArray& iSource );

};

template <class T> class NodeSwapArray
{
public:
   
   /////////////////////////////////////////
   // Constructors/Destructors
   /////////////////////////////////////////
   ~NodeSwapArray()
   {
      Clear();
   }

   NodeSwapArray() : mUseSize(0), mpData(NULL)
   {
   }

   NodeSwapArray( int iSize ) : 
    mUseSize(0),
    mpData(NULL)
   {
      Allocate( iSize );
   }


   /////////////////////////////////////////
   // Main Methods
   /////////////////////////////////////////
   void Remove( int iIndex )
   {
      //A pointer safe swap-out
      ASSSERT( (iIndex<this->mUseSize) );
      this->mSwapT = this->mpData[iIndex]; 
      this->mpData[iIndex] = this->mpData[this->mUseSize-1];
      this->mpData[this->mUseSize-1] = this->mSwapT;
      this->mUseSize--;
   }

   void RemoveKeepOrder( int iIndex )
   {
      //A pointer safe swap-out
      ASSSERT( (iIndex<this->mUseSize) );
      this->mSwapT = this->mpData[iIndex]; 
      while(iIndex<this->mUseSize-1)
      {
          this->mpData[iIndex] = this->mpData[iIndex+1];
          iIndex++;
      }
      this->mpData[this->mUseSize-1] = this->mSwapT;
      this->mUseSize--;
   }

   void Swap( int iIndex1, int iIndex2 )
   {
      //A pointer safe swap-out
      ASSSERT( (iIndex1<this->mUseSize) && (iIndex2<this->mUseSize) );
      this->mSwapT = this->mpData[iIndex1]; 
      this->mpData[iIndex1] = this->mpData[iIndex2];
      this->mpData[iIndex2] = this->mSwapT;
   }

   void Init( int iIndex, T& irVal )
   {
      ASSSERT( (iIndex>=this->mUseSize)&&(iIndex<this->mSize) );
      this->mUseSize = iIndex+1;
      this->mpData[iIndex] = irVal;
   }

   void ClearUse()
   {
      ASSSERT(this->IsSetUp());
      this->mUseSize = 0;
   }

   void Use( int iIndex )
   {
      ASSSERT( (iIndex>=this->mUseSize)&&(iIndex<this->mSize) );
      this->mUseSize = iIndex+1;
   }

   void AddUse( int iCountSize )
   {
      ASSSERT( (iCountSize+this->mUseSize)<=this->mSize );
      this->mUseSize += iCountSize;
   }

   bool Add( T& irVal )
   {
      if(this->mUseSize>=this->mSize)
          return false;
      this->mpData[this->mUseSize] = irVal;
      this->mUseSize++;
      return true;
   }

   T& operator[]( int iIndex )
   {
      ASSSERT( (iIndex < this->mUseSize) && (iIndex > -1));
      return this->mpData[iIndex];
   }
   
   const T& operator[]( int iIndex )const
   {
      ASSSERT( (iIndex < this->mUseSize) && (iIndex > -1));
      return this->mpData[iIndex];
   }

   void Reserve( int iCount )
   {
      // UseSize is used during the 
      // unallocated state to count the reservations
      ASSSERT( !this->IsSetUp() );
      this->mUseSize += iCount;
   }

   void Allocate()
   {
      ASSSERT( !this->IsSetUp() );
      if( this->mUseSize == 0 )
      {
         this->mSize = this->mUseSize;
         this->mpData = NULL;
      }
      else
      {
         this->mSize = this->mUseSize;
         this->mpData = new T[this->mSize];
         ASSSERT(this->mSize>0);
         ASSSERT(this->mpData!=NULL);
         this->mUseSize = 0;
      }
   }

   void Allocate( int iSize )
   {
      ASSSERT( this->mUseSize == 0 );
      //TODO: wha?
      if( !this->IsSetUp() )
         iSize += this->mUseSize;
      this->Clear();
      this->mSize = iSize;
      this->mpData = new T[this->mSize];
      ASSSERT(this->mSize>0);
      ASSSERT(this->mpData!=NULL);
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
   int mUseSize;
   T*  mpData;
   T   mSwapT;
   
protected:

private:
   /////////////////////////////////////////
   // Currently Disallowed Functions 
   //    -Not implemented
   //    -Not accessible
   //    -Use will error at Compile
   /////////////////////////////////////////
   NodeSwapArray( const NodeSwapArray& iSource );
   NodeSwapArray& operator=( const NodeSwapArray& iSource );

};
#endif