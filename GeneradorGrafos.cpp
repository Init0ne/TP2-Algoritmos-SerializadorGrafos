#ifndef GENERADORGRAFOS_H_
#define GENERADORGRAFOS_H_
#include<iostream>
#include "Grafo.h"
#include <random>
#include <string>
#include <vector>
using namespace URGGrafo;


using namespace std;
using URGGrafo::Grafo;

namespace URGGeneradorGrafos {
	/*
	 * Precondicion: ninguna
	 * Postcondicion: Devuelve una instancia nueva de grafo con las siguientes caracteristicas
	 * - Nombre: random_001 donde 001 sera el numero de llamadas realizadas a esta primitiva (la segunda vez sera 002)
	 * - La cantidad de vertices del grafo es @vertices
	 * - El tope maximo de aristas del grafo sera @maximaCantidadAristas y estas deben ser aleatorias
	 */
	Grafo* ObtenerGrafoRandom(unsigned int vertices, int maximaCantidadAristas = 0);

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

	//FALTA 
	Grafo* ObtenerGrafoRandom(unsigned int vertices, int maximaCantidadAristas = 0) {

	}


	Grafo* ObtenerGrafoCompleto(unsigned int vertices) {

		string nombre = "completo_" + std::to_string(vertices);
		Grafo* grafo = CrearGrafoNoDirigido(nombre, vertices);

		for (unsigned int verticeOrigen = 0; verticeOrigen < vertices; ++verticeOrigen) {
			for (unsigned int verticeDestino = verticeOrigen + 1; verticeDestino < vertices; ++verticeDestino) {
				Conectar(grafo, verticeOrigen, verticeDestino);
			}
		}

		return grafo;
	}


	//FALTA 
	Grafo* ObtenerGrafoProvinciasArgentina() {}


	Grafo* ObtenerGrafoPetersen() {
		string nombre = "petersen";
		Grafo* grafo = CrearGrafoNoDirigido(nombre, 10);


		Conectar(grafo, 0, 1);
		Conectar(grafo, 1, 2);
		Conectar(grafo, 2, 3);
		Conectar(grafo, 3, 4);
		Conectar(grafo, 4, 0);


		Conectar(grafo, 5, 7);
		Conectar(grafo, 7, 9);
		Conectar(grafo, 9, 6);
		Conectar(grafo, 6, 8);
		Conectar(grafo, 8, 5);


		Conectar(grafo, 0, 5);
		Conectar(grafo, 1, 6);
		Conectar(grafo, 2, 7);
		Conectar(grafo, 3, 8);
		Conectar(grafo, 4, 9);

		return grafo;
	}



}
#endif