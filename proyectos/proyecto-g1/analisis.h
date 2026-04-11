#ifndef __ANALISIS__
#define __ANALISIS__
#include <string>
#include <stdexcept>


/*
Comandos de análisis: permiten al robot investigar la superficie de Marte para analizar los elementos
que va encontrando en su desplazamiento. Estos comandos tienen la siguiente estructura:
tipo_analisis objeto comentario
*/
class Analisis
{
    private:
        
        //tipo_analisis puede ser fotografiar, composicion o perforar
        std::string tipoAnalisis;

        //objeto es el nombre del elemento sobre el cual se hace el análisis
        std::string objeto;

        //comentario es un valor opcional que permite agregar información sobre el análisis a 
        //realizar o el elemento que se analizará
        std::string comentario;
    
    public:

        // ------- Constructor -------
        Analisis(std::string tipo, std::string objeto, std::string comentario): 
            tipoAnalisis(tipo), 
            objeto(objeto), 
            comentario(comentario){};

        //Constructor sin comentario
        Analisis(std::string tipo, std::string objeto): 
            tipoAnalisis(tipo), 
            objeto(objeto), 
            comentario(""){};

        // Constructor por defecto
        Analisis(): tipoAnalisis(""), objeto(""), comentario("") {};

        // ------- Getters -------
        std::string getTipo(){return tipoAnalisis;}
        std::string getObjeto(){return objeto;}
        std::string getComentario(){return comentario;}

        // ------- Metodos -------
        /* esAnalisisCorrecto
         * ---
         * Verifica si el analisis está dentro de los tipos de analisis permitidos
         * Lo hacemos static para poderlo usar sin instanciar un objeto
         */
        static bool esAnalisisCorrecto(std::string tipo);

};

#endif //__ANALISIS__