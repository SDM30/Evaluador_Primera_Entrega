#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <list>
#include <cmath>
#include <iomanip>
#include "ComandoMovimiento.h"
#include "ComandoAnalisis.h"
#include "Elemento.h"
#include "ListaComandos.h"
#include "ListaElementos.h"
using namespace std;
const double PI = 3.14159265358979323846;

//  FUNCIONES DE VALIDACION
//Estas funciones revisn si los datos ingresados por el usuario tienen el formato correcto
// Verifica si un string representa un numero valido (entero o decimal)
bool esNumero(string s)
{
    if (s.empty())
    {
        return false;
    }
    istringstream ss(s); // intento convertir el string a un numero
    double d;
    return (ss >> d) && ss.eof(); // si se pudo convertir y no quedaron caracteres extra, es un numro valido
}

// Verifica si el tipo de movimiento es "avanzar" o "girar"
bool validarTipoMov(string tipo)
{
    return tipo == "avanzar" || tipo == "girar";
}

// Verifica si la unidad de medida es valida para el tipo de movimiento dado
bool validarUnidadMov(string tipo, string unidad)
{
    if (tipo == "avanzar")
    {
        return unidad == "cm" || unidad == "dm" || unidad == "m" || unidad == "km";
    }
    if (tipo == "girar")
    {
        return unidad == "grd" || unidad == "rad";
    }
    return false;
}

// Verifica si el tipo de analisis es uno de los tres permitidos
bool validarTipoAnalisis(string tipo)
{
    return tipo == "fotografiar" || tipo == "composicion" || tipo == "perforar";
}

// Verifica si el tipo de elemento es uno de los cuatro permitidos
bool validarTipoElemento(string tipo)
{
    return tipo == "roca" || tipo == "crater" || tipo == "monticulo" || tipo == "duna";
}

// Verifica si la unidad de medida de distancia es valida
bool validarUnidadElemento(string u)
{
    return u == "cm" || u == "dm" || u == "m" || u == "km";
}

// Verifica si el comentario esta vacio (es opcional) o entre comillas simples
bool validarComentario(string c)
{
    if (c.empty())
    {
        return true; // el comentario es opcional, si no viene esta bien
    }
    // si hay comentario, debe empezar y terminar con comilla simple
    return c.length() >= 2 && c.front() == '\'' && c.back() == '\''; // el front() devuelve el primer caracter del string y el back() devuelve el ultimo caracter del string, entonces verificamos que ambos sean comillas simples
}

//  FUNCIONES DE CONVERSION DE UNIDADES

// Convierte una distancia a metros segun la unidad dada
double aMetros(double mag, string unidad)
{
    if (unidad == "cm")
    {
        return mag / 100.0;
    }
    if (unidad == "dm")
    {
        return mag / 10.0;
    }
    if (unidad == "m")
    {
        return mag;
    }
    if (unidad == "km")
    {
        return mag * 1000.0;
    }
    return mag;
}

// Convierte un angulo a radianes segun la unidad dada (si ya esta en radianes, no hace nada)
double aRadianes(double mag, string unidad)
{
    if (unidad == "grd")
    {
        return mag * PI / 180.0; //PI es la constante de pi que viene en la bilbioteca de cmath
    }
    return mag; // ya esta en radianes
}

