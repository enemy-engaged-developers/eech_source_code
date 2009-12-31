/*
 * ap_stored_point.h
 *
 *  Created on: 12.okt.2009
 *      Author: arneh
 */

#ifndef AP_STORED_POINT_H_
#define AP_STORED_POINT_H_

#define NUM_APACHE_WAYPOINT_CM_POINTS  100
#define NUM_APACHE_WAYPOINTS 50
#define NUM_APACHE_TARGET_POINTS  50

typedef struct APACHE_COORDINATE_POINTS {
	vec3d position;
	entity* waypoint_entity;
	char free_text[4];  // Three letter free text.  By default contains waypoint letter from EECH, or some more specific string like TGT or TD(touchdown)
	char type, valid, number;  // Type is one of W (waypoint/hazard), C (control meassure) or T (target/threat).  If valid is FALSE then the rest of the data are not valid
} apache_coordinate_points;

// waypoints/hazards will be in positions 0-49, countrol measures in 50-99
extern apache_coordinate_points apache_waypoint_hazard_points[NUM_APACHE_WAYPOINT_CM_POINTS];
extern apache_coordinate_points apache_target_points[NUM_APACHE_TARGET_POINTS];

// may return NULL if no valid navigation point
apache_coordinate_points* get_current_apache_navigation_point(unsigned* is_direct_nav);
void set_apache_direct_navigation_waypoint(apache_coordinate_points* wpt);

// Returns an array with pointers to waypoints.  Last pointer is NULL
// May return NULL if no route selected
// current_waypoint is index of the currently selected waypoint, or -1 if none
apache_coordinate_points** get_current_apache_navigation_route(unsigned* last_waypoint, int* current_waypoint);

int get_current_apache_waypoint_number(void);
unsigned get_current_apache_last_waypoint_number(void);

unsigned get_apache_can_add_more_waypoint_hazzard_points(void);
unsigned get_apache_can_add_more_target_points(void);

apache_coordinate_points* get_next_free_waypoint(void);
apache_coordinate_points* get_next_free_control_measure_point(void);
apache_coordinate_points* get_next_free_target_point(void);
void store_apache_coordinate_point(apache_coordinate_points*);

// a waypoint entity has changed, need to sync with Apache's waypoints
void apache_waypoint_changed(entity* waypoint, waypoint_update_action change);

void apache_delete_coordinate_point(apache_coordinate_points* waypoint);

void apache_remove_waypoint_from_route(apache_coordinate_points* waypoint);
// inserts a waypoint (which must exist already) into an existing route.  the waypoint
// will be inserted in the route before next_waypoint (which must exist in the route already)
void apache_insert_waypoint_into_route(apache_coordinate_points* waypoint, apache_coordinate_points* next_waypoint);

#endif /* AP_STORED_POINT_H_ */
