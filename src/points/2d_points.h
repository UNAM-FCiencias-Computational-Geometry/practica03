/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 * Description:
 * Contiene la estructura junto con sus funciones que hacen referencia hacia 
 * puntos en 2D.
 */

#ifndef TWOD_POINTS_H_
#define TWOD_POINTS_H_

#define LEFT 0
#define RIGHT 1

struct point {
	double x;
	double y;

	/**
	 * Apuntador hacia el half_edge que es incidente. Se ocupa para 
	 * la estructura DCEL;
	 */
	void* incident_edge;
	
	/**
	 * Nombre que le damos al vertice, sirve para probar las funciones
	 * que deben implementar.
	 */
	const char* name;

	/**
	 * Si es un punto que ayuda a representar un segmentos, entonces
	 * el apuntador de intersecion es nulo y el apuntador de half_edge
	 * hace referencia al segmento que ayuda a representar.
	 * Si el punto representa la interseccion de segmentos, entonces
	 * half_edge y intersection son los segmentos que contiene al punto.
	 *
	 * NOTA: Sus apuntadores son void* por que crearia conflictos al
	 * momento de compilar.
	 */
	void* half_edge;
	void* intersection;
};

/**
 * Se renombra la estructura points a vertex para su uso mas natural en la
 * DCEL.
 */
typedef struct point vertex;

/** Inicializa un punto con coordenadas por defecto 0 */
vertex* init_point_empty(void);

/** Inicializa un punto con las coordenadas que se le pasan */
vertex* init_point(double x, double y, const char* name);

/** Libera la memoria que guarda la punto */
void destroy_point(vertex* point);

/** Crea una copia del punto que se le pase */
vertex* create_copy_point(vertex* point);

/**
 * Calcula el siguiente determinante:
 *          | 1 a->x a->y |
 * det(O) = | 1 b->x b->y |
 *	        | 1 c->x c->y |
 *
 * Si det(O) < 0 => Vuelta a la derecha.
 * Si det(O) > 0 => Vuelta a la izquierda.
 */
int curve_orientation(vertex* a, vertex* b, vertex* c);

/** Funciones de comparacion de las puntos, sirve para el arbol rojo negro. */
int point_greater_than(vertex *a, vertex* b);
int point_less_than(vertex* a, vertex* b);
int point_equals(vertex* a, vertex* b);

/** Funcion que hace un casting del punto, sirve para los tests. */
vertex* cast_point(void* a);

/** Imprime el valor de un vertice */
void print_vertex(vertex* v);
#endif
