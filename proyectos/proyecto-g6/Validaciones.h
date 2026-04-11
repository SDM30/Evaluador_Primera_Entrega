#include <sstream>
#ifndef VALIDACIONES_H
#define VALIDACIONES_H

using namespace std;

void lista_comandos();
void ayudaComando(string par1);
int revPar1(stringstream &token, string orden, string &par1);
int revPar3(stringstream &token, string orden, string &par1, string &par2, string &par3);
int revPar2(stringstream &token, string orden, string &par1, string &par2);
int revPar4(stringstream &token, string orden, string &par1, string &par2, string &par3, string &par4);
int revPar0(stringstream &token, string orden);
int revAgregarMov(string orden, string &par1, string &par2, string &par3, double &numero);
int revPar2Par3(stringstream &token, string orden, string &par1, string &par2, string &par3);
int revAgregarAn(string orden, string &par1, string &par2, string &par3, int verificacion);
int revPar5(stringstream &token, string orden, string &par1, string &par2, string &par3, string &par4, string &par5);
int revAgregarEle(string orden, string &par1, string &par2, string &par3, string &par4, string &par5, double &numero, double &coordX, double &coordY);
int revGuardar(string orden, string &par1, string &par2);
int revSimCom(string orden, string &par1, string &par2, double &coordX, double &coordY);
int revArchivo(string dir);
int revCreMap(string orden, string par1, double &numero);
int revEnCuad(string orden, string par1, string par2, string par3, string par4, double &coordX, double &coordY, double &coordX2, double &coordY2);

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Comandos de revisión y comprobación:
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int revPar3Archivo(stringstream &token, string &par2, string &par3);
int revAgregarMovArchivo(string &par1, string &par2, string &par3, double &numero);
int revPar2Par3Archivo(stringstream &token, string &par2, string &par3);
int revAgregarAnArchivo(string &par1, string &par2, string &par3, int verificacion);
int revPar5Archivo(stringstream &token, string &par1, string &par2, string &par3, string &par4, string &par5);
int revAgregarEleArchivo(string &par1, string &par2, string &par3, string &par4, string &par5, double &numero, double &coordX, double &coordY);

#endif

// eof - Validaciones.h
