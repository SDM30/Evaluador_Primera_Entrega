#include "Validaciones.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>

using namespace std;

//Implementacion de funciones:

void lista_comandos(){

    cout<<"\nPara este programa, los comandos permitidos son:\n\n";
    cout<<"ayuda\n";
    cout<<"ayuda --comando del que se requiere informacion--.\n";
    cout<<"cargar_comandos\n";
    cout<<"cargar_elementos\n";
    cout<<"agregar_movimiento\n";
    cout<<"agregar_analisis\n";
    cout<<"agregar_elemento\n";
    cout<<"guardar\n";
    cout<<"simular_comandos\n";
    cout<<"salir\n";
    cout<<"ubicar_elementos\n";
    cout<<"en_cuadrante\n";
    cout<<"crear_mapa\n";
    cout<<"ruta_mas_larga\n\n";

}

void ayudaComando(string par1){

    if(par1 == "cargar_comandos"){
        cout<<"\nEste comando cuenta con 1 paramentro y su estructura es la siguiente:\n\n";
        cout<<par1<<" nombre_archivo\n\n";
        cout<<"Especificaciones de su parametro:\n";
        cout<<"- nombre_archivo: corresponde al nombre de algun archivo existente, con su extension, en la carpeta empleada.\n\n";
    } else if(par1 == "cargar_elementos"){
        cout<<"\nEste comando cuenta con 1 paramentro y su estructura es la siguiente:\n\n";
        cout<<par1<<" nombre_archivo\n\n";
        cout<<"Especificaciones de su parametro:\n";
        cout<<"- nombre_archivo: corresponde al nombre de algun archivo existente, con su extension, en la carpeta empleada.\n\n";
    } else if(par1 == "agregar_movimiento"){
        cout<<"\nEste comando cuenta con 3 paramentros y su estructura es la siguiente:\n\n";
        cout<<par1<<" tipo_mov magnitud unidad_med\n\n";
        cout<<"Especificaciones de sus parametros:\n\n";
        cout<<"- tipo_mov: corresponde al tipo de movimiento a efectuar. Puede ser avanzar o girar.\n";
        cout<<"- magnitud: corresponde a la cuantificacion del desplazamiento. Se reciben valores decimales y negativos. Dado que el curiosity se encuentra \n  posicionado, de forma predeterminada, hacia la derecha del eje X de un plano cartesiano, los valores negativos, si se trata de un avance, \n  corresponden a movimientos hacia el contrario de su orientacion (hacia la izquierda del eje X si no se ha girado el vehiculo aun); si se \n  trata de un giro, los negativos producen movimiento a favor de las manecillas del reloj. Los positivos propician desplazamientos contrarios.\n";
        cout<<"- unidad_med: corresponde a la unidad en que se mide el desplazamiento. Para el caso de avanzar, las escalas permitidas son: cm, dm, m o km. \n  Por otra parte, si se trata de un giro, unicamente se reciben las unidades grd o rad.\n\n";
    } else if(par1 == "agregar_analisis"){
        cout<<"\nEste comando cuenta con 2 o 3 paramentros, puesto que uno de ellos es opcional, y su estructura es la siguiente:\n\n";
        cout<<par1<<" tipo_analisis objeto comentario(opcional)\n\n";
        cout<<"Especificaciones de sus parametros:\n\n";
        cout<<"- tipo_analisis: corresponde al tipo de analisis que desea realizarse. Puede ser de tres tipos: fotografiar, composicion o perforar.\n";
        cout<<"- objeto: representa el objeto a analizar (roca, arena, monticulo, ...). No hay unos tipos estrictamente definidos para este parametro.\n";
        cout<<"- comentario: este es un parametro que puede o no incluirse. En caso de agregar un comentario que anada informacion sobre el analisis, \n  se requiere que se encuentre encerrado por comillas simples (ej: 'roca_cuadrante_32')\n\n";
    } else if(par1 == "agregar_elemento"){
        cout<<"\nEste comando cuenta con 5 paramentros, y su estructura es la siguiente:\n\n";
        cout<<par1<<" tipo_comp tamano unidad_med coordX coordY\n\n";
        cout<<"Especificaciones de sus parametros:\n\n";
        cout<<"- tipo_comp: determina el tipo de componente o elemento que se busca agregar. Puede ser de 4 tipos: roca, crater, monticulo o duna.\n";
        cout<<"- tamano: corresponde a un valor real que establece que tan grande es el elemento en cuestion. Se aceptan decimales, pero no es \n  posible introducir valores negativos.\n";
        cout<<"- unidad_med: representa la unidad en que se tasa el tamano del componente. Las escalas permitidas son: cm, dm, m y km.\n";
        cout<<"- coordX: es la coordenada en el eje X que define la ubicacion del elemento en el plano cartesiano del suelo marciano utilizado \n  por el vehiculo.\n";
        cout<<"- coordX: es la coordenada en el eje Y que define la ubicacion del elemento en el plano cartesiano del suelo marciano utilizado \n  por el vehiculo.\n\n";
    } else if(par1 == "guardar"){
        cout<<"\nEste comando cuenta con 2 paramentros, y su estructura es la siguiente:\n\n";
        cout<<par1<<" tipo_archivo nombre_archivo\n\n";
        cout<<"Especificaciones de sus parametros:\n\n";
        cout<<"- tipo_archivo: define la clase de archivo que se almacenara, de acuerdo con su contenido. Existen dos tipos: comandos, que reserva \n  informacion sobre comandos de movimiento y de analisis, y elementos que condensa datos sobre componentes o puntos de interes conocidos \n  sobre el suelo marciano.\n";
        cout<<"- nombre_archivo: establece el nombre del archivo a generar para almacenar la informacion correspondiente. Si no se desea que se conserve \n  con un tipo de archivo generico, se debe anadir la extension del documento.\n\n";
    } else if(par1 == "simular_comandos"){
        cout<<"\nEste comando cuenta con 2 paramentros, y su estructura es la siguiente:\n\n";
        cout<<par1<<" coordX coordY\n\n";
        cout<<"Especificaciones de sus parametros:\n\n";
        cout<<"- coordX: refleja la coordenada en el eje X de la ubicacion actual del vehiculo, a partir de la cual se simularan los comandos respectivos.\n";
        cout<<"- coordY: refleja la coordenada en el eje Y de la ubicacion actual del vehiculo, a partir de la cual se simularan los comandos respectivos.\n\n";
    } else if(par1 == "salir"){
        cout<<"\nEste comando no cuenta con parametros. Su estructura unicamente incluye el nombre de la orden, de la siguiente forma:\n\n";
        cout<<par1<<"\n\n";
        cout<<"Es necesario aclarar que este comando no genera ningun resultado por pantalla. Simplemente culmina el programa.\n\n";
    } else if(par1 == "ubicar_elementos"){
        cout<<"\nEste comando no cuenta con parametros. Su estructura unicamente incluye el nombre de la orden, de la siguiente forma:\n\n";
        cout<<par1<<"\n\n";
        cout<<"Si bien no se incluyen parametros, el comando en cuestion utiliza como insumo la informacion almacenada en memoria sobre los \npuntos de interes para vehiculo.\n\n";
    } else if(par1 == "en_cuadrante"){
        cout<<"\nEste comando cuenta con 4 paramentros, y su estructura es la siguiente:\n\n";
        cout<<par1<<" coordX1 coordX2 coordY1 coordY2\n\n";
        cout<<"Especificaciones de sus parametros:\n\n";
        cout<<"- coordX1: expresa la coordenada inicial, en el eje X, del cuadrante sobre el que se han de buscar componentes.\n";
        cout<<"- coordX2: representa la coordenada final, en el eje X, del cuadrante sobre el que se han de buscar componentes.\n";
        cout<<"- coordY1: identifica la coordenada inicial, en el eje Y, del cuadrante sobre el que se han de buscar componentes.\n";
        cout<<"- coordX2: establece la coordenada final, en el eje Y, del cuadrante sobre el que se han de buscar componentes.\n\n";
        cout<<"Es pertinente resaltar que, previo a ejecutar este comando, es recomendable haber efectuado la orden --ubicar_elementos--, \nde modo que la busqueda por cuadrantes sea mas efectiva.\n\n";
    } else if(par1 == "crear_mapa"){
        cout<<"\nEste comando cuenta con 1 parametro, y su estructura es la siguiente:"<<endl<<endl;
        cout<<par1<<" coeficiente_conectividad"<<endl<<endl;
        cout<<"Especificaciones de su parametro:\n\n";
        cout<<"- coeficiente_conectividad: corresponde a un valor numerico que representa la proporcion de componentes cercanos que podria \n  tener un elemento respecto al total de objetos, en el plano, de los que se dispone en memoria. Dado que es una proporcion, \n  no puede ser negativa ni superior a 1. Es decir, debe hallarse entre 0 y 1, con valores decimales."<<endl<<endl;
    } else if(par1 == "ruta_mas_larga"){
        cout<<"\nEste comando no cuenta con parametros. Su estructura unicamente incluye el nombre de la orden, de la siguiente forma:\n\n";
        cout<<par1<<"\n\n";
        cout<<"Para ejecutar este comando, primero se debe haber generado un mapa de elementos, contemplando sus distancias, a traves \ndel comando --crear_mapa--. De esta manera, esta orden retornara el camino mas extenso posible entre dos componentes, no \nde acuerdo a su distancia euclidiana, sino segun la medida del sendero que atraviece una serie de objetos hasta alcanzar \nsu destino.\n\n";
    } else{
        cout<<"\nEl comando para el que esta solicitando ayuda no existe. Revisar --ayuda-- para mas informacion sobre los comandos disponibles.\n\n";
    }

}

