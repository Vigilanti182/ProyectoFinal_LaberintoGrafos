#ifndef NODO_H
#define NODO_H
#include<string>

using namespace std;

class Nodo{
    string nom;
    Nodo* sig;  // Agregamos un puntero al siguiente nodo
    bool visitado;
    //boolean visitado

    public:
        /**Para el grafo*/
        Nodo ();
        Nodo(string Nom);
        string getNom();
        void setNom(string s);
        Nodo* getSig();  // Getter para el puntero sig
        void setSig(Nodo* s);  // Setter para el puntero sig
        bool getVisitado();
        void setVisitado(bool v);

};


#endif // NODO_H