import argparse
import os
import ensayador_proyecto as ensayador


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-v", "--verbose", action="store_true", help="Muestra salida detallada.")
    args = parser.parse_args()

    base_dir = os.path.dirname(os.path.abspath(__file__))
    proyectos = os.path.join(base_dir, "proyectos")
    casos = os.path.join(base_dir, "casos_prueba")

    if args.verbose:
        print(f"Buscando proyectos en: {proyectos}")
        print(f"Buscando casos en: {casos}")

    resultado = ensayador.ejecutar_proyectos(proyectos, casos, verbose=args.verbose)
    if args.verbose and resultado is not None:
        print(resultado)
    elif isinstance(resultado, str) and resultado.startswith("ERROR:"):
        print(resultado)
    print("Fin")


if __name__ == "__main__":
    main()
