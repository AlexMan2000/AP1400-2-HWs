#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template <typename T> 
class UniquePtr {
    public:
        // Default Constructor, initialize to nullptr
        explicit UniquePtr() {
            this -> _p = nullptr;
        }


        // Fill Constructor, support UniquePtr<int> ptr{new int{10}};
        explicit UniquePtr(T* addr) {
            this -> _p = elem;
        }


        // Copy Constructor
        /*
            Copy Constructor As you already know you cannot copy a UniquePtr
            , make arrangements so the following code would cause a compile error.
        */
        // using keyword delete, we make sure that once
        // the client write UniquePtr<int> uptr1 = uptr2;
        // there will be a compile time error.
        UniquePtr(const UniquePtr& upt) = delete;

        // Copy Assignment
        /*
            Copy Constructor As you already know you cannot copy a UniquePtr
            , make arrangements so the following code would cause a compile error.
        */
        void operator=(const UniquePtr& uptr) = delete;


        // Dereference Operator, must be const
        T& operator* () const {
            // Return the reference to the resource that is managed
            return *(this -> _p);
        }


        // Pointer operator, must be const
        T* operator-> () const {
            // Return pointer to the resource that is managed
            return this -> _p;
        }


        // get raw pointer, same as deference, but preferred in modern C++
        T* get() {
            return this -> _p;
        }


        // Free up the resources, same as desructor, but preferred in modern C++
        void reset() {
            delete this -> _p;
            this -> _p = nullptr;
        }


        // Parametrized Version, take a pointer
        void reset() {

        }


        // Destructor
        ~UniquePtr() {
            delete this -> _p;
            this -> _p = nullptr;
        }

    private:
        // Resource that is managed by the smart pointer
        T* _p;
}

// Factory pattern, preferred over new keyword.
template <typename T> 
T* make_unique(T elem) {
    return new UniquePtr<T>(elem);
}






#endif //UNIQUE_PTR