#ifndef CURIOSITY_H
#define CURIOSITY_H

#include <string>
#include <vector>
#include <iostream>
#include "Comando.h"
#include "Elemento.h"

using namespace std;

class Curiosity {

private:

    vector<Comando> listadeComandos;
    vector<Elemento<double,double>> listadeElementos;
    Punto<double> posicion;

public:

    // Constructor
    Curiosity();

    // --- Getters y Setters ---
    const vector<Comando>& getListaComandos() const;
    const vector<Elemento<double,double>>& getListaElementos() const;
    Punto<double> getPosicion() const;
    void setPosicion(const Punto<double>& nuevoPunto);

    // Utilidades de validación
    bool esNumero(const string& str);
    bool esUnidadValida(const string& unidad);
    string unidadToString(const UnidadMedida& u);
    UnidadMedida obtenerUnidad(const string u);

    // --- Manejadores de Comandos ---
    // Todos reciben el vector de argumentos: [comando, param1, param2, ...]

    void cargar_comandos(const vector<string>& args);  // args: [nombre_archivo]
    void cargar_elementos(const vector<string>& args); // args: [nombre_archivo]
    void agregar_movimiento(const vector<string>& args); // args: [tipo, magnitud, unidad]
    void agregar_analisis(const vector<string>& args);   // args: [tipo, objeto, comentario]
    void agregar_elemento(const vector<string>& args);   // args: [tipo, tamaño, unidad, x, y]
    void guardar(const vector<string>& args);            // args: [tipo_archivo, nombre_archivo]
    void simular_comandos(const vector<string>& args);   // args: [coordX, coordY]
    void ubicar_elementos(const vector<string>& args);   // Sin parámetros adicionales
    void en_cuadrante(const vector<string>& args);       // args: [x1, x2, y1, y2]
    void crear_mapa(const vector<string>& args);         // args: [coeficiente]
    void ruta_mas_larga(const vector<string>& args);     // Sin parámetros adicionales
    void ayuda(const vector<string>& args);              // args opcional: [comando]

};

#endif