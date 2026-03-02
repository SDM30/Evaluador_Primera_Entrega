# Evaluador de Proyectos C++

Este módulo compila y ejecuta múltiples proyectos C++ contra un conjunto de casos de prueba, y genera un archivo de salida por proyecto.

## Requisitos

- Linux o entorno compatible con `python3` y `g++`
- Python 3.10+

Instalación de dependencias (si aplica en tu entorno):

```bash
pip install -r ../requerimientos.txt
```

## Estructura esperada

Dentro de `app/`:

```text
app/
  main.py
  ensayador_proyecto.py
  proyectos/
    Proyecto1/
      *.cpp o *.cxx
    Proyecto2/
      *.cpp o *.cxx
  casos_prueba/
    prueba1.txt
    prueba2.txt
  salidas/
    Proyecto1.txt
    Proyecto2.txt
```

Notas:
- Cada subcarpeta dentro de `proyectos/` se considera un proyecto independiente.
- Los casos de prueba se leen desde `casos_prueba/`.
- Los archivos de `salidas/*.txt` se regeneran en cada ejecución.

## Ejecución

Desde cualquier ruta:

```bash
python3 evaluador_primera_entrega/app/main.py
```

Con salida detallada (verbose):

```bash
python3 evaluador_primera_entrega/app/main.py -v
```

## Salida de consola

### Modo normal (sin `-v`)
Muestra un resumen:

- `Compilando Proyecto: <Nombre>`
- `Compilacion exitosa` o `Compilacion no exitosa`
- `Ejecutando Proyecto: <Nombre>`
- `Ejecutando <caso>.txt en <Nombre>`
- `Fin`

### Modo verbose (`-v`)
Además del resumen, muestra:

- rutas buscadas
- comando de compilación
- errores de compilación/ejecución
- salida completa del programa por caso

## Formato de archivos de salida

Se genera un archivo por proyecto en `app/salidas/<NombreProyecto>.txt`.

Cada archivo se divide por caso:

```text
========== CASO: prueba1.txt ==========
>comando1
salida1
>comando2
salida2
```

El símbolo `>` indica el comando leído desde el archivo de caso, y debajo aparece la salida asociada.

## Errores comunes

- `ERROR: No hay proyectos en ...`: la carpeta `proyectos/` no existe o está vacía.
- `ERROR: No hay casos de prueba en ...`: la carpeta `casos_prueba/` no existe o no tiene archivos.
- `Compilacion no exitosa`: el proyecto no tiene fuentes válidos (`.cpp/.cxx`) o `g++` falla.

## Archivos principales

- `app/main.py`: punto de entrada, parsea `-v` y dispara la ejecución.
- `app/ensayador_proyecto.py`: descubrimiento de proyectos, compilación, ejecución de casos y generación de salidas.
