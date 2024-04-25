#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>

using namespace std;

// Definición de la clase Pila utilizando templates para ser genérica
template<typename T>
class Pila {
private:
	// Estructura interna Nodo para almacenar los elementos de la pila
	struct Nodo {
		T dato;         // El dato almacenado de tipo genérico T
		Nodo* siguiente; // Puntero al siguiente nodo en la pila

		// Constructor del Nodo
		Nodo(T dato, Nodo* siguiente = nullptr) : dato(dato), siguiente(siguiente) {}
	};

	Nodo* cima = nullptr; // Puntero al nodo en la cima de la pila, inicialmente nullptr

public:
	// Constructor por defecto
	Pila() : cima(nullptr) {}

	// Destructor para liberar la memoria
	~Pila() {
		while (!estaVacia()) {
			pop(); // Elimina elementos de la pila, liberando la memoria de cada nodo
		}
	}

	// Método para agregar un elemento a la pila
	void push(T dato) {
		Nodo* nuevoNodo = new Nodo(dato, cima); // Crea un nuevo nodo que apunta a la cima actual
		cima = nuevoNodo; // Actualiza la cima para que apunte al nuevo nodo
	}

	// Método para eliminar el elemento en la cima de la pila
	T pop() {
		if (estaVacia()) throw std::out_of_range("Pila vacía.");
		Nodo* nodoEliminado = cima; // Guarda el nodo actual de la cima
		T dato = nodoEliminado->dato; // Extrae el dato del nodo
		cima = cima->siguiente; // Mueve la cima al siguiente nodo
		delete nodoEliminado; // Libera la memoria del nodo eliminado
		return dato; // Retorna el dato del nodo eliminado
	}

	// Método para verificar si la pila está vacía
	bool estaVacia() const {
		return cima == nullptr;
	}
};

struct Paciente
{
	char nombre[50];
	char apellido[50];
	int DNI = 0;
	int Genero = 0;
	Pila<const char*> historial;
}; //Mandalo abajo de las estructuras

Paciente pacienteAtendido;

template<typename T>
class Lista {
	private:
		// Definición interna de un nodo de la lista.
		struct Nodo {
			T dato;         // El dato almacenado en el nodo.
			Nodo* siguiente; // Puntero al siguiente nodo en la lista.

			// Constructor del nodo que inicializa el dato y el puntero siguiente.
			Nodo(T dato, Nodo* siguiente = nullptr) : dato(dato), siguiente(siguiente) {}
		};

		Nodo* cabeza = nullptr; // Puntero al primer nodo de la lista.

	public:
		// Constructor por defecto
		Lista() : cabeza(nullptr) {}

		// Destructor que libera toda la memoria de los nodos de la lista.
		~Lista() {
			Nodo* actual = cabeza;
			while (actual != nullptr) {
				Nodo* aBorrar = actual;
				actual = actual->siguiente;
				delete aBorrar;
			}
		}

		// Método para agregar un elemento al inicio de la lista.
		void agregarAlInicio(T dato) {
			cabeza = new Nodo(dato, cabeza);
		}

		// Método para imprimir todos los elementos de la lista.
		void imprimir() const {
			Nodo* actual = cabeza;
			while (actual != nullptr) {
				cout << actual->dato << " -> ";
				actual = actual->siguiente;
			}
			cout << "null" << std::endl;
		}

		// Metodo para verificar si un paciente se encuentra en espera
		bool verificarPaciente(int documento) {
			//Puntero a primer nodo de la lista
			Nodo* punteroVerif = cabeza;
			while (punteroVerif != nullptr) {
				//Recorre la lista verificando que documento no se encuentre en la lista
				if (punteroVerif->dato == documento)
				{
					return true;
				}
				punteroVerif = punteroVerif->siguiente;
			}
			return false;
		}

		int buscarDNI(int dniPaciente){
			
		}

		Paciente buscarPaciente(int pacienteLeido) {
			//Puntero a primer nodo de la lista
			Nodo* punteroVerif = cabeza;
			Paciente pacienteAux = cabeza->dato;
			while (punteroVerif != nullptr) {
				//Recorre la lista verificando que documento no se encuentre en la lista
				if (pacienteLeido == pacienteAux.DNI)
				{
					 return pacienteAux;
				}
				punteroVerif = punteroVerif->siguiente;
				pacienteAux = punteroVerif->dato;
			}
		}
};

// Definición de la clase template Cola
template<typename T>
class Cola {
private:
	// Definición del nodo interno de la cola
	struct Nodo {
		T dato;        // Dato almacenado en el nodo
		Nodo* siguiente; // Puntero al siguiente nodo en la cola

