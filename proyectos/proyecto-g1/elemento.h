#ifndef __ELEMENTO__
#define __ELEMENTO__
#include <string>
#include <stdexcept>


/*
Para identificar la complejidad del terreno sobre el cual debe moverse el vehículo, se almacena de forma
adicional la información de elementos o componentes previamente hallados en el terreno. Esta información
tiene la siguente estructura por cada elemento o componente:
*/
class Elemento
{
    private:

        //tipo_elemento puede ser roca, crater, monticulo o duna
        std::string tipoElemento;

        //las unidades de medida aceptadas son las mismas que las del comando avanzar
        std::string unidad;

        //coordenada_x es la posición sobre el eje x en el plano cartesiano del elemento
        double x;

        //coordenada_y es la posición sobre el eje y en el plano cartesiano del elemento
        double y;
        
        /*
         * tamaño es el valor de la dimensión del elemento, unidad_medida 
         * es la unidad con la que se realizó la medición del tamaño del elemento 
         */
        double tamano; 

    public:

        // ------- Constructor
        Elemento(std::string t, std::string unidad, double x, double y, double tam):
            tipoElemento(t),
            unidad(unidad),  
            x(x), 
            y(y),
            tamano(tam)
            {
                if(!esTipoCorrecto(t))
                {
                    throw std::invalid_argument("Tipo incorrecto");
                }

                if(!esUnidadCorrecta(unidad))
                {
                    throw std::invalid_argument("Unidad incorrecta");
                }
            };

        // ------- Getters -------
        std::string getTipo(){return tipoElemento;}
        std::string getUnidad(){return unidad;}
        double getX(){return x;}
        double getY(){return y;};
        double getTamano(){return tamano;}

        //------- Metodos -------
        static bool esTipoCorrecto(std::string t);
        static bool esUnidadCorrecta(std::string unidad);
};

#endif //__ELEMENTO__