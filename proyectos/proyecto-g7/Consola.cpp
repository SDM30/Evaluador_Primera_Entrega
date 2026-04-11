#include "Consola.hpp"
#include "parser.hpp"
#include "colores.hpp"
#include "Sistema.hpp"
#include "Movimiento.hpp"
#include "Analisis.hpp"
#include "Elemento.hpp"

#include<iostream>
#include<sstream>
#include<vector>
#include<string>

using namespace std;

void ayuda()
{
  cout<<YELLOW;
  cout<<"  COMANDO DE CURIOSITY  "<<endl;
  cout<<"agregar_movimiento <tipo> <magnitud> <unidad>"<<endl;
  cout<<"agregar_analisis <tipo> <objeto> <comentario>"<<endl;
  cout<<"agregar_elemento <tipo> <tamaño> <unidad_medida> <coord_x> <coord_y>"<<endl;
  cout<<"guardar <Tipo_archivo> <nombre_archivo>"<<endl;
  cout<<"simular_comandos <coord_x> <coord_y>"<<endl;
  cout<<"cargar_comandos <nombre_archivo>"<<endl;
  cout<<"cargar_elementos <nombre_archivo>"<<endl;
  cout<<"ubicar_elementos"<<endl;
  cout<<"en_cuadrante <coord_x1> <coord_x2> <coord_y1> <coord_y2> "<<endl;
  cout<<"crear_mapa <coeficiente_conectividad>"<<endl;
  cout<<"ruta_mas_larga"<<endl;
  cout<<"ayuda <comando>"<<endl;
  cout<<RESET;
  cout<<"salir"<<endl;
}