//  FUNCIONES DE LECTURA DE ARCHIVOS
// Lee el archivo de comandos y llena la lista. Retorna false si el archivo no se puede abrir.
// Los contadores llevan la cuenta de lo que se cargo y los errores.
bool cargarArchivoComan(string nombreArchivo, ListaComandos& lista, int& movCargados, int& anaCargados, int& errores)
{
    ifstream arch(nombreArchivo);  // intento abrir el archivo
    if (!arch.is_open())
    {
        return false; // el archivo no existe o no se puede leer
    }

    // limpiamos la lista antes de cargar el nuevo archivo
    lista.limpiar();
    movCargados = 0;
    anaCargados = 0;
    errores= 0;

    string linea;
    while (getline(arch, linea))
    {
        // eliminar el caracter \r que sale en windows cuando creamos un archivo de texto con bloc de notas y nos causaba error al leer
        if (!linea.empty() && linea[linea.size() - 1] == '\r')
        {
            linea.erase(linea.size() - 1);
        }
        if (linea.empty())
        {
            continue; // ignoramos las lineas vacias
        }

        istringstream ss(linea);
        string tipo;
        ss >> tipo; // leemos el primer token: el tipo de comando

        if (tipo == "avanzar" || tipo == "girar")
        {
            // es un comando de movimiento: leemos magnitud y unidad
            string magStr, unidad;
            if (ss >> magStr >> unidad && esNumero(magStr) && validarUnidadMov(tipo, unidad))
            {
                lista.agregarMovimiento(ComandoMovimiento(tipo, stod(magStr), unidad));
                movCargados++;
            }
            else
            {
                errores++; // linea con formato incorrecto
            }
        }
        else if (tipo == "fotografiar" || tipo == "composicion" || tipo == "perforar")
        {
            // es un comando de analisis, entonces leemos objeto y comentario opcional
            string objeto, comentario;
            if (ss >> objeto)
            {
                // el comentario puede o no estar, lo leemos con getline
                getline(ss, comentario);

                // quitamos el espacio del inicio si hay
                if (!comentario.empty() && comentario[0] == ' ')
                {
                    comentario.erase(0, 1); // eliminamos el espacio del inicio del comentario si existe
                }

                if (validarComentario(comentario))
                {
                    lista.agregarAnalisis(ComandoAnalisis(tipo, objeto, comentario));
                    anaCargados++;
                }
                else
                {
                    errores++;
                }
            }
            else
            {
                errores++;
            }
        }
        else
        {
            errores++; // tipo de comando desconocido o formato incorrecto
        }
    }
    arch.close();
    return true;
}

// Lee el archivo de elementos y llena la lista.
// Retorna false si el archivo no se puede abrir.
bool cargarArchivoElem(string nombreArchivo, ListaElementos& lista, int& cargados, int& errores)
{
    ifstream arch(nombreArchivo);
    if (!arch.is_open())
    {
        return false;
    }

    // limpiamos la lista antes de cargar el nuevo archivo
    lista.limpiar();
    cargados = 0;
    errores  = 0;

    string linea;
    while (getline(arch, linea))
    {
        if (!linea.empty() && linea[linea.size() - 1] == '\r') // eliminamos el \r de windows
        {
            linea.erase(linea.size() - 1);
        }
        if (linea.empty())
        {
            continue;
        }

        istringstream ss(linea); // leemos la linea del archivo
        string tipo, unidad;
        double tam, x, y;

        // el formato esperado es tipo, tamano, unidad, x, y
        if (ss >> tipo >> tam >> unidad >> x >> y && validarTipoElemento(tipo) && validarUnidadElemento(unidad) && tam > 0)
        {
            lista.agregarElemento(Elemento(tipo, tam, unidad, x, y));
            cargados++;
        }
        else
        {
            errores++;
        }
    }
    arch.close();
    return true;
}

//  FUNCIONES DE GUARDADO EN ARCHIVO

// Guarda todos los comandos en el archivo, respetando el orden original en que fueron ingresados
bool guardarComandos(string nombreArchivo, ListaComandos& lista)
{
    ofstream arch(nombreArchivo);
    if (!arch.is_open())
    {
        return false;
    }

    // recorremos la lista de comandos y escribimos cada uno en el archivo con el formato adecuado
    list<EntradaComando>& entradas = lista.getEntradas(); // obtenemos la lista de comandos para recorrerla
    list<EntradaComando>::iterator it;
    it = entradas.begin();
    for (; it != entradas.end(); ++it)
    {
        if (it->tipo == ENTRADA_MOVIMIENTO)
        {
            // escribimos el comando de movimiento con tipo magnitud y unidad
            arch << it->movimiento.getTipoMovimiento() << " "<< it->movimiento.getMagnitud()<< " "<< it->movimiento.getUnidad()<< "\n";
        }
        else
        {
            // escribimos el comando de analisis
            arch << it->analisis.getTipoAnalisis() << " "<< it->analisis.getObjeto();

            // el comentario es opcional entonces solo lo escribo si existe
            if (!it->analisis.getComentario().empty())
            {
                arch << " " << it->analisis.getComentario();
            }
            arch << "\n";
        }
    }
    arch.close();
    return true;
}
// Guarda todos los elementos en el archivo
bool guardarElementos(string nombreArchivo, ListaElementos& lista)
{
    ofstream arch(nombreArchivo);
    if (!arch.is_open())
    {
        return false;
    }

    list<Elemento>& elems = lista.getElementos(); // obtenemos la lista de elementos para recorrerla
    list<Elemento>::iterator it;
    it = elems.begin();
    for (; it != elems.end(); ++it)
    {
        arch << it->getTipo() << " " << it->getTamano() << " " << it->getUnidad() << " "<< it->getCoordX() << " "<< it->getCoordY() << "\n";
    }
    arch.close();
    return true;
}

