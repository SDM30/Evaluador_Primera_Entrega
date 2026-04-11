#ifndef __GESTOR_DE_ARCHIVO__
#define __GESTOR_DE_ARCHIVO__
#include <fstream>
#include <vector>
#include <sstream>
#include "elemento.h"
#include "comando.h"
#include "analisis.h"

class GestorArchivo
{
    private:

        //Son los analisis que contiene un archivo
        std::vector<Comando> comandos;

        //Son los elementos que contiene un archivo distinto al anterior
        std::vector<Elemento> elementos;
        
    public:

        /*
        FUNCIÓN AUXILIAR PARA cargarComandos()
        ------------------------------------------
        Recibe una lista de parámetros, decide si es un análisis o un movimiento
        y lo guarda dentro de un Comando.
        */
        bool agregarComando(std::vector<std::string>);
        /* Cargar Comandos
         * ---
         * Carga en memoria los comandos de desplazamiento contenidos en el archivo identificado
         * por nombre_archivo , es decir, utiliza adecuadamente las estructuras lineales para cargar la información
         * de los comandos en memoria. Si dentro de la misma sesión de trabajo ya se han cargado otros archivos
         * de comandos (usando el comando cargar_comandos), la información debe sobreescribirse en memoria,
         * es decir, no se deben combinar informaciones de comandos de diferentes archivos.
         */
        void cargarComandos(std::string);

        /*
         * Carga en memoria los datos de puntos de interés o elementos contenidos en el archivo
         * identificado por nombre_archivo , es decir, utiliza adecuadamente las estructuras lineales para cargar
         * la información de los elementos en memoria. Si dentro de la misma sesión de trabajo ya se han cargado
         * otros archivos de puntos de interés (usando el comando cargar_elementos), la información debe
         * sobreescribirse en memoria, es decir, no se deben combinar informaciones de elementos de diferentes
         * archivos.
         */
        void cargarElementos(std::string);

        /*
        Agrega el componente o elemento descrito a la lista de puntos de interés del robot “Curiosity”. El tipo de componente puede ser uno entre roca, crater, monticulo o duna. El tamaño es
        un valor real que da cuenta de qué tan grande es el elemento; y la unidad de medida complementa este
        valor con la convención que se usó para su medición, de acuerdo a la tabla presentada anteriormente.
        Finalmente, las coordenadas x y y corresponden a números reales que permiten conocer la ubicación del
        elemento en el sistema de coordenadas del suelo marciano utilizado por el vehículo. Si no se envía la
        información completa y adecuada del elemento, éste no puede agregarse a la lista de puntos de interés
        que se enviarán al robot desde la tierra.
        */
        void agregarElemento(std::string tipo, std::string tam, std::string unidad, std::string x, std::string y);
        
        /*
        Agrega el comando de análisis descrito a la lista de comandos del robot “Curiosity”. El
        análisis puede ser de tres tipos: fotografiar, composicion o perforar. El objeto es el nombre del
        elemento que se quiere analizar (roca, arena, monticulo, ...). El comentario es opcional y permite agregar
        más información sobre el elemento o el análisis, este comentario estará encerrado entre comillas simples
        (ejemplo: ’roca_cuadrante_32’). Si no se envía la información completa y adecuada del comando de
        análisis, éste no puede agregarse a la lista de los comandos que se enviarán al robot desde la tierra.
        */
        void agregarAnalisis(std::string analisis, std::string objeto, std::string comentario);
        
        /*
        Agrega el comando de movimiento descrito a la lista de comandos del robot “Curiosity”. El movimiento puede ser de dos tipos: avanzar o girar. La magnitud corresponde al valor del
        movimiento; si es avanzar, el número de unidades que se espera avanzar, si es girar la cantidad de grados
        que debe girar. La unidad de medida corresponde a la convención con la que se mide la magnitud del
        movimiento, de acuerdo a la tabla presentada anteriormente. Si no se envía la información completa
        y adecuada del comando de movimiento, éste no puede agregarse a la lista de los comandos que se
        enviarán al robot desde la tierra.
        */
        void agregarMovimiento(std::string movimiento, std::string magnitud, std::string unidad);
        
        /*
        Guarda en el archivo nombre_archivo la información solicitada de acuerdo al tipo de
        archivo: comandos almacena en el archivo la información de comandos de movimiento y de análisis que
        debe ejecutar el robot, elementos almacena en el archivo la información de los componentes o puntos
        de interés conocidos en el suelo marciano.
        */
        void guardar(std::string extension, std::string nombre);
        
        double cambiarUnidad(double &magnitud, std::string unidad);

        void ejecutarAvance(double &x, double &y, double &angulo, double &distancia);

        void rotar(double &theeta, double &angulo, std::string unidad);

        /*
        Permite simular el resultado de los comandos de movimiento que se enviarán al robot
        “Curiosity” desde la Tierra, facilitando asi la validación de la nueva posición en la que podría ubicarse.
        Para ejecutarse adecuadamente, requiere conocer la posición actual (coordenadas x y y) del vehículo.
        A partir de la posición actual, se asume que el “Curiosity” está orientado mirando hacia la parte derecha
        del eje x en un sistema cartesiano (hacia la derecha). Los ángulos de giro positivos generan movimiento
        en el sentido contrario de las manecillas del reloj, mientras que los ángulos de giro negativos generan
        movimiento en el sentido de las manecillas del reloj. Hay que tener en cuenta que sólo los comandos de
        movimiento son necesarios, no los de análisis.
        */
        void simularComandos(std::string x, std::string y);

        /*
        Valida si el comando enviado es correcto, retornando 1 si es tipo analisis, 2 si es tipo movimiento y 0 si no es ninguno de los dos
        */
        int validarComando(std::string comando);

};

#endif //__GESTOR_DE_ARCHIVO__