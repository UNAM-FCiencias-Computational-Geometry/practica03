/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 */

#include "red_black_tree/rb_tree.h"

#include "face/face.h"
#include "half_edge/half_edge.h"
#include "points/2d_points.h"

#include "types/types.h"

#include <stdio.h>
#include <stdlib.h>

struct rb_node sentinel = {NULL,NULL,NULL,BLACK,NULL,NULL,NULL};

/**  Verifica si el arbol que se le pase esta vacio o no.*/
int empty_rb_tree(struct rb_tree* tree)
{
	if (tree == NULL)
		return tree == NULL;

	return tree->root == &sentinel;
}

/**
 * Toma el nodo tmp1 y le aplica una rotacion hacia la izquierda.
 *
 *     tmp1                   tmp2
 *     / \                    /	\
 *	  *  tmp2        -->    tmp1 *
 *       / \                / \
 *      c   *              *   c
 */
void left_rotate(struct rb_tree* tree, struct rb_node* node)
{
	struct rb_node *tmp1, *tmp2;
 	tmp1 = node;
 	tmp2 = node->right;

 	tmp1->right = tmp2->left;
	
	if (tmp2->left != &sentinel) 
 		tmp2->left->parent = tmp1;

	tmp2->parent = tmp1->parent;

	if (tmp1->parent == &sentinel) {
		tree->root = tmp2;
	} else if (tmp1 == tmp1->parent->left) {
	 	tmp1->parent->left = tmp2;
	} else {
	 	tmp1->parent->right = tmp2;
	}

	tmp2->left = tmp1;
	tmp1->parent = tmp2;
}

/** Toma el nodo tmp1 y le aplica una rotacion hacia la derecha .
 *
 *     tmp1             tmp2
 *     / \              / \
 *   tmp2 *    -->     * tmp1
 *   / \                  /	\
 *	*   c                c   *
 */
void right_rotate(struct rb_tree* tree, struct rb_node* node)
{
	struct rb_node *tmp1, *tmp2;
	tmp1 = node;
	tmp2 = node->left;

	tmp1->left = tmp2->right;

	if (tmp2->right != &sentinel)
	 tmp2->right->parent = tmp1;

	tmp2->parent = tmp1->parent;

	if (tmp1->parent == &sentinel) {
		tree->root = tmp2;
	} else if(tmp1 == tmp1->parent->left) {
	 	tmp1->parent->left = tmp2;
	} else {
	 	tmp1->parent->right = tmp2;
	}
	
	tmp2->right = tmp1;
	tmp1->parent = tmp2;
}

/**
 * Compone el arbol una vez que se inserta un nodo como hoja y descompone
 * las propiedades del arbol.
 */
void rb_insert_fixup(rb_tree* tree, rb_node* node)
{

	struct rb_node *tmp1, *tmp2;
	tmp1 = node;

	while (tmp1->parent->color == RED) {
		/** El padre de node es hijo izquierdo. */
		if (tmp1->parent == tmp1->parent->parent->left) {
			
			/** tmp es el tío derecho del padre de node*/
			tmp2 = tmp1->parent->parent->right;
			
			/** Caso 1: tmp tiene color rojo. */
			if (tmp2->color == RED) {
				
				tmp1->parent->color = BLACK;
				tmp2->color = BLACK;
				tmp1->parent->parent->color = RED;
				
				tmp1 = tmp1->parent->parent;
				
			} else {
				/** Caso 2: tmp tiene color negro y node es hijo derecho.
				 *  convertimos el caso 2 en el caso 3.
				 */
				if ( tmp1 == tmp1->parent->right) {
					tmp1 = tmp1->parent;
					left_rotate(tree, tmp1);
				}

				/** Caso 3: tmp tiene color negro y node es hujo izquierdo.*/
				tmp1->parent->color = BLACK;
				tmp1->parent->parent->color = RED;

				right_rotate(tree,tmp1->parent->parent);
			}

		} else {
			/** tmp es el tío izquierdo del padre de node.*/
			tmp2 = tmp1->parent->parent->left;

			/** Caso 1: tmp tiene color rojo*/
			if (tmp2->color == RED) {
				
				tmp1->parent->color = BLACK;
				tmp2->color = BLACK;
				tmp1->parent->parent->color = RED;
				
				tmp1 = tmp1->parent->parent;
				
			} else {
				/** Caso 2: tmp tiene color negro y node es hijo izquierdo.
				 *  convertimos el caso 2 en el caso 3.
				 */
				if ( tmp1 == tmp1->parent->left) {
					tmp1 = tmp1->parent;
					right_rotate(tree, tmp1);
				}

				/** Caso 3: tmp tiene color negro y node es hujo derecho.*/
				tmp1->parent->color = BLACK;
				tmp1->parent->parent->color = RED;

				left_rotate(tree,tmp1->parent->parent);
			}

		}
	}

	tree->root->color = BLACK;
}

