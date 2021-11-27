//Headers
#include <iostream>

//Declaracion de namespaces
using namespace std;

template <class dataType>
class Pila {
private:
	class Nodo {
	public:
		Nodo* siguiente;
		dataType dato;

		Nodo(dataType key) {
			dato = key;
			siguiente = NULL;
		}

	};

	Nodo* tope;
	int cantElementos;
public:
	//Constructor
	Pila() {
		tope = NULL;
		cantElementos = 0;
	}

	void push(dataType key);
	dataType pop();
	const dataType topeDePila();
	const bool pilaVacia();
	bool limpiarPila();
	int getCantElements();
	void imprimirElementos();

	//Destructor
	~Pila() {
		limpiarPila();
	}
};

template <class dataType>
const bool Pila<dataType>::pilaVacia() {
	if (tope == NULL) {
		return true;
	}

	return false;
}

template <class dataType>
bool Pila<dataType>::limpiarPila() {
	Nodo* aux;
	if (pilaVacia()) {
		cerr << "Error: La pila ya se encuentra vacia." << endl;
		return false;
	}

	while (!pilaVacia()) {
		aux = tope;
		tope = tope->siguiente;
		delete aux;
		cantElementos--;
	}
	return true;
}

template <class dataType>
void Pila<dataType>::push(dataType key) {
	Nodo* nuevoElemento;

	nuevoElemento = new Nodo(key);
	nuevoElemento->siguiente = tope;
	tope = nuevoElemento;

	cantElementos++;
}

template <class dataType>
dataType Pila<dataType>::pop() {
	if (pilaVacia()) {
		cerr << "ERROR: UNDERFLOW - Pila vacia, no se puede extraer el elemento." << endl;
		return NULL;
	}

	dataType aux = tope->dato;
	tope = tope->siguiente;

	cantElementos--;
	return aux;
}

template <class dataType>
const dataType Pila<dataType>::topeDePila() {
	if (pilaVacia()) {
		cerr << "ERROR: UNDERFLOW - Pila vacia, no se puede leer el elemento en el tope de la pila" << endl;
		return NULL;
	}

	return tope->dato;
}

template <class dataType>
int Pila<dataType>::getCantElements() {
	return cantElementos;
}

template <class dataType>
void Pila<dataType>::imprimirElementos() {
	if (pilaVacia()) {
		cerr << "Error: La pila se encuentra vacia." << endl;
	}

	Nodo* aux = tope;
	int auxCant = cantElementos;

	while (aux != NULL) {
		cout << "Elemento " << auxCant << " : " << aux->dato << endl;
		auxCant--;
		aux = aux->siguiente;
	}
}

//Funcion principal
int main(int args, char* argsv[]) {
	//Code Here
	return 0;
}