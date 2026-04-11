#include "gestorDeArchivo.h"
#include "interfaz.h"
#include <sstream>
#include <cmath>

double pi = acos(-1); //Es la forma estándar de sacar PI. 
//Lo pongo como variable global para no recalcularlo tanto

bool GestorArchivo::agregarComando(std::vector<std::string> input)
{
    if(input.size() < 2) //Un comando no puede tener menos de 2 parametros 
    {
        Interfaz::printError("Cantidad de parametros inadecuada");
        return false;  
    } 

    int tipo = validarComando(input[0]);

    if(tipo == 0)
    {
        Interfaz::printError("Comando no reconocido");
        return false;
    }
    
    if(tipo == 1) //Esto indica que es un análisis
    {
        if(input.size() == 2)
        {   
            Analisis analisis(input[0], input[1]);
            Comando c(analisis);
            this->comandos.push_back(c); 
            Interfaz::printExito(input[0] + " " + input[1] + " SIN COMENTARIO");
            return true;
        }
        else //Si hay mas de 2 parametros, el resto se considera un comentario
        {
            std::string comentario;

            if(input[2][0] != '\'' || input[input.size()-1].back() != '\'') // Para que el comentario tenga comillas simples al inicio y al final
            {
                Interfaz::printError("El comentario debe estar entre comillas simples");
                return false;
            }

            // Esta parte es la encargada de unir el comentario
            
            for(unsigned int i = 2; i < input.size(); i++)
            {
               comentario += input[i] + (i < input.size() - 1 ? " " : "");  
            }

            // Bro esta verificación me costó mucho (gracias claude)
            // Lo que hace es sacar las comillas simples al inicio y al final del comentario para verificar que el interior no esté vacío o compuesto solo por espacios
            std::string interior = comentario.substr(1, comentario.length() - 2);

            // interior.find_first_not_of(' ') == std::string::npos verifica que el interior no esté compuesto 
            // solo por espacios, ya que find_first_not_of devuelve npos si no encuentra ningún caracter que no sea un espacio
            if(interior.empty() || interior.find_first_not_of(' ') == std::string::npos)
            {
                Interfaz::printError("El comentario no puede estar vacio");
                return false;
            }


            Analisis analisis(input[0], input[1], comentario);
            Comando c(analisis);
            this->comandos.push_back(c);
            Interfaz::printExito
            (input[0] + " " + input[1] + " -" + comentario);
            return true;
        }
    }
    else if(tipo == 2) //Esto indica que es un movimiento
    {
        //Como no hay comentarios, procedemos normalito
        if(input.size() != 3)
        {
            Interfaz::printError("Cantidad de parametros inadecuada para un movimiento");
            return false;
        }

        double tam;
        
        try
        {
            tam = std::stod(input[1]);
        }
        catch(const std::invalid_argument &e)
        {
            Interfaz::printError("Magnitud del movimiento debe ser un numero");
            return false;
        }
        Movimiento tmp;
        //imput[2] hace referencia a la unidad
        //input[0] al tipo de movimiento
        if(!tmp.esUnidadCorrecta(input[2], input[0]))
        {
            Interfaz::printError("La unidad ingresada es incorrecta");
            return false;
        }
        
        Movimiento movimiento(input[0], tam, input[2]);
        Comando c(movimiento);
        this->comandos.push_back(c);
        Interfaz::printExito(input[0] + " " + input[1] + " " + input[2]);
        return true;
    }
    return false;
}