//  SIMULAR COMANDOS
//  Recorre los comandos de movimiento en orden y calcula la posicion final del robot.
//  El robot inicia en (posX, posY) con un angulo = 0
//  nos dice el proyecto que los giros positivos = sentido antihorario (izquierda) y que los giros negativos = sentido horario (derecha).
//  Los comandos de analisis se ignoran en la simulacion.
void simularMovimientos(double posX, double posY, ListaComandos& lista, double& finalX, double& finalY) //
{
    double angulo = 0.0;
    double x = posX;
    double y = posY;

    list<EntradaComando>& entradas = lista.getEntradas();
    list<EntradaComando>::iterator it;
    it = entradas.begin();
    for (; it != entradas.end(); it++)
    {
        // solo procesamos comandos de movimiento
        if (it->tipo != ENTRADA_MOVIMIENTO)
        {
            continue;
        }

        string tipo   = it->movimiento.getTipoMovimiento();
        double mag    = it->movimiento.getMagnitud();
        string unidad = it->movimiento.getUnidad();

        if (tipo == "avanzar")
        {
            // convertimos la distancia a metros y avanzamos en la direccion actual
            double distancia = aMetros(mag, unidad);
            x += distancia * cos(angulo); // componente horizontal
            y += distancia * sin(angulo); // componente vertical
        }
        else if (tipo == "girar")
        {
            // sumamos el angulo al acumulado (positivo = antihorario)
            angulo += aRadianes(mag, unidad);
        }
    }
    // guardo el resultado en las variables de salida
    finalX = x;
    finalY = y;
}