		// Constructor del Nodo
		Nodo(T dato, Nodo* sig = nullptr) : dato(dato), siguiente(sig) {}
	};

	Nodo* frente; // Puntero al primer nodo de la cola
	Nodo* final;  // Puntero al último nodo de la cola

public:
	// Constructor de la cola
	Cola() : frente(nullptr), final(nullptr) {}

	// Destructor de la cola
	~Cola() {
		while (frente != nullptr) { // Liberar todos los nodos
			Nodo* temp = frente;
			frente = frente->siguiente;
			delete temp;
		}
	}

	// Método para agregar un elemento al final de la cola
	void enqueue(T dato) {
		Nodo* nuevoNodo = new Nodo(dato);
		if (final == nullptr) {
			// Si la cola está vacía, frente y final apuntan al nuevo nodo
			frente = final = nuevoNodo;
		}
		else {
			// Si no está vacía, añadir el nuevo nodo al final y actualizar el puntero final
			final->siguiente = nuevoNodo;
			final = nuevoNodo;
		}
	}

	// Método para eliminar el elemento al frente de la cola
	T dequeue() {
		if (frente == nullptr) {
			throw out_of_range("Intento de dequeue en cola vacía");
		}
		Nodo* temp = frente;
		T dato = frente->dato;
		frente = frente->siguiente;

		if (frente == nullptr) {
			final = nullptr; // Si la cola quedó vacía, ajustar el puntero final
		}

		delete temp; // Liberar el nodo eliminado
		return dato; // Devolver el dato del nodo eliminado
	}

	// Método para comprobar si la cola está vacía
	bool estaVacia() const {
		return frente == nullptr;
	}
};

void ingresarPaciente(Lista<int>& listaVerificacion, Cola<int>& colaAtencion) {
	int dni = 0;
	
	cout << "Ingrese el dni del paciente"<<endl;
	cin >> dni;

	if(listaVerificacion.verificarPaciente(dni) == true)
	{
		cout << "Usted ya tiene un turno asignado" << endl;
	}
	else
	{
		listaVerificacion.agregarAlInicio(dni);
		colaAtencion.enqueue(dni);
	}
}

 /*void atenderPaciente(Lista<Paciente>& listaVerificacion, Lista<Paciente> listaPacientes, Cola<Paciente>& colaPacientes, Cola<Paciente> colaPacientesUrgencias){


	if (!colaPacientesUrgencias.estaVacia())
	{
		pacienteAtendido.DNI = colaPacientesUrgencias.dequeue().DNI;
		cout << "Se llama al paciente DNI:" << pacienteAtendido.DNI;
		if(listaPacientes.verificarPaciente(pacienteAtendido.DNI))
		{
			pacienteAtendido = listaPacientes.buscarPaciente(pacienteAtendido.DNI);
		}
	}
}*/

void agregarPacienteDeUrgencia(Lista<int>& listaVerificacion, Cola<int> colaPacientesUrgencias){
int dni = 0;
	
	cout << "Ingrese el dni del paciente"<<endl;
	cin >> dni;

	if(listaVerificacion.verificarPaciente(dni) == true){
		cout<<"Usted ya tiene un turno asignado"<<endl;
	}else{
		listaVerificacion.agregarAlInicio(dni);
		colaPacientesUrgencias.enqueue(dni);

	}} 
  

int main() {

	Lista<Paciente> verificarPaciente;

	Lista<Paciente> listaPacientes;
	Lista<int> listaVerificacion;

	Cola<int> colaPacientes;
	Cola<Paciente> colaPacientesUrgencias;

	//Menu de opciones 
	int select = 0;
	while (select != 6) {


		//Logica de selector de operaciones con una variable evaluada por estructura switch

		cout << "Ingrese: " << endl;
		cout << "1. Para ingresar paciente a lista de espera" << endl;
		cout << "2. Para atender paciente" << endl;
		cout << "3. Para ingresar un paciente a la cola de urgencias" << endl;
		cout << "4. " << endl;
		cout << "5. " << endl;
		cout << "6. Salir " << endl;
		cin >> select;

		switch (select) {
		case 1:
			ingresarPaciente(listaVerificacion, colaPacientes);		
			break;
		case 2:

			break;
		case 3:
			//agregarPacienteDeUrgencia(listaVerificacion, colaPacientesUrgencias);
			break;
		case 4:

			break;
		case 5:

			break;
			//default del menu principal
		case 6:
			return 0;
			break;
		default:
			cout << "Opcion incorrecta" << endl;
			break;
		}

		system("pause");
		system("cls");

	}
	return 0;
}