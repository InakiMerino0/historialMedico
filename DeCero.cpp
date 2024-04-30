#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// Definicion de la clase Pila utilizando templates para ser generica
template<typename T>
class Pila {
private:
    // Estructura interna Nodo para almacenar los elementos de la pila
    struct Nodo {
        T dato;         // El dato almacenado de tipo gen?rico T
        Nodo* siguiente; // Puntero al siguiente nodo en la pila

        // Constructor del Nodo
        Nodo(T dato, Nodo* siguiente = nullptr) : dato(dato), siguiente(siguiente) {}
    };

    Nodo* cima = nullptr; // Puntero al nodo en la cima de la pila, inicialmente nullptr

public:
    // Constructor por defecto
    Pila() : cima(nullptr) {}

    // Metodo para agregar un elemento a la pila
    void push(T dato) {
        Nodo* nuevoNodo = new Nodo(dato, cima); // Crea un nuevo nodo que apunta a la cima actual
        cima = nuevoNodo; // Actualiza la cima para que apunte al nuevo nodo
    }

    // Metodo para eliminar el elemento en la cima de la pila
    T pop()
    {
        if (cima == nullptr) {
            throw out_of_range("Intento de pop en pila vacia");
        }
        T dato;
        Nodo* temp = cima; // Guarda el nodo en la cima actual
        cima = cima->siguiente; // Actualiza la cima para que apunte al siguiente nodo
        dato = temp->dato; // Guarda el dato del nodo eliminado
        delete temp; // Libera la memoria del nodo eliminado
        return dato;
    }
    //funcion que retorna la cima de la pila
    T peek() {
        if (cima == nullptr) {//verifica que la pila no este vacia
            throw out_of_range("Intento de peek en pila vacia");
        }
        return cima->dato;//devuelve el dato cima

    }

    // Metodo para verificar si la pila esta vac?a
    bool estaVacia() const {
        return cima == nullptr;
    }

    // Método para copiar una pila
    Pila<T> copiar() const {
        Pila<T> pilaCopia;
        Nodo* actual = cima;
        while (actual != nullptr) {//copia todos los datos de la pila actual en la pila copia 
            pilaCopia.push(actual->dato);
            actual = actual->siguiente;
        }
        return pilaCopia;//retorna la copia de la pila original
    }
};

// Definicion de la estructura Paciente
struct Paciente
{
    //Atributos de la estructura Paciente
    char nombre[50];
    char apellido[50];
    int DNI = 0;
    int edad = 0;
    int Genero = 0;
    Pila<int> Doctor;//se usan 2 pilas para poder almacenar varias consultas
    Pila<string> historial;
};

// Definicion de la clase Lista utilizando templates para ser generica
template<typename T>
class Lista {
private:
    // Definicion interna de un nodo de la lista.
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

    // Metodo para eliminar un paciente de la lista de verificacion
    void eliminardni(int dniPaciente) {
        Nodo* actual = cabeza;
        Nodo* anterior = nullptr;

        // Busca el nodo con el DNI dado
        while (actual != nullptr && actual->dato != dniPaciente) {
            anterior = actual;
            actual = actual->siguiente;
        }

        // Si se encuentra el nodo con el DNI dado, se elimina
        if (actual != nullptr) {
            if (actual == cabeza) {
                cabeza = cabeza->siguiente;
            }
            else {
                anterior->siguiente = actual->siguiente;
            }
            delete actual;
        }
    }

    // Metodo que devuelve el dato cabeza
    T datoCabeza() {
        return cabeza->dato;
    }

    // Metodo para agregar un elemento al inicio de la lista.
    void agregarAlInicio(T dato) {
        cabeza = new Nodo(dato, cabeza);
    }

    // Metodo para verificar si un paciente se encuentra en espera
    bool verificarPaciente(int documento) {

        //Puntero a primer nodo de la lista
        Nodo* punteroVerif = cabeza;

        while (punteroVerif != nullptr) {
            //Recorre la lista verificando que documento no se encuentre en la lista
            if (punteroVerif->dato == documento)
            {
                return true;//si lo encuntra devuelve true
            }
            punteroVerif = punteroVerif->siguiente;
        }
        return false;
    }

