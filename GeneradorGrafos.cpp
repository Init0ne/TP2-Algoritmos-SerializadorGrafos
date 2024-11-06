#ifndef GENERADORGRAFOS_H_
#define GENERADORGRAFOS_H_
#include<iostream>
#include "Grafo.h"
#include <random>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace URGGrafo;


using namespace std;
using URGGrafo::Grafo;

namespace URGGeneradorGrafos {

	static int llamadasRandom = 0;  // Contador para generar nombres únicos
	/*
	 * Precondicion: ninguna
	 * Postcondicion: Devuelve una instancia nueva de grafo con las siguientes caracteristicas
	 * - Nombre: random_001 donde 001 sera el numero de llamadas realizadas a esta primitiva (la segunda vez sera 002)
	 * - La cantidad de vertices del grafo es @vertices
	 * - El tope maximo de aristas del grafo sera @maximaCantidadAristas y estas deben ser aleatorias
	 */
	Grafo* ObtenerGrafoRandom(unsigned int vertices, int maximaCantidadAristas);

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
	Grafo* ObtenerGrafoRandom(unsigned int vertices, int maximaCantidadAristas) {
		llamadasRandom++;

		string numeroFormateado = std::to_string(llamadasRandom);
		numeroFormateado = string(3 - numeroFormateado.length(), '0') + numeroFormateado;
		string nombre = "random_" + numeroFormateado;

		Grafo* grafo = CrearGrafoNoDirigido(nombre, vertices);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> vertice_dist(0, vertices - 1);

		int intentos = 0;
		int aristasCreadas = 0;
		const int maxIntentos = maximaCantidadAristas * 2;

		while (aristasCreadas < maximaCantidadAristas && intentos < maxIntentos) {
			int vertice1 = vertice_dist(gen);
			int vertice2 = vertice_dist(gen);

			if (vertice1 != vertice2 && !SonAdyacentes(grafo, vertice1, vertice2)) {
				Conectar(grafo, vertice1, vertice2);
				aristasCreadas++;
			}
			intentos++;
		}

		return grafo;
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
	Grafo* ObtenerGrafoProvinciasArgentina() {
		const int NUM_PROVINCIAS = 23;  
		Grafo* grafo = CrearGrafoNoDirigido("provincias_argentinas", NUM_PROVINCIAS + 1);

		vector<string> abreviaturas = {
			"CABA", "BA", "CAT", "CHA", "CHU", "CBA", "COR", "ER", "FOR", "JUJ",
			"LP", "LR", "MZA", "MIS", "NQN", "RN", "SAL", "SJ", "SL", "SC",
			"SF", "SE", "TF", "TUC"
		};

		for (int i = 0; i < NUM_PROVINCIAS + 1; i++) {
			AgregarEtiqueta(grafo, i, abreviaturas[i]);
		}

    // CABA (0)
    Conectar(grafo, 0, 1);  // Buenos Aires

    // Buenos Aires (1)
    Conectar(grafo, 1, 5);  // Córdoba
    Conectar(grafo, 1, 10); // La Pampa
    Conectar(grafo, 1, 20); // Santa Fe
    Conectar(grafo, 1, 19); // Río Negro

    // Catamarca (2)
    Conectar(grafo, 2, 5);  // Córdoba
    Conectar(grafo, 2, 11); // La Rioja
    Conectar(grafo, 2, 16); // Salta
    Conectar(grafo, 2, 21); // Santiago del Estero
    Conectar(grafo, 2, 23); // Tucumán

    // Chaco (3)
    Conectar(grafo, 3, 8);  // Formosa
    Conectar(grafo, 3, 20); // Santa Fe
    Conectar(grafo, 3, 21); // Santiago del Estero
    Conectar(grafo, 3, 6);  // Corrientes

    // Chubut (4)
    Conectar(grafo, 4, 19); // Río Negro
    Conectar(grafo, 4, 18); // Santa Cruz

    // Córdoba (5)
    Conectar(grafo, 5, 20); // Santa Fe
    Conectar(grafo, 5, 21); // Santiago del Estero
    Conectar(grafo, 5, 10); // La Pampa
    Conectar(grafo, 5, 18); // San Luis

    // Corrientes (6)
    Conectar(grafo, 6, 7);  // Entre Ríos
    Conectar(grafo, 6, 13); // Misiones
    Conectar(grafo, 6, 20); // Santa Fe

    // Entre Ríos (7)
    Conectar(grafo, 7, 20); // Santa Fe

    // Formosa (8)
    Conectar(grafo, 8, 16); // Salta

    // Jujuy (9)
    Conectar(grafo, 9, 16); // Salta

    // La Pampa (10)
    Conectar(grafo, 10, 19); // Río Negro
    Conectar(grafo, 10, 18); // San Luis
    Conectar(grafo, 10, 12); // Mendoza

    // La Rioja (11)
    Conectar(grafo, 11, 18); // San Luis
    Conectar(grafo, 11, 17); // San Juan
    Conectar(grafo, 11, 5);  // Córdoba

    // Mendoza (12)
    Conectar(grafo, 12, 17); // San Juan
    Conectar(grafo, 12, 14); // Neuquén

    // Misiones (13)
    // No necesita más conexiones, ya está conectada con Corrientes

    // Neuquén (14)
    Conectar(grafo, 14, 19); // Río Negro

    // Río Negro (15)
    // Ya están todas sus conexiones

    // Salta (16)
    Conectar(grafo, 16, 21); // Santiago del Estero
    Conectar(grafo, 16, 23); // Tucumán

    // San Juan (17)
    Conectar(grafo, 17, 18); // San Luis

    // San Luis (18)
    // Ya están todas sus conexiones

    // Santa Cruz (19)
    Conectar(grafo, 19, 22); // Tierra del Fuego (conexión marítima)

    // Santa Fe (20)
    Conectar(grafo, 20, 21); // Santiago del Estero

    // Santiago del Estero (21)
    Conectar(grafo, 21, 23); // Tucumán

    // Tierra del Fuego (22)
    // Ya está conectada (conexión marítima con Santa Cruz)

    // Tucumán (23)
    // Ya están todas sus conexiones
	
		return grafo;
	}


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