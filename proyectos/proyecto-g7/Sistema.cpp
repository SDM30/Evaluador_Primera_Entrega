#include<vector>
#include<iostream>
#include<fstream>
#include<string>

#include"Sistema.hpp"
#include"parser.hpp"
#include"colores.hpp"

using namespace std;

//constructor
Sistema::Sistema()
{
  archivoAbierto = false; 
  guardado = true; 
}

bool Sistema::agregarMovimiento(string tipoStr, string magStr, string unidadStr) 
{
    TipoMovimiento tipo = ComandoMovimiento::stringATipo(tipoStr);
    if (tipo == TipoMovimiento::INVALIDO) return false;

    double magnitud;

    try {
        magnitud = stod(magStr);
    } catch (const exception& e) {
        return false;
    }

    UnidadMovimiento unidad = ComandoMovimiento::stringAUnidad(unidadStr);
    if (unidad==UnidadMovimiento::INVALIDA) return false;

    if (!ComandoMovimiento::esUnidadValida(tipo, unidad)) return false;

    this->movimientos.push_back(ComandoMovimiento(tipo, magnitud, unidad));

    Comando c;
    c.tipo = TipoComando::MOVIMIENTO;
    c.movimiento = ComandoMovimiento(tipo, magnitud, unidad);
    this->comandos.push_back(c);

    return true;
}

bool Sistema::agregarAnalisis(string tipoStr, string objeto, string comentario) 
{
    TipoAnalisis tipo = ComandoAnalisis::stringATipo(tipoStr);
    if (tipo == TipoAnalisis::INVALIDO) return false;
    if (objeto.empty()) return false;

    this->analisis.push_back(ComandoAnalisis(tipo, objeto, comentario));

    Comando c;
    c.tipo = TipoComando::ANALISIS;
    c.analisis = ComandoAnalisis(tipo, objeto, comentario);
    this->comandos.push_back(c);

    return true;
}

bool Sistema::agregarElemento(string tipoStr, string tamStr, string unidadStr, string xStr, string yStr) 
{
    TipoElemento tipo = Elemento::stringATipo(tipoStr);
    if (tipo == TipoElemento::INVALIDO) return false;

    UnidadElemento unidad = Elemento::stringAUnidad(unidadStr);
    if (unidad == UnidadElemento::INVALIDA) return false;

    double tam, x, y;
    try {
        tam = stod(tamStr);
        x   = stod(xStr);
        y   = stod(yStr);
    } catch (const exception& e) {
        return false;
    }

    Punto puntotemp = crearPunto(x, y);

    this->elementos.push_back(Elemento(tipo, tam, unidad, puntotemp));
    return true;
}

void Sistema::cargarComandos(string nombreArchivo) 
{
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout<<RED<<nombreArchivo<<" no se encuentra o no puede leerse."<<RESET<<endl;
        return;
    }

    this->movimientos.clear();
    this->analisis.clear();
    this->comandos.clear();

    int total = 0;
    string linea;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        if(linea.back()=='\r') linea.pop_back();

        vector<string> tokens = separar(linea);

        if (tokens.empty()) continue;

        if (tokens.size() >= 3 && agregarMovimiento(tokens[0], tokens[1], tokens[2])) total++;
        else
        {
            if(tokens.size()==2)
            {
            if (agregarAnalisis(tokens[0], tokens[1], "")) total++;
            }
            if(tokens.size()==3 && linea.find('\'')!=string::npos)
            {
              if(agregarAnalisis(tokens[0], tokens[1], tokens[2])) total++;
            }
        }
    }
    archivo.close();

    if (total == 0)
    {
      cout<<YELLOW<<nombreArchivo<<" no contiene comandos."<<RESET<<endl;
    }
    else
    {
      cout<<GREEN<<total<<" comandos cargados correctamente desde "<<nombreArchivo<<"."<<RESET<<endl;
    }
}

