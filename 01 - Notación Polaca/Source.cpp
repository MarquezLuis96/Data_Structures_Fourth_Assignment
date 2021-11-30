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

	for (unsigned int i = 0; i < expresion.size(); i++) {
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

void notacionPolaca(string expresion) {
	Pila<char> pila;

	char charAux;

	char arrayAux[MAX];
	int contAux = 0;

	char polaca[MAX];
	int contPolaca = 0;

	cout << "Expresion antes de la transformacion: " << expresion << endl;

	for (unsigned int i = 0; i < expresion.size(); i++) {
		charAux = expresion.at(i);
		if (charAux == '(' && !(pila.pilaVacia())) {
			do {
				polaca[contPolaca++] = pila.pop();
			} while (!(pila.pilaVacia()));
			for (int i = 0; i < contAux; i++) {
				polaca[contPolaca++] = arrayAux[i];
			}
			contAux = 0;
		}

		if (charAux == '(' || charAux == ')') {
			continue;
		}
		
		if (charAux == '+' || charAux == '-' || charAux == '*' || charAux == '/' || charAux == '^') {
			pila.push(charAux);
		}
		else {
			arrayAux[contAux++] = charAux;
		}
	}

	while (!(pila.pilaVacia())) {
		polaca[contPolaca++] = pila.pop();
	}

	for (int i = 0; i < contAux; i++) {
		polaca[contPolaca++] = arrayAux[i];
	}

	cout << "Expresion luego de la transformacion: ";
	for (int i = 0; i < contPolaca; i++) {
		cout << polaca[i];
	}
	cout << endl;

	pila.~Pila();
}

bool verificarOperadoresYOperandos(string expresion) {
	char charAux;
	for (unsigned int i = 0; i < expresion.length(); i++) {
		charAux = expresion.at(i);
		if (charAux == '+' || charAux == '-' || charAux == '*' || charAux == '/' || charAux == '^' || charAux == '(' || charAux == ')') {
			continue;
		}
		else {
			if (charAux >= 65 && charAux <= 90 || charAux >= 97 && charAux <= 122) {
				continue;
			}
			else {
				return false;
			}
		}
		
	}
	return true;
}

bool verificarParentesis(string expresion) {
	int contParentAbierto = 0;
	int contParentCerrado = 0;
	char charAux;
	for (unsigned int i = 0; i < expresion.length(); i++) {
		charAux = expresion.at(i);
		if (charAux == '(') {
			contParentAbierto++;
		}
		if (charAux == ')') {
			contParentCerrado++;
		}
	}
	if (contParentAbierto == contParentCerrado) {
		return true;
	}
	return false;
}

bool verificarExpresion(string expresion) {
	if (verificarOperadoresYOperandos(expresion)) {
		if (verificarParentesis(expresion)) {
			return true;
		}
	}
	return false;
}

int agruparCaracteres(string expresion, char listaDeOperandos[]) {
	char charAux;
	int contListaOpr = 0;
	bool ban = false;
	for (unsigned int i = 0; i < expresion.length(); i++) {
		charAux = expresion.at(i);
		if (charAux >= 65 && charAux <= 90 || charAux >= 97 && charAux <= 122) {
			for (int j = 0; j < contListaOpr; j++) {
				if (charAux == listaDeOperandos[j]) {
					ban = true;
					break;
				}
				else {
					ban = false;
				}
			}
			if (ban == false) {
				listaDeOperandos[contListaOpr] = charAux;
				contListaOpr++;
			}
		}
	}

	return contListaOpr;
}

void llenarConValores(int numeroDeOpr, char listaOpr[], int valoresOpr[]) {
	for (int i = 0; i < numeroDeOpr; i++) {
		cout << "Ingrese un valor para '" << listaOpr[i] << "' : ";
		cin >> valoresOpr[i];
		cout << endl;
	}
}

void imprimirTablaDeValores(int numeroDeOpr, char listaOpr[], int valoresOpr[]) {
	cout << "La tabla de valores es la siguiente: " << endl;

	for (int i = 0; i < numeroDeOpr; i++) {
		cout << "|" << listaOpr[i] << "|";
	}
	cout << endl;

	for (int i = 0; i < numeroDeOpr; i++) {
		cout << "|" << valoresOpr[i] << "|";
	}
	cout << endl;
}

//Funcion principal
int main(int args, char* argsv[]) {

	string expresion = "A+B*(C*D(E-F)^G)";
	char listaOpr[MAX];
	int valoresOpr[MAX];
	int numeroDeOpr;

	numeroDeOpr = agruparCaracteres(expresion, listaOpr);
	llenarConValores(numeroDeOpr, listaOpr, valoresOpr);
	imprimirTablaDeValores(numeroDeOpr, listaOpr, valoresOpr);



	/*string expresion;
	int opc;
	
	cout << "Bienvenido al programa de Notacion Polaca" << endl;

	do {
		cout << "Ingrese la opcion de la operacion que desea realizar: " << endl;
		cout << "1 - De Notacion Infija a Notacion Polaca (Prefija)." << endl;
		cout << "2 - De Notacion Infija a Notacion Polaca Inversa (Postfija)." << endl;
		cout << "0 - Salir del programa." << endl;
		cin >> opc;
		if (opc > 2 || opc < 0) {
			cerr << "Error: Usted ha ingresado una opcion incorrecta." << endl;
			cerr << "Intente nuevamente." << endl;
		}

		if (opc == 0) {
			cout << "Hasta Luego!!!" << endl;
			break;
		}

		if (opc == 1) {
			cout << "Ingrese la expresion a evaluar: ";
			cin >> expresion;
			cout << endl;

			if (verificarExpresion(expresion)) {
				cout << "Notacion Polaca (Prefija): " << endl;
				notacionPolaca(expresion);
			}
			else {
				cerr << "ERROR: Ha ocurrido un error con la expresion ingresada." << endl;
				cerr << "Posibles errores: " << endl;
				cerr << "1 - Posible falta de parentesis por cerrar." << endl;
				cerr << "2 - Operadores u Operandos no permitidos en el programa." << endl;
				cerr << "Intente arreglando su expresion o ingresando una nueva." << endl;
				continue;
			}
		}

		if (opc == 2) {
			cout << "Ingrese la expresion a evaluar: ";
			cin >> expresion;
			cout << endl;

			if (verificarExpresion(expresion)) {
				cout << "Notacion Polaca inversa (Postfija): " << endl;
				notacionPolacaInversa(expresion);
			}
			else {
				cerr << "ERROR: Ha ocurrido un error con la expresion ingresada." << endl;
				cerr << "Posibles errores: " << endl;
				cerr << "1 - Posible falta de parentesis por cerrar." << endl;
				cerr << "2 - Operadores u Operandos no permitidos en el programa." << endl;
				cerr << "Intente arreglando su expresion o ingresando una nueva." << endl;
				continue;
			}
		}
		cout << endl;
	} while (true);*/
	
	
	//Pruebas durante producción
	// --------------------------------------------
	//Notacion Polaca Inversa
	//notacionPolacaInversa("a*(b+c-(d/e^f)-g)-h");
	//notacionPolacaInversa("a*b/(a+c)");
	//notacionPolacaInversa("a*b/a+c");
	//notacionPolacaInversa("(a-b)^c+d");
	// --------------------------------------------
	//Notacion Polaca
	//notacionPolaca("a*b/(a+c)");
	//notacionPolaca("a*b/a+c");
	//notacionPolaca("(a-b)^c+d");

	return 0;
}