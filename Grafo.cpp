#include "Grafo.h"
#include "GeneradorIdentificador.h"
#include <vector>
#include <list>
#include <string>
#include <algorithm>  // Para std::max
#include <unordered_map>
#include <sstream>

using namespace URGGeneradorIdentificador;
using namespace std;
using namespace URGGrafo;

namespace URGGrafo {
	struct Grafo {
		string id;
		string nombre;
		int cantidadVertices = 0;
		vector<list<int>> listaAdyacencia;
		TipoGrafo tipo = DIRIGIDO;
	};
	/*
	* Precondicion: -
	* Postcondicion: Si @cantidad de vertices es un numero mayor o igual que cero
	* devuelve un grafo dirigido de nombre @nombre al cual se le asocia un identificador unico.
	* Si @cantidad de vertices es menor que cero devueleve NULL
	*/
	Grafo* CrearGrafoDirigido(string nombre, int cantidadVertices) {
		if (cantidadVertices < 0) {
			return nullptr;
		}
		else {
			Grafo* grafo = new Grafo;
			grafo->nombre = nombre;
			grafo->id = GenerarIdentificadorUnico();
			grafo->tipo = DIRIGIDO;
			grafo->listaAdyacencia.resize(cantidadVertices);
			grafo->cantidadVertices = cantidadVertices;
			return grafo;
		}
	}

	/*
	* Precondicion: -
	* Postcondicion: Si @cantidad de vertices es un numero mayor o igual que cero
	* devuelve un grafo no dirigido de nombre @nombre al cual se le asocia un identificador unico.
	* Si @cantidad de vertices es menor que cero devuelve NULL
	*/
	Grafo* CrearGrafoNoDirigido(string nombre, int cantidadVertices) {
		if (cantidadVertices < 0) {
			return nullptr;
		}
		else {
			Grafo* grafo = new Grafo;
			grafo->nombre = nombre;
			grafo->id = GenerarIdentificadorUnico();
			grafo->tipo = NODIRIGIDO;
			grafo->listaAdyacencia.resize(cantidadVertices);
			grafo->cantidadVertices = cantidadVertices;
			return grafo;
		}
	}

	/*
	* Precondicion: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	* Postcondicion: Devuelve el nombre de @grafo
	*/
	string ObtenerNombre(const Grafo* grafo) {
		return grafo->nombre;
	}

	/*
	* Precondicion: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	* Postcondicion: Devuelve el identificador unico de @grafo
	*/
	string ObtenerIdentificador(const Grafo* grafo) {
		return grafo->id;
	}

	/*
	* Precondicion: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	* Postcondicion: Si @grafo es un grafo no dirigido, se agrega una relacion de adyacencia conmutativa entre @verticeOrigen y @verticeDestino (@verticeOrigen es adyacente a @verticeDestino y viceversa).
	* Si @grafo es un grafo dirigido, se agrega una relacion de adyacencia de @verticeOrigen y @verticeDestino (@verticeOrigen es adyacente a @vertice destino)
	* Si @verticeOrigen o @verticeDestino no pertenece al grafo no realiza ninguna accion
	*/
	void Conectar(Grafo* grafo, int verticeOrigen, int verticeDestino) {
		if (verticeOrigen >= 0 && verticeDestino >= 0 &&
			verticeOrigen < grafo->cantidadVertices && verticeDestino < grafo->cantidadVertices) {
			if (grafo->tipo == DIRIGIDO) {
				grafo->listaAdyacencia[verticeOrigen].push_back(verticeDestino);
			}
			else {
				grafo->listaAdyacencia[verticeOrigen].push_back(verticeDestino);
				grafo->listaAdyacencia[verticeDestino].push_back(verticeOrigen);
			}
		}
	}

