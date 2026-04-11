#include <iostream>
#include <string>
#include "comandos.h"

using namespace std;


int leer_comando(string palabras[], int max_palabras) {
    string linea;
    getline(cin, linea);
    
    int num_palabras = 0;
    string palabra_actual = "";
    bool dentro_comillas = false;
    
    for (int i = 0; i < (int)linea.length() && num_palabras < max_palabras; i++) {
        char c = linea[i];
        
        
        if (c == '\'') {
            dentro_comillas = !dentro_comillas;
            palabra_actual += c;
        }
        
        else if (dentro_comillas) {
            palabra_actual += c;
        }
        
        else if (c == ' ' || c == '\t') {
            if (palabra_actual.length() > 0) {
                palabras[num_palabras] = palabra_actual;
                num_palabras++;
                palabra_actual = "";
            }
        }
       
        else {
            palabra_actual += c;
        }
    }
    
   
    if (palabra_actual.length() > 0 && num_palabras < max_palabras) {
        palabras[num_palabras] = palabra_actual;
        num_palabras++;
    }
    
    return num_palabras;
}

int main() {
   
    programa p;
    p.hay_comandos = false;
    p.hay_elementos = false;
    p.elementos_ubicados = false;
    p.mapa_creado = false;
    inicializar_lista_comandos(p.lista_comandos);
    inicializar_lista_elementos(p.lista_elementos);    
    
    const int MAX_PALABRAS = 32;
    string palabras[MAX_PALABRAS];
    bool salir = false;
    
    
    cout << "Sistema de simulación del vehículo Curiosity\n";
    cout << "Pontificia Universidad Javeriana\n";
    cout << "Estructuras de Datos 2026-10\n";
    cout << "Escriba 'ayuda' para ver los comandos disponibles.\n\n";
    
   
    while (!salir) {
        cout << "$ ";
        
        int cantidad = leer_comando(palabras, MAX_PALABRAS);
        
       
        if (cantidad == 0) {
            continue;
        }
        
        
        salir = ayuda_comandos(palabras, cantidad, p);
    }

    liberar_lista_comandos(p.lista_comandos);
    liberar_lista_elementos(p.lista_elementos);
    
    cout << "\nSaliendo del sistema...\n";
    
    return 0;
}