int revPar0(stringstream &token, string orden){

    string par1;
    if(token>>par1){
        cout<<"\nSe ingresaron mas parametros de los requeridos. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
        return 0;
    } else{
        return 1;
    }

}

int revPar1(stringstream &token, string orden, string &par1){

    string par2;
    if(!(token>>par1)){
        cout<<"\nNo se ingresaron los parametros suficientes. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
        return 0;
    } else if(token>>par2){
        cout<<"\nSe ingresaron mas parametros de los requeridos. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
        return 0;
    } else{
        return 1;
    }

}

int revPar3(stringstream &token, string orden, string &par1, string &par2, string &par3){

    string par4;
    if(!(token>>par1) || !(token>>par2) || !(token>>par3)){
        cout<<"\nNo se ingresaron los parametros suficientes. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
        return 0;
    } else if(token>>par4){
        cout<<"\nSe ingresaron mas parametros de los requeridos. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
        return 0;
    } else{
        return 1;
    }

}

int revAgregarMov(string orden, string &par1, string &par2, string &par3, double &numero){

    if(par1 == "avanzar" || par1 == "girar"){
        try{
            numero = stod(par2);
        } catch(invalid_argument&){
            cout<<"\nLa magnitud del movimiento ingresado (parametro 2) no es numerica. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
            return 0;
        }
        if(par1 == "avanzar"){
            if(par3 == "cm" || par3 == "dm" || par3 == "m" || par3 == "km"){
                return 1;
            } else{
                cout<<"\nLa unidad de medida ingresada (parametro 3) no es valida. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
                return 0;
            }
        } else{
            if(par3 == "grd" || par3 == "rad"){
                return 1;
            }
            else{
                cout<<"\nLa unidad de medida ingresada (parametro 3) no es valida. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
                return 0;
            }
        }

    } else{
        cout<<"\nEl movimiento ingresado (parametro 1) no es valido. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
        return 0;
    }

}

