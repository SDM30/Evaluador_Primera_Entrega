#include "comandos.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

bool es_numero(const string& str) {
    if (str.empty()) return false;
    int inicio = 0;
   
    if (str[0] == '-' || str[0] == '+') inicio = 1;
    if (inicio >= (int)str.length()) return false;
   
    bool tiene_punto = false;
    for (int i = inicio; i < (int)str.length(); i++) {
        if (str[i] == '.') {
            if (tiene_punto) return false; // Más de un punto
            tiene_punto = true;
        } else if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }
    return true;
}

bool validar_tipo_movimiento(const string& tipo) {
    return (tipo == "avanzar" || tipo == "girar");
}

bool validar_unidad_distancia(const string& unidad) {
    return (unidad == "cm" || unidad == "dm" || unidad == "m" || unidad == "km");
}

bool validar_unidad_angulo(const string& unidad) {
    return (unidad == "grd" || unidad == "rad");
}

bool validar_tipo_analisis(const string& tipo) {
    return (tipo == "fotografiar" || tipo == "composicion" || tipo == "perforar");
}

bool validar_tipo_elemento(const string& tipo) {
    return (tipo == "roca" || tipo == "crater" || tipo == "monticulo" || tipo == "duna");
}

double a_metros(double magnitud, const string& unidad) {
    if (unidad == "cm")  return magnitud / 100.0;
    if (unidad == "dm")  return magnitud / 10.0;
    if (unidad == "km")  return magnitud * 1000.0;
    return magnitud; 
}

static double a_grados(double magnitud, const string& unidad) {
    if (unidad == "rad") return magnitud * (180.0 / M_PI);
    return magnitud; // "grd"
}

void inicializar_lista_comandos(ListaComandos& lista) {
    lista.cabeza  = nullptr;
    lista.tamanio = 0;
}

