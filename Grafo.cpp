#include "Grafo.h"
#include "Cola.h"
#include "Pila.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

Grafo::Grafo(string nomArch) {
    string cad;
    arch.open(nomArch); // Abrir el archivo
    if (arch.fail()) {
        cout << "Error al abrir el archivo" << endl;
        return;  // Salir del constructor si no se pudo abrir el archivo
    }
    getline(arch, cad); // Leer la primera línea (número de nodos)
    numNodos = stoi(cad); // Convertir a entero y almacenar en numNodos
    listaNodos = new Nodo[numNodos]; // Crear arreglo dinámico de Nodos
    matAdj = new int*[numNodos]; // Crear matriz de adyacencia dinámica
    for (int i = 0; i < numNodos; i++) {
        matAdj[i] = new int[numNodos]; // Crear filas de la matriz
        for (int j = 0; j < numNodos; j++) {
            matAdj[i][j] = 0; // Inicializar todos los elementos a 0
        }
    }
}

Grafo::~Grafo() {
    // Liberar memoria de la matriz de adyacencia
    for (int i = 0; i < numNodos; i++) {
        delete[] matAdj[i];
    }
    delete[] matAdj;
    delete[] listaNodos; // Liberar memoria del arreglo de Nodos
}

void Grafo::generaListaNodos() {
    string cad;
    for (int i = 0; i < numNodos; i++) {
        getline(arch, cad); // Leer línea del archivo
        listaNodos[i].setNom(cad); // Asignar nombre del nodo
    }
}

int Grafo::buscaNodo(string nombre) {
    for (int i = 0; i < numNodos; i++) {
        if (listaNodos[i].getNom() == nombre) {
            return i; // Devolver índice si se encuentra el nodo
        }
    }
    return -1; // Devolver -1 si no se encuentra el nodo
}

void Grafo::generaMatriz() {
    string cad;
    while (getline(arch, cad)) { // Leer líneas restantes del archivo
        if (cad.empty()) continue; // Saltar líneas vacías
        int pos1 = cad.find('*'); // Encontrar primera ocurrencia de '*'
        int pos2 = cad.find('*', pos1 + 1); // Encontrar segunda ocurrencia de '*'
        string origen = cad.substr(0, pos1); // Extraer nombre del nodo origen
        string destino = cad.substr(pos1 + 1, pos2 - pos1 - 1); // Extraer nombre del nodo destino
        int peso = stoi(cad.substr(pos2 + 1)); // Extraer peso de la arista
        int posOrigen = buscaNodo(origen); // Obtener índice del nodo origen
        int posDestino = buscaNodo(destino); // Obtener índice del nodo destino
        if (posOrigen != -1 && posDestino != -1) { // Si ambos nodos existen
            matAdj[posOrigen][posDestino] = peso; // Asignar peso en la matriz de adyacencia
            matAdj[posDestino][posOrigen] = peso; // Para grafo no dirigido
        }
    }
    muestraMatriz(); // Mostrar la matriz de adyacencia
}

void Grafo::muestraListaNodos() {
    cout << "Lista de vertices del grafo" << endl;
    for (int i = 0; i < numNodos; i++) {
        cout << listaNodos[i].getNom() << endl; // Imprimir nombre de cada nodo
    }
}

void Grafo::muestraMatriz() {
    cout << "Matriz de Adyacencia:" << endl;
    for (int i = 0; i < numNodos; i++) {
        for (int j = 0; j < numNodos; j++) {
            cout << matAdj[i][j] << " "; // Imprimir elemento de la matriz
        }
        cout << endl; // Nueva línea después de cada fila
    }
}

