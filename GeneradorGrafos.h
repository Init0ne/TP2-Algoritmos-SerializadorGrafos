#ifndef GENERADORGRAFOS_H_
#define GENERADORGRAFOS_H_

#include "Grafo.h"
using URGGrafo::Grafo;

namespace URGGeneradorGrafos{
	/*
	 * Precondicion: ninguna
	 * Postcondicion: Devuelve una instancia nueva de grafo con las siguientes caracteristicas
	 * - Nombre: random_001 donde 001 sera el numero de llamadas realizadas a esta primitiva (la segunda vez sera 002)
	 * - La cantidad de vertices del grafo es @vertices
	 * - El tope maximo de aristas del grafo sera @maximaCantidadAristas y estas deben ser aleatorias
	 */
	Grafo* ObtenerGrafoRandom(unsigned int vertices, int maximaCantidadAristas =0);

	/*
	 * Precondicion: ninguna
	 * Postcondicion: Devuelve una instancia nueva de un grafo completo de una cantidad de vertices igual a @vertices
	 * de nombre completo_@vertices. Ejemplo de nombre si se invoca con 22 vertices: completo_22
	 */
	Grafo* ObtenerGrafoCompleto(unsigned int vertices);

	/*
	 * Precondicion: ninguna
	 * Postcondicion: Devuelve una instancia nueva de un grafo que cumple las siguientes caracteristicas
	 * - El nombre del grafo es provincias_argentinas
	 * - Los vertices representan las provincias argentinas
	 * - Las aristas representan la relacion "es limitrofe"
	 * - Cada vertice tiene como etiqueta la abreviatura de la provincia
	 */
	Grafo* ObtenerGrafoProvinciasArgentina();

	/*
	 * Precondicion: ninguna
	 * Postcondicion: Devuelve una instancia nueva de el grafo de Petersen de nombre petersen
	 */
	Grafo* ObtenerGrafoPetersen();
}

#endif