void liberar_lista_comandos(ListaComandos& lista) {
    NodoComando* actual = lista.cabeza;
    while (actual != nullptr) {
        NodoComando* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    lista.cabeza  = nullptr;
    lista.tamanio = 0;
}

void agregar_comando_movimiento(ListaComandos& lista,
                                const string& tipo_mov,
                                double magnitud,
                                const string& unidad) {
    NodoComando* nuevo = new NodoComando();
    nuevo->tipo_comando    = "movimiento";
    nuevo->tipo_movimiento = tipo_mov;
    nuevo->magnitud        = magnitud;
    nuevo->unidad          = unidad;
    nuevo->siguiente       = nullptr;

    if (lista.cabeza == nullptr) {
        lista.cabeza = nuevo;
    } else {
        NodoComando* actual = lista.cabeza;
        while (actual->siguiente != nullptr) actual = actual->siguiente;
        actual->siguiente = nuevo;
    }
    lista.tamanio++;
}

void agregar_comando_analisis(ListaComandos& lista, const string& tipo_analisis, const string& objeto, const string& comentario) {
    NodoComando* nuevo = new NodoComando();
    nuevo->tipo_comando   = "analisis";
    nuevo->tipo_analisis  = tipo_analisis;
    nuevo->objeto         = objeto;
    nuevo->comentario     = comentario;
    nuevo->magnitud       = 0;
    nuevo->siguiente      = nullptr;

    if (lista.cabeza == nullptr) {
        lista.cabeza = nuevo;
    } else {
        NodoComando* actual = lista.cabeza;
        while (actual->siguiente != nullptr) actual = actual->siguiente;
        actual->siguiente = nuevo;
    }
    lista.tamanio++;
}

void inicializar_lista_elementos(ListaElementos& lista) {
    lista.cabeza  = nullptr;
    lista.tamanio = 0;
}

void liberar_lista_elementos(ListaElementos& lista) {
    NodoElemento* actual = lista.cabeza;
    while (actual != nullptr) {
        NodoElemento* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    lista.cabeza  = nullptr;
    lista.tamanio = 0;
}

void agregar_elemento_lista(ListaElementos& lista, const string& tipo, double tamanio, const string& unidad, double x, double y) {
    NodoElemento* nuevo = new NodoElemento();
    nuevo->tipo          = tipo;
    nuevo->tamanio       = tamanio;
    nuevo->unidad        = unidad;
    nuevo->x    = x;
    nuevo->y    = y;
    nuevo->siguiente     = nullptr;

    if (lista.cabeza == nullptr) {
        lista.cabeza = nuevo;
    } else {
        NodoElemento* actual = lista.cabeza;
        while (actual->siguiente != nullptr) actual = actual->siguiente;
        actual->siguiente = nuevo;
    }
    lista.tamanio++;
}

static bool parsear_linea_comando(const string& linea, string& tipo_cmd, string& campo1, string& campo2, double& magnitud, string& campo3) {
    string tokens[8];
    int nTok = 0;
    string tok_actual = "";
    bool en_comillas = false;

    for (int i = 0; i < (int)linea.length() && nTok < 8; i++) {
        char c = linea[i];
        if (c == '\'') {
            en_comillas = !en_comillas;
            tok_actual += c;
        } else if (en_comillas) {
            tok_actual += c;
        } else if (c == ' ' || c == '\t') {
            if (!tok_actual.empty()) {
                tokens[nTok++] = tok_actual;
                tok_actual = "";
            }
        } else {
            tok_actual += c;
        }
    }
    if (!tok_actual.empty() && nTok < 8) tokens[nTok++] = tok_actual;

    if (nTok < 2) return false;

    if ((tokens[0] == "avanzar" || tokens[0] == "girar") && nTok == 3) {
        bool unidad_ok = (tokens[0] == "avanzar")
                         ? validar_unidad_distancia(tokens[2])
                         : validar_unidad_angulo(tokens[2]);
        if (!es_numero(tokens[1]) || !unidad_ok) return false;
        tipo_cmd = "movimiento";
        campo1   = tokens[0]; 
        magnitud = stod(tokens[1]);
        campo3   = tokens[2];
        return true;
    }

    if (validar_tipo_analisis(tokens[0]) && (nTok == 2 || nTok == 3)) {
        if (nTok == 3) {
            const string& com = tokens[2];
            if (com.length() < 2 || com[0] != '\'' || com[com.length()-1] != '\'')
                return false;
            campo2 = com;
        } else {
            campo2 = "";
        }
        tipo_cmd = "analisis";
        campo1   = tokens[0]; 
        campo3   = tokens[1]; 
        return true;
    }

    return false;
}


void cmd_ayuda (const string parametros[], int cantidad)
{
	if (cantidad == 0){
		cout << "Comandos disponibles:\n";
	        cout << "  ayuda\n";
        	cout << "  ayuda <comando>\n";
        	cout << "  salir\n";
	        cout << "  cargar_comandos <archivo>\n";
       		cout << "  cargar_elementos <archivo>\n";
        	cout << "  agregar_movimiento <tipo> <magnitud> <unidad>\n";
        	cout << "  agregar_analisis <tipo> <objeto> [comentario]\n";
        	cout << "  agregar_elemento <tipo> <tam> <unidad> <x> <y>\n";
        	cout << "  guardar <comandos|elementos> <archivo>\n";
        	cout << "  simular_comandos <x> <y>\n";
        	cout << "  ubicar_elementos\n";
        	cout << "  en_cuadrante <x1> <x2> <y1> <y2>\n";
        	cout << "  crear_mapa <coef>\n";
        	cout << "  ruta_mas_larga\n";
        return;
    }
	    if (cantidad == 1) {
        const string& c = parametros[0];

        if (c == "ayuda") {
            cout << "Comando: ayuda [comando]\n";
            cout << "Descripción: Muestra la lista de comandos disponibles o ayuda específica de un comando.\n";
        } else if (c == "salir") {
            cout << "Comando: salir\n";
            cout << "Descripción: Termina la ejecución de la aplicación.\n";
        } else if (c == "cargar_comandos") {
            cout << "Comando: cargar_comandos <archivo>\n";
            cout << "Descripción: Carga en memoria los comandos de desplazamiento contenidos en el archivo.\n";
            cout << "Parámetros:\n";
            cout << "  <archivo>: Nombre del archivo que contiene los comandos.\n";
        } else if (c == "cargar_elementos") {
            cout << "Comando: cargar_elementos <archivo>\n";
            cout << "Descripción: Carga en memoria los datos de puntos de interés contenidos en el archivo.\n";
            cout << "Parámetros:\n";
            cout << "  <archivo>: Nombre del archivo que contiene los elementos.\n";
        } else if (c == "agregar_movimiento") {
            cout << "Comando: agregar_movimiento <tipo> <magnitud> <unidad>\n";
            cout << "Descripción: Agrega un comando de movimiento a la lista de comandos del robot.\n";
            cout << "Parámetros:\n";
            cout << "  <tipo>: Tipo de movimiento (avanzar o girar).\n";
            cout << "  <magnitud>: Valor del movimiento.\n";
            cout << "  <unidad>: Unidad de medida (cm, dm, m, km para avanzar; grd, rad para girar).\n";
        } else if (c == "agregar_analisis") {
            cout << "Comando: agregar_analisis <tipo> <objeto> [comentario]\n";
            cout << "Descripción: Agrega un comando de análisis a la lista de comandos del robot.\n";
            cout << "Parámetros:\n";
            cout << "  <tipo>: Tipo de análisis (fotografiar, composicion o perforar).\n";
            cout << "  <objeto>: Nombre del elemento a analizar.\n";
            cout << "  [comentario]: Comentario opcional entre comillas simples.\n";
        } else if (c == "agregar_elemento") {
            cout << "Comando: agregar_elemento <tipo> <tam> <unidad> <x> <y>\n";
            cout << "Descripción: Agrega un elemento a la lista de puntos de interés.\n";
            cout << "Parámetros:\n";
            cout << "  <tipo>: Tipo de elemento (roca, crater, monticulo o duna).\n";
            cout << "  <tam>: Tamaño del elemento.\n";
            cout << "  <unidad>: Unidad de medida (cm, dm, m, km).\n";
            cout << "  <x>: Coordenada x del elemento.\n";
            cout << "  <y>: Coordenada y del elemento.\n";
        } else if (c == "guardar") {
            cout << "Comando: guardar <tipo> <archivo>\n";
            cout << "Descripción: Guarda en archivo la información solicitada.\n";
            cout << "Parámetros:\n";
            cout << "  <tipo>: Tipo de información (comandos o elementos).\n";
            cout << "  <archivo>: Nombre del archivo donde guardar.\n";
        } else if (c == "simular_comandos") {
            cout << "Comando: simular_comandos <x> <y>\n";
            cout << "Descripción: Simula el resultado de los comandos de movimiento desde una posición inicial.\n";
            cout << "Parámetros:\n";
            cout << "  <x>: Coordenada x inicial del robot.\n";
            cout << "  <y>: Coordenada y inicial del robot.\n";
        } else if (c == "ubicar_elementos") {
            cout << "Comando: ubicar_elementos\n";
            cout << "Descripción: Ubica los elementos en una estructura jerárquica para consultas geográficas.\n";
        } else if (c == "en_cuadrante") {
            cout << "Comando: en_cuadrante <x1> <x2> <y1> <y2>\n";
            cout << "Descripción: Retorna los elementos dentro del cuadrante geográfico especificado.\n";
            cout << "Parámetros:\n";
            cout << "  <x1>: Coordenada x mínima del cuadrante.\n";
            cout << "  <x2>: Coordenada x máxima del cuadrante.\n";
            cout << "  <y1>: Coordenada y mínima del cuadrante.\n";
            cout << "  <y2>: Coordenada y máxima del cuadrante.\n";
        } else if (c == "crear_mapa") {
            cout << "Comando: crear_mapa <coef>\n";
            cout << "Descripción: Genera un mapa conectando elementos según el coeficiente de conectividad.\n";
            cout << "Parámetros:\n";
            cout << "  <coef>: Coeficiente de conectividad (valor entre 0 y 1).\n";
        } else if (c == "ruta_mas_larga") {
            cout << "Comando: ruta_mas_larga\n";
            cout << "Descripción: Identifica los dos componentes más alejados en el mapa y la ruta que los conecta.\n";
        } else {
            cout << "Error: comando no reconocido.\n";
        }
        return;
	}

	        cout << "Error: número de parámetros inválido.\n";
}

bool ayuda_comandos(const string palabras_usuario[],int cantidad, programa& p){
	    if (cantidad <= 0) return false;

    const string& comando = palabras_usuario[0];

    if (comando == "salir") return true;

    const int MAX_PARAMETROS = 32;
    string parametros[MAX_PARAMETROS];
    int nParam = 0;

    for (int i = 1; i < cantidad && nParam < MAX_PARAMETROS; i++) {
        parametros[nParam++] = palabras_usuario[i];
    }


    if (comando == "ayuda") { cmd_ayuda(parametros, nParam); return false; }
    if (comando == "cargar_comandos") { cmd_cargar_comandos(parametros, nParam, p); return false; }
    if (comando == "cargar_elementos") { cmd_cargar_elementos(parametros, nParam, p); return false; }
    if (comando == "agregar_movimiento") { cmd_agregar_movimiento(parametros, nParam, p); return false; }
    if (comando == "agregar_analisis") { cmd_agregar_analisis(parametros, nParam, p); return false; }
    if (comando == "agregar_elemento") { cmd_agregar_elemento(parametros, nParam, p); return false; }
    if (comando == "guardar") { cmd_guardar(parametros, nParam, p); return false; }
    if (comando == "simular_comandos") { cmd_simular_comandos(parametros, nParam, p); return false; }
    if (comando == "ubicar_elementos") { cmd_ubicar_elementos(parametros, nParam, p); return false; }
    if (comando == "en_cuadrante") { cmd_en_cuadrante(parametros, nParam, p); return false; }
    if (comando == "crear_mapa") { cmd_crear_mapa(parametros, nParam, p); return false; }
    if (comando == "ruta_mas_larga") { cmd_ruta_mas_larga(parametros, nParam, p); return false; }

    cout << "Error: comando no reconocido.\n";
    return false;
}

void cmd_cargar_comandos(const string parametros[], int cantidad, programa& p)
{
     if (cantidad != 1) {
        cout << "Error: uso correcto -> cargar_comandos <archivo>\n";
        return;
    }

    const string& nombre = parametros[0];
    ifstream archivo(nombre.c_str());
    if (!archivo.is_open()) {
        cout << "(Archivo erroneo) " << nombre << " no se encuentra o no puede leerse.\n";
        return;
    }

    liberar_lista_comandos(p.lista_comandos);
    p.hay_comandos = false;

    string linea;
    int cargados = 0;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        bool solo_espacios = true;
        for (char c : linea) if (c != ' ' && c != '\t' && c != '\r') { solo_espacios = false; break; }
        if (solo_espacios) continue;

        if (!linea.empty() && linea.back() == '\r') linea.pop_back();

        string tipo_cmd, campo1, campo2, campo3;
        double magnitud = 0;
        if (parsear_linea_comando(linea, tipo_cmd, campo1, campo2, magnitud, campo3)) {
            if (tipo_cmd == "movimiento") {
                agregar_comando_movimiento(p.lista_comandos, campo1, magnitud, campo3);
            } else {
                agregar_comando_analisis(p.lista_comandos, campo1, campo3, campo2);
            }
            cargados++;
        }
    }

    archivo.close();

    if (cargados == 0) {
        cout << "(Archivo vacio) " << nombre << " no contiene comandos.\n";
        return;
    }

    p.hay_comandos = true;
    cout << "(Resultado exitoso) " << cargados << " comandos cargados correctamente desde " << nombre << ".\n";
}

void cmd_cargar_elementos(const string parametros[], int cantidad, programa& p)
{
    if (cantidad != 1) {
        cout << "Error: uso correcto -> cargar_elementos <archivo>\n";
        return;
    }

    const string& nombre = parametros[0];
    ifstream archivo(nombre.c_str());
    if (!archivo.is_open()) {
        cout << "(Archivo erroneo) " << nombre << " no se encuentra o no puede leerse.\n";
        return;
    }

    liberar_lista_elementos(p.lista_elementos);
    p.hay_elementos      = false;
    p.elementos_ubicados = false;
    p.mapa_creado        = false;

    string linea;
    int cargados = 0;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        if (!linea.empty() && linea.back() == '\r') linea.pop_back();

        string tokens[6];
        int nTok = 0;
        string tok = "";
        for (char c : linea) {
            if (c == ' ' || c == '\t') {
                if (!tok.empty()) { tokens[nTok++] = tok; tok = ""; }
            } else {
                tok += c;
            }
            if (nTok >= 6) break;
        }
        if (!tok.empty() && nTok < 6) tokens[nTok++] = tok;

        if (nTok != 5) continue;
        if (!validar_tipo_elemento(tokens[0])) continue;
        if (!es_numero(tokens[1]))             continue;
        if (!validar_unidad_distancia(tokens[2])) continue;
        if (!es_numero(tokens[3]) || !es_numero(tokens[4])) continue;

        double tam = stod(tokens[1]);
        double x   = stod(tokens[3]);
        double y   = stod(tokens[4]);

        agregar_elemento_lista(p.lista_elementos, tokens[0], tam, tokens[2], x, y);
        cargados++;
    }

    archivo.close();

    if (cargados == 0) {
        cout << "(Archivo vacio) " << nombre << " no contiene elementos.\n";
        return;
    }

    p.hay_elementos = true;
    cout << "(Resultado exitoso) " << cargados << " elementos cargados correctamente desde " << nombre << ".\n";
}

