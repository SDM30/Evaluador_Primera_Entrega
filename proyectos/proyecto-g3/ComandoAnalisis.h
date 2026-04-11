#ifndef COMANDOANALISIS_H
#define COMANDOANALISIS_H

#include <string>
using namespace std;

enum Tipo_Analisis {
    FOTOGRAFIAR,
    COMPOSICION,
    PERFORAR
};

class ComandoAnalisis{

private:

    Tipo_Analisis tipo_analisis;
    string objeto;
    string comentario;

public:

    ComandoAnalisis();
    ComandoAnalisis(Tipo_Analisis ta, string objeto, string comentario);

    Tipo_Analisis getTipoAnalisis() const;
    string tipoAnalisis_toString(Tipo_Analisis ta) const;
    static Tipo_Analisis obtenerTipoAnalisis(const string& ta);
    string getObjeto() const;
    string getComentario() const;

};

#endif