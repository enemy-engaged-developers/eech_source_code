/*
 * tacview.h
 *
 * Format documentation: http://lomac.strasoftware.com/tacview-flight-recordings.php
 *
 *  Created on: 25.mar.2009
 *      Author: arneh
 */

#ifndef TACVIEW_H_
#define TACVIEW_H_

typedef enum {
	TACVIEW_UNIT_LEFT_AREA,
	TACVIEW_UNIT_DESTROYED,
	TACVIEW_UNIT_TOOK_OFF,
	TACVIEW_UNIT_LANDED
} tacview_event_type;

void open_tacview_log(void);
void close_tacview_log(void);

void write_tacview_header(entity* pilot, entity* player_gunship);

void write_tacview_frame_header(void);
void write_tacview_new_unit(entity* en);
void write_tacview_unit_removed(entity* en, tacview_event_type type);
void write_tacview_unit_update(entity* en);

#endif /* TACVIEW_H_ */
