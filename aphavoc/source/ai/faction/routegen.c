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



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_WAYPOINT_NODES 768

#define MAX_WAYPOINT_LINKS 24

#define MAX_WAYPOINT_STARTS 24

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct WAYPOINT_NODE
{

	int
		tree_depth,
		tree_number,
		node_index,
		number_of_children,
		number_of_parents,
		primary,
		start,
		possible_start,
		references,
		in_route,
		processed;

	vec3d
		position;

	struct WAYPOINT_NODE
		*parents[MAX_WAYPOINT_LINKS],
		*children[MAX_WAYPOINT_LINKS];
};

typedef struct WAYPOINT_NODE waypoint_node;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

waypoint_node
	waypoint_nodes[MAX_WAYPOINT_NODES],
	*waypoint_starting_nodes[MAX_WAYPOINT_STARTS];

int
	number_of_waypoint_nodes,
	number_of_waypoint_starting_nodes;

int
	number_of_route_waypoint_positions;

route_waypoint_position
	*route_waypoint_positions;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_number_of_nodes_at_depth ( int tree_depth );

int get_waypoint_node_child_index ( waypoint_node *parent, waypoint_node *child );

static void set_node_indices ( void );

static void match_end_slots ( int tree_depth, int number_of_matching_slots, vec3d *slots );

static int node_within_range ( vec3d *pos1, vec3d *pos2 );

