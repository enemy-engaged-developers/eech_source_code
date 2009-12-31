/*
 * ap_stored_point.c
 *
 *  Created on: 12.okt.2009
 *      Author: arneh
 */

#include "project.h"

#include "ap_coordinate_point.h"

#define MAX_NUMBER_OF_ROUTES 10
#define MAX_NUMBER_OF_WAYPOINTS_IN_ROUTE 50

apache_coordinate_points apache_waypoint_hazard_points[NUM_APACHE_WAYPOINT_CM_POINTS];
apache_coordinate_points apache_target_points[NUM_APACHE_TARGET_POINTS];

static int
	current_route_waypoint,
	current_route;

static unsigned
	is_direct_waypoint,
	nwaypoints_in_route[MAX_NUMBER_OF_ROUTES],
	ntarget_points,
	next_free_waypoint,
	next_free_control_measure_point,
	next_free_target_point;

static apache_coordinate_points
	*current_navigation_point,
	*current_acquisition_source_point;

static apache_coordinate_points
	*navigation_route[MAX_NUMBER_OF_ROUTES][MAX_NUMBER_OF_WAYPOINTS_IN_ROUTE];

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

apache_coordinate_points* get_current_apache_navigation_point(unsigned* is_direct_nav)
{
	*is_direct_nav = is_direct_waypoint;

	if (current_navigation_point && current_navigation_point->valid)
		return current_navigation_point;

	return NULL;
}

void set_apache_direct_navigation_waypoint(apache_coordinate_points* wpt)
{
	current_navigation_point = wpt;
	is_direct_waypoint = TRUE;
	current_route_waypoint = -1;
}

apache_coordinate_points** get_current_apache_navigation_route(unsigned* last_waypoint, int* current_waypoint)
{
	if (current_route >= 0)
	{
		*last_waypoint = nwaypoints_in_route[current_route] - 1;
		*current_waypoint = current_route_waypoint;
		return navigation_route[current_route];
	}
	else
	{
		*last_waypoint = -1;
		*current_waypoint = -1;
		return NULL;
	}
}

int get_current_apache_waypoint_number(void)
{
	return current_route_waypoint;
}

unsigned get_current_apache_last_waypoint_number(void)
{
	if (current_route >= 0)
		return nwaypoints_in_route[current_route] - 1;
	else
		return 0;
}

apache_coordinate_points* get_next_free_waypoint(void)
{
	if (next_free_waypoint < NUM_APACHE_WAYPOINTS)
		return &apache_waypoint_hazard_points[next_free_waypoint];

	return NULL;
}

apache_coordinate_points* get_next_free_control_measure_point(void)
{
	if (next_free_control_measure_point < NUM_APACHE_WAYPOINT_CM_POINTS)
		return &apache_waypoint_hazard_points[next_free_control_measure_point];

	return NULL;
}

apache_coordinate_points* get_next_free_target_point(void)
{
	if (next_free_target_point < NUM_APACHE_TARGET_POINTS)
		return &apache_target_points[next_free_target_point];

	return NULL;
}

void store_apache_coordinate_point(apache_coordinate_points* point)
{
	point->valid = TRUE;

	// update next free point variable
	if (point->type == 'T')
	{
		if (point->number == next_free_target_point)
			for (; ++next_free_target_point < NUM_APACHE_TARGET_POINTS; next_free_target_point++)
				if (!apache_target_points[next_free_target_point].valid)
					break;
	}
	else if (point->type == 'C')
	{
		if (point->number == next_free_control_measure_point)
			for (; ++next_free_control_measure_point < NUM_APACHE_WAYPOINT_CM_POINTS; next_free_control_measure_point++)
				if (!apache_waypoint_hazard_points[next_free_control_measure_point].valid)
					break;
	}
	else
	{
		if (point->number == next_free_waypoint)
			for (; ++next_free_waypoint < NUM_APACHE_WAYPOINTS; next_free_waypoint++)
				if (!apache_waypoint_hazard_points[next_free_waypoint].valid)
					break;
	}
}

unsigned get_apache_can_add_more_waypoint_hazzard_points(void)
{
	return next_free_waypoint < NUM_APACHE_WAYPOINTS || next_free_control_measure_point < NUM_APACHE_WAYPOINT_CM_POINTS;
}

