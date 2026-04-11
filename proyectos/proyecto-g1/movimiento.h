#ifndef __MOVIMIENTO__
#define __MOVIMIENTO__
#include <string>
#include <stdexcept> //pa lanzar excepciones


/*
Comandos de movimiento: permiten al robot desplazarse sobre la superficie de Marte. Estos comandos
tienen la siguiente estructura:
tipo_movimiento magnitud unidad_medida
*/
class Movimiento
{
    private:
        //tipo_movimiento puede ser avanzar o girar
        std::string tipoMovimiento;

        //unidad_medida es la unidad con la que se hace la medición del movimiento
        std::string unidad;
        
        //magnitud es el valor o cantidad del movimiento
        double tamano;
        
    public:
        // ------- Constructores -------

        // Constructor por defecto
        Movimiento() : tipoMovimiento(""), tamano(0), unidad("") {};

        // Constructor con parámetros
        Movimiento(std::string tipoMovimiento, double tamano, std::string unidad):
            tipoMovimiento(tipoMovimiento),
            unidad(unidad),
            tamano(tamano)
            {};

        // ------- Getters -------
        std::string getTipo(){return tipoMovimiento;}
        std::string getUnidad(){return unidad;}
        double getTamano(){return tamano;}

        // ------- Metodos -------
        /* esUnidadCorrecta
         * ---
         * Verifica si la unidad está dentro de las permitidas
         */
        static bool esUnidadCorrecta(std::string unidad, std::string tipoMovimiento);

        /* esTipoCorrecto
         * ---
         * Verifica si el movimiento está dentro de los permitidos
         */
        static bool esTipoCorrecto(std::string tipoMovimiento);

};

#endif //__MOVIMIENTO__