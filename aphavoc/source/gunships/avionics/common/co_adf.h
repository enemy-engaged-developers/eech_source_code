/*
 * co_adf.h
 *
 *  Created on: 27.sep.2009
 *      Author: arneh
 */

#ifndef CO_ADF_H_
#define CO_ADF_H_

typedef enum {
	ADF_MODE_ADF,  // gives bearing to transmitter and radio audio receiver
	ADF_MODE_ANT   // only radio audio receiver
} adf_modes;

/* This is the data for the actual physical transmitter */
typedef struct {
	entity* en;
	char code[4];
	char morse_code[20];
	unsigned radio_frequency;
} ndb_transmitter;

/*
 * This is a transmitter as represented in the instruments.  There need not
 * be an actual transmitter at the frequency or ID the pilot has chosen, but
 * we still need to represent it.
 */
typedef struct {
	ndb_transmitter* transmitter;  // points at actual transmitter if there is one
	char code[4];
	char morse_code[20];
	unsigned radio_frequency;
} ndb_instrument_transmitter;

void initialize_common_adf(void);
void update_common_adf(void);

int get_adf_enabled(void);
void toggle_adf_enabled(void);

// Get's the actual transmitter at this frequency
ndb_transmitter* get_ndb_transmitter_from_frequency(unsigned Hz);

// All the instrument transmitters in an array.  ntransmitters is the number of them
ndb_instrument_transmitter* get_instrument_transmitters(unsigned* ntransmitters);

vec3d* get_transmitter_position(ndb_transmitter*);

ndb_instrument_transmitter* get_current_adf_station(void);
void set_current_adf_station(ndb_instrument_transmitter* transmitter);

// All frequencies in Hz (not kHz as they are usually shown as in the cockpit)
unsigned get_current_adf_frequency(void);
void set_current_adf_frequency(unsigned Hz);
void swap_to_last_adf_frequency(void);

// Do we receive any signal from tunes NDB?
int has_ndb_signal(void);

// Do we get bearings to transmitter.  Call before using get_adf_bearing
int has_adf_bearing(void);

// Bearing to transmitter.  Only valid if has_adf_bearing returns TRUE
float get_adf_bearing(void);

adf_modes get_adf_mode(void);
void set_adf_mode(adf_modes);

// Offsets bearing by 90 degrees for 2 seconds.  For testing purposes
void set_adf_test_mode(void);

// Plays a tone when receiving NDB signal
void toggle_adf_tone(void);
int get_adf_tone_enabled(void);

#endif /* CO_ADF_H_ */
