#include "Escritor.h"

namespace URGEscritor {
    struct Escritor {
        TipoEscritor tipo = CONSOLA;
        std::ofstream archivo;
    };

    /*
	 * Precondicion: -
	 * Postcondicion: Si @nombreArchivo es un nombre de archivo invalido devuelve NULL.
	 * Si @nombreArchivo es valido devuelve una instancia de Escritor del tipo archivo.
	 * Parametros:
	 * 		@nombreArchivo: ruta y nombre del archivo donde se desea escribir
	 * 		@return: Instancia de Escritor lista para ser utilizada por las primitivas del TDA UGBEscritor
	 */
    Escritor* CrearEscritorArchivo(string nombreArchivo) {
        Escritor* escritor = new Escritor;
        escritor->tipo = ARCHIVO;
        escritor->archivo.open(nombreArchivo);

        if (!escritor->archivo.is_open()) {
            delete escritor;
            return nullptr;
        }
        return escritor;
    }

    /*
	 * Precondicion: -
	 * Postcondicion: Devuelve una instancia de Escritor del tipo consola.
	 * Parametros:
	 * 		@return: Instancia de Escritor lista para ser utilizada por las primitivas del TDA Escritor
	 */
    Escritor* CrearEscritorConsola() {
        Escritor* escritor = new Escritor;
        escritor->tipo = CONSOLA;
        return escritor;
    }

    /*
	 * Precondicion: @escritor fue creado con alguna de las primitivas: CrearEscritorArchivo o CrearEscritorConsola
	 * Postcondicion: Si el @escritor es del tipo Consola escribe @texto en la salida estandard y agrega una nueva linea.
	 * Si @escritor es del tipo archivo escribe @texto al final del archivo y agrega una nueva linea.
	 * Parametros:
	 * 		@escritor: Instancia de Escritor donde se desea escribir el @texto
	 * 		@texto: Mensaje que se desea escribir.
	 */
    void Escribir(Escritor* escritor, string texto) {
        if (escritor->tipo == CONSOLA) {
            std::cout << texto << std::endl;
        }
        else if (escritor->tipo == ARCHIVO) {
            escritor->archivo << texto << std::endl;
        }
    }

    /*
	 * Precondiciones: @escritor es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Libera todos los recursos asociados a @escritor
	 */
    void Destruir(Escritor* escritor) {
        if (escritor->tipo == ARCHIVO) {
            escritor->archivo.close();
        }
        delete escritor;
    }

}
