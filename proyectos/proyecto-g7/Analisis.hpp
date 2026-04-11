#ifndef ANALISIS_HPP
#define ANALISIS_HPP

#include<string>

using namespace std;

enum class TipoAnalisis {
    FOTOGRAFIAR,
    COMPOSICION,
    PERFORAR,
    INVALIDO
};

class ComandoAnalisis {
private:
    TipoAnalisis tipo;
    string       objeto;
    string       comentario; // vacio si no se proporciono

public:
    ComandoAnalisis();
    ComandoAnalisis(TipoAnalisis tipo, string objeto, string comentario);

    TipoAnalisis getTipo() const;

    string getTipoString();

    string getObjeto() const;

    string getComentario() const;

    static TipoAnalisis stringATipo(string t);
};

#endif