void ayudaEspecifica(string comando)
{
  cout<<RESET;
  if(comando == "agregar_movimiento") {
    cout<<"Agrega el comando de movimiento descrito a la lista de comandos del robot \"Curiosity\". El movimiento puede ser de dos tipos: avanzar o girar. La magnitud corresponde al valor del movimiento; si es avanzar, el número de unidades que se espera avanzar, si es girar la cantidad de grados que debe girar. La unidad de medida corresponde a la convención con la que se mide la magnitud del movimiento, de acuerdo a la tabla presentada anteriormente. Si no se envía la información completa y adecuada del comando de movimiento, éste no puede agregarse a la lista de los comandos que se enviarán al robot desde la tierra."<<endl;
  }
  else if(comando == "agregar_analisis") {
    cout<<"Agrega el comando de análisis descrito a la lista de comandos del robot \"Curiosity\". El análisis puede ser de tres tipos: fotografiar, composicion o perforar. El objeto es el nombre del elemento que se quiere analizar (roca, arena, monticulo, ...). El comentario es opcional y permite agregar más información sobre el elemento o el análisis, este comentario estará encerrado entre comillas simples (ejemplo: 'roca_cuadrante_32'). Si no se envía la información completa y adecuada del comando de análisis, éste no puede agregarse a la lista de los comandos que se enviarán al robot desde la tierra."<<endl;
  }
  else if(comando == "agregar_elemento") {
    cout<<"Agrega el componente o elemento descrito a la lista de puntos de interés del robot \"Curiosity\". El tipo de componente puede ser uno entre roca, crater, monticulo o duna. El tamaño es un valor real que da cuenta de qué tan grande es el elemento; y la unidad de medida complementa este valor con la convención que se usó para su medición, de acuerdo a la tabla presentada anteriormente. Finalmente, las coordenadas x y y corresponden a números reales que permiten conocer la ubicación del elemento en el sistema de coordenadas del suelo marciano utilizado por el vehículo. Si no se envía la información completa y adecuada del elemento, éste no puede agregarse a la lista de puntos de interés que se enviarán al robot desde la tierra."<<endl;
  }
  else if(comando == "guardar") {
    cout<<"Guarda en el archivo nombre_archivo la información solicitada de acuerdo al tipo de archivo: comandos almacena en el archivo la información de comandos de movimiento y de análisis que debe ejecutar el robot, elementos almacena en el archivo la información de los componentes o puntos de interés conocidos en el suelo marciano."<<endl;
  }
  else if(comando == "simular_comandos") {
    cout<<"Permite simular el resultado de los comandos de movimiento que se enviarán al robot \"Curiosity\" desde la Tierra, facilitando asi la validación de la nueva posición en la que podría ubicarse. Para ejecutarse adecuadamente, requiere conocer la posición actual (coordenadas x y y) del vehículo. A partir de la posición actual, se asume que el \"Curiosity\" está orientado mirando hacia la parte derecha del eje x en un sistema cartesiano (hacia la derecha). Los ángulos de giro positivos generan movimiento en el sentido contrario de las manecillas del reloj, mientras que los ángulos de giro negativos generan movimiento en el sentido de las manecillas del reloj. Hay que tener en cuenta que sólo los comandos de movimiento son necesarios, no los de análisis."<<endl;
  }
  else if(comando == "cargar_comandos") {
    cout<<"Carga en memoria los comandos de desplazamiento contenidos en el archivo identificado por nombre_archivo , es decir, utiliza adecuadamente las estructuras lineales para cargar la información de los comandos en memoria. Si dentro de la misma sesión de trabajo ya se han cargado otros archivos de comandos (usando el comando cargar_comandos), la información debe sobreescribirse en memoria, es decir, no se deben combinar informaciones de comandos de diferentes archivos."<<endl;
  }
  else if(comando == "cargar_elementos") {
    cout<<"Carga en memoria los datos de puntos de interés o elementos contenidos en el archivo identificado por nombre_archivo , es decir, utiliza adecuadamente las estructuras lineales para cargar la información de los elementos en memoria. Si dentro de la misma sesión de trabajo ya se han cargado otros archivos de puntos de interés (usando el comando cargar_elementos), la información debe sobreescribirse en memoria, es decir, no se deben combinar informaciones de elementos de diferentes archivos."<<endl;
  }
  else if(comando == "ubicar_elementos") {
    cout<<"Los elementos han sido procesados exitosamente. descripción: El comando debe utilizar la información de puntos de interés almacenada en memoria para ubicarlos en una estructura de datos jerárquica adecuada, que permita luego realizar consultas geográficas sobre estos elementos. Si alguno de los elementos no puede agregarse adecuadamente, debe generarse un mensaje de error, pero deben procesarse todos los elementos almacenados en memoria"<<endl;
  }
  else if(comando == "en_cuadrante") {
    cout<<"Permite utilizar la estructura creada con el comando anterior para retornar una lista de los componentes o elementos que están dentro del cuadrante geográfico descrito por los límites de coordenadas en x y y. Es necesario haber ejecutado el comando ubicar_elementos para poder realizar la búsqueda por cuadrantes. Los límites de coordenadas deben garantizar que coordX1 <coordX2 y coordY1 <coordY2 ."<<endl;
  }
  else if(comando == "crear_mapa") {
    cout<<"El comando debe utilizar la información de puntos de interés almacenada en memoria para ubicarlos en una estructura no lineal y conectarlos entre sí teniendo en cuenta el coeficiente de conectividad dado. El objetivo es que cada elemento esté conectado a los demás elementos más cercanos a él, midiendo la cercanía a través de la distancia euclidiana entre los elementos. Esta distancia euclidiana también se utiliza como el peso o etiqueta de la conexión entre los elementos. Con el coeficiente de conectividad se identifica la cantidad de vecinos que puede tener cada elemento tomando como base el total de elementos que se ubicarán en el mapa (ejemplo: si se van a ubicar 35 elementos, y el coeficiente de conectividad es 0.4, la cantidad de vecinos que cada elemento debe tener es 35 * 0.4 = 14)."<<endl;
  }
  else if(comando == "ruta_mas_larga") {
    cout<<"Con el mapa ya creado, el comando permite identificar los dos componentes más alejados entre sí de acuerdo a las conexiones generadas. Es importante aclarar que el comando retorna los elementos más alejados de acuerdo a las conexiones que se encuentran en el mapa, no los elementos que estén a mayor distancia euclidiana entre sí. Al encontrar esa ruta más larga dentro del mapa, el comando imprime en pantalla los elementos de origen y destino, la longitud total de la ruta, y la secuencia de elementos que hay que seguir para ir del elemento origen al elemento destino"<<endl;
  }
  else {
    cout<<"Comando: "<<comando<<" ERROR :(. Escribe 'ayuda' para ver lista de comandos"<<endl;
  }
}

