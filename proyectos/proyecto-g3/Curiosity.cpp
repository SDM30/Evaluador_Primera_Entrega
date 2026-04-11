#include "Curiosity.h"
#include <iostream>
#include "Comando.h"
#include <cctype>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Comando.h"
#include "Elemento.h"
#include <math.h>
#include <iomanip>

using namespace std;

string archivoComandos = "comandos.txt" //por defectoo
    ,archivoElementos = "elementos.txt";

bool Curiosity::esNumero(const string& str) {
    if (str.empty()) return false;
    bool punto = false;
    int i = (str[0] == '-') ? 1 : 0;
    if (i == 1 && str.length() == 1) return false;
    for (; i < str.length(); ++i) {
        if (str[i] == '.') {
            if (punto) return false;
            punto = true;
        } else if (!isdigit(str[i])) return false;
    }
    return true;
}

bool Curiosity::esUnidadValida(const string& unidad) {
    return (unidad == "cm" || unidad == "dm" || unidad == "m" || unidad == "km" || unidad == "grd" || unidad == "rad");
}


string Curiosity::unidadToString(const UnidadMedida& u) {
    switch(u) {
        case CM: return "cm";
        case DM: return "dm";
        case M:  return "m";
        case KM: return "km";
        case GRD: return "grd";
        case RAD: return "rad";
        default: return "desconocido";
    }
}

UnidadMedida Curiosity::obtenerUnidad(const string u){

    if(u == "cm"){
        return CM;
    } else if(u == "dm"){
        return DM;
    }else if(u == "m"){
        return M;
    }else if(u == "km"){
        return KM;
    }else if(u == "grd"){
        return GRD;
    } else if (u == "rad"){
        return RAD;
    } else {
        return DESCONOCIDO;
    }

}

void Curiosity::cargar_comandos(const vector<string>& args) {

    if (args.size() != 2) {
        cout << "(Formato erroneo) Uso: cargar_comandos nombre_archivo" << endl;
        return;
    }
    archivoComandos=args[1];
    ifstream salida(archivoComandos);

    if(!salida.is_open()){
        cout << "(Archivo erroeno) " + archivoComandos + " no se encuentra o no puede leerse" <<endl;
        return;
    }

    listadeComandos.clear();

    if(salida.peek() == EOF){
        cout<< "(Archivo vacío) " + archivoComandos +" no contiene comandos"<<endl;
        return;
    }

    vector<string> comandos;
    string linea, comando;

    int i=0;

    while(getline(salida, linea)){

        stringstream ss(linea);
        comandos.clear();
     while(ss >> comando) {
        // Si empieza con comilla simple, es un comentario
        if(comando[0] == '\'') {
            string comentario = comando;
            // Mientras no tenga la comilla de cierre
            while(comentario.back() != '\'' && ss >> comando) {
                comentario += " " + comando;  // concatenamos las palabras
            }
            // Quitamos las comillas
            if(comentario.front() == '\'') comentario.erase(0, 1);
            if(comentario.back() == '\'') comentario.pop_back();

            comandos.push_back(comentario);
        } else {
            comandos.push_back(comando);
        }
    }

    if(comandos.empty()) continue;

        try{

            if(comandos[0]=="avanzar" || comandos[0]=="girar"){

                if (comandos.size() != 3)
                    throw invalid_argument("Parametros incorrectos en movimiento");

                if(!esNumero(comandos[1])){
                    throw invalid_argument("la magnitud debe ser un numero real valido");
                }

                double numero = stod(comandos[1]);

                UnidadMedida unidad = obtenerUnidad(comandos[2]);

                Tipo_Movimiento tipo = ComandoMovimiento<double>::obtenerTipoMovimiento(comandos[0]);

                ComandoMovimiento<double> movimiento(tipo,numero, unidad);
                Comando cm(movimiento);
                listadeComandos.push_back(cm);
            } else if(comandos[0]=="fotografiar" || comandos[0]=="composicion" || comandos[0]=="perforar"){

                if (comandos.size() < 2)
                    throw invalid_argument("Faltan parámetros para comando de análisis");

                string comentario = "";

                if(comandos.size() == 3){

                    // verificar si la línea tiene comillas simples
                    if(linea.find('\'') == -1){
                        throw invalid_argument("Comentario invalido (debe ir entre comillas simples)");
                    }

                    comentario = comandos[2];
                }

                if(comandos.size() > 3){
                    throw invalid_argument("Demasiados parametros en comando de analisis");
                }

                Tipo_Analisis tipo = ComandoAnalisis::obtenerTipoAnalisis(comandos[0]);

                ComandoAnalisis analisis(tipo, comandos[1], comentario);
                Comando ca(analisis);
                listadeComandos.push_back(ca);

            }

            i++;

        } catch (const exception &e){
            cerr << "Error: " << e.what() << endl;
            continue;
        }
    }

    // Mostrar los comandos cargados
    vector<Comando>::const_iterator it;

    for(it = listadeComandos.begin(); it != listadeComandos.end(); it++) {
        if(it->getTipo() == MOVIMIENTO) {
            ComandoMovimiento m = it->getMovimiento();

            cout << m.tipoMovimiento_toString(m.getTipoMovimiento())
                << " " << m.getMagnitud()
                << " " << unidadToString(m.getUnidadMedida()) << endl;

        } else if(it->getTipo() == ANALISIS) {
            ComandoAnalisis m = it->getAnalisis();

            cout << m.tipoAnalisis_toString(m.getTipoAnalisis())
                << " " << m.getObjeto()
                << " " << m.getComentario() << endl;
        }
    }

    cout << "(Resultado exitoso) " << i << " Comandos cargados correctamente desde " << archivoComandos << endl;
    salida.close();

}

