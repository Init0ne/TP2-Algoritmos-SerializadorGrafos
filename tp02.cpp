#include "GeneradorGrafos.h"
#include "Escritor.h"
#include "Serializador.h"

using URGGrafo::Grafo;
using URGGrafo::ObtenerCantidadVertices;
using URGGrafo::ObtenerSucesionGrafica;
using URGGrafo::ObtenerGrafoComplementario;
using URGGrafo::ObtenerUnion;
using URGGrafo::DestruirGrafo;
using URGGrafo::CambiarNombre;
using namespace URGGeneradorGrafos;
using namespace URGEscritor;
using namespace URGSerializador;

void EjecutarCaso1(Escritor* consola);
Grafo* CrearGrafoCaso1();

void EjecutarCaso2(Escritor* consola);
void PersistirGrafoCaso2(Grafo* grafo);

int main() {
	Escritor* consola = CrearEscritorConsola();
	EjecutarCaso1(consola);
	EjecutarCaso2(consola);
	Grafo* grafo = CrearGrafoCaso1();
	PersistirGrafoCaso2(grafo);
	Destruir(consola);
	return 0;
}

Grafo* CrearGrafoCaso1()
{
	Grafo* grafoPetersen = ObtenerGrafoPetersen();
	Grafo* grafoRandom = ObtenerGrafoRandom(ObtenerCantidadVertices(grafoPetersen), 10);
	Grafo* grafoComplementarioRandom = ObtenerGrafoComplementario(grafoRandom);
	Grafo* grafoCaso1 = ObtenerUnion(grafoPetersen, grafoComplementarioRandom);
	CambiarNombre(grafoCaso1, "URG_Grafo_Caso_01");
	DestruirGrafo(grafoPetersen);
	DestruirGrafo(grafoRandom);
	DestruirGrafo(grafoComplementarioRandom);
	return grafoCaso1;
}

void EjecutarCaso1(Escritor* consola) {
	Escribir(consola, "#Comienzo Caso 1");
	Grafo* grafoCaso1 = CrearGrafoCaso1();
	Serializador* serializador = CrearSerializador(consola);
	Escribir(consola, "Sucesion Grafica: " + ObtenerSucesionGrafica(grafoCaso1));
	Serializar(serializador, grafoCaso1);
	DestruirGrafo(grafoCaso1);
	DestruirSerializador(serializador);
	Escribir(consola, "#Fin Caso 1");
}

void PersistirGrafoCaso2(Grafo* grafoCaso2) {
	Serializador* serializador = CrearSerializador(ObtenerNombre(grafoCaso2));
	Serializar(serializador, grafoCaso2);
	DestruirSerializador(serializador);
	DestruirGrafo(grafoCaso2);
}

void EjecutarCaso2(Escritor* consola) {
	Escribir(consola, "#Comienzo Caso 2");
	PersistirGrafoCaso2(ObtenerGrafoProvinciasArgentina());
	PersistirGrafoCaso2(ObtenerGrafoRandom(30, 22));
	PersistirGrafoCaso2(ObtenerGrafoCompleto(30));
	Escribir(consola, "#Fin Caso 2");
}