void GestorArchivo::cargarComandos(std::string archivo)
{
    // ---- Fase de lectura del archivo ----
    std::ifstream input(archivo, std::ios::in);
    if(!input.is_open())
    {
        Interfaz::printError(archivo + " no se encuentra o no puede leerse");
        return;
    }
    char c;
    bool soloEspacios = true;
    while (input.get(c))
    {
        if (!std::isspace(static_cast<unsigned char>(c)))
        {
            soloEspacios = false;
            break;
        }
    }
    if (soloEspacios)
    {
        Interfaz::printError(archivo + " no contiene comandos");
        return;
    }
    input.clear();
    input.seekg(0);

    // ---- Fase de purga de comandos anteriores ----
    comandos.clear();
    int contadorComandos = 0;

    // ---- Fase de procesamiento de cada linea del archivo ----
    std::string linea;
    while(std::getline(input, linea))
    {
        std::istringstream ss(linea); //Creamos un stringstream para separar la linea en palabras
        std::vector<std::string> parametros; //Vector donde guardaremos los parametros de cada comando
        std::string parametro; //Variable auxiliar para guardar cada parametro mientras separamos la linea

        // Si hay una linea vacia, se ignora
        if(linea.empty()) continue;

        // Separamos la linea en palabras y las guardamos en un vector de strings
        // Para los analisis con comentario, el comentario se guarda como si tuviera varios parametros
        // El metodo agregarComando se encargará de unirlos y formar el comentario completo
        while(ss >> parametro) //Mientras haya palabras para leer, las guardamos en el vector de parametros
        {
           parametros.push_back(parametro); 
        }
        
        if(agregarComando(parametros)) //Si el comando se agregó correctamente, aumentamos el contador de comandos cargados
        {
            contadorComandos++;
        }
    }

    Interfaz::printExito(std::to_string(contadorComandos) + " comandos cargados exitosamente desde " + archivo);
    input.close();
}

void GestorArchivo::cargarElementos(std::string archivo)
{
    std::ifstream input(archivo, std::ios::in);

    if(!input.is_open())
    {
        Interfaz::printError(archivo + " no se encuentra o no puede leerse");
        return;
    }
    
    char c;
    bool soloEspacios = true;

    while (input.get(c))
    {
        if (!std::isspace(static_cast<unsigned char>(c)))
        {
            soloEspacios = false;
            break;
        }
    }

    if (soloEspacios)
    {
        Interfaz::printError(archivo + " no contiene comandos");
        return;
    }

    input.clear();
    input.seekg(0);


    std::string linea;
    while(std::getline(input, linea))
    {
        std::istringstream ss(linea);
        std::string tipo, unidad, x, y, tam;

        if(ss >> tipo >> tam >> unidad >> x >> y)
        {
            double tamano, X, Y;
            try
            {
                tamano = std::stod(tam);
                X = std::stod(x);
                Y = std::stod(y);
                Elemento e(tipo, unidad, X, Y, tamano);
                elementos.push_back(e);
                Interfaz::printExito(tipo + " " + tam + " " + " " + unidad + " " + x + " " + y); 
            }
            catch(const std::invalid_argument &e)
            {
                Interfaz::printError("Error en linea " + std::string(e.what()));
            }
        }
        else Interfaz::printError("Argumentos insuficientes. . .");
    }
}

void GestorArchivo::agregarElemento(std::string tipo, std::string tam, std::string unidad,
                                    std::string x, std::string y)
{
    if(!Elemento::esTipoCorrecto(tipo))
    {
        Interfaz::printError("La informacion del elemento no corresponde a los datos esperados (tipo).");
        return;
    }

    double tamano;

    try
    {
        tamano = std::stod(tam);
    }
    catch(const std::invalid_argument&) //Si el tamaño no es un numero, se lanza una excepcion que se captura aquí
    {
        Interfaz::printError("La informacion del elemento no corresponde a los datos esperados (tamaño).");
        return;
    }
    catch(const std::out_of_range&) //Si el tamaño es un numero pero es demasiado grande o pequeño para ser representado como double, se lanza una excepcion que se captura aquí
    {
        Interfaz::printError("La informacion del elemento no corresponde a los datos esperados (tamaño).");
        return;
    }

    if(!Elemento::esUnidadCorrecta(unidad))
    {
        Interfaz::printError("La informacion del elemento no corresponde a los datos esperados (unidad).");
        return;
    }

    double X, Y;

    try
    {
        X = std::stod(x);
    }
    catch(const std::invalid_argument&) //Si la coordenada x no es un numero, se lanza una excepcion que se captura aquí
    {
        Interfaz::printError("La informacion del elemento no corresponde a los datos esperados (coordenada x).");
        return;
    }
    catch(const std::out_of_range&) //Si la magnitud es un numero pero es demasiado grande o pequeño para ser representado como double, se lanza una excepcion que se captura aquí
    {
        Interfaz::printError("La informacion del elemento no corresponde a los datos esperados (coordenada x).");
        return;
    }

    try
    {
        Y = std::stod(y);
    }
    catch(const std::invalid_argument&) //Si la coordenada y no es un numero, se lanza una excepcion que se captura aquí
    {
        Interfaz::printError("La informacion del elemento no corresponde a los datos esperados (coordenada y).");
        return;
    }
    catch(const std::out_of_range&) //Si la magnitud es un numero pero es demasiado grande o pequeño para ser representado como double, se lanza una excepcion que se captura aquí
    {
        Interfaz::printError("La informacion del elemento no corresponde a los datos esperados (coordenada y).");
        return;
    }

    Elemento e(tipo, unidad, X, Y, tamano);
    elementos.push_back(e);

    Interfaz::printExito("El elemento ha sido agregado exitosamente.");
}

