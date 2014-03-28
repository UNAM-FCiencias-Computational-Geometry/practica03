/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 * Description:
 * Implementación de la DCEL, con la diferencia de que en lugar de usar una 
 * lista doublemente ligada para las caras, otra para los vertices y otro más
 * para las aristas, se utilizan arboles rojo negro.
 * 
 */

#ifndef DCEL_H_
#define DCEL_H_

#include "red_black_tree/rb_tree.h"

#include "face/face.h"
#include "half_edge/half_edge.h"
#include "points/2d_points.h"

/**
 * Estructura DCEL, para guardar las caras, vertices y aristas
 */
struct dcel {
	/** 
	 * Registro de las caras, vertices y aristas guardadas en arboles 
	 * rojo negros 
	*/
	rb_tree* face;
	rb_tree* vertex;
	rb_tree* half_edge;
};

/** Renombramos la DCEL para usarla de forma más sencilla. */
typedef struct dcel dcel;

/** Funcion para inicializar para alojar la memoria necesaria para la DCEL. */
dcel* init_dcel(void);

/**
 * Funcion para destruir la dcel sin eliminar los elementos dentro de ella.
 * Solo destruye los arboles que utiliza.
*/
void destroy_dcel(dcel* dcel);

/**
 * Inserta una cara a la DCEL, esta funcion maneja por dentro los arboles rojo
 * negro.
 */
void dcel_insert_face(dcel* dcel, face* face);

/**
 * Inserta una arista a la DCEL, esta funcion maneja por dentro los arboles rojo
 * negro.
 */
void dcel_insert_half_edge(dcel* dcel, half_edge* half_edge);

/**
 * Inserta un vertice a la DCEL, esta funcion maneja por dentro los arboles rojo
 * negro.
 */
void dcel_insert_vertex(dcel* dcel, vertex* vertex);


/**
 * Funciones que debes de implementar.
 *
 * incident_he_to_v() debe regresar una lista de half_edge que tengan como origen * el vertice dado.
 */
list* incident_he_to_v(vertex* vertex);

/**
 * incident_f_to_f() debe regresar una lista de face que tengan como origen la
 * cara que se le pase. Puedes utilizar la funcion rb_tree_to_list(), 
 * recuerda que el arbol rojo negro te puede ayudar para saber si una cara ya
 * esta dentro del del arbol rojo negro.
 */
list* incident_f_to_f(face* face);

/**
 * incident_he_to_f() debe de regresa todos las aristas que son incidentes a 
 * la cara dada, recuerda que debes iterar la lista inner_components.
 */
list* incident_he_to_f(face* face);

#endif
