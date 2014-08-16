/*=======================================================================*
  Copyright (C) 2009-2011 William Andrew Burnson, Rick Taube.  This
  program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License available at
  http://www.gnu.org/licenses/gpl.html
 *=======================================================================*/

#ifndef menc_Array_h
#define menc_Array_h

//For placement new, memset, and memcpy.
#include <new>
#include <string>

namespace menc
{
  /**A smart array with exponential (base-two) element creation. Since
  reallocations only occur at the base-two increments (1 unit, 2 units,
  4 units, 8 units, etc.) very little time is spent overall doing memory
  copies.*/
  template <class T>
  class Array
  {
    /**A wrapper for clearing and copying memory via templated methods. You should
    only use these methods on plain-old data objects, that is, objects not
    containing members with their own special constructors or containing virtual
    methods (and thus a vtable which would be wiped out).*/
    class Memory
    {
      ///Private wrapper for memset. Use Clear instead since it is strongly typed.
      static void MemSet(void* Destination, unsigned char ValueToSet,
        int BytesToSet)
      {
        if(Destination != 0 && BytesToSet > 0)
          memset(Destination, ValueToSet, BytesToSet);
      }

      ///Private wrapper for memcpy. Use Copy instead since it is strongly typed.
      static void MemCopy(void* Destination, void* Source,
        int BytesToCopy)
      {
        if(Destination != 0 && Source != 0 && BytesToCopy > 0)
          memcpy(Destination, Source, BytesToCopy);
      }

    public:
    
      ///Clears an object with a particular byte-value.
      template <class Type>
      static void Clear(Type& Object, unsigned char Value = 0)
      {
        MemSet((void*)&Object, Value, sizeof(Type));
      }

      ///Clears an array of consecutive objects with a particular byte-value.
      template <class Type>
      static void Clear(Type* Object, int Items, unsigned char Value = 0)
      {
        MemSet((void*)Object, Value, sizeof(Type) * Items);
      }

      ///Copies an object's data to another object.
      template <class Type>
      static void Copy(Type& Destination, const Type& Source)
      {
        MemCopy((void*)&Destination, (void*)&Source, sizeof(Type));
      }

      ///Copies an array of consecutive objects to another array.
      template <class Type>
      static void Copy(Type* Destination, const Type* Source, int Items)
      {
        MemCopy((void*)Destination, (void*)Source, sizeof(Type) * Items);
      }

      /**Calls a placement new on an object. A placement new is used to call an
      object's constructor in the case that the memory for the object has already
      been allocated.*/
      template <class Type>
      static Type* PlacementNew(Type* Object)
      {
        return new (Object) Type;
      }
    };
    
    //------------//
    //Data Members//
    //------------//
    void* Data;
    
    int LogicalSize;

    static int calculatePhysicalSizeFromLogical(int Logical)
    {
      //Return 0 if bad argument.
      if(Logical < 0)
        return 0;

      //If 1 or 2, then Physical = Logical
      if(Logical <= 2)
        return Logical;

      /*If 3 or higher calculate the physical size by finding the least power of
      two greater than the logical size.*/
      int Physical = 2;
      do
      {
        Physical *= 2;
        if(Logical <= Physical)
          return Physical;
      }
      while(Physical > 0 &&
        (unsigned long)Physical < 0x80000000UL);

      //Overflow returns zero.
      return 0;
    }

  public:
    ///Returns the size of the array.
    inline int n(void) const
    {
      return LogicalSize;
    }
    
    ///Returns the size of the array.
    inline int size(void) const
    {
      return LogicalSize;
    }

