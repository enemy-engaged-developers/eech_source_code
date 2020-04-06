// 
// 	 Enemy Engaged RAH-66 Comanche Versus KA-52 Hokum
// 	 Copyright (C) 2000 Empire Interactive (Europe) Ltd,
// 	 677 High Road, North Finchley, London N12 0DA
// 
// 	 Please see the document LICENSE.TXT for the full licence agreement
// 
// 2. LICENCE
//  2.1 	
//  	Subject to the provisions of this Agreement we now grant to you the 
//  	following rights in respect of the Source Code:
//   2.1.1 
//   	the non-exclusive right to Exploit  the Source Code and Executable 
//   	Code on any medium; and 
//   2.1.2 
//   	the non-exclusive right to create and distribute Derivative Works.
//  2.2 	
//  	Subject to the provisions of this Agreement we now grant you the
// 	following rights in respect of the Object Code:
//   2.2.1 
// 	the non-exclusive right to Exploit the Object Code on the same
// 	terms and conditions set out in clause 3, provided that any
// 	distribution is done so on the terms of this Agreement and is
// 	accompanied by the Source Code and Executable Code (as
// 	applicable).
// 
// 3. GENERAL OBLIGATIONS
//  3.1 
//  	In consideration of the licence granted in clause 2.1 you now agree:
//   3.1.1 
// 	that when you distribute the Source Code or Executable Code or
// 	any Derivative Works to Recipients you will also include the
// 	terms of this Agreement;
//   3.1.2 
// 	that when you make the Source Code, Executable Code or any
// 	Derivative Works ("Materials") available to download, you will
// 	ensure that Recipients must accept the terms of this Agreement
// 	before being allowed to download such Materials;
//   3.1.3 
// 	that by Exploiting the Source Code or Executable Code you may
// 	not impose any further restrictions on a Recipient's subsequent
// 	Exploitation of the Source Code or Executable Code other than
// 	those contained in the terms and conditions of this Agreement;
//   3.1.4 
// 	not (and not to allow any third party) to profit or make any
// 	charge for the Source Code, or Executable Code, any
// 	Exploitation of the Source Code or Executable Code, or for any
// 	Derivative Works;
//   3.1.5 
// 	not to place any restrictions on the operability of the Source 
// 	Code;
//   3.1.6 
// 	to attach prominent notices to any Derivative Works stating
// 	that you have changed the Source Code or Executable Code and to
// 	include the details anddate of such change; and
//   3.1.7 
//   	not to Exploit the Source Code or Executable Code otherwise than
// 	as expressly permitted by  this Agreement.
// 



#include "3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Complex primitive clipper
//
// The routines here will clip a triangle fan or strip.
//
// Before calling the clip routine - you must fill out the vertices structure with proper data
//
//
// It is based on edge clipping rather than polygon clipping.
//  When clipping a primitive, all the edges are constructed, and clipped.
//  Then, extra edges are added / removed from the triangles, turning them into polygons ( or removing them altogether )
//
// This is repeated for each clip plane.
//
// In the end, there are a list of edges, and a list of vertices.
// This is then returned to the caller.
//
//
//
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define REPORT_CLIP_STATISTICS 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_NUMBER_OF_CLIP_PRIMITIVES 64

#define MAX_NUMBER_OF_CLIP_EDGE_REFERENCES 512

#define MAX_NUMBER_OF_CLIP_EDGES 256

#define MAX_NUMBER_OF_CLIP_VERTICES 256

#define MAX_NUMBER_OF_CLIP_VERTEX_INDICES 256

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum CLIP_PRIMITIVE_STATUS
{

	CLIP_STATUS_REJECTED,
	CLIP_STATUS_UNCLIPPED,
	CLIP_STATUS_CLIPPED_FIRST_POINT,
	CLIP_STATUS_CLIPPED_SECOND_POINT,
};

typedef enum CLIP_PRIMITIVE_STATUS clip_primitive_status;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CLIP_PRIMITIVE_EDGE
{

	int
		clip_status;

	unsigned char
		outcode,
		outcode2,
		point1_index,
		point2_index;
};

typedef struct CLIP_PRIMITIVE_EDGE clip_primitive_edge;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CLIP_PRIMITIVE_EDGE_REFERENCE
{

	unsigned char
		direction,
		edge_index,
		pad1,
		pad2;
};

typedef struct CLIP_PRIMITIVE_EDGE_REFERENCE clip_primitive_edge_reference;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CLIP_PRIMITIVE
{

	int
		number_of_edges;

	clip_primitive_edge_reference
		*edges = nullptr;
};

typedef struct CLIP_PRIMITIVE clip_primitive;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

clip_primitive
	*current_clipping_primitives = nullptr,
	clipping_primitives_array1[MAX_NUMBER_OF_CLIP_PRIMITIVES],
	clipping_primitives_array2[MAX_NUMBER_OF_CLIP_PRIMITIVES];

clip_primitive_edge_reference
	*current_clipping_edge_references = nullptr,
	clipping_edge_reference_array1[MAX_NUMBER_OF_CLIP_EDGE_REFERENCES],
	clipping_edge_reference_array2[MAX_NUMBER_OF_CLIP_EDGE_REFERENCES];

clip_primitive_edge
	*current_clipping_edges = nullptr,
	clipping_edges_array1[MAX_NUMBER_OF_CLIP_EDGES],
	clipping_edges_array2[MAX_NUMBER_OF_CLIP_EDGES];

vertex
	clipping_vertices[MAX_NUMBER_OF_CLIP_VERTICES];

int
	number_of_clipping_primitives,
	number_of_clipping_vertices,
	number_of_clipping_edges,
	number_of_clipping_edge_references;

