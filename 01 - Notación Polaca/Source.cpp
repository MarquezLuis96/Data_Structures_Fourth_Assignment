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

string notacionPolacaInversa(string expresion) {
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

	string tempString = "";
	cout << "Expresion luego de la transformacion: ";
	for (int i = 0; i < contadorPolacaInversa; i++) {
		tempString += polacaInversa[i];
		cout << polacaInversa[i];
	}
	cout << endl;
	pila.~Pila();
	return tempString;
}

string notacionPolaca(string expresion) {
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


	string tempString = "";
	cout << "Expresion luego de la transformacion: ";
	for (int i = 0; i < contPolaca; i++) {
		tempString += polaca[i];
		cout << polaca[i];
	}
	cout << endl;

	pila.~Pila();
	return tempString;
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

float operacionSegunSea(char operador, float operandoA, float operandoB) {
	switch (operador) {
		case '+':
			return operandoA + operandoB;
			break;
		case '-':
			return operandoA - operandoB;
			break;
		case '*':
			return operandoA * operandoB;
			break;
		case '/':
			if (operandoB != 0.0) {
				return operandoA / operandoB;
			}
			else {
				cerr << "ERROR: La division entre cero no existe." << endl;
				return NULL;
			}
			break;
		case '^':
			return pow(operandoA, operandoB);
			break;
		default:
			cerr << "Ha ocurrido un error inesperado..." << endl;
			return NULL;
			break;
	}
}

int buscarValorEnTabla(char buscar, int numeroDeOpr, char listaOpr[], int valoresOpr[]) {
	for (int i = 0; i < numeroDeOpr; i++) {
		if (buscar == listaOpr[i]) {
			return valoresOpr[i];
		}
	}
	return NULL;
}

float postEvaluacion(string expresion, int numeroDeOpr, char listaOpr[], int valoresOpr[]) {
	Pila<char> pilaOperandos;
	Pila<float> resultados;
	char charAux;
	float operadorA, operadorB;

	for (unsigned int i = 0; i < expresion.length(); i++) {
		charAux = expresion.at(i);

		if (charAux >= 65 && charAux <= 90 || charAux >= 97 && charAux <= 122) {
			pilaOperandos.push(charAux);
			continue;
		}

		if (charAux == '+' || charAux == '-' || charAux == '*' || charAux == '/' || charAux == '^') {
			if (pilaOperandos.pilaVacia()) {
				operadorB = resultados.pop();
				operadorA = resultados.pop();
				resultados.push(operacionSegunSea(charAux, operadorA, operadorB));
			}
			else {
				if (pilaOperandos.getCantElements() == 1) {
					operadorA = resultados.pop();
					operadorB = (float) buscarValorEnTabla(pilaOperandos.pop(), numeroDeOpr, listaOpr, valoresOpr);
					resultados.push(operacionSegunSea(charAux, operadorA, operadorB));
				}
				else {
					operadorB = (float) buscarValorEnTabla(pilaOperandos.pop(), numeroDeOpr, listaOpr, valoresOpr);
					operadorA = (float) buscarValorEnTabla(pilaOperandos.pop(), numeroDeOpr, listaOpr, valoresOpr);
					resultados.push(operacionSegunSea(charAux, operadorA, operadorB));
				}
			}
		}
	}

	return resultados.pop();
}

void evaluacionPostfija(string expresion) {
	char listaOpr[MAX];
	int valoresOpr[MAX];
	int numeroDeOpr;
	float resultado;

	numeroDeOpr = agruparCaracteres(expresion, listaOpr);
	llenarConValores(numeroDeOpr, listaOpr, valoresOpr);
	imprimirTablaDeValores(numeroDeOpr, listaOpr, valoresOpr);
	resultado = postEvaluacion(expresion, numeroDeOpr, listaOpr, valoresOpr);

	cout << "El resultado de la expresion dados los valores a sustituir es: " << resultado << endl;
}

float preEvaluacion(string expresion, int numeroDeOpr, char listaOpr[], int valoresOpr[]) {
	Pila<char> operandos;
	Pila<char> operadores;
	Pila<float> resultado;
	char charAux;

	float operandoA, operandoB;

	//True para cuando lo ultimo ingresado fue un operador y false para cuando lo ultimo ingresado fue un operando
	bool ban = false;

	for (unsigned int i = 0; i < expresion.length(); i++) {
		charAux = expresion.at(i);
		
		if (charAux == '+' || charAux == '-' || charAux == '*' || charAux == '/' || charAux == '^') {
			//Entra aca si es un caracter de operador
			//Cambio bandera para indicar la entrada de un operador
			ban = true;

			//Apilar los operadores
			operadores.push(charAux);
		}
		else {
			//Entra aca si es un caracter de operando
			
			if (ban == true) {
				//Viene de ingresar un caracter de operador
				
				if (operandos.getCantElements() < 2) {
					//No hay los suficientes operadores, asi que hago push y no cambio la bandera para que vuelva a entrar aca
					operandos.push(charAux);
				}

				if (operandos.getCantElements() == 2) {
					operandoB = (float) buscarValorEnTabla(operandos.pop(), numeroDeOpr, listaOpr, valoresOpr);
					operandoA = (float) buscarValorEnTabla(operandos.pop(), numeroDeOpr, listaOpr, valoresOpr);
					resultado.push(operacionSegunSea(operadores.pop(), operandoA, operandoB));
					ban = false;
					//ahora si cambio a false la bandera
				}
			}
			else {
				//Viene de ingresar un caracter de operando
				if (!resultado.pilaVacia() && !operadores.pilaVacia()) {
					operandoA = resultado.pop();
					operandoB = (float) buscarValorEnTabla(charAux, numeroDeOpr, listaOpr, valoresOpr);
					resultado.push(operacionSegunSea(operadores.pop(), operandoA, operandoB));
					ban = false; //por si a las moscas, aunque no creo que llegue false por aca
				}
			}
		}
	}

	while (!operadores.pilaVacia()) {
		operandoB = resultado.pop();
		operandoA = resultado.pop();
		resultado.push(operacionSegunSea(operadores.pop(), operandoA, operandoB));
	}

	return resultado.pop();
}

void evaluacionPrefija(string expresion) {
	char listaOpr[MAX];
	int valoresOpr[MAX];
	int numeroDeOpr;
	float resultado;

	numeroDeOpr = agruparCaracteres(expresion, listaOpr);
	llenarConValores(numeroDeOpr, listaOpr, valoresOpr);
	imprimirTablaDeValores(numeroDeOpr, listaOpr, valoresOpr);
	resultado = preEvaluacion(expresion, numeroDeOpr, listaOpr, valoresOpr);

	cout << "El resultado de la expresion dados los valores a sustituir es: " << resultado << endl;
}

//Funcion principal
int main(int args, char* argsv[]) {

	string expresion;
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
			string prefija;
			cout << "Ingrese la expresion a evaluar: ";
			cin >> expresion;
			cout << endl;

			if (verificarExpresion(expresion)) {
				cout << "Notacion Polaca (Prefija): " << endl;
				prefija = notacionPolaca(expresion);
			}
			else {
				cerr << "ERROR: Ha ocurrido un error con la expresion ingresada." << endl;
				cerr << "Posibles errores: " << endl;
				cerr << "1 - Posible falta de parentesis por cerrar." << endl;
				cerr << "2 - Operadores u Operandos no permitidos en el programa." << endl;
				cerr << "Intente arreglando su expresion o ingresando una nueva." << endl;
				continue;
			}
			cout << "Ingrese los valores para sustituir en la notacion prefija: " << endl;
			evaluacionPrefija(prefija);
		}

		if (opc == 2) {
			string postfija;
			cout << "Ingrese la expresion a evaluar: ";
			cin >> expresion;
			cout << endl;

			if (verificarExpresion(expresion)) {
				cout << "Notacion Polaca inversa (Postfija): " << endl;
				postfija = notacionPolacaInversa(expresion);
			}
			else {
				cerr << "ERROR: Ha ocurrido un error con la expresion ingresada." << endl;
				cerr << "Posibles errores: " << endl;
				cerr << "1 - Posible falta de parentesis por cerrar." << endl;
				cerr << "2 - Operadores u Operandos no permitidos en el programa." << endl;
				cerr << "Intente arreglando su expresion o ingresando una nueva." << endl;
				continue;
			}
			cout << "Ingrese los valores para sustituir en la notacion postfija: " << endl;
			evaluacionPostfija(postfija);
		}
		cout << endl;
	} while (true);
	
	
	//Pruebas durante producci�n
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
	// --------------------------------------------
	// Evaluacion de expresiones postfijas
	//string expresion = "AB*AC+/";
	//string expresion = "AB*A/C+";
	//string expresion = "AB-C^D+";
	//evaluacionPostfija(expresion);
	// --------------------------------------------
	// Evaluacion de expresiones prefijas
	//string expresion = "/*AB+AC";
	//string expresion = "+/*ABAC";
	//string expresion = "+^-ABCD";
	//evaluacionPrefija(expresion);

	return 0;
}