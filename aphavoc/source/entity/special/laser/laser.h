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


#endif /* LASER_H_ */
