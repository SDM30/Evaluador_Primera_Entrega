#include"parser.hpp"

#include<iostream>
#include<vector>
#include<sstream>
#include<string>
using namespace std;

vector<string> separar(string linea)
{
  vector<string> tokens;
  for(int i = 0; i < linea.size(); i++)
  {
    if(linea[i] == ' ') continue;

    if(linea[i] == '\'')
    {
      i++;
      string token = "";
      
      while(i < linea.size() && linea[i]!='\'')
      {
        token += linea[i];
        i++;
      }
      i++; //para saltar la comilla que cierra el comentario ajajaj este era el error
      tokens.push_back(token);
    }
    else 
    {
      string token = "";

      while(i < linea.size() && linea[i]!=' ')
      {
        token += linea[i];
        i++;
      }
      tokens.push_back(token);
    }
  }
  return tokens;
}