    ///Sets the size of the array.
    T* n(int NewLogicalSize)
    {
      //In case the new requested size is the same, quickly return.
      if(NewLogicalSize == LogicalSize)
        return (T*)Data;
      
      //In the case of a no size array, just delete all the data.
      if(NewLogicalSize <= 0)
      {
        //Call all the destructors.
        for(int i = 0; i < LogicalSize; i++)
          ((T*)Data)[i].~T();
        delete [] (unsigned char*)Data;
        Data = 0;
        LogicalSize = 0;
        return 0;
      }

      /*Since this class uses an exponential expansion model, the size will only
      increase at powers of two. This means in exchange for using up a little
      more memory, there are much fewer actual allocations.*/
      int OldPhysicalSize = calculatePhysicalSizeFromLogical(LogicalSize);
      int NewPhysicalSize = calculatePhysicalSizeFromLogical(NewLogicalSize);

      /*If no extra data needs to be allocated, then just change the size of the
      array.*/
      if(OldPhysicalSize == NewPhysicalSize)
      {
        //Zero out any previously uninitialized elements.
        if(NewLogicalSize > LogicalSize)
        {
          Memory::Clear(&((T*)Data)[LogicalSize], NewLogicalSize - LogicalSize);

          //Call the constructors of the new objects.
          for(int i = LogicalSize; i < NewLogicalSize; i++)
            Memory::PlacementNew(&((T*)Data)[i]);
        }
        else //Assume that NewLogicalSize is less than LogicalSize.
        {
          //Call the destructors for the objects that are being removed.
          for(int i = NewLogicalSize; i < LogicalSize; i++)
            ((T*)Data)[i].~T();
        }
        
        //Set the new size of the array.
        LogicalSize = NewLogicalSize;
        return (T*)Data;
      }

      //Allocate a new contiguous block of memory.
      void* NewData = (void*)new unsigned char[sizeof(T) * NewPhysicalSize];

      //If memory could not be allocated, return zero.
      if(!NewData)
        return 0;

      //Test to see if the array is getting bigger or smaller.
      if(NewLogicalSize > LogicalSize)
      {
        //Copy original data and zero out the new portion.
        Memory::Copy((T*)NewData, (T*)Data, LogicalSize);
        Memory::Clear(&((T*)NewData)[LogicalSize], 0,
          NewLogicalSize - LogicalSize);
        for(int i = LogicalSize; i < NewLogicalSize; i++)
          Memory::PlacementNew(&((T*)NewData)[i]);
      }
      else //Assume that NewLogicalSize is less than LogicalSize.
      {
        //Call the destructors of the objects being removed.
        for(int i = NewLogicalSize; i < LogicalSize; i++)
          ((T*)Data)[i].~T();

        //Copy data into a smaller array.
        Memory::Copy((T*)NewData, (T*)Data, NewLogicalSize);
      }

      //Delete old array.
      delete [] (unsigned char*)Data;

      //Set the new size of the array.
      LogicalSize = NewLogicalSize;

      //Return pointer to the new data array.
      return (T*)(Data = NewData);
    }

    ///Clears the array.
    inline void clear(void)
    {
      n(0);
    }
    
    /**Returns the first element of the array. Note that 'first' is lowercase
    since it is treated as a mathematical variable.*/
    inline T& first(void)
    {
      return *((T*)Data);
    }
    
    /**Returns the last element of the array. Note that 'last' is lowercase
    since it is treated as a mathematical variable.*/
    inline T& last(void)
    {
      return ((T*)Data)[LogicalSize - 1];
    }

    /** Returns the first element in the array or 0 if the array is empty. **/

    T getFirst()
    {
      if (!size())
        return T();
      return *((T*)Data);
    }
    
    /** Returns the last element in the array or 0 if array is empty. **/

    T getLast()
    {
      if (!size())
        return T();
      return ((T*)Data)[LogicalSize - 1];
    }

    /** Returns true if the array contains element otherwise false. **/

    bool contains(const T& element)
    {
      for (int i=0; i<size(); i++)
        if (((T*)Data)[i] == element)
        return true;
      return false;
    }

    /** Returns the index of element in the array or -1 if it isn't found. **/

    int indexOf(const T& element)
    {
      for (int i=0; i<size(); i++)
        if (((T*)Data)[i] == element)
        return i;
      return -1;
    }

    ///Adds an element to the end of the array using a copy constructor.
    void add(const T& NewElement)
    {
      n(LogicalSize + 1);
      ((T*)Data)[LogicalSize - 1] = NewElement;
    }

    /** Replaces an element with a new value. If the index is less
        than zero, this method does nothing. If the index is beyond
        the end of the array, the item is added to the end of the
        array. **/


    void set(const int index, const T& element)
    {
      if (index >= 0)
        {
          if (index < size())
            ((T*)Data)[index] = element;
          else
            add(element);
        }
    }

