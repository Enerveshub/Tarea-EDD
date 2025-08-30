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
/*Esta funcion recibe el string con el nombre del archivo y una direccion de memoria apuntando a un puntero fuera de la funcion, el cual determina el
    tamaño del arreglo en el que se guardaran los datos del archivo que se abre*/
char* Leer_archivo(string narch, size_t &size){

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
     /*En caso de fallar, la funcion regresa un puntero nulo y te avisa que no se pudo abrir el archivo*/
    else {
        cout<< "No se pudo abrir el archivo";
        size = 0;
        return nullptr;
    }
    
    
}
// funcion que elimina los datos duplicados 
void Eliminar_Duplicados ( Dato *& datos , int & cantidad_datos ) {
    int n_tamaño = 0;
    for (int i=0; i < cantidad_datos; i++){
        bool duplicado=false;
        for (int g=0; g < n_tamaño; g++){
            // compara con id y curso para eliminar duplicados
            if (datos[i].Id == datos[g].Id && datos[i].Curso == datos[g].Curso){
                duplicado=true;
                break;
            };
        };
        if (!duplicado){
           datos[n_tamaño++] = datos[i];
       };
    };
    
    cantidad_datos = n_tamaño;
};

void Agregar_Alumno( Dato *& datos , int &cantidad_datos){
    Dato nuevo;

    cout << "Ingrese los datos del estudiante:\n";
    //Ingreso de datos
    do {
        cout << "ID (Número mayor a 1500): ";
        cin >> nuevo.Id;
        cin.ignore();
    } while (nuevo.Id <= 1500);

    cout << "Primer nombre y primer apellido: ";
    cin.getline(nuevo.Nombre, 50);

    cout << "Fecha de nacimiento: ";
    cin.getline(nuevo.Fecha_Nacimiento, 11);

    cout << "Notas de las 3 evaluaciones: ";
    for (int i = 0; i < 3; i++) {
        cin >> nuevo.Notas[i];
    }
    cin.ignore();

    cout << "Sigla del curso: ";
    cin.getline(nuevo.Curso, 7);
    do {
        cout << "VTR: ";
        cin >> nuevo.VTR;
        cin.ignore();
    } while (nuevo.VTR < 1 || nuevo.VTR > 3);

    // arreglar arreglo (xd) y agregar alumno
    Dato* nuevo_arreglo = new Dato[cantidad_datos + 1];
    for (int i = 0; i < cantidad_datos; i++) {
        nuevo_arreglo[i] = datos[i];
    }
    nuevo_arreglo[cantidad_datos] = nuevo;
    delete[] datos;
    datos = nuevo_arreglo;
    cantidad_datos++;

    cout << "\nAlumno ingresado con éxito.\n";
};

int Calcular_Promedio_Estudiante(Dato* datos, int cantidad_de_datos){
    unsigned int id_alumno;
    char asignatura[7];
    bool almn = false;
    bool asg = false;
    cout<< "Ingrese los datos del estudiante:";
    cout << "Ingrese el ID del alumno: ";
    cin >> id_alumno;
    cout << "Ingrese el curso a buscar: ";
    cin >> asignatura;

    for (int i = 0 ; i<cantidad_de_datos; i++){
        if (datos[i].Id == id_alumno){
            almn = true;
        }
        if (strcmp(asignatura, datos[i].Curso)==0){
            asg = true;
        }
        if ((datos[i].Id == id_alumno)&& (strcmp(asignatura, datos[i].Curso)==0)){
            int suma = 0;
            for (int j = 0; j<3; j++){

                suma += datos[i].Notas[j];

            }
        cout<<"El promedio del estudiante es: "<< round(suma/3)<<endl;
        return round(suma/3);
        }
    }
    if((almn == false) and (asg ==true)){
        cout<<"No existe un estudiante de ID "<<id_alumno<<" en el curso "<< asignatura<<"."<<endl;
        return -1;
    }
    if(asg == false){
        cout<<"No existe el curso "<< asignatura;
        return -1;
    }
    cout<<"Error";
    return -1;
};

void Listar_Cursos_Estudiante(Dato* datos, int cantidad_de_datos){
    int id_estudiante;
    cout<<"Ingrese la ID del alumno a buscar: "<< endl;
    cin>> id_estudiante;
    string cursos = "";
    for (int i = 0; i < cantidad_de_datos; i++){

        if (id_estudiante == datos[i].Id){
            cursos += string(datos[i].Curso);
            cursos += " ";
        }
    }
    if(cursos.empty()){
        cout<<"No existe registro para el estudiante con Id: "<< id_estudiante<< endl;
    }
    else{
        cout<< "Las asignaturas inscritas por el estudiante son: "<< cursos<< endl;
    }
};

int* Calcular_Promedio_Asignatura(Dato* datos, int cantidad_de_datos, char* asignatura_a_buscar){
    char asignatura_a_buscar[7];
    cout<<"Ingrese la asignatura a calcular el promedio por evaluacion";
    int contador = 0;
    int promedios[3];
    bool no_existe = true;
    for (int i = 0; i<cantidad_de_datos; i++){
        if(strcmp(asignatura_a_buscar, datos[i].Curso)==0){
            int suma = 0;
            no_existe = false;
            for (int j = 0; j<3; j++){
                promedios[j] += datos[i].Notas[j];
            }
            contador += 1;
        }
    }
    for (int j = 0; j<3; j++){
        promedios[j] = promedios[j]/3;
    }
    if (no_existe){
        cout<<"Error, La asignatura"<< asignatura_a_buscar<<"No existe";
        return nullptr;
    }
    cout<<"El promedio por evaluacion de la asignatura "<< asignatura_a_buscar<<" es:"<<promedios[0], promedios[1],promedios[2];
    return promedios;
};

void Menú(){

    std::cout << 
        "1) Agregar un alumno.\n" <<
        "2) Obtener promedio de un estudiante.\n" << 
        "3) Obtener promedio por evaluación de una asignatura.\n" <<
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

int main(){

    string nombre_archivo;
    size_t tamaño = 0;
    cout << "Ingrese el nombre del archivo que desea abrir";
    cin >> nombre_archivo;
    char* archivo = Leer_archivo(nombre_archivo, tamaño);
    
      Dato* datos = nullptr;
    int cantidad_datos = 0;
    int id_alumno;
    char asignatura_a_buscar[7];


    if (archivo && tamaño > 0) {
        int cantidad_datos = tamaño / sizeof(Dato);
        Dato* datos = reinterpret_cast<Dato*>(archivo);

        Eliminar_Duplicados(datos, cantidad_datos);
        

        delete[] archivo;
    }
    // MENU
    int opcion;
    do {
        Menú();
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            // aca podi agregar los casos para cada funcion
            case 1:
                Agregar_Alumno(datos, cantidad_datos);
                break;
            case 2:
                Calcular_Promedio_Estudiante(datos, cantidad_datos);
                break;
            case 3:
                Calcular_Promedio_Asignatura(datos, cantidad_datos, asignatura_a_buscar);
                break;
            case 4:
                Listar_Cursos_Estudiante(datos, cantidad_datos);
                break;

            case 0:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción inválida. Intente nuevamente.\n";
        }
    } while (opcion != 0);

    if (datos) {
        delete[] datos;
    }
    if (archivo) {
        delete[] archivo;
    }
    return 0;

}