void GestorArchivo::agregarAnalisis(std::string analisis, std::string objeto, std::string comentario)
{
    if(!Analisis::esAnalisisCorrecto(analisis))
    {
        Interfaz::printError("La informacion del analisis no corresponde a los datos esperados (tipo).");
        return;
    }

    if(objeto.empty())
    {
        Interfaz::printError("La informacion del analisis no corresponde a los datos esperados (objeto).");
        return;
    }

    if(!comentario.empty())
    {
        if(comentario.front() != '\'' || comentario.back() != '\'' || comentario.length() < 2) // Para q no pongan simplemente ''
        {
            Interfaz::printError("La informacion del analisis no corresponde a los datos esperados (comentario).");
            return;
        }
    }

    Analisis a(analisis, objeto, comentario);
    Comando c(a);
    comandos.push_back(c);

    Interfaz::printExito("El comando de analisis ha sido agregado exitosamente.");
}

void GestorArchivo::agregarMovimiento(std::string movimiento, std::string magnitud, std::string unidad)
{
    if(!Movimiento::esTipoCorrecto(movimiento))
    {
        Interfaz::printError("La informacion del movimiento no corresponde a los datos esperados (tipo).");
        return;
    }

    double tam;

    try
    {
        tam = std::stod(magnitud);
    }
    catch(const std::invalid_argument&) //Si la magnitud no es un numero, se lanza una excepcion que se captura aquí
    {
        Interfaz::printError("La informacion del movimiento no corresponde a los datos esperados (magnitud).");
        return;
    }
    catch(const std::out_of_range&) //Si la magnitud es un numero pero es demasiado grande o pequeño para ser representado como double, se lanza una excepcion que se captura aquí
    {
        Interfaz::printError("La informacion del movimiento no corresponde a los datos esperados (magnitud).");
        return;
    }

    if(!Movimiento::esUnidadCorrecta(unidad, movimiento))
    {
        Interfaz::printError("La informacion del movimiento no corresponde a los datos esperados (unidad).");
        return;
    }

    Movimiento m(movimiento, tam, unidad);
    Comando c(m);
    comandos.push_back(c);

    Interfaz::printExito("El comando de movimiento ha sido agregado exitosamente.");
}