	/*
	* Precondicion: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	* Postcondicion: Devuelve true si @verticeOrigen es adyacente a @verticeDestino. Caso contrario devuelve false
	*/
	bool SonAdyacentes(const Grafo* grafo, int verticeOrigen, int verticeDestino) {
		if (verticeOrigen >= 0 && verticeOrigen < grafo->cantidadVertices &&
			verticeDestino >= 0 && verticeDestino < grafo->cantidadVertices) {
			for (int vertice : grafo->listaAdyacencia[verticeOrigen]) {
				if (vertice == verticeDestino) {
					return true;
				}
			}
		}
		return false;
	}

	/*
	* Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	* Postcondiciones: Devuelve los vertices en un registro en formato CSV donde cada campo es un vertice
	*/
	string ObtenerVertices(const Grafo* grafo) {
		if (grafo == nullptr || grafo->cantidadVertices == 0) {
			return "Sin Vertices";
		}

		string resultado;
		for (int i = 0; i < grafo->cantidadVertices; ++i) {
			resultado += std::to_string(i);
			if (i < grafo->cantidadVertices - 1) {
				resultado += ",";
			}
		}
		return resultado;
	}

	/*
	* Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	* Postcondiciones: Devuelve las aristas en formato de etiquetas.
	* El formato de etiquetas para un grafo no dirigido es el siguiente: 1-4 2-3 0-1
	* Donde nos dice que el conjunto E del grafo es: {(1,4), (2,3), (0,1)}
	* El formato de etiquetas para un grafo dirigido es el siguiente: 1-4 2-3 4-1
	* Donde nos dice que el conjunto E del grafo es: {(1,4), (2,3), (0,1), (4,1)}
	*
	* Vemos que en ambos casos son las adyacencias separadas por espacio.
	* Para el caso de los grafos no dirigidos no hay que duplicar las relaciones conmutativas
	*/
	string ObtenerAristas(const Grafo* grafo) {
		if (grafo == nullptr || grafo->listaAdyacencia.size() == 0) {
			return "Sin Aristas";
		}

		string resultado;
		vector<vector<bool>> visitado(grafo->listaAdyacencia.size(), vector<bool>(grafo->listaAdyacencia.size(), false));

		for (int i = 0; i < grafo->listaAdyacencia.size(); ++i) {
			for (int vecino : grafo->listaAdyacencia[i]) {
				if (grafo->tipo == DIRIGIDO) {
					resultado += std::to_string(i) + "-" + std::to_string(vecino) + " ";
				}
				else {
					if (!visitado[i][vecino]) {
						resultado += std::to_string(i) + "-" + std::to_string(vecino) + " ";
						visitado[i][vecino] = visitado[vecino][i] = true;
					}
				}
			}
		}

		// Eliminar el espacio final si existe
		if (!resultado.empty() && resultado.back() == ' ') {
			resultado.pop_back();
		}

		return resultado;
	}

	/*
 * Precondiciones:
 * - @nombre es un nombre válido para el grafo.
 * - @tipo es un valor de TipoGrafo (DIRIGIDO o NODIRIGIDO).
 * - @cantidadVertices es mayor o igual a cero.
 *
 * Postcondiciones:
 * - Devuelve un puntero a un nuevo Grafo inicializado con el nombre, tipo, identificador único, y lista de adyacencia de tamaño @cantidadVertices.
 */
	Grafo* InicializarGrafo(const string& nombre, TipoGrafo tipo, int cantidadVertices) {
		Grafo* nuevoGrafo = new Grafo;
		nuevoGrafo->nombre = nombre;
		nuevoGrafo->id = GenerarIdentificadorUnico();
		nuevoGrafo->tipo = tipo;
		nuevoGrafo->cantidadVertices = cantidadVertices;
		nuevoGrafo->listaAdyacencia.resize(cantidadVertices);

		return nuevoGrafo;
	}

