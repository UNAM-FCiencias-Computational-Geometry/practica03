/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 * Description:
 * Funciones básicas para implementar el particionamiento de un 
 * poligono simple a piezas monotonas.
 * 
 */

#ifndef MAKE_MONOTONE_H_
#define MAKE_MONOTONE_H_

#include "dcel/dcel.h"

/**
 * Tipos que nos ayudan a clasificar los tipos de vértices que contiene
 * poligono simple.
 */
typedef enum {START = 1, SPLIT, END, MERGE, REGULAR} vertex_type;

/** Calcula el tipo de vertice que es p. */
vertex_type calculate_vertex_type(vertex* p);

/** 
 * Implementación del algoritmo para particionar un poligono 
 * en piezas monotonas. 
 */
void make_monotone(dcel* dcel);

/** 
 * Funciones para manejar los distintos tipos de vértices que puede
 * tener un poligono simple.
 */
void handle_start_vertex(vertex* vi, rb_tree* tree, dcel* dcel);
void handle_merge_vertex(vertex* vi, rb_tree* tree, dcel* dcel);
void handle_regular_vertex(vertex* vi, rb_tree* tree, dcel* dcel);
void handle_split_vertex(vertex* vi, rb_tree* tree, dcel* dcel);
void handle_end_vertex(vertex* vi, rb_tree* tree, dcel* dcel);

/**
 * Funcion para hacer una diagonal entre dos vertices del poligono simple.
 * Se le tiene que pasar el árbol de búsqueda que mantiene el estado de la DCEL
 * por que se tiene que borrar las aristas de la nueva cara que genera
 * la diagonal.
 */
void connect_diagonal(vertex* first, vertex* last, dcel* dcel, rb_tree* tree);

#endif