void GestorArchivo::guardar(std::string tipo_archivo, std::string nombre_archivo)
{
    if(tipo_archivo == "comandos")
    {
        if(comandos.empty()) // Si no hay comandos en memoria, no tiene sentido guardar un archivo de comandos
        {
            Interfaz::printError("La informacion requerida no esta almacenada en memoria.");
            return;
        }

        std::ofstream salida(nombre_archivo);

        if(!salida)
        {
            Interfaz::printError("Error guardando en " + nombre_archivo + ".");
            return;
        }

        for(size_t i = 0; i < comandos.size(); i++) // Usamos size_t para evitar warnings de comparación entre signed y unsigned
        {
            Comando c = comandos[i];

            if(c.esTipoAnalisis())
            {
                Analisis a = c.getAnalisis();

                salida
                    << a.getTipo() << " "
                    << a.getObjeto() << " "
                    << a.getComentario();
            }
            else
            {
                Movimiento m = c.getMovimiento();

                salida
                    << m.getTipo() << " "
                    << m.getTamano() << " "
                    << m.getUnidad();
            }

            if(i < comandos.size() - 1)
                salida << std::endl;
        }

        Interfaz::printExito("La informacion ha sido guardada en " + nombre_archivo + ".");
    }
    else if(tipo_archivo == "elementos")
    {
        if(elementos.empty()) // Si no hay elementos en memoria, no tiene sentido guardar un archivo de elementos
        {
            Interfaz::printError("La informacion requerida no esta almacenada en memoria.");
            return;
        }

        std::ofstream salida(nombre_archivo);

        if(!salida)
        {
            Interfaz::printError("Error guardando en " + nombre_archivo + ".");
            return;
        }

        for(size_t i = 0; i < elementos.size(); i++)
        {
            Elemento e = elementos[i];

            salida
                << e.getTipo() << " "
                << e.getTamano() << " "
                << e.getUnidad() << " "
                << e.getX() << " "
                << e.getY();

            if(i < elementos.size() - 1)
                salida << std::endl;
        }

        Interfaz::printExito("La informacion ha sido guardada en " + nombre_archivo + ".");
    }
    else
    {
        Interfaz::printError("El tipo especificado es incorrecto.");
        Interfaz::printError("Revise guardar '--ayuda'");
    }
}

double GestorArchivo::cambiarUnidad(double &magnitud, std::string unidad)
{
    if(unidad == "cm") return magnitud * 100;
    else if(unidad == "dm") return magnitud * 10;
    else if(unidad == "m") return magnitud;
    else if(unidad == "km") return magnitud / 1000;
    else if(unidad == "rad") return magnitud;
    else if(unidad == "grd") return magnitud * pi / 180;
    else return 0.0;
}

void GestorArchivo::ejecutarAvance(double &x, double &y, double &angulo, double &distancia)
{
    // 'distancia' está en metros.
    x += cos(angulo) * distancia;
    y += sin(angulo) * distancia;
}

void GestorArchivo::rotar(double &theta, double &angulo, std::string unidad)
{
    angulo = cambiarUnidad(angulo, unidad);
    theta += angulo;

    while(theta > 2 * pi) // Brosito esto es para q no salga de rango, no es necesario pero se ve más bonito
        theta -= 2 * pi;

    while(theta < -2 * pi) // Esto también es para que no salga de rango, por si el ángulo de rotación es negativo y grande
        theta += 2 * pi;
}


void GestorArchivo::simularComandos(std::string x, std::string y)
{
    if(comandos.empty())
    {
        Interfaz::printError("La informacion requerida no esta almacenada en memoria.");
        return;
    }

    double X, Y;

    try
    {
        X = std::stod(x);
        Y = std::stod(y);
    }
    catch(const std::invalid_argument &e)
    {
        Interfaz::printError("Las coordenadas no son un número real.");
        return;
    }

    double theeta = 0; // radianes

    for(const Comando& c : comandos)
    {
        if(!c.esTipoAnalisis())
        {
            Movimiento m = c.getMovimiento();
            double tam = m.getTamano();

            std::string tipo = m.getTipo();
            for(char &c : tipo)
                c = std::tolower(c);

            if(tipo == "avanzar")
            {
                tam = cambiarUnidad(tam, m.getUnidad());
                ejecutarAvance(X, Y, theeta, tam);
            }
            else
            {
                rotar(theeta, tam, m.getUnidad());
            }
        }
    }

    Interfaz::printExito(
        "La simulacion de los comandos, a partir de la posicion (" +
        x + "," + y + "), deja al robot en la nueva posicion (" +
        std::to_string(X) + "," + std::to_string(Y) + ")."
    );
}

int GestorArchivo::validarComando(std::string comando)
{
    std::istringstream ss(comando);
    std::string tipo;
    ss >> tipo;

    if(Analisis::esAnalisisCorrecto(tipo)) return 1;
    else if(Movimiento::esTipoCorrecto(tipo)) return 2;
    return 0;
}