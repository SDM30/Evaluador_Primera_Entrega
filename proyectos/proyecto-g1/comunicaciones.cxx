#include "comunicaciones.h"
#include "interfaz.h"
#include <sstream> //Para convertir el de agregar elemento
#include <iostream>


void Comunicaciones::cargarComandos(std::string archivo)
{
    try
    {
        this -> gestor.cargarComandos(archivo);
    }
    catch(const std::invalid_argument &e)
    {
        Interfaz::printError("Error en el archivo por tipo de dato erroneo");
        std::cerr << "";
        return;
    }
    catch(const std::exception &e)
    {
        Interfaz::printError("Error al leer el archivo!");
        return;
    }
    return;
    
}

void Comunicaciones::cargarElementos(std::string archivo)
{
    try
    {
        this->gestor.cargarElementos(archivo);
    }
    catch(const std::exception& e)
    {
        Interfaz::printError("Error inesperado: " + std::string(e.what()));
    }
}

void Comunicaciones::agregarElemento(std::string tipo, std::string tam, std::string unidad, std::string x, std::string y)
{
    this->gestor.agregarElemento(tipo, tam, unidad, x, y);
}

void Comunicaciones::agregarAnalisis(std::string analisis, std::string objeto, std::string comentario)
{
    this->gestor.agregarAnalisis(analisis, objeto, comentario);
}

void Comunicaciones::agregarMovimiento(std::string movimiento, std::string magnitud, std::string unidad)
{
    this->gestor.agregarMovimiento(movimiento, magnitud, unidad);
}

void Comunicaciones::guardar(std::string tipo, std::string nombre)
{
    this->gestor.guardar(tipo, nombre);
}

void Comunicaciones::simularComandos(std::string x, std::string y)
{
    this->gestor.simularComandos(x, y);
}


/*
// Brooo esta parte es full simulada, entonces vamos con mucha fé
void cargarComandos(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    
    // Verificar si el archivo se puede abrir
    if (!archivo.is_open()) {
        cout << "(Archivo erroneo) " << nombreArchivo << " no se encuentra o no puede leerse." << endl;
        return;
    }
    
    // Contar lineas no vacias en el archivo
    int contador = 0;
    string linea;
    
    while (getline(archivo, linea)) {
        // Brooo esta parte es full ia, pq puede que hayan lineas vacias entonces por eso se usa isspace
        bool soloEspacios = true;
        for (char c : linea) {
            if (!isspace(static_cast<unsigned char>(c))) {
                soloEspacios = false;
                break;
            }
        }

        if (!soloEspacios) contador++;
    }
    
    archivo.close();
    
    if (contador == 0) {
        cout << "(Archivo vacio) " << nombreArchivo << " no contiene comandos." << endl;
        return;
    }
    
    // Exito
    cout << "(Resultado exitoso) " << contador << " comandos cargados correctamente desde " << nombreArchivo << "." << endl;
}
*/
