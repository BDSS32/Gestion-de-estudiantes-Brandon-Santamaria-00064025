#include <iostream>
#include <fstream>
#include <string> 
#include <limits> 
using namespace std;

// --- ESTRUCTURAS DE DATOS ---
struct Direccion {
    string calle;
    int numero;
    string ciudad;
};

struct Estudiante {
    string nombre;
    int edad;
    float notas[5]; // Cambiado a float para poder calcular promedio
    float promedio;
    Direccion direccion; // Estructura anidada
};

// 1. Validar que sea Numero Entero 
int leerEntero() {
    string entrada;
    while (true) {
       
        getline(cin, entrada);

        bool esValido = true;
        if (entrada.empty()) esValido = false;
        
        for (char c : entrada) {
            if (!isdigit(c)) { 
                esValido = false;
                break;
            }
        }

        if (esValido) {
           
            try {
                return stoi(entrada);
            } catch (...) {
                cout << "Numero demasiado grande. Intente de nuevo: ";
            }
        } else {
            cout << "Error: Ingrese solo numeros enteros (sin decimales ni letras): ";
        }
    }
}

// 2. Validar que sea Numero tipo float
float leerFlotante() {
    float numero;
    while (true) {
        if (cin >> numero) {
    cin.ignore(10000, '\n'); 
    return numero;
        } else {
            cout << "Error: Ingrese un numero valido (decimales con punto). Intente de nuevo: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// 3. Validar que el Texto NO tenga numeros
string leerTextoSoloLetras() {
    string texto;
    while (true) {
        getline(cin, texto);
        bool valido = true;
        
        // Revisamos letra por letra
        for (char c : texto) {
           
            if (!isalpha(c) && !isspace(c)) { 
                valido = false;
                break;
            }
        }
        
        if (valido && texto.length() > 0) {
            return texto;
        } else {
            cout << "Error: El texto no puede contener numeros ni simbolos. Intente de nuevo: ";
        }
    }
}


// Variables globales para el manejo simple
const int MAX_ESTUDIANTES = 50;
Estudiante estudiantes[MAX_ESTUDIANTES]; // Arreglo de estructuras
int contador = 0; // Cantidad actual de estudiantes

// --- PROTOTIPOS DE FUNCIONES ---
void registrarEstudiante();
void mostrarEstudiantes();
void buscarEstudiante();
void guardarArchivo();
void cargarArchivo();
void calcularPromedio(int indice);

int main() {
    int opcion;
    bool ejecutando = true; //bandera "encendida"

    cargarArchivo();

    //condicion del ciclo
    do {
        // Se limpia la pantalla para que se vea ordenado
        system("cls"); 

        cout << "\n--- GESTION DE ESTUDIANTES ---" << endl;
        cout << "1. Registrar Estudiante" << endl;
        cout << "2. Mostrar Todos" << endl;
        cout << "3. Buscar por Nombre" << endl;
        cout << "4. Guardar y Salir" << endl;
        cout << "-----------------------------" << endl;
        cout << "Seleccione una opcion: ";
        
       
        opcion = leerEntero(); 

        if (opcion == 1) {
            registrarEstudiante();
            system("pause"); // Pausa para que el usuario lea antes de volver al menu
        } 
        else if (opcion == 2) {
            mostrarEstudiantes();
            system("pause");
        } 
        else if (opcion == 3) {
            buscarEstudiante();
            system("pause");
        } 
        else if (opcion == 4) {
            guardarArchivo();
            cout << "Saliendo del sistema..." << endl;
            ejecutando = false;
        } 
        else {
            cout << "\n[!] ERROR: Opcion invalida (" << opcion << "). Intente de nuevo." << endl;
            system("pause"); 
        }

    } while (ejecutando); //El ciclo se repite MIENTRAS la bandera sea true

    return 0;
}


// --- IMPLEMENTACIÓN DE FUNCIONES ---

void registrarEstudiante() {
    if (contador >= MAX_ESTUDIANTES) {
        cout << "Lista llena, no se pueden agregar mas." << endl;
        return;
    }

    cout << "\n--- Registro ---" << endl;
    
    cout << "Nombre (Solo letras): ";
    estudiantes[contador].nombre = leerTextoSoloLetras();
    
    cout << "Edad: ";
    estudiantes[contador].edad = leerEntero();

    float suma = 0;
    cout << "Ingrese 5 notas:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Nota " << i + 1 << ": ";
        estudiantes[contador].notas[i] = leerFlotante();
        
        while(estudiantes[contador].notas[i] < 0 || estudiantes[contador].notas[i] > 10) {
             cout << "Nota invalida (0-10). Ingrese de nuevo: ";
             estudiantes[contador].notas[i] = leerFlotante();
        }

        suma += estudiantes[contador].notas[i];
    }
    
    estudiantes[contador].promedio = suma / 5.0;

    cout << "Direccion - Calle: ";
    getline(cin, estudiantes[contador].direccion.calle);
    
    cout << "Direccion - Numero de casa: ";
    estudiantes[contador].direccion.numero = leerEntero();
    
    cout << "Direccion - Ciudad (Solo letras): ";
    estudiantes[contador].direccion.ciudad = leerTextoSoloLetras();

    contador++;
    cout << "Estudiante registrado con exito!" << endl;
}

void mostrarEstudiantes() {
    cout << "\n--- Lista de Estudiantes ---" << endl;
    for (int i = 0; i < contador; i++) {
        cout << "Estudiante #" << i + 1 << endl;
        cout << "Nombre: " << estudiantes[i].nombre << endl;
        cout << "Promedio: " << estudiantes[i].promedio << endl;
        cout << "Ciudad: " << estudiantes[i].direccion.ciudad << endl;
        cout << "-------------------------" << endl;
    }
}

void buscarEstudiante() {
    string busqueda;
    cout << "Ingrese nombre a buscar: ";
    getline(cin, busqueda);
    
    bool encontrado = false;
    for (int i = 0; i < contador; i++) {
        // Buscar coincidencia exacta o parcial
        if (estudiantes[i].nombre == busqueda) {
            cout << "\n--- ENCONTRADO ---" << endl;
            cout << "Nombre: " << estudiantes[i].nombre << endl;
            cout << "Edad: " << estudiantes[i].edad << endl;
            cout << "Promedio: " << estudiantes[i].promedio << endl;
            cout << "Direccion: " << estudiantes[i].direccion.calle << " #" 
                 << estudiantes[i].direccion.numero << ", " 
                 << estudiantes[i].direccion.ciudad << endl;
            encontrado = true;
        }
    }
    
    if (!encontrado) {
        cout << "Estudiante no encontrado." << endl;
    }
}

// Manejo de Archivos
void guardarArchivo() {
    ofstream archivo("datos_estudiantes.txt"); // Abrir para escribir
    
    if (archivo.is_open()) {
        // Primero guardamos cuantos estudiantes hay
        archivo << contador << endl;
        
        for (int i = 0; i < contador; i++) {
            archivo << estudiantes[i].nombre << endl;
            archivo << estudiantes[i].edad << endl;
            for(int j=0; j<5; j++){
                archivo << estudiantes[i].notas[j] << endl;
            }
            archivo << estudiantes[i].promedio << endl;
            archivo << estudiantes[i].direccion.calle << endl;
            archivo << estudiantes[i].direccion.numero << endl;
            archivo << estudiantes[i].direccion.ciudad << endl;
        }
        archivo.close(); // Cerrar archivo
        cout << "Informacion guardada en 'datos_estudiantes.txt'" << endl;
    } else {
        cout << "Error al crear el archivo." << endl;
    }
}

void cargarArchivo() {
    ifstream archivo("datos_estudiantes.txt"); // Abrir para leer
    
    if (archivo.is_open()) {
        archivo >> contador;
        archivo.ignore(); // Limpiar el enter después del numero
        
        for (int i = 0; i < contador; i++) {
            getline(archivo, estudiantes[i].nombre);
            archivo >> estudiantes[i].edad;
            
            float suma = 0;
            for(int j=0; j<5; j++){
                archivo >> estudiantes[i].notas[j];
                suma += estudiantes[i].notas[j];
            }
            archivo >> estudiantes[i].promedio; 
            archivo.ignore(); 

            getline(archivo, estudiantes[i].direccion.calle);
            archivo >> estudiantes[i].direccion.numero;
            archivo.ignore();
            getline(archivo, estudiantes[i].direccion.ciudad);
        }
        archivo.close();
        cout << "Datos cargados: " << contador << " estudiantes." << endl;
    } else {
        cout << "No se encontro archivo previo. Iniciando vacio." << endl;
    }
}