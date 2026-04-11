#ifndef COMANDOANALISIS_H
#define COMANDOANALISIS_H
#include <string>
using namespace std;

// me baso en el TAD ComandoAnalisis. Representa un comando que le dice al robot que analisis hacer si fotografiar, analizar composicion o perforar un elemento
class ComandoAnalisis
{
private:
    string tipoAnalisis; // "fotografiar", "composicion" o "perforar"
    string objeto;       // elemento que se va a analizar (ej: "roca", "arena")
    string comentario;   // informacion adicional opcional, entre comillas simples
public:
    // Constructor por defecto: crea un comando vacio
    ComandoAnalisis();
    // Constructor con parametros
    ComandoAnalisis(string tipo, string objeto, string comentario);
    // Getters
    string getTipoAnalisis();
    string getObjeto();
    string getComentario();
};
#endif
