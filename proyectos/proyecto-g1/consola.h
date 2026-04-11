#ifndef __CONSOLA__
#define __CONSOLA__
#include <string>
#include <vector>

#include "mapa.h"
#include "distancias.h"
#include "comunicaciones.h"

class Consola
{
    private:
        std::string input;
        void ayuda(std::string especifico); //recibe el comando de ayuda default
        Comunicaciones c;
        Distancias d;
        Mapa m;

    public:
        //Recibe con un getline lo que haya en la consola
        std::string ingresoConsola(bool &);

        //Recibe el string de la consola y lo separa en un vector
        std::vector <std::string> separarString(std::string);

        //Comprueba que el comando exista y llama funciones
        void llamarFunciones(std::vector <std::string>);

        void funcionDePrueba(std::string);
};

#endif //__CONSOLA__