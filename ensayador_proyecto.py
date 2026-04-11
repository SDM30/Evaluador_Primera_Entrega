import glob
import os
import re
import subprocess

ANSI_ESCAPE_RE = re.compile(r"\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~])")
COMANDOS_CONSOLA = {
    "cargar_comandos",
    "cargar_elementos",
    "agregar_movimiento",
    "agregar_analisis",
    "agregar_elemento",
    "guardar",
    "simular_comandos",
    "ubicar_elementos",
    "en_cuadrante",
    "crear_mapa",
    "ruta_mas_larga",
    "ayuda",
    "clear",
    "salir",
}
TIPOS_MOVIMIENTO = {"avanzar", "girar"}
TIPOS_ANALISIS = {"fotografiar", "perforar", "composicion"}


def decodificar_bytes(datos):
    """Decodifica bytes de salida de procesos con fallback seguro."""
    if datos is None:
        return ""
    if isinstance(datos, str):
        return datos
    try:
        return datos.decode("utf-8")
    except UnicodeDecodeError:
        return datos.decode("utf-8", errors="replace")


def limpiar_ansi(texto):
    """Elimina secuencias ANSI y retornos de carro de una salida de terminal."""
    if not texto:
        return ""
    return ANSI_ESCAPE_RE.sub("", texto).replace("\r", "")


def extraer_respuestas_por_prompt(salida):
    """Separa la salida por prompt ('$:' o '$ ') y retorna una respuesta por comando."""
    if not salida:
        return []

    # Prompt válido al inicio de línea o encadenado por espacios: "$: " y "$ "
    partes = re.split(r"(?<!\S)\$(?::)?\s*", salida)

    if len(partes) == 1:
        unico = salida.strip()
        return [unico] if unico else []

    encabezado = partes[0].strip()
    respuestas = [fragmento.strip() for fragmento in partes[1:]]

    while respuestas and not respuestas[-1]:
        respuestas.pop()

    if encabezado:
        if respuestas:
            respuestas[0] = f"{encabezado}\n{respuestas[0]}".strip()
        else:
            respuestas = [encabezado]

    return respuestas


def construir_comandos_para_caso(nombre_caso, comandos):
    """
    Normaliza comandos según el tipo de archivo de caso.
    - elementos_* => agregar_elemento ...
    - comandos_*  => agregar_movimiento/agregar_analisis ...
    Si el archivo ya contiene comandos de consola, se respeta tal cual.
    """
    if not comandos:
        return [], []

    primeros_tokens = [linea.split()[0] for linea in comandos if linea.split()]
    if primeros_tokens and all(token in COMANDOS_CONSOLA for token in primeros_tokens):
        return comandos, comandos

    if nombre_caso.startswith("elementos_"):
        return [f"agregar_elemento {linea}" for linea in comandos], comandos

    if nombre_caso.startswith("comandos_"):
        comandos_normalizados = []
        for linea in comandos:
            partes = linea.split()
            if not partes:
                continue
            tipo = partes[0]
            if tipo in TIPOS_ANALISIS:
                comandos_normalizados.append(f"agregar_analisis {linea}")
            elif tipo in TIPOS_MOVIMIENTO:
                comandos_normalizados.append(f"agregar_movimiento {linea}")
            elif len(partes) <= 3:
                comandos_normalizados.append(f"agregar_movimiento {linea}")
            else:
                comandos_normalizados.append(f"agregar_analisis {linea}")
        return comandos_normalizados, comandos

    return comandos, comandos


def cargar_proyecto(ruta_proyectos):
    """Retorna los subdirectorios de proyectos como rutas absolutas."""
    try:
        if not os.path.exists(ruta_proyectos):
            return []
        proyectos = [
            os.path.join(ruta_proyectos, proyecto)
            for proyecto in os.listdir(ruta_proyectos)
            if os.path.isdir(os.path.join(ruta_proyectos, proyecto))
        ]
        return proyectos
    except Exception as e:
        print(f"Error al cargar proyectos: {e}")
        return []