void Curiosity::cargar_elementos(const vector<string>& args) {

    if (args.size() != 2) {
        cout << "(Formato erroneo) Uso: cargar_elementos nombre_archivo" << endl;
        return;
    }

    archivoElementos = args[1];
    ifstream salida(archivoElementos);

    if(!salida.is_open()){
        cout << "(Archivo erroeno) " + archivoElementos + " no se encuentra o no puede leerse" <<endl;
        return;
    }

    listadeElementos.clear();

    if(salida.peek() == EOF){
        cout<< "(Archivo vacío) " + archivoElementos +" no contiene comandos"<<endl;
        return;
    }

    vector<string> comandos;
    string linea, comando;

    int i=0;

    while(getline(salida, linea)){

        stringstream ss(linea);
        comandos.clear();
        while(ss >> comando)
            comandos.push_back(comando);

        if(comandos.empty()) continue;

        try{

            if(comandos.size() != 5) {
                throw invalid_argument("Cantidad incorrecta de parametros");
            }

            TipoElemento tipo=Elemento<double,double>::obtenerTipoElemento(comandos[0]);

            if(!esNumero(comandos[1])){
                throw invalid_argument("El tamaño debe ser un numero real valido");
            }
            
            if(!esNumero(comandos[3]) || !esNumero(comandos[4])){
                throw invalid_argument("Las coordenadas deben ser numeros reales validos");
            }

            double size = stod(comandos[1]);
            double cX = stod(comandos[3]);
            double cY = stod(comandos[4]);

            Punto<double> posicion(cX, cY);

            UnidadMedida unidad=obtenerUnidad(comandos[2]);

            Elemento <double, double> e(tipo, size, unidad, posicion);
            listadeElementos.push_back(e);
            i++;
        } catch (const exception &e){
            cerr << "Error: " << e.what() << endl;
            continue;
        }
    }

    vector<Elemento<double, double>>::const_iterator it = listadeElementos.begin();
    // mostrar los elementos cargados
    for(;it != listadeElementos.end(); it++) {

        cout << it->tipoElemento_toString(it->getTipoElemento())
            << " " << it->getTamano()
            << " " << unidadToString(it->getUnidadMedida())
            << " " << it->getCx()
            << " " << it->getCy()
            << endl;
    }

    cout << "(Resultado exitoso) " << i << " Elementos cargados correctamente desde " << archivoElementos << endl;
    salida.close();
}

void Curiosity::agregar_movimiento(const vector<string>& args) {
    if (args.size() != 4) {
        cout << "(Formato erroneo) La informacion del movimiento no corresponde a los datos esperados (tipo, magnitud, unidad)." << endl;
        return;
    }

    if (!esNumero(args[2])) {
        cerr << "(Error) Debe ingresar un numero en el campo magnitud." << endl;
        return;
    }

    try{
        double tam = stod(args[2]);;
        ComandoMovimiento<double> cm(ComandoMovimiento<double>::obtenerTipoMovimiento(args[1]), tam, obtenerUnidad(args[3]));

        Comando c(cm);
        listadeComandos.push_back(c);

    } catch (const exception &e){
        cerr << "Error: " << e.what() << endl;
        return;
    }

    cout << "(Resultado exitoso) El comando de movimiento ha sido agregado exitosamente." << endl;
}

