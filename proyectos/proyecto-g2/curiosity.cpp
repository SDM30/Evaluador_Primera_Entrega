#include "curiosity.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

void Curiosity::cargarComandos(string archivo)
{

    ifstream file(archivo);

    if (!file)
    {
        cout << archivo << " no se encuentra o no puede leerse." << endl;
        return;
    }

    movimientos.clear();
    analisis.clear();

    string linea;
    int contador = 0;

    while (getline(file, linea))
    {

        if (linea.empty())
            continue;

        stringstream ss(linea);
        string tipo;

        ss >> tipo;

        if (tipo == "avanzar" || tipo == "girar")
        {

            Movimiento m;
            m.tipo = tipo;

            ss >> m.magnitud >> m.unidad;

            movimientos.push_back(m);
        }
        else
        {

            Analisis a;
            a.tipo = tipo;

            ss >> a.objeto;
            getline(ss, a.comentario);

            analisis.push_back(a);
        }

        contador++;
    }

    if (contador == 0)
    {
        cout << "(Archivo vacío) " << archivo << " no contiene comandos." << endl;
    }
    else
    {
        cout << contador << " comandos cargados correctamente desde " << archivo << endl;
    }
}

void Curiosity::cargarElementos(string archivo)
{

    ifstream file(archivo);

    if (!file)
    {
        cout << archivo << " no se encuentra o no puede leerse." << endl;
        return;
    }

    elementos.clear();

    int contador = 0;

    string tipo, unidad;
    double tam, x, y;

    while (file >> tipo >> tam >> unidad >> x >> y)
    {

        Elemento e;

        e.tipo = tipo;
        e.tamano = tam;
        e.unidad = unidad;
        e.x = x;
        e.y = y;

        elementos.push_back(e);
        contador++;
    }

    if (contador == 0)
    {
        cout << "(Archivo vacío) " << archivo << " no contiene elementos." << endl;
    }
    else
    {
        cout << contador << " elementos cargados correctamente desde " << archivo << endl;
    }
}

void Curiosity::agregarMovimiento(string tipo, double magnitud, string unidad)
{

    if (tipo != "avanzar" && tipo != "girar")
    {

        cout << "(Formato erróneo) La información del movimiento no corresponde a los datos esperados" << endl;
        return;
    }

    Movimiento m;

    m.tipo = tipo;
    m.magnitud = magnitud;
    m.unidad = unidad;

    movimientos.push_back(m);

    cout << "El comando de movimiento ha sido agregado exitosamente." << endl;
}

void Curiosity::agregarAnalisis(string tipo, string objeto, string comentario)
{

    if (tipo != "fotografiar" && tipo != "composicion" && tipo != "perforar")
    {

        cout << "(Formato erróneo) La información del análisis no corresponde a los datos esperados" << endl;
        return;
    }

    Analisis a;

    a.tipo = tipo;
    a.objeto = objeto;
    a.comentario = comentario;

    analisis.push_back(a);

    cout << "El comando de análisis ha sido agregado exitosamente." << endl;
}

void Curiosity::agregarElemento(string tipo, double tam, string unidad, double x, double y)
{

    if (tipo != "roca" && tipo != "crater" && tipo != "monticulo" && tipo != "duna")
    {

        cout << "(Formato erróneo) La información del elemento no corresponde a los datos esperados" << endl;
        return;
    }

    Elemento e;

    e.tipo = tipo;
    e.tamano = tam;
    e.unidad = unidad;
    e.x = x;
    e.y = y;

    elementos.push_back(e);

    cout << "El elemento ha sido agregado exitosamente." << endl;
}

