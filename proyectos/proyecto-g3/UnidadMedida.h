#ifndef UNIDADMEDIDA_H
#define UNIDADMEDIDA_H

enum UnidadMedida {
    CM, DM, M, KM,   // para avanzar
    GRD, RAD         // para girar
    ,DESCONOCIDO
};

bool esUnidadLongitud(UnidadMedida u);
bool esUnidadAngulo(UnidadMedida u);

#endif