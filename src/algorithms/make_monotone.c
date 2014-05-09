#include "algorithms/make_monotone.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <string.h>

#define STR_LENGTH 7

void rand_str(char *dest, int length) {
    char charset[] = "0123456789"
                     "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while (length-- > 0) {
		rand();
        int index = (double) rand() / RAND_MAX * (sizeof charset - 1);
        *dest++ = charset[index];
    }
    *dest = '\0';
}

void make_monotone(dcel* dcel)
{
	/** Genera random strings */
	srand(time(NULL));

	/** Aqui debe comienzar tu algoritmo. */
	
	list* l;
	struct list_item* tmp;
	rb_tree* rb_tree;
	
	l = rb_tree_to_priority_queue(dcel->vertex);
	tmp = l->head;
	rb_tree = init_rb_tree(HALF_EDGE);
	
	while(tmp != NULL){
		switch(calculate_vertex_type(tmp->element)){
			case START:
				handle_start_vertex(tmp->element, rb_tree, dcel);
				break;
			case END:
				handle_end_vertex(tmp->element, rb_tree, dcel);
				break;
			case SPLIT:
				handle_split_vertex(tmp->element, rb_tree, dcel);
				break;
			case MERGE:
				handle_merge_vertex(tmp->element, rb_tree, dcel);
				break;
			case REGULAR:
				handle_regular_vertex(tmp->element, rb_tree, dcel);
				break;	
		}		
		tmp = tmp->right;
	}
	
}

vertex_type calculate_vertex_type(vertex* p) 
{
	if (p == NULL) {
		printf("calculate_vertex_type(): p es nulo\n");
		exit(EXIT_FAILURE);
		//return NULL;
	}

	vertex *m, *q;
	half_edge* incident_edge;

	incident_edge = p->incident_edge;

	/** Si el half_edge incidente es del exterior, me cambio al interior. */
	if ( strcmp(((face*) incident_edge->incident_face)->name, "face 1\0") == 0) {
		p->incident_edge = incident_edge->twin->next;
		incident_edge = p->incident_edge;
	}
	
	
	m = incident_edge->last;
	q = incident_edge->prev->first;

	int angule = curve_orientation(m,p,q);

	/** Si es una vuelta a la izquierda, entonces el angulo es mayor que PI. */
	/** Si es una vuelta a la derecha, entonces el angulo es menor que PI. */
	
	if (angule == RIGHT && point_less_than(q,p) && point_less_than(m,p)) {
		
		return START;
		
	} else if (angule == LEFT && point_less_than(q,p) && point_less_than(m,p)) {
		
		return SPLIT;

	} else if (angule == RIGHT && point_less_than(p,q) && point_less_than(p,m)) {
		
		return END;

	} else if (angule == LEFT && point_less_than(p,q) && point_less_than(p,m)) {

		return MERGE;

	} else {

		return REGULAR;
		
	}
}

void handle_start_vertex(vertex* vi, rb_tree* tree, dcel* dcel) 
{
	half_edge* e = vi->incident_edge;
	rb_insert(tree, e);
	e->helper = vi;
}

void handle_merge_vertex(vertex* vi, rb_tree* tree, dcel* dcel) 
{
	half_edge *ei_1, *ej;
	
	ei_1 = cast_half_edge((vi->incident_edge))->prev;
	if(ei_1->helper != NULL){
		if(calculate_vertex_type(ei_1->helper) == MERGE)
			connect_diagonal(vi, ei_1->helper, dcel, tree);
	}
	rb_delete(tree, ei_1);
	
	ej = rb_search_left_he(tree,vi);
	
	if(calculate_vertex_type(ej->helper) == MERGE)
		connect_diagonal(vi, ej->helper, dcel, tree);
	
	ej->helper = vi;	
}

void handle_regular_vertex(vertex* vi, rb_tree* tree, dcel* dcel)
{
	vertex *m, *q;
	half_edge *ei, *ei_1, *ej;

	ei = vi->incident_edge;
	ei_1 = cast_half_edge((vi->incident_edge))->prev;
	
	m = ei->last;
	q = ei->prev->first;
	
	if(curve_orientation(m, vi, q)){
		if(calculate_vertex_type(ei_1->helper) == MERGE){
			connect_diagonal(vi, ei_1->helper, dcel, tree);
			rb_delete(tree,ei_1);
			rb_insert(tree, ei);
			ei->helper  = vi;
		}
	}else{
		ej = rb_search_left_he(tree,vi);
		if(calculate_vertex_type(ej->helper) == MERGE)
			connect_diagonal(vi, ej->helper, dcel, tree);
		ej->helper = vi;
	}
	
}

