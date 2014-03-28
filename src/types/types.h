/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 * Description:
 * Contiene los tipos que puede representar una lista. Y funciones
 * para Ruby-Processing.
 */

#ifndef TYPES_H_
#define TYPES_H_

/** En C no existen booleanos como tal, pero toma como 0 falso y verdadero 1.*/
#define FALSE 0
#define TRUE 1

/**
 * Tipos que nos ayudan a identificar que contiene un arbol rojo negro o
 * una lista doblemente ligada.
 */
typedef enum {POINT = 1, HALF_EDGE, FACE} item_type;

#endif