void Grafo::busquedaAnchura() {
    int inicio = 0; // Índice del nodo de inicio
    int fin = numNodos - 1; // Índice del nodo de fin

    int* padre = new int[numNodos]; // Arreglo para almacenar nodos padres
    int* pesosCamino = new int[numNodos]; // Arreglo para almacenar pesos de las aristas en el camino

    // Inicializar todos los nodos como no visitados
    for (int i = 0; i < numNodos; ++i) {
        listaNodos[i].setVisitado(false);
        padre[i] = -1; // -1 indica nodo sin padre
        pesosCamino[i] = 0; // Inicializar pesos de las aristas en 0
    }

    Cola cola; // Crear cola vacía

    cola.enqueue(listaNodos[inicio].getNom()); // Encolar nodo de inicio
    listaNodos[inicio].setVisitado(true); // Marcar nodo de inicio como visitado

    bool caminoEncontrado = false; // Bandera para indicar si se encontró un camino

    while (!cola.isEmpty()) { // Mientras la cola no esté vacía
        string nodoActual = cola.dequeue(); // Desencolar nodo
        int nodo = buscaNodo(nodoActual); // Obtener índice del nodo actual

        cout << "Visitando nodo: " << nodoActual << endl; // Imprimir nodo visitado

        if (nodo == fin && !caminoEncontrado) { // Si se encuentra el nodo final
            caminoEncontrado = true; // Marcar bandera
        }

        // Iterar sobre todos los nodos posibles
        for (int i = 0; i < numNodos; ++i) {
            int pesoArista = matAdj[nodo][i]; // Peso de la arista entre el nodo actual y el nodo i

            bool visitado = listaNodos[i].getVisitado(); // Estado de visitado del nodo i

            // Verificar si hay una arista entre el nodo actual y el nodo i, y si el nodo i no ha sido visitado
            if (pesoArista != 0 && !visitado) {
                // Encolar el nodo vecino i
                cola.enqueue(listaNodos[i].getNom());
                // Marcar el nodo vecino i como visitado
                listaNodos[i].setVisitado(true);
                // Registrar que el nodo actual es el padre del nodo vecino i
                padre[i] = nodo;
                // Actualizar el peso del camino para el nodo vecino i
                pesosCamino[i] = pesosCamino[nodo] + pesoArista;
            }
        }
    }

    if (caminoEncontrado) { // Si se encontró un camino
        cout << "Camino encontrado (Busqueda por Anchura): ";
        int pesoTotalCamino = pesosCamino[fin]; // Obtener el peso total del camino
        imprimirCamino(padre, inicio, fin); // Imprimir camino
        cout << endl;
        cout << "Peso total del camino: " << pesoTotalCamino << endl; // Imprimir peso total del camino
    } else {
        cout << "No se encontró camino." << endl; // Si no se encontró camino
    }

    delete[] padre; // Liberar memoria del arreglo padre
    delete[] pesosCamino; // Liberar memoria del arreglo pesosCamino
}


void Grafo::busquedaProfundidad() {
    int inicio = 0; // Índice del nodo de inicio
    int fin = numNodos - 1; // Índice del nodo de fin
    int* padre = new int[numNodos]; // Arreglo para almacenar nodos padres
    int* pesosCamino = new int[numNodos]; // Arreglo para almacenar pesos de las aristas en el camino

    // Inicializar todos los nodos como no visitados
    for (int i = 0; i < numNodos; ++i) {
        listaNodos[i].setVisitado(false);
        padre[i] = -1; // -1 indica nodo sin padre
        pesosCamino[i] = 0; // Inicializar pesos de las aristas en 0
    }

    Pila pila; // Crear pila vacía
    pila.push(listaNodos[inicio].getNom()); // Agregar el nodo de inicio a la pila
    listaNodos[inicio].setVisitado(true); // Marcar el nodo inicial como visitado

    bool caminoEncontrado = false; // Bandera para indicar si se encontró un camino

    while (!pila.isEmpty()) { // Mientras la pila no esté vacía
        string nodoActual = pila.pop(); // Sacar un nodo de la pila
        int nodo = buscaNodo(nodoActual); // Obtener índice del nodo actual
        cout << "Visitando nodo: " << nodoActual << endl; // Imprimir nodo visitado

        if (nodo == fin && !caminoEncontrado) { // Si se encuentra el nodo final
            caminoEncontrado = true; // Marcar bandera
        }

        // Iterar sobre todos los nodos vecinos en orden ascendente
        for (int i = 0; i < numNodos; ++i) {
            if (matAdj[nodo][i] != 0 && !listaNodos[i].getVisitado()) { // Si hay arista y el nodo no ha sido visitado
                pila.push(listaNodos[i].getNom()); // Agregar nodo vecino a la pila
                listaNodos[i].setVisitado(true); // Marcar nodo vecino como visitado
                padre[i] = nodo; // Asignar nodo actual como padre del nodo vecino
                pesosCamino[i] = pesosCamino[nodo] + 1; // Actualizar el peso del camino para el nodo vecino i
            }
        }
    }

    if (caminoEncontrado) { // Si se encontró un camino
        cout << "Camino encontrado (Busqueda por Profundidad): ";
        int pesoTotalCamino = pesosCamino[fin]; // Obtener el peso total del camino
        imprimirCamino(padre, inicio, fin); // Imprimir camino
        cout << endl;
        cout << "Peso total del camino: " << pesoTotalCamino << endl; // Imprimir peso total del camino
    } else {
        cout << "No se encontró camino." << endl; // Si no se encontró camino
    }

    delete[] padre; // Liberar memoria del arreglo padre
    delete[] pesosCamino; // Liberar memoria del arreglo pesosCamino
}

void Grafo::imprimirCamino(int* padre, int inicio, int fin) {
    if (fin == -1) { // Si se llega al nodo inicial (fin == -1)
        return; // Salir de la recursión
    }

    imprimirCamino(padre, inicio, padre[fin]); // Llamada recursiva con el nodo padre
    cout << listaNodos[fin].getNom() << " "; // Imprimir el nombre del nodo actual
}
