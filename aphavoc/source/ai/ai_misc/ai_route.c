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



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 3 levels of debug

#define DEBUG_MODULE 0

#define SAFE_RADIUS 1

#define CHECK_ROUTE_NODE_HEIGHT 0

#define AI_ROUTE_ROAD_SEARCH 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define ALLIED_SECTOR         0

#define ENEMY_SECTOR          2

#define FRONT_LINE_SECTOR     1

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int read_road_route_node_data (unsigned char *name);

static int read_road_route_node_positions (unsigned char *name);

static int read_road_route_node_link_positions (unsigned char *name);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

node_data
   *road_nodes;

vec3d
   *road_node_positions;

node_link_data
   *road_node_link_positions;

int
   duplicate_count = 0,
	road_nodes_loaded;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
   total_road_node_link_count,
   total_number_of_road_nodes,
   best_recurse_level = INT_MAX,
   current_route [MAX_ROUTE_LENGTH],
   best_route [MAX_ROUTE_LENGTH];

entity
	**ground_landing_entities;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_route_data (void)
{

	deinitialise_route_data ();

   #if DEBUG_MODULE

   debug_log ("ROUTE: Initialise ");

   #endif

	road_nodes_loaded = FALSE;

   road_node_link_positions = NULL;
   road_node_positions = NULL;
   road_nodes = NULL;

   total_road_node_link_count = 0;

   total_number_of_road_nodes = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void load_route_data (void)
{
	deinitialise_road_route_data ();

	read_road_route_data ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_route_data (void)
{

   #if DEBUG_MODULE

   debug_log ("ROUTE: Deinitialise");

   #endif

	deinitialise_road_route_data ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_road_route_data (void)
{

   int
      loop;

   //
   // Free road_nodes
   //

   if (road_nodes)
   {
   
      for (loop = 0; loop < total_number_of_road_nodes; loop ++)
      {

         if (road_nodes [loop].links)
         {
   
            free_mem (road_nodes [loop].links);
      
            #if AI_DEBUG
         
            ai_memory_counter --;
         
            #endif
         }
      }
   
      free_mem (road_nodes);

      #if AI_DEBUG
   
		ai_memory_counter --;
	
		#endif
	}

	//
	// Free node road_node_link_positions
	//

	if (road_node_positions)
	{

		free_mem (road_node_positions);

		#if AI_DEBUG
	
		ai_memory_counter --;
	
		#endif
	}

	//
	// Free all road_node_link_positions for node links
	//

	if (road_node_link_positions)
	{
	
		for (loop = 0; loop < total_road_node_link_count; loop ++)
		{

			if (road_node_link_positions [loop].number_of_links > 0)
			{

				ASSERT (road_node_link_positions [loop].link_positions);
	
				free_mem (road_node_link_positions [loop].link_positions);
		
				#if AI_DEBUG
			
				ai_memory_counter --;
			
				#endif
			}
		}
	
		free_mem (road_node_link_positions);

		#if AI_DEBUG
	
		ai_memory_counter --;
	
		#endif
	}

   road_node_link_positions = NULL;
   road_node_positions = NULL;
   road_nodes = NULL;

   total_road_node_link_count = 0;
   total_number_of_road_nodes = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void read_road_route_data (void)
{

	#if DEBUG_MODULE

	debug_log ("AI_ROUTE: loading road node database");

	#endif

   if (read_road_route_node_data ("ROADS"))
	{
	   read_road_route_node_positions ("ROADS");

   	read_road_route_node_link_positions ("ROADS");
	}
	else if (read_road_route_node_data ("ROADDATA"))
	{
	   read_road_route_node_positions ("ROADDATA");

   	read_road_route_node_link_positions ("ROADDATA");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Data format:
//
// Number of nodes
// loop 	{
//				node_id,
//				number_of_links
//				list of links
//			}
//

int read_road_route_node_data (unsigned char *name)
{

	int
		loop,
		value;

	float
		fvalue;

   FILE
      *file_ptr;

   int
      number_of_road_nodes;

   node_data
      *new_node;

	char
		filename [1024];

	ASSERT (get_valid_current_game_session ());

	sprintf (filename, "%s\\route\\%s%s", current_game_session->data_path, name, ROUTE_NODE_DATA_EXTENSION);

	if (file_exist (filename))
	{
	
		file_ptr = safe_fopen (filename, "rb");
	
		duplicate_count = 0;
	
		//
		// malloc array of number of road_nodes
		//

		// read map sizes
		safe_fread (&fvalue, 4, 1, file_ptr);
		safe_fread (&fvalue, 4, 1, file_ptr);

		safe_fread (&total_number_of_road_nodes, 4, 1, file_ptr);

		number_of_road_nodes = total_number_of_road_nodes;

		if (number_of_road_nodes == 0)
		{

			fclose (file_ptr);

			return FALSE;
		}

		road_nodes = (node_data *) malloc_heap_mem (sizeof (node_data) * number_of_road_nodes);

		memset (road_nodes, 0, sizeof (node_data) * number_of_road_nodes);

		#if AI_DEBUG
	
		ai_memory_counter ++;
	
		#endif

		new_node = road_nodes;

		total_road_node_link_count = 0;

		while (number_of_road_nodes)
		{

			safe_fread (&value, 4, 1, file_ptr);
			new_node->node = value;

			#if SAFE_RADIUS
				
			safe_fread (&value, 4, 1, file_ptr);
//			new_node->safe_radius = value;

			#endif

			// override - DL
			new_node->safe_radius = 28;
				
			safe_fread (&value, 4, 1, file_ptr);
			new_node->number_of_links = value;

			new_node->visited = MAX_ROUTE_LENGTH;
	
			new_node->links = (link_data *) malloc_heap_mem (sizeof (link_data) * ((new_node->number_of_links) + 1));

			memset (new_node->links, 0, sizeof (link_data) * ((new_node->number_of_links) + 1));
	
			#if AI_DEBUG
		
			ai_memory_counter ++;
		
			#endif

			for (loop = 0; loop < new_node->number_of_links; loop ++)
			{

				safe_fread (&value, 4, 1, file_ptr);
				new_node->links [loop].node = value;

				safe_fread (&value, 4, 1, file_ptr);
				new_node->links [loop].cost = value;

				new_node->links [loop].breaks = 0;
			}
	
			number_of_road_nodes --;

			#if DEBUG_MODULE >= 2
			{

				int
					loop,
					loop2;
	
				//
				// debug check for duplicate link descriptions
				//
	
				for (loop = 0; loop < new_node->number_of_links; loop ++)
				{
	
					for (loop2 = 0; loop2 < new_node->number_of_links; loop2 ++)
					{
	
						if ((loop != loop2) && (new_node->links [loop].node == new_node->links [loop2].node))
						{
	
							debug_log ("ROUTE: CHECK DUPLICATE ROUTE DESCRIPTION BETWEEN %d AND %d", new_node->node, new_node->links [loop].node);
						}
					}
				}
			}
			#endif

			new_node ++;
		}

		fclose (file_ptr);

		//
		// debug check for duplicate link descriptions
		//

		#if 0
		for (loop = 0; loop < total_number_of_road_nodes; loop ++)
		{

			count = 0;

			other_count = 0;

			for (loop2 = 0; loop2 < road_nodes [loop].number_of_links; loop2 ++)
			{

				for (loop3 = 0; loop3 < road_nodes [loop].number_of_links; loop3 ++)
				{

					if ((loop2 != loop3) && (road_nodes [loop].links [loop2].node == road_nodes [loop].links [loop3].node))
					{

						count ++;

						other_count = 0;

						for (loop4 = 0; loop4 < road_nodes [road_nodes [loop].links [loop2].node].number_of_links; loop4 ++)
						{

							if (road_nodes [road_nodes [loop].links [loop2].node].links [loop4].node == road_nodes [loop].node)
							{

								if (road_nodes [road_nodes [loop].links [loop2].node].node != road_nodes [loop].node)
								{

									other_count ++;
								}
							}
						}
					}
				}
			}

			if (count != other_count)
			{

				duplicate_count += 2;

				#if DEBUG_MODULE

				debug_log ("ROUTE: DUPLICATE ROUTE DESCRIPTION IN NODE %d, dup = %d", road_nodes [loop].node, duplicate_count);

				#endif
			}
		}

		#endif

		return TRUE;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Data format
//
// Number of nodes
// list of vec3d positions
//

int read_road_route_node_positions (unsigned char *name)
{

   FILE
      *file_ptr;

   int
      number_of_road_nodes;

	char
		filename [1024];

	ASSERT (get_valid_current_game_session ());

	sprintf (filename, "%s\\route\\%s%s", current_game_session->data_path, name, ROUTE_NODE_POSITIONS_EXTENSION);

	ASSERT (file_exist (filename));

	file_ptr = safe_fopen (filename, "rb");

	safe_fread (&number_of_road_nodes, 4, 1, file_ptr);

	ASSERT (number_of_road_nodes == total_number_of_road_nodes);

	if (number_of_road_nodes == 0)
	{

		fclose (file_ptr);

		return FALSE;
	}

	road_node_positions = (vec3d *) malloc_heap_mem (sizeof (vec3d) * number_of_road_nodes);

	memset (road_node_positions, 0, sizeof (vec3d) * number_of_road_nodes);

	#if AI_DEBUG

	ai_memory_counter ++;

	#endif

	safe_fread (road_node_positions, sizeof (vec3d) * number_of_road_nodes, 1, file_ptr);

	fclose (file_ptr);

	#if CHECK_ROUTE_NODE_HEIGHT
	{

		int
			loop;

		float
			terrain_elevation;

		for (loop = 0; loop < number_of_road_nodes; loop ++)
		{

			terrain_elevation = get_3d_terrain_elevation (road_node_positions [loop].x, road_node_positions [loop].z);

			if (terrain_elevation > road_node_positions [loop].y)
			{

				debug_log ("AI_ROUTE: warning, road node %d below terrain", loop);
			}
			else if (terrain_elevation < road_node_positions [loop].y)
			{

				debug_log ("AI_ROUTE: warning, road node %d above terrain", loop);
			}

			road_node_positions [loop].y = terrain_elevation;
		}
	}
	#endif

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Data format
//
// Source
// Destination
// Number of links
// List of node_link_data for each position and cost.
//

int read_road_route_node_link_positions (unsigned char *name)
{

   FILE
      *file_ptr;

   int
		value,
		loop,
      count;

   node_link_data
      *new_link;

	char
		filename [1024];

	ASSERT (get_valid_current_game_session ());

	sprintf (filename, "%s\\route\\%s%s", current_game_session->data_path, name, ROUTE_NODE_LINK_POSITION_DATA_EXTENSION);

	ASSERT (file_exist (filename));

	file_ptr = safe_fopen (filename, "rb");

	//
	// read in number of links
	//

	safe_fread (&total_road_node_link_count, 4, 1, file_ptr);

	if (total_road_node_link_count == 0)
	{

		fclose (file_ptr);

		return FALSE;
	}

	road_node_link_positions = (node_link_data *) malloc_heap_mem (sizeof (node_link_data) * total_road_node_link_count);

	memset (road_node_link_positions, 0, sizeof (node_link_data) * total_road_node_link_count);

	#if AI_DEBUG

	ai_memory_counter ++;

	#endif

	new_link = road_node_link_positions;

	count = total_road_node_link_count;

	#if AI_DEBUG

	debug_log ("ROUTE: node link count %d", total_road_node_link_count);

	#endif

	while (count)
	{

		safe_fread (&value, 4, 1, file_ptr);
		new_link->source = value;
			
		safe_fread (&value, 4, 1, file_ptr);
		new_link->destination = value;

		safe_fread (&value, 4, 1, file_ptr);
		new_link->path_type = value;

		safe_fread (&value, 4, 1, file_ptr);
		new_link->number_of_links = value;

		if (new_link->number_of_links > 0)
		{

			new_link->link_positions = (vec3d *) malloc_heap_mem (sizeof (vec3d) * (new_link->number_of_links + 2));
	
			#if AI_DEBUG
		
			ai_memory_counter ++;
		
			#endif
	
			safe_fread (&new_link->link_positions [1], sizeof (vec3d) * new_link->number_of_links, 1, file_ptr);

			new_link->link_positions [0] = road_node_positions [new_link->source];
			new_link->link_positions [new_link->number_of_links + 1] = road_node_positions [new_link->destination];

			new_link->number_of_links += 2;
		}

		//
		// Safeguard to keep link road road_nodes on map
		//

		for (loop = 0; loop < new_link->number_of_links; loop ++)
		{

			new_link->link_positions [loop].x = bound (new_link->link_positions [loop].x, 0, MAX_MAP_X);

			new_link->link_positions [loop].z = bound (new_link->link_positions [loop].z, 0, MAX_MAP_Z);

			#if CHECK_ROUTE_NODE_HEIGHT
			{
				float
					terrain_elevation;

				terrain_elevation = get_3d_terrain_elevation (new_link->link_positions [loop].x, new_link->link_positions [loop].z);
	
				if (terrain_elevation > new_link->link_positions [loop].y)
				{
	
					debug_log ("AI_ROUTE: warning, between node %d and %d (sub_node %d) below terrain", new_link->source, new_link->destination, loop);
				}
				else if (terrain_elevation < new_link->link_positions [loop].y)
				{
	
					debug_log ("AI_ROUTE: warning, between node %d and %d (sub_node %d) above terrain", new_link->source, new_link->destination, loop);
				}
			}
			#endif
		}

		new_link ++;

		count --;
	}

	fclose (file_ptr);

	road_nodes_loaded = TRUE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void clear_road_route_data (void)
{

	int
		loop;

	if (!get_road_nodes_loaded ())
	{

		return;
	}

	best_recurse_level = 0;

	//
	// initialise node visited data
	//

	if (road_nodes)
	{
	
		for (loop = 0; loop < total_number_of_road_nodes; loop ++)
		{
	
			road_nodes [loop].visited = MAX_ROUTE_LENGTH;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// road routing system
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

node_link_data *get_road_link_data (int node1, int node2)
{

	int
		loop;

	//
	// check database loaded
	//

	ASSERT (road_nodes);
	ASSERT (road_node_positions);
	ASSERT (road_node_link_positions);

	if (!get_road_nodes_loaded ())
	{

		debug_fatal ("AI_ROUTE: data not loaded");
	}

	//
	// Easy case
	//

	if (node1 == node2)
	{

		return NULL;
	}

	//
	// correct order
	//

	if (node1 > node2)
	{

		int
			temp;

		temp = node1;

		node1 = node2;

		node2 = temp;
	}

	//
	// Search for route
	//

	for (loop = (total_road_node_link_count - 1); loop >= 0; loop --)
	{

		//
		// setup index pointers for forward wp list
		//

		if ((road_node_link_positions [loop].source == node1) && (road_node_link_positions [loop].destination == node2))
		{

			return &road_node_link_positions [loop];
		}
	}

	debug_log ("AI_ROUTE: Warning! Link between %d and %d not found", node1, node2);

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

node_link_data *get_road_sub_route (int node1, int node2, int *count, node_link_data *start_route)
{

	int
		loop;

	//
	// check database loaded
	//

	ASSERT (road_nodes);
	ASSERT (road_node_positions);
	ASSERT (road_node_link_positions);

	if (!get_road_nodes_loaded ())
	{

		debug_fatal ("AI_ROUTE: data not loaded");
	}

	//
	// Easy case
	//

	if (node1 == node2)
	{

		return NULL;
	}

	//
	// correct order
	//

	if (node1 > node2)
	{

		int
			temp;

		temp = node1;

		node1 = node2;

		node2 = temp;
	}

	//
	// zip to start_route position
	//

	while (TRUE)
	{
	
		loop = total_road_node_link_count - 1;
	
		if (start_route)
		{
		
			for (; loop >= 0; loop --)
			{
		
				//
				// setup index pointers for forward wp list
				//
		
				if (&road_node_link_positions [loop] == start_route)
				{

					loop --;
		
					break;
				}
			}
		}
	
		//
		// Search for route
		//
	
		for (; loop >= 0; loop --)
		{
	
			//
			// setup index pointers for forward wp list
			//
	
			if ((road_node_link_positions [loop].source == node1) && (road_node_link_positions [loop].destination == node2))
			{
	
				*count = road_node_link_positions [loop].number_of_links;
	
				return &road_node_link_positions [loop];
			}
		}

		if (start_route)
		{

			start_route = NULL;
		}
		else
		{

			break;
		}
	}

	*count = 0;

	#if 0

	debug_log ("AI_ROUTE: Warning ! Null sub route between %d and %d", node1, node2);

	debug_log ("      node %d links to :", node1);

	for (loop = 0; loop < road_nodes [node1].number_of_links; loop ++)
	{

		debug_log ("      node %d %f km", road_nodes [node1].links [loop].node, road_nodes [node1].links [loop].cost);
	}

	for (loop = 0; loop < total_road_node_link_count; loop ++)
	{

		if (road_node_link_positions [loop].source == node1)
		{

			debug_log ("      found link for %d to %d", node1, road_node_link_positions [loop].destination);
		}

		if (road_node_link_positions [loop].destination == node1)
		{

			debug_log ("      found link for %d to %d", road_node_link_positions [loop].source, node1);
		}
	}

	debug_log ("      node %d links to :", node2);

	for (loop = 0; loop < road_nodes [node2].number_of_links; loop ++)
	{

		debug_log ("      node %d %f km", road_nodes [node2].links [loop].node, road_nodes [node2].links [loop].cost);
	}

	for (loop = 0; loop < total_road_node_link_count; loop ++)
	{

		if (road_node_link_positions [loop].source == node2)
		{

			debug_log ("      found link for %d to %d", node2, road_node_link_positions [loop].destination);
		}

		if (road_node_link_positions [loop].destination == node2)
		{

			debug_log ("      found link for %d to %d", road_node_link_positions [loop].source, node2);
		}
	}

	#endif

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int set_road_link_breaks (int node1, int node2, int count)
{

	int
		loop;

	ASSERT (road_nodes);
	ASSERT (road_node_positions);

	//
	// Set valid node1 -> node2 link
	//

	if (count > 32)
	{

		debug_fatal ("AI_ROUTE: too many bridges destroyed on link between %d and %d (max 32)", node1, node2);
	}

	for (loop = 0; loop < road_nodes [node1].number_of_links; loop ++)
	{

		if (road_nodes [node1].links [loop].node == node2)
		{

			road_nodes [node1].links [loop].breaks = count;

			//
			// Set valid node2 -> node1 link
			//

			for (loop = 0; loop < road_nodes [node2].number_of_links; loop ++)
			{

				if (road_nodes [node2].links [loop].node == node1)
				{
	
					road_nodes [node2].links [loop].breaks = count;

					return TRUE;
				}
			}

			debug_fatal ("AI_ROUTE: only found 1 way link between %d and %d", node1, node2);
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_road_link_breaks (int node1, int node2)
{

	int
		loop2,
		loop;

	ASSERT (road_nodes);
	ASSERT (road_node_positions);

	//
	// find node 1
	//

	for (loop = 0; loop < road_nodes [node1].number_of_links; loop ++)
	{

		if (road_nodes [node1].links [loop].node == node2)
		{

			//
			// Check that node2 has same valid flag
			//
	
			for (loop2 = 0; loop2 < road_nodes [node2].number_of_links; loop2 ++)
			{
	
				if (road_nodes [node2].links [loop2].node == node1)
				{

					ASSERT (road_nodes [node1].links [loop].breaks == road_nodes [node2].links [loop2].breaks);
	
					return road_nodes [node1].links [loop].breaks;
				}
			}
		}
	}

	return -1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_SAFE_RADIUS_CHECK (50 * KILOMETRE)
/*
void initialise_road_safe_radius (void)
{

	int
		safe,
		loop;

	float
		segment_size,
		radius,
		angle,
		x,
		z;

	terrain_3d_find_fast
		terrain_cache;

	ASSERT (road_nodes);
	ASSERT (road_node_positions);
	ASSERT (road_node_link_positions);

	memset (&terrain_cache, 0, sizeof (terrain_3d_find_fast));

	segment_size = (float) PI2 / 4;

	for (loop = 0; loop < total_number_of_road_nodes; loop ++)
	{

		//
		// do radius check for forest floor
		//

		safe = TRUE;

		for (radius = 0; ((radius < MAX_SAFE_RADIUS_CHECK) && (safe)); radius ++)
		{

			for (angle = 0.0; ((angle < PI2) && (safe)); angle += segment_size)
			{

				x = road_node_positions [loop].x + (sin (angle) * radius);
				z = road_node_positions [loop].z + (cos (angle) * radius);

				if ((x <= MIN_MAP_X) || (x >= MAX_MAP_X) || (z <= MIN_MAP_Z) || (z >= MAX_MAP_Z))
				{

					safe = FALSE;
				}
				else
				{
			
					get_3d_terrain_elevation_and_face_normal (x, z, NULL, &terrain_cache);
			
					safe = get_terrain_type_suitable_for_ground_vehicle (terrain_cache.terrain_type);
				}
			}
		}

		debug_log ("AI_ROUTE: safe radius for node %d is %f", loop, radius);

		road_nodes [loop].safe_radius = radius;
	}
}
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_route_node_data_filename (char **route_node_data_filename, const char *filename)
{

	if (*route_node_data_filename)
	{

		free_mem (*route_node_data_filename);

		*route_node_data_filename = NULL;
	}

	*route_node_data_filename = (char *) malloc_heap_mem (sizeof (char) * (strlen (filename) + 1));

	strcpy (*route_node_data_filename, filename);

	#if DEBUG_MODULE

	debug_log ("AI_ROUTE: setting database(%d) filename to %s", *route_node_data_filename, filename);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
