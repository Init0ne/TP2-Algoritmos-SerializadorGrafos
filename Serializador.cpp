#include "Serializador.h"
#include "Escritor.h"

struct Serializador{
    Escritor* escritor; //Puntero al escritor que lo serializa en el archivo
    const Grafo* grafo; //Puntero al grafo que queres serializar
};

/*
	 * Precondicion: @escritor es una instancia valida
	 * Postcondicion: Crear un serializador de grafos que serializara el grafo en @escritor
	 */
Serializador* CrearSerializador(Escritor* escritor){
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
Serializador* CrearSerializador(string nombreGrafo){
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
void Serializar(Serializador* serializador, const Grafo* grafo){

}

/*
	 * Precondiciones: @serializador es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondiciones: Libera todos los recursos asociados a @serializador
	 */
void DestruirSerializador(Serializador* serializador){

}