int
	clipping_vertices_remap_table[MAX_NUMBER_OF_CLIP_VERTICES],
	clipping_primitives_results[MAX_NUMBER_OF_CLIP_PRIMITIVES],
	clipping_primitives_vertex_indices[MAX_NUMBER_OF_CLIP_VERTEX_INDICES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clip_3d_primitives ( int whole_outcode );

void reconstruct_clip_edges ( void );

int generate_hither_clipped_edge ( vertex *point1, vertex *point2 );

int generate_yonder_clipped_edge ( vertex *point1, vertex *point2 );

int generate_xmin_clipped_edge ( vertex *point1, vertex *point2 );

int generate_xmax_clipped_edge ( vertex *point1, vertex *point2 );

int generate_ymin_clipped_edge ( vertex *point1, vertex *point2 );

int generate_ymax_clipped_edge ( vertex *point1, vertex *point2 );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clip_3d_triangle_fan ( int number_of_points, int whole_outcode )
{

	int
		count,
		point_count,
		total_number_of_clipping_primitives;

	//
	// First, generate all the edges, and primitives
	//

	number_of_clipping_vertices = number_of_points;

	total_number_of_clipping_primitives = number_of_points - 2;

	number_of_clipping_edges = ( number_of_points * 2 ) - 3;

	number_of_clipping_edge_references = 0;

	//
	// The vertices have already been placed into the array by the caller
	//

	//
	// Construct the edges array - mark them as rejected which later will be corrected
	//

	//
	// First, the "spoke" edges
	//

	for ( count = 0; count < ( number_of_clipping_vertices - 1 ); count++ )
	{

		clipping_edges_array1[count].point1_index = 0;
		clipping_edges_array1[count].point2_index = count+1;
		clipping_edges_array1[count].outcode = ( ( clipping_vertices[0].outcode ) | ( clipping_vertices[count+1].outcode ) );
		clipping_edges_array1[count].outcode2 = ( ( clipping_vertices[0].outcode ) & ( clipping_vertices[count+1].outcode ) );
		clipping_edges_array1[count].clip_status = CLIP_STATUS_REJECTED;
	}

	//
	// Next the "outside" edges
	//

	for ( point_count = 1; count < number_of_clipping_edges; count++, point_count++ )
	{

		clipping_edges_array1[count].point1_index = point_count;
		clipping_edges_array1[count].point2_index = point_count+1;
		clipping_edges_array1[count].outcode = ( ( clipping_vertices[point_count].outcode ) | ( clipping_vertices[point_count+1].outcode ) );
		clipping_edges_array1[count].outcode2 = ( ( clipping_vertices[point_count].outcode ) & ( clipping_vertices[point_count+1].outcode ) );
		clipping_edges_array1[count].clip_status = CLIP_STATUS_REJECTED;
	}

	//
	// Construct the primitives ( initially triangles )
	//

	current_clipping_primitives = clipping_primitives_array1;

	current_clipping_edges = clipping_edges_array1;

	current_clipping_edge_references = clipping_edge_reference_array1;

	number_of_clipping_primitives = 0;

	for ( count = 0; count < total_number_of_clipping_primitives; count++ )
	{

		unsigned char
			outcode;

		outcode = clipping_vertices[0].outcode;
		outcode &= clipping_vertices[count+1].outcode;
		outcode &= clipping_vertices[count+2].outcode;

		if ( !outcode )
		{

			current_clipping_primitives[number_of_clipping_primitives].number_of_edges = 3;
	
			current_clipping_primitives[number_of_clipping_primitives].edges = &current_clipping_edge_references[number_of_clipping_edge_references];
	
			current_clipping_edge_references[number_of_clipping_edge_references].direction = 0;
			current_clipping_edge_references[number_of_clipping_edge_references].edge_index = count;
	
			current_clipping_edge_references[number_of_clipping_edge_references+1].direction = 0;
			current_clipping_edge_references[number_of_clipping_edge_references+1].edge_index = ( count + number_of_clipping_vertices - 1 );
	
			current_clipping_edge_references[number_of_clipping_edge_references+2].direction = 1;
			current_clipping_edge_references[number_of_clipping_edge_references+2].edge_index = count+1;

			//
	 		// Validate the edges.
			//

			current_clipping_edges[count].clip_status = CLIP_STATUS_UNCLIPPED;
			current_clipping_edges[count+1].clip_status = CLIP_STATUS_UNCLIPPED;
			current_clipping_edges[ ( count + number_of_clipping_vertices - 1 ) ].clip_status = CLIP_STATUS_UNCLIPPED;

			number_of_clipping_primitives++;

			number_of_clipping_edge_references += 3;
		}
	}

	//
	// Now hand over to the clipper part
	//

	clip_3d_primitives ( whole_outcode );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clip_3d_primitives ( int whole_outcode )
{

	int
//		destination_vertex_index,
		primitive_count,
//		vertex_count,
		vertex_index_index,
		edge_count,
		clipped_vertex_index;

	//
	// Clip the 3d parts of the primitives first of all
	//

	if ( whole_outcode & ( CLIP_HITHER | CLIP_YONDER ) )
	{

		if ( whole_outcode & CLIP_HITHER )
		{

			for ( edge_count = 0; edge_count < number_of_clipping_edges; edge_count++ )
			{

				if ( current_clipping_edges[edge_count].outcode & CLIP_HITHER )
				{

					if ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode & CLIP_HITHER )
					{

						if ( clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode & CLIP_HITHER )
						{

							current_clipping_edges[edge_count].clip_status = CLIP_STATUS_REJECTED;

							current_clipping_edges[edge_count].outcode = 0;
						}
						else
						{

							current_clipping_edges[edge_count].clip_status = CLIP_STATUS_CLIPPED_FIRST_POINT;

							clipped_vertex_index = generate_hither_clipped_edge ( &clipping_vertices[ current_clipping_edges[edge_count].point1_index],
																									&clipping_vertices[ current_clipping_edges[edge_count].point2_index] );

							current_clipping_edges[edge_count].point1_index = clipped_vertex_index;

							current_clipping_edges[edge_count].outcode = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode |
																							clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
							current_clipping_edges[edge_count].outcode2 = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode &
																							clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
						}
					}
					else
					{

						current_clipping_edges[edge_count].clip_status = CLIP_STATUS_CLIPPED_SECOND_POINT;

						clipped_vertex_index = generate_hither_clipped_edge ( &clipping_vertices[ current_clipping_edges[edge_count].point2_index ],
																								&clipping_vertices[ current_clipping_edges[edge_count].point1_index ] );

						current_clipping_edges[edge_count].point2_index = clipped_vertex_index;

						current_clipping_edges[edge_count].outcode = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode |
																						clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
						current_clipping_edges[edge_count].outcode2 = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode &
																						clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
					}
				}
			}

			reconstruct_clip_edges ();

			if ( number_of_clipping_primitives == 0 )
			{
		
				return;
			}
		}

		if ( whole_outcode & CLIP_YONDER )
		{

			for ( edge_count = 0; edge_count < number_of_clipping_edges; edge_count++ )
			{

				if ( current_clipping_edges[edge_count].outcode & CLIP_YONDER )
				{

					if ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode & CLIP_YONDER )
					{

						if ( clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode & CLIP_YONDER )
						{

							current_clipping_edges[edge_count].clip_status = CLIP_STATUS_REJECTED;

							current_clipping_edges[edge_count].outcode = 0;
						}
						else
						{

							current_clipping_edges[edge_count].clip_status = CLIP_STATUS_CLIPPED_FIRST_POINT;

							clipped_vertex_index = generate_yonder_clipped_edge ( &clipping_vertices[ current_clipping_edges[edge_count].point1_index ],
																									&clipping_vertices[ current_clipping_edges[edge_count].point2_index ] );

							current_clipping_edges[edge_count].point1_index = clipped_vertex_index;

							current_clipping_edges[edge_count].outcode = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode |
																							clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
							current_clipping_edges[edge_count].outcode2 = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode &
																							clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
						}
					}
					else
					{

						current_clipping_edges[edge_count].clip_status = CLIP_STATUS_CLIPPED_SECOND_POINT;

						clipped_vertex_index = generate_yonder_clipped_edge ( &clipping_vertices[ current_clipping_edges[edge_count].point2_index ],
																								&clipping_vertices[ current_clipping_edges[edge_count].point1_index ] );

						current_clipping_edges[edge_count].point2_index = clipped_vertex_index;

						current_clipping_edges[edge_count].outcode = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode |
																						clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
						current_clipping_edges[edge_count].outcode2 = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode &
																						clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
					}
				}
			}

			reconstruct_clip_edges ();
	
			if ( number_of_clipping_primitives == 0 )
			{
		
				return;
			}
		}

		//
		// Now modify the whole outcode
		//

		whole_outcode = 0;

		for ( edge_count = 0; edge_count < number_of_clipping_edges; edge_count++ )
		{

			if ( current_clipping_edges[edge_count].clip_status != CLIP_STATUS_REJECTED )
			{

				whole_outcode |= current_clipping_edges[edge_count].outcode;
			}
		}
	}

	//
	// Now clip the 2d parts.
	//

	if ( whole_outcode & ( CLIP_LEFT | CLIP_RIGHT | CLIP_TOP | CLIP_BOTTOM ) )
	{

		int
			vertex_count;

		//
		// Apply persepctive correction to the textures
		//

		for ( vertex_count = 0; vertex_count < number_of_clipping_vertices; vertex_count++ )
		{

			clipping_vertices[vertex_count].u *= clipping_vertices[vertex_count].q;
			clipping_vertices[vertex_count].u2 *= clipping_vertices[vertex_count].q;
			clipping_vertices[vertex_count].v *= clipping_vertices[vertex_count].q;
			clipping_vertices[vertex_count].v2 *= clipping_vertices[vertex_count].q;
		}

		if ( whole_outcode & CLIP_LEFT )
		{

			for ( edge_count = 0; edge_count < number_of_clipping_edges; edge_count++ )
			{

				if ( current_clipping_edges[edge_count].outcode & CLIP_LEFT )
				{

					if ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode & CLIP_LEFT )
					{

						if ( clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode & CLIP_LEFT )
						{

							current_clipping_edges[edge_count].clip_status = CLIP_STATUS_REJECTED;

							current_clipping_edges[edge_count].outcode = 0;
						}
						else
						{

							current_clipping_edges[edge_count].clip_status = CLIP_STATUS_CLIPPED_FIRST_POINT;

							clipped_vertex_index = generate_xmin_clipped_edge ( &clipping_vertices[ current_clipping_edges[edge_count].point1_index ],
																								 &clipping_vertices[ current_clipping_edges[edge_count].point2_index ] );

							current_clipping_edges[edge_count].point1_index = clipped_vertex_index;

							current_clipping_edges[edge_count].outcode = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode |
																							clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
							current_clipping_edges[edge_count].outcode2 = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode &
																							clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
						}
					}
					else
					{

						current_clipping_edges[edge_count].clip_status = CLIP_STATUS_CLIPPED_SECOND_POINT;

						clipped_vertex_index = generate_xmin_clipped_edge ( &clipping_vertices[ current_clipping_edges[edge_count].point2_index ],
																							 &clipping_vertices[ current_clipping_edges[edge_count].point1_index ] );

						current_clipping_edges[edge_count].point2_index = clipped_vertex_index;

						current_clipping_edges[edge_count].outcode = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode |
																						clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
						current_clipping_edges[edge_count].outcode2 = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode &
																						clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
					}
				}
			}

			reconstruct_clip_edges ();

			if ( number_of_clipping_primitives == 0 )
			{
		
				return;
			}
		}

		if ( whole_outcode & CLIP_RIGHT )
		{

			for ( edge_count = 0; edge_count < number_of_clipping_edges; edge_count++ )
			{

				if ( current_clipping_edges[edge_count].outcode & CLIP_RIGHT )
				{

					if ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode & CLIP_RIGHT )
					{

						if ( clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode & CLIP_RIGHT )
						{

							current_clipping_edges[edge_count].clip_status = CLIP_STATUS_REJECTED;

							current_clipping_edges[edge_count].outcode = 0;
						}
						else
						{

							current_clipping_edges[edge_count].clip_status = CLIP_STATUS_CLIPPED_FIRST_POINT;

							clipped_vertex_index = generate_xmax_clipped_edge ( &clipping_vertices[ current_clipping_edges[edge_count].point1_index ],
																								 &clipping_vertices[ current_clipping_edges[edge_count].point2_index ] );

							current_clipping_edges[edge_count].point1_index = clipped_vertex_index;

							current_clipping_edges[edge_count].outcode = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode |
																							clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
							current_clipping_edges[edge_count].outcode2 = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode &
																							clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
						}
					}
					else
					{

						current_clipping_edges[edge_count].clip_status = CLIP_STATUS_CLIPPED_SECOND_POINT;

						clipped_vertex_index = generate_xmax_clipped_edge ( &clipping_vertices[ current_clipping_edges[edge_count].point2_index ],
																							 &clipping_vertices[ current_clipping_edges[edge_count].point1_index ] );

						current_clipping_edges[edge_count].point2_index = clipped_vertex_index;

						current_clipping_edges[edge_count].outcode = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode |
																						clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
						current_clipping_edges[edge_count].outcode2 = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode &
																						clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
					}
				}
			}

			reconstruct_clip_edges ();

			if ( number_of_clipping_primitives == 0 )
			{
		
				return;
			}
		}

		if ( whole_outcode & CLIP_TOP )
		{

			for ( edge_count = 0; edge_count < number_of_clipping_edges; edge_count++ )
			{

				if ( current_clipping_edges[edge_count].outcode & CLIP_TOP )
				{

					if ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode & CLIP_TOP )
					{

						if ( clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode & CLIP_TOP )
						{

							current_clipping_edges[edge_count].clip_status = CLIP_STATUS_REJECTED;

							current_clipping_edges[edge_count].outcode = 0;
						}
						else
						{

							current_clipping_edges[edge_count].clip_status = CLIP_STATUS_CLIPPED_FIRST_POINT;

							clipped_vertex_index = generate_ymin_clipped_edge ( &clipping_vertices[ current_clipping_edges[edge_count].point1_index ],
																								 &clipping_vertices[ current_clipping_edges[edge_count].point2_index ] );

							current_clipping_edges[edge_count].point1_index = clipped_vertex_index;

							current_clipping_edges[edge_count].outcode = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode |
																							clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
							current_clipping_edges[edge_count].outcode2 = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode &
																							clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
						}
					}
					else
					{

						current_clipping_edges[edge_count].clip_status = CLIP_STATUS_CLIPPED_SECOND_POINT;

						clipped_vertex_index = generate_ymin_clipped_edge ( &clipping_vertices[ current_clipping_edges[edge_count].point2_index ],
																							 &clipping_vertices[ current_clipping_edges[edge_count].point1_index ] );

						current_clipping_edges[edge_count].point2_index = clipped_vertex_index;

						current_clipping_edges[edge_count].outcode = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode |
																						clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
						current_clipping_edges[edge_count].outcode2 = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode &
																						clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
					}
				}
			}

			reconstruct_clip_edges ();

			if ( number_of_clipping_primitives == 0 )
			{
		
				return;
			}
		}

		if ( whole_outcode & CLIP_BOTTOM )
		{

			for ( edge_count = 0; edge_count < number_of_clipping_edges; edge_count++ )
			{

				if ( current_clipping_edges[edge_count].outcode & CLIP_BOTTOM )
				{

					if ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode & CLIP_BOTTOM )
					{

						if ( clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode & CLIP_BOTTOM )
						{

							current_clipping_edges[edge_count].clip_status = CLIP_STATUS_REJECTED;

							current_clipping_edges[edge_count].outcode = 0;
						}
						else
						{

							current_clipping_edges[edge_count].clip_status = CLIP_STATUS_CLIPPED_FIRST_POINT;

							clipped_vertex_index = generate_ymax_clipped_edge ( &clipping_vertices[ current_clipping_edges[edge_count].point1_index ],
																								 &clipping_vertices[ current_clipping_edges[edge_count].point2_index ] );

							current_clipping_edges[edge_count].point1_index = clipped_vertex_index;

							current_clipping_edges[edge_count].outcode = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode |
																							clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
							current_clipping_edges[edge_count].outcode2 = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode &
																							clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
						}
					}
					else
					{

						current_clipping_edges[edge_count].clip_status = CLIP_STATUS_CLIPPED_SECOND_POINT;

						clipped_vertex_index = generate_ymax_clipped_edge ( &clipping_vertices[ current_clipping_edges[edge_count].point2_index ],
																							 &clipping_vertices[ current_clipping_edges[edge_count].point1_index ] );

						current_clipping_edges[edge_count].point2_index = clipped_vertex_index;

						current_clipping_edges[edge_count].outcode = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode |
																						clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
						current_clipping_edges[edge_count].outcode2 = ( clipping_vertices[ current_clipping_edges[edge_count].point1_index ].outcode &
																						clipping_vertices[ current_clipping_edges[edge_count].point2_index ].outcode );
					}
				}
			}

			reconstruct_clip_edges ();

			if ( number_of_clipping_primitives == 0 )
			{
		
				return;
			}
		}

		//
		// Remove perspective correction from the vertices
		//

		for ( vertex_count = 0; vertex_count < number_of_clipping_vertices; vertex_count++ )
		{

			clipping_vertices[vertex_count].u *= clipping_vertices[vertex_count].z;
			clipping_vertices[vertex_count].u2 *= clipping_vertices[vertex_count].z;
			clipping_vertices[vertex_count].v *= clipping_vertices[vertex_count].z;
			clipping_vertices[vertex_count].v2 *= clipping_vertices[vertex_count].z;
		}
	}

	//
	// Now to get all this data into a reasonable form.
	//