    // Metodo bool para buscar un paciente por su DNI en una lista de paciente
    bool buscarDNI(int dniPaciente) {
        Nodo* actual = cabeza;
        while (actual != nullptr) {

            // Si encuentra el paciente con el DNI dado, devuelve true 
            if (actual->dato.DNI == dniPaciente) {
                return true;
            }
            actual = actual->siguiente;
        }
        // Si no se encuentra el DNI en la lista, devuelve false 
        return false;
    }

    // Metodo bool para buscar un paciente por su DNI en lista de tipo int
    bool buscarDNI2(int dniPaciente) {
        Nodo* actual = cabeza;
        while (actual != nullptr) {

            // Si encuentra el paciente con el DNI dado, devuelve true
            if (actual->dato == dniPaciente) {
                return true;
            }
            actual = actual->siguiente;
        }
        // Si no se encuentra el DNI en la lista, devuelve false 
        return false;
    }

    // Metodo para buscar los datos de un paciente
    Paciente& buscarPaciente(int dniPaciente) {
        //Puntero a primer nodo de la lista
        Nodo* punteroVerif = cabeza;
        while (punteroVerif != nullptr) {

            // Recorre la lista verificando que documento sea igual al documento 
            // de un paciente de la lista
            if (punteroVerif->dato.DNI == dniPaciente)
            {
                // Si lo encuntra, devuelve el paciente
                return punteroVerif->dato;
            }
            punteroVerif = punteroVerif->siguiente;
        }
        throw std::runtime_error("Paciente no encontrado"); // Si no lo encuntra, Lanza una excepción si el paciente no se encuentra
    }

    // Metodo para verificar si la lista esta vacia
    bool estaVacia() {
        if (cabeza == nullptr) {
            return true;
        }
        return false;
    }

    // Metodo para mostrar la lista de pacientes
    void mostrarLista() {
        //Puntero a primer nodo de la lista
        Nodo* punteroTemp = cabeza;

        cout << "Lista de pacientes del dia : " << endl;
        // Se crea una lista int para almacenar los dni de los 
        // pacientes para no mostrar pacientes repetidos
        Lista<int> dni;

        while (punteroTemp != nullptr) {

            // Se crea un paciente temporal para almacenar los datos del paciente
            Paciente& tempPaciente = punteroTemp->dato;

            if (!dni.buscarDNI2(tempPaciente.DNI))
            {
                // Se agrega el dni a la lista para no mostrar paciente de nuevo
                dni.agregarAlInicio(tempPaciente.DNI);
                cout << endl;

                // Se muestran los datos del paciente
                cout << "DNI: " << tempPaciente.DNI << endl;
                cout << "Nombre: " << tempPaciente.nombre << endl;
                cout << "Apellido: " << tempPaciente.apellido << endl;
                cout << "Edad: " << tempPaciente.edad << endl;
                if (tempPaciente.Genero == 1)
                {
                    cout << "Masculino" << endl;
                }
                else
                {
                    cout << "Femenino" << endl;
                }

                // Se crean copias de las pilas del paciente 
                // para no manipular las originales
                Pila<string> pilaHistorial = tempPaciente.historial.copiar();
                Pila<int> pilaDoctor = tempPaciente.Doctor.copiar();

                int contador = 1;

                while (!pilaDoctor.estaVacia()) {//revisa que la pila no este vacia
                    cout << "Consulta " << contador << endl;
                    cout << "El paciente vino al doctor: ";
                    switch (pilaDoctor.peek()) {//segun el valor almacenado en la pila determina que caso mostrar
                    case 1:
                        cout << "Cirujano" << endl;
                        break;
                    case 2:
                        cout << "Cardiologo" << endl;
                        break;
                    case 3:
                        cout << "Oftalmologo" << endl;
                        break;
                    case 4:
                        cout << "Traumatologo" << endl;
                        break;
                    case 5:
                        cout << "Odontologo" << endl;
                        break;
                    case 6:
                        cout << "Dentista" << endl;
                        break;
                    case 7:
                        cout << "Dermatologo" << endl;
                        break;
                    default:
                        cout << "Guardia" << endl;
                        break;
                    }
                    cout << "Por el motivo: " << pilaHistorial.peek() << endl;
                    pilaDoctor.pop(); // Eliminar el elemento cima de la pila después de mostrarlo
                    pilaHistorial.pop(); // Eliminar el elemento cima de la pila después de mostrarlo
                    contador++;//un contador para expresar el numero de consultas
                }

            }
            cout << endl << endl;
            punteroTemp = punteroTemp->siguiente; // Se avanzar al siguiente nodo en cada iteración
        }
    }

