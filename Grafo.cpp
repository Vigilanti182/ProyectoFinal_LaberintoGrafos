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
    int inicio = 0; // Índice del nodo de inicio (N1)
    int fin = numNodos - 1; // Índice del nodo de fin (N41)

    int* padre = new int[numNodos]; // Arreglo para almacenar nodos padres. Esto ayudará a reconstruir el camino.
    int* pesosCamino = new int[numNodos]; // Arreglo para almacenar pesos de las aristas en el camino.

    // Inicializar todos los nodos como no visitados
    for (int i = 0; i < numNodos; ++i) {
        listaNodos[i].setVisitado(false); // Marcar el nodo como no visitado.
        padre[i] = -1; // -1 indica que el nodo no tiene padre.
        pesosCamino[i] = 0; // Inicializar pesos de las aristas en 0.
    }

    Cola cola; // Crear cola vacía para la BFS.

    cola.enqueue(listaNodos[inicio].getNom()); // Encolar el nombre del nodo de inicio.
    listaNodos[inicio].setVisitado(true); // Marcar el nodo de inicio como visitado.

    bool caminoEncontrado = false; // Bandera para indicar si se encontró un camino.

    while (!cola.isEmpty()) { // Mientras la cola no esté vacía.
        string nodoActualNom = cola.dequeue(); // Desencolar el nombre del nodo.
        int nodoActual = buscaNodo(nodoActualNom); // Obtener el índice del nodo actual a partir de su nombre.

        cout << "Visitando nodo: " << nodoActualNom << endl; // Imprimir el nodo visitado.

        if (nodoActual == fin && !caminoEncontrado) { // Si se encuentra el nodo final.
            caminoEncontrado = true; // Marcar bandera como verdadero.
        }

        // Iterar sobre todos los nodos posibles.
        for (int i = 0; i < numNodos; ++i) {
            int pesoArista = matAdj[nodoActual][i]; // Peso de la arista entre el nodo actual y el nodo i.

            if (pesoArista != 0 && !listaNodos[i].getVisitado()) { // Si hay una arista y el nodo no ha sido visitado.
                cola.enqueue(listaNodos[i].getNom()); // Encolar el nombre del nodo vecino i.
                listaNodos[i].setVisitado(true); // Marcar el nodo vecino i como visitado.
                padre[i] = nodoActual; // Registrar que el nodo actual es el padre del nodo vecino i.
                pesosCamino[i] = pesosCamino[nodoActual] + pesoArista; // Actualizar el peso del camino para el nodo vecino i.
            }
        }
    }

    if (caminoEncontrado) { // Si se encontró un camino.
        cout << "Camino encontrado (Busqueda por Anchura): ";
        int pesoTotalCamino = pesosCamino[fin]; // Obtener el peso total del camino.
        imprimirCamino(padre, inicio, fin); // Imprimir el camino.
        cout << endl;
        cout << "Peso total del camino: " << pesoTotalCamino << endl; // Imprimir el peso total del camino.
    } else {
        cout << "No se encontró camino." << endl; // Si no se encontró camino.
    }

    delete[] padre; // Liberar memoria del arreglo padre.
    delete[] pesosCamino; // Liberar memoria del arreglo pesosCamino.
}


void Grafo::busquedaProfundidad() {
    int inicio = 0; // Primer nodo (N1)
    int fin = numNodos - 1; // Último nodo (N41)

    // Inicializar todos los nodos como no visitados.
    for (int i = 0; i < numNodos; i++) {
        listaNodos[i].setVisitado(false); // Marcar cada nodo como no visitado.
    }

    int* anterior = new int[numNodos]; // Arreglo para almacenar el nodo anterior en el camino.
    for (int i = 0; i < numNodos; i++) {
        anterior[i] = -1; // Inicializar todos los nodos como sin padre (-1).
    }

    Pila pila; // Crear una pila para la DFS.
    pila.push(listaNodos[inicio].getNom()); // Apilar el nombre del nodo de inicio.

    while (!pila.isEmpty()) { // Mientras la pila no esté vacía.
        string nodoActualNom = pila.top(); // Obtener el nombre del nodo en la cima de la pila.
        int nodoActual = buscaNodo(nodoActualNom); // Obtener el índice del nodo actual.
        pila.pop(); // Desapilar el nodo.

        if (!listaNodos[nodoActual].getVisitado()) { // Si el nodo no ha sido visitado.
            listaNodos[nodoActual].setVisitado(true); // Marcar el nodo como visitado.
            cout << "Visitando nodo: " << nodoActualNom << endl; // Imprimir el nodo visitado.

            if (nodoActual == fin) { // Si se encuentra el nodo final.
                // Imprimir el camino encontrado.
                cout << "Camino encontrado (Busqueda por Profundidad): ";
                imprimirCamino(anterior, inicio, fin);
                cout << endl;

                // Calcular el peso total del camino.
                int pesoTotal = 0;
                int nodoActualPeso = fin;
                while (anterior[nodoActualPeso] != -1) { // Recorrer el camino hasta el inicio.
                    pesoTotal += matAdj[nodoActualPeso][anterior[nodoActualPeso]]; // Sumar el peso de cada arista.
                    nodoActualPeso = anterior[nodoActualPeso]; // Moverse al nodo anterior.
                }
                cout << "Peso total del camino: " << pesoTotal << endl; // Imprimir el peso total del camino.

                delete[] anterior; // Liberar memoria del arreglo anterior.
                return; // Terminar la búsqueda.
            }

            // Añadir nodos adyacentes a la pila.
            for (int i = numNodos - 1; i >= 0; --i) { // Iterar en orden inverso para mantener el orden de visita.
                if (matAdj[nodoActual][i] != 0 && !listaNodos[i].getVisitado()) { // Si hay una arista y el nodo no ha sido visitado.
                    pila.push(listaNodos[i].getNom()); // Apilar el nombre del nodo vecino.
                    anterior[i] = nodoActual; // Registrar que el nodo actual es el padre del nodo vecino i.
                }
            }
        }
    }

    cout << "No se encontro camino." << endl; // Si no se encontró camino.
    delete[] anterior; // Liberar memoria del arreglo anterior.
}


void Grafo::imprimirCamino(int* padre, int inicio, int fin) {
    if (fin == -1) { // Si se llega al nodo inicial (fin == -1).
        return; // Salir de la recursión.
    }

    imprimirCamino(padre, inicio, padre[fin]); // Llamada recursiva con el nodo padre.
    cout << listaNodos[fin].getNom() << " "; // Imprimir el nombre del nodo actual.
}