/*
	//
	// First, compact all the vertices
	//

	destination_vertex_index = 0;

	for ( vertex_count = 0; vertex_count < number_of_clipping_vertices; vertex_count++ )
	{

		if ( clipping_vertices[vertex_count].outcode == 0 )
		{

			clipping_vertices[destination_vertex_index] = clipping_vertices[vertex_count];

			clipping_vertices_remap_table[vertex_count] = destination_vertex_index;

			destination_vertex_index++;
		}
	}

	number_of_clipping_vertices = destination_vertex_index;
	*/

	//
	// Next, go through all the primitives, turning them into indexed primitives.
	//

	vertex_index_index = 0;

	for ( primitive_count = 0; primitive_count < number_of_clipping_primitives; primitive_count++ )
	{

		clipping_primitives_results[primitive_count] = current_clipping_primitives[primitive_count].number_of_edges;

		for ( edge_count = 0; edge_count < current_clipping_primitives[primitive_count].number_of_edges; edge_count++ )
		{

			clip_primitive_edge
				*edge = nullptr;

			edge = &current_clipping_edges[ current_clipping_primitives[primitive_count].edges[edge_count].edge_index ];

			if ( current_clipping_primitives[primitive_count].edges[edge_count].direction == 0 )
			{

//				clipping_primitives_vertex_indices[vertex_index_index] = clipping_vertices_remap_table[ ( edge->point1 - clipping_vertices ) ];
				clipping_primitives_vertex_indices[vertex_index_index] = edge->point1_index;	//( edge->point1 - clipping_vertices );
			}
			else
			{

//				clipping_primitives_vertex_indices[vertex_index_index] = clipping_vertices_remap_table[ ( edge->point2 - clipping_vertices ) ];
				clipping_primitives_vertex_indices[vertex_index_index] = edge->point2_index;	//( edge->point2 - clipping_vertices );
			}

			vertex_index_index++;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reconstruct_clip_edges ( void )
{

	int
//		edge_count,
		source_edge_index,
		destination_edge_index,
		destination_primitive_index,
		source_primitive_index,
		old_number_of_clipping_edges;

	clip_primitive
		*new_clipping_primitives = nullptr;
	
	clip_primitive_edge_reference
		*new_clipping_edge_references = nullptr,
		*destination_clipping_edge_references = nullptr;

	//
	// Now reconstruct the primitives.
	//

	if ( current_clipping_primitives == clipping_primitives_array1 )	{ new_clipping_primitives = clipping_primitives_array2; }
	else																					{ new_clipping_primitives = clipping_primitives_array1; }

	if ( current_clipping_edge_references == clipping_edge_reference_array1 )	{ new_clipping_edge_references = clipping_edge_reference_array2; }
	else																								{ new_clipping_edge_references = clipping_edge_reference_array1; }

	old_number_of_clipping_edges = number_of_clipping_edges;

	destination_clipping_edge_references = new_clipping_edge_references;

	destination_primitive_index = 0;

	for ( source_primitive_index = 0; source_primitive_index < number_of_clipping_primitives; source_primitive_index++ )
	{

		unsigned char
			primitive_outcode;

		int
			last_edge_clipped,
			number_of_source_edges,
			number_of_destination_edges;

		clip_primitive
			*source_primitive = nullptr,
			*destination_primitive = nullptr;

		clip_primitive_edge_reference
			*source_edges = nullptr,
			*destination_edges = nullptr;

		clip_primitive_edge
			*source_edge = nullptr;

		unsigned char
			last_clipped_vertex_index;

		destination_edge_index = 0;

		source_edge_index = 0;

		source_primitive = &current_clipping_primitives[source_primitive_index];

		destination_primitive = &new_clipping_primitives[destination_primitive_index];

		source_edges = source_primitive->edges;

		destination_edges = destination_clipping_edge_references;

		destination_primitive->edges = destination_edges;

		number_of_source_edges = source_primitive->number_of_edges;

		number_of_destination_edges = 0;

		while ( current_clipping_edges[ source_edges[source_edge_index].edge_index ].clip_status == CLIP_STATUS_REJECTED )
		{

			source_edge_index++;
		}

		source_edge = &current_clipping_edges[ source_edges[source_edge_index].edge_index ];

		destination_edges[number_of_destination_edges] = source_edges[source_edge_index];

		if ( source_edge->clip_status == CLIP_STATUS_UNCLIPPED )
		{

			last_edge_clipped = FALSE;
		}
		else if ( source_edge->clip_status == CLIP_STATUS_CLIPPED_FIRST_POINT )
		{

			last_edge_clipped = source_edges[source_edge_index].direction;

			last_clipped_vertex_index = source_edge->point1_index;
		}
		else if ( source_edge->clip_status == CLIP_STATUS_CLIPPED_SECOND_POINT )
		{

			last_edge_clipped = 1 - source_edges[source_edge_index].direction;

			last_clipped_vertex_index = source_edge->point2_index;
		}

		primitive_outcode = source_edge->outcode2;

		source_edge_index++;

		number_of_destination_edges++;

		for ( ; source_edge_index < number_of_source_edges; source_edge_index++ )
		{

			source_edge = &current_clipping_edges[ source_edges[source_edge_index].edge_index ];

			if ( source_edge->clip_status == CLIP_STATUS_UNCLIPPED )
			{

				destination_edges[number_of_destination_edges] = source_edges[source_edge_index];

				primitive_outcode &= source_edge->outcode2;
	
				number_of_destination_edges++;
			}
			else if ( source_edge->clip_status == CLIP_STATUS_CLIPPED_FIRST_POINT )
			{

				if ( source_edges[source_edge_index].direction == 1 )
				{

					last_edge_clipped = TRUE;

					last_clipped_vertex_index = source_edge->point1_index;
				}
				else
				{

					last_edge_clipped = FALSE;

					current_clipping_edges[number_of_clipping_edges].clip_status = CLIP_STATUS_UNCLIPPED;
					current_clipping_edges[number_of_clipping_edges].point1_index = last_clipped_vertex_index;
					current_clipping_edges[number_of_clipping_edges].point2_index = source_edge->point1_index;
					current_clipping_edges[number_of_clipping_edges].outcode = ( clipping_vertices[ last_clipped_vertex_index ].outcode | clipping_vertices[ source_edge->point1_index ].outcode );
					current_clipping_edges[number_of_clipping_edges].outcode2 = ( clipping_vertices[ last_clipped_vertex_index ].outcode & clipping_vertices[ source_edge->point1_index ].outcode );

					destination_edges[number_of_destination_edges].direction = 0;
					destination_edges[number_of_destination_edges].edge_index = number_of_clipping_edges;

					number_of_clipping_edges++;
					number_of_destination_edges++;
				}

				destination_edges[number_of_destination_edges] = source_edges[source_edge_index];

				primitive_outcode &= source_edge->outcode2;
	
				number_of_destination_edges++;
			}
			else if ( source_edge->clip_status == CLIP_STATUS_CLIPPED_SECOND_POINT )
			{

				if ( source_edges[source_edge_index].direction == 1 )
				{

					last_edge_clipped = FALSE;

					current_clipping_edges[number_of_clipping_edges].clip_status = CLIP_STATUS_UNCLIPPED;
					current_clipping_edges[number_of_clipping_edges].point1_index = last_clipped_vertex_index;
					current_clipping_edges[number_of_clipping_edges].point2_index = source_edge->point2_index;
					current_clipping_edges[number_of_clipping_edges].outcode = ( clipping_vertices[ last_clipped_vertex_index ].outcode | clipping_vertices[ source_edge->point2_index ].outcode );
					current_clipping_edges[number_of_clipping_edges].outcode2 = ( clipping_vertices[ last_clipped_vertex_index ].outcode & clipping_vertices[ source_edge->point2_index ].outcode );

					destination_edges[number_of_destination_edges].direction = 0;
					destination_edges[number_of_destination_edges].edge_index = number_of_clipping_edges;

					number_of_clipping_edges++;
					number_of_destination_edges++;
				}
				else
				{

					last_edge_clipped = TRUE;

					last_clipped_vertex_index = source_edge->point2_index;
				}

				destination_edges[number_of_destination_edges] = source_edges[source_edge_index];

				primitive_outcode &= source_edge->outcode2;
	
				number_of_destination_edges++;
			}
		}

		//
		// Clear up the ending of the primitive
		//

		if ( last_edge_clipped )
		{

			last_edge_clipped = FALSE;

			if ( destination_edges[0].direction == 0 )	{ current_clipping_edges[number_of_clipping_edges].point2_index = current_clipping_edges[ destination_edges[0].edge_index ].point1_index; }
			else														{ current_clipping_edges[number_of_clipping_edges].point2_index = current_clipping_edges[ destination_edges[0].edge_index ].point2_index; }

			current_clipping_edges[number_of_clipping_edges].clip_status = CLIP_STATUS_UNCLIPPED;
			current_clipping_edges[number_of_clipping_edges].point1_index = last_clipped_vertex_index;
			current_clipping_edges[number_of_clipping_edges].outcode = ( clipping_vertices[ current_clipping_edges[number_of_clipping_edges].point1_index ].outcode |
																					clipping_vertices[ current_clipping_edges[number_of_clipping_edges].point2_index ].outcode );

			destination_edges[number_of_destination_edges].direction = 0;
			destination_edges[number_of_destination_edges].edge_index = number_of_clipping_edges;

			number_of_clipping_edges++;
			number_of_destination_edges++;
		}

		if ( !primitive_outcode )
		{

			destination_primitive->number_of_edges = number_of_destination_edges;

			destination_primitive_index++;

			destination_clipping_edge_references += number_of_destination_edges;
		}
	}

	current_clipping_primitives = new_clipping_primitives;

	current_clipping_edge_references = new_clipping_edge_references;

	number_of_clipping_primitives = destination_primitive_index;

	//
	// Tag all edges as rejected
	//

//	for ( edge_count = ( number_of_clipping_edges - 1 ); edge_count >= 0; edge_count-- )
//	{
//
//		current_clipping_edges[edge_count].clip_status = CLIP_STATUS_REJECTED;
//	}

	//
	// Now go through all the primitives, tagging their edges as unclipped
	//

	for ( source_primitive_index = 0; source_primitive_index < number_of_clipping_primitives; source_primitive_index++ )
	{

		int
			source_edge_index,
			number_of_source_edges;

		clip_primitive
			*source_primitive = nullptr;

		clip_primitive_edge_reference
			*source_edges = nullptr;

		source_primitive = &current_clipping_primitives[source_primitive_index];

		source_edges = source_primitive->edges;

		number_of_source_edges = source_primitive->number_of_edges;

		for ( source_edge_index = 0; source_edge_index < number_of_source_edges; source_edge_index++ )
		{

			current_clipping_edges[ source_edges[source_edge_index].edge_index ].clip_status = CLIP_STATUS_UNCLIPPED;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int generate_hither_clipped_edge ( vertex *point1, vertex *point2 )
{

	double
		t;

	vertex
		*clip = nullptr;

	float
		fog,
		alpha,
//		alpha2,
		red,
//		red2,
		green,
//		green2,
		blue;
//		blue2;

	int
		int_fog,
		int_dfog,
		int_alpha,
		int_dalpha,
//		int_alpha2,
//		int_dalpha2,
		int_red,
		int_dred,
//		int_red2,
//		int_dred2,
		int_green,
		int_dgreen,
//		int_green2,
//		int_dgreen2,
		int_blue,
		int_dblue;
//		int_blue2,
//		int_dblue2;

	t = ( ( clip_hither - point2->z ) / ( point2->z - point1->z ) );

	clip = &clipping_vertices[number_of_clipping_vertices];

	*( ( int * ) &clip->z ) = *( ( int * ) &clip_hither );
	*( ( int * ) &clip->q ) = *( ( int * ) &clip_hither_reciprocal );

	int_fog = point2->fog;
	int_dfog = int_fog - ( int ) point1->fog;

	int_alpha = point2->alpha;
	int_dalpha = int_alpha - ( int ) point1->alpha;
//	int_alpha2 = point2->alpha2;
//	int_dalpha2 = int_alpha2 - ( int ) point1->alpha2;

	int_red = point2->red;
	int_dred = int_red - ( int ) point1->red;
//	int_red2 = point2->red2;
//	int_dred2 = int_red2 - ( int ) point1->red2;

	int_green = point2->green;
	int_dgreen = int_green - ( int ) point1->green;
//	int_green2 = point2->green2;
//	int_dgreen2 = int_green2 - ( int ) point1->green2;

	int_blue = point2->blue;
	int_dblue = int_blue - ( int ) point1->blue;
//	int_blue2 = point2->blue2;
//	int_dblue2 = int_blue2 - ( int ) point1->blue2;

	clip->x = point2->x + ( t * ( point2->x - point1->x ) );
	clip->y = point2->y + ( t * ( point2->y - point1->y ) );

	fog = ( float ) int_fog + ( t * ( float ) int_dfog );
	alpha = ( float ) int_alpha + ( t * ( float ) int_dalpha );
//	alpha2 = ( float ) int_alpha2 + ( t * ( float ) int_dalpha2 );
	red = ( float ) int_red + ( t * ( float ) int_dred );
//	red2 = ( float ) int_red2 + ( t * ( float ) int_dred2 );
	green = ( float ) int_green + ( t * ( float ) int_dgreen );
//	green2 = ( float ) int_green2 + ( t * ( float ) int_dgreen2 );
	blue = ( float ) int_blue + ( t * ( float ) int_dblue );
//	blue2 = ( float ) int_blue2 + ( t * ( float ) int_dblue2 );

	fog += FLOAT_FLOAT_FACTOR;
	alpha += FLOAT_FLOAT_FACTOR;
//	alpha2 += FLOAT_FLOAT_FACTOR;
	red += FLOAT_FLOAT_FACTOR;
//	red2 += FLOAT_FLOAT_FACTOR;
	green += FLOAT_FLOAT_FACTOR;
//	green2 += FLOAT_FLOAT_FACTOR;
	blue += FLOAT_FLOAT_FACTOR;
//	blue2 += FLOAT_FLOAT_FACTOR;

	int_fog = ( *( ( int * ) &fog ) - INTEGER_FLOAT_FACTOR );
	int_alpha = ( *( ( int * ) &alpha ) - INTEGER_FLOAT_FACTOR );
//	int_alpha2 = ( *( ( int * ) &alpha2 ) - INTEGER_FLOAT_FACTOR );
	int_red = ( *( ( int * ) &red ) - INTEGER_FLOAT_FACTOR );
//	int_red2 = ( *( ( int * ) &red2 ) - INTEGER_FLOAT_FACTOR );
	int_green = ( *( ( int * ) &green ) - INTEGER_FLOAT_FACTOR );
//	int_green2 = ( *( ( int * ) &green2 ) - INTEGER_FLOAT_FACTOR );
	int_blue = ( *( ( int * ) &blue ) - INTEGER_FLOAT_FACTOR );
//	int_blue2 = ( *( ( int * ) &blue2 ) - INTEGER_FLOAT_FACTOR );

	clip->fog = int_fog;
	clip->alpha = int_alpha;
//	clip->alpha2 = int_alpha2;
	clip->red = int_red;
//	clip->red2 = int_red2;
	clip->green = int_green;
//	clip->green2 = int_green2;
	clip->blue = int_blue;
//	clip->blue2 = int_blue2;

	clip->u = point2->u + ( t * ( point2->u - point1->u ) );
	clip->v = point2->v + ( t * ( point2->v - point1->v ) );
//	clip->u2 = point2->u2 + ( t * ( point2->u2 - point1->u2 ) );
//	clip->v2 = point2->v2 + ( t * ( point2->v2 - point1->v2 ) );

	clip->j = active_3d_environment->y_origin;
	clip->i = ( active_3d_environment->screen_i_scale * clip->x * clip->q );
	clip->j -= ( active_3d_environment->screen_j_scale * clip->y * clip->q );
	clip->i += active_3d_environment->x_origin;

	clip->outcode = generate_3d_outcode ( clip->i, clip->j );

#if REPORT_CLIP_STATISTICS

	number_of_near_coordinates_inserted++;

#endif

	return ( number_of_clipping_vertices++ );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int generate_yonder_clipped_edge ( vertex *point1, vertex *point2 )
{

	double
		t;

	vertex
		*clip = nullptr;

	float
		fog,
		alpha,
		alpha2,
		red,
		red2,
		green,
		green2,
		blue,
		blue2;

	int
		int_fog,
		int_dfog,
		int_alpha,
		int_dalpha,
		int_alpha2,
		int_dalpha2,
		int_red,
		int_dred,
		int_red2,
		int_dred2,
		int_green,
		int_dgreen,
		int_green2,
		int_dgreen2,
		int_blue,
		int_dblue,
		int_blue2,
		int_dblue2;

	t = ( ( clip_yonder - point2->z ) / ( point2->z - point1->z ) );

	clip = &clipping_vertices[number_of_clipping_vertices];

	*( ( int * ) &clip->z ) = *( ( int * ) &clip_yonder );
	*( ( int * ) &clip->q ) = *( ( int * ) &clip_yonder_reciprocal );

	int_fog = point2->fog;
	int_dfog = int_fog - ( int ) point1->fog;

	int_alpha = point2->alpha;
	int_dalpha = int_alpha - ( int ) point1->alpha;
	int_alpha2 = point2->alpha2;
	int_dalpha2 = int_alpha2 - ( int ) point1->alpha2;

	int_red = point2->red;
	int_dred = int_red - ( int ) point1->red;
	int_red2 = point2->red2;
	int_dred2 = int_red2 - ( int ) point1->red2;

	int_green = point2->green;
	int_dgreen = int_green - ( int ) point1->green;
	int_green2 = point2->green2;
	int_dgreen2 = int_green2 - ( int ) point1->green2;

	int_blue = point2->blue;
	int_dblue = int_blue - ( int ) point1->blue;
	int_blue2 = point2->blue2;
	int_dblue2 = int_blue2 - ( int ) point1->blue2;

	clip->x = point2->x + ( t * ( point2->x - point1->x ) );
	clip->y = point2->y + ( t * ( point2->y - point1->y ) );

	fog = ( float ) int_fog + ( t * ( float ) int_dfog );
	alpha = ( float ) int_alpha + ( t * ( float ) int_dalpha );
	alpha2 = ( float ) int_alpha2 + ( t * ( float ) int_dalpha2 );
	red = ( float ) int_red + ( t * ( float ) int_dred );
	red2 = ( float ) int_red2 + ( t * ( float ) int_dred2 );
	green = ( float ) int_green + ( t * ( float ) int_dgreen );
	green2 = ( float ) int_green2 + ( t * ( float ) int_dgreen2 );
	blue = ( float ) int_blue + ( t * ( float ) int_dblue );
	blue2 = ( float ) int_blue2 + ( t * ( float ) int_dblue2 );

	fog += FLOAT_FLOAT_FACTOR;
	alpha += FLOAT_FLOAT_FACTOR;
	alpha2 += FLOAT_FLOAT_FACTOR;
	red += FLOAT_FLOAT_FACTOR;
	red2 += FLOAT_FLOAT_FACTOR;
	green += FLOAT_FLOAT_FACTOR;
	green2 += FLOAT_FLOAT_FACTOR;
	blue += FLOAT_FLOAT_FACTOR;
	blue2 += FLOAT_FLOAT_FACTOR;

	int_fog = ( *( ( int * ) &fog ) - INTEGER_FLOAT_FACTOR );
	int_alpha = ( *( ( int * ) &alpha ) - INTEGER_FLOAT_FACTOR );
	int_alpha2 = ( *( ( int * ) &alpha2 ) - INTEGER_FLOAT_FACTOR );
	int_red = ( *( ( int * ) &red ) - INTEGER_FLOAT_FACTOR );
	int_red2 = ( *( ( int * ) &red2 ) - INTEGER_FLOAT_FACTOR );
	int_green = ( *( ( int * ) &green ) - INTEGER_FLOAT_FACTOR );
	int_green2 = ( *( ( int * ) &green2 ) - INTEGER_FLOAT_FACTOR );
	int_blue = ( *( ( int * ) &blue ) - INTEGER_FLOAT_FACTOR );
	int_blue2 = ( *( ( int * ) &blue2 ) - INTEGER_FLOAT_FACTOR );

	clip->fog = int_fog;
	clip->alpha = int_alpha;
	clip->alpha2 = int_alpha2;
	clip->red = int_red;
	clip->red2 = int_red2;
	clip->green = int_green;
	clip->green2 = int_green2;
	clip->blue = int_blue;
	clip->blue2 = int_blue2;

	clip->u = point2->u + ( t * ( point2->u - point1->u ) );
	clip->v = point2->v + ( t * ( point2->v - point1->v ) );
	clip->u2 = point2->u2 + ( t * ( point2->u2 - point1->u2 ) );
	clip->v2 = point2->v2 + ( t * ( point2->v2 - point1->v2 ) );

	clip->j = active_3d_environment->y_origin;
	clip->i = ( active_3d_environment->screen_i_scale * clip->x * clip->q );
	clip->j -= ( active_3d_environment->screen_j_scale * clip->y * clip->q );
	clip->i += active_3d_environment->x_origin;

	clip->outcode = generate_3d_outcode ( clip->i, clip->j );

#if REPORT_CLIP_STATISTICS

	number_of_far_coordinates_inserted++;

#endif

	return ( number_of_clipping_vertices++ );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int generate_xmin_clipped_edge ( vertex *point1, vertex *point2 )
{

	vertex
		*clip = nullptr;

	double
		t,
		numerator,
		denominator;

	float
		fog,
		alpha,
		alpha2,
		red,
		red2,
		green,
		green2,
		blue,
		blue2;

	int
		int_alpha,
		int_dalpha,
		int_alpha2,
		int_dalpha2,
		int_fog,
		int_dfog,
		int_red,
		int_dred,
		int_red2,
		int_dred2,
		int_green,
		int_dgreen,
		int_green2,
		int_dgreen2,
		int_blue,
		int_dblue,
		int_blue2,
		int_dblue2;

	if ( point1->j > point2->j )
	{

		clip = point1;

		point1 = point2;

		point2 = clip;
	}

	numerator = active_viewport.x_min - point2->i;

	denominator = point2->i - point1->i;

#ifdef DEBUG

	if ( fabs ( denominator ) < fabs ( numerator ) )
	{

		debug_fatal ( "Internal clipping error" );
	}

#endif

	t = ( numerator / denominator );

	clip = &clipping_vertices[number_of_clipping_vertices];

	int_fog = point2->fog;
	int_dfog = int_fog - ( int ) point1->fog;

	int_alpha = point2->alpha;
	int_dalpha = int_alpha - ( int ) point1->alpha;
	int_alpha2 = point2->alpha2;
	int_dalpha2 = int_alpha2 - ( int ) point1->alpha2;

	int_red = point2->red;
	int_dred = int_red - ( int ) point1->red;
	int_red2 = point2->red2;
	int_dred2 = int_red2 - ( int ) point1->red2;

	int_green = point2->green;
	int_dgreen = int_green - ( int ) point1->green;
	int_green2 = point2->green2;
	int_dgreen2 = int_green2 - ( int ) point1->green2;

	int_blue = point2->blue;
	int_dblue = int_blue - ( int ) point1->blue;
	int_blue2 = point2->blue2;
	int_dblue2 = int_blue2 - ( int ) point1->blue2;

	fog = ( float ) int_fog + ( t * ( float ) int_dfog );
	alpha = ( float ) int_alpha + ( t * ( float ) int_dalpha );
	alpha2 = ( float ) int_alpha2 + ( t * ( float ) int_dalpha2 );
	red = ( float ) int_red + ( t * ( float ) int_dred );
	red2 = ( float ) int_red2 + ( t * ( float ) int_dred2 );
	green = ( float ) int_green + ( t * ( float ) int_dgreen );
	green2 = ( float ) int_green2 + ( t * ( float ) int_dgreen2 );
	blue = ( float ) int_blue + ( t * ( float ) int_dblue );
	blue2 = ( float ) int_blue2 + ( t * ( float ) int_dblue2 );

	fog += FLOAT_FLOAT_FACTOR;
	alpha += FLOAT_FLOAT_FACTOR;
	alpha2 += FLOAT_FLOAT_FACTOR;
	red += FLOAT_FLOAT_FACTOR;
	red2 += FLOAT_FLOAT_FACTOR;
	green += FLOAT_FLOAT_FACTOR;
	green2 += FLOAT_FLOAT_FACTOR;
	blue += FLOAT_FLOAT_FACTOR;
	blue2 += FLOAT_FLOAT_FACTOR;

	int_fog = ( *( ( int * ) &fog ) - INTEGER_FLOAT_FACTOR );
	int_alpha = ( *( ( int * ) &alpha ) - INTEGER_FLOAT_FACTOR );
	int_alpha2 = ( *( ( int * ) &alpha2 ) - INTEGER_FLOAT_FACTOR );
	int_red = ( *( ( int * ) &red ) - INTEGER_FLOAT_FACTOR );
	int_red2 = ( *( ( int * ) &red2 ) - INTEGER_FLOAT_FACTOR );
	int_green = ( *( ( int * ) &green ) - INTEGER_FLOAT_FACTOR );
	int_green2 = ( *( ( int * ) &green2 ) - INTEGER_FLOAT_FACTOR );
	int_blue = ( *( ( int * ) &blue ) - INTEGER_FLOAT_FACTOR );
	int_blue2 = ( *( ( int * ) &blue2 ) - INTEGER_FLOAT_FACTOR );

	clip->fog = int_fog;
	clip->alpha = int_alpha;
	clip->red = int_red;
	clip->green = int_green;
	clip->blue = int_blue;
	clip->alpha2 = int_alpha2;
	clip->red2 = int_red2;
	clip->green2 = int_green2;
	clip->blue2 = int_blue2;

	clip->i = active_viewport.x_min;
	clip->j = point2->j + ( t * ( point2->j - point1->j ) );
	clip->q = point2->q + ( t * ( point2->q - point1->q ) );
	clip->z = 1.0 / clip->q;

	clip->u = point2->u + ( t * ( point2->u - point1->u ) );
	clip->v = point2->v + ( t * ( point2->v - point1->v ) );
	clip->u2 = point2->u2 + ( t * ( point2->u2 - point1->u2 ) );
	clip->v2 = point2->v2 + ( t * ( point2->v2 - point1->v2 ) );

	clip->outcode = generate_3d_j_outcode ( clip->j );

#if REPORT_CLIP_STATISTICS

	number_of_xmin_coordinates_inserted++;

#endif
	return ( number_of_clipping_vertices++ );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int generate_xmax_clipped_edge ( vertex *point1, vertex *point2 )
{

	vertex
		*clip = nullptr;

	double
		t,
		numerator,
		denominator;

	float
		fog,
		alpha,
		alpha2,
		red,
		red2,
		green,
		green2,
		blue,
		blue2;

	int
		int_fog,
		int_dfog,
		int_alpha,
		int_dalpha,
		int_alpha2,
		int_dalpha2,
		int_red,
		int_dred,
		int_red2,
		int_dred2,
		int_green,
		int_dgreen,
		int_green2,
		int_dgreen2,
		int_blue,
		int_dblue,
		int_blue2,
		int_dblue2;

	if ( point1->j > point2->j )
	{

		clip = point1;

		point1 = point2;

		point2 = clip;
	}

	numerator = active_viewport.x_max - point2->i;

	denominator = point2->i - point1->i;

#ifdef DEBUG

	if ( fabs ( denominator ) < fabs ( numerator ) )
	{

		debug_fatal ( "Internal clipping error" );
	}

#endif

	t = ( numerator / denominator );

	clip = &clipping_vertices[number_of_clipping_vertices];

	int_fog = point2->fog;
	int_dfog = int_fog - ( int ) point1->fog;

	int_alpha = point2->alpha;
	int_dalpha = int_alpha - ( int ) point1->alpha;
	int_alpha2 = point2->alpha2;
	int_dalpha2 = int_alpha2 - ( int ) point1->alpha2;

	int_red = point2->red;
	int_dred = int_red - ( int ) point1->red;
	int_red2 = point2->red2;
	int_dred2 = int_red2 - ( int ) point1->red2;

	int_green = point2->green;
	int_dgreen = int_green - ( int ) point1->green;
	int_green2 = point2->green2;
	int_dgreen2 = int_green2 - ( int ) point1->green2;

	int_blue = point2->blue;
	int_dblue = int_blue - ( int ) point1->blue;
	int_blue2 = point2->blue2;
	int_dblue2 = int_blue2 - ( int ) point1->blue2;

	fog = ( float ) int_fog + ( t * ( float ) int_dfog );
	alpha = ( float ) int_alpha + ( t * ( float ) int_dalpha );
	alpha2 = ( float ) int_alpha2 + ( t * ( float ) int_dalpha2 );
	red = ( float ) int_red + ( t * ( float ) int_dred );
	red2 = ( float ) int_red2 + ( t * ( float ) int_dred2 );
	green = ( float ) int_green + ( t * ( float ) int_dgreen );
	green2 = ( float ) int_green2 + ( t * ( float ) int_dgreen2 );
	blue = ( float ) int_blue + ( t * ( float ) int_dblue );
	blue2 = ( float ) int_blue2 + ( t * ( float ) int_dblue2 );

	fog += FLOAT_FLOAT_FACTOR;
	alpha += FLOAT_FLOAT_FACTOR;
	alpha2 += FLOAT_FLOAT_FACTOR;
	red += FLOAT_FLOAT_FACTOR;
	red2 += FLOAT_FLOAT_FACTOR;
	green += FLOAT_FLOAT_FACTOR;
	green2 += FLOAT_FLOAT_FACTOR;
	blue += FLOAT_FLOAT_FACTOR;
	blue2 += FLOAT_FLOAT_FACTOR;

	int_fog = ( *( ( int * ) &fog ) - INTEGER_FLOAT_FACTOR );
	int_alpha = ( *( ( int * ) &alpha ) - INTEGER_FLOAT_FACTOR );
	int_alpha2 = ( *( ( int * ) &alpha2 ) - INTEGER_FLOAT_FACTOR );
	int_red = ( *( ( int * ) &red ) - INTEGER_FLOAT_FACTOR );
	int_red2 = ( *( ( int * ) &red2 ) - INTEGER_FLOAT_FACTOR );
	int_green = ( *( ( int * ) &green ) - INTEGER_FLOAT_FACTOR );
	int_green2 = ( *( ( int * ) &green2 ) - INTEGER_FLOAT_FACTOR );
	int_blue = ( *( ( int * ) &blue ) - INTEGER_FLOAT_FACTOR );
	int_blue2 = ( *( ( int * ) &blue2 ) - INTEGER_FLOAT_FACTOR );

	clip->fog = int_fog;
	clip->alpha = int_alpha;
	clip->alpha2 = int_alpha2;
	clip->red = int_red;
	clip->red2 = int_red2;
	clip->green = int_green;
	clip->green2 = int_green2;
	clip->blue = int_blue;
	clip->blue2 = int_blue2;

	clip->i = active_viewport.x_max;
	clip->j = point2->j + ( t * ( point2->j - point1->j ) );
	clip->q = point2->q + ( t * ( point2->q - point1->q ) );
	clip->z = 1.0 / clip->q;

	clip->u = point2->u + ( t * ( point2->u - point1->u ) );
	clip->v = point2->v + ( t * ( point2->v - point1->v ) );
	clip->u2 = point2->u2 + ( t * ( point2->u2 - point1->u2 ) );
	clip->v2 = point2->v2 + ( t * ( point2->v2 - point1->v2 ) );

	clip->outcode = generate_3d_j_outcode ( clip->j );

#if REPORT_CLIP_STATISTICS

	number_of_xmax_coordinates_inserted++;

#endif
	return ( number_of_clipping_vertices++ );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int generate_ymin_clipped_edge ( vertex *point1, vertex *point2 )
{

	vertex
		*clip = nullptr;

	double
		t,
		numerator,
		denominator;

	float
		fog,
		alpha,
		alpha2,
		red,
		red2,
		green,
		green2,
		blue,
		blue2;

	int
		int_fog,
		int_dfog,
		int_alpha,
		int_dalpha,
		int_alpha2,
		int_dalpha2,
		int_red,
		int_dred,
		int_red2,
		int_dred2,
		int_green,
		int_dgreen,
		int_green2,
		int_dgreen2,
		int_blue,
		int_dblue,
		int_blue2,
		int_dblue2;

	if ( point1->i > point2->i )
	{

		clip = point1;
		point1 = point2;
		point2 = clip;
	}

	numerator = active_viewport.y_min - point2->j;

	denominator = point2->j - point1->j;

#ifdef DEBUG

	if ( fabs ( denominator ) < fabs ( numerator ) )
	{

		debug_fatal ( "Internal clipping error" );
	}

#endif

	t = ( numerator / denominator );

	clip = &clipping_vertices[number_of_clipping_vertices];

	int_fog = point2->fog;
	int_dfog = int_fog - ( int ) point1->fog;

	int_alpha = point2->alpha;
	int_dalpha = int_alpha - ( int ) point1->alpha;
	int_alpha2 = point2->alpha2;
	int_dalpha2 = int_alpha2 - ( int ) point1->alpha2;

	int_red = point2->red;
	int_dred = int_red - ( int ) point1->red;
	int_red2 = point2->red2;
	int_dred2 = int_red2 - ( int ) point1->red2;

	int_green = point2->green;
	int_dgreen = int_green - ( int ) point1->green;
	int_green2 = point2->green2;
	int_dgreen2 = int_green2 - ( int ) point1->green2;

	int_blue = point2->blue;
	int_dblue = int_blue - ( int ) point1->blue;
	int_blue2 = point2->blue2;
	int_dblue2 = int_blue2 - ( int ) point1->blue2;

	fog = ( float ) int_fog + ( t * ( float ) int_dfog );
	alpha = ( float ) int_alpha + ( t * ( float ) int_dalpha );
	alpha2 = ( float ) int_alpha2 + ( t * ( float ) int_dalpha2 );
	red = ( float ) int_red + ( t * ( float ) int_dred );
	red2 = ( float ) int_red2 + ( t * ( float ) int_dred2 );
	green = ( float ) int_green + ( t * ( float ) int_dgreen );
	green2 = ( float ) int_green2 + ( t * ( float ) int_dgreen2 );
	blue = ( float ) int_blue + ( t * ( float ) int_dblue );
	blue2 = ( float ) int_blue2 + ( t * ( float ) int_dblue2 );

	fog += FLOAT_FLOAT_FACTOR;
	alpha += FLOAT_FLOAT_FACTOR;
	alpha2 += FLOAT_FLOAT_FACTOR;
	red += FLOAT_FLOAT_FACTOR;
	red2 += FLOAT_FLOAT_FACTOR;
	green += FLOAT_FLOAT_FACTOR;
	green2 += FLOAT_FLOAT_FACTOR;
	blue += FLOAT_FLOAT_FACTOR;
	blue2 += FLOAT_FLOAT_FACTOR;

	int_fog = ( *( ( int * ) &fog ) - INTEGER_FLOAT_FACTOR );
	int_alpha = ( *( ( int * ) &alpha ) - INTEGER_FLOAT_FACTOR );
	int_alpha2 = ( *( ( int * ) &alpha2 ) - INTEGER_FLOAT_FACTOR );
	int_red = ( *( ( int * ) &red ) - INTEGER_FLOAT_FACTOR );
	int_red2 = ( *( ( int * ) &red2 ) - INTEGER_FLOAT_FACTOR );
	int_green = ( *( ( int * ) &green ) - INTEGER_FLOAT_FACTOR );
	int_green2 = ( *( ( int * ) &green2 ) - INTEGER_FLOAT_FACTOR );
	int_blue = ( *( ( int * ) &blue ) - INTEGER_FLOAT_FACTOR );
	int_blue2 = ( *( ( int * ) &blue2 ) - INTEGER_FLOAT_FACTOR );

	clip->fog = int_fog;
	clip->alpha = int_alpha;
	clip->alpha2 = int_alpha2;
	clip->red = int_red;
	clip->red2 = int_red2;
	clip->green = int_green;
	clip->green2 = int_green2;
	clip->blue = int_blue;
	clip->blue2 = int_blue2;

	clip->i = point2->i + ( t * ( point2->i - point1->i ) );
	clip->j = active_viewport.y_min;
	clip->q = point2->q + ( t * ( point2->q - point1->q ) );
	clip->z = 1.0 / clip->q;

	clip->u = point2->u + ( t * ( point2->u - point1->u ) );
	clip->v = point2->v + ( t * ( point2->v - point1->v ) );
	clip->u2 = point2->u2 + ( t * ( point2->u2 - point1->u2 ) );
	clip->v2 = point2->v2 + ( t * ( point2->v2 - point1->v2 ) );

	clip->outcode = 0;

#if REPORT_CLIP_STATISTICS

	number_of_ymin_coordinates_inserted++;

#endif
	return ( number_of_clipping_vertices++ );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int generate_ymax_clipped_edge ( vertex *point1, vertex *point2 )
{

	vertex
		*clip = nullptr;

	double
		t,
		numerator,
		denominator;

	float
		fog,
		alpha,
		alpha2,
		red,
		red2,
		green,
		green2,
		blue,
		blue2;

	int
		int_fog,
		int_dfog,
		int_alpha,
		int_dalpha,
		int_alpha2,
		int_dalpha2,
		int_red,
		int_dred,
		int_red2,
		int_dred2,
		int_green,
		int_dgreen,
		int_green2,
		int_dgreen2,
		int_blue,
		int_dblue,
		int_blue2,
		int_dblue2;

	if ( point1->i > point2->i )
	{

		clip = point1;
		point1 = point2;
		point2 = clip;
	}

	numerator = active_viewport.y_max - point2->j;

	denominator = point2->j - point1->j;

#ifdef DEBUG

	if ( fabs ( denominator ) < fabs ( numerator ) )
	{

		debug_fatal ( "Internal clipping error" );
	}

#endif

	t = ( numerator / denominator );

	clip = &clipping_vertices[number_of_clipping_vertices];

	int_fog = point2->fog;
	int_dfog = int_fog - ( int ) point1->fog;

	int_alpha = point2->alpha;
	int_dalpha = int_alpha - ( int ) point1->alpha;
	int_alpha2 = point2->alpha2;
	int_dalpha2 = int_alpha2 - ( int ) point1->alpha2;

	int_red = point2->red;
	int_dred = int_red - ( int ) point1->red;
	int_red2 = point2->red2;
	int_dred2 = int_red2 - ( int ) point1->red2;

	int_green = point2->green;
	int_dgreen = int_green - ( int ) point1->green;
	int_green2 = point2->green2;
	int_dgreen2 = int_green2 - ( int ) point1->green2;

	int_blue = point2->blue;
	int_dblue = int_blue - ( int ) point1->blue;
	int_blue2 = point2->blue2;
	int_dblue2 = int_blue2 - ( int ) point1->blue2;

	fog = ( float ) int_fog + ( t * ( float ) int_dfog );
	alpha = ( float ) int_alpha + ( t * ( float ) int_dalpha );
	alpha2 = ( float ) int_alpha2 + ( t * ( float ) int_dalpha2 );
	red = ( float ) int_red + ( t * ( float ) int_dred );
	red2 = ( float ) int_red2 + ( t * ( float ) int_dred2 );
	green = ( float ) int_green + ( t * ( float ) int_dgreen );
	green2 = ( float ) int_green2 + ( t * ( float ) int_dgreen2 );
	blue = ( float ) int_blue + ( t * ( float ) int_dblue );
	blue2 = ( float ) int_blue2 + ( t * ( float ) int_dblue2 );

	fog += FLOAT_FLOAT_FACTOR;
	alpha += FLOAT_FLOAT_FACTOR;
	alpha2 += FLOAT_FLOAT_FACTOR;
	red += FLOAT_FLOAT_FACTOR;
	red2 += FLOAT_FLOAT_FACTOR;
	green += FLOAT_FLOAT_FACTOR;
	green2 += FLOAT_FLOAT_FACTOR;
	blue += FLOAT_FLOAT_FACTOR;
	blue2 += FLOAT_FLOAT_FACTOR;

	int_fog = ( *( ( int * ) &fog ) - INTEGER_FLOAT_FACTOR );
	int_alpha = ( *( ( int * ) &alpha ) - INTEGER_FLOAT_FACTOR );
	int_alpha2 = ( *( ( int * ) &alpha2 ) - INTEGER_FLOAT_FACTOR );
	int_red = ( *( ( int * ) &red ) - INTEGER_FLOAT_FACTOR );
	int_red2 = ( *( ( int * ) &red2 ) - INTEGER_FLOAT_FACTOR );
	int_green = ( *( ( int * ) &green ) - INTEGER_FLOAT_FACTOR );
	int_green2 = ( *( ( int * ) &green2 ) - INTEGER_FLOAT_FACTOR );
	int_blue = ( *( ( int * ) &blue ) - INTEGER_FLOAT_FACTOR );
	int_blue2 = ( *( ( int * ) &blue2 ) - INTEGER_FLOAT_FACTOR );

	clip->fog = int_fog;
	clip->alpha = int_alpha;
	clip->alpha2 = int_alpha2;
	clip->red = int_red;
	clip->red2 = int_red2;
	clip->green = int_green;
	clip->green2 = int_green2;
	clip->blue = int_blue;
	clip->blue2 = int_blue2;

	clip->i = point2->i + ( t * ( point2->i - point1->i ) );
	clip->j = active_viewport.y_max;
	clip->q = point2->q + ( t * ( point2->q - point1->q ) );
	clip->z = 1.0 / clip->q;

	clip->u = point2->u + ( t * ( point2->u - point1->u ) );
	clip->v = point2->v + ( t * ( point2->v - point1->v ) );
	clip->u2 = point2->u2 + ( t * ( point2->u2 - point1->u2 ) );
	clip->v2 = point2->v2 + ( t * ( point2->v2 - point1->v2 ) );

	clip->outcode = 0;

#if REPORT_CLIP_STATISTICS

	number_of_ymax_coordinates_inserted++;

#endif
	return ( number_of_clipping_vertices++ );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