void handle_split_vertex(vertex* vi, rb_tree* tree, dcel* dcel)
{
	half_edge *ei, *ej;
	ei = vi->incident_edge;
	ej = rb_search_left_he(tree, vi);
	
	connect_diagonal(vi, ej->helper, dcel, tree);
	ej->helper = vi;
	ei->helper = vi;rb_insert(tree, ei);
	
}

void handle_end_vertex(vertex* vi, rb_tree* tree, dcel* dcel)
{
	half_edge* ei_1 = cast_half_edge((vi->incident_edge))->prev;
	
	if(calculate_vertex_type(ei_1->helper) == MERGE)
		connect_diagonal(vi, ei_1->helper, dcel, tree);
	
	rb_delete(tree, ei_1);
}

void connect_diagonal(vertex* first, vertex* last, dcel* dcel, rb_tree* tree) 
{	
	
	if (first->x > last->x) {
		vertex* aux = last;
		last = first;
		first = aux;
	}

	char *he_name_1, *he_name_2, *face_name;
	he_name_1 = (char *) malloc(sizeof(char)*STR_LENGTH);
	he_name_2 = (char *) malloc(sizeof(char)*STR_LENGTH);
	face_name = (char *) malloc(sizeof(char)*STR_LENGTH);
	rand_str(he_name_1, STR_LENGTH);
	rand_str(he_name_2, STR_LENGTH);
	rand_str(face_name, STR_LENGTH);

	half_edge* original_incident_edge_1 = first->incident_edge;
	half_edge* original_incident_edge_2 = last->incident_edge;

	/** Creo los nuevos half_edges. */
	half_edge *tmp1, *tmp2;
	tmp1 = init_half_edge(first, last, (const char*) he_name_1);
	tmp2 = init_half_edge(last, first, (const char*) he_name_2);

	/** Dejo los half_edges incidentes originales. */
	first->incident_edge = original_incident_edge_1;
	last->incident_edge = original_incident_edge_2;

	/** Les asigno sus gemelos. */
	tmp1->twin = tmp2;
	tmp2->twin = tmp1;
	
	/** Les asigno sus half_edge previos. */
	tmp1->prev = ((half_edge*) first->incident_edge)->prev;
	tmp2->prev = ((half_edge*) last->incident_edge)->prev;

	/** Les asigno sus half_edge siguientes. */
	tmp1->next = last->incident_edge;
	tmp2->next = first->incident_edge;

	/** Les asigno sus caras incidentes a los nuevos half_edge. */
	list* list = init_double_linked_list(HALF_EDGE);
	push_back(list, tmp1);
	
	face* face = init_face(face_name,NULL,list);

	tmp1->incident_face = face;
	tmp2->incident_face = ((half_edge*) first->incident_edge)->incident_face;

	/** Compongo los inner_components de la cara original. */
	struct face* original_face;
	original_face = tmp2->incident_face;

	struct double_linked_list* original_list = face->inner_components;
	pop_front(original_list);
	push_front(original_list, tmp2);
	
	original_face->outer_component = tmp2;


	/** Compongo los prev y next de los 4 half_edges originales. */
	((half_edge*) first->incident_edge)->prev->next = tmp1;
	((half_edge*) first->incident_edge)->prev = tmp2;

	((half_edge*) last->incident_edge)->prev->next = tmp2;
	((half_edge*) last->incident_edge)->prev = tmp1;

	/** Actualizo los incident_face de los half_edge del lado de tmp1. */
	half_edge* tmp;
	for (tmp = tmp1->next; tmp != tmp1; tmp = tmp->next) {
		
		rb_delete(tree, tmp);
		tmp->incident_face = face;
	}

	rb_insert(dcel->face, face);
	rb_insert(dcel->half_edge, tmp1);
	rb_insert(dcel->half_edge, tmp2);
	
	return;
	
}
 
