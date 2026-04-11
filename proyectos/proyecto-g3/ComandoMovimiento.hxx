    #ifndef COMANDOMOVIMIENTO_HXX
    #define COMANDOMOVIMIENTO_HXX

    #include "ComandoMovimiento.h"
    #include <stdexcept>

    using namespace std;

    template<class T>
    ComandoMovimiento<T>::ComandoMovimiento(){}

    template<class T>
    ComandoMovimiento<T>::ComandoMovimiento(Tipo_Movimiento tipo_movimiento, T magnitud, UnidadMedida unidad_medida){

        // No permitir distancia negativa
        if (tipo_movimiento == AVANZAR && magnitud < 0)
            throw invalid_argument("Magnitud negativa no permitida para avanzar");

        // Validar unidades para avanzar
        if(tipo_movimiento == AVANZAR && (unidad_medida == GRD || unidad_medida == RAD))
            throw invalid_argument("Unidad invalida para avanzar");

        // Validar unidades para girar
        if(tipo_movimiento == GIRAR && (unidad_medida == CM || unidad_medida == DM || unidad_medida == M || unidad_medida == KM))
            throw invalid_argument("Unidad invalida para girar");

        if(unidad_medida == DESCONOCIDO)
            throw invalid_argument("Debe ingresar una unidad de medida correcta");

        this->tipo_movimiento = tipo_movimiento;
        this->magnitud = magnitud;
        this->unidad_medida = unidad_medida;
    }

    //getters

    template<class T>
    Tipo_Movimiento ComandoMovimiento<T>::getTipoMovimiento() const
    {
        return tipo_movimiento;
    }

    template<class T>
    string ComandoMovimiento<T>::tipoMovimiento_toString(Tipo_Movimiento tm) const
    {
        switch(tm){
        case AVANZAR:
            return "avanzar";
        break;
        case GIRAR:
            return "girar";
        break;
        default:
            return "desconocido";
        }
    }

    template<class T>
    Tipo_Movimiento ComandoMovimiento<T>::obtenerTipoMovimiento(const string& tm)
    {
        if(tm=="avanzar"){
            return AVANZAR;
        } else if(tm=="girar"){
            return GIRAR;
        } else {
            throw invalid_argument("Tipo movimiento invalido");
        }
    }

    template<class T>
    T ComandoMovimiento<T>::getMagnitud() const
    {
        return magnitud;
    }
    
    template<class T>
    UnidadMedida ComandoMovimiento<T>::getUnidadMedida() const
    {
        return unidad_medida;
    }

    #endif