//  EN CUADRANTE (esta aun no se hace bien sino con lista normal pq es de la entrega 2)
//  Busca y retorna los elementos que estan dentro del rectangulo definido por (xMin, xMax, yMin, yMax).
list<Elemento> enCuadrante(ListaElementos& lista, double xMin, double xMax, double yMin, double yMax)
{
    list<Elemento> resultado;

    list<Elemento>& elems = lista.getElementos();
    list<Elemento>::iterator it;
    for (it = elems.begin(); it != elems.end();it++)
    {
        double ex = it->getCoordX(); // coordenada x del elemento
        double ey = it->getCoordY(); // coordenada y del elemento

        // verificamos si el elemento esta dentro del cuadrante
        if (ex >= xMin && ex <= xMax && ey >= yMin && ey <= yMax)
        {
            resultado.push_back(*it);
        }
    }
    return resultado;
}
//  AYUDA POR COMANDO (lo que corregimos de la entrega 0 que no lo tenia bien)
//  Muestra la descripcion detallada de un comando especifico
void mostrarAyudaComando(string sub)
{
    if (sub == "cargar_comandos")
    {
        cout << "cargar_comandos nombre_archivo" << endl;
        cout << "Carga en memoria los comandos de desplazamiento contenidos en el archivo identificado" << endl;
        cout << "por nombre_archivo, es decir, utiliza adecuadamente las estructuras lineales para cargar la" << endl;
        cout << "informacion de los comandos en memoria. Si dentro de la misma sesion de trabajo ya se han" << endl;
        cout << "cargado otros archivos de comandos (usando el comando cargar_comandos), la informacion debe" << endl;
        cout << "sobreescribirse en memoria, es decir, no se deben combinar informaciones de comandos de" << endl;
        cout << "diferentes archivos" << endl;
    }
    else if (sub == "cargar_elementos")
    {
        cout << "cargar_elementos nombre_archivo" << endl;
        cout << "Carga en memoria los datos de puntos de interes o elementos contenidos en el archivo" << endl;
        cout << "identificado por nombre_archivo, es decir, utiliza adecuadamente las estructuras lineales" << endl;
        cout << "para cargar la informacion de los elementos en memoria. Si dentro de la misma sesion de" << endl;
        cout << "trabajo ya se han cargado otros archivos de puntos de interes (usando el comando" << endl;
        cout << "cargar_elementos), la informacion debe sobreescribirse en memoria, es decir, no se deben" << endl;
        cout << "combinar informaciones de elementos de diferentes archivos" << endl;
    }
    else if (sub == "agregar_movimiento")
    {
        cout << "agregar_movimiento tipo_mov magnitud unidad_med" << endl;
        cout << "Agrega el comando de movimiento descrito a la lista de comandos del robot Curiosity." << endl;
        cout << "El movimiento puede ser de dos tipos: avanzar o girar. La magnitud corresponde al valor" << endl;
        cout << "del movimiento; si es avanzar, el numero de unidades que se espera avanzar, si es girar" << endl;
        cout << "la cantidad de grados que debe girar. La unidad de medida corresponde a la convencion" << endl;
        cout << "con la que se mide la magnitud del movimiento. Si no se envia la informacion completa y" << endl;
        cout << "adecuada del comando de movimiento, este no puede agregarse a la lista de los comandos" << endl;
        cout << "que se enviaran al robot desde la tierra" << endl;
    }
    else if (sub == "agregar_analisis")
    {
        cout << "agregar_analisis tipo_analisis objeto comentario" << endl;
        cout << "Agrega el comando de analisis descrito a la lista de comandos del robot Curiosity." << endl;
        cout << "El analisis puede ser de tres tipos: fotografiar, composicion o perforar. El objeto es" << endl;
        cout << "el nombre del elemento que se quiere analizar (roca, arena, monticulo, ...). El comentario" << endl;
        cout << "es opcional y permite agregar mas informacion sobre el elemento o el analisis, este" << endl;
        cout << "comentario estara encerrado entre comillas simples (ejemplo: 'roca_cuadrante_32')." << endl;
        cout << "Si no se envia la informacion completa y adecuada del comando de analisis, este no puede" << endl;
        cout << "agregarse a la lista de los comandos que se enviaran al robot desde la tierra" << endl;
    }
    else if (sub == "agregar_elemento")
    {
        cout << "agregar_elemento tipo_comp tamano unidad_med coordX coordY" << endl;
        cout << "Agrega el componente o elemento descrito a la lista de puntos de interes del robot" << endl;
        cout << "Curiosity. El tipo de componente puede ser uno entre roca, crater, monticulo o duna." << endl;
        cout << "El tamano es un valor real que da cuenta de que tan grande es el elemento; y la unidad" << endl;
        cout << "de medida complementa este valor con la convencion que se uso para su medicion." << endl;
        cout << "Las coordenadas x y y corresponden a numeros reales que permiten conocer la ubicacion" << endl;
        cout << "del elemento en el sistema de coordenadas del suelo marciano. Si no se envia la" << endl;
        cout << "informacion completa y adecuada del elemento, este no puede agregarse a la lista de" << endl;
        cout << "puntos de interes que se enviaran al robot desde la tierra" << endl;
    }
    else if (sub == "guardar")
    {
        cout << "guardar tipo_archivo nombre_archivo" << endl;
        cout << "Guarda en el archivo nombre_archivo la informacion solicitada de acuerdo al tipo de" << endl;
        cout << "archivo: comandos almacena en el archivo la informacion de comandos de movimiento y de" << endl;
        cout << "analisis que debe ejecutar el robot, elementos almacena en el archivo la informacion de" << endl;
        cout << "los componentes o puntos de interes conocidos en el suelo marciano" << endl;
    }
    else if (sub == "simular_comandos")
    {
        cout << "simular_comandos coordX coordY" << endl;
        cout << "Permite simular el resultado de los comandos de movimiento que se enviaran al robot" << endl;
        cout << "Curiosity desde la Tierra, facilitando asi la validacion de la nueva posicion en la" << endl;
        cout << "que podria ubicarse. Para ejecutarse adecuadamente, requiere conocer la posicion actual" << endl;
        cout << "(coordenadas x y y) del vehiculo. A partir de la posicion actual, se asume que el" << endl;
        cout << "Curiosity esta orientado mirando hacia la parte derecha del eje x en un sistema" << endl;
        cout << "cartesiano (hacia la derecha). Los angulos de giro positivos generan movimiento en el" << endl;
        cout << "sentido contrario de las manecillas del reloj, mientras que los angulos de giro" << endl;
        cout << "negativos generan movimiento en el sentido de las manecillas del reloj. Solo los" << endl;
        cout << "comandos de movimiento son necesarios, no los de analisis" << endl;
    }
    else if (sub == "ubicar_elementos")
    {
        cout << "ubicar_elementos" << endl;
        cout << "El comando debe utilizar la informacion de puntos de interes almacenada en memoria" << endl;
        cout << "para ubicarlos en una estructura de datos jerarquica adecuada, que permita luego" << endl;
        cout << "realizar consultas geograficas sobre estos elementos. Si alguno de los elementos no" << endl;
        cout << "puede agregarse adecuadamente, debe generarse un mensaje de error, pero deben" << endl;
        cout << "procesarse todos los elementos almacenados en memoria" << endl;
    }
    else if (sub == "en_cuadrante")
    {
        cout << "en_cuadrante coordX1 coordX2 coordY1 coordY2" << endl;
        cout << "Permite utilizar la estructura creada con el comando ubicar_elementos para retornar" << endl;
        cout << "una lista de los componentes o elementos que estan dentro del cuadrante geografico" << endl;
        cout << "descrito por los limites de coordenadas en x y y. Es necesario haber ejecutado el" << endl;
        cout << "comando ubicar_elementos para poder realizar la busqueda por cuadrantes. Los limites" << endl;
        cout << "de coordenadas deben garantizar que coordX1 < coordX2 y coordY1 < coordY2" << endl;
    }
    else if (sub == "crear_mapa")
    {
        cout << "crear_mapa coeficiente_conectividad" << endl;
        cout << "El comando debe utilizar la informacion de puntos de interes almacenada en memoria" << endl;
        cout << "para ubicarlos en una estructura no lineal y conectarlos entre si teniendo en cuenta" << endl;
        cout << "el coeficiente de conectividad dado. El objetivo es que cada elemento este conectado" << endl;
        cout << "a los demas elementos mas cercanos a el, midiendo la cercania a traves de la distancia" << endl;
        cout << "euclidiana entre los elementos. Con el coeficiente de conectividad se identifica la" << endl;
        cout << "cantidad de vecinos que puede tener cada elemento tomando como base el total de" << endl;
        cout << "elementos que se ubicaran en el mapa (ejemplo: si se van a ubicar 35 elementos y el" << endl;
        cout << "coeficiente es 0.4, la cantidad de vecinos es 35 * 0.4 = 14)" << endl;
    }
    else if (sub == "ruta_mas_larga")
    {
        cout << "ruta_mas_larga" << endl;
        cout << "Con el mapa ya creado, el comando permite identificar los dos componentes mas alejados" << endl;
        cout << "entre si de acuerdo a las conexiones generadas. El comando retorna los elementos mas" << endl;
        cout << "alejados de acuerdo a las conexiones que se encuentran en el mapa, no los elementos" << endl;
        cout << "que esten a mayor distancia euclidiana entre si. Al encontrar esa ruta mas larga, el" << endl;
        cout << "comando imprime en pantalla los elementos de origen y destino, la longitud total de" << endl;
        cout << "la ruta, y la secuencia de elementos que hay que seguir para ir del origen al destino" << endl;
    }
    else if (sub == "salir")
    {
        cout << "salir" << endl;
        cout << "Termina la ejecucion de la aplicacion." << endl;
    }
    else
    {
        cout << "(Comando desconocido) No existe ayuda para '" << sub << "'." << endl;
        cout << "Escriba 'ayuda' para ver todos los comandos disponibles" << endl;
    }
}
//  AYUDA GENERAL
//  Muestra la lista de todos los comandos disponibles
void mostrarAyudaGeneral()
{
    cout << "Comandos disponibles:" << endl;
    cout << "  cargar_comandos <nombre_archivo>" << endl;
    cout << "  cargar_elementos <nombre_archivo>" << endl;
    cout << "  agregar_movimiento <avanzar|girar> <magnitud> <unidad>" << endl;
    cout << "  agregar_analisis <fotografiar|composicion|perforar> <objeto> ['comentario']" << endl;
    cout << "  agregar_elemento <roca|crater|monticulo|duna> <tamano> <unidad> <x> <y>" << endl;
    cout << "  guardar <comandos|elementos> <nombre_archivo>" << endl;
    cout << "  simular_comandos <coordX> <coordY>" << endl;
    cout << "  ubicar_elementos" << endl;
    cout << "  en_cuadrante <xMin> <xMax> <yMin> <yMax>" << endl;
    cout << "  crear_mapa <coeficiente>" << endl;
    cout << "  ruta_mas_larga" << endl;
    cout << "  ayuda [comando]" << endl;
    cout << "  salir" << endl;
    cout << "Use 'ayuda <comando>' para ver la descripcion de un comando especifico" << endl;
}

