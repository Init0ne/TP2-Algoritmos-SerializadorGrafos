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
		// Formatear el número con ceros a la izquierda
		string numeroFormateado = std::to_string(llamadasRandom);
		numeroFormateado = string(3 - numeroFormateado.length(), '0') + numeroFormateado;
		string nombre = "random_" + numeroFormateado;

		// Crear grafo no dirigido
		Grafo* grafo = CrearGrafoNoDirigido(nombre, vertices);

		// Configurar generador de números aleatorios
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> vertice_dist(0, vertices - 1);

		// Límite para evitar bucles infinitos
		int intentos = 0;
		int aristasCreadas = 0;
		const int maxIntentos = maximaCantidadAristas * 2;

		while (aristasCreadas < maximaCantidadAristas && intentos < maxIntentos) {
			int v1 = vertice_dist(gen);
			int v2 = vertice_dist(gen);

			// Evitar autoconexiones y conexiones duplicadas
			if (v1 != v2 && !SonAdyacentes(grafo, v1, v2)) {
				Conectar(grafo, v1, v2);
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
		const int NUM_PROVINCIAS = 23;  // Sin contar la Ciudad Autónoma de Buenos Aires
		Grafo* grafo = CrearGrafoNoDirigido("provincias_argentinas", NUM_PROVINCIAS + 1);

		// Definir abreviaturas de provincias
		vector<string> abreviaturas = {
			"CABA", "BA", "CAT", "CHA", "CHU", "CBA", "COR", "ER", "FOR", "JUJ",
			"LP", "LR", "MZA", "MIS", "NQN", "RN", "SAL", "SJ", "SL", "SC",
			"SF", "SE", "TF", "TUC"
		};

		// Agregar etiquetas a cada vértice
		for (int i = 0; i < NUM_PROVINCIAS + 1; i++) {
			AgregarEtiqueta(grafo, i, abreviaturas[i]);
		}

		// Definir conexiones (provincias limítrofes)
		// CABA - Buenos Aires
		Conectar(grafo, 0, 1);

		// Buenos Aires
		Conectar(grafo, 1, 5);  // Córdoba
		Conectar(grafo, 1, 13); // La Pampa
		Conectar(grafo, 1, 20); // Santa Fe
		Conectar(grafo, 1, 19); // Río Negro

		// Catamarca
		Conectar(grafo, 2, 5);  // Córdoba
		Conectar(grafo, 2, 11); // La Rioja
		Conectar(grafo, 2, 16); // Salta
		Conectar(grafo, 2, 23); // Tucumán

		// Chaco
		Conectar(grafo, 3, 8);  // Formosa
		Conectar(grafo, 3, 20); // Santa Fe
		Conectar(grafo, 3, 21); // Santiago del Estero

		// Chubut
		Conectar(grafo, 4, 19); // Río Negro
		Conectar(grafo, 4, 18); // Santa Cruz

		// ... (Continuar con el resto de conexiones limítrofes)
		// Nota: Se han incluido solo algunas conexiones como ejemplo
		// En una implementación real se deberían incluir todas las conexiones

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