    // Metodo para eliminar el primer nodo de la lista
    void eliminarCabecera() {
        if (cabeza != nullptr) {
            //Puntero a primer nodo de la lista
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;//elimino el anterior cabeza
        }
    }
};

// Definicion de la clase Cola utilizando templates para ser generica
template<typename T>
class Cola {
private:
    // Definicion del nodo interno de la cola
    struct Nodo {
        T dato;        // Dato almacenado en el nodo
        Nodo* siguiente; // Puntero al siguiente nodo en la cola

        // Constructor del Nodo
        Nodo(T dato, Nodo* sig = nullptr) : dato(dato), siguiente(sig) {}
    };

    Nodo* frente; // Puntero al primer nodo de la cola
    Nodo* final;  // Puntero al ultimo nodo de la cola

public:
    // Constructor de la cola
    Cola() : frente(nullptr), final(nullptr) {}

    // Metodo para agregar un elemento al final de la cola
    void enqueue(T dato) {
        Nodo* nuevoNodo = new Nodo(dato);
        if (final == nullptr) {
            // Si la cola esta vacia, frente y final apuntan al nuevo nodo
            frente = final = nuevoNodo;
        }
        else {
            // Si no esta vacia, añadir el nuevo nodo al final y actualizar el puntero final
            final->siguiente = nuevoNodo;
            final = nuevoNodo;
        }
    }

    // Metodo para eliminar el elemento al frente de la cola
    T dequeue() {
        if (frente == nullptr) {
            throw out_of_range("Intento de dequeue en cola vacia");
        }
        // Puntero al primer nodo frente de la cola
        Nodo* temp = frente;
        T dato = frente->dato;
        frente = frente->siguiente;

        if (frente == nullptr) {
            final = nullptr; // Si la cola queda vacia, ajustar el puntero final
        }

        delete temp; // Liberar el nodo eliminado
        return dato; // Devolver el dato del nodo eliminado
    }

    // Metodo para comprobar si la cola esta vacia
    bool estaVacia() const {
        return frente == nullptr;
    }

    // Metodo para obtener DNI del paciente del frente de la cola 
    bool buscarDNI(int dniPaciente) {
        // Puntero al primer nodo frente de la cola
        Nodo* actual = frente;
        while (actual != nullptr) {
            // Si encuentra el paciente con el DNI dado, devuelve su índice
            if (actual->dato == dniPaciente) {
                return true;
            }
            actual = actual->siguiente;
        }
        // Si no se encuentra el DNI en la lista, devuelve -1
        return false;
    }


};

