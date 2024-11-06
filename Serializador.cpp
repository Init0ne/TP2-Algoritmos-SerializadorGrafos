#include "Serializador.h"
#include "Escritor.h"
#include "Grafo.h"

namespace URGSerializador {
	struct Serializador {
		Escritor* escritor; //Puntero al escritor que lo serializa en el archivo
		const Grafo* grafo; //Puntero al grafo que queres serializar
	};

	/*
		 * Precondicion: @escritor es una instancia valida
		 * Postcondicion: Crear un serializador de grafos que serializara el grafo en @escritor
		 */
	Serializador* CrearSerializador(URGEscritor::Escritor* escritor) {
		Serializador* serializador = new Serializador;
		serializador->escritor = escritor;
		return serializador;
	}

	/*
		 * Precondicion: ninguna
		 * Postcondicion: Crear un serializador de grafos que serializara el grafo en un escritor de arvhivos
		 * que tendra como nombre el siguiente: [@nombreGrafo].urg es decir el nombre del grafo con la extencion .urg
		 * Si no puede crear un escritor de archivo con ese nombre, devuelve NULL
		 */
	Serializador* CrearSerializador(string nombreGrafo) {
		string  nombreArchivo = nombreGrafo + ".urg";
		Escritor* escritor = URGEscritor::CrearEscritorArchivo(nombreArchivo);
		Serializador* serializador = new Serializador;
		serializador->escritor = escritor;
		return serializador;
	}

	/*
		 * Precondicion: ninguna
		 * Postcondicion: Serializa el grafo segun el siguiente formato
		 * [Comienzo]
		 * # Archivo "@nombreGrafo.urg" del URG (Undav Repositorio de grafos) 2018 Universidad Nacional de Avellaneda
		 * # Este archivo puede ser copiado libremente pero por favor no lo modifique!
		 * # Identificador: @identificadorUnicoGrafo
		 * #Vertices
		 * @v0
		 * @v1
		 * ...
		 * #Aristas
		 * @vx-@vy
		 * ...
		 * [Fin]
		 * Omitir los tags [Comienzo] y [Fin].
		 * Respetar el formato dado. Tener en cuenta que los vertices y aristas estan separador por nueva linea.
		 * Los vertices seran los numeros o las etiquetas (si es que el grafo tiene etiquetas)
		 */
	void Serializar(Serializador* serializador, const Grafo* grafo) {

		Escribir(serializador->escritor, "Archivo " + URGGrafo::ObtenerNombre(grafo) + ".urg del URG (Undav Repositorio de grafos) 2018 Universidad Nacional de Avellaneda");
		Escribir(serializador->escritor, "# Este archivo puede ser copiado libremente pero por favor no lo modifique!");
		Escribir(serializador->escritor, "# Identificador: " + URGGrafo::ObtenerIdentificador(grafo));

		Escribir(serializador->escritor, "# Vertices");
		//Modificar los vertices en formato CSV <Separados por comas> para que concuerden con la postcondicion
		string vertices = URGGrafo::ObtenerVertices(grafo);
		//Lee la cadena como un flujo de datos, investigar mas.
		std::istringstream stream(vertices);
		string vertice;
		//Separa luego de cada coma como si fuera una linea.
		while (std::getline(stream, vertice, ',')) {
			Escribir(serializador->escritor, "@v" + vertice);
		}

		Escribir(serializador->escritor, "# Aristas");
		//Modificar las aristas en formato CSV para que concuerden con la postcondicion
		string aristas = URGGrafo::ObtenerAristas(grafo);

		string aristaFormateada;
		for (char c : aristas) {
			if (c == ' ') {
				if (!aristaFormateada.empty()) {
					Escribir(serializador->escritor, "@" + aristaFormateada);
					aristaFormateada.clear();
				}
			}
			else {
				aristaFormateada += c;
			}
		}

		if (!aristaFormateada.empty()) {
			Escribir(serializador->escritor, "@" + aristaFormateada);
		}
	}

	/*
		 * Precondiciones: @serializador es una instancia valida creada con alguna de las primitivas creacionales
		 * Postcondiciones: Libera todos los recursos asociados a @serializador
		 */
	void DestruirSerializador(Serializador* serializador) {
		if (serializador != nullptr) {
			if (serializador->escritor != nullptr) {
				URGEscritor::Destruir(serializador->escritor);
			}
			delete serializador;
		}
	}
}