unsigned get_apache_can_add_more_target_points(void)
{
	return next_free_target_point < ARRAY_LENGTH(apache_target_points);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static void create_waypoint_from_entity(entity* wp, unsigned ind)
{
	entity_sub_type_wapoints sub_type = get_local_entity_int_value(wp, INT_TYPE_ENTITY_SUB_TYPE);

	apache_waypoint_hazard_points[ind].valid = TRUE;
	apache_waypoint_hazard_points[ind].waypoint_entity = wp;
	get_local_entity_vec3d(wp, VEC3D_TYPE_POSITION, &apache_waypoint_hazard_points[ind].position);
	if (point_inside_map_area(&apache_waypoint_hazard_points[ind].position))
		apache_waypoint_hazard_points[ind].position.y = get_3d_terrain_elevation (apache_waypoint_hazard_points[ind].position.x, apache_waypoint_hazard_points[ind].position.z);

	// Initialize the free text to something useful, depending on waypoint type
	switch (sub_type)
	{
	case ENTITY_SUB_TYPE_WAYPOINT_TARGET:
	case ENTITY_SUB_TYPE_WAYPOINT_ATTACK:
		if (ind > 0)
			strcpy(apache_waypoint_hazard_points[ind-1].free_text, "IP");
		strcpy(apache_waypoint_hazard_points[ind].free_text, "TGT");
		break;
	case ENTITY_SUB_TYPE_WAYPOINT_CAP_LOOP:
	case ENTITY_SUB_TYPE_WAYPOINT_CAP_START:
		strcpy(apache_waypoint_hazard_points[ind].free_text, "CAP");
		break;
	case ENTITY_SUB_TYPE_WAYPOINT_PREPARE_FOR_DROP_OFF:
		strcpy(apache_waypoint_hazard_points[ind].free_text, "IP");
		break;
	default:
	case ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION:
		// Use waypoint tag from campaign map, so that it's easier to correspond
		sprintf(apache_waypoint_hazard_points[ind].free_text, "%c", get_local_entity_char_value(wp, CHAR_TYPE_TAG));
		break;
	case ENTITY_SUB_TYPE_WAYPOINT_RECON:
		strcpy(apache_waypoint_hazard_points[ind].free_text, "REC");
		break;
	case ENTITY_SUB_TYPE_WAYPOINT_DROP_OFF:
	case ENTITY_SUB_TYPE_WAYPOINT_TROOP_INSERT:
		strcpy(apache_waypoint_hazard_points[ind].free_text, "INS");
		break;
	case ENTITY_SUB_TYPE_WAYPOINT_APPROACH:
		strcpy(apache_waypoint_hazard_points[ind].free_text, "APR");
		break;
	case ENTITY_SUB_TYPE_WAYPOINT_LAND:
		strcpy(apache_waypoint_hazard_points[ind].free_text, "TD");
		break;
	}
}

void initialise_apache_coordinate_points(void)
{
	unsigned i, nwaypoints;

	entity
		*wp;

	nwaypoints = ntarget_points = 0;
	current_navigation_point = current_acquisition_source_point = NULL;

	memset(apache_waypoint_hazard_points, 0, sizeof(apache_waypoint_hazard_points));
	memset(apache_target_points, 0, sizeof(apache_target_points));
	memset(navigation_route, 0, sizeof(navigation_route));
	memset(nwaypoints_in_route, 0, sizeof(nwaypoints_in_route));

	for (i = 0; i < NUM_APACHE_WAYPOINT_CM_POINTS; i++)
	{
		char type = (i < NUM_APACHE_WAYPOINTS) ? 'W' : 'C';

		apache_waypoint_hazard_points[i].type = type;
		apache_waypoint_hazard_points[i].number = i;

		if (i < NUM_APACHE_TARGET_POINTS)
		{
			apache_target_points[i].type = 'T';
			apache_target_points[i].number = i;
		}
	}

	current_route = -1;

	// Build up route 0 from the waypoint entities
	for (wp = get_local_entity_first_waypoint(get_gunship_entity()); wp; wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT))
	{
		create_waypoint_from_entity(wp, nwaypoints);

		if (nwaypoints_in_route[0] < MAX_NUMBER_OF_WAYPOINTS_IN_ROUTE)
			navigation_route[0][nwaypoints_in_route[0]++] = &apache_waypoint_hazard_points[nwaypoints];

		nwaypoints++;
		if (nwaypoints >= NUM_APACHE_WAYPOINTS)
			break;
	}

	next_free_waypoint = nwaypoints;
	next_free_target_point = ntarget_points;
	next_free_control_measure_point = NUM_APACHE_WAYPOINTS;

	if (nwaypoints)
	{
		current_navigation_point = navigation_route[0][0];
		current_route = 0;
		current_route_waypoint = 0;
		nwaypoints_in_route[0] = min(nwaypoints, MAX_NUMBER_OF_WAYPOINTS_IN_ROUTE);
		navigation_route[0][nwaypoints] = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define has_eech_waypoint_name(x)  ((x)->free_text[0] >= 'A' && (x)->free_text[0] <= 'V' && !(x)->free_text[1])

void apache_delete_coordinate_point(apache_coordinate_points* waypoint)
{
	mfd_locations mfd;

	ASSERT(waypoint);

	apache_remove_waypoint_from_route(waypoint);

	// clear variables (keep type and number as they are constant)
	waypoint->valid = FALSE;
	waypoint->position.x = waypoint->position.y = waypoint->position.z = 0.0;
	waypoint->free_text[0] = 0;
	waypoint->waypoint_entity = NULL;

	if (waypoint->type == 'T')
		next_free_target_point = min(next_free_target_point, waypoint->number);
	else if (waypoint->type == 'C')
		next_free_control_measure_point = min(next_free_control_measure_point, waypoint->number);
	else
		next_free_waypoint = min(next_free_waypoint, waypoint->number);

	// remove all references to the waypoint
	for (mfd = MFD_LOCATION_PILOT_LHS; mfd <= MFD_LOCATION_CPG_RHS; mfd++)
		if (get_apache_tsd_show_waypoint_review(mfd) == waypoint)
			set_apache_tsd_show_waypoint_review(mfd, NULL);
}

void apache_remove_waypoint_from_route(apache_coordinate_points* waypoint)
{
	unsigned i=0;

	if (current_route == -1)
	{
		ASSERT(FALSE);
		return;
	}

	for (i=0; i<MAX_NUMBER_OF_WAYPOINTS_IN_ROUTE; i++)
		if (navigation_route[current_route][i] == waypoint)
			break;

	if (i < MAX_NUMBER_OF_WAYPOINTS_IN_ROUTE)  // found the waypoint to delete in route
	{
		char next_waypoint_name = 0;

		waypoint->waypoint_entity = NULL;  // it will be deleted

		if (has_eech_waypoint_name(waypoint))
		{
			next_waypoint_name = waypoint->free_text[0];
			waypoint->free_text[0] = 0;
		}

		// move the other waypoints in route one step up
		for (; i < MAX_NUMBER_OF_WAYPOINTS_IN_ROUTE - 1; i++)
		{
			navigation_route[current_route][i] = navigation_route[current_route][i+1];

			if (navigation_route[current_route][i] && has_eech_waypoint_name(navigation_route[current_route][i]))
				sprintf(navigation_route[current_route][i]->free_text, "%c", next_waypoint_name++);
				//sprintf(navigation_route[current_route][i]->free_text, "%c", get_local_entity_char_value(navigation_route[current_route][i]->waypoint_entity, CHAR_TYPE_TAG));
		}
		navigation_route[current_route][MAX_NUMBER_OF_WAYPOINTS_IN_ROUTE - 1] = NULL;

		nwaypoints_in_route[current_route]--;

		if (current_navigation_point == waypoint) // removing current waypoint.
		{
			if (!navigation_route[current_route][i+1])  // if this is last waypoint, then chose second to last waypoint as current
				current_route_waypoint--;

			if (current_route_waypoint >= 0)
				current_navigation_point = navigation_route[current_route][current_route_waypoint];
			else
				current_navigation_point = NULL;
		}
	}
}

void apache_insert_waypoint_into_route(apache_coordinate_points* waypoint, apache_coordinate_points* next_waypoint)
{
	unsigned i=0, insertion_point;

	if (current_route == -1)
	{
		ASSERT(FALSE);
		return;
	}

	if (nwaypoints_in_route[current_route] >= MAX_NUMBER_OF_WAYPOINTS_IN_ROUTE)
		return;

	for (insertion_point=0; insertion_point < MAX_NUMBER_OF_WAYPOINTS_IN_ROUTE; insertion_point++)
		if (navigation_route[current_route][insertion_point] == next_waypoint)
			break;

	if (insertion_point == MAX_NUMBER_OF_WAYPOINTS_IN_ROUTE || insertion_point == 0)  // next waypoint doesn't exist in route
		return;

	ASSERT(navigation_route[current_route][insertion_point-1]->waypoint_entity);
	if (!waypoint->waypoint_entity)
		waypoint->waypoint_entity = map_add_waypoint(navigation_route[current_route][insertion_point-1]->waypoint_entity, &waypoint->position, FALSE);

	for (i = nwaypoints_in_route[current_route]; i > insertion_point; i--)
	{
		navigation_route[current_route][i] = navigation_route[current_route][i-1];
		if (has_eech_waypoint_name(navigation_route[current_route][i]) && navigation_route[current_route][i]->waypoint_entity)
			sprintf(navigation_route[current_route][i]->free_text, "%c", get_local_entity_char_value(navigation_route[current_route][i]->waypoint_entity, CHAR_TYPE_TAG));
	}

	navigation_route[current_route][insertion_point] = waypoint;
	if (!*waypoint->free_text || has_eech_waypoint_name(waypoint))
		sprintf(navigation_route[current_route][insertion_point]->free_text, "%c", get_local_entity_char_value(navigation_route[current_route][insertion_point]->waypoint_entity, CHAR_TYPE_TAG));
	nwaypoints_in_route[current_route]++;
}

void apache_waypoint_changed(entity* waypoint, waypoint_update_action change)
{
	unsigned i;

	if (change == MAP_WAYPOINT_CREATED)
	{
		if (next_free_waypoint < NUM_APACHE_WAYPOINT_CM_POINTS)
		{
			entity* next_waypoint = get_local_entity_child_succ (waypoint, LIST_TYPE_WAYPOINT);

			create_waypoint_from_entity(waypoint, next_free_waypoint);

			if (current_route == -1)
			{
				ASSERT(FALSE);
				return;
			}

			// find next waypoint in route:
			for (i=0; i < nwaypoints_in_route[current_route]; i++)
			{
				if (navigation_route[current_route][i]->waypoint_entity == next_waypoint)
				{
					apache_insert_waypoint_into_route(&apache_waypoint_hazard_points[next_free_waypoint], navigation_route[current_route][i]);
					break;
				}
			}

			debug_log("inserted entity %x, index: %d", apache_waypoint_hazard_points[next_free_waypoint].waypoint_entity, next_free_waypoint);

			// find next free slot
			while (next_free_waypoint < NUM_APACHE_WAYPOINT_CM_POINTS && apache_waypoint_hazard_points[next_free_waypoint].valid)
				next_free_waypoint++;
		}
	}
	else
	{
		for (i=0; i < NUM_APACHE_WAYPOINTS; i++)
			if (apache_waypoint_hazard_points[i].waypoint_entity == waypoint)
			{
				if (change == MAP_WAYPOINT_DELETED)
				{
					// don't actually delete, just remove from current route
					apache_remove_waypoint_from_route(&apache_waypoint_hazard_points[i]);
#if 0
					memset(&apache_waypoint_hazard_points[i], 0, sizeof(apache_waypoint_hazard_points[i]));
					next_free_waypoint = min(next_free_waypoint, i);

					while (nwaypoints > 0 && !apache_waypoint_hazard_points[nwaypoints-1].valid)
						nwaypoints--;
#endif
				}
				else
				{
					get_local_entity_vec3d(waypoint, VEC3D_TYPE_POSITION, &apache_waypoint_hazard_points[i].position);
					debug_log("moved to: %.0f, %.0f", apache_waypoint_hazard_points[i].position.x, apache_waypoint_hazard_points[i].position.z);
					if (point_inside_map_area(&apache_waypoint_hazard_points[i].position))
						apache_waypoint_hazard_points[i].position.y = get_3d_terrain_elevation (apache_waypoint_hazard_points[i].position.x, apache_waypoint_hazard_points[i].position.z);
				}

				break;
			}
	}
}