void cmd_agregar_movimiento(const string parametros[], int cantidad, programa& p)
{
    if (cantidad != 3) { 
        cout << "(Formato erróneo) La información del movimiento no corresponde a los datos esperados (tipo, magnitud, unidad).\n"; 
        return; 
    }
    
   
    if (!validar_tipo_movimiento(parametros[0])) {
        cout << "(Formato erróneo) La información del movimiento no corresponde a los datos esperados (tipo, magnitud, unidad).\n"; 
        return;
    }
    
   
    if (!es_numero(parametros[1])) {
        cout << "(Formato erróneo) La información del movimiento no corresponde a los datos esperados (tipo, magnitud, unidad).\n"; 
        return;
    }
    
   
    bool unidad_valida = (parametros[0] == "avanzar")
                         ? validar_unidad_distancia(parametros[2])
                         : validar_unidad_angulo(parametros[2]);
    if (!unidad_valida) {
        cout << "(Formato erroneo) La informacion del movimiento no corresponde a los datos esperados (tipo, magnitud, unidad).\n";
        return;
    }

    double magnitud = stod(parametros[1]);
    agregar_comando_movimiento(p.lista_comandos, parametros[0], magnitud, parametros[2]);
    p.hay_comandos = true;
    cout << "(Resultado exitoso) El comando de movimiento ha sido agregado exitosamente.\n";
}

