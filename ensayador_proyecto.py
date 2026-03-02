import glob
import os
import subprocess


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
            if os.path.isfile(os.path.join(ruta_casos, caso))
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
        os.path.dirname(ruta_casos) if os.path.isdir(ruta_casos) else os.path.dirname(os.path.abspath(ruta_casos))
    )
    for proyecto, ejecutable in proyecto_ejecutable.items():
        nombre_proyecto = os.path.basename(proyecto)
        print(f"Ejecutando Proyecto: {nombre_proyecto}")
        for caso in archivos_casos:
            print(f"Ejecutando {caso} en {nombre_proyecto}")
            ruta_completa_caso = caso if os.path.isfile(ruta_casos) else os.path.join(ruta_casos, caso)
            comando_ejecucion = f"{ejecutable} < {ruta_completa_caso}"
            with open(ruta_completa_caso, "r") as archivo_caso:
                comandos_entrada = archivo_caso.read()

            try:
                with open(ruta_completa_caso, "r") as f:
                    ejecutar = subprocess.run(
                        [ejecutable],
                        stdin=f,
                        capture_output=True,
                        text=True,
                        timeout=2,
                        cwd=base_ejecucion,
                    )
                salida = ejecutar.stdout
                error = ejecutar.stderr
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
                "entrada": comandos_entrada,
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
                fragmentos_salida = [frag.strip() for frag in resultado["salida"].split("$") if frag.strip()]
                error = resultado["error"].strip()

                if not comandos:
                    comandos = [resultado["comando"]]

                for i, comando in enumerate(comandos):
                    if i < len(fragmentos_salida):
                        salida = fragmentos_salida[i]
                    elif i == len(comandos) - 1 and error:
                        salida = error
                    else:
                        salida = "(sin salida)"

                    salida_txt.write(f">{comando}\n")
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