void iniciarConsola()
{
  Sistema sistema;
  
  bool salir = false;
  while(!salir){
    cout<<GREEN<<"$ "<<BRIGHT;

    string linea;
    getline(cin, linea);

    vector<string> tokens = separar(linea);//cada vez que se itera para el menú se crea un nuevo vector de tokens, por lo que no es necesario limpiarlo cada vez

    if(tokens.empty()) continue;

    if(tokens[0] == "cargar_comandos") //resulta que no se puede hacer case switch con strings
    {
      if(tokens.size() != 2)
      {
        cout<<RED<<"El comando: 'cargar_comandos' necesita un nombre del archivo"<<endl;
      }
      else
      {
        sistema.cargarComandos(tokens[1]);
      }
    }
    else if(tokens[0] == "cargar_elementos")
    {
      if(tokens.size() != 2){
        cout<<RED<< "El comando: 'cargar_elementos' necesita un nombre del archivo" << endl;
      }else{
        sistema.cargarElementos(tokens[1]);
      }          
    }
    else if(tokens[0] == "agregar_movimiento")
    {

      if (tokens.size() != 4)
      {
        cout<<RED<<"La información del movimiento no corresponde a los datos esperados(tipo, magnitud, unidad)."<<RESET<<endl;
      }
      else
      {
        if(!sistema.agregarMovimiento(tokens[1], tokens[2], tokens[3]))
        {
          cout<<RED<<"La información del movimiento no corresponde a los datos esperados(tipo, magnitud, unidad)."<<RESET<<endl; 
        }
        else
        {
          cout<<GREEN<<"Movimiento agregado correctamente"<<RESET<<endl;
        }
      }
    }
    else if(tokens[0] == "agregar_analisis")
    {
      if(tokens.size() < 3 || tokens.size() > 4){
        cout<<RED << "La información del análisis no corresponde a los datos esperados (tipo, objeto, comentario)." << endl;
      }
      else
      {
        string comentario = "";
        if(tokens.size() == 4) comentario = tokens[3];
        if(!sistema.agregarAnalisis(tokens[1], tokens[2], comentario))
        {
          cout<<RED << "La información del análisis no corresponde a los datos esperados (tipo, objeto, comentario)." << endl;
        }
        else
        {
          cout<<GREEN<<"El comando de análisis ha sido agregado exitosamente."<<RESET<<endl;          
        }
      }          
    }
    else if(tokens[0] == "agregar_elemento")
    {
        if(tokens.size() < 6){
            cout<<RED << "La información del elemento no corresponde a los datos esperados (tipo,tamaño, unidad, x, y)." << endl;
        } 
        else 
        {
          if(!sistema.agregarElemento(tokens[1], tokens[2], tokens[3], tokens[4], tokens[5]))
          {
            cout<<RED << "La información del elemento no corresponde a los datos esperados (tipo,tamaño, unidad, x, y)." << endl;
          }
          else
          {
            cout<<GREEN<<"El elemento ha sido agregado exitosamente."<<RESET<<endl;
          }
        }         
    }
    else if(tokens[0] == "guardar")
    {
      if(tokens.size() != 3){
        cout<<RED << "El comando: guardar necesita un tipo de archivo y un nombre de archivo" << endl;
      } else {
        sistema.guardar(tokens [1], tokens [2]);
      }         
    }
    else if(tokens[0] == "simular_comandos")
    {
      if(tokens.size() != 3){
        cout<<RED << "El comando: simular_comandos necesita la coordenada x y coordenada y" << endl;
      } 
      else 
      {
        sistema.simularComandos(tokens[1], tokens[2]);
      }        
    }
    else if(tokens[0] == "ubicar_elementos")
    {
      cout<<"Ubicando elementos ... por ahora no hace nada" << endl;         
    }
    else if(tokens[0] == "en_cuadrante")
    {
     if(tokens.size() != 5){
        cout<<RED << "El comando: en_cuadrante necesita coord_x1, coord_x2, coord_y1 y coord_y2" << endl;
      } else {
        cout << "Buscando elementos en cuadrante ... por ahora no hace nada" << endl;
      }
    }
    else if(tokens[0] == "crear_mapa")
    {
      if(tokens.size() != 2){
        cout<<RED << "El comando: crear_mapa necesita un coeficiente de conectividad" << endl;
      } else {
        cout << "Creando mapa ... por ahora no hace nada" << endl;
      }
    }
    else if(tokens[0] == "ruta_mas_larga")
    {
      cout<<"Identificando ruta mas larga ... por ahora no hace nada" << endl;        
    }
    else if(tokens[0] == "ayuda")
    {
      if(tokens.size() == 1)
      {
        ayuda();
      }
      else
      {
        ayudaEspecifica(tokens[1]);
      }
    }
    else if(tokens[0] == "salir")
    {
      sistema.salir();
    }
    else
    {
      cout<<RED<<"Comando: "<<tokens[0]<<" no reconocido. Escriba ayuda para ver lista de comandos"<<endl;
    }
  }
}