	/*
	 * Precondiciones: @grafo1 y @grafo2 son instancias validas creadas con alguna de las primitivas creacionales
	 * Postcondiciones: Devuelve una instancia nueva de Grafo que es la union de conjuntos de los vertices y aristas de @grafo1 y @grafo2
	 */
	Grafo* ObtenerUnion(const Grafo* grafo1, const Grafo* grafo2) {
		if (grafo1->tipo != grafo2->tipo) {
			return nullptr;
		}

		Grafo* grafoUnion = InicializarGrafo("Union_" + grafo1->nombre + "_" + grafo2->nombre, grafo1->tipo,
			std::max(grafo1->cantidadVertices, grafo2->cantidadVertices));

		for (int indiceVerticeGrafo1 = 0; indiceVerticeGrafo1 < grafo1->cantidadVertices; ++indiceVerticeGrafo1) {
			for (int verticeAdyacente : grafo1->listaAdyacencia[indiceVerticeGrafo1]) {
				grafoUnion->listaAdyacencia[indiceVerticeGrafo1].push_back(verticeAdyacente);
			}
		}

		if (grafoUnion->tipo == DIRIGIDO) {
			for (int indiceVerticeGrafo2 = 0; indiceVerticeGrafo2 < grafo2->cantidadVertices; ++indiceVerticeGrafo2) {
				for (int verticeAdyacente : grafo2->listaAdyacencia[indiceVerticeGrafo2]) {
					grafoUnion->listaAdyacencia[indiceVerticeGrafo2].push_back(verticeAdyacente);
				}
			}
		}

		else {
			vector<vector<bool>> aristaAgregada(grafoUnion->cantidadVertices, vector<bool>(grafoUnion->cantidadVertices, false));

			for (int indiceVerticeGrafo1 = 0; indiceVerticeGrafo1 < grafo1->cantidadVertices; ++indiceVerticeGrafo1) {
				for (int verticeAdyacente : grafo1->listaAdyacencia[indiceVerticeGrafo1]) {
					aristaAgregada[indiceVerticeGrafo1][verticeAdyacente] = aristaAgregada[verticeAdyacente][indiceVerticeGrafo1] = true;
				}

				for (int indiceVerticeGrafo2 = 0; indiceVerticeGrafo2 < grafo2->cantidadVertices; ++indiceVerticeGrafo2) {
					for (int verticeAdyacente : grafo2->listaAdyacencia[indiceVerticeGrafo2]) {
						if (!aristaAgregada[indiceVerticeGrafo2][verticeAdyacente]) {
							grafoUnion->listaAdyacencia[indiceVerticeGrafo2].push_back(verticeAdyacente);
							aristaAgregada[indiceVerticeGrafo2][verticeAdyacente] = aristaAgregada[verticeAdyacente][indiceVerticeGrafo2] = true;
						}
					}
				}
			}

			return grafoUnion;

		}
	}

	/*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Devuelve una instancia nueva del Grafo que es el complemento de @grafo
	 */
	Grafo* ObtenerGrafoComplementario(const Grafo* grafo) {
		if (!grafo) {
			return nullptr;
		}

		Grafo* grafoComplementario = InicializarGrafo("Complemento_" + grafo->nombre, grafo->tipo, grafo->cantidadVertices);

		// Recorremos todos los pares de vértices para encontrar los que no son adyacentes
		for (int verticeOrigen = 0; verticeOrigen < grafo->cantidadVertices; ++verticeOrigen) {
			for (int verticeDestino = 0; verticeDestino < grafo->cantidadVertices; ++verticeDestino) {
				// Para grafos dirigidos o para evitar duplicados en grafos no dirigidos
				if ((grafo->tipo == DIRIGIDO) || (verticeDestino > verticeOrigen)) {
					if (!SonAdyacentes(grafo, verticeOrigen, verticeDestino) && verticeOrigen != verticeDestino) {
						grafoComplementario->listaAdyacencia[verticeOrigen].push_back(verticeDestino);
						if (grafo->tipo == NODIRIGIDO) {
							grafoComplementario->listaAdyacencia[verticeDestino].push_back(verticeOrigen);
						}
					}
				}
			}
		}

		return grafoComplementario;
	}

