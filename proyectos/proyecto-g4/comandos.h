#ifndef comandos_h
#define comandos_h

#include <string>
using namespace std;


struct NodoComando {
   string tipo_comandos;
   string tipo_movimiento;
   double magnitud;
   string unidad;
   string tipo_analisis;
   string objeto;
   string comentario;

   NodoComando* siguiente; 
};

struct ListaComandos{
   NodoComando* cabeza;
   int tamanio;
};

void inicializar_lista_comandos(ListaComandos& lista);
void liberar_lista_comandos(ListaComandos& lista);
void agregar_comando_movimiento(ListaComandos& lista, const string& tipo_mov, double magnitud, const string& unidad);
void agregar_comando_analisis(ListaComandos& lista, const string& tipo_analisis, const string& objeto, const string& comentario);

struct NodoElemento{
   string tipo;
   double tamanio;
   string unidad;
   double x;
   double y;
   NodoElemento* siguiente;
};

struct ListaElementos{
    NodoElemento* cabeza;
    int tamanio;
};

void inicializar_lista_elementos(ListaElementos& lista);
void liberar_lista_elementos(ListaElementos& lista);
void agregar_elemento_lista(ListaElementos& lista, const string& tipo, double tamanio, const string& unidad, double x, double y);

struct programa {
	bool hay_comandos;
	bool hay_elementos;
	bool elementos_ubicados;
	bool mapa_creado;
	
	ListaComandos lista_comandos;
	ListaElementos lista_elementos;
};


bool es_numero(const string& str);
bool validar_tipo_movimiento(const string& tipo);
bool validar_unidad_distancia(const string& unidad);
bool validar_unidad_angulo(const string& unidad);
bool validar_tipo_analisis(const string& tipo);
bool validar_tipo_elemento(const string& tipo);

double a_metros(double magnitud, const string& unidad);

bool ayuda_comandos(const string palabras_usuario[], int cantidad, programa& p);

void cmd_ayuda(const string parametros[], int cantidad);

void cmd_cargar_comandos(const string parametros[], int cantidad, programa& p);
void cmd_cargar_elementos(const string parametros[], int cantidad, programa& p);

void cmd_agregar_movimiento(const string parametros[], int cantidad, programa& p);
void cmd_agregar_analisis(const string parametros[], int cantidad, programa& p);
void cmd_agregar_elemento(const string parametros[], int cantidad, programa& p);

void cmd_guardar(const string parametros[], int cantidad, programa& p);
void cmd_simular_comandos(const string parametros[], int cantidad, programa& p);

void cmd_ubicar_elementos(const string parametros[], int cantidad, programa& p);
void cmd_en_cuadrante(const string parametros[], int cantidad, programa& p);

void cmd_crear_mapa(const string parametros[], int cantidad, programa& p);
void cmd_ruta_mas_larga(const string parametros[], int cantidad, programa& p);



#endif


