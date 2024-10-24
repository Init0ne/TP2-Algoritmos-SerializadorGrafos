#ifndef ESCRITOR_H_
#define ESCRITOR_H_

#include <fstream>
#include <iostream>
#include <string>
using std::string;

namespace URGEscritor{
	enum TipoEscritor { ARCHIVO, CONSOLA };
	struct Escritor;

	/*
	 * Precondicion: -
	 * Postcondicion: Si @nombreArchivo es un nombre de archivo invalido devuelve NULL.
	 * Si @nombreArchivo es valido devuelve una instancia de Escritor del tipo archivo.
	 * Si el archivo existia, el archivo es truncado.
	 * Parametros:
	 * 		@nombreArchivo: ruta y nombre del archivo donde se desea escribir
	 * 		@return: Instancia de Escritor lista para ser utilizada por las primitivas del TDA UGBEscritor
	 */
	Escritor* CrearEscritorArchivo(string nombreArchivo);

	/*
	 * Precondicion: -
	 * Postcondicion: Devuelve una instancia de Escritor del tipo consola.
	 * Parametros:
	 * 		@return: Instancia de Escritor lista para ser utilizada por las primitivas del TDA Escritor
	 */
	Escritor* CrearEscritorConsola();

	/*
	 * Precondicion: @escritor fue creado con alguna de las primitivas: CrearEscritorArchivo o CrearEscritorConsola
	 * Postcondicion: Si el @escritor es del tipo Consola escribe @texto en la salida estandard y agrega una nueva linea.
	 * Si @escritor es del tipo archivo escribe @texto al final del archivo y agrega una nueva linea.
	 * Parametros:
	 * 		@escritor: Instancia de Escritor donde se desea escribir el @texto
	 * 		@texto: Mensaje que se desea escribir.
	 */
	void Escribir(Escritor* escritor, string texto);

	/*
	 * Precondiciones: @escritor es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Libera todos los recursos asociados a @escritor
	 */
	void Destruir(Escritor* escritor);
}

#endif
