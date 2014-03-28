/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 * 
 * Description:
 * Representación de una cara del DCEL
 */

#ifndef FACE_H_
#define FACE_H_

#include "half_edge/half_edge.h"

/**
 * Estructura para representar las caras que contiene una DCEL.
 */

struct face {

	/**
	 * Nombre que tendra la cara dentro de la DCEL, para esta práctica
	 * el nombre debe de ser unico.
	 */
	const char* name;
	
	/**
	 * outer_component tiene la direccion de memoria a algun half_edge que forme
	 * parte del recubrimiento exterior de la cara.
	 */
	struct half_edge* outer_component;

	/**
	   inner_compontens es una lista de half_edges que pertenecen a diferentes
	   recubrimiento intenteriores, si no tiene nada, entonces es nulo.
	 */
	void* inner_components;
};

/** Renombramos la estructura anterior para un uso mas sencillo. */
typedef struct face face;

/**
 * Aloja la memoria para una cara de la lista, y se le pasan el componente 
 * exterior y los componentes interiores.
 */
face* init_face(const char* name, half_edge* outer_component,
				void* list_of_inner_components);

/** Libera la memoria de la cara, sin destruir los half_edge. */
void destroy_face(face* face);

/** Funciones de comparacion de las caras, sirve para el arbol rojo negro. */
int face_greater_than(face* a, face* b);
int face_less_than(face* a, face* b);
int face_equals(face* a, face* b);

/** Funcion que hace un casting de una cara, sirve para los tests. */
face* cast_face(void* face);

#endif

