#include "validaciones.h"
#include "sistema.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main() {

    Sistema sistema;  //instancia del sistema
    string linea;

    while (true) {

        cout << "$ ";
        getline(cin, linea);

        vector<string> frase;
        string palabra;
        stringstream ss(linea);
        
        while (ss >> palabra) {
            frase.push_back(palabra);
        }

        if (frase.empty()) continue;

        string comando = frase[0];

        if (comando == "salir"){
            break;
        }

        if (!comandoValido(comando)) {
            cout << "Comando inválido" << endl;
            
        }

//Comando ayuda  
        if (comando == "ayuda") {
          if (frase.size()==1){
            cout << "Comandos:" << endl;
            cout << "cargar_comandos archivo" << endl;
            cout << "cargar_elementos archivo" << endl;
            cout << "agregar_movimiento tipo magnitud unidad" << endl;
            cout << "agregar_analisis tipo objeto comentario" << endl;
            cout << "agregar_elemento tipo tam unidad x y" << endl;
            cout << "guardar tipo_archivo nombre_archivo" << endl;
            cout << "simular_comandos x y" << endl;
            cout << "ubicar_elementos" << endl;
            cout << "en_cuadrante x1 x2 y1 y2" << endl;
            cout << "crear_mapa coeficiente" << endl;
            cout << "ruta_mas_larga" << endl;
            cout << "salir" << endl;
        } else if(frase.size()==2) {
            string command = frase[1];
            
            if (command=="cargar_comandos"){
              cout<<"Uso adecuado de comando: cargar_comandos nombre_archivo "<<endl;
              cout<<"Descripción: Carga en memoria los comandos de desplazamiento contenidos en el archivo identificado por nombre_archivo , es decir, utiliza adecuadamente las estructuras lineales para cargar la información de los comandos en memoria. Si dentro de la misma sesión de trabajo ya se han cargado otros archivos de comandos (usando el comando cargar_comandos), la información debe sobreescribirse en memoria, es decir, no se deben combinar informaciones de comandos de diferentes archivos."<<endl;
            }
            if (command=="cargar_elementos"){
              cout<<"Uso adecuado de comando: cargar_elementos nombre_archivo"<<endl;
              cout<<"Descripción: Carga en memoria los datos de puntos de interés o elementos contenidos en el archivo identificado por nombre_archivo , es decir, utiliza adecuadamente las estructuras lineales para cargar la información de los elementos en memoria. Si dentro de la misma sesión de trabajo ya se han cargado otros archivos de puntos de interés (usando el comando cargar_elementos), la información debe sobreescribirse en memoria, es decir, no se deben combinar informaciones de elementos de diferentes archivos."<<endl;
            }
           if (command == "agregar_movimiento" ){
              cout<<"Uso adecuado de comando: agregar_movimiento tipo_mov magnitud unidad_med"<<endl;
             cout<<"Descripción: Agrega el comando de movimiento descrito a la lista de comandos del robot “Curiosity”. El movimiento puede ser de dos tipos: avanzar o girar. La magnitud corresponde al valor del movimiento; si es avanzar, el número de unidades que se espera avanzar, si es girar la cantidad de grados que debe girar. La unidad de medida corresponde a la convención con la que se mide la magnitud del movimiento, de acuerdo a la tabla presentada anteriormente. Si no se envía la información completa y adecuada del comando de movimiento, éste no puede agregarse a la lista de los comandos que se enviarán al robot desde la tierra."<<endl;
            }
           if (command == "agregar_analisis" ){
              cout<<"Uso adecuado de comando: agregar_analisis tipo_analisis objeto comentario"<<endl;
             cout<<"Descripción: Agrega el comando de análisis descrito a la lista de comandos del robot “Curiosity”. El análisis puede ser de tres tipos: fotografiar, composicion o perforar. El objeto es el nombre del elemento que se quiere analizar (roca, arena, monticulo, ...). El comentario es opcional y permite agregar más información sobre el elemento o el análisis, este comentario estará encerrado entre comillas simples (ejemplo: ’roca_cuadrante_32’). Si no se envía la información completa y adecuada del comando de análisis, éste no puede agregarse a la lista de los comandos que se enviarán al robot desde la tierra."<<endl;
           }
           if (command == "agregar_elemento" ){
              cout<<"Uso adecuado de comando: agregar_elemento tipo_comp tamaño unidad_med coordX coordY"<<endl;
             cout<<"Descripción: Agrega el componente o elemento descrito a la lista de puntos de interés del robot “Curiosity”. El tipo de componente puede ser uno entre roca, crater, monticulo o duna. El tamaño es un valor real que da cuenta de qué tan grande es el elemento; y la unidad de medida complementa este valor con la convención que se usó para su medición, de acuerdo a la tabla presentada anteriormente. Finalmente, las coordenadas x y y corresponden a números reales que permiten conocer la ubicación del elemento en el sistema de coordenadas del suelo marciano utilizado por el vehículo. Si no se envía la información completa y adecuada del elemento, éste no puede agregarse a la lista de puntos de interés que se enviarán al robot desde la tierra."<<endl;
           }
           if (command == "guardar"){
              cout<<"Uso adecuado de comando: guardar tipo_archivo nombre_archivo"<<endl;
             cout<<"Descripción: Guarda en el archivo nombre_archivo la información solicitada de acuerdo al tipo de archivo: comandos almacena en el archivo la información de comandos de movimiento y de análisis que debe ejecutar el robot, elementos almacena en el archivo la información de los componentes o puntos de interés conocidos en el suelo marciano."<<endl;
           }
           if (command == "simular_comandos" ){
              cout<<"Uso adecuado de comando: simular_comandos coordX coordY"<<endl;
             cout<<"Descripción: Permite simular el resultado de los comandos de movimiento que se enviarán al robot “Curiosity” desde la Tierra, facilitando asi la validación de la nueva posición en la que podría ubicarse. Para ejecutarse adecuadamente, requiere conocer la posición actual (coordenadas x y y) del vehículo. A partir de la posición actual, se asume que el “Curiosity” está orientado mirando hacia la parte derecha del eje x en un sistema cartesiano (hacia la derecha). Los ángulos de giro positivos generan movimiento en el sentido contrario de las manecillas del reloj, mientras que los ángulos de giro negativos generan movimiento en el sentido de las manecillas del reloj. Hay que tener en cuenta que sólo los comandos de movimiento son necesarios, no los de análisis."<<endl;
           }
           if (command == "salir" ){
              cout<<"Uso adecuado de comando: salir"<<endl;
             cout<<"Descripción: Termina la ejecución de la aplicación."<<endl;
           }
           if (command == "ubicar_elementos" ){
              cout<<"Uso adecuado de comando: ubicar_elementos"<<endl;
             cout<<"Descripción: El comando debe utilizar la información de puntos de interés almacenada en memoria para ubicarlos en una estructura de datos jerárquica adecuada, que permita luego realizar consultas geográficas sobre estos elementos. Si alguno de los elementos no puede agregarse adecuadamente, debe generarse un mensaje de error, pero deben procesarse todos los elementos almacenados en memoria. "<<endl;
           }
           if (command == "en_cuadrante" ){
              cout<<"Uso adecuado de comando: en_cuadrante coordX1 coordX2 coordY1 coordY2"<<endl;
             cout<<"Descripción: Permite utilizar la estructura creada con el comando anterior para retornar una lista de los componentes o elementos que están dentro del cuadrante geográfico descrito por los límites de coordenadas en x y y. Es necesario haber ejecutado el comando ubicar_elementos para poder realizar la búsqueda por cuadrantes. Los límites de coordenadas deben garantizar que coordX1<coordX2 y coordY1<coordY2 ."<<endl;

           }
           if (command == "crear_mapa" ){
              cout<<"Uso adecuado de comando: crear_mapa coeficiente_conectividad"<<endl;
             cout<<"Descripción: El comando debe utilizar la información de puntos de interés almacenada en memoria para ubicarlos en una estructura no lineal y conectarlos entre sí teniendo en cuenta el coeficiente de conectividad dado. El objetivo es que cada elemento esté conectado a los demás elementos más cercanos a él, midiendo la cercanía a través de la distancia euclidiana entre los elementos. Esta distancia euclidiana también se utiliza como el peso o etiqueta de la conexión entre los elementos. Con el coeficiente de conectividad se identifica la cantidad de vecinos que puede tener cada elemento tomando como base el total de elementos que se ubicarán en el mapa (ejemplo: si se van a ubicar 35 elementos, y el coeficiente de conectividad es 0.4, la cantidad de vecinos que cada elemento debe tener es 35 * 0.4 = 14)."<<endl;
           }
           if (command =="ruta_mas_larga"){
              cout<<"Uso adecuado de comando: ruta_mas_larga"<<endl;
             cout<<"Descripción: Con el mapa ya creado, el comando permite identificar los dos componentes más alejados entre sí de acuerdo a las conexiones generadas. Es importante aclarar que el comando retorna los elementos más alejados de acuerdo a las conexiones que se encuentran en el mapa, no los elementos que estén a mayor distancia euclidiana entre sí. Al encontrar esa ruta más larga dentro del mapa, el comando imprime en pantalla los elementos de origen y destino, la longitud total de la ruta, y la secuencia de elementos que hay que seguir para ir del elemento origen al elemento destino."<<endl;
           }
          } else {
            cout<<"ERROR: Uso incorrecto de comando ayuda"<<endl;
          }
        }

//Validaciones de parametros
        if (comando == "cargar_comandos") {
            if (frase.size() != 2) {
              cout << "ERROR: faltan parametros" << endl;
            } else {
                cout << sistema.cargarComandos(frase[1]) << endl;
            }
        }

        else if (comando == "cargar_elementos") {
            if (frase.size() != 2) {
              cout << "ERROR: faltan parametros" << endl;
            } else {
                cout << sistema.cargarElementos(frase[1]) << endl;
            }
        }

        else if (comando == "agregar_movimiento") {
            if (frase.size() != 4) {
              cout << "(Formato erróneo) La información del movimiento no corresponde a los datos esperados (tipo, magnitud, unidad)." << endl;
            } else {
                string tipo = frase[1];
                string magnitud = frase[2];
                string unidadMed = frase[3];

                if (!validarTipoMovimiento(tipo)){
                    cout << "ERROR: tipo de movimiento invalido" << endl;
                } else if (!validarNumero(magnitud)){
                    cout << "ERROR: magnitud invalida" << endl;
                } else if (!validarUnidadMovimiento(tipo, unidadMed)){
                    cout << "ERROR: unidad invalida" << endl;
                } else {
                    stringstream conv(magnitud);
                    double mag;
                    conv >> mag;
                    cout << sistema.agregarMovimiento(tipo, mag, unidadMed) << endl;
                }
            }
        }

        else if (comando == "agregar_analisis") {
            if (frase.size() < 3) {
              cout << "(Formato erróneo) La información del análisis no corresponde a los datos esperados (tipo, objeto, comentario)." << endl;
            } else {
                string tipo, objeto, comentario;
                stringstream ss2(linea);
                ss2 >> tipo >> tipo >> objeto; // saltar "agregar_analisis"
                getline(ss2, comentario);
                if (!comentario.empty() && comentario[0] == ' ') {
                    comentario.erase(0, 1);
                }
                if (!validarTipoAnalisis(tipo)){
                    cout << "La información del análisis no corresponde a los datos esperados (tipo, objeto, comentario)" << endl;
                } else if (objeto.empty()) {
                    cout << "ERROR: objeto invalido" << endl;
                } else if (!validarComentario(comentario)){
                    cout << "ERROR: comentario debe ir entre comillas simples" << endl;
                } else {
                    cout << sistema.agregarAnalisis(tipo, objeto, comentario) << endl;
                }
            }
        }

        else if (comando == "agregar_elemento") {
            if (frase.size() != 6) {
              cout << "(Formato erróneo) La información del elemento no corresponde a los datos esperados (tipo, tamaño, unidad, x, y)." << endl;
            } else {
                string tipo = frase[1];
                string tam = frase[2];
                string unidad = frase[3];
                string x = frase[4];
                string y = frase[5];
                if (!validarTipoElemento(tipo) || !validarNumero(tam) || !validarUnidadMedida(tipo, unidad) || !validarNumero(x) || !validarNumero(y)) {
                    cout << "La información del elemento no corresponde a los datos esperados (tipo, tamaño, unidad, x, y)." << endl;
                } else {
                    stringstream cT(tam), cX(x), cY(y);
                    double dTam, dX, dY;
                    cT >> dTam; cX >> dX; cY >> dY;
                    cout << sistema.agregarElemento(tipo, dTam, unidad, dX, dY) << endl;
                }
            }
        }

        else if (comando == "guardar") {
           if (frase.size() != 3 || !validarTipoArchivo(frase[1])) {
                cout << "(Formato erroneo) El tipo de archivo o nombre no son válidos." << endl;
            } else {
                cout << sistema.guardar(frase[1], frase[2]) << endl;
            }
        }

        else if (comando == "simular_comandos") {
            if (frase.size() != 3) {
              cout << "ERROR: faltan parametros" << endl;
            } else if(!validarNumero(frase[1]) || !validarNumero(frase[2])) {
                cout << "La simulacion no pudo realizarse debido a datos invalidos." << endl;
            } else {
                stringstream cX(frase[1]), cY(frase[2]);
                double x, y;
                cX >> x; cY >> y;
                cout << sistema.simularComandos(x, y) << endl;
            }
        }

        else if (comando == "ubicar_elementos") {
            if (frase.size() != 1) {
              cout << "ERROR: faltan parametros" << endl;
            } else {
                cout << "EXITO elementos ubicados" << endl;
            }
        }

        else if (comando == "en_cuadrante") {
            if (frase.size() != 5) {
              cout << "(Formato erróneo) La información del cuadrante no corresponde a los datos esperados (x_min,x_max, y_min, y_max)"<< endl;
            } else {
                string x1 = frase[1];
                string x2 = frase[2];
                string y1 = frase[3];
                string y2 = frase[4];
                if (!validarNumero(x1) || !validarNumero(x2) ||
                    !validarNumero(y1) || !validarNumero(y2)) {
                    cout << "La información del cuadrante no corresponde a los datos esperados (x_min, x_max, y_min, y_max)" << endl;
                } else {
                    cout << "EXITO Parametros validos" << endl;
                }
            }
        }

        else if (comando == "crear_mapa") {
            if (frase.size() != 2) {
              cout << "(No hay información) La información requerida no está almacenada en memoria" << endl;
            } else if (!validarNumero(frase[1])){
                cout << "El coeficiente de conectividad no corresponde a los datos esperados" << endl;
            } else {
                cout << "(Pendiente) Componente 3 aun no implementado." << endl;
            }
        }

        else if (comando == "ruta_mas_larga") {
            if (frase.size() != 1) {
              cout << "(No hay información) El mapa no ha sido generado todavía (con el comando crear_mapa)." << endl;
            } else {
              cout << "EXITO Comando valido" << endl;
            }
        }
    }

    return 0;
}