#include "Validaciones.h"
#include "TAD_Curiosity.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>

using namespace std;

//Se utilizan int y no bool para los retornos de las funciones porque para el bloque revPar2Par3 se requieren 3 tipos de resultado. De esta forma, para estandarizar, se utiliza generación de enteros en todas las funciones.

int main(){

    string comando;
    string orden;
    string par1;
    string par2;
    string par3;
    string par4;
    string par5;
    double numero;
    double coordX;
    double coordY;
    double coordX2;
    double coordY2;
    int verificacion;
    int conteo;

    //Creación del Robot:
    Curiosity robot_curiosity;

    cout<<"\n$ ";
    getline(cin, comando);

    //No es posible realizar un getline(cin, comando, " "), porque los parámetros del comando no se captarían. Es necesario tokenizar.
    
    while(comando != "salir"){

        stringstream token(comando);
        getline(token, orden, ' ');
        //token>>orden;

        if(orden == "ayuda"){
            if(!(token>>par1)){
                lista_comandos();
            } else if(!(token>>par2)){
                ayudaComando(par1);
            } else{
                cout<<"\nSe ingresaron mas parametros de los requeridos. Recuerde que si desea observar la estructura especifica \nde un comando debe escribir la palabra --ayuda-- acompanada del comando que desea rectificar.\n\n";
            }

        } else if(orden == "cargar_comandos"){

            verificacion = revPar1(token, orden, par1);
            if(verificacion){
                verificacion = revArchivo(par1);
                if(verificacion){
                    //Desarrollo del comando:
                    robot_curiosity.eliminarComandos();
                    conteo = robot_curiosity.cargarComandosArchivo(par1);
                    cout<<"\n"<<"Se cargaron "<<conteo<<" comandos adecuadamente desde el archivo "<<par1<<".\n\n";
                }
            }

        } else if(orden == "cargar_elementos"){

            verificacion = revPar1(token, orden, par1);
            if(verificacion){
                verificacion = revArchivo(par1);
                if(verificacion){
                    robot_curiosity.eliminarElementos();
                    conteo = robot_curiosity.cargarElementosArchivo(par1);
                    cout<<"\n"<<"Se cargaron "<<conteo<<" elementos adecuadamente desde el archivo "<<par1<<".\n\n";
                }
            }
                
        } else if(orden == "agregar_movimiento"){

            verificacion = revPar3(token, orden, par1, par2, par3);
            if(verificacion){
                verificacion = revAgregarMov(orden, par1, par2, par3, numero);
                if(verificacion){
                    //Desarrollo del comando:
                    robot_curiosity.aggDesplazamiento_mov(par1, numero, par3);
                    //Mensaje de éxito:
                    cout<<"\nEl comando de movimiento ha sido agregado satisfactoriamente.\n\n";
                }
            }
    
        } else if(orden == "agregar_analisis"){

            verificacion = revPar2Par3(token, orden, par1, par2, par3);
            if(verificacion){
                verificacion = revAgregarAn(orden, par1, par2, par3, verificacion);
                if(verificacion){
                    //Desarrollo del comando:
                    if(verificacion == 2){
                        robot_curiosity.aggDesplazamiento_ana(par1, par2, par3);
                        //Mensaje de éxito:
                        cout<<"\nEl comando de analisis (con comentario) ha sido agregado satisfactoriamente.\n\n";
                    } else{
                        robot_curiosity.aggDesplazamiento_ana(par1, par2);
                        //Mensaje de éxito:
                        cout<<"\nEl comando de analisis (sin comentario) ha sido agregado satisfactoriamente.\n\n";
                    }
                }
            }
                
        } else if(orden == "agregar_elemento"){

            verificacion = revPar5(token, orden, par1, par2, par3, par4, par5);
            if(verificacion){
                verificacion = revAgregarEle(orden, par1, par2, par3, par4, par5, numero, coordX, coordY);
                if(verificacion){
                    //Desarrollo del comando:
                    robot_curiosity.aggPunto_interes(par1, numero, par3, coordX, coordY);
                    //Mensaje de éxito:
                    cout<<"\nEl elemento ha sido agregado satisfactoriamente.\n\n";
                }
            }
                
        } else if(orden == "guardar"){

            verificacion = revPar2(token, orden, par1, par2);
            if(verificacion){
                verificacion = revGuardar(orden, par1, par2);
                if(verificacion){
                    //Desarrollo del comando:
                    robot_curiosity.guardar(par1, par2);
                }
            }
                
        } else if(orden == "simular_comandos"){

            verificacion = revPar2(token, orden, par1, par2);
            if(verificacion){
                verificacion = revSimCom(orden, par1, par2, coordX, coordY);
                if(verificacion){
                    //Desarrollo del comando:
                    robot_curiosity.simular_comandos(coordX, coordY);
                }
            }
                
        } //else if(orden == "salir"){
            
            //Esta parte se puede eliminar, porque si se percibe una palabra salir, el bucle finalizará en su siguiente iteración.
            //Sería posible evaluar si se ingresó un comando con la palabra inicial salir, pero con parámetros o unidades de texto adicionales.
            //} 

        else if(orden == "ubicar_elementos"){

            verificacion = revPar0(token, orden);
            if(verificacion){
                cout<<"\nExito. El comando posee el formato adecuado.\n\n";
                //codigo para desarrollar comando;
            }
                
        } else if(orden == "en_cuadrante"){

            verificacion = revPar4(token, orden, par1, par2, par3, par4);
            if(verificacion) {
                verificacion = revEnCuad(orden, par1, par2, par3, par4, coordX, coordY, coordX2, coordY2);
                if(verificacion) {
                    cout<<"\nExito. El comando posee el formato adecuado.\n\n";
                    //codigo para desarrollar comando;
                }   
            }
                
        } else if(orden == "crear_mapa"){

            verificacion = revPar1(token, orden, par1);
            if(verificacion){
                verificacion = revCreMap(orden, par1, numero);
                if(verificacion) {
                    cout<<"\nExito. El comando posee el formato adecuado.\n\n";
                    //codigo para desarrollar comando;
                }
            }
                
        } else if(orden == "ruta_mas_larga"){

            verificacion = revPar0(token, orden);
            if(verificacion){
                cout<<"\nExito. El comando posee el formato adecuado.\n\n";
                //codigo para desarrollar comando;
            }
                
        } else{

            cout<<"\nEl comando ingresado no existe. Para mas informacion sobre los comandos disponibles, revisar --ayuda--.\n\n";
                
        }

        cout<<"$ ";
        getline(cin, comando);
        
    }
    
    //Estas últimas 3 funciones, únicamente tienen como propósito comprobar la correcta inclusión de comandos y elementos en la memoria del Curiosity.

    //robot_curiosity.revContenidoAn();
    //robot_curiosity.revContenidoMov();
    //robot_curiosity.revContenidoPI();

    cout<<"\nPresione cualquier tecla para finalizar...";
    cin.get();
    return 0;

}

// eof - curiosity_main.cpp