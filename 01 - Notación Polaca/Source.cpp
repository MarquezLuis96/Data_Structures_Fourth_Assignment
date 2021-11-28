//Headers
#include <iostream>
const int MAX = 100;

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
		//cerr << "Error: La pila ya se encuentra vacia." << endl;
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

//RETORNA TRUE SI VA A LA PILA
bool compararOperadoresPolacaInversa(char nuevoOperador, Pila<char> *pila) {
	if (pila->pilaVacia()) {
		return true;
	}

	char charAux = pila->topeDePila();
	
	if (nuevoOperador == '(') {
		return true;
	}

	if (nuevoOperador == '^') {
		return true;
	}

	if (nuevoOperador == '+' && charAux == '-' || nuevoOperador == '+' && charAux == '(') {
		return true;
	}

	if (nuevoOperador == '-' && charAux == '(') {
		return true;
	}

	if (nuevoOperador == '*' || nuevoOperador == '/') {
		if (nuevoOperador == '*') {
			if (charAux == '/' || charAux == '+' || charAux == '-' || charAux == '(') {
				return	true;
			}
		}
		
		if (nuevoOperador == '/') {
			if (charAux == '+' || charAux == '-' || charAux == '(') {
				return true;
			}
		}
	}

	return false;
}

void notacionPolacaInversa(string expresion) {
	Pila<char> pila;
	
	char polacaInversa[MAX];
	int contadorPolacaInversa = 0;
	
	char caracter;
	char caracterAux;

	cout << "Expresion antes de la transformacion: " << expresion << endl;

	for (int i = 0; i < expresion.length(); i++) {
		caracter = expresion.at(i);
		if (caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/' || caracter == '^' || caracter == '(' || caracter == ')') {
			if (pila.pilaVacia()) {
				pila.push(caracter);
			}
			else {
				if (caracter == ')') {
					//Entra aca si el caracter es el cierre del operador de maxima prioridad: parentesis ("()")
					caracterAux = pila.topeDePila();
					while (caracterAux != '(') {
						polacaInversa[contadorPolacaInversa] = pila.pop();
						contadorPolacaInversa++;
						caracterAux = pila.topeDePila();
						if (caracterAux == '(') {
							pila.pop();
						}
					}
				}
				else {
					bool bandera;
					do {
						bandera = compararOperadoresPolacaInversa(caracter, &pila);
						if (bandera == true) {
							pila.push(caracter);
						}
						else {
							polacaInversa[contadorPolacaInversa] = pila.pop();
							contadorPolacaInversa++;
						}
					} while (!bandera);
				}
			}
		}
		else {
			polacaInversa[contadorPolacaInversa] = caracter;
			contadorPolacaInversa++;
		}

		if (i == expresion.length()-1) {
			while (!pila.pilaVacia()) {
				polacaInversa[contadorPolacaInversa] = pila.pop();
				contadorPolacaInversa++;
			}
			break;
		}
	}

	cout << "Expresion luego de la transformacion: ";
	for (int i = 0; i < contadorPolacaInversa; i++) {
		cout << polacaInversa[i];
	}
	cout << endl;
	pila.~Pila();
}

//Funcion principal
int main(int args, char* argsv[]) {
	//Code Here

	//Notacion Polaca Inversa
	//notacionPolacaInversa("a*(b+c-(d/e^f)-g)-h");
	//notacionPolacaInversa("a*b/(a+c)");
	//notacionPolacaInversa("a*b/a+c");
	//notacionPolacaInversa("(a-b)^c+d");


	return 0;
}