// Funcion para ingresar un paciente a la cola de espera
void ingresarPaciente(Lista<int>& listaVerificacion, Cola<int>& colaAtencion) {

    // El usuario ingresa DNI del paciente
    int dni = 0;
    cout << "Ingrese el dni del paciente" << endl;

    cin >> dni;

    // Manejo de errores dni
    while (cin.fail() || dni < 1)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); // Se ignora toda la entrada anterior hasta encontrar un salto de linea  
        cout << "Ingrese un dni valido: ";
        cin >> dni;
    }

    // Condicion para verificar si el dni ya tiene turno asignado
    if (listaVerificacion.verificarPaciente(dni))
    {
        // Si ya tiene un turno, no puede registrarse de nuevo
        cout << "Usted ya tiene un turno asignado" << endl << endl;
    }
    // Si no esta en la lista lo agrega a la cola de urgencias
    else
    {
        // Si no tiene turno, se registra el turno 
        // a la lista de verificacion y se agrega a la cola de atencion
        listaVerificacion.agregarAlInicio(dni);
        colaAtencion.enqueue(dni);
        cout << "Perfecto. Espera a ser llamado! " << endl << endl;
    }
    return;
}

// Funcion para atender un paciente en la cola
void atenderPaciente(Lista<int>& listaVerificacion, Lista<Paciente>& listaPacientes, Cola<int>& colaPacientes, Cola<int>& colaPacientesUrgencias) {

    // Se crea un paciente registrado
    Paciente nuevoPaciente;
    int dni = 0;

    // Verificar si la cola de urgencias esta vacia

    if (!colaPacientesUrgencias.estaVacia())
    {
        // Se obtiene el dni del paciente en la cola y lo eliminamos
        int dni = colaPacientesUrgencias.dequeue();

        // Eliminamos dni de la lista de verificacion
        listaVerificacion.eliminardni(dni);

        cout << "Atendiendo paciente con DNI: " << dni << endl;

        // Creamos una variable bool para analizar si el paciente ya ha sido registrado anteriormente
        if (listaPacientes.buscarDNI(dni))
        {
            // Si el paciente ya ha sido registrado, se obtiene su informacion desde la listaPacientes
            nuevoPaciente = listaPacientes.buscarPaciente(dni);

        }
        else
        {
            // Si el paciente nunca ha sido registrado, se solicita su informacion
            nuevoPaciente.DNI = dni;
            cout << "Ingrese su nombre: ";
            cin >> nuevoPaciente.nombre;

            cout << "Ingrese su apellido: ";
            cin >> nuevoPaciente.apellido;

            cout << "Ingrese su edad: ";
            cin >> nuevoPaciente.edad;

            //Manejo de errores nuevoPaciente.edad
            while (cin.fail() || (nuevoPaciente.edad < 1 || nuevoPaciente.edad > 150)) {
                cin.clear();
                cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); // Se ignora toda la entrada anterior hasta encontrar un salto de linea  
                cout << "Ingrese una edad valida (entre 1 y 150) : ";
                cin >> nuevoPaciente.edad;
            }

            cout << "Ingrese 1 si su genero es Masculino y 2 si es Femenino: ";
            cin >> nuevoPaciente.Genero;

            //Manejo de errores nuevoPaciente.genero
            while (cin.fail() || (nuevoPaciente.Genero != 1 && nuevoPaciente.Genero != 2)) {
                cin.clear();
                cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); // Se ignora toda la entrada anterior hasta encontrar un salto de linea  
                cout << "Ingrese un genero valido (1 o 2) : ";
                cin >> nuevoPaciente.Genero;
            }
        }
    }
    // Si la cola de urgencia esta vacia, se verifica si la cola de pacientes esta vacia
    else if (!colaPacientes.estaVacia())
    {
        // Se obtiene el dni del paciente en la cola y lo eliminamos
        int dni = colaPacientes.dequeue();

        // Eliminamos dni de la lista de verificacion
        listaVerificacion.eliminardni(dni);

        // Se crea una variable bool para analizar si el paciente ya ha sido registrado anteriormente
        cout << "Atendiendo paciente con DNI: " << dni << endl;

        if (listaPacientes.buscarDNI(dni))
        {
            // Si el paciente ya ha sido registrado, se obtiene su informacion desde la listaPacientes
            nuevoPaciente = listaPacientes.buscarPaciente(dni);
        }
        else
        {
            // Si el paciente nunca ha sido registrado, se solicita su informacion
            nuevoPaciente.DNI = dni;
            cout << "Ingrese su nombre: ";
            cin >> nuevoPaciente.nombre;

            cout << "Ingrese su apellido: ";
            cin >> nuevoPaciente.apellido;

            cout << "Ingrese su edad: ";
            cin >> nuevoPaciente.edad;

            //Manejo de errores nuevoPaciente.edad
            while (cin.fail() || (nuevoPaciente.edad < 1 || nuevoPaciente.edad > 150)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Se ignora toda la entrada anterior hasta encontrar un salto de linea  
                cout << "Ingrese una edad valida (entre 1 y 150) : ";
                cin >> nuevoPaciente.edad;
            }

            cout << "Ingrese 1 si su genero es Masculino y 2 si es Femenino: ";
            cin >> nuevoPaciente.Genero;
            //Manejo de errores nuevoPaciente.genero
            while (cin.fail() || (nuevoPaciente.Genero != 1 && nuevoPaciente.Genero != 2)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Se ignora toda la entrada anterior hasta encontrar un salto de linea  
                cout << "Ingrese un genero valido (1 o 2) : ";
                cin >> nuevoPaciente.Genero;
            }
        }
    }
    // Si ambas colas estan vacias, se informa al usuario
    else
    {
        cout << "No hay pacientes en la fila." << endl << endl;
        return;
    }
    // Se crea la variable num para averiguar a que doctor el paciente desea visitar
    int num = 0;
    cout << "Ingrese a que doctor viene a visitar: " << endl;
    cout << "1. Cirujano" << endl;
    cout << "2. Cardiologo" << endl;
    cout << "3. Oftalmologo" << endl;
    cout << "4. Traumatologo" << endl;
    cout << "5. Odontologo" << endl;
    cout << "6. Dentista " << endl;
    cout << "7. Dermatologo" << endl;
    cout << "8. Guardia" << endl;
    cin >> num;

    // Manejo de errores num
    while (cin.fail() || (num < 1 || num > 8))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Se ignora toda la entrada anterior hasta encontrar un salto de linea  
        cout << "Ingrese un numero valido: ";
        cin >> num;
    }

    // Se le hace push a la pila Doctor
    nuevoPaciente.Doctor.push(num);

    // Se crea la variable motivo para saber el motivo de la consulta
    string motivo = "";
    cout << "Ingrese el motivo de la consulta" << endl;
    cin.ignore();
    getline(cin, motivo);

    // Se le hace push a la pila historial
    nuevoPaciente.historial.push(motivo);

    // Se agrega el nuevo paciente a la lista de pacientes (para futuras consultas)
    listaPacientes.agregarAlInicio(nuevoPaciente);

    cout << "Paciente: " << nuevoPaciente.nombre << " " << nuevoPaciente.apellido << " atendido con exito. " << endl << endl;
    return;
}

