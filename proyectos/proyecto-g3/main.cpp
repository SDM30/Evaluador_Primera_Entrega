#include "Curiosity.h"
#include <sstream>
#include <locale.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "");

    Curiosity robot;

    string linea;
    bool activo = true;

    cout << "Sistema Curiosity - Entrega 0. Escriba 'ayuda' para iniciar." << endl;

    while (activo) {
        cout << "$ ";
        if (!getline(cin, linea)) break;
        if (linea.empty()) continue;

        stringstream ss(linea);
        string palabra;
        vector<string> args;

        while (ss >> palabra)
            args.push_back(palabra);

        if (args.empty()) continue;

        string cmd = args[0];

        if (cmd == "salir") activo = false;
        else if (cmd == "cargar_comandos") robot.cargar_comandos(args);
        else if (cmd == "cargar_elementos") robot.cargar_elementos(args);
        else if (cmd == "agregar_movimiento") robot.agregar_movimiento(args);
        else if (cmd == "agregar_analisis") robot.agregar_analisis(args);
        else if (cmd == "agregar_elemento") robot.agregar_elemento(args);
        else if (cmd == "guardar") robot.guardar(args);
        else if (cmd == "simular_comandos") robot.simular_comandos(args);
        else if (cmd == "ubicar_elementos") robot.ubicar_elementos(args);
        else if (cmd == "en_cuadrante") robot.en_cuadrante(args);
        else if (cmd == "crear_mapa") robot.crear_mapa(args);
        else if (cmd == "ruta_mas_larga") robot.ruta_mas_larga(args);
        else if (cmd == "ayuda") robot.ayuda(args);
        else cout << "Comando desconocido." << endl;
    }

    return 0;
}