#ifndef __INTERFAZ__
#define __INTERFAZ__
#include <string>

class Interfaz
{
    private:

        //PALETA DE COLORES DEL PROYECTO EN GENERAL
        
        static const std::string colTitle2; 
        static const std::string colTitle;
        static const std::string colText;
        static const std::string error;
        static const std::string exito;
        static const std::string reset;  
        
        static std::string centrarTexto(std::string);

    public:
        


        //Imprime con formato titulo
        static void prinTitle(std::string);

        //Imprime con formato titulo
        static void prinTitle2(std::string);

        //Imprime con formato texto
        static void prinText(std::string);

        //Imprime con formato de error
        static void printError(std::string);

        //Imprime con formato de exito
        static void printExito(std::string);
};

#endif //__INTERFAZ__