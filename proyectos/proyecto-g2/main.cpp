#include "curiosity.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{

    Curiosity robot;
    string linea;

    while (true)
    {

        cout << "$ ";

        getline(cin, linea);

        if (linea.empty())
            continue;

        stringstream ss(linea);
        string comando;

        ss >> comando;

        if (comando == "salir")
        {
            break;
        }

        else if (comando == "ayuda")
        {
            robot.ayuda();
        }

        else if (comando == "cargar_comandos")
        {
            string archivo;

            if (ss >> archivo)
            {
                robot.cargarComandos(archivo);
            }
            else
            {
                cout << "(Error) Falta informacion. Uso: cargar_comandos <archivo>" << endl;
            }
        }

        else if (comando == "cargar_elementos")
        {
            string archivo;
            if (ss >> archivo)
            {
                robot.cargarElementos(archivo);
            }
            else
            {
                cout << "(Error) Falta informacion. Uso: cargar_elementos <archivo>" << endl;
            }
        }

        else if (comando == "agregar_movimiento")
        {
            string tipo, unidad;
            double magnitud;

            if (ss >> tipo >> magnitud >> unidad)
            {
                robot.agregarMovimiento(tipo, magnitud, unidad);
            }
            else
            {
                cout << "(Error) Falta informacion o formato incorrecto. Uso: agregar_movimiento <tipo> <magnitud> <unidad>" << endl;
            }
        }

        else if (comando == "agregar_analisis")
        {
            string tipo, objeto, comentario;

            if (ss >> tipo >> objeto)
            {
                getline(ss, comentario);

                if (!comentario.empty() && comentario[0] == ' ')
                {
                    comentario = comentario.substr(1);
                }

                robot.agregarAnalisis(tipo, objeto, comentario);
            }
            else
            {
                cout << "(Error) Falta informacion. Uso: agregar_analisis <tipo> <objeto> <comentario>" << endl;
            }
        }

        else if (comando == "agregar_elemento")
        {
            string tipo, unidad;
            double tam, x, y;

            if (ss >> tipo >> tam >> unidad >> x >> y)
            {
                robot.agregarElemento(tipo, tam, unidad, x, y);
            }
            else
            {
                cout << "(Error) Falta informacion o formato incorrecto. Uso: agregar_elemento <tipo> <tamaño> <unidad> <x> <y>" << endl;
            }
        }

        else if (comando == "guardar")
        {
            string tipo, archivo;

            if (ss >> tipo >> archivo)
            {
                robot.guardar(tipo, archivo);
            }
            else
            {
                cout << "(Error) Falta informacion. Uso: guardar <tipo> <archivo>" << endl;
            }
        }

        else if (comando == "simular_comandos")
        {
            double x, y;

            if (ss >> x >> y)
            {
                robot.simularComandos(x, y);
            }
            else
            {
                cout << "(Error) Falta informacion o se ingresaron letras. Uso: simular_comandos <x> <y>" << endl;
            }
        }

        else
        {
            cout << "Comando no reconocido" << endl;
        }
    }

    return 0;
}