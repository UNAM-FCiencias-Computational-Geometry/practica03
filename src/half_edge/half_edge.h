/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 * Description:
 * Dado que un segmento no tiene direcion, le llamaremos half_edge
 * a los segmentos con direccion que se representan.
 * 
 */

#ifndef HALF_EDGE_H_
#define HALF_EDGE_H_

#include "points/2d_points.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

/**
 * Estructura basica para representar segmentos con direccion.
 * Tiene un punto incian first y un punto final last.
 */
struct half_edge {
	/** Vertice de inicio */
	vertex* first;
	/** Vertice final */
	vertex* last;
	
	/** Vertece helper para hacer un poligono monotono. */
	vertex* helper;
	
	/** Arista gemela. */
	struct half_edge* twin;
	/** Arista siguiente. */
	struct half_edge* next;
	/** Arista previa*/
	struct half_edge* prev;
	
	/** 
	 * Cara incidente a la arista, es de tipo void* por problemas
	 * de dependencias
	 */
	void* incident_face;

	/** 
	 * Tiene un nombre para identificar que arista es, sirve para hacer sus
	 * pruebas.
	 */
	const char* name;
};

/** Renombramos la estructura anterior para un uso más sencillo. */
typedef struct half_edge half_edge;

/**
 * Inicializa los segmentos pasandole la direccion de los puntos que lo 
 * describen.
 */
half_edge* init_half_edge(vertex* first, vertex* last, const char* name);

/** Destruye el segmento liberando su memoria. */
void destroy_half_edge(half_edge* half_edge);

/** Destruye el segmento liberando su memoria y la de los puntos que contiene. */
void destroy_half_edge_with_points(half_edge* half_edge);

/** Crea una copia del segmento y sus puntos. */
half_edge* copy_half_edge(half_edge* half_edge);

/** 
 * Calcula la intersecion de dos segmentos, si no existe regresa nulo, y si
 * existe regresa el punto que esta en la intersecion de los dos segmentos.
 */
vertex* he_intersection(half_edge* a,half_edge* b);

/** Funciones de comparacion de las aristas, sirve para el arbol rojo negro. */
int half_edge_greater_than(half_edge* a, half_edge* b);
int half_edge_less_than(half_edge* a, half_edge* b);
int half_edge_equals(half_edge* a, half_edge* b);

/** Funcion que hace un casting de una arista, sirve para los tests. */
half_edge* cast_half_edge(void* half_edge);
#endif
