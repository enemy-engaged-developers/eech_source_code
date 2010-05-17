/*
 * laser.h
 *
 *  Created on: 3. mars 2010
 *      Author: arneh
 */

#ifndef LASER_H_
#define LASER_H_

typedef struct LASER_DESIGNATION {
	unsigned int
		valid : 1,
		side : 2,
		frequency : 9;

	vec3d
		direction,
		position;

	entity
		*target,
		*source;


} laser_designation;

unsigned can_spot_designation(entity* source, laser_designation* spot);

laser_designation* get_first_spotted_designation(entity* source, unsigned frequency);

unsigned get_packed_laser_frequency(const char* display_freq);
// display_freq must be a pointer to a buffer of at least length 5
void get_display_laser_frequency(unsigned packed_freq, char* display_freq);

#endif /* LASER_H_ */