int revPar2Par3(stringstream &token, string orden, string &par1, string &par2, string &par3){

    if(!(token>>par1) || !(token>>par2)){
        cout<<"\nNo se ingresaron los parametros suficientes. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
        return 0;
    } else if(token>>ws && getline(token, par3)){
            return 2; //El dos significa que el número de parámetros es 3 (existe comentario).
    } else{
        return 1; //El 1 representa la situación en que el número de parámetros es 2, lo cual sigue siendo válido, pero no existe comentario.
    }
    
}

int revAgregarAn(string orden, string &par1, string &par2, string &par3, int verificacion){

    if(par1 == "fotografiar" || par1 == "composicion" || par1 == "perforar"){
        //No se verifica el tipo de objeto ingresado porque no existe una lista declarada de objetos validos.
        if(verificacion == 2){
            if(par3[0] == '\'' && par3[(par3.length() - 1)] == '\''){ //¿Es necesario también evaluar y descartar el comando si el comentario se encuentra entre comillas, pero vacío?
                //cout<<"valido";
                return 2;
            } else{
                cout<<"\nEl comentario ingresado no cuenta con un el formato adecuado. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
                return 0;
            }
        } else{
            return 1;
        }

    } else{
        cout<<"\nEl tipo de analisis ingresado (parametro 1) no es valido. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
        return 0;
    }

}

