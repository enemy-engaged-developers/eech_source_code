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

extern FILE* tacview_log_file;
#define tacview_is_logging()  (tacview_log_file != NULL)

typedef enum {
	TACVIEW_UNIT_LEFT_AREA,
	TACVIEW_UNIT_DESTROYED,
	TACVIEW_UNIT_TOOK_OFF,
	TACVIEW_UNIT_LANDED
} tacview_event_type;

// Start a new log.  Call when you want to start logging
void start_tacview_logging(entity* player_gunship);

// Ends logging and closes the log file
void close_tacview_log(void);

// Writes the file header.  Must be called before any other logging functions
void write_tacview_header(entity* pilot, entity* player_gunship);
void write_tacview_town_names(void);

// Writes the tacview header needed each frame
void write_tacview_frame_header(void);

// Checks the tacview logfile size and returns TRUE if bigger than allowed
int check_tacview_filesize(void);

// Addes logging for a new unit
void write_tacview_new_unit(entity* en);

// Log a special event for unit (one of the types in tacview_event_type)
// Related may be a related unit to the event (e.g. the weapon that the destroyed the unit)
// Leave it NULL if there is no related unit.
void write_tacview_unit_event(entity* en, tacview_event_type type, entity* related);

// Write unit's position (if moved is TRUE) and rotation (if rotated is TRUE)
// May not actually write anything unless force is TRUE.  We only write the update
// once every set number of times the function is called to save FPS.  Use force when
// it's really important that this update is logged, like when just having created or
// is destroying the unit
void write_tacview_unit_update(entity* en, int moved, int rotated, int force);

// Log some debug event.  May be connected to a specific entity, otherwise leave en as NULL
// Rest of arguments is a printf-like string format with arguments
void write_tacview_debug_event(entity* en, const char* format, ...);

// Called once per frame, and updates the variables which needs to be updated once per frame
// Return value is currently always TRUE, so just ignore it
int tacview_reset_frame(void);

// Updates some information from the playes gunship.  Call once per frame
void tacview_update_gunship(void);

#endif /* TACVIEW_H_ */