def cargar_casos_prueba(ruta_casos):
    """Retorna la lista de archivos de casos de prueba."""
    try:
        if not os.path.exists(ruta_casos):
            return []
        if os.path.isfile(ruta_casos):
            return [ruta_casos]
        casos = [
            caso
            for caso in os.listdir(ruta_casos)
            if os.path.isfile(os.path.join(ruta_casos, caso)) and not caso.startswith("salida_")
        ]
        return casos
    except Exception as e:
        print(f"Error al cargar casos: {e}")
        return []


def compilar_proyectos(dir_proyectos, verbose=False):
    """Retorna un diccionario: ruta_proyecto -> ruta_ejecutable."""
    proyecto_ejecutable = {}

    for i, ruta_proyecto in enumerate(dir_proyectos):
        nombre_proyecto = os.path.basename(ruta_proyecto)
        print(f"Compilando Proyecto: {nombre_proyecto}")
        archivos_cpp = glob.glob(os.path.join(ruta_proyecto, "*.cpp"))
        archivos_cpp.extend(glob.glob(os.path.join(ruta_proyecto, "*.cxx")))

        if not archivos_cpp:
            print("Compilacion no exitosa")
            if verbose:
                print(f"Sin archivos .cpp/.cxx en {ruta_proyecto}")
            continue

        nombre_ejecutable = os.path.abspath(f"temp_program{i}")
        comando_compilacion = ["g++", "-std=c++17", *archivos_cpp, "-o", nombre_ejecutable]
        if verbose:
            print(f"Comando compilacion: {' '.join(comando_compilacion)}")

        compilar = subprocess.run(comando_compilacion, capture_output=True, text=True)

        if compilar.returncode != 0:
            print("Compilacion no exitosa")
            if verbose:
                print(f"ERROR de compilacion {ruta_proyecto}:\n{compilar.stderr}")
            continue

        print("Compilacion exitosa")
        proyecto_ejecutable[ruta_proyecto] = nombre_ejecutable

    return proyecto_ejecutable


def probar_casos(proyecto_ejecutable, archivos_casos, ruta_casos, verbose=False):
    if not proyecto_ejecutable:
        if verbose:
            print("No se crearon ejecutables")
        return []

    resultados = []
    base_ejecucion = (
        os.path.abspath(ruta_casos) if os.path.isdir(ruta_casos) else os.path.dirname(os.path.abspath(ruta_casos))
    )
    for proyecto, ejecutable in proyecto_ejecutable.items():
        nombre_proyecto = os.path.basename(proyecto)
        print(f"Ejecutando Proyecto: {nombre_proyecto}")
        for caso in archivos_casos:
            print(f"Ejecutando {caso} en {nombre_proyecto}")
            ruta_completa_caso = (
                os.path.abspath(caso)
                if os.path.isfile(ruta_casos)
                else os.path.abspath(os.path.join(ruta_casos, caso))
            )
            comando_ejecucion = f"{ejecutable} < {ruta_completa_caso}"
            with open(ruta_completa_caso, "r") as archivo_caso:
                comandos_archivo = [linea.strip() for linea in archivo_caso.read().splitlines() if linea.strip()]

            comandos_ejecucion, comandos_reporte = construir_comandos_para_caso(caso, comandos_archivo)
            entrada_ejecucion = "\n".join(comandos_ejecucion)
            if not comandos_ejecucion or comandos_ejecucion[-1] != "salir":
                entrada_ejecucion = (f"{entrada_ejecucion}\n" if entrada_ejecucion else "") + "salir\n"

            try:
                ejecutar = subprocess.run(
                    [ejecutable],
                    input=entrada_ejecucion.encode("utf-8"),
                    stdout=subprocess.PIPE,
                    stderr=subprocess.STDOUT,
                    text=False,
                    timeout=2,
                    cwd=base_ejecucion,
                )
                salida = limpiar_ansi(decodificar_bytes(ejecutar.stdout))
                error = limpiar_ansi(decodificar_bytes(ejecutar.stderr))
                codigo = ejecutar.returncode
            except subprocess.TimeoutExpired:
                salida = ""
                error = "Timeout: la ejecucion excedio 2 segundos."
                codigo = -1
            except OSError as e:
                salida = ""
                error = f"No se pudo ejecutar el binario: {e}"
                codigo = -1

            resultado = {
                "proyecto": proyecto,
                "caso": caso,
                "comando": comando_ejecucion,
                "entrada": "\n".join(comandos_reporte),
                "salida": salida,
                "error": error,
                "codigo": codigo,
            }
            resultados.append(resultado)

            if verbose:
                if codigo == 0:
                    print("Ejecucion exitosa")
                    if salida:
                        print(f"  Salida: {salida}")
                else:
                    print(f"Error (codigo {codigo})")

    return resultados


