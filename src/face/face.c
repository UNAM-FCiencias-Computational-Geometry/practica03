/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 * 
 */

#include "face/face.h"
#include "double_linked_list/double_linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

face* init_face(const char* name, half_edge* outer_component, 
				void* list_of_inner_components)
{
	struct face* face;
	face = (struct face*) malloc(sizeof(struct face));

	face->name = name;
	face->outer_component = outer_component;
	
	if (list_of_inner_components == NULL) {
		face->inner_components = NULL;
	} else {
		
		struct list_item* tmp;
		tmp = ((list*) list_of_inner_components)->head;
		
		if (tmp == NULL) {
			face->inner_components = NULL;
			return face;
		} else {
			face->inner_components = init_double_linked_list(HALF_EDGE);
		}

		while (tmp != NULL) {
			push_back(face->inner_components,tmp->element);
			tmp =  tmp->right;
		}
		
	}
	
	return face;
}


void destroy_face(face* face)
{
	if (face->inner_components != NULL) 
		destroy_double_linked_list(face->inner_components);
	
	free(face);
}

int face_greater_than(face* a, face* b)
{
	int comparation = strcmp(a->name, b->name);

	return comparation > 0;
}

int face_less_than(face* a, face* b)
{
	int comparation = strcmp(a->name, b->name);
	
	return comparation < 0;		
}

int face_equals(face* a, face* b) 
{
	int comparation = strcmp(a->name, b->name);
	
	return comparation == 0;
}


face* cast_face(void* face)
{
	return (struct face*) face;
}