/** 
 * Coloca al nodo b como hijo del padre de a y le indica al nodo
 * b que su padre cambio, al nodo a no le dice que su padre ya 
 * no hace referencia
 */
void rb_transplant(struct rb_tree* tree, struct rb_node* a,struct rb_node* b)
{
	if (a->parent == &sentinel) {
		tree->root = b;
	} else if (a == a->parent->left) {
		a->parent->left = b;
	} else {
	 	a->parent->right = b;
	}
	
	b->parent = a->parent;
}


/** Funcion para comparar los nodos del arbol*/
int rb_equals(item_type type, void* a, void* b) 
{
	switch (type) {
	case FACE:
		return face_equals((struct face*)a, (struct face*)b);
		break;

	case HALF_EDGE:
		return half_edge_equals((struct half_edge*) a, (struct half_edge*) b);
		break;
		
	case POINT:
		return point_equals((struct point*) a, (struct point*) b);
		break;
	}

	return FALSE;
}

/** Funcion para comparar los nodos del arbol*/
int rb_less_than(item_type type, void* a, void* b)
{
	switch (type) {
	case FACE:
		return face_less_than((face*) a, (face*) b);
		break;

	case HALF_EDGE:
		return half_edge_less_than((half_edge*) a, (half_edge*) b);
		break;

	case POINT:
		return point_less_than((vertex*) a,(vertex*) b);
		break;

	}
	
	return FALSE;
}

/**
 * Busca un un nodo en el arbol que contenga exactamente el punto que se le paso.
 **/
rb_node* rb_node_search(rb_tree* tree, void* element)
{
	struct rb_node* tmp;
	tmp = tree->root;

	while(tmp != &sentinel) {
		if (rb_equals(tree->type,tmp->element,element)) {
			break;
		} else if(rb_less_than(tree->type, tmp->element ,element)) {
			tmp = tmp->right;
		} else {
			tmp = tmp->left;
		}
	}
	
	if (tmp == &sentinel)
		return NULL;

	return tmp;
}

/**
 * Compone las propiedades del arbol una vez que el nodo que se le paso se
 * borra.
 */
void rb_delete_fixup(struct rb_tree* tree, struct rb_node* node)
{
	struct rb_node *tmp1, *tmp2;
	tmp1 = node;
	
	while ((tmp1 != tree->root) && (tmp1->color == BLACK)) {
		
		if (tmp1 == tmp1->parent->left) {
			tmp2 = tmp1->parent->right;
			
			if (tmp2->color == RED) {
			
				tmp2->color = BLACK;
				tmp1->parent->color = RED;
				
				left_rotate(tree,tmp1->parent);
				tmp2 = tmp1->parent->right;
			}
			
			
			if ((tmp2->left->color == BLACK) && (tmp2->right->color == BLACK)) {
				
				tmp2->color = RED;
				tmp1 = tmp1->parent;
				
			} else {
				if (tmp2->right->color == BLACK) {
					
					tmp2->left->color = BLACK;
					tmp2->color = RED;
					right_rotate(tree,tmp2);
					tmp2 = tmp1->parent->right;					
				}
				
				tmp2->color = tmp1->parent->color;
				tmp1->parent->color = BLACK;
				tmp2->right->color = BLACK;
				
				left_rotate(tree,tmp1->parent);
				tmp1 = tree->root;
			}
		} else {
			tmp2 = tmp1->parent->left;
			
			if (tmp2->color == RED) {
				
				tmp2->color = BLACK;
				tmp1->parent->color = RED;
				
				right_rotate(tree,tmp1->parent);
				tmp2 = tmp1->parent->left;
			}
			
			if ((tmp2->right->color == BLACK) && (tmp2->left->color == BLACK)) {
				
				tmp2->color = RED;
				tmp1 = tmp1->parent;
				
			} else {
				if (tmp2->left->color == BLACK) {
					
					tmp2->right->color = BLACK;
					tmp2->color = RED;
					left_rotate(tree,tmp2);
					tmp2 = tmp1->parent->left;					
				}
				
				tmp2->color = tmp1->parent->color;
				tmp1->parent->color = BLACK;
				tmp2->left->color = BLACK;
				
				right_rotate(tree,tmp1->parent);
				tmp1 = tree->root;
			}
			
		}
	}
	tmp1->color = BLACK;
}