void cmd_agregar_analisis(const string parametros[], int cantidad, programa& p)
{
    if (cantidad != 2 && cantidad != 3) { 
        cout << "(Formato erróneo) La información del análisis no corresponde a los datos esperados (tipo, objeto, comentario).\n"; 
        return; 
    }
    
   
    if (!validar_tipo_analisis(parametros[0])) {
        cout << "(Formato erróneo) La información del análisis no corresponde a los datos esperados (tipo, objeto, comentario).\n"; 
        return;
    }
    
    string comentario = "";
    if (cantidad == 3) {
        const string& comentario = parametros[2];
        if (comentario.length() < 2 || comentario[0] != '\'' || comentario[comentario.length()-1] != '\'') {
            cout << "(Formato erróneo) La información del análisis no corresponde a los datos esperados (tipo, objeto, comentario).\n"; 
            return;
        }
    }
    agregar_comando_analisis(p.lista_comandos, parametros[0], parametros[1], comentario);
    p.hay_comandos = true;
    cout << "(Resultado exitoso) El comando de análisis ha sido agregado exitosamente.\n";
}

void cmd_agregar_elemento(const string parametros[], int cantidad, programa& p)
{
    if (cantidad != 5) { 
        cout << "(Formato erróneo) La información del elemento no corresponde a los datos esperados (tipo, tamaño, unidad, x, y).\n"; 
        return; 
    }
    

    if (!validar_tipo_elemento(parametros[0])) {
        cout << "(Formato erróneo) La información del elemento no corresponde a los datos esperados (tipo, tamaño, unidad, x, y).\n"; 
        return;
    }
    
  
    if (!es_numero(parametros[1])) {
        cout << "(Formato erróneo) La información del elemento no corresponde a los datos esperados (tipo, tamaño, unidad, x, y).\n"; 
        return;
    }
    
   
    if (!validar_unidad_distancia(parametros[2])) {
        cout << "(Formato erróneo) La información del elemento no corresponde a los datos esperados (tipo, tamaño, unidad, x, y).\n"; 
        return;
    }
    
   
    if (!es_numero(parametros[3]) || !es_numero(parametros[4])) {
        cout << "(Formato erróneo) La información del elemento no corresponde a los datos esperados (tipo, tamaño, unidad, x, y).\n"; 
        return;
    }
    
    double tam = stod(parametros[1]);
    double x   = stod(parametros[3]);
    double y   = stod(parametros[4]);
    agregar_elemento_lista(p.lista_elementos, parametros[0], tam, parametros[2], x, y);
    p.hay_elementos = true;
    p.elementos_ubicados = false;
    p.mapa_creado = false;
    cout << "(Resultado exitoso) El elemento ha sido agregado exitosamente.\n";
}