def guardar_salidas_por_proyecto(resultados, ruta_salida):
    os.makedirs(ruta_salida, exist_ok=True)
    for archivo in os.listdir(ruta_salida):
        if archivo.endswith(".txt"):
            try:
                os.remove(os.path.join(ruta_salida, archivo))
            except OSError:
                pass

    proyectos = []
    for resultado in resultados:
        proyecto = resultado["proyecto"]
        if proyecto not in proyectos:
            proyectos.append(proyecto)

    for proyecto in proyectos:
        nombre_proyecto = os.path.basename(proyecto)
        archivo_proyecto = os.path.join(ruta_salida, f"{nombre_proyecto}.txt")

        with open(archivo_proyecto, "w") as salida_txt:
            for resultado in resultados:
                if resultado["proyecto"] != proyecto:
                    continue
                salida_txt.write(f"========== CASO: {resultado['caso']} ==========\n")

                comandos = [linea.strip() for linea in resultado["entrada"].splitlines() if linea.strip()]
                fragmentos_salida = extraer_respuestas_por_prompt(resultado["salida"])
                error = resultado["error"].strip()

                if not comandos:
                    comandos = [resultado["comando"]]

                for i, comando in enumerate(comandos):
                    salida = fragmentos_salida[i] if i < len(fragmentos_salida) else ""
                    if not salida and i == len(comandos) - 1 and error:
                        salida = error
                    if not salida:
                        salida = "(sin salida)"

                    salida_txt.write(f"$ {comando}\n")
                    salida_txt.write(f"{salida}\n")
                salida_txt.write("\n")


def ejecutar_proyectos(ruta_proyectos, ruta_casos, verbose=False):
    """Ejecuta proyectos contra casos de prueba."""
    dir_proyectos = cargar_proyecto(ruta_proyectos)
    if not dir_proyectos:
        return f"ERROR: No hay proyectos en {ruta_proyectos}"

    archivos_casos = cargar_casos_prueba(ruta_casos)
    if not archivos_casos:
        return f"ERROR: No hay casos de prueba en {ruta_casos}"

    if verbose:
        print(f"Proyectos encontrados: {len(dir_proyectos)}")
        print(f"Casos encontrados: {len(archivos_casos)}")

    proyecto_ejecutable = compilar_proyectos(dir_proyectos, verbose=verbose)
    if not proyecto_ejecutable:
        return "ERROR: Ningun proyecto compilo correctamente"

    resultados = probar_casos(proyecto_ejecutable, archivos_casos, ruta_casos, verbose=verbose)
    carpeta_salidas = os.path.join(os.path.dirname(os.path.abspath(ruta_proyectos)), "salidas")
    guardar_salidas_por_proyecto(resultados, carpeta_salidas)

    for _, ejecutable in proyecto_ejecutable.items():
        try:
            os.remove(ejecutable)
        except OSError:
            pass

    return f"Resultados guardados en: {carpeta_salidas}"
