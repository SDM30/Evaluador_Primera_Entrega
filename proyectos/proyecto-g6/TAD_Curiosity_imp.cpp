/*
 * TAD_Curiosity_imp.cpp
 * ----------------------
 * 
 * Comentarios
 * 
 */

#ifndef TAD_CURIOSITY_IMP_CPP
#define TAD_CURIOSITY_IMP_CPP

#include "TAD_Curiosity.h"
#include "Validaciones.h"
#include <fstream>
#include <sstream>
#include <cmath>
//#include <iostream>

using namespace std;

void Curiosity::aggDesplazamiento_mov(string tipo_mov, double magnitud, string unidades){

    Movimiento nuevo_mov(tipo_mov, magnitud, unidades);
    Desplazamiento nuevo_desplazamiento(nuevo_mov);
    this->desplazamientos.push_back(nuevo_desplazamiento);

}

void Curiosity::aggDesplazamiento_ana(string tipo_an, string objeto, string &comentario){

    Analisis nuevo_ana(tipo_an, objeto, comentario);
    Desplazamiento nuevo_desplazamiento(nuevo_ana);
    this->desplazamientos.push_back(nuevo_desplazamiento);

}

void Curiosity::aggDesplazamiento_ana(string tipo_an, string objeto){ //Sobrecarga de métodos, tal como se utilizó para los constructores de Análisis.

    Analisis nuevo_ana(tipo_an, objeto);
    Desplazamiento nuevo_desplazamiento(nuevo_ana);
    this->desplazamientos.push_back(nuevo_desplazamiento);

}

void Curiosity::aggPunto_interes(string tipo_ele, double tamano, string unidad_med, double x, double y){

    Punto_interes nuevo_punto(tipo_ele, tamano, unidad_med, x, y);
    this->puntos_interes.push_back(nuevo_punto);

}

int Curiosity::cargarComandosArchivo(string dir){

    string comando;
    string par1;
    string par2;
    string par3;
    int conteo_comandos_validos = 0;
    int verificacion;
    double numero;

    ifstream archivo(dir, ios::in);
    if(!archivo){
        cout<<"\nEl archivo " << dir << " no se encuentra o no puede leerse\n\n";
        return 0;
    }
    archivo.seekg(0);
    while(getline(archivo, comando)){
        //cout<<comando;
        if(comando.empty()){
            continue;
        }
        stringstream token(comando);
        //getline(token, par1, ' ');
        if(!(token>>par1)){
            continue;
        }
        if (par1 == "avanzar" || par1 == "girar"){
            verificacion = revPar3Archivo(token, par2, par3);
            if(verificacion){
                verificacion = revAgregarMovArchivo(par1, par2, par3, numero);
                if(verificacion){
                    this->aggDesplazamiento_mov(par1, numero, par3);
                    conteo_comandos_validos++;
                }
            }
            
        } else if(par1 == "fotografiar" || par1 == "composicion" || par1 == "perforar"){
            verificacion = revPar2Par3Archivo(token, par2, par3);
            if(verificacion){
                verificacion = revAgregarAnArchivo(par1, par2, par3, verificacion);
                if(verificacion == 2){
                    this->aggDesplazamiento_ana(par1, par2, par3);
                    conteo_comandos_validos++;
                } else{
                    this->aggDesplazamiento_ana(par1, par2);
                    conteo_comandos_validos++;
                }
            }
        }
    }

    archivo.close();
    return conteo_comandos_validos;

}

void Curiosity::eliminarComandos(){ //Método para eliminar todos los comandos del Curiosity antes de insertar nuevos desplazamientos a través de un archivo.

    this->desplazamientos.clear();

}

int Curiosity::cargarElementosArchivo(string dir){

    string comando;
    string par1;
    string par2;
    string par3;
    string par4;
    string par5;
    int conteo_elementos_validos = 0;
    int verificacion;
    double numero;
    double coordX;
    double coordY;

    ifstream archivo(dir, ios::in);
    if(!archivo){
        cout<<"\nEl archivo " << dir << " no se encuentra o no puede leerse\n\n";
        return 0;
    }
    archivo.seekg(0);

    while(getline(archivo, comando)){
        if(comando.empty()){
            continue;
        }
        stringstream token(comando);
        verificacion = revPar5Archivo(token, par1, par2, par3, par4, par5);
        if(verificacion){
            verificacion = revAgregarEleArchivo(par1, par2, par3, par4, par5, numero, coordX, coordY);
            if(verificacion){
                this->aggPunto_interes(par1, numero, par3, coordX, coordY);
                conteo_elementos_validos++;
            }
        }
    }

    archivo.close();
    return conteo_elementos_validos;

}

void Curiosity::eliminarElementos(){ //Método para eliminar todos los puntos de interés del Curiosity antes de insertar nuevos componentes a través de un archivo.

    this->puntos_interes.clear();

}

