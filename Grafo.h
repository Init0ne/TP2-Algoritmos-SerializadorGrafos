#ifndef GRAFO_H_
#define GRAFO_H_

#include <sstream>
#include <string>
#include <list>
#include <vector>
#include "GeneradorIdentificador.h"
using std::string;
using std::vector;
using std::list;

namespace URGGrafo{

	enum TipoGrafo { DIRIGIDO, NODIRIGIDO };
	
	struct Grafo;

	/*
	 * Precondicion: -
	 * Postcondicion: Si @cantidad de vertices es un numero mayor o igual que cero
	 * devuelve un grafo dirigido de nombre @nombre al cual se le asocia un identificador unico.
	 * Si @cantidad de vertices es menor que cero devueleve NULL
	 */
	Grafo* CrearGrafoDirigido(string nombre, int cantidadVertices);

	/*
	 * Precondicion: -
	 * Postcondicion: Si @cantidad de vertices es un numero mayor o igual que cero
	 * devuelve un grafo no dirigido de nombre @nombre al cual se le asocia un identificador unico.
	 * Si @cantidad de vertices es menor que cero devuelve NULL
	 */
	Grafo* CrearGrafoNoDirigido(string nombre, int cantidadVertices);

	/*
	 * Precondicion: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Devuelve el nombre de @grafo
	 */
	string ObtenerNombre(const Grafo* grafo);

	/*
	 * Precondicion: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Devuelve el identificador unico de @grafo
	 */
	string ObtenerIdentificador(const Grafo* grafo);

	/*
	 * Precondicion: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Si @grafo es un grafo no dirigido, se agrega una relacion de adyacencia conmutativa entre @verticeOrigen y @verticeDestino (@verticeOrigen es adyacente a @verticeDestino y viceversa).
	 * Si @grafo es un grafo dirigido, se agrega una relacion de adyacencia de @verticeOrigen y @verticeDestino (@verticeOrigen es adyacente a @vertice destino)
	 * Si @verticeOrigen o @verticeDestino no pertenece al grafo no realiza ninguna accion
	 */
	void Conectar(Grafo* grafo, int verticeOrigen, int verticeDestino);

	/*
	 * Precondicion: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Devuelve true si @verticeOrigen es adyacente a @verticeDestino. Caso contrario devuelve false
	 */
	bool SonAdyacentes(const Grafo* grafo, int verticeOrigen, int verticeDestino);

	/*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Devuelve los vertices en un registro en formato CSV donde cada campo es un vertice. Si los vertices tienen etiquetas devuelve las etiquetas en lugar del numero de vertice
	 */
	string ObtenerVertices(const Grafo* grafo);

	/*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Devuelve las aristas en formato de etiquetas.
	 * El formato de etiquetas para un grafo no dirigido es el siguiente: 1-4 2-3 0-1
	 * Donde nos dice que el conjunto E del grafo es: {(1,4), (2,3), (0,1)}
	 * El formato de etiquetas para un grafo dirigido es el siguiente: 1-4 2-3 4-1
	 * Donde nos dice que el conjunto E del grafo es: {(1,4), (2,3), (0,1), (4,1)}
	 *
	 * Vemos que en ambos casos son las adyacencias separadas por espacio.
	 * Para el caso de los grafos no dirigidos no hay que duplicar las relaciones conmutativas.
	 * Si los vertices tienen etiquetas devuelve las etiquetas en lugar del numero de vertice
	 */
	string ObtenerAristas(const Grafo* grafo);

	/*
	 * Precondiciones: @grafo1 y @grafo2 son instancias validas creadas con alguna de las primitivas creacionales
	 * Postcondiciones: Devuelve una instancia nueva de Grafo que es la union de conjuntos de los vertices y aristas de @grafo1 y @grafo2
	 */
	Grafo* ObtenerUnion(const Grafo* grafo1, const Grafo* grafo2);

	/*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Devuelve una instancia nueva del Grafo que es el complemento de @grafo
	 */
	Grafo* ObtenerGrafoComplementario(const Grafo* grafo);

	/*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Si es @grafo es un grafo no dirigido devuelve el grado del vertice @vertice. Si es un grafo dirigido, devuelve el grado de salida de @vertice
	 */
	int ObtenerGrado(const Grafo* grafo, int vertice);

	/*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Asocia la etiqueta @etiqueta al vertive @vertice de @grafo. Si ya tenia etiqueta la sobreescribe por @etiqueta
	 */
	void AgregarEtiqueta(Grafo* grafo, int vertice, string etiqueta);

	/*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Devuelve true si @grafo es un grafo completo. Caso contrario devuelve false
	 */
	bool EsCompleto(const Grafo* grafo);

	/*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Devuelve la sucesion grafica de @grafo separados por coma
	 */
	string ObtenerSucesionGrafica(const Grafo* grafo);

	/*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Devuelve la cantidad de vertices de @grafo
	 */
	int ObtenerCantidadVertices(const Grafo* grafo);

	/*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Cambia el nombre que tiene @grafo por @nombre
	 */
	void CambiarNombre(Grafo* grafo, string nombre);

	/*
	 * Precondiciones: @grafo es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Libera todos los recursos asociados a @grafo
	 */
	void DestruirGrafo(Grafo* grafo);

	/*
	* Precondiciones:
	* - @nombre es un nombre válido para el grafo.
	* - @tipo es un valor de TipoGrafo (DIRIGIDO o NODIRIGIDO).
	* - @cantidadVertices es mayor o igual a cero.
	*
	* Postcondiciones:
	* - Devuelve un puntero a un nuevo Grafo inicializado con el nombre, tipo, identificador único, y lista de adyacencia de tamaño @cantidadVertices.
	*/
	Grafo* InicializarGrafo(const string& nombre, TipoGrafo tipo, int cantidadVertices);
}

#endif
