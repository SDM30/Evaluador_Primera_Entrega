//funciones
#include "consola.h"


//de la logica interna
#include "interfaz.h"
#include <iostream>
#include <sstream>

using I = Interfaz; //para no andar escribiendo Interfaz::

void Consola::ayuda(std::string comando)
{
    I::prinTitle2("-- Menu de ayuda --");
    if(comando == "cargar_comandos") { 
        I::prinTitle("cargar_comando"); 
        I::prinText("Descripcion: Carga en memoria los comandos de desplazamiento contenidos en el archivo identificado"); 
        I::prinText("por nombre_archivo , es decir, utiliza adecuadamente las estructuras lineales para cargar la informacion"); 
        I::prinText("de los comandos en memoria. Si dentro de la misma sesion de trabajo ya se han cargado otros archivos"); 
        I::prinText("de comandos (usando el comando cargar_comandos), la informacion debe sobreescribirse en memoria,"); 
        I::prinText("es decir, no se deben combinar informaciones de comandos de diferentes archivos."); 
    }
    else if(comando == "cargar_elementos")
    {
        I::prinTitle("cargar_elementos");
        I::prinText("Descripcion: Carga en memoria los datos de puntos de interés o elementos contenidos en el archivo");
        I::prinText("identificado por nombre_archivo , es decir, utiliza adecuadamente las estructuras lineales para cargar");
        I::prinText("la informacion de los elementos en memoria. Si dentro de la misma sesion de trabajo ya se han cargado");
        I::prinText("otros archivos de puntos de interés (usando el comando cargar_elementos), la informacion debe");
        I::prinText("sobreescribirse en memoria, es decir, no se deben combinar informaciones de elementos de diferentes");
        I::prinText("archivos.");
    }
    else if(comando == "agregar_movimiento")
    {
        I::prinTitle("agregar_movimiento");
        I::prinText("Descripcion: Agrega el comando de movimiento descrito a la lista de comandos del robot “Curiosity”. El");
        I::prinText("movimiento puede ser de dos tipos: avanzar o girar. La magnitud corresponde al valor del");
        I::prinText("movimiento; si es avanzar, el número de unidades que se espera avanzar, si es girar la cantidad de grados");
        I::prinText("que debe girar. La unidad de medida corresponde a la convencion con la que se mide la magnitud del");
        I::prinText("movimiento, de acuerdo a la tabla presentada anteriormente. Si no se envía la informacion completa");
        I::prinText("y adecuada del comando de movimiento, éste no puede agregarse a la lista de los comandos que se");
        I::prinText("enviarán al robot desde la tierra.");
    }
    else if(comando == "agregar_analisis")
    {
        I::prinTitle("agregar_analisis");
        I::prinText("descripcion: Agrega el comando de análisis descrito a la lista de comandos del robot “Curiosity”. El");
        I::prinText("análisis puede ser de tres tipos: fotografiar, composicion o perforar. El objeto es el nombre del");
        I::prinText("elemento que se quiere analizar (roca, arena, monticulo, ...). El comentario es opcional y permite agregar");
        I::prinText("más informacion sobre el elemento o el análisis, este comentario estará encerrado entre comillas simples");
        I::prinText("(ejemplo: 'roca_cuadrante_32'). Si no se envía la informacion completa y adecuada del comando de");
        I::prinText("análisis, éste no puede agregarse a la lista de los comandos que se enviarán al robot desde la tierra.");
    }
    else if(comando == "agregar_elemento")
    {
        I::prinTitle("agregar_elemento");
        I::prinText("Descripcion: Agrega el componente o elemento descrito a la lista de puntos de interés del robot");
        I::prinText("“Curiosity”. El tipo de componente puede ser uno entre roca, crater, monticulo o duna. El tamaño es");
        I::prinText("un valor real que da cuenta de qué tan grande es el elemento; y la unidad de medida complementa este");
        I::prinText("valor con la convencion que se uso para su medicion, de acuerdo a la tabla presentada anteriormente.");
        I::prinText("Finalmente, las coordenadas x y y corresponden a números reales que permiten conocer la ubicacion del");
        I::prinText("elemento en el sistema de coordenadas del suelo marciano utilizado por el vehículo. Si no se envía la");
        I::prinText("informacion completa y adecuada del elemento, éste no puede agregarse a la lista de puntos de interés");
        I::prinText("que se enviarán al robot desde la tierra.");
    }
    else if(comando == "guardar")
    {
        I::prinTitle("guardar");
        I::prinText("Descripcion: Guarda en el archivo nombre_archivo la informacion solicitada de acuerdo al tipo de");
        I::prinText("archivo: comandos almacena en el archivo la informacion de comandos de movimiento y de análisis que");
        I::prinText("debe ejecutar el robot, elementos almacena en el archivo la informacion de los componentes o puntos");
        I::prinText("de interés conocidos en el suelo marciano.");
    }
    else if(comando == "simular_comandos")
    {
        I::prinTitle("simular_comandos");
        I::prinText("Descripcion: Permite simular el resultado de los comandos de movimiento que se enviarán al robot");
        I::prinText("“Curiosity” desde la Tierra, facilitando asi la validacion de la nueva posicion en la que podría ubicarse.");
        I::prinText("Para ejecutarse adecuadamente, requiere conocer la posicion actual (coordenadas x y y) del vehículo.");
        I::prinText("A partir de la posicion actual, se asume que el “Curiosity” está orientado mirando hacia la parte derecha");
        I::prinText("del eje x en un sistema cartesiano (hacia la derecha). Los ángulos de giro positivos generan movimiento");
        I::prinText("en el sentido contrario de las manecillas del reloj, mientras que los ángulos de giro negativos generan");
        I::prinText("movimiento en el sentido de las manecillas del reloj. Hay que tener en cuenta que solo los comandos de");
        I::prinText("movimiento son necesarios, no los de análisis.");
    }
    else if(comando == "salir")
    {
        I::prinTitle("salir");
        I::prinText("Descripcion: Termina la ejecucion de la aplicacion.");
    }
    else if(comando == "general")
    {
        I::prinTitle2("Componente 1: Manejo de informacion");

        I::printError("(de momento solo estos estan disponibles)");

        I::prinText("cargar_comandos nombre_archivo");
        I::prinText("cargar_elementos nombre_archivo");
        I::prinText("agregar_movimiento tipo_mov magnitud unidad_med");
        I::prinText("agregar_analisis tipo_analisis objeto comentario");
        I::prinText("agregar_elemento tipo_comp tama\xa4o unidad_med coordX coordY"); //brosito si necesitas poner la enie es con \xa4
        I::prinText("guardar tipo_archivo nombre_archivo");
        I::prinText("simular_comandos coordX coordY");

        std::cout<<std::endl;

        I::prinTitle2("Componente 2: Planeacion de dezplazamientos");

        I::prinText("ubicar_elementos");
        I::prinText("en_cuadrante coordX1 coordX2 coordY1 coordY2");

        std::cout<<std::endl;

        I::prinTitle2("Componente 3: Recorridos entre puntos de interes");

        I::prinText("crear_mapa coeficiente_conectividad");
        I::prinText("ruta_mas_larga");

        std::cout<<std::endl;
        
        I::prinTitle2("salir");
    }

}