static void swap_waypoint_nodes ( int node, int other_node );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_routegen_waypoint_routes ( void )
{

	int
		count;

	if ( number_of_route_waypoint_positions )
	{

		for ( count = 0; count < number_of_route_waypoint_positions; count++ )
		{

			safe_free ( route_waypoint_positions[count].offsets );
		}

		safe_free ( route_waypoint_positions );

		route_waypoint_positions = NULL;

		number_of_route_waypoint_positions = 0;
	}

	number_of_waypoint_starting_nodes = 0;

	for ( count = 0; count < MAX_WAYPOINT_STARTS; count++ )
	{

		waypoint_starting_nodes[count] = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void parse_waypoint_routes_from_object ( int object_index, int number_of_matching_slots, vec3d *slots )
{

	int
		surface,
		count,
		number_of_primary_nodes,
		number_of_nodes_left,
		number_of_primary_nodes_left,
		maximum_tree_depth,
		current_depth;

	struct POINT_3D_SHORT_REFERENCE
		*point_refs;

	struct POINT_3D_PLAIN_REFERENCE
		*surface_point_refs;

	object_3d_face
		*faces;

	//
	// Copy the point data into each node.
	//

	number_of_waypoint_nodes = objects_3d_data[object_index].number_of_points;

	ASSERT ( number_of_waypoint_nodes < MAX_WAYPOINT_NODES );

	{

		float
			xmax,
			ymax,
			zmax;
	
		xmax = max ( fabs ( objects_3d_data[object_index].bounding_box.xmin ), fabs ( objects_3d_data[object_index].bounding_box.xmax ) );
		ymax = max ( fabs ( objects_3d_data[object_index].bounding_box.ymin ), fabs ( objects_3d_data[object_index].bounding_box.ymax ) );
		zmax = max ( fabs ( objects_3d_data[object_index].bounding_box.zmin ), fabs ( objects_3d_data[object_index].bounding_box.zmax ) );

		for ( count = 0; count < number_of_waypoint_nodes; count++ )
		{
	
			int
				loop;
	
			waypoint_nodes[count].tree_depth = -1;
			waypoint_nodes[count].tree_number = -1;
			waypoint_nodes[count].node_index = -1;
			waypoint_nodes[count].number_of_children = 0;
			waypoint_nodes[count].number_of_parents = 0;
			waypoint_nodes[count].primary = FALSE;
			waypoint_nodes[count].start = FALSE;
			waypoint_nodes[count].possible_start = FALSE;
			waypoint_nodes[count].references = 0;
			waypoint_nodes[count].in_route = FALSE;
			waypoint_nodes[count].processed = FALSE;
			waypoint_nodes[count].position.x = objects_3d_data[object_index].points[count].x;
			waypoint_nodes[count].position.y = objects_3d_data[object_index].points[count].y;
			waypoint_nodes[count].position.z = objects_3d_data[object_index].points[count].z;

			waypoint_nodes[count].position.x *= xmax / 32767;
			waypoint_nodes[count].position.y *= ymax / 32767;
			waypoint_nodes[count].position.z *= zmax / 32767;
	
			for ( loop = 0; loop < MAX_WAYPOINT_LINKS; loop++ )
			{
	
				waypoint_nodes[count].parents[loop] = NULL;
			}
	
			for ( loop = 0; loop < MAX_WAYPOINT_LINKS; loop++ )
			{
	
				waypoint_nodes[count].children[loop] = NULL;
			}
		}
	}

	//
	// Set the attributes on each node
	//

	surface_point_refs = objects_3d_data[object_index].surface_points;

	point_refs = objects_3d_data[object_index].object_faces_point_plain_list;

	faces = objects_3d_data[object_index].faces;

	number_of_primary_nodes = 0;

	for ( surface = 0; surface < objects_3d_data[object_index].number_of_surfaces; surface++ )
	{

		int
			number_of_surface_points;

		ASSERT ( !objects_3d_data[object_index].surfaces[surface].polygons );

		number_of_surface_points = objects_3d_data[object_index].surfaces[surface].number_of_points;

		if ( number_of_surface_points == 0 )
		{

			number_of_surface_points = 256;
		}

		for ( count = 0; count < objects_3d_data[object_index].surfaces[surface].number_of_faces; count++ )
		{

			int
				point0,
				point1;

			//
			// Add the point reference counts
			//

			point0 = surface_point_refs[ point_refs[0].point ].point;
			point1 = surface_point_refs[ point_refs[1].point ].point;

			waypoint_nodes[point0].references++;
			waypoint_nodes[point1].references++;

			//
			// Set attributes on the nodes
			//

			if (	( objects_3d_data[object_index].surfaces[surface].green == 0 ) &&
					( objects_3d_data[object_index].surfaces[surface].blue == 0 ) &&
					( objects_3d_data[object_index].surfaces[surface].red == 0 ) )
			{

				waypoint_nodes[point0].possible_start = TRUE;
				waypoint_nodes[point1].possible_start = TRUE;
			}
			else if (	( objects_3d_data[object_index].surfaces[surface].green == 255 ) &&
							( objects_3d_data[object_index].surfaces[surface].blue == 0 ) &&
							( objects_3d_data[object_index].surfaces[surface].red == 0 ) )
			{

				number_of_primary_nodes++;

				waypoint_nodes[point0].primary = TRUE;
				waypoint_nodes[point1].primary = TRUE;
			}

			point_refs += 2;
		}

		surface_point_refs += number_of_surface_points;
	}

//	ASSERT ( number_of_primary_nodes );

	//
	// Now go through setting up the start nodes
	//

	number_of_nodes_left = number_of_waypoint_nodes;

	number_of_waypoint_starting_nodes = 0;

	for ( count = 0; count < number_of_waypoint_nodes; count++ )
	{

		if ( ( waypoint_nodes[count].possible_start ) && ( waypoint_nodes[count].references == 1 ) )
		{

			waypoint_nodes[count].start = TRUE;
			waypoint_nodes[count].in_route = TRUE;
			waypoint_nodes[count].tree_depth = 0;
			waypoint_nodes[count].tree_number = number_of_waypoint_starting_nodes;

			ASSERT ( number_of_waypoint_starting_nodes < MAX_WAYPOINT_STARTS );

			waypoint_starting_nodes[number_of_waypoint_starting_nodes] = &waypoint_nodes[count];

			number_of_waypoint_starting_nodes++;

			number_of_nodes_left--;
		}
	}

	//
	// Iteratively add in nodes until we have populated the trees with all the *primary* nodes
	//

	maximum_tree_depth = 0;

	number_of_primary_nodes_left = 0;

	for ( count = 0; count < number_of_waypoint_nodes; count++ )
	{

		if ( ( waypoint_nodes[count].primary ) && ( !waypoint_nodes[count].in_route ) )
		{

			number_of_primary_nodes_left++;
		}
	}

	while ( number_of_primary_nodes_left )
	{

		surface_point_refs = objects_3d_data[object_index].surface_points;
	
		point_refs = objects_3d_data[object_index].object_faces_point_plain_list;
	
		for ( surface = 0; surface < objects_3d_data[object_index].number_of_surfaces; surface++ )
		{
	
			int
				number_of_surface_points;
	
			number_of_surface_points = objects_3d_data[object_index].surfaces[surface].number_of_points;
	
			if ( number_of_surface_points == 0 )
			{
	
				number_of_surface_points = 256;
			}
	
			for ( count = 0; count < objects_3d_data[object_index].surfaces[surface].number_of_faces; count++ )
			{
	
				int
					point0,
					point1,
					add_node_flag,
					parent,
					child;
	
				point0 = surface_point_refs[ point_refs[0].point ].point;
				point1 = surface_point_refs[ point_refs[1].point ].point;
	
				//
				// If one node referenced is in the route system & one isn't - add the one that isn't
				//
	
				add_node_flag = FALSE;
	
				if ( ( waypoint_nodes[point0].in_route ) && ( !waypoint_nodes[point1].in_route ) )
				{
	
					if (	( ( waypoint_nodes[point0].primary ) || ( waypoint_nodes[point0].start ) ) &&
							( waypoint_nodes[point1].primary ) )
					{
	
						add_node_flag = TRUE;
						parent = point0;
						child = point1;
					}
				}
				else if ( ( waypoint_nodes[point1].in_route ) && ( !waypoint_nodes[point0].in_route ) )
				{
	
					if (	( ( waypoint_nodes[point1].primary ) || ( waypoint_nodes[point1].start ) ) &&
							( waypoint_nodes[point0].primary ) )
					{
		
						add_node_flag = TRUE;
						parent = point1;
						child = point0;
					}
				}
	
				if ( add_node_flag )
				{
	
					int
						number_of_children,
						number_of_parents;
	
					number_of_children = waypoint_nodes[parent].number_of_children;
					number_of_parents = waypoint_nodes[child].number_of_parents;
	
					waypoint_nodes[parent].children[number_of_children] = &waypoint_nodes[child];
					waypoint_nodes[parent].number_of_children++;
	
					waypoint_nodes[child].parents[number_of_parents] = &waypoint_nodes[parent];
					waypoint_nodes[child].number_of_parents++;
					waypoint_nodes[child].in_route = TRUE;
					waypoint_nodes[child].tree_depth = waypoint_nodes[parent].tree_depth+1;
					waypoint_nodes[child].tree_number = waypoint_nodes[parent].tree_number;
	
					if ( waypoint_nodes[child].tree_depth > maximum_tree_depth )
					{
	
						maximum_tree_depth = waypoint_nodes[child].tree_depth;
					}
	
					number_of_nodes_left--;
	
					number_of_primary_nodes_left--;
				}
	
				point_refs += 2;
			}

			surface_point_refs += number_of_surface_points;
		}
	}

	//
	// Iteratively add in nodes until we have populated the trees with ALL the nodes
	//

	while ( number_of_nodes_left )
	{

		surface_point_refs = objects_3d_data[object_index].surface_points;
	
		point_refs = objects_3d_data[object_index].object_faces_point_plain_list;
	
		for ( surface = 0; surface < objects_3d_data[object_index].number_of_surfaces; surface++ )
		{
	
			int
				number_of_surface_points;
	
			number_of_surface_points = objects_3d_data[object_index].surfaces[surface].number_of_points;
	
			if ( number_of_surface_points == 0 )
			{
	
				number_of_surface_points = 256;
			}
	
			for ( count = 0; count < objects_3d_data[object_index].surfaces[surface].number_of_faces; count++ )
			{
	
				int
					point0,
					point1,
					add_node_flag,
					parent,
					child;
	
				point0 = surface_point_refs[ point_refs[0].point ].point;
				point1 = surface_point_refs[ point_refs[1].point ].point;
	
				//
				// If one node referenced is in the route system & one isn't - add the one that isn't
				//
	
				add_node_flag = FALSE;
	
				if ( ( waypoint_nodes[point0].in_route ) && ( !waypoint_nodes[point1].in_route ) )
				{
	
					add_node_flag = TRUE;
					parent = point0;
					child = point1;
				}
				else if ( ( waypoint_nodes[point1].in_route ) && ( !waypoint_nodes[point0].in_route ) )
				{
	
					add_node_flag = TRUE;
					parent = point1;
					child = point0;
				}
	
				if ( add_node_flag )
				{
	
					int
						number_of_children,
						number_of_parents;
	
					number_of_children = waypoint_nodes[parent].number_of_children;
					number_of_parents = waypoint_nodes[child].number_of_parents;
	
					waypoint_nodes[parent].children[number_of_children] = &waypoint_nodes[child];
					waypoint_nodes[parent].number_of_children++;
	
					waypoint_nodes[child].parents[number_of_parents] = &waypoint_nodes[parent];
					waypoint_nodes[child].number_of_parents++;
					waypoint_nodes[child].in_route = TRUE;
					waypoint_nodes[child].tree_depth = waypoint_nodes[parent].tree_depth+1;
					waypoint_nodes[child].tree_number = waypoint_nodes[parent].tree_number;
	
					if ( waypoint_nodes[child].tree_depth > maximum_tree_depth )
					{
	
						maximum_tree_depth = waypoint_nodes[child].tree_depth;
					}
	
					number_of_nodes_left--;
				}
	
				point_refs += 2;
			}

			surface_point_refs += number_of_surface_points;
		}
	}

	//
	// Rearrange the starting nodes depending on which one is the primary one
	//

	for ( count = 0; count < number_of_waypoint_nodes; count++ )
	{

		if ( waypoint_nodes[count].primary )
		{

			waypoint_node
				*this_node;

			//
			// Follow route up to top
			//

			this_node = waypoint_nodes[count].parents[0];

			while ( this_node )
			{

				this_node->primary = TRUE;

				this_node = this_node->parents[0];
			}
		}
	}

	if ( !waypoint_starting_nodes[0]->primary )
	{

		int
			primary_start_index;

		waypoint_node
			*tmp;

		for ( count = 1; count < number_of_waypoint_starting_nodes; count++ )
		{

			if ( waypoint_starting_nodes[count]->primary )
			{

				primary_start_index = count;
			}
		}


		tmp = waypoint_starting_nodes[0];
		waypoint_starting_nodes[0] = waypoint_starting_nodes[primary_start_index];
		waypoint_starting_nodes[primary_start_index] = tmp;
	}

	//
	// Go through each tree setting the main route node index
	//

	for ( count = 0; count < number_of_waypoint_starting_nodes; count++ )
	{

		waypoint_node
			*this_node;

		this_node = waypoint_starting_nodes[count];

		while ( this_node )
		{

			this_node->node_index = count;

			this_node = this_node->children[0];
		}
	}

	//
	// Set all the other node indices
	//

	set_node_indices ();

	if ( number_of_matching_slots )
	{

		match_end_slots ( maximum_tree_depth, number_of_matching_slots, slots );
	}

	//
	// Construct the table of vec3d stuff
	//

	number_of_route_waypoint_positions = maximum_tree_depth + 1;

	route_waypoint_positions = safe_malloc ( number_of_route_waypoint_positions * sizeof ( route_waypoint_position ) );

	memset ( route_waypoint_positions, 0, ( number_of_route_waypoint_positions * sizeof ( route_waypoint_position ) ) );

	for ( current_depth = 0; current_depth <= maximum_tree_depth; current_depth++ )
	{

		int
			finished,
			number_of_nodes,
			node_index;

		finished = FALSE;

		node_index = 0;

		number_of_nodes = get_number_of_nodes_at_depth ( current_depth );

		route_waypoint_positions[current_depth].number_of_positions = number_of_nodes;

		route_waypoint_positions[current_depth].offsets = safe_malloc ( number_of_nodes * sizeof ( vec3d ) );

		while ( number_of_nodes )
		{

			for ( count = 0; count < number_of_waypoint_nodes; count++ )
			{

				if (	( waypoint_nodes[count].tree_depth == current_depth ) &&
						( waypoint_nodes[count].node_index == node_index ) &&
						( !waypoint_nodes[count].processed ) )
				{

					route_waypoint_positions[current_depth].offsets[node_index].x = waypoint_nodes[count].position.x;
					route_waypoint_positions[current_depth].offsets[node_index].y = waypoint_nodes[count].position.y;
					route_waypoint_positions[current_depth].offsets[node_index].z = waypoint_nodes[count].position.z;

					waypoint_nodes[count].processed = TRUE;

					node_index++;

					number_of_nodes--;
				}
			}
		}
	}

	//
	// Turn all the offsets to relative positions
	//

	for ( current_depth = 0; current_depth <= maximum_tree_depth; current_depth++ )
	{

		route_waypoint_positions[current_depth].position = route_waypoint_positions[current_depth].offsets[0];

		for ( count = 0; count < route_waypoint_positions[current_depth].number_of_positions; count++ )
		{

			route_waypoint_positions[current_depth].offsets[count].x -= route_waypoint_positions[current_depth].position.x;
			route_waypoint_positions[current_depth].offsets[count].y -= route_waypoint_positions[current_depth].position.y;
			route_waypoint_positions[current_depth].offsets[count].z -= route_waypoint_positions[current_depth].position.z;
		}
	}
/*
	for ( current_depth = 0; current_depth < maximum_tree_depth; current_depth++ )
	{

		debug_log ( "Node %d ( %d ) : %f, %f, %f", current_depth,
							route_waypoint_positions[current_depth].number_of_positions,
							route_waypoint_positions[current_depth].position.x,
							route_waypoint_positions[current_depth].position.y,
							route_waypoint_positions[current_depth].position.z );

		for ( count = 0; count < route_waypoint_positions[current_depth].number_of_positions; count++ )
		{

			debug_log ( "%f %f %f",
						route_waypoint_positions[current_depth].offsets[count].x,
						route_waypoint_positions[current_depth].offsets[count].y,
						route_waypoint_positions[current_depth].offsets[count].z );
		}
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_waypoint_node_child_index ( waypoint_node *parent, waypoint_node *child )
{

	int
		count;

	for ( count = 0; count < parent->number_of_children; count++ )
	{

		if ( parent->children[count] == child )
		{

			return ( count );
		}
	}

	debug_fatal ( "Unable to find child pointer on parent route node" );

	return ( 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_number_of_nodes_at_depth ( int tree_depth )
{

	int
		total,
		count;

	total = 0;

	for ( count = 0; count < number_of_waypoint_nodes; count++ )
	{

		if ( waypoint_nodes[count].tree_depth == tree_depth )
		{

			total++;
		}
	}

	return ( total );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_node_indices ( void )
{

	int
		number_of_nodes_left,
		count;

	//
	// Count the number of nodes that haven't been given a valid node index
	//

	number_of_nodes_left = 0;

	for ( count = 0; count < number_of_waypoint_nodes; count++ )
	{

		if ( waypoint_nodes[count].node_index == -1 )
		{

			number_of_nodes_left++;
		}
	}

	//
	// Go through all the nodes left setting the node indices
	//

	while ( number_of_nodes_left )
	{
	
		for ( count = 0; count < number_of_waypoint_nodes; count++ )
		{
	
			if ( waypoint_nodes[count].node_index == -1 )
			{

				if ( waypoint_nodes[count].number_of_parents == 1 )
				{

					waypoint_node
						*parent;

					parent = waypoint_nodes[count].parents[0];

					if ( parent->node_index != -1 )
					{

						int
							hierarchy_width,
							child_index;

						child_index = get_waypoint_node_child_index ( parent, &waypoint_nodes[count] );

						hierarchy_width = get_number_of_nodes_at_depth ( parent->tree_depth );

						waypoint_nodes[count].node_index = hierarchy_width * child_index + parent->node_index;

						number_of_nodes_left--;
					}
				}
				else
				{

					int
						lowest_parent_index,
						parent_count;

					lowest_parent_index = waypoint_nodes[count].parents[0]->node_index;

					for ( parent_count = 1; parent_count < waypoint_nodes[count].number_of_parents; parent_count++ )
					{

						waypoint_node
							*parent;

						parent = waypoint_nodes[count].parents[parent_count];

						if ( parent->node_index < lowest_parent_index )
						{

							lowest_parent_index = parent->node_index;
						}
					}

					if ( lowest_parent_index != -1 )
					{

						waypoint_nodes[count].node_index = lowest_parent_index;

						number_of_nodes_left--;
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void match_end_slots ( int tree_depth, int number_of_matching_slots, vec3d *slots )
{

	int
		count,
		node,
		other_node,
		finished;

	finished = FALSE;

	while ( !finished )
	{

		//
		// Go through the routes, checking each end point matches the slots given
		//

		finished = TRUE;

		for ( count = 0; count < number_of_matching_slots; count++ )
		{

			for ( node = 0; node < number_of_waypoint_nodes; node++ )
			{

				if ( ( waypoint_nodes[node].tree_depth == tree_depth ) && ( waypoint_nodes[node].node_index == count ) )
				{

					if ( !node_within_range ( &waypoint_nodes[node].position, &slots[count] ) )
					{

						//
						// Find the node we need to swap with this one
						//

						for ( other_node = 0; other_node < number_of_waypoint_nodes; other_node++ )
						{

							if (	( waypoint_nodes[other_node].tree_depth == tree_depth ) &&
									( node_within_range ( &waypoint_nodes[other_node].position, &slots[count] ) ) )
							{

								break;
							}
						}

						if ( other_node != number_of_waypoint_nodes )
						{

							#if DEBUG_MODULE

							debug_log ( "Swapping nodes %d and %d", node, other_node );

							#endif

							swap_waypoint_nodes ( node, other_node );

							finished = FALSE;
						}

						#if DEBUG_MODULE

						else
						{

							debug_log ( "CANT FIND A NODE TO SWAP!!!!! %f, %f, %f", slots[count].x, slots[count].y, slots[count].z );

							for ( other_node = 0; other_node < number_of_waypoint_nodes; other_node++ )
							{


								if ( waypoint_nodes[other_node].tree_depth == tree_depth )
								{

									debug_log ( "NODE: %f, %f, %f",
														waypoint_nodes[other_node].position.x,
														waypoint_nodes[other_node].position.y,
														waypoint_nodes[other_node].position.z );


								}
							}

							debug_fatal ( "ERROR" );
						}

						#endif
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int node_within_range ( vec3d *pos1, vec3d *pos2 )
{

	float
		dx,
		dy,
		dz;

	float
		range;

	dx = pos1->x - pos2->x;
	dy = pos1->y - pos2->y;
	dz = pos1->z - pos2->z;

	range = sqrt ( ( dx * dx ) + ( dy * dy ) + ( dz * dz ) );

	if ( range < 3.0 )
	{

		return ( TRUE );
	}
	else
	{

		return ( FALSE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void swap_waypoint_nodes ( int node, int other_node )
{

	int
		found,
		count,
		child_index,
		other_child_index;

	waypoint_node
		*child,
		*other_child,
		*common_parent;

	//
	// Find the common parent of these two nodes.
	//

	found = FALSE;

	child = &waypoint_nodes[node];

	other_child = &waypoint_nodes[other_node];

	common_parent = NULL;

	while ( !found )
	{

		if ( ( !child ) || ( !other_child ) )
		{

			debug_fatal ( "Run out of tree!" );
		}

		if ( child->parents[0] == other_child->parents[0] )
		{

			found = TRUE;

			common_parent = child->parents[0];
		}
		else
		{

			child = child->parents[0];

			other_child = other_child->parents[0];
		}
	}

	if ( common_parent )
	{
	
		//
		// Swap the two child pointers around
		//
	
		for ( count = 0; count < common_parent->number_of_children; count++ )
		{
	
			if ( common_parent->children[count] == child )
			{
	
				child_index = count;
			}
	
			if ( common_parent->children[count] == other_child )
			{
	
				other_child_index = count;
			}
		}
	
		common_parent->children[child_index] = other_child;
	
		common_parent->children[other_child_index] = child;
	
		//
		// Now invalidate the node indices of every child below the parents level
		//
	
		for ( count = 0; count < number_of_waypoint_nodes; count++ )
		{
	
			if ( waypoint_nodes[count].tree_depth > common_parent->tree_depth )
			{
	
				if ( waypoint_nodes[count].node_index )
				{
	
					waypoint_nodes[count].node_index = -1;
				}
			}
		}
	}
	else
	{

		//
		// Swap the waypoint starting nodes around!
		//

		for ( child_index = 1; child_index < number_of_waypoint_starting_nodes; child_index++ )
		{

			if ( waypoint_starting_nodes[child_index] == child )
			{

				break;
			}
		}

		for ( other_child_index = 1; other_child_index < number_of_waypoint_starting_nodes; other_child_index++ )
		{

			if ( waypoint_starting_nodes[other_child_index] == other_child )
			{

				break;
			}
		}

		ASSERT ( child_index < number_of_waypoint_starting_nodes );

		ASSERT ( other_child_index < number_of_waypoint_starting_nodes );

		waypoint_starting_nodes[child_index] = other_child;

		waypoint_starting_nodes[other_child_index] = child;

		//
		// Now invalidate all the node indices apart from the primary
		//
	
		for ( count = 0; count < number_of_waypoint_nodes; count++ )
		{
	
			if ( waypoint_nodes[count].node_index )
			{

				waypoint_nodes[count].node_index = -1;
			}
		}

		//
		// Go through each tree setting the main route node index
		//
	
		for ( count = 0; count < number_of_waypoint_starting_nodes; count++ )
		{
	
			waypoint_node
				*this_node;
	
			this_node = waypoint_starting_nodes[count];
	
			while ( this_node )
			{
	
				this_node->node_index = count;
	
				this_node = this_node->children[0];
			}
		}
	}

	//
	// Now renumber the indices ( again )
	//

	set_node_indices ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