/**
 * Regresa el nodo que tenga el punto con la menor coordenada X o Y.
 */
struct rb_node* rb_min_node(struct rb_tree* tree,struct rb_node* node)
{
	struct rb_node* tmp = node;

	if (tmp == NULL)
		return NULL;

	if (tmp == &sentinel)
		return tmp;

	while(tmp->left != &sentinel)
		tmp = tmp->left;

	return tmp;
}

/**
 * Regresa el nodo que tenga el punto con la mayor coordenada X o Y.
 */
struct rb_node* rb_max_node(struct rb_tree* tree,struct rb_node* node)
{
	struct rb_node* tmp = node;
	
	if (tmp == NULL)
		return NULL;

	if (tmp == &sentinel)
		return tmp;

	while(tmp->right != &sentinel)
		tmp = tmp->right;
	
	return tmp;
}

/**
 * Destruye un elemento dentro del arbol.
 */
void destroy_element(item_type type, void* element)
{
	switch (type) {
	
	case POINT:
		destroy_point((vertex*)element);
		break;
		
	case HALF_EDGE:
		destroy_half_edge((half_edge*) element);
		break;
		
	case FACE:
		destroy_face((face*) element);
		break;
	}
}

int is_left_son(rb_tree* tree, rb_node* node) 
{
	if (node->parent == &sentinel) {
		return TRUE;
	}

	return node->parent->left == node;
	
}

struct rb_tree* init_rb_tree(item_type type)
{
	struct rb_tree* tree;
	tree = (struct rb_tree*) malloc(sizeof(struct rb_tree));

	if (tree == NULL) {
		printf("Ya no hay memoria disponible: init_rb_tree()\n");
		exit(EXIT_FAILURE);
	}
	
	tree->root = &sentinel;
	tree->type = type;
	tree->size = 0;
	
	tree->min = tree->max = &sentinel;

	return tree;
}

void destroy_rb_tree(struct rb_tree* tree)
{
	if (tree == NULL)
		return;
	
	while (!empty_rb_tree(tree))
		rb_delete(tree,rb_min(tree));
	
	free(tree);
}

void destroy_rb_tree_with_elements(rb_tree* tree)
{
	if (tree == NULL)
		return;

	while(!empty_rb_tree(tree)) {
		destroy_element(tree->type,rb_delete(tree,rb_min(tree)));
		
	}

	free(tree);
}

struct rb_node* init_rb_node(){
	struct rb_node* node;
	node = (struct rb_node*) malloc(sizeof(struct rb_node));
	
      	if (node == NULL) {
		printf("Ya no hay memoria disponible: init_rb_node()\n");
		exit(EXIT_FAILURE);
	}

	node->left = node->right = node->parent = &sentinel;
	node->color = RED;
	
	node->prev = node->next = &sentinel;

	node->element = NULL;

	return node;
}

void destroy_rb_node(rb_tree* tree, struct rb_node* node)
{
	if (node != NULL && node != &sentinel)
		free(node);
}

void rb_insert(struct rb_tree* tree, void* element)
{	
	struct rb_node *tmp1, *tmp2;
	tmp1 = tree->root;
	tmp2 = &sentinel;

	while (tmp1 != &sentinel) {
		tmp2 = tmp1;	   
		
		if (rb_less_than(tree->type, element, tmp1->element))
			tmp1 = tmp1->left;
		else
			tmp1 = tmp1->right;
	}

	struct rb_node* node;
	node = init_rb_node();
	
	node->parent = tmp2;
	node->element = element;

	if (tmp2 == &sentinel) {
		tree->root = node;
	} else if (rb_less_than(tree->type, element, tmp2->element)) {
		tmp2->left = node;
	} else {
		tmp2->right = node;
	}	

	rb_insert_fixup(tree,node);	
	tree->size += 1;

	/** Mantengo los apuntadores prev y next de forma consistente. */
	if (tree->size == 1) {
		tree->min = tree->max = node;		
		return;
	}

	if (rb_less_than(tree->type,node->element, tree->min->element)) {
		node->next = tree->min;
		tree->min->prev = node;

		tree->min = node;
				
		return;
	}

	if (rb_less_than(tree->type, tree->max->element, node->element) ||
		rb_equals(tree->type, node->element, tree->max->element)) {

		node->prev = tree->max;
		tree->max->next = node;

		tree->max = node;

		return;
	}

	rb_node *pre, *suc;
	suc = &sentinel;
	
	pre = rb_max_node(tree,node->left);
	if (pre != &sentinel) {
		
		suc = pre->next;

		pre->next = node;
		node->prev = pre;
	} else {
		pre = node;
		while (is_left_son(tree,pre)) {
			pre = pre->parent;
		}
		pre = pre->parent;

		suc = pre->next;

		pre->next = node;
		node->prev = pre;
	}

	suc->prev = node;
	node->next = suc;

	return;
}

