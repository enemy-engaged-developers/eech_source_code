/*
 * co_laser.c
 *
 *  Created on: 17. mai 2010
 *      Author: arneh
 */

#include "project.h"

#include "co_laser.h"

#include "entity/special/laser/laser.h"

char current_laser_channels[4];

static unsigned laser_channels[16];

static char
	lrfd_channel,
	lst_channel,
	priority_laser_channel,
	alternate_laser_channel;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char get_laser_range_finder_designator_channel(void)
{
	return lrfd_channel;
}

char get_laser_spot_tracker_channel(void)
{
	return lst_channel;
}

char get_priority_laser_channel(void)
{
	return priority_laser_channel;
}

char get_alternate_laser_channel(void)
{
	return alternate_laser_channel;
}

void set_laser_range_finder_designator_channel(char channel)
{
	lrfd_channel = channel;
}

void set_laser_spot_tracker_channel(char channel)
{
	lst_channel = channel;
}

void set_priority_laser_channel(char chan)
{
	ASSERT(chan == 0 || (chan >= 'A' && chan <= 'R' && chan != 'I' && chan != 'O'));

	// swap if same as alt
	if (chan && chan == alternate_laser_channel)
		alternate_laser_channel = priority_laser_channel;

	priority_laser_channel = chan;
}

void set_alternate_laser_channel(char chan)
{
	ASSERT(chan == 0 || (chan >= 'A' && chan <= 'R' && chan != 'I' && chan != 'O'));

	// swap if same as pri
	if (chan && chan == priority_laser_channel)
		priority_laser_channel = alternate_laser_channel;

	alternate_laser_channel = chan;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_display_laser_channel_frequency(unsigned index, char* display_freq)
{
	ASSERT(index < ARRAY_LENGTH(laser_channels));

	get_display_laser_frequency(laser_channels[index], display_freq);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_common_laser(void)
{
	// setup default laser channels

	lrfd_channel = lst_channel = 'A';
	priority_laser_channel = alternate_laser_channel = 0;

	current_laser_channels[0] = 'A';
	current_laser_channels[1] = 'B';
	current_laser_channels[2] = 'C';
	current_laser_channels[3] = 'D';

	laser_channels[0] = get_packed_laser_frequency("1111");
	laser_channels[1] = get_packed_laser_frequency("1155");
	laser_channels[2] = get_packed_laser_frequency("1221");
	laser_channels[3] = get_packed_laser_frequency("1266");
	laser_channels[4] = get_packed_laser_frequency("1332");
	laser_channels[5] = get_packed_laser_frequency("1377");
	laser_channels[6] = get_packed_laser_frequency("1443");
	laser_channels[7] = get_packed_laser_frequency("1488");
	laser_channels[8] = get_packed_laser_frequency("1511");
	laser_channels[9] = get_packed_laser_frequency("1555");
	laser_channels[10] = get_packed_laser_frequency("1621");
	laser_channels[11] = get_packed_laser_frequency("1666");
	laser_channels[12] = get_packed_laser_frequency("1732");
	laser_channels[13] = get_packed_laser_frequency("1777");
	laser_channels[14] = get_packed_laser_frequency("1782");
	laser_channels[15] = get_packed_laser_frequency("1788");
}

void deinitialise_common_laser(void)
{

}