void cmd_guardar(const string parametros[], int cantidad, programa& p)
{
    if (cantidad != 2) {
        cout << "Error: uso correcto -> guardar <comandos|elementos> <archivo>\n";
        return;
    }

    const string& tipo   = parametros[0];
    const string& nombre = parametros[1];

    if (tipo != "comandos" && tipo != "elementos") {
        cout << "Error: el tipo debe ser 'comandos' o 'elementos'.\n";
        return;
    }

    if (tipo == "comandos" && !p.hay_comandos) {
        cout << "(No hay informacion) La informacion requerida no esta almacenada en memoria.\n";
        return;
    }
    if (tipo == "elementos" && !p.hay_elementos) {
        cout << "(No hay informacion) La informacion requerida no esta almacenada en memoria.\n";
        return;
    }

    ofstream archivo(nombre.c_str());
    if (!archivo.is_open()) {
        cout << "(Problemas en archivo) Error guardando en " << nombre << ".\n";
        return;
    }

    if (tipo == "comandos") {
        NodoComando* actual = p.lista_comandos.cabeza;
        while (actual != nullptr) {
            if (actual->tipo_comando == "movimiento") {
                archivo << actual->tipo_movimiento << " " << actual->magnitud << " " << actual->unidad << "\n";
            } else {
                archivo << actual->tipo_analisis << " " << actual->objeto;
                if (!actual->comentario.empty()) archivo << " " << actual->comentario;
                archivo << "\n";
            }
            actual = actual->siguiente;
        }
    } else {
        NodoElemento* actual = p.lista_elementos.cabeza;
        while (actual != nullptr) {
            archivo << actual->tipo << " " << actual->tamanio << " " << actual->unidad
                    << " " << actual->x << " " << actual->y << "\n";
            actual = actual->siguiente;
        }
    }

    archivo.close();
    cout << "(Escritura exitosa) La informacion ha sido guardada en " << nombre << ".\n";
}