// Funcion para agregar un paciente de urgencia a la cola de espera (con prioridad)
void agregarPacienteDeUrgencia(Lista<int>& listaVerificacion, Cola<int>& colaPacientesUrgencias) {
    int dni = 0;
    cout << "Ingrese el dni del paciente" << endl;//se solicita el dni y para poder añadirlo a la cola

    cin >> dni;
    // Manejo de errores dni
    while (cin.fail() || dni < 1)
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); // Se ignora toda la entrada anterior hasta encontrar un salto de linea  
        cout << "Ingrese un dni valido: ";
        cin >> dni;
    }

    // Condicion para verificar si el dni ya tiene turno asignado
    if (listaVerificacion.verificarPaciente(dni))
    {
        // Si ya tiene un turno, no puede registrarse de nuevo
        cout << "Usted ya tiene un turno asignado" << endl << endl;
    }
    // Si no esta en la lista lo agrega a la cola de urgencias
    else
    {
        // Si no tiene turno, se registra el turno 
        // a la lista de verificacion y se agrega a la cola de atencion
        listaVerificacion.agregarAlInicio(dni);
        colaPacientesUrgencias.enqueue(dni);
        cout << "Perfecto. Espera a ser llamado! " << endl << endl;
    }
    return;
}

//Funcion para revisar historial medico
void revisarHistorial(Lista<Paciente> listaPacientes)
{

    int contador = 1;
    int dni = 0;
    cout << "Ingrese el DNI del paciente: ";
    cin >> dni;

    // Manejo de errores dni
    while (cin.fail() || dni < 1)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Se ignora toda la entrada anterior hasta encontrar un salto de linea  
        cout << "Ingrese un dni valido: ";
        cin >> dni;
    }

    if (listaPacientes.buscarDNI(dni)) {// busco que el dni en la lista
        // si lo encuntra lo muestra
        Paciente& paciente = listaPacientes.buscarPaciente(dni);
        cout << "Datos del pacientes: " << endl;
        cout << "Nombre y apellido: " << paciente.nombre << " " << paciente.apellido << endl;
        cout << "Edad: " << paciente.edad << endl;
        cout << "Genero del paciente: ";
        if (paciente.Genero == 1)
        {
            cout << "Masculino" << endl;
        }
        else
        {
            cout << "Femenino" << endl;
        }

        // Creamos dos pilas dinamicas para almacenar una copia de las pilas de historial y doctor
        Pila<int> pilaDoctorCopia = paciente.Doctor.copiar();
        Pila<string> pilaHistorialCopia = paciente.historial.copiar();

        // Mientras haya elementos en la pila de historial, mostramos los datos
        while (!pilaDoctorCopia.estaVacia()) {
            cout << "Consulta " << contador << endl;
            cout << "El paciente vino al doctor: ";
            switch (pilaDoctorCopia.pop()) {
            case 1:
                cout << "Cirujano" << endl;
                break;
            case 2:
                cout << "Cardiologo" << endl;
                break;
            case 3:
                cout << "Oftalmologo" << endl;
                break;
            case 4:
                cout << "Traumatologo" << endl;
                break;
            case 5:
                cout << "Odontologo" << endl;
                break;
            case 6:
                cout << "Dentista" << endl;
                break;
            case 7:
                cout << "Dermatologo" << endl;
            default:
                cout << "Guardia" << endl;
                break;
            }
            cout << "Por el motivo: " << pilaHistorialCopia.pop() << endl;
            contador++;
        }
        cout << endl;
    }

    else {
        cout << "Paciente no encontrado" << endl;
    }


}