int revPar4(stringstream &token, string orden, string &par1, string &par2, string &par3, string &par4){

    string par5;
    if(!(token>>par1) || !(token>>par2) || !(token>>par3) || !(token>>par4)){
        cout<<"\nNo se ingresaron los parametros suficientes. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
        return 0;
    } else if(token>>par5){
        cout<<"\nSe ingresaron mas parametros de los requeridos. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
        return 0;
    } else{
        return 1;
    }

}

int revPar5(stringstream &token, string orden, string &par1, string &par2, string &par3, string &par4, string &par5){

    string par6;
    if(!(token>>par1) || !(token>>par2) || !(token>>par3) || !(token>>par4) || !(token>>par5)){
        cout<<"\nNo se ingresaron los parametros suficientes. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
        return 0;
    } else if(token>>par6){
        cout<<"\nSe ingresaron mas parametros de los requeridos. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
        return 0;
    } else{
        return 1;
    }

}

int revAgregarEle(string orden, string &par1, string &par2, string &par3, string &par4, string &par5, double &numero, double &coordX, double &coordY){

    if(par1 == "roca" || par1 == "crater" || par1 == "monticulo" || par1 == "duna"){
        try{
            numero = stod(par2);
        } catch(invalid_argument&){
            cout<<"\nLa magnitud del movimiento ingresado (parametro 2) no es numerica. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
            return 0;
        }
        if(numero < 0){
            cout<<"\nLa magnitud del movimiento ingresado (parametro 2) no puede ser negativa. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
            return 0;
        }
        if(par3 == "cm" || par3 == "dm" || par3 == "m" || par3 == "km"){
            try{
            coordX = stod(par4);
            coordY = stod(par5);
            } catch(invalid_argument&){
                cout<<"\nLas coordenadas establecidas no son numericas. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
                return 0;
            }
            return 1;
        } else{
            cout<<"\nLa unidad de medida ingresada (parametro 3) no es valida. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
            return 0;
        }
    } else{
        cout<<"\nEl tipo de componente ingresado (parametro 1) no es valido. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
        return 0;
    }

}

int revPar2(stringstream &token, string orden, string &par1, string &par2){

    string par3;
    if(!(token>>par1) || !(token>>par2)){
        cout<<"\nNo se ingresaron los parametros suficientes. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
        return 0;
    } else if(token>>par3){
        cout<<"\nSe ingresaron mas parametros de los requeridos. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
        return 0;
    } else{
        return 1;
    }

}

int revGuardar(string orden, string &par1, string &par2){

    if(par1 == "comandos" || par1 == "elementos"){
        //ofstream archivo(par2, ios::out); //¿Verificar que par2 posea extensión?
        //if(!archivo){
            //cout<<"\nOcurrió un error con la dirección de archivo ingresada: " << par2 << "\n\n";
            //return 0;
        //} else{
            //archivo.close();
            return 1;
        //}
    } else{
        cout<<"\nEl tipo de archivo ingresado (parametro 1) no es valido. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
        return 0;
    }

}

int revSimCom(string orden, string &par1, string &par2, double &coordX, double &coordY){

    try{
        coordX = stod(par1);
        coordY = stod(par2);
    } catch(invalid_argument&){
        cout<<"\nLas coordenadas establecidas no son numericas. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
        return 0;
    }
    return 1;

}

int revEnCuad(string orden, string par1, string par2, string par3, string par4, double &coordX, double &coordY, double &coordX2, double &coordY2){

    stringstream ss1(par1);
    stringstream ss2(par2);
    stringstream ss3(par3);
    stringstream ss4(par4);

    bool p1_valido = (ss1 >> coordX) && (ss1.eof()); //El eof permite verificar que el número que se almacena no está acompañado de caracteres adicionales no requeridos.
    bool p2_valido = (ss2 >> coordX2) && (ss2.eof());
    bool p3_valido = (ss3 >> coordY) && (ss3.eof());
    bool p4_valido = (ss4 >> coordY2) && (ss4.eof());

    if (p1_valido == false || p2_valido == false || p3_valido == false || p4_valido == false) {
        cout<<"\nLas coordenadas establecidas no son numericas. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
        return 0;
    }
    if(coordX>coordX2 || coordY>coordY2){
        cout<<"\nLa segunda coordenada de X o Y no puede ser mayor que la primera. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
        return 0;
    }

    return 1;

}