void cmd_simular_comandos(const string parametros[], int cantidad, programa& p)
{
    if (cantidad != 2) {
        cout << "Error: uso correcto -> simular_comandos <x> <y>\n";
        return;
    }

    if (!es_numero(parametros[0]) || !es_numero(parametros[1])) {
        cout << "Error: las coordenadas deben ser valores numericos.\n";
        return;
    }

    if (!p.hay_comandos) {
        cout << "(No hay informacion) La informacion requerida no esta almacenada en memoria.\n";
        return;
    }

    double posX   = stod(parametros[0]);
    double posY   = stod(parametros[1]);
    double angulo = 0.0; // grados, 0 = mirando hacia la derecha (eje x+)

    NodoComando* actual = p.lista_comandos.cabeza;
    while (actual != nullptr) {
        if (actual->tipo_comando == "movimiento") {
            if (actual->tipo_movimiento == "avanzar") {
                double distancia_m = a_metros(actual->magnitud, actual->unidad);
                double angulo_rad  = angulo * M_PI / 180.0;
                posX += distancia_m * cos(angulo_rad);
                posY += distancia_m * sin(angulo_rad);
            } else if (actual->tipo_movimiento == "girar") {
                double delta_grd = a_grados(actual->magnitud, actual->unidad);
                angulo += delta_grd; // positivo = antihorario
            }
        }
        actual = actual->siguiente;
    }

    cout << "(Resultado exitoso) La simulacion de los comandos, a partir de la posicion (" << stod(parametros[0]) << "," << stod(parametros[1]) << "), deja al robot en la nueva posicion (" << posX << "," << posY << ").\n";
}

