/*
 * co_laser.h
 *
 *  Created on: 17. mai 2010
 *      Author: arneh
 */

#ifndef CO_LASER_H_
#define CO_LASER_H_

extern char current_laser_channels[4];

char get_laser_range_finder_designator_channel(void);
char get_laser_spot_tracker_channel(void);
void set_laser_range_finder_designator_channel(char channel);
void set_laser_spot_tracker_channel(char channel);

char get_priority_laser_channel(void);
char get_alternate_laser_channel(void);
void set_priority_laser_channel(char chan);
void set_alternate_laser_channel(char chan);

// display_freq must be a pointer to a buffer of at least length 5
void get_display_laser_channel_frequency(unsigned index, char* display_freq);

void initialise_common_laser(void);
void deinitialise_common_laser(void);

#endif /* CO_LASER_H_ */
