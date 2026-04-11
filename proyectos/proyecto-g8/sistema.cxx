#include "sistema.h"
#include "validaciones.h"
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

// cargarComandos
string Sistema::cargarComandos(string nombreArchivo) {
     ifstream archivo(nombreArchivo); //leemos el archivo
    if (!archivo.is_open()) { //verifica si se abrio correctamente
        return "(Archivo erroneo) " + nombreArchivo + " no se encuentra o no puede leerse.";
    }

    list<Comando> nuevosComandos; //creamos una lista temporal de comandos para guardar los que se van leyendo del archivo
    string linea; //guardar cada linea

    while (getline(archivo, linea)) {
        // Ignorar lineas vacias
        if (linea.empty()) continue;

        istringstream ss(linea); //leer las palabras por separado como un flujo
        string token;
        ss >> token;//extraemos la primera palabra de cada linea

        // Comando de movimiento: avanzar o girar
        if (token == "avanzar" || token == "girar") {
            string unidad;
            double magnitud;
            if (!(ss >> magnitud >> unidad)) continue;
            if (!validarUnidadMovimiento(token, unidad)) continue;
            nuevosComandos.push_back(Comando(token, magnitud, unidad)); //se crea un objeto Comando con los datos leidos y se agrega al final de la lista con push_back

        // Comando de analisis: fotografiar, composicion, perforar
        } else if (token == "fotografiar" || token == "composicion" || token == "perforar") {
            string objeto, adicional, comentario;
            if (!(ss >> objeto)) continue;
            getline(ss, adicional);
            // Eliminar espacio inicial
            if (!adicional.empty() && adicional[0] == ' '){ //Si el comentario inicia con un espacio se elimina
                adicional.erase(0, 1);
            }
            // El comentario es todo lo que queda (incluye comillas, sean ASCII o tipograficas)
            comentario = adicional;
            nuevosComandos.push_back(Comando(token, objeto, comentario));//Se crea el objeto comando con el tipo, objeto y comentario
        }
        // Lineas no reconocidas se ignoran
    }
    archivo.close();

    if (nuevosComandos.empty()) {
        return "(Archivo vacio) " + nombreArchivo + " no contiene comandos.";
    }

    // Sobreescribir la lista de comandos
    comandos = nuevosComandos; // la lista de los comandos del sistema se reemplaza por la nueva lista cargada
    int n; 
    n = comandos.size();
    return "(Resultado exitoso) " + to_string(n) +
       " comandos cargados correctamente desde " +
       nombreArchivo + ".";
}

// cargarElementos
string Sistema::cargarElementos(string nombreArchivo) {
     ifstream archivo(nombreArchivo); //leer el archivo
    if (!archivo.is_open()) {
        return "(Archivo erroneo) " + nombreArchivo + " no se encuentra o no puede leerse.";
    }

    list<Elemento> nuevosElementos; //lista temporal con los elementos que se van leyendo
    string linea;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        istringstream ss(linea); //convertir la linea en flujo para usar >>
        string tipo, unidad;
        double tam, x, y;

        if (!(ss >> tipo >> tam >> unidad >> x >> y)) continue; //orden de leer los datos, si no se ignoran
        if (!validarTipoElemento(tipo)) continue; //tipo sea valido si no se ignora
        if (!validarUnidadMedida(tipo, unidad)) continue; // unidad de medida sea correcta para ese tipo de elemento

        nuevosElementos.push_back(Elemento(tipo, tam, unidad, x, y)); // se crea un objeto Elemento con esos datos y se guarda en la lista
    }
    archivo.close();

    if (nuevosElementos.empty()) {
        return "(Archivo vacio) " + nombreArchivo + " no contiene elementos.";
    }

    // Sobreescribir la lista de elementos
    elementos = nuevosElementos;
    int n = elementos.size();
    return "(Resultado exitoso) " + to_string(n) +
           " elementos cargados correctamente desde " +
           nombreArchivo + ".";
}

// agregarMovimiento
string Sistema::agregarMovimiento(string tipoMov, double mag, string unidad) {
    comandos.push_back(Comando(tipoMov, mag, unidad));
    return "(Resultado exitoso) El comando de movimiento ha sido agregado exitosamente.";
}