    ///Adds an element to the array and returns a reference to that element.
    T& add(void)
    {
      n(LogicalSize + 1);
      return last();
    }

    /** Inserts a new element into the array at a given position. If
        the index is less than 0 or greater than the size of the
        array, the element will be added to the end of the
        array. Otherwise, it will be inserted into the array, moving
        all the later elements along to make room. **/

    void insert(int indexToInsertAt, const T& newElement)
    {
      if ((indexToInsertAt < 0) || (indexToInsertAt >= size()))
        add(newElement);
      else
        {
          n(LogicalSize + 1);
          for (int i= size()-2; i >= indexToInsertAt; i--)
            ((T*)Data)[i+1] = ((T*)Data)[i];
          ((T*)Data)[indexToInsertAt] = newElement;
        }
    }
    /** Appends a new element to the end of the array if the array
        doesn't already contain it, otherwise nothing will be
        done. **/

    void addIfNotAlreadyThere(const T& newElement)
    {
      if (!contains(newElement))
        add(newElement);
    }

    /** Removes the element from the array and shifts all the
        subsequent elements backwards to close the gap. If the index
        passed in is out-of-range, nothing will happen. **/

    void remove(int index)
    {
      if (index >= 0 && index < size())
        {
          for (int i= index+1; i < size(); i++)
            ((T*)Data)[i-1] = ((T*)Data)[i];
          n(LogicalSize - 1);
        }
    }

    /** Removes the element from the array and shifts all the
        subsequent elements backwards to close the gap. If the element
        is not in the array, nothing will happen. **/

    void removeElement(const T& element)
    {
      remove(indexOf(element));
    }
   
    /** Returns an element by index. The method does not check bounds
    before attempting to access the data. The element itself has
    read-write access. **/


    inline T& operator[] (int Index) const
    {
      return ((T*)Data)[Index];
    }

    /**Returns an element by index. The method does not check bounds before
    attempting to access the data. */
    inline T& getUnchecked(int Index) const
    {
      return ((T*)Data)[Index];
    }


    /**Returns an element by index. The method does not check bounds before
    attempting to access the data. The element itself has read-write access.*/
    inline T& getItem(int Index) const
    {
      return ((T*)Data)[Index];
    }

    /**Returns an element read-only by index. The method does not check bounds
    before attempting to access the data.*/
    inline const T& getConstItem(int Index) const
    {
      return (const T&)(((T*)Data)[Index]);
    }
    
    /**Returns the value of an element given its index. Changing the value does
    not change the array since the value returned is a copy.*/
    inline T getItemValue(int Index) const
    {
      return ((T*)Data)[Index];
    }

    /** Reverses the order of the elements in the array. **/

    void reverse()
    {
     for (int i = 0; i < size() / 2; i++)
      {
        int j = (size() - 1 ) - i;
        T x=getItem(i);
        getItem(i)=getItem(j);
        getItem(j)=x;
      }
    }


    ///Creates an array with no elements.
    Array() : Data(0), LogicalSize(0) {}

    ///Constructs the array with the given number of elements.
    Array(int Size) : Data(0), LogicalSize(0) {n(Size);}

    /**Copys another array into this one. First the array is resized to have the
    same number of elements as the other. Then each element from the other is
    copied by assignment. Note that the resizing step will cause constructors
    to be called, which may be inefficient. If your array contains plain-old
    data then you are better off using the CopyMemoryFrom() method.*/
    void copyFrom(const Array<T>& Other)
    {
      //If the source and destination are the same, no copying is necessary.
      if(&Other == this)
        return;
      
      //Resize the array to be the size of the other.
      n(Other.LogicalSize);
      
      //Copy each element by assignment.
      for(int i = 0; i < LogicalSize; i++)
        ((T*)Data)[i] = ((T*)Other.Data)[i];
    }
    
    /** Adds elements from an array to the end of this array. **/
    void addArray(const Array<T>& other)
    {
      int pos=size();
      n(LogicalSize+other.size());
      for (int i = 0; i < other.size(); i++)
        ((T*)Data)[pos+i] = ((T*)other.Data)[i];
    }

