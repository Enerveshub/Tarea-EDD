#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

struct Dato{

    unsigned int Id;      
    char Nombre [50];    
    char Fecha_Nacimiento [11]; 
    int Notas [3];      
    char Curso [7];      
    unsigned short VTR;   
};

char* Leer_archivo(string narch, size_t size){

    ifstream archivo(narch, ios::binary | ios::in);
    if (archivo.is_open()){
        archivo.seekg(0, ios::end);
        size = archivo.tellg();
        archivo.seekg(0, ios::beg);

        char* puntero = new char[size];
        archivo.read(puntero, size);
        archivo.close();

        return puntero;
    }
    else {
        cout<< "No se pudo abrir el archivo";
        size = 0;
        return nullptr;
    }
    
    
}

int main(){

    string nombre_archivo;
    size_t tamano = 0;
    cout << "Ingrese el nombre del archivo que desea abrir (Debe incluir el tipo de extension)";
    cin >> nombre_archivo;
    char* archivo = Leer_archivo(nombre_archivo, tamano);
}

void Menú(){

    std::cout << 
        "1) Agregar un alumno.\n" <<
        "2) Obtener promedio de un estudiante.\n" << 
        "3) Obtener por evaluación de una asignatura.\n" <<
        "4) Obtener los cursos en los que está inscrito un estudiante.\n" <<
        "5) Obtener los reprobados de un curso con cierto VTR.\n" <<
        "6) Generar informe por cursos.\n" <<
        "0) Salir del programa.\n" <<
        "Ingrese su opción: ";  
}

void Mostrar_Datos_Alumno(Dato* datos, int tamanio){

    /*
    *    Descripción: 
    *            Imprimir por consola los datos cargados en el parametro 'datos', mostrando los primeros 5 o menos en caso de que 'tamanio' sea menor a 5.
    *
    *    Parametros:
    *            Dato* datos: Puntero/arreglo que contiene los datos a querer mostrar.
    *            int tamanio: Tamaño del arreglo.
    *    
    *    Retorno:
    *            Función tipo void, no retorna nada.
    *    
    */
    
    std::cout << std::left 
                    << std::setw(8) << "ID" 
                    << std::setw(50) << "NOMBRE" 
                    << std::setw(12) << "CURSO" 
                    << std::setw(17) << "FECHA NAC." 
                    << std::setw(5) << "VTR" 
                    << std::endl;

    for (int i = 0; i < 5 && i < tamanio; i++) {

        std::cout << std::left
                    << std::setw(8) << datos[i].Id 
                    << std::setw(50) << datos[i].Nombre 
                    << std::setw(12) << datos[i].Curso 
                    << std::setw(17) << datos[i].Fecha_Nacimiento 
                    << std::setw(5) << datos[i].VTR 
                    << std::endl;
    }
}
