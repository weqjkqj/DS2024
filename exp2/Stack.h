#include "C:\Users\81202\Desktop\DS2024-main\exp2\Stack.h"


template<typename T> class Stack:public Vector<T>{
    public:
        Stack( int c =DEFAULT_CAPACITY):Vector<T>(c){}
        Stack(T* A,Rank lo ,Rank hi):Vector<T>(A,lo,hi){}
        Stack(T* A, Rank n ):Vector<T>(A,n){}
        Stack(Vector<T> const& V,Rank lo,Rank hi):Vector<T>(V,lo,hi){}
        Stack(Vector<T> const& V):Vector<T>(V){}
        ~Stack(){}
        void push(T const& e){ this->insert(this->size(),e);}
        T pop(){return this->remove(int(this->size())-1);}
        T& top() { return (*this)[this->size()-1];}
};