std::string Consola::ingresoConsola(bool& control)
{
    std::string ingreso;
    getline(std::cin, ingreso);
    if(ingreso == "salir")
    {
        control = false;

        return "salir";
    }
    return ingreso;
}

std::vector<std::string> Consola::separarString(std::string input)
{

    //Ya vi que es mejor el ss porque con getline separando por espacios como que se muere mucho. . .
    std::vector <std::string> resultado;
    std::stringstream ss(input);
    std::string linea;

    while(ss >> linea)
    {
        resultado.push_back(linea);
    }

    return resultado;
}


void Consola::llamarFunciones(std::vector<std::string> separadas)
{
    //Aquí va lo feo que separa todo el menú

    std::string general = separadas[0];

    //Pensé en hacer case switch pero toca usar una enumeracion y se vuelve menos legible
    if(general == "cargar_comandos")
    {
        //este metodo verifica si hay un segundo elemento, si no lo hay, muestra un mensaje de numero incorrecto de parametros, si lo hay, llama a la funcion con el segundo elemento como parametro
        if(separadas.size() < 2){ 
            I::printError("Faltan parametros para cargar_comandos");
            return;
        }
        else 
            c.cargarComandos(separadas[1]);
    }
    else if(general == "cargar_elementos")
    {
        if(separadas.size() < 2)
        {
            I::printError("Faltan parametros para cargar_elementos");
            return;
        }
        
        if(separadas[1].empty()){
            I::printError("Ingrese un nombre de archivo valido. . .");
            return;
        }
        else
            c.cargarElementos(separadas[1]); //me decia que era ambiguo, por eso el Comunicaciones::
    }
    else if(general == "agregar_elemento")
    {
        if(separadas.size() < 6)
        { 
            I::printError("No hay parametros suficientes para agregar_elemento");
            return;
        }
        c.agregarElemento(separadas[1], separadas[2], separadas[3], separadas[4], separadas[5]);
    }
    else if(general == "agregar_movimiento")
    {
        if(separadas.size() < 4)
        {
            I::printError("No hay suficientes parametros para agregar el movimiento");
            return;
        }
        c.agregarMovimiento(separadas[1], separadas[2], separadas[3]);
    }
    else if(general == "agregar_analisis")
    {
        if(separadas.size() < 3)
        {
            I::printError("No hay suficientes parametros para agregar el analisis");
            return;
        }

        std::string comentario = "";
        // Si hay más de 3 elementos, significa que hay un comentario 
        if(separadas.size() >= 4)
        {
            //El .size() retorna un unsigned int
            for(unsigned int i = 3; i < separadas.size(); ++i)
            {
                //Esto solo hace que se añada el espacio donde va y al final no se agregue
                //Tipo para que quede "hola mundo" y no "hola mundo "
                comentario += separadas[i] + (i == separadas.size() - 1 ? "" : " ");
            }

            // Validar que el comentario completo empiece y termine con comillas simples
            if(comentario.front() != '\'' || comentario.back() != '\'')
            {
                I::printError("El comentario tiene que estar entre comillas simples (ej: 'comentario largo')");
                return;
            }
        }
        c.agregarAnalisis(separadas[1], separadas[2], comentario);
    }
    else if(general == "guardar")
    {
        if(separadas.size() < 3)
        {
            I::printError("No hay suficientes parametros para guardar");
            return;
        }
        c.guardar(separadas[1], separadas[2]);        
    }
    else if(general == "simular_comandos")
    {
        if(separadas.size() < 3)
        {
            c.simularComandos("0", "0");
            return;
        }
        c.simularComandos(separadas[1], separadas[2]);
    }
    else if(general == "ayuda")
    {
        if(separadas.size() < 2)
        {
            ayuda("general");
            return;
        }
        ayuda(separadas[1]); //la ayuda va en el primer comando
    }

    //PARTE DOS

    else if(general == "ubicar_elementos")
    {
        d.ubicarElementos();
    }
    else if(general == "en_cuadrante")
    {
        if(separadas.size() < 5)
        {
            I::printError("No hay suficientes elementos para hacer este comando");
        }
        d.enCuadrante(separadas[1], separadas[2], separadas[3], separadas[4]);
    }

    //PARTE TRES

    else if(general == "crear_mapa")
    {
        if(separadas.size() < 2)
        {
            I::printError("Falta el coeficiente de conectividad para crear este mapa");
        }
        m.crearMapa(separadas[1]);        
    }
    else if(general == "ruta_mas_larga")
    {
        m.rutaMasLarga();
    }
    //Un pequeño añadido jajaja
    else if(general == "clear")
    {
        system("clear");
    }
    else if(general == "salir"){
        I::printExito("Hasta luego!");
        return;
    }
    //HELP
    else
    {
        I::printError("Comando invalido, prueba 'ayuda' para conocer los comandos");
    }
}

void Consola::funcionDePrueba(std::string input)
{
    I::prinText(input);
    I::prinTitle(input);
    I::prinTitle2(input);
    I::printError(input);
}
