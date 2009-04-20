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

void start_tacview_logging(entity* player_gunship);

//void open_tacview_log(void);
void close_tacview_log(void);

void write_tacview_header(entity* pilot, entity* player_gunship);
void write_tacview_town_names(void);

void write_tacview_frame_header(void);
void write_tacview_new_unit(entity* en);
void write_tacview_unit_event(entity* en, tacview_event_type type, entity* related);
void write_tacview_unit_update(entity* en, int moved, int rotated, int force);
void write_tacview_debug_event(entity* en, const char* format, ...);

int tacview_reset_frame(void);

#endif /* TACVIEW_H_ */
