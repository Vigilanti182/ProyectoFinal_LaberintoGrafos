#ifndef COLA_H
#define COLA_H
#include "Nodo.h"

using namespace std;

class Cola
{
    Nodo* primero;
	Nodo* ultimo;

	public:
    Cola();
    ~Cola();  // Destructor para limpiar la memoria
    void enqueue(string s);
    string dequeue();
    string first();
    bool isEmpty();  // Método para verificar si la cola está vacía

};

#endif // COLA_H