// Funcion prinpipal
int main() {
    // Se crean las estructuras de datos necesarias
    Lista<Paciente> listaPacientes;
    Lista<int> listaVerificacion;

    Cola<int> colaPacientes;
    Cola<int> colaPacientesUrgencias;

    //Menu de opciones 
    int select = 0;
    while (select != 6) {
        cout << "Ingrese: " << endl;
        cout << "1. Para ingresar paciente a lista de espera" << endl;
        cout << "2. Para atender paciente" << endl;
        cout << "3. Para ingresar un paciente a la cola de urgencias" << endl;
        cout << "4. Revisar el historial medico de un paciente " << endl;
        cout << "5. Mostrar todos los pacientes del dia" << endl;
        cout << "6. Salir " << endl;
        cin >> select;

        // Manejo de errores select
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Se ignora toda la entrada anterior hasta encontrar un salto de linea  
            cout << "Ingrese una opcion valida: ";
            cin >> select;
        }

        switch (select) {
        case 1:
            ingresarPaciente(listaVerificacion, colaPacientes);
            break;
        case 2:
            atenderPaciente(listaVerificacion, listaPacientes, colaPacientes, colaPacientesUrgencias);
            break;
        case 3:
            agregarPacienteDeUrgencia(listaVerificacion, colaPacientesUrgencias);
            break;
        case 4:
            revisarHistorial(listaPacientes);
            break;
        case 5:
            listaPacientes.mostrarLista();
            break;
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