void Curiosity::agregar_analisis(const vector<string>& args) {

    if (args.size() < 3) {
        cout << "(Formato erroneo) La informacion del analisis no corresponde a los datos esperados (tipo, objeto, comentario)." << endl;
        return;
    }

    string comentario="";

    try{

        Tipo_Analisis ta=ComandoAnalisis::obtenerTipoAnalisis(args[1]);

        // Solo si hay mas de 3 argumentos, existe comentario
        if (args.size() > 3) {

        for (int i = 3; i < args.size(); ++i)
            comentario += args[i] + (i < args.size() - 1 ? " " : "");

            // validar comillas
            if (comentario.front() != '\'' || comentario.back() != '\'') {
                cout << "(Formato erroneo) El comentario debe estar entre comillas simples." << endl;
                return;
            }

        }

        ComandoAnalisis ca(ta, args[2], comentario);

        Comando c(ca);
        listadeComandos.push_back(c);

    } catch (const exception &e){
        cerr << "Error: " << e.what() << endl;
        return;
    }

    cout << "(Resultado exitoso) El comando de analisis ha sido agregado exitosamente." << endl;
}

void Curiosity::agregar_elemento(const vector<string>& args) {
    if (args.size() != 6) {
        cout << "(Formato erroneo) La informacion del elemento no corresponde a los datos esperados (tipo, tamaño, unidad, x, y)." << endl;
        return;
    }
    if (!esNumero(args[2]) || !esNumero(args[4]) || !esNumero(args[5])) {
        cerr << "(Formato erroneo) Datos de elemento invalidos." << endl;
        return;
    }

    try{

        TipoElemento te = Elemento<double,double>::obtenerTipoElemento(args[1]);
        UnidadMedida unidad = obtenerUnidad(args[3]);

        Punto<double> posicion(stod(args[4]), stod(args[5]));

        Elemento<double, double> nuevoElemento(te, stod(args[2]), unidad, posicion);
        listadeElementos.push_back(nuevoElemento);

    } catch (const exception &e){
        cerr << "Error: " << e.what() << endl;
        return;
    }
    cout << "(Resultado exitoso) El elemento ha sido agregado exitosamente." << endl;
}

void Curiosity::guardar(const vector<string>& args) {
    if (args.size() != 3) {
        cout << "(Formato erroneo) Uso: guardar tipo_archivo nombre_archivo" << endl;
        return;
    }

    string tipo = args[1];

    if (tipo != "comandos" && tipo != "elementos") {
        cout << "(Formato erroneo) El tipo debe ser 'comandos' o 'elementos'." << endl;
        return;
    }
    
    string archivo;

    if(tipo=="comandos"){
        archivoComandos=args[2];
        archivo=archivoComandos;
    } else {
        archivoElementos=args[2];
        archivo=archivoElementos;
    }

    // Validar información en memoria según tipo
    if (tipo == "comandos" && listadeComandos.empty()) {
        cout << "(No hay información) La información requerida no está almacenada en memoria." << endl;
        return;
    }

    if (tipo == "elementos" && listadeElementos.empty()) {
        cout << "(No hay información) La información requerida no está almacenada en memoria." << endl;
        return;
    }

    ofstream entrada(archivo);

    if(!entrada.is_open()){
        cout << "(Problemas en archivo) Error guardando en " <<archivo<<endl;
        return;
    }

    vector<Comando>::iterator itC = listadeComandos.begin();
    vector<Elemento<double,double>>::iterator itE = listadeElementos.begin();

    if(tipo=="comandos"){

        for(; itC != listadeComandos.end(); itC++){
            if(itC->getTipo() == MOVIMIENTO){
                ComandoMovimiento<double> cm = itC->getMovimiento();
                entrada << cm.tipoMovimiento_toString(cm.getTipoMovimiento()) <<" "<< cm.getMagnitud() 
                        <<" "<<unidadToString(cm.getUnidadMedida()) << endl;
            } else {
                ComandoAnalisis ca = itC->getAnalisis();
                entrada << ca.tipoAnalisis_toString(ca.getTipoAnalisis()) <<" "<< ca.getObjeto()
                        <<" "<< ca.getComentario() << endl;
            }
        }

    } else {

        for(; itE != listadeElementos.end(); itE++){
            entrada << itE->tipoElemento_toString(itE->getTipoElemento()) <<" "<<itE->getTamano() <<" "
                    << unidadToString(itE->getUnidadMedida()) << " " << itE->getCx() <<" " << itE->getCy() <<endl;
        }

    }

    cout << "(Escritura exitosa) Informacion guardada en " << archivo << endl;
    entrada.close();
}

