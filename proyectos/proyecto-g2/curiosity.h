#ifndef CURIOSITY_H
#define CURIOSITY_H

#include <vector>
#include <string>

using namespace std;

struct Movimiento
{
    string tipo;
    double magnitud;
    string unidad;
};

struct Analisis
{
    string tipo;
    string objeto;
    string comentario;
};

struct Elemento
{
    string tipo;
    double tamano;
    string unidad;
    double x;
    double y;
};

class Curiosity
{

private:
    vector<Movimiento> movimientos;
    vector<Analisis> analisis;
    vector<Elemento> elementos;

public:
    void cargarComandos(string archivo);
    void cargarElementos(string archivo);

    void agregarMovimiento(string tipo, double magnitud, string unidad);
    void agregarAnalisis(string tipo, string objeto, string comentario);

    void agregarElemento(string tipo, double tam, string unidad, double x, double y);

    void guardar(string tipo, string archivo);

    void simularComandos(double x, double y);

    void ayuda(string comando_especifico = "");
};

#endif