void Curiosity::guardar(string tipo, string dir){

    if(tipo == "comandos"){
        if(this->desplazamientos.empty()){
            cout<<"\nNo existe informacion de comandos almacenada en memoria.\n\n";
            return;
        }
        ofstream archivo(dir, ios::out);
        list<Desplazamiento>::iterator it = this->desplazamientos.begin();
        for(;it != this->desplazamientos.end(); it++){
            if(it->getEsMov()){
                archivo<<it->getMov().getTipo_mov()<<" "<<it->getMov().getMagnitud()<<" "<<it->getMov().getUnidades()<<endl;
            } else{
                if(it->getAna().getHayComentario()){
                    archivo<<it->getAna().getTipo_an()<<" "<<it->getAna().getObjeto()<<" "<<it->getAna().getComentario()<<endl;
                } else{
                    archivo<<it->getAna().getTipo_an()<<" "<<it->getAna().getObjeto()<<endl;
                }
            }
        }
        archivo.close();
        cout<<"\nComandos cargados en "<<dir<<" correctamente."<<"\n\n";
    } else{
        if(this->puntos_interes.empty()){
            cout<<"\nNo existe informacion de elementos almacenada en memoria.\n\n";
            return;
        }
        ofstream archivo(dir, ios::out);
        vector<Punto_interes>::iterator it = this->puntos_interes.begin();
        for(; it != this->puntos_interes.end(); it++){
            archivo<<it->getTipo_ele()<<" "<<it->getTamano()<<" "<<it->getUnidad_med()<<" "<<it->getX()<<" "<<it->getY()<<endl;
        }
        archivo.close();
        cout<<"\nElementos cargados en "<<dir<<" correctamente."<<"\n\n";
    }

}

void Curiosity::simular_comandos(double x_inicial, double y_inicial){

    double x_final = x_inicial;
    double y_final = y_inicial;
    double conversion_metros; //Se realizan conversiones a metros porque el sistema de coordenadas se encuentra en metros.
    double conversion_radianes; //Se realizan conversiones a radianes, porque las funciones sin() y cos() de la librería cmath, trabajan en radianes.
    double direccion = 0; //Este atributo corresponde a la dirección, en radianes, en la que apunta el Curiosity en cada instante de su exploración.  Se inicializa en 0 para garantizar que el robot se encuentre en dirección hacia los valores positivos (derecha) del eje X.
    const double PI = 3.14159265358979323846;

    if(this->desplazamientos.empty()){
        cout<<"\nNo se han almacenado comandos de desplazamiento para simular.\n\n";
        return;
    }

    list<Desplazamiento>::iterator it = this->desplazamientos.begin();
    for(; it != this->desplazamientos.end(); it++){
        if(it->getEsMov()){
            if(it->getMov().getTipo_mov() == "avanzar"){
                if(it->getMov().getUnidades() == "cm"){
                    conversion_metros = (it->getMov().getMagnitud())/100;
                } else if(it->getMov().getUnidades() == "dm"){
                    conversion_metros = (it->getMov().getMagnitud())/10;
                } else if(it->getMov().getUnidades() == "km"){
                    conversion_metros = (it->getMov().getMagnitud())*1000;
                } else{
                    conversion_metros = it->getMov().getMagnitud();
                }

                x_final += conversion_metros*cos(direccion);
                y_final += conversion_metros*sin(direccion);

            } else{
                if(it->getMov().getUnidades() == "grd"){
                    conversion_radianes = ((it->getMov().getMagnitud())*PI)/180;
                } else{
                    conversion_radianes = it->getMov().getMagnitud();
                }

                direccion += conversion_radianes;

            }
        }
    }

    cout<<"\nLa simulacion de los comandos de desplazamiento almacenados, partiendo de una posicion ("<<x_inicial<<", "<<y_inicial<<"), ubica al Curiosity, finalmente, en el punto ("<<x_final<<", "<<y_final<<") del plano de coordenadas del planeta Marte.\n\n";

}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Comandos de revisión y comprobación:
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Curiosity::revContenidoAn(){

    int i = 1;
    list<Desplazamiento>::iterator it;
    for(it = this->desplazamientos.begin(); it != this->desplazamientos.end(); it++){
        if(!((*it).getEsMov())){
            cout<<"Analisis "<<i++<<endl<<endl;
            if((*it).getAna().getHayComentario()){
                cout<<"Tipo de analisis: "<<(*it).getAna().getTipo_an()<<endl;
                cout<<"Objeto: "<<(*it).getAna().getObjeto()<<endl;
                cout<<"Comentario: "<<(*it).getAna().getComentario()<<endl<<endl;
            } else{
                cout<<"Tipo de analisis: "<<(*it).getAna().getTipo_an()<<endl;
                cout<<"Objeto: "<<(*it).getAna().getObjeto()<<endl<<endl;
            }
        }
    }

}

void Curiosity::revContenidoMov(){

    int i = 1;
    list<Desplazamiento>::iterator it;
    for(it = this->desplazamientos.begin(); it != this->desplazamientos.end(); it++){
        if((*it).getEsMov()){
            cout<<"Movimiento "<<i++<<endl<<endl;
            cout<<"Tipo de movimiento: "<<(*it).getMov().getTipo_mov()<<endl;
            cout<<"Magnitud: "<<(*it).getMov().getMagnitud()<<endl;
            cout<<"Unidad de medida: "<<(*it).getMov().getUnidades()<<endl<<endl;
        }
    }

}

void Curiosity::revContenidoPI(){

    int i = 1;
    vector<Punto_interes>::iterator it;
    for(it = this->puntos_interes.begin(); it != this->puntos_interes.end(); it++){
        
        cout<<"Punto de interes "<<i++<<endl<<endl;
        cout<<"Tipo de componente: "<<(*it).getTipo_ele()<<endl;
        cout<<"Tamano: "<<(*it).getTamano()<<endl;
        cout<<"Unidad de medida: "<<(*it).getUnidad_med()<<endl;
        cout<<"Coordenada X: "<<(*it).getX()<<endl;
        cout<<"Coordenada Y: "<<(*it).getY()<<endl<<endl;
        
    }

}

#endif

//EOF - TAD_Curiosity_imp.cpp