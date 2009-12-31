// Priorty Fire Zones - written by arneh, nov 2006

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Data structures and functions for managing PFZs
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"


#define MAX_PFZS 16
#define MAX_NFZS 4


#define DEBUG_MODULE 0

int current_pfz = NO_PFZ;
unsigned int next_free_pfz = 0, next_free_nfz = 0;


static pfz pfzs[MAX_PFZS];
static pfz nfzs[MAX_NFZS];

#if DEBUG_MODULE
#define debug_print_vec(vec)   debug_log("%s = %.2f, %s = %.2f, %s = %.2f", #vec "->x", (vec)->x, #vec "->y", (vec)->y, #vec "->z", vec->z);
#endif

pfz* get_pfz(unsigned int pfz_number)
{
	ASSERT(pfz_number < next_free_pfz);

	return &pfzs[pfz_number];
}

pfz* get_nfz(unsigned int nfz_number)
{
	ASSERT(nfz_number < next_free_nfz);

	return &nfzs[nfz_number];
}

void delete_pfz(unsigned int pfz_number)
{
	// deletes by moving all following elements one step up to fill the slot

	ASSERT(pfz_number < next_free_pfz);

	memmove(&pfzs[pfz_number], &pfzs[pfz_number+1], (next_free_pfz - pfz_number) * sizeof(pfzs[0]));

	next_free_pfz--;

	if (current_pfz >= next_free_pfz)
		select_previous_pfz();
}

void delete_nfz(unsigned int nfz_number)
{
	ASSERT(nfz_number < next_free_nfz);

	memmove(&nfzs[nfz_number], &nfzs[nfz_number+1], (next_free_nfz - nfz_number) * sizeof(nfzs[0]));

	next_free_nfz--;

	if (!ground_radar_is_active())
		update_common_radar (TRUE);
}

void add_pfz(vec3d* corner1, vec3d* corner2, vec3d* corner3, vec3d* corner4)
{
	if (next_free_pfz == MAX_PFZS)  // if full delete oldest
		delete_pfz(0);

	#if DEBUG_MODULE
	debug_print_vec(corner1);
	debug_print_vec(corner2);
	debug_print_vec(corner3);
	debug_print_vec(corner4);
	#endif

	pfzs[next_free_pfz].corner1 = *corner1;
	pfzs[next_free_pfz].corner2 = *corner2;
	pfzs[next_free_pfz].corner3 = *corner3;
	pfzs[next_free_pfz].corner4 = *corner4;

	next_free_pfz++;
}

void add_nfz(vec3d* corner1, vec3d* corner2, vec3d* corner3, vec3d* corner4)
{
	if (next_free_nfz == MAX_NFZS)  // if full delete oldest
		delete_nfz(0);

	nfzs[next_free_nfz].corner1 = *corner1;
	nfzs[next_free_nfz].corner2 = *corner2;
	nfzs[next_free_nfz].corner3 = *corner3;
	nfzs[next_free_nfz].corner4 = *corner4;

	next_free_nfz++;
}

void relative_position_to_world_coordinate (vec3d* relative_position, vec3d* world_coordinate, matrix3x3 rotation_matrix)
{
	vec3d position_vector;

	multiply_matrix3x3_vec3d(&position_vector, rotation_matrix, relative_position);

	world_coordinate->x = current_flight_dynamics->position.x + position_vector.x;
	world_coordinate->y = 0.0;
	world_coordinate->z = current_flight_dynamics->position.z + position_vector.z;
}

void world_coordinate_to_relative_position (vec3d* world_coordinate, vec3d* relative_vector, matrix3x3 rotation_matrix)
{
	vec3d relative_position;

	relative_position.x = world_coordinate->x - current_flight_dynamics->position.x;
	relative_position.y = 0;
	relative_position.z = world_coordinate->z - current_flight_dynamics->position.z;

	multiply_matrix3x3_vec3d(relative_vector, rotation_matrix, &relative_position);
}


int coordinate_is_inside_pfz(vec3d* coordinate, unsigned int pfz_number, int is_nfz)
{
	if (is_nfz)
	{
		return coordinate_is_inside_square(coordinate,
			&nfzs[pfz_number].corner1, &nfzs[pfz_number].corner2,
			&nfzs[pfz_number].corner3, &nfzs[pfz_number].corner4);
	}
	else
	{
		return coordinate_is_inside_square(coordinate,
			&pfzs[pfz_number].corner1, &pfzs[pfz_number].corner2,
			&pfzs[pfz_number].corner3, &pfzs[pfz_number].corner4);
	}
}

int coordinate_is_inside_square(vec3d* coordinate, vec3d* corner1, vec3d* corner2, vec3d* corner3, vec3d* corner4)
{
	int negative;
	float winding_direction;

	winding_direction = (coordinate->z - corner1->z) * (corner2->x - corner1->x)
					  - (coordinate->x - corner1->x) * (corner2->z - corner1->z);
	negative = (winding_direction < 0);

	winding_direction = (coordinate->z - corner2->z) * (corner3->x - corner2->x)
					  - (coordinate->x - corner2->x) * (corner3->z - corner2->z);
	if ((negative && winding_direction > 0) || (!negative && winding_direction < 0))
		return FALSE;

	winding_direction = (coordinate->z - corner3->z) * (corner4->x - corner3->x)
					  - (coordinate->x - corner3->x) * (corner4->z - corner3->z);
	if ((negative && winding_direction > 0) || (!negative && winding_direction < 0))
		return FALSE;

	winding_direction = (coordinate->z - corner4->z) * (corner1->x - corner4->x)
					  - (coordinate->x - corner4->x) * (corner1->z - corner4->z);
	if ((negative && winding_direction > 0) || (!negative && winding_direction < 0))
		return FALSE;

	return TRUE;
}



void select_next_pfz(void)
{
	if (next_free_pfz)  // there are any PFZs
	{
		current_pfz++;

		if (current_pfz >= next_free_pfz)
			current_pfz = 0;

		if (!ground_radar_is_active())
			update_common_radar (TRUE);
	}
	else
		current_pfz = NO_PFZ;
}

void select_previous_pfz(void)
{
	if (next_free_pfz)  // there are any PFZs
	{
		current_pfz--;

		if (current_pfz <= -1)
			current_pfz = next_free_pfz-1;

		update_common_radar (TRUE);
	}
	else
		current_pfz = NO_PFZ;
}

void deselect_pfz(void)
{
	current_pfz = NO_PFZ;
	if (!ground_radar_is_active())
		update_common_radar (TRUE);
}

void delete_current_pfz(void)
{
	if (current_pfz != NO_PFZ)
		delete_pfz((unsigned int)current_pfz);
}

int is_valid_pfz_target(vec3d* target_position)
{
	int i;

	// If we have an active PFZ check that if position is inside it
	if (current_pfz != NO_PFZ
		&& !coordinate_is_inside_pfz(target_position, current_pfz, FALSE))
	{
		return FALSE;
	}

	// If it is check that it is also not in a No Fire Zone
	for (i=0; i < next_free_nfz; i++)
		if (coordinate_is_inside_pfz(target_position, i, TRUE))
			return FALSE;

	return TRUE;
}

int pfz_active()
{
	return current_pfz != NO_PFZ;
}
