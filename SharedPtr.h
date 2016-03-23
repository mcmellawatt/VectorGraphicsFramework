#if !defined(CST_SHARED_PTR_H_ALREADY_INCLUDED)
#define CST_SHARED_PTR_H_ALREADY_INCLUDED

//
//  Description: This is a reference counted smart pointer class.  The class
//               encasulates a raw pointer to any scalar type and is responsible
//               for memory deallocation when all objects that share the raw
//               pointer go out of scope.  This class was designed to use with 
//               STL based containers and algorithms.  This class will not work
//               properly if the raw pointer points to an array. It is an error
//               to use the same raw pointer to initialize two different shared
//               pointer classes. The proper way to use the class is to encapsulate
//               the raw pointer in the class via the constructor and then perform
//               any copying or assigment on the encapsulated class.  A typical
//               usage might look like the following:
//
//               std::vector< SharedPtr<SomeClass> > someVector;
//
//               for (idx = 0; idx < 20; ++idx)
//               {
//                   someVector.push_back(SharedPtr<SomeClass>(new SomeClass(...));
//               } 
//

#include <stdexcept>

namespace Cst
{

template <typename T> class SharedPtr
{
public:
    // Initialize the class with a raw pointer
    explicit SharedPtr(T* ptr=0)
        : myDataP(ptr)
    {
        try
        {
            myRefCountP = new unsigned long(1L);
        }
        catch (...)
        {
            delete myDataP;
            throw;
        }
    }

    // Copying shares the internal pointer and bumps the reference count
    SharedPtr(const SharedPtr< T >& ptr) throw() 
        : myRefCountP(ptr.myRefCountP), myDataP(ptr.myDataP)
    {
        ++(*myRefCountP);
    }

    ~SharedPtr() throw()
    {
        conditionalDtor();
    }

    unsigned long count() const
    {
        return *myRefCountP;
    }

    SharedPtr< T >& operator=(const SharedPtr< T >& rhs) throw()
    {
       if (myRefCountP != rhs.myRefCountP)
        {
            ++(*rhs.myRefCountP);
            conditionalDtor();
            myRefCountP = rhs.myRefCountP;
            myDataP = rhs.myDataP;
        }
        
        return *this;
    }

    void reset(T* ptr=0)
    {
        if (myDataP != ptr)
        {
            if (--(*myRefCountP) != 0)
            {
                try
                {
                    myRefCountP = new unsigned long;
                }
                catch (...)
                {
                    // Restore counter to value before method call.
                    ++(*myRefCountP);
                    
                    delete ptr;
                    throw;
                }
            }
            else
            {
                delete myDataP;
            }
            myDataP      = ptr;
            *myRefCountP = 1L;
        }
    }
   
	T& operator*() const
    {

        if (myDataP == 0)
        {
			throw std::runtime_error("Attempting to dereference null pointer");
        }           

        return *myDataP;    
    }

    T* operator->() const
    { 
        if (myDataP == 0)
        {
			throw std::runtime_error("Attempting to dereference null pointer");
        }           
            
        return myDataP;
    }

    T* get() const
    {
        return myDataP;
    }

private:
    unsigned long* myRefCountP;
    T*   myDataP;

    void conditionalDtor(void)
    {
        // Check for valid count pointer
        if (myRefCountP == 0)
        {
            return;
        }

        if ((--(*myRefCountP)) == 0)
        {
            delete myDataP;
            delete myRefCountP;
        }
        
        // Make sure this SharedPtr can no longer refer to
        // the internal pointers it is being decoupled from
        myDataP = 0;
        myRefCountP = 0;
    }
};

}  // namespace Cst

#endif