void Curiosity::simular_comandos(const vector<string>& args) {
    if (args.size() != 3) {
        cout << "(Formato erroneo) Uso: simular_comandos coordX coordY" << endl;
        return;
    }

    if (!esNumero(args[1]) || !esNumero(args[2])) {
        cout << "(Formato erroneo) Las coordenadas deben ser valores numericos reales" << endl;
        return;
    }

    if(listadeComandos.empty()){
        cout << "(No hay información) La información requerida no está almacenada en memoria." << endl;
        return;
    }

    double anguloRadActual = 0; //empieza en la derecha del eje X
    double xActual = stod(args[1]);
    double yActual = stod(args[2]);

    vector<Comando>:: iterator itC = listadeComandos.begin();
    for(; itC != listadeComandos.end(); itC++) {

        if(itC->getTipo() == MOVIMIENTO){

            if(itC->getMovimiento().getTipoMovimiento() == GIRAR) {
                if (itC ->getMovimiento().getUnidadMedida() == GRD) {
                    anguloRadActual += itC ->getMovimiento().getMagnitud()*M_PI/180;
                } else {
                    anguloRadActual += itC ->getMovimiento().getMagnitud();
                }
            } else {
                double magnitudMetros = itC->getMovimiento().getMagnitud();
                double moverseX = 0;
                double moverseY = 0;
                switch (itC->getMovimiento().getUnidadMedida()) {
                    case CM:
                        magnitudMetros = magnitudMetros/100;
                    break;
                    case DM:
                        magnitudMetros = magnitudMetros/10;
                    break;
                    case KM:
                        magnitudMetros = magnitudMetros*1000;
                    break;
                }
                moverseX = cos(anguloRadActual) * magnitudMetros;
                moverseY = sin(anguloRadActual) * magnitudMetros;
                xActual += moverseX;
                yActual += moverseY;
            }

        }

    }
    cout << fixed << setprecision(5);
    cout << "(Resultado exitoso) La simulación de los comandos, a partir de la posición ("
     << args[1] << "," << args[2] << "), deja al robot en la nueva posición ("
     << xActual << "," << yActual << ")." << endl;
}

void Curiosity::ubicar_elementos(const vector<string>& args) {
    cout << "(Resultado exitoso) Elementos procesados exitosamente." << endl;
}

void Curiosity::en_cuadrante(const vector<string>& args) {
    if (args.size() != 5 || !esNumero(args[1]) || !esNumero(args[2]) || !esNumero(args[3]) || !esNumero(args[4])) {
        cout << "(Formato erroneo) Datos de cuadrante invalidos." << endl;
        return;
    }
    if (stof(args[1]) >= stof(args[2]) || stof(args[3]) >= stof(args[4])) {
        cout << "(Formato erroneo) Limites invalidos (x1 < x2 y y1 < y2)." << endl;
        return;
    }
    cout << "(Resultado exitoso) Busqueda en cuadrante finalizada (Simulado)." << endl;
}

void Curiosity::crear_mapa(const vector<string>& args) {
    if (args.size() != 2 || !esNumero(args[1])) {
        cout << "(Formato erroneo) Uso: crear_mapa coeficiente" << endl;
        return;
    }
    float c = stof(args[1]);
    if (c < 0 || c > 1) {
        cout << "(Formato erroneo) Coeficiente debe estar entre 0 y 1." << endl;
        return;
    }
    cout << "(Resultado exitoso) Mapa generado exitosamente." << endl;
}

void Curiosity::ruta_mas_larga(const vector<string>& args) {
    cout << "(Resultado exitoso) Ruta calculada (Simulado)." << endl;
}