void Sistema::cargarElementos(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout<<RED<<nombreArchivo<<" no se encuentra o no puede leerse."<<RESET<<endl;
        return;
    }

    this->elementos.clear();

    int total = 0;
    string linea;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        vector<string> tokens = separar(linea);
        if (tokens.size() < 5) continue;

        if (agregarElemento(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4])) total++;
    }
    
    archivo.close();

    if (total == 0)
    {
      cout<<YELLOW<<nombreArchivo<<" no contiene elementos."<<RESET<<endl;
    }
    else
    {
      cout<<GREEN<<total<<" elementos cargados correctamente desde "<<nombreArchivo<<"."<<RESET<<endl;
    }
}

void Sistema::simularComandos(string xStr, string yStr)
{
  double x, y;
  try{
    x = stod(xStr);
    y = stod(yStr);
  }catch (const exception& e){
    cout<<RED<<"Error: argumento invalido"<<RESET<<endl;
    return;
  }

  if(this->movimientos.empty()) 
  {
    cout<<RED<<"La información requerida no está almacenada en memoria."<<RESET<<endl;
    return;
  }


  vector<ComandoMovimiento>::iterator it = this->movimientos.begin();

  double angulo = 0.0; //0 porque empieza mirando hacia la derecha

  for(; it!=this->movimientos.end(); it++)
  {
    if(it->getTipo() == TipoMovimiento::AVANZAR)
    {
      double distancia = it->getMagnitudEnMetros();
      x += distancia * cos(angulo);
      y += distancia * sin(angulo);
    }
    if(it->getTipo() == TipoMovimiento::GIRAR)
    {
      angulo += it->getMagnitudEnRadianes();
    }
  }

  cout<<GREEN<<"La simulación de los comandos, a partir de la posición ("<<xStr<<", "<<yStr<<") deja al robot en la nueva posición ("<<x<<", "<<y<<")."<<RESET<<endl;

}

void Sistema::guardar(string tipo, string nombre_archivo){ 
  if(tipo != "comandos" && tipo != "elementos")
  {
    cout<<RED<<"El tipo debe ser de analisis o movimiento"<<RESET<<endl; 
    return; 
  } 
  if(tipo == "comandos" && this->comandos.empty())
  {
        cout<<YELLOW<<"La informacion requerida no esta almacenada en memoria"<<RESET<<endl; 
        return;
  }
  if (tipo == "elementos" && this->elementos.empty())
  {
    cout<<YELLOW<<"La informacion requerida no esta almacenada en memoria "<<RESET<<endl; 
    return; 
  }
  // abrir el archivo y escribo
  ofstream archivo(nombre_archivo); 
  if(!archivo.is_open())
  {
    cout<<RED<<"Error guardando en "<<nombre_archivo<<RESET<<endl; 
    return; 
  }
  
  if(tipo=="comandos")
  {
    vector<Comando>::iterator itC = this->comandos.begin();
    for(; itC != this->comandos.end(); itC++)
    {
      if(itC->tipo == TipoComando::MOVIMIENTO)
      {
        archivo<<itC->movimiento.getTipoString()<<" "
              <<itC->movimiento.getMagnitud()<<" "
              <<itC->movimiento.getUnidadString()
              <<endl;
      }
      if(itC->tipo == TipoComando::ANALISIS)
      {
        archivo<<itC->analisis.getTipoString()<<" "
              <<itC->analisis.getObjeto()<<" ";
        if(!itC->analisis.getComentario().empty()) archivo<<itC->analisis.getComentario();
        archivo<<endl;
              
      }
    }
  }

  if(tipo=="elementos")
  {
    vector<Elemento>::iterator itE = this->elementos.begin();
    for(; itE != this->elementos.end(); itE++)
    {
      archivo<<itE->getTipoString()<<" "
             <<itE->getTamano()<<" "
             <<itE->getUnidadString()<<" "
             <<itE->getPuntoString()<<" "
             <<endl;
    }
  }
  
  archivo.close();
  guardado = true; 
  cout<<GREEN<<"La informacion a sido guardada en "<<nombre_archivo<<RESET<<endl; 
}

void Sistema::salir()
{   
// guardo archivos abrietos
  if(archivoAbierto && !guardado)
  {
    guardar("comandos", "archivo_sinnombre.txt"); 
    guardar("elementos", "archivo_sinnombre.txt");
  }
  movimientos.clear(); 
  analisis.clear();
  // voy a usar el de limpiar para linux
system("clear");
exit(0); 
}
  
  
