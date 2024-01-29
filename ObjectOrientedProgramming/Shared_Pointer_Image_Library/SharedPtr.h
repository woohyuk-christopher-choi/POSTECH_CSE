#ifndef SHAREDPTR_H
#define SHAREDPTR_H

#include <iostream>
#include <cassert>

template<typename ObjectType>
void Deallocator(ObjectType* ptr)
{
    std::cout << "Dealloc Object" << std::endl;
    delete ptr;
}

template<typename ObjectType>
void ArrayDeallocator(ObjectType* ptr)
{
    std::cout << "Dealloc Array" << std::endl;
    delete[] ptr;
}

template<typename T>
using DeallocatorFuncType = void (T*);

// SharedPtr
template<typename ObjectType, DeallocatorFuncType<ObjectType> Dealloc = Deallocator<ObjectType> >
class SharedPtr
{
private:
    ObjectType* m_object;
    int* m_ref_counter;

    // ======= ADD CODE HERE IF NEEDED =========
                
public:
    ////////////////////////////////////////////
    // Constructors & destructor
    
    ////////////////////////////////////////////
    
    // ======= ADD CODE HERE IF NEEDED =========
    SharedPtr() : m_object(nullptr), m_ref_counter(nullptr) {}

    SharedPtr(ObjectType* object) : m_object(object), m_ref_counter(new int(1)) { }

    SharedPtr(const SharedPtr& other) : m_object(other.m_object), m_ref_counter(other.m_ref_counter)
    {
        ++(*m_ref_counter);
    }

    // Destructor
    ~SharedPtr(){
        if (m_ref_counter && --(*m_ref_counter) == 0)
      {
         Dealloc(m_object); // Use Dealloc instead of delete
         delete m_ref_counter;
         m_object = nullptr;
         m_ref_counter = nullptr;
      }
    }
    ////////////////////////////////////////////
    // Assignment operator

    
    SharedPtr& operator=(const SharedPtr& other){
        if (this != &other){
            // Decrease the current reference counter
            if (m_ref_counter && --(*m_ref_counter) == 0)
            {
                Dealloc(m_object); // Use Dealloc instead of delete
                delete m_ref_counter;
                m_object = nullptr;
                m_ref_counter = nullptr;
            }

            m_object = other.m_object;
            m_ref_counter = other.m_ref_counter;
            ++(*m_ref_counter);
        }
        return *this;
    }

    

    ////////////////////////////////////////////
    
    // ======= ADD CODE HERE IF NEEDED =========
    
    ////////////////////////////////////////////
    // Pointer operators
    ////////////////////////////////////////////
    // operator->
    ObjectType* operator->()
    {
        assert(m_object != nullptr);
        return m_object;
    }

    const ObjectType* operator->() const
    {
        assert(m_object != nullptr);
        return m_object;
    }

    // operator*
    ObjectType& operator*(){
        assert(m_object != nullptr);
        return *m_object;
    }

    const ObjectType& operator*() const{
        assert(m_object != nullptr);
        return *m_object;
    }

    // operator ObjectType*()

    operator ObjectType*()
    {
        return m_object;
    }

    operator const ObjectType*() const
    {
        return m_object;
    }

    // ======= ADD CODE HERE IF NEEDED =========
    
    ////////////////////////////////////////////
    // Array element access operators
    ////////////////////////////////////////////
    // operator[]
    ObjectType& operator[](size_t index){
        assert(m_object != nullptr);
        return m_object[index];
    }

    const ObjectType& operator[](size_t index) const{
        assert(m_object != nullptr);
        return m_object[index];
    }
    
    // ======= ADD CODE HERE IF NEEDED =========

    ////////////////////////////////////////////
    // Array element access operators
    ////////////////////////////////////////////
    // operator[]
    
    ////////////////////////////////////////////
    // Type casting operators
    ////////////////////////////////////////////
    // operator ObjectType const*() const
    // operator ObjectType*()
    
    // ======= ADD CODE HERE IF NEEDED =========
    ObjectType* get()
    {
        return m_object;
    }

    const ObjectType* get() const
    {
        return m_object;
    }
};

template<typename T>
using SharedArray = SharedPtr<T, ArrayDeallocator<T> >;

#endif