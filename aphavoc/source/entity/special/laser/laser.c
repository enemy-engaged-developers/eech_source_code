/*
 * laser.c
 *
 *  Created on: 3. mars 2010
 *      Author: arneh
 */

#include "project.h"

#include "laser.h"

// One slot for each valid frequency.  Each slot contains a list of all designations for that frequency
laser_designation* laser_designations[512];