void* rb_search(struct rb_tree* tree, void* element)
{
	if (tree == NULL)
		return NULL; 

	struct rb_node* tmp = rb_node_search(tree,element);

	if (tmp == NULL || tmp == &sentinel)
		return NULL;
	else
		return tmp->element;
}

void* rb_delete(rb_tree* tree, void* element)
{
	struct rb_node *tmp1, *tmp2, *tmp3;
	tmp1 = rb_node_search(tree,element);
		
	if (tmp1 == NULL || tmp1 == &sentinel)
		return NULL;
	
	void* original_element = tmp1->element;
	
	if (tree->size == 1) {
		tree->min = tree->max = &sentinel;
	} else {
		if ((tree->min == tmp1) || (tree->max == tmp1)) {
			if (tree->min == tmp1) {
				tree->min = tmp1->next;
				tmp1->next->prev = &sentinel;
			}
			if (tree->max == tmp1) {				
				tree->max = tmp1->prev;
				tmp1->prev->next = &sentinel;
			}
		} else {
			tmp1->next->prev = tmp1->prev;
			tmp1->prev->next = tmp1->next;
		}
	}

	tmp2 = tmp1;
	color tmp2_original_color = tmp2->color;
	
	if (tmp1->left == &sentinel) {
		tmp3 = tmp1->right;
		rb_transplant(tree,tmp1,tmp1->right);
	} else if(tmp1->right == &sentinel) {
		tmp3 = tmp1->left;
		rb_transplant(tree,tmp1,tmp1->left);
	} else {
		tmp2 = rb_min_node(tree,tmp1->right);
		tmp2_original_color = tmp2->color;
		tmp3 = tmp2->right;

		if (tmp2->parent == tmp1) {
			tmp3->parent = tmp2;
		} else {
			rb_transplant(tree,tmp2,tmp2->right);
			tmp2->right = tmp1->right;
			tmp2->right->parent = tmp2;
		}

		rb_transplant(tree,tmp1,tmp2);
		tmp2->left = tmp1->left;
		tmp2->left->parent = tmp2;
		tmp2->color = tmp1->color;
	}

	if (tmp2_original_color == BLACK)
		rb_delete_fixup(tree,tmp3);
 	
	tree->size -= 1;	
	destroy_rb_node(tree,tmp1);
	return original_element;
}

void* rb_min(rb_tree* tree)
{
	if (empty_rb_tree(tree))
		return NULL;
	
	return tree->min->element;
}



void* rb_max(rb_tree* tree)
{
	if (empty_rb_tree(tree))
		return NULL;

	return tree->max->element;
}

list* rb_tree_to_list(rb_tree* tree)
{
	if (tree == NULL)
		return NULL;

	list* list = init_double_linked_list(tree->type);
	rb_node* tmp = tree->min;

	while(tmp != &sentinel) {
		push_back(list,tmp->element);
		tmp = tmp->next;
	}

	return list;
}


rb_node* rb_search_left_node(rb_tree* tree, vertex* v)
{
	if (empty_rb_tree(tree))
		return NULL;

	rb_node *tmp, *left;
	tmp = tree->root;
	left = NULL;
			
	half_edge* tmp_he = tmp->element;

	while(tmp != &sentinel) {
		
		if (tmp_he->first->x < v->x) {
			left = tmp;
			
			tmp = tmp->right;
			tmp_he = tmp->element;
		} else {
			tmp = tmp->left;
			tmp_he = tmp->element;
		}
	}
	
	if (left == &sentinel)
		return NULL;

	return left;
}

half_edge* rb_search_left_he(rb_tree* tree, vertex* v)
{
	rb_node* left = rb_search_left_node(tree,v);

	if (left == NULL)
		return NULL;
	
	half_edge* he_left = left->element;
	
	return he_left;
}