	/*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Si es @grafo es un grafo no dirigido devuelve el grado del vertice @vertice. Si es un grafo dirigido, devuelve el grado de salida de @vertice
	 */
	int ObtenerGrado(const Grafo* grafo, int vertice) {
		int grado = -1;
		if (grafo && vertice >= 0 && vertice < grafo->cantidadVertices) {
			if (grafo->tipo == NODIRIGIDO) {
				grado = grafo->listaAdyacencia[vertice].size();
			}
			else if (grafo->tipo == DIRIGIDO) {
				grado = grafo->listaAdyacencia[vertice].size();

			}
		}
		return grado;
	}

	/*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Asocia la etiqueta @etiqueta al vertive @vertice de @grafo. Si ya tenia etiqueta la sobreescribe por @etiqueta
	 */
	unordered_map<const Grafo*, unordered_map<int, string>> etiquetasVertices;
	void AgregarEtiqueta(Grafo* grafo, int vertice, string etiqueta) {
		if (!grafo || vertice < 0 || vertice >= grafo->cantidadVertices) {
			return;
		}
		etiquetasVertices[grafo][vertice] = etiqueta;
	}

	/*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Devuelve true si @grafo es un grafo completo. Caso contrario devuelve false
	 */
	bool EsCompleto(const Grafo* grafo) {
		if (grafo == nullptr) {
			return false;
		}

		int numVertices = grafo->cantidadVertices;

		for (int verticeOrigen = 0; verticeOrigen < numVertices; ++verticeOrigen) {
			for (int verticeDestino = 0; verticeDestino < numVertices; ++verticeDestino) {
				if (verticeOrigen != verticeDestino) {
					if (!SonAdyacentes(grafo, verticeOrigen, verticeDestino)) {
						return false;
					}
				}
			}
		}
		return true;
	}

	/*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Devuelve la sucesion grafica de @grafo separados por coma
	 */
	string ObtenerSucesionGrafica(const Grafo* grafo) {
		// Verifica si el puntero al grafo es nulo
		if (!grafo) {
			return "";
		}

		std::vector<int> grados;

		// Calcular el grado de cada vértice y agregarlo al vector de grados
		for (int i = 0; i < grafo->cantidadVertices; ++i) {
			int grado = 0;

			// Contar cuántos vértices están conectados al vértice actual
			for (int j = 0; j < grafo->cantidadVertices; ++j) {
				if (i != j && SonAdyacentes(grafo, i, j)) {
					++grado;
				}
			}

			grados.push_back(grado);
		}

		// Ordenar los grados en orden descendente
		std::sort(grados.begin(), grados.end(), std::greater<int>());

		// Convertir el vector de grados a un string separado por comas
		std::ostringstream resultado;
		for (size_t i = 0; i < grados.size(); ++i) {
			resultado << grados[i];
			if (i != grados.size() - 1) {
				resultado << ",";
			}
		}

		return resultado.str();
	}

	/*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Devuelve la cantidad de vertices de @grafo
	 */
	int ObtenerCantidadVertices(const Grafo* grafo) {
		if (grafo == nullptr) {
			return 0;
		}
		return grafo->cantidadVertices;
	}

	/*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Cambia el nombre que tiene @grafo por @nombre
	 */
	void CambiarNombre(Grafo* grafo, string nombre) {
		if (!grafo) {
			return;
		}
		grafo->nombre = nombre;
	}

	/*
	* Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	* Postcondiciones: Libera todos los recursos asociados a @grafo
	*/
	void DestruirGrafo(Grafo* grafo) {
		if (grafo == nullptr) {
			return;
		}
		grafo->listaAdyacencia.clear();
		delete grafo;
	}
}