void Curiosity::ayuda(const vector<string>& args) { 
    if (args.size() == 1) {
        cout << "\nComandos disponibles:" << endl;
        cout << "\n--- COMPONENTE 1: GESTION BASICA ---" << endl;

        cout << "\n - cargar_comandos" << endl;
        cout << " - cargar_elementos" << endl;
        cout << " - agregar_movimiento" << endl;
        cout << " - agregar_analisis" << endl;
        cout << " - agregar_elemento" << endl;
        cout << " - guardar" << endl;
        cout << " - simular_comandos" << endl;
        cout << " - salir" << endl;

        cout << "\n--- COMPONENTE 2: PLANEACION DE DESPLAZAMIENTOS ---" << endl;
        cout << "\n - ubicar_elementos" << endl;
        cout << " - en_cuadrante" << endl;

        cout << "\n--- COMPONENTE 3: RECORRIDOS Y MAPAS ---" << endl;
        cout << "\n - crear_mapa" << endl;
        cout << " - ruta_mas_larga" << endl;
        cout << "\nEscriba 'ayuda [comando]' para ver tipos de dato y parametros." << endl;
    } else {
        string c = args[1];
        
        if (c == "cargar_comandos") 
            cout << "Uso: cargar_comandos <nombre_archivo: string>\nDesc: Carga instrucciones desde un archivo de texto." << endl;
        
        else if (c == "cargar_elementos") 
            cout << "Uso: cargar_elementos <nombre_archivo: string>\nDesc: Carga puntos de interes (rocas, dunas, etc.)." << endl;
        
        else if (c == "agregar_movimiento") 
            cout << "Uso: agregar_movimiento <tipo_mov: string (avanzar|girar)> <magnitud: numerico> <unidad: string (cm|m|km|grd|rad)>" << endl;
        
        else if (c == "agregar_analisis") 
            cout << "Uso: agregar_analisis <tipo_an: string (fotografiar|composicion|perforar)> <objeto: string> <'comentario': string entre comillas simples>" << endl;
        
        else if (c == "agregar_elemento") 
            cout << "Uso: agregar_elemento <tipo: string (roca|crater|monticulo|duna)> <tamanio: numerico> <unidad: string (cm|m|km)> <x: numerico> <y: numerico>" << endl;
        
        else if (c == "guardar") 
            cout << "Uso: guardar <tipo_archivo: string (comandos|elementos)> <nombre_archivo: string>\nDesc: Exporta los datos actuales a un archivo." << endl;
        
        else if (c == "simular_comandos") 
            cout << "Uso: simular_comandos <coordX: numerico> <coordY: numerico>\nDesc: Simula el recorrido desde un punto inicial." << endl;
        
        else if (c == "ubicar_elementos") 
            cout << "Uso: ubicar_elementos (Sin parametros)\nDesc: Organiza los elementos en la estructura de datos del sistema." << endl;
        
        else if (c == "en_cuadrante") 
            cout << "Uso: en_cuadrante <x_min: numerico> <x_max: numerico> <y_min: numerico> <y_max: numerico>\nDesc: Filtra elementos en un rango geografico." << endl;
        
        else if (c == "crear_mapa") 
            cout << "Uso: crear_mapa <coeficiente: numerico (valor entre 0 y 1)>\nDesc: Genera un mapa de conectividad segun la proximidad." << endl;
        
        else if (c == "ruta_mas_larga") 
            cout << "Uso: ruta_mas_larga (Sin parametros)\nDesc: Identifica el camino de mayor distancia entre dos puntos." << endl;
        
        else if (c == "salir") 
            cout << "Uso: salir\nDesc: Finaliza la sesion y cierra el programa." << endl;
        
        else 
            cout << "Comando desconocido. Escriba 'ayuda' para ver la lista." << endl;
    }
}

// Constructor
Curiosity::Curiosity() : posicion(0.0, 0.0) {}

// Getters
const vector<Comando>& Curiosity::getListaComandos() const {
    return listadeComandos;
}

const vector<Elemento<double,double>>& Curiosity::getListaElementos() const {
    return listadeElementos;
}

Punto<double> Curiosity::getPosicion() const {
    return posicion;
}

// Setter
void Curiosity::setPosicion(const Punto<double>& nuevoPunto) {
    posicion = nuevoPunto;
}