//  Main donde se leen comandos del usuario y llamamos las funciones segun el caso
int main()
{
    // estructuras lineales para guardar la info en memoria
    ListaComandos  listaComandos;
    ListaElementos listaElementos;

    // banderas de estado para los comandos del Componente 2 (que aun no se hace para estap entrega)
    bool elementosUbicados = false;
    bool mapaCreado = false;

    cout << "Sistema Curiosity grupo 5" << endl;
    cout << "Escriba 'ayuda' para ver los comandos disponibles." << endl;

    string lineaEntrada, comando;

    while (true)
    {
        cout << "$ ";

        // si no se puede leer la entrada, salimos
        if (!getline(cin, lineaEntrada))
        {
            break;
        }

        // esto de elimiar el \r al final de la linea es porque en windows me ponia error, cuando se crea un archivo de texto con el bloc de notas, cada linea termina con \r\n, entonces al leer la linea con getline, el \r queda al final de la linea y puede causar problemas al comparar strings o al procesar la entrada
        if (!lineaEntrada.empty() && lineaEntrada[lineaEntrada.size() - 1] == '\r')
        {
            lineaEntrada.erase(lineaEntrada.size() - 1);
        }

        if (lineaEntrada.empty())
        {
            continue; // ignoramos lineas vacias
        }

        if (lineaEntrada == "salir")
        {
            break;
        }

        // extraemos el primer token como nombre del comando
        istringstream ss(lineaEntrada);
        ss >> comando;

        // cargar_comandos <nombre_archivo>
        if (comando == "cargar_comandos")
        {
            string nombreArchivo;
            if (!(ss >> nombreArchivo))
            {
                cout << "(Formato erroneo) La informacion del comando no corresponde a los datos esperados (nombre_archivo)" << endl;
                continue;
            }

            int movC = 0, anaC = 0, err = 0; // contadores para movimientos, analisis y errores de formato

            if (!cargarArchivoComan(nombreArchivo, listaComandos, movC, anaC, err))
            {
                cout << "(Archivo erroneo) " << nombreArchivo << " no se encuentra o no puede leerse" << endl;
            }
            else if (listaComandos.estaVacia())
            {
                cout << "(Archivo vacio) " << nombreArchivo << " no contiene comandos" << endl;
            }
            else
            {
                cout << "(Resultado exitoso) " << listaComandos.cantidad() << " comandos cargados correctamente desde " << nombreArchivo << endl;
            }
        }

        // cargar_elementos <nombre_archivo>
        else if (comando == "cargar_elementos")
        {
            string nombreArchivo;
            if (!(ss >> nombreArchivo))
            {
                cout << "(Formato erroneo) La informacion del comando no corresponde a los datos esperados (nombre_archivo)" << endl;
                continue;
            }
            int carg = 0, err = 0;

            if (!cargarArchivoElem(nombreArchivo, listaElementos, carg, err))
            {
                cout << "(Archivo erroneo) " << nombreArchivo << " no se encuentra o no puede leerse" << endl;
            }
            else if (listaElementos.estaVacia())
            {
                cout << "(Archivo vacio) " << nombreArchivo << " no contiene elementos" << endl;
            }
            else
            {
                // cuando se cargan nuevos elementos, hay que volver a ubicarlos
                elementosUbicados = false;

                cout << "(Resultado exitoso) " << carg << " elementos cargados correctamente desde " << nombreArchivo << endl;
            }
        }

        // agregar_movimiento <tipo> <magnitud> <unidad>
        else if (comando == "agregar_movimiento")
        {
            string tipo, magStr, unidad; // leemos los parametros como strings para validar el formato antes de convertir

            if (!(ss >> tipo >> magStr >> unidad))
            {
                cout << "(Formato erroneo) La informacion del movimiento no corresponde a los datos esperados (tipo, magnitud, unidad)" << endl;
            }
            else if (!validarTipoMov(tipo) || !esNumero(magStr) || !validarUnidadMov(tipo, unidad))
            {
                cout << "(Formato erroneo) La informacion del movimiento no corresponde a los datos esperados (tipo, magnitud, unidad)" << endl;
            }
            else
            {
                listaComandos.agregarMovimiento(ComandoMovimiento(tipo, stod(magStr), unidad));
                cout << "(Resultado exitoso) El comando de movimiento ha sido agregado exitosamente" << endl;
            }
        }

        // agregar_analisis <tipo> <objeto> y comentario opcional entre comillas simples
        else if (comando == "agregar_analisis")
        {
            string tipo, objeto, comentario;

            if (!(ss >> tipo >> objeto))
            {
                cout << "(Formato erroneo) La informacion del analisis no corresponde a los datos esperados (tipo, objeto, comentario)" << endl;
            }
            else
            {
                // leemos el resto de la linea como comentario (puede estar vacio)
                getline(ss, comentario);

                // quitamos el espacio del inicio si hay
                if (!comentario.empty() && comentario[0] == ' ')
                {
                    comentario.erase(0, 1); // el 0 es la posicion del primer caracter, el 1 es la cantidad de caracteres a eliminar
                }

                if (!validarTipoAnalisis(tipo) || !validarComentario(comentario))
                {
                    cout << "(Formato erroneo) La informacion del analisis no corresponde a los datos esperados (tipo, objeto, comentario)" << endl;
                }
                else
                {
                    listaComandos.agregarAnalisis(ComandoAnalisis(tipo, objeto, comentario));
                    cout << "(Resultado exitoso) El comando de analisis ha sido agregado exitosamente" << endl;
                }
            }
        }
        // agregar_elemento <tipo> <tamano> <unidad> <x> <y>
        else if (comando == "agregar_elemento")
        {
            string tipo, unidad, extra;
            double tam, x, y;

            if (!(ss >> tipo >> tam >> unidad >> x >> y))
            {
                cout << "(Formato erroneo) La informacion del elemento no corresponde a los datos esperados (tipo, tamano, unidad, x, y)" << endl;
            }
            else if (!validarTipoElemento(tipo) || !validarUnidadElemento(unidad) || tam <= 0 || (ss >> extra)) //el >> extra intenta leer un token mas, si lo logra es porque hay informacion extra que no corresponde al formato esperado
            {
                cout << "(Formato erroneo) La informacion del elemento no corresponde a los datos esperados (tipo, tamano, unidad, x, y)" << endl;
            }
            else
            {
                listaElementos.agregarElemento(Elemento(tipo, tam, unidad, x, y));
                elementosUbicados = false; // hay que volver a ubicar con el nuevo elemento
                cout << "(Resultado exitoso) El elemento ha sido agregado exitosamente" << endl;
            }
        }
        // guardar <comandos|elementos> <nombre_archivo>
        else if (comando == "guardar")
        {
            string tipoArch, nombreArch;

            if (!(ss >> tipoArch >> nombreArch))
            {
                cout << "(Formato erroneo) La informacion del archivo no corresponde a los datos esperados (tipo_archivo, nombre_archivo)" << endl;
            }
            else if (tipoArch == "comandos")
            {
                if (listaComandos.estaVacia())
                {
                    cout << "(No hay informacion) La informacion requerida no esta almacenada en memoria" << endl;
                }
                else if (guardarComandos(nombreArch, listaComandos))
                {
                    cout << "(Escritura exitosa) La informacion ha sido guardada en " << nombreArch <<endl;
                }
                else
                {
                    cout << "(Problemas en archivo) Error guardando en " << nombreArch << endl;
                }
            }
            else if (tipoArch == "elementos")
            {
                if (listaElementos.estaVacia())
                {
                    cout << "(No hay informacion) La informacion requerida no esta almacenada en memoria" << endl;
                }
                else if (guardarElementos(nombreArch, listaElementos))
                {
                    cout << "(Escritura exitosa) La informacion ha sido guardada en " << nombreArch << endl;
                }
                else
                {
                    cout << "(Problemas en archivo) Error guardando en " << nombreArch << endl;
                }
            }
            else
            {
                cout << "(Formato erroneo) La informacion del archivo no corresponde a los datos esperados (tipo_archivo, nombre_archivo)" << endl;
            }
        }
        // simular_comandos <coordX> <coordY>
        else if (comando == "simular_comandos")
        {
            double posX, posY;

            if (!(ss >> posX >> posY))
            {
                cout << "(Formato erroneo) La informacion de la simulacion no corresponde a los datos esperados (coordX, coordY)." << endl;
            }
            else if (listaComandos.cantidadMovimientos() == 0)
            {
                // no tiene sentido simular si no hay comandos de movimiento
                cout << "(No hay informacion) La informacion requerida no esta almacenada en memoria" << endl;
            }
            else
            {
                double finalX = 0.0;
                double finalY = 0.0;

                simularMovimientos(posX, posY, listaComandos, finalX, finalY);

                cout << "(Resultado exitoso) La simulacion de los comandos, a partir de la posicion ("<< posX << "," << posY<< "), deja al robot en la nueva posicion ("<< finalX << "," << finalY << ")." << endl;
            }
        }
        // ubicar_elementos
        else if (comando == "ubicar_elementos")
        {
            if (listaElementos.estaVacia())
            {
                cout << "(No hay informacion) La informacion requerida no esta almacenada en memoria." << endl;
            }
            else
            {
                // AUN NO SE HACE BIEN, SOLO VERIFICA QUE LOS ELEMENTOS TENGAN DATOS VALIDOS es en entrega 2
                cout << "(Resultado exitoso) Los elementos han sido procesados exitosamente." << endl;
                elementosUbicados = true;
            }
        }
        // en_cuadrante <xMin> <xMax> <yMin> <yMax>
        else if (comando == "en_cuadrante")
        {
            double xMin, xMax, yMin, yMax;

            if (!(ss >> xMin >> xMax >> yMin >> yMax))
            {
                cout << "(Formato erroneo) La informacion del cuadrante no corresponde a los datos esperados (x_min, x_max, y_min, y_max)" << endl;
            }
            else if (!elementosUbicados)
            {
                cout << "(No hay informacion) Los elementos no han sido ubicados todavia (con el comando ubicar_elementos)" << endl;
            }
            else if (xMin >= xMax || yMin >= yMax)
            {
                cout << "(Formato erroneo) La informacion del cuadrante no corresponde a los datos esperados (x_min, x_max, y_min, y_max)" << endl;
            }
            else
            {
                // Aun no se hace bien, solo verifica el formato de los datos es entrega 2
                cout << "(Resultado exitoso) Los elementos ubicados en el cuadrante solicitado son: " << endl;
            }
        }
        // crear_mapa <coeficiente>
        else if (comando == "crear_mapa")
        {
            string sc;
            if (!(ss >> sc) || !esNumero(sc))
            {
                cout << "(Formato erroneo) La informacion del mapa no corresponde a los datos esperados (coeficiente_conectividad)" << endl;
            }
            else
            {
                double c = stod(sc);
                if (c <= 0 || c > 1)
                {
                    cout << "(Formato erroneo) La informacion del mapa no corresponde a los datos esperados (coeficiente_conectividad)" << endl;
                }
                else
                {
                    // TODO Entrega 2: construir estructura de conectividad
                    mapaCreado = true;
                    cout << "(Resultado exitoso) El mapa se ha generado exitosamente" << endl;
                }
            }
        }
        // ruta_mas_larga
        else if (comando == "ruta_mas_larga")
        {
            if (!mapaCreado)
            {
                cout << "(No hay informacion) El mapa no ha sido generado todavia (con el comando crear_mapa)" << endl;
            }
            else
            {
                // TODO Entrega 2: calcular ruta mas larga
                cout << "(Resultado exitoso) Los puntos de interes mas alejados entre si son ... y ... La ruta que los conecta tiene una longitud total de ... y pasa por los siguientes elementos: ..." << endl;
            }
        }
        // ayuda [subcomando]
        else if (comando == "ayuda")
        {
            string sub;
            if (ss >> sub)
            {
                mostrarAyudaComando(sub); // ayuda especifica de un comando
            }
            else
            {
                mostrarAyudaGeneral(); // lista de todos los comandos
            }
        }
        // Comando no reconocido
        else
        {
            cout << "(Comando no reconocido) Escriba 'ayuda' para ver los comandos disponibles." << endl;
        }
    }
    return 0;
}