    /**Copies the memory of another array into this one. First the array is
    resized to have the same number of elements. Then a memory copy operation is
    done on the array to copy the contents of the other array byte-for-byte into
    this one. Note well, in order for this to be valid, the elements must be
    plain-old data, i.e., they must not contain members with special
    constructors and must not contain virtual methods. Use the CopyFrom() method
    for complex objects so that they will be properly copied using the
    assignment operator.*/
    void copyMemoryFrom(const Array<T>& Other)
    {
      //If the source and destination are the same, no copying is necessary.
      if(&Other == this)
        return;
      
      //Resize the array to be the size of the other.
      n(Other.LogicalSize);
      
      //Copy the entire array as plain-old data.
      Memory::Copy(first(), Other.first(), n()); 
    }

    /**Safe copy constructor. Internally calls the CopyFrom() method. Normally
    you would want to use references to the Array (when possible) so that its
    contents are not needlessly copied. You could also use CopyMemoryFrom() if
    your element is plain-old data.*/
    Array(const Array<T> &Other) : Data(0), LogicalSize(0) {CopyFrom(Other);}
    
    /**Memory-based copy constructor from array data. This method will only
    call the constructors of the newly created elements. Then it performs a
    memory copy from the source array. If your source is already an Array, then
    you would normally pass in the Array object so that the assignment operators
    will be used. You should only use this copy constructor if your elements are
    plain-old data.*/
    Array(const T* OtherData, int Length) : Data(0), LogicalSize(0)
    {
      //Resize the array.
      n(Length);
      
      //If the source and destination are the same, no copying is necessary.
      if((T*)Data == OtherData)
        return;
      
      //Copy the entire array as plain-old data.
      Memory::Copy((T*)Data, OtherData, Length);
    }

    ///Assignment operator to safely copy another array to this one.
    Array<T>& operator = (const Array<T>& Other)
    {
      copyFrom(Other);
      return *this;
    }

    ///Destroys the array, calling each of the items' destructors.
    virtual ~Array() {n(0);}
    
    private:
    
    ///Private helper that implements Quicksort recursion.
    static void quicksortRecursive(T* ArrayData, int Left, int Right)
    {
      int Pivot, LeftIndex = Left, RightIndex = Right;
      if(Right - Left <= 0)
        return;
      Pivot = (Left + Right) / 2;
      while(LeftIndex <= Pivot && RightIndex >= Pivot)
      {    
        while(ArrayData[LeftIndex] < ArrayData[Pivot] && LeftIndex <= Pivot)
          LeftIndex = LeftIndex + 1;
        
        while(ArrayData[RightIndex] > ArrayData[Pivot] && RightIndex >= Pivot)
             RightIndex = RightIndex - 1;
        
        T SwapValue = ArrayData[LeftIndex];
        ArrayData[LeftIndex] = ArrayData[RightIndex];
        ArrayData[RightIndex] = SwapValue;
        LeftIndex++;
        RightIndex--;
        if(LeftIndex - 1 == Pivot)
          Pivot = RightIndex = RightIndex + 1;
        else if(RightIndex + 1 == Pivot)
          Pivot = LeftIndex = LeftIndex - 1;
      }
      quicksortRecursive(ArrayData, Left, Pivot - 1);
      quicksortRecursive(ArrayData, Pivot + 1, Right);
    }
    
    public:
    
    ///Runs the Quicksort routine.
    void quicksort(void)
    {
      quicksortRecursive((T*)Data, 0, n() - 1);
    }
    
    ///Returns whether or not the array is sorted.
    bool isSorted(void)
    {
      for(int i = 0; i < n() - 1; i++)
      {
        if(getItem(i) > getItem(i + 1))
          return false;
      }
      return true;
    }
    
    ///Determines if sorting is necessary and runs the most appropriate sort.
    void sort(void)
    {
      if(isSorted())
        return;
      
      quicksort();
    }
    
    ///Adds an element to the array and then sorts the array.
    void addSorted(const T& newElement)
    {
      add(newElement);
      sort();
    }

    ///Deletes elements and clears array.
    void clearWithDelete(void)
    {
      for(int i = 0; i < n(); i++)
        delete getItem(i);
      n(0);
    }

  };
}
#endif