int revCreMap(string orden, string par1, double &numero){

    stringstream ss1(par1);
    bool p1_valido = (ss1 >> numero) && (ss1.eof());

    if(!p1_valido){
        cout<<"\nLas coordenadas establecidas no son numericas. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
        return 0;
    } 
    
    if(numero > 1 || numero < 0){
        cout<<"\nEl coeficiente de conectividad debe hallarse entre 0 y 1. Para mas informacion sobre la estructura de este comando, revisar --ayuda " << orden << "--.\n\n";
        return 0;
    } else{
        return 1;
    }

}

int revArchivo(string dir){

    ifstream archivo(dir, ios::in);
        if(!archivo){
            cout<<"\nEl archivo " << dir << " no se encuentra o no puede leerse\n\n";
            return 0;
        } else{
            archivo.seekg(0, ios::end);
            if(archivo.tellg() == 0){
                cout<<"\n" << dir << " no contiene comandos\n\n";
                archivo.close();
                return 0;
            } else{
                cout<<"\n" << dir << " listo para procesarse...\n";
                archivo.close();
                return 1;
            }
        }

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Nuevas funciones de verificación:
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


int revPar3Archivo(stringstream &token, string &par2, string &par3){

    string par4;
    if(!(token>>par2) || !(token>>par3)){
        return 0;
    } else if(token>>par4){
        return 0;
    } else{
        return 1;
    }

}

int revAgregarMovArchivo(string &par1, string &par2, string &par3, double &numero){

    try{
        numero = stod(par2);
    } catch(invalid_argument&){
        return 0;
    }
    if(par1 == "avanzar"){
        if(par3 == "cm" || par3 == "dm" || par3 == "m" || par3 == "km"){
            return 1;
        } else{
            return 0;
        }
    } else{
        if(par3 == "grd" || par3 == "rad"){
            return 1;
        }
        else{
            return 0;
        }
    }

}

int revPar2Par3Archivo(stringstream &token, string &par2, string &par3){

    if(!(token>>par2)){
        return 0;
    } else if(token>>ws && getline(token, par3)){
            return 2; //El dos significa que el número de parámetros es 3 (existe comentario).
    } else{
        return 1; //El 1 representa la situación en que el número de parámetros es 2, lo cual sigue siendo válido, pero no existe comentario.
    }
    
}

int revAgregarAnArchivo(string &par1, string &par2, string &par3, int verificacion){

    //No se verifica el tipo de objeto ingresado porque no existe una lista declarada de objetos validos.
    if(verificacion == 2){
        if(par3[0] == '\'' && par3[(par3.length() - 1)] == '\''){ //¿Es necesario también evaluar y descartar el comando si el comentario se encuentra entre comillas, pero vacío?
            return 2;
        } else{
            return 0;
        }
    } else{
        return 1;
    }

}

int revPar5Archivo(stringstream &token, string &par1, string &par2, string &par3, string &par4, string &par5){

    string par6;
    if(!(token>>par1) || !(token>>par2) || !(token>>par3) || !(token>>par4) || !(token>>par5)){
        return 0;
    } else if(token>>par6){
        return 0;
    } else{
        return 1;
    }

}

int revAgregarEleArchivo(string &par1, string &par2, string &par3, string &par4, string &par5, double &numero, double &coordX, double &coordY){

    if(par1 == "roca" || par1 == "crater" || par1 == "monticulo" || par1 == "duna"){
        try{
            numero = stod(par2);
        } catch(invalid_argument&){
            return 0;
        }
        if(numero < 0){
            return 0;
        }
        if(par3 == "cm" || par3 == "dm" || par3 == "m" || par3 == "km"){
            try{
            coordX = stod(par4);
            coordY = stod(par5);
            } catch(invalid_argument&){
                return 0;
            }
            return 1;
        } else{
            return 0;
        }
    } else{
        return 0;
    }

}

// eof - Validaciones_imp.cpp