void cmd_ubicar_elementos(const string parametros[], int cantidad, programa& p)
{
    (void)parametros;
    if (cantidad != 0) { cout << "Error: número de parámetros inválido.\n"; return; }
    if (!p.hay_elementos) { cout << "(No hay información) La información requerida no está almacenada en memoria.\n"; return; }
    p.elementos_ubicados = true;
    cout << "Comando ejecutado correctamente.\n";
}

void cmd_en_cuadrante(const string parametros[], int cantidad, programa& p)
{
    if (cantidad != 4) { 
        cout << "(Formato erróneo) La información del cuadrante no corresponde a los datos esperados (x_min, x_max, y_min, y_max).\n"; 
        return; 
    }
    
   for (int i = 0; i < 4; i++) {
        if (!es_numero(parametros[i])) {
            cout << "(Formato erroneo) La informacion del cuadrante no corresponde a los datos esperados (x_min, x_max, y_min, y_max).\n";
            return;
        }
    }
    double x1 = stod(parametros[0]), x2 = stod(parametros[1]);
    double y1 = stod(parametros[2]), y2 = stod(parametros[3]);
    if (x1 >= x2 || y1 >= y2) {
        cout << "(Formato erroneo) La informacion del cuadrante no corresponde a los datos esperados (x_min, x_max, y_min, y_max).\n";
        return;
    }
    if (!p.elementos_ubicados) {
        cout << "(No hay informacion) Los elementos no han sido ubicados todavia (con el comando ubicar_elementos).\n";
        return;
    }
    
    cout << "(Resultado exitoso) Los elementos ubicados en el cuadrante solicitado son: (pendiente Entrega 2)\n";
}

void cmd_crear_mapa(const string parametros[], int cantidad, programa& p)
{
    if (cantidad != 1) { cout << "Error: número de parámetros inválido.\n"; return; }
    
    
    if (!es_numero(parametros[0])) {
        cout << "Error: el coeficiente debe ser un valor numérico.\n"; 
        return;
    }
    
    if (!p.hay_elementos) { cout << "(No hay información) La información requerida no está almacenada en memoria.\n"; return; }
    p.mapa_creado = true;
    cout << "Comando ejecutado correctamente.\n";
}

void cmd_ruta_mas_larga(const string parametros[], int cantidad, programa& p)
{
    (void)parametros;
    if (cantidad != 0) { cout << "Error: número de parámetros inválido.\n"; return; }
    if (!p.mapa_creado) { cout << "(No hay información) El mapa no ha sido generado todavía.\n"; return; }
    cout << "Comando ejecutado correctamente.\n";
}
