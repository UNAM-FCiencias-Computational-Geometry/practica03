/**
 * Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
 *
 */
#include "example.h"

#include "dcel/dcel.h"
#include "double_linked_list/double_linked_list.h"

#include "algorithms/make_monotone.h"

#include <stdlib.h>
#include <stdio.h>

int main(void)
{	
	dcel* dcel = construct_example();
	list* l = rb_tree_to_priority_queue(dcel->vertex);
	print_list(l);
	
	make_monotone(dcel);
		  
	return EXIT_SUCCESS;
}