// agregarAnalisis
string Sistema::agregarAnalisis(string tipoAnal, string obj, string com) {
    comandos.push_back(Comando(tipoAnal, obj, com));
    return "(Resultado exitoso) El comando de analisis ha sido agregado exitosamente.";
}

// agregarElemento
string Sistema::agregarElemento(string tipo, double tam, string unidad, double x, double y) {
    // agregarElemento AQUI VA LA EJECUCION
    elementos.push_back(Elemento(tipo, tam, unidad, x, y)); // se agrega al final de la lista de elementos
    return "(Resultado exitoso) El elemento ha sido agregado exitosamente.";
}

// guardar
string Sistema::guardar(string tipoArchivo, string nombreArchivo) {
   if (tipoArchivo == "comandos") { //guardar comandos 
        if (comandos.empty()) { // verificar si hay comandos
            return "(No hay informacion) La informacion requerida no esta almacenada en memoria";
        }
        ofstream archivo(nombreArchivo); // abrir el archivo para escritura
        if (!archivo.is_open()) {
            return "(Problemas en archivo) Error guardando en " + nombreArchivo + ".";
        }
        for (list<Comando>::iterator it = comandos.begin(); it != comandos.end(); ++it) { // recorremos todos los comandos que hay en la lista
            if (it->getTipo() == "movimiento") {
                archivo << it->getTipoMovimiento() << " "
                        << it->getMagnitud()       << " "
                        << it->getUnidadMedida()   << "\n";
            } else { //comando analisis 
                archivo << it->getTipoAnalisis() << " " << it->getObjeto();
                if (!it->getComentario().empty()) {
                    archivo << " " << it->getComentario();
                }
                archivo << "\n";
            }
        }
        archivo.close();
        return "(Escritura exitosa) La informacion ha sido guardada en " + nombreArchivo + ".";

    } else { // si no es comandos, entonces guardamos elementos
        if (elementos.empty()) {
            return "(No hay informacion) La informacion requerida no esta almacenada en memoria.";
        }
        ofstream archivo(nombreArchivo);//archivo para escritura
        if (!archivo.is_open()) {
            return "(Problemas en archivo) Error guardando en " + nombreArchivo + ".";
        }
        for (list<Elemento>::iterator it = elementos.begin(); it != elementos.end(); ++it) {
            archivo << it->getTipoElemento() << " "
                    << it->getTamanio()      << " "
                    << it->getUnidadMedida() << " "
                    << it->getCoordenadaX()  << " "
                    << it->getCoordenadaY()  << "\n";
        }
        archivo.close();
        return "(Escritura exitosa) La informacion ha sido guardada en " + nombreArchivo + ".";
    }
}

// simularComandos
string Sistema::simularComandos(double x, double y) {
    if (comandos.empty()) {
        return "(No hay informacion) La informacion requerida no esta almacenada en memoria.";
    }

    double theta = 0.0;
    const double PI = 3.14159265358979323846;
    double nuevoX = x;
    double nuevoY = y;

    for (list<Comando>::iterator it = comandos.begin(); it != comandos.end(); ++it) {
        if (it->getTipo() == "analisis") continue;

        string tipoMov = it->getTipoMovimiento();
        double mag     = it->getMagnitud();
        string unidad  = it->getUnidadMedida();

        if (tipoMov == "avanzar") {
            double metros;
            if      (unidad == "cm") metros = mag / 100.0;
            else if (unidad == "dm") metros = mag / 10.0;
            else if (unidad == "m")  metros = mag;
            else                     metros = mag * 1000.0;

            nuevoX += metros * cos(theta);
            nuevoY += metros * sin(theta);

        } else {
            double rad = mag;
            if (unidad == "grd") rad = mag * PI / 180.0;
            else                 rad = mag;

            theta += rad;
        }
    }

    string resultado;
    
    resultado = "(Resultado exitoso) La simulación de los comandos, a partir de la posición ("
    + to_string(x) + ", " + to_string(y) + "), deja al robot en la nueva posición ("
    + to_string(nuevoX) + ", " + to_string(nuevoY) + ")";
    
    return resultado;
}
