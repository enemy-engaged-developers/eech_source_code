/*
 * co_laser.h
 *
 *  Created on: 17. mai 2010
 *      Author: arneh
 */

#ifndef CO_LASER_H_
#define CO_LASER_H_

extern char current_laser_channels[4];

char get_priority_laser_channel(void);
char get_alternate_laser_channel(void);
void set_priority_laser_channel(char chan);
void set_alternate_laser_channel(char chan);

void initialise_common_laser(void);
void deinitialise_common_laser(void);

#endif /* CO_LASER_H_ */
