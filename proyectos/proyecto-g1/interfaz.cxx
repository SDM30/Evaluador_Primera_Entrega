#include "interfaz.h"
#include <iostream>

const std::string Interfaz::colTitle2 = "\033[1;38;2;224;159;62m"; //No me gusta este
const std::string Interfaz::colTitle = "\033[1;38;2;51;92;150m";
const std::string Interfaz::colText = "\033[0;38;2;255;243;177m";
const std::string Interfaz::error = "\033[3;38;2;171;42;43m";
const std::string Interfaz::exito = "\033[3;38;2;46;204;113m";
const std::string Interfaz::reset = "\033[0m"; 

std::string Interfaz::centrarTexto(std::string input)
{
    int padding = (80 - input.length()) / 2;
    if (padding > 0)
        std::cout << std::string(padding, ' ');
    return input;
}

void Interfaz::prinText(std::string input)
{
    std::cout << centrarTexto(colText + input + reset) << "\n";
}

void Interfaz::printError(std::string input)
{
    std::cout << centrarTexto(error + input + reset) << "\n";
}

void Interfaz::printExito(std::string input)
{
    std::cout << centrarTexto(exito + input + reset) << "\n";
}

void Interfaz::prinTitle2(std::string input)
{
    std::cout << centrarTexto(colTitle2 + input + reset) << "\n";
}

void Interfaz::prinTitle(std::string input)
{
    std::cout << centrarTexto(colTitle + input + reset) << "\n";
}