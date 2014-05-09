#include "example.h"

#include "red_black_tree/rb_tree.h"

#include "dcel/dcel.h"

#include "points/2d_points.h"
#include "half_edge/half_edge.h"
#include "face/face.h"

#include <stdlib.h>
#include <stdio.h>

dcel* construct_example()
{
	/** Declaramos los vertices. */
	//vertex *v1, *v2, *v3, *v4, *v5, *v6, *v7, *v8, *v9, *v10, *v11, *v12, *v13,
		//*v14, *v15;
		int i;
	vertrex **v;
	v=(vertrex**)malloc(15*sizeof(vertrex*));
	
	/** 
	 * Inicializamos cada vertice, los nombres que se le pasan sirven, para
	 * identificar de forma más sencilla los vertices.
	 */
	 /*
	v1 = init_point(22.0,16.0,"v_1\0");
	v2 = init_point(18.0,13.0,"v_2\0");
	v3 = init_point(16.0,22.0,"v_3\0");
	v4 = init_point(13.0,20.0,"v_4\0");
	v5 = init_point(10.0,22.0,"v_5\0");
	v6 = init_point(5.0,19.0,"v_6\0");
	v7 = init_point(7.0,16.0,"v_7\0");
	v8 = init_point(5.0,12.0,"v_8\0");
	v9 = init_point(2.0,14.0,"v_9\0");
	v10 = init_point(1.0,6.0,"v_10\0");
	v11 = init_point(6.0,1.0,"v_11\0");
	v12 = init_point(11.0,4.0,"v_12\0");	
	v13 = init_point(18.0,2.0,"v_13\0");	
	v14 = init_point(15.0,9.0,"v_14\0");
	v15 = init_point(20.0,7.0,"v_15\0");
*/	FILE *f=fopen("datos.dat","r");
	float get, geu;
	char cad[15][6];
	for(i=0;i<20;i++)
	{
		fscanf(f,"%f",&get);
		fscanf(f,"%f",&geu);
		sprintf(cad[i],"v_%d",i+1);
		init_point(get,geu,cad[i]);
	}
	/** 
	 * Declaramos todas las aristas del ejemplo, dado que C no acepta
	 * declaraciones tipo e', lo sustituimos por e_1.
	 */
	 /*
	half_edge *e_1, *e1_1, *e_2, *e1_2, *e_3, *e1_3, *e_4, *e1_4,
		*e_5, *e1_5, *e_6, *e1_6, *e_7, *e1_7, *e_8, *e1_8,
		*e_9, *e1_9, *e_10, *e1_10, *e_11, *e1_11, *e_12, *e1_12,
		*e_13, *e1_13, *e_14, *e1_14, *e_15, *e1_15;
		*/
	half_edge **e,**e1;
	e=(half_edge**)malloc(15*sizeof(half_edge*));
	e1=(half_edge**)malloc(15*sizeof(half_edge*));

	/** Inicializamos los half_edge. */
	/*
	e_1 = init_half_edge(v1,v2,"e_1\0");
	e1_1 = init_half_edge(v2,v1,"e'_1\0");

	e_2 = init_half_edge(v2,v3,"e_2\0");
	e1_2 = init_half_edge(v3,v2,"e'_2\0");

	e_3 = init_half_edge(v3,v4,"e_3\0");
	e1_3 = init_half_edge(v4,v3,"e'_3\0");

	e_4 = init_half_edge(v4,v5,"e_4\0");
	e1_4 = init_half_edge(v5,v4,"e'_4\0");

	e_5 = init_half_edge(v5,v6,"e_5\0");
	e1_5 = init_half_edge(v6,v5,"e'_5\0");

	e_6 = init_half_edge(v6,v7,"e_6\0");
	e1_6 = init_half_edge(v7,v6,"e'_6\0");
	
	e_7 = init_half_edge(v7,v8,"e_7\0");
	e1_7 = init_half_edge(v8,v7,"e'_7\0");

	e_8 = init_half_edge(v8,v9,"e_8\0");
	e1_8 = init_half_edge(v9,v8,"e'_8\0");

	e_9 = init_half_edge(v9,v10,"e_9\0");
	e1_9 = init_half_edge(v10,v9,"e'_9\0");

	e_10 = init_half_edge(v10,v11,"e_10\0");
	e1_10 = init_half_edge(v11,v10,"e'_10\0");

	e_11 = init_half_edge(v11,v12,"e_11\0");
	e1_11 = init_half_edge(v12,v11,"e'_11\0");

	e_12 = init_half_edge(v12,v13,"e_12\0");
	e1_12 = init_half_edge(v13,v12,"e'_12\0");

	e_13 = init_half_edge(v13,v14,"e_13\0");
	e1_13 = init_half_edge(v14,v13,"e'_13\0");
	
	e_14 = init_half_edge(v14,v15,"e_14\0");
	e1_14 = init_half_edge(v15,v14,"e'_14\0");

	e_15 = init_half_edge(v15,v1,"e_15\0");
	e1_15 = init_half_edge(v1,v15,"e'_15\0");
	*/
	for(i=15;i--;)
	{
		e[i]=init_half_edge(v[i],v[14-i],cad[i]);
		e[i]=init_half_edge(v[i],v[14-i],cad[i]);
	}
	/** Inidicamos los gemelos de cada half_edge. */
	e_1->twin = e1_1;
	e1_1->twin = e_1;
	
	e_2->twin = e1_2;
	e1_2->twin = e_2;
	
	e_3->twin = e1_3;
	e1_3->twin = e_3;

	e_4->twin = e1_4;
	e1_4->twin = e_4;

	e_5->twin = e1_5;
	e1_5->twin = e_5;

	e_6->twin = e1_6;
	e1_6->twin = e_6;

	e_7->twin = e1_7;
	e1_7->twin = e_7;

	e_8->twin = e1_8;
	e1_8->twin = e_8;

	e_9->twin = e1_9;
	e1_9->twin = e_9;
	
	e_10->twin = e1_10;
	e1_10->twin = e_10;

	e_11->twin = e1_11;
	e1_11->twin = e_11;

	e_12->twin = e1_12;
	e1_12->twin = e_12;

	e_13->twin = e1_13;
	e1_13->twin = e_13;

	e_14->twin = e1_14;
	e1_14->twin = e_14;

	e_15->twin = e1_15;
	e1_15->twin = e_15;

	/** Inializamos los next y prev de los half_edge interiores. */
	e_1->next = e_2;
	e_1->prev = e_15;

	e_2->next = e_3;
	e_2->prev = e_1;

	e_3->next = e_4;
	e_3->prev = e_2;

	e_4->next = e_5;
	e_4->prev = e_3;

	e_5->next = e_6;
	e_5->prev = e_4;

	e_6->next = e_7;
	e_6->prev = e_5;

	e_7->next = e_8;
	e_7->prev = e_6;

	e_8->next = e_9;
	e_8->prev = e_7;

	e_9->next = e_10;
	e_9->prev = e_8;

	e_10->next = e_11;
	e_10->prev = e_9;

	e_11->next = e_12;
	e_11->prev = e_10;

	e_12->next = e_13;
	e_12->prev = e_11;

	e_13->next = e_14;
	e_13->prev = e_12;
	
	e_14->next = e_15;
	e_14->prev = e_13;
	
	e_15->next = e_1;
	e_15->prev = e_14;

	/** Inicializamos los prev y next de los half_edge exteriores. */
	e1_1->next = e1_15;
	e1_1->prev = e1_2;

	e1_2->next = e1_1;
	e1_2->prev = e1_3;

	e1_3->next = e1_2;
	e1_3->prev = e1_4;

	e1_4->next = e1_3;
	e1_4->prev = e1_5;

	e1_5->next = e1_4;
	e1_5->prev = e1_6;

	e1_6->next = e1_5;
	e1_6->prev = e1_7;

	e1_7->next = e1_6;
	e1_7->prev = e1_8;

	e1_8->next = e1_7;
	e1_8->prev = e1_9;
	
	e1_9->next = e1_8;
	e1_9->prev = e1_10;
	
	e1_10->next = e1_9;
	e1_10->prev = e1_11;

	e1_11->next = e1_10;
	e1_11->prev = e1_12;

	e1_12->next = e1_11;
	e1_12->prev = e1_13;

	e1_13->next = e1_12;
	e1_13->prev = e1_14;

	e1_14->next = e1_13;
	e1_14->prev = e1_15;

	e1_15->next = e1_14;
	e1_15->prev = e1_1;

	/**  Inicializamos las caras. */
	face* face1, *face2;
	
	list *f1_inner, *f2_inner;
	f1_inner = init_double_linked_list(HALF_EDGE);
	push_back(f1_inner, e1_1);
	
	face1 = init_face("face 1\0", NULL, f1_inner);
	face2 = init_face("face 2\0", e_1, NULL);

	/** Le indicamos a los half_edges cual es su cara incidente */
	e_1->incident_face = face2;
	e1_1->incident_face = face1;

	e_2->incident_face = face2;
	e1_2->incident_face = face1;

	e_3->incident_face = face2;
	e1_3->incident_face = face1;

	e_4->incident_face = face2;
	e1_4->incident_face = face1;

	e_5->incident_face = face2;
	e1_5->incident_face = face1;

	e_6->incident_face = face2;
	e1_6->incident_face = face1;

	e_7->incident_face = face2;
	e1_7->incident_face = face1;

	e_8->incident_face = face2;
	e1_8->incident_face = face1;

	e_9->incident_face = face2;
	e1_9->incident_face = face1;

	e_10->incident_face = face2;
	e1_10->incident_face = face1;

	e_11->incident_face = face2;
	e1_11->incident_face = face1;

	e_12->incident_face = face2;
	e1_12->incident_face = face1;

	e_13->incident_face = face2;
	e1_13->incident_face = face1;

	e_14->incident_face = face2;
	e1_14->incident_face = face1;

	e_15->incident_face = face2;
	e1_15->incident_face = face1;

	/**
	 * Ahora que las estructuras internas de la DCEL estan completas, inicializo
	 * la dcel y le agrego sus estructuras.
	 */

	dcel* dcel = init_dcel();

	/** Insertamos los vertices.*/
	
	dcel_insert_vertex(dcel,v1);
	dcel_insert_vertex(dcel,v2);
	dcel_insert_vertex(dcel,v3);
	dcel_insert_vertex(dcel,v4);
	dcel_insert_vertex(dcel,v5);
	dcel_insert_vertex(dcel,v6);
	dcel_insert_vertex(dcel,v7);
	dcel_insert_vertex(dcel,v8);
	dcel_insert_vertex(dcel,v9);
	dcel_insert_vertex(dcel,v10);
	dcel_insert_vertex(dcel,v11);
	dcel_insert_vertex(dcel,v12);
	dcel_insert_vertex(dcel,v13);
	dcel_insert_vertex(dcel,v14);
	dcel_insert_vertex(dcel,v15);

	/** Insertamos los half_edges. */
	dcel_insert_half_edge(dcel,e_1);
	dcel_insert_half_edge(dcel,e1_1);

	dcel_insert_half_edge(dcel,e_2);
	dcel_insert_half_edge(dcel,e1_2);

	dcel_insert_half_edge(dcel,e_3);
	dcel_insert_half_edge(dcel,e1_3);

	dcel_insert_half_edge(dcel,e_4);
	dcel_insert_half_edge(dcel,e1_4);

	dcel_insert_half_edge(dcel,e_5);
	dcel_insert_half_edge(dcel,e1_5);

	dcel_insert_half_edge(dcel,e_6);
	dcel_insert_half_edge(dcel,e1_6);

	dcel_insert_half_edge(dcel,e_7);
	dcel_insert_half_edge(dcel,e1_7);

	dcel_insert_half_edge(dcel,e_8);
	dcel_insert_half_edge(dcel,e1_8);

	dcel_insert_half_edge(dcel,e_9);
	dcel_insert_half_edge(dcel,e1_9);

	dcel_insert_half_edge(dcel,e_10);
	dcel_insert_half_edge(dcel,e1_10);

	dcel_insert_half_edge(dcel,e_11);
	dcel_insert_half_edge(dcel,e1_11);

	dcel_insert_half_edge(dcel,e_12);
	dcel_insert_half_edge(dcel,e1_12);

	dcel_insert_half_edge(dcel,e_13);
	dcel_insert_half_edge(dcel,e1_13);

	dcel_insert_half_edge(dcel,e_14);
	dcel_insert_half_edge(dcel,e1_14);

	dcel_insert_half_edge(dcel,e_15);
	dcel_insert_half_edge(dcel,e1_15);
		
	/** Insertamos las caras. */
	dcel_insert_face(dcel,face1);
	dcel_insert_face(dcel,face2);
	
	return dcel;
}
