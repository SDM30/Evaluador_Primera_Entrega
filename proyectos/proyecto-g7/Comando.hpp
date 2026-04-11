#ifndef Comandos_HXX
#define Comandos_HXX

#include <string>
using namespace std;

void iniciarConsola();
void ayuda();
void ayudaEspecifica(string comando);

// Firmas de las funciones

void agregarMovimiento(String tipo, double magnitud, string unidad);
void agregarAnalisis(String tipo, string objeto, string comentario);
void agregarElemento(String tipo, double tam, string unidadMedida, float coord_x, float coord_y);
void guardar(String tipoArchivo, string nombreArchivo);
void simularComandos(float coord_x, float coord_y);
void ubicarElementos(); // no tiene parametros :/
void enCuadrante(float coord_x1, float coord_x2, float coord_y1, float coord_y2);
void crearMapa(float coeficienteConectividad);
void rutaMasLarga();
void cargarComandos(string nombreArchivo);
void cargarElementos(string nombreArchivo);
void salir(); //tampoco tiene parametros (logico)

#endif