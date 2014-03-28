/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 * 
 */

#include "half_edge/half_edge.h"

#include <stdio.h>
#include <stdlib.h>


half_edge* init_half_edge(vertex* first, vertex* last, const char* name)
{
	struct half_edge* edge;
	edge = (struct half_edge*) malloc(sizeof(struct half_edge));
	
	if (edge == NULL) {
		printf("Ya no hay memoria disponible: init_half_edge()\n");
		exit(EXIT_FAILURE);
	}
	
	first->incident_edge = edge;

	edge->first = first;
	edge->last = last;
	edge->helper = NULL;

	first->half_edge = edge;
	last->half_edge = edge;

	edge->twin = NULL;
	edge->next = NULL;
	edge->prev = NULL;

	edge->name = name;

	edge->incident_face = NULL;
	
	return edge;
}

void destroy_half_edge(half_edge* half_edge)
{
	free(half_edge);
}

void destroy_half_edge_with_points(half_edge* half_edge)
{
	
	
	destroy_point(half_edge->first);
	destroy_point(half_edge->last);

	free(half_edge);
}

vertex* he_intersection(half_edge* a, half_edge* b)
{
	double x1, y1, x2, y2, x3, y3, x4, y4;
	
	x1 = a->first->x;
	y1 = a->first->y;

	x2 = a->last->x;
	y2 = a->last->y;
	
	x3 = b->first->x;
	y3 = b->first->y;

	x4 = b->last->x;
	y4 = b->last->y;

	double det;
	det = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
	
	if (det == 0.0) 
		return NULL;

	double xi, yi;
	xi = ((x3-x4)*(x1*y2-y1*x2)-(x1-x2)*(x3*y4-y3*x4))/det;
	yi = ((y3-y4)*(x1*y2-y1*x2)-(y1-y2)*(x3*y4-y3*x4))/det;

	
	if (xi < MIN(x1,x2) || xi > MAX(x1,x2))
		return NULL;

	if (xi < MIN(x3,x4) || xi > MAX(x3,x4))
		return NULL;

	struct point* point;
	point = init_point(xi,yi,"");
	point->half_edge = a;
	point->intersection = b;

	return point;
	
}

half_edge* copy_half_edge(half_edge* half_edge)
{
	struct half_edge* tmp;
	tmp = init_half_edge(create_copy_point(half_edge->first),
						 create_copy_point(half_edge->last), half_edge->name);

	tmp->twin = half_edge->twin;
	tmp->next = half_edge->next;
	tmp->prev = half_edge->prev;
	
	tmp->incident_face = half_edge->incident_face;

	return tmp;
}

int half_edge_greater_than(half_edge* a, half_edge* b)
{
	return a->first->x > b->first->x;
}

int half_edge_less_than(half_edge* a, half_edge* b)
{
	return a->first->x < b->first->x;
}

int half_edge_equals(half_edge* a, half_edge* b)
{
	double x1, y1, x2, y2, x3, y3, x4, y4;
	x1 = a->first->x;
	y1 = a->first->y;

	x2 = a->last->x;
	y2 = a->last->y;

	x3 = b->first->x;
	y3 = b->first->y;

	x4 = b->last->x;
	y4 = b->last->y;

	return ((x1 == x3) && (y1 == y3) && (x2 == x4) && (y2 == y4));
}

half_edge* cast_half_edge(void* half_edge)
{
	return (struct half_edge*) half_edge;
}