void Curiosity::guardar(string tipo, string archivo)
{

    ofstream file(archivo);

    if (!file)
    {
        cout << "(Problemas en archivo) Error guardando en " << archivo << endl;
        return;
    }

    if (tipo == "comandos")
    {

        if (movimientos.empty() && analisis.empty())
        {
            cout << "(No hay información) La información requerida no está almacenada en memoria." << endl;
            return;
        }

        for (Movimiento m : movimientos)
        {
            file << m.tipo << " " << m.magnitud << " " << m.unidad << endl;
        }

        for (Analisis a : analisis)
        {
            file << a.tipo << " " << a.objeto << " " << a.comentario << endl;
        }

        cout << "(Escritura exitosa) La información ha sido guardada en " << archivo << endl;
    }
    else if (tipo == "elementos")
    {

        if (elementos.empty())
        {
            cout << "(No hay información) La información requerida no está almacenada en memoria." << endl;
            return;
        }

        for (Elemento e : elementos)
        {
            file << e.tipo << " " << e.tamano << " " << e.unidad << " " << e.x << " " << e.y << endl;
        }

        cout << "(Escritura exitosa) La información ha sido guardada en " << archivo << endl;
    }
    else
    {
        cout << "(Formato erróneo) El tipo a guardar debe ser 'comandos' o 'elementos'." << endl;
    }
}

void Curiosity::simularComandos(double x, double y)
{

    if (movimientos.empty())
    {
        cout << "(No hay información) La información requerida no está almacenada en memoria." << endl;
        return;
    }

    double angulo = 0;

    for (Movimiento m : movimientos)
    {

        if (m.tipo == "girar")
        {

            angulo += m.magnitud;
        }

        if (m.tipo == "avanzar")
        {

            double d = m.magnitud;

            x += d * cos(angulo * M_PI / 180);
            y += d * sin(angulo * M_PI / 180);
        }
    }

    cout << "La simulación de los comandos deja al robot en (" << x << "," << y << ")" << endl;
}

void Curiosity::ayuda(string comando_especifico)
{

    if (comando_especifico == "")
    {
        cout << "Comandos disponibles:" << endl;
        cout << "cargar_comandos archivo" << endl;
        cout << "cargar_elementos archivo" << endl;
        cout << "agregar_movimiento tipo magnitud unidad" << endl;
        cout << "agregar_analisis tipo objeto comentario" << endl;
        cout << "agregar_elemento tipo tamaño unidad x y" << endl;
        cout << "guardar tipo archivo" << endl;
        cout << "simular_comandos x y" << endl;
        cout << "salir" << endl;
    }
    else if (comando_especifico == "cargar_comandos")
    {
        cout << "cargar_comandos <archivo> : Carga los comandos de movimiento y analisis desde el archivo especificado." << endl;
    }
    else if (comando_especifico == "cargar_elementos")
    {
        cout << "cargar_elementos <archivo> : Carga los elementos del entorno desde el archivo especificado." << endl;
    }
    else if (comando_especifico == "agregar_movimiento")
    {
        cout << "agregar_movimiento <tipo> <magnitud> <unidad> : Agrega un comando de movimiento (avanzar o girar) a la memoria." << endl;
    }
    else if (comando_especifico == "agregar_analisis")
    {
        cout << "agregar_analisis <tipo> <objeto> <comentario> : Agrega un comando de analisis (fotografiar, composicion, perforar) a la memoria." << endl;
    }
    else if (comando_especifico == "agregar_elemento")
    {
        cout << "agregar_elemento <tipo> <tamaño> <unidad> <x> <y> : Agrega un elemento (roca, crater, monticulo, duna) al entorno." << endl;
    }
    else if (comando_especifico == "guardar")
    {
        cout << "guardar <tipo> <archivo> : Guarda la informacion de 'comandos' o 'elementos' en memoria en un archivo de texto." << endl;
    }
    else if (comando_especifico == "simular_comandos")
    {
        cout << "simular_comandos <x> <y> : Simula la ejecucion de los comandos de movimiento partiendo desde la coordenada (x, y)." << endl;
    }
    else if (comando_especifico == "salir")
    {
        cout << "salir : Termina la ejecucion de la aplicacion." << endl;
    }
    else
    {
        cout << "El comando '" << comando_especifico << "' no existe o no tiene un manual de ayuda." << endl;
    }
}