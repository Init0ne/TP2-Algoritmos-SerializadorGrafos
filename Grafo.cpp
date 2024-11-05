#include "Grafo.h"
#include "GeneradorIdentificador.h"

using namespace URGGeneradorIdentificador;

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
	 * Precondiciones: @grafo1 y @grafo2 son instancias validas creadas con alguna de las primitivas creacionales
	 * Postcondiciones: Devuelve una instancia nueva de Grafo que es la union de conjuntos de los vertices y aristas de @grafo1 y @grafo2
	 */
	Grafo* ObtenerUnion(const Grafo* grafo1, const Grafo* grafo2){

    }

    /*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Devuelve una instancia nueva del Grafo que es el complemento de @grafo
	 */
Grafo* ObtenerGrafoComplementario(const Grafo* grafo){
Grafo* ObtenerUnion(const Grafo* grafo1, const Grafo* grafo2) {
	if (grafo1->tipo != grafo2->tipo) {
		return nullptr; 
	}
	Grafo* grafoUnion = new Grafo;
	grafoUnion->nombre = "Union_" + grafo1->nombre + "_" + grafo2->nombre;
	grafoUnion->id = GenerarIdentificadorUnico();  
	grafoUnion->tipo = grafo1->tipo;

	grafoUnion->cantidadVertices = std::max(grafo1->cantidadVertices, grafo2->cantidadVertices);
	grafoUnion->listaAdyacencia.resize(grafoUnion->cantidadVertices);
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
		vector<vector<bool>> aristaAgregada (grafoUnion->cantidadVertices, vector<bool>(grafoUnion->cantidadVertices, false));

		for (int indiceVerticeGrafo1 = 0; indiceVerticeGrafo1 < grafo1->cantidadVertices; ++indiceVerticeGrafo1) {
			for (int verticeAdyacente : grafo1->listaAdyacencia[indiceVerticeGrafo1]) {
				aristaAgregada [indiceVerticeGrafo1][verticeAdyacente] = aristaAgregada [verticeAdyacente][indiceVerticeGrafo1] = true;
			}

		for (int indiceVerticeGrafo2 = 0; indiceVerticeGrafo2 < grafo2->cantidadVertices; ++indiceVerticeGrafo2) {
			for (int verticeAdyacente : grafo2->listaAdyacencia[indiceVerticeGrafo2]) {
				if (!aristaAgregada[indiceVerticeGrafo2][verticeAdyacente]) {
					grafoUnion->listaAdyacencia[indiceVerticeGrafo2].push_back(verticeAdyacente);
					aristaAgregada [indiceVerticeGrafo2][verticeAdyacente] = aristaAgregada [verticeAdyacente][indiceVerticeGrafo2] = true;
				}
			}
		}
	}

	return grafoUnion;



    }

    /*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Si es @grafo es un grafo no dirigido devuelve el grado del vertice @vertice. Si es un grafo dirigido, devuelve el grado de salida de @vertice
	 */
	int ObtenerGrado(const Grafo* grafo, int vertice){

    }

    /*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Asocia la etiqueta @etiqueta al vertive @vertice de @grafo. Si ya tenia etiqueta la sobreescribe por @etiqueta
	 */
	void AgregarEtiqueta(Grafo* grafo, int vertice, string etiqueta){

    }

    /*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Devuelve true si @grafo es un grafo completo. Caso contrario devuelve false
	 */
	bool EsCompleto(const Grafo* grafo){

    }

    /*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Devuelve la sucesion grafica de @grafo separados por coma
	 */
	string ObtenerSucesionGrafica(const Grafo* grafo){

    }

    /*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Devuelve la cantidad de vertices de @grafo
	 */
	int ObtenerCantidadVertices(const Grafo* grafo){

    }

    /*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Cambia el nombre que tiene @grafo por @nombre
	 */
	void CambiarNombre(Grafo* grafo, string nombre){
        
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
