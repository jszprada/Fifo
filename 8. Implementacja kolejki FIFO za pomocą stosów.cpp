#include <iostream>
#include <cassert>
#include <string>

using namespace std;

template <class T> class Link;
template <class T> class Lista;
// ======================================================================
//                            Klasa -> Fifo
// ======================================================================
template <class T>
class Fifo{
    public:
        Lista <T> ALifo;
        Lista <T> BLifo;
        Fifo(){}
        ~Fifo(){}
        void dodaj(T value);
        void usunPierwszy();
        T* pierwszyElement();
        void zAdoB();
};
// ======================================================================
//                             Fifo -> dodaj
// ======================================================================
template <class T> void Fifo<T>::dodaj(T value){
    ALifo.dodaj(value);
}
// ======================================================================
//                             Fifo -> usunPierwszy
// ======================================================================
template <class T> void Fifo<T>::usunPierwszy(){
    if(BLifo.pierwszyElement() != nullptr){
        BLifo.usunPierwszy();  
        return;
    } 
    if(ALifo.pierwszyElement() != nullptr){
        zAdoB();
        usunPierwszy();
    }
    return;
}
// ======================================================================
//                             Fifo -> pierwszyElement
// ======================================================================
template <class T> T* Fifo<T>::pierwszyElement(){
    return BLifo.pierwszyElement();
}
// ======================================================================
//                             Fifo -> zAdoB
// ======================================================================
template <class T> void Fifo<T>::zAdoB(){
    while(ALifo.pierwszyElement() != nullptr){
        BLifo.dodaj(ALifo.pierwszyElement()->value);
        ALifo.usunPierwszy();
    }
}
// ======================================================================
//                            operatro<<
// ======================================================================
template <class T> ostream& operator<<(ostream& w, const Lista<T> &mylista){
    if(mylista.first == nullptr) return w<<"";
    Link <T> *pointer = mylista.first;
    Lista<T> x;
    do{
        x.dodaj(pointer->value);
        pointer = pointer->next;
    }while(pointer);
    pointer = x.first;
    do{
        w<<pointer->value<<" ";
        pointer = pointer->next;
    }while(pointer);
    return w;
}
// ======================================================================
//                    Template Class lista
// ======================================================================
template <class T>
class Lista {
protected:
    Link <T> *first;                // data field
    
public:
    Lista() : first(nullptr) {}      // default constructor
    virtual ~Lista() {};                // destructor
    virtual void dodaj(T value);      // insert a new item
    virtual void usunPierwszy();
    Link<T>* pierwszyElement();        // access the first item
    
    template <class W> friend ostream& operator<<(ostream& w, const Lista<W> &mylista);
};
// ======================================================================
//                    Template Class link
// ======================================================================
template <class T>
class Link {
private:
    T value;
    Link <T> *next;
    Link(T val, Link *pointer) : value(val), next(pointer) { }
    
public:
    friend class Lista <T>;
    friend class Fifo <T>;
    template <class W> friend ostream& operator<<(ostream& w, const Lista<W> &mylista);
};
// ======================================================================
//                    Template Class list - attributes
// ======================================================================
template <class T> void Lista <T> ::dodaj(T value)
{
    first = new Link <T>(value, first);
}
template <class T> Link<T>* Lista <T> ::pierwszyElement() 
{
    if(first == nullptr) return nullptr;
    return first;
    assert(first != nullptr);
}
template <class T> void Lista <T> ::usunPierwszy() {
    assert(first != nullptr);
    Link <T> *pointer = first;  // save pointer to the first item
    first = pointer->next;      // reassign the first node
    delete pointer;
}
// ======================================================================
//                            main
// ======================================================================
int main()
{
Fifo <int> myFifo;
    int k;
    cin>>k;
    int licba;
for(int i = 0; i < k ; i++){
        cin>>licba;
        myFifo.dodaj(licba);
}
    myFifo.zAdoB();
    int l;
    cin>>l;
for(int i = 0; i < l; i++){
        myFifo.usunPierwszy();   
}
    int m;
    cin>>m;
for(int i = 0; i < m; i++){
        cin>>licba;
        myFifo.dodaj(licba);
}
    int n;
    cin>>n;
for(int i = 0; i < n; i++){
        myFifo.usunPierwszy();
}
    cout<<myFifo.ALifo;
    cout<<myFifo.BLifo;
return 1;
}