/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SMOKE_LIST_DECLARATION
#define SMOKE_LIST_DECLARATION(x) x
#define SMOKE_LIST(x) SMOKE_LIST_TYPE_##x,
#define SMOKE_LIST_(x) x
#endif

SMOKE_LIST_DECLARATION(typedef enum SMOKE_LIST_TYPES)
SMOKE_LIST_DECLARATION({)
	SMOKE_LIST(GREY_TRAIL)
	SMOKE_LIST(WHITE_TRAIL)
	SMOKE_LIST(ADDITIVE_TRAIL)
	SMOKE_LIST(LARGE_ADDITIVE_TRAIL)

	SMOKE_LIST(FIRE)
	SMOKE_LIST(SMALL_FIRE)
	SMOKE_LIST(PURPLE_FLARE)
	SMOKE_LIST(LARGE_DUST_CLOUD)

	SMOKE_LIST(SMALL_PARTICLE_TRAIL)

	SMOKE_LIST(MEDIUM_EARTH_PARTICLE_TRAIL)
	SMOKE_LIST(MEDIUM_WATER_PARTICLE_TRAIL)

	SMOKE_LIST(DUST_TRAIL_1)
	SMOKE_LIST(DUST_TRAIL_2)

	SMOKE_LIST(REAR_SHIP_WAKE)
	SMOKE_LIST(FRONT_SHIP_WAKE)
		
	SMOKE_LIST(AIRCRAFT_LIGHT_DAMAGE_MOVING_TRAIL)
	SMOKE_LIST(AIRCRAFT_HEAVY_DAMAGE_MOVING_TRAIL)
	SMOKE_LIST(AIRCRAFT_LIGHT_DAMAGE_STATIC_TRAIL)
	SMOKE_LIST(AIRCRAFT_HEAVY_DAMAGE_STATIC_TRAIL)

	// Xhit: added following for the downwash effects (these are taken from terrain_types) (030328)
	// Xhit: added DOWNWASH_DESERT for desert campaigns (030515)
	SMOKE_LIST(DOWNWASH_START)				//21

	SMOKE_LIST(DOWNWASH_DESERT)				//22
	SMOKE_LIST(DOWNWASH_SAND)				//23
	SMOKE_LIST(DOWNWASH_GRASS)				//24
	SMOKE_LIST(DOWNWASH_ASPHALT)			//25
	SMOKE_LIST(DOWNWASH_WATER)				//26
	SMOKE_LIST(DOWNWASH_SOIL)				//27
	SMOKE_LIST(DOWNWASH_FIELD_LIGHTBROWN)//28
	SMOKE_LIST(DOWNWASH_FIELD_DARKBROWN)	//29	
	SMOKE_LIST(DOWNWASH_FIELD_LIGHTGREEN)//30
	SMOKE_LIST(DOWNWASH_FIELD_DARKGREEN)	//31
	SMOKE_LIST(DOWNWASH_ROCK)				//32
	SMOKE_LIST(DOWNWASH_SNOW)				//33
	SMOKE_LIST(FLAME)		//Werewolf: Additional burning flame for vehicle wrecks

	SMOKE_LIST(GUN_SMOKE)
	SMOKE_LIST(GUN_SMOKE_2)

	SMOKE_LIST_(NUM_SMOKE_LIST_TYPES)

SMOKE_LIST_DECLARATION(} smoke_list_types;)

#undef SMOKE_LIST_DECLARATION
#undef SMOKE_LIST
#undef SMOKE_LIST_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef META_SMOKE_LIST_DECLARATION
#define META_SMOKE_LIST_DECLARATION(x) x
#define META_SMOKE_LIST(x) META_SMOKE_LIST_TYPE_##x,
#define META_SMOKE_LIST_(x) x
#endif

META_SMOKE_LIST_DECLARATION(typedef enum META_SMOKE_LIST_TYPES)
META_SMOKE_LIST_DECLARATION({)
	META_SMOKE_LIST(NONE)
	META_SMOKE_LIST(GENERIC_ROCKET_TRAIL)
	META_SMOKE_LIST(SMALL_ROCKET_TRAIL)
	META_SMOKE_LIST(DECOY_FLARE_TRAIL)
	META_SMOKE_LIST(INFINITE_FIRE)
	META_SMOKE_LIST(FIRE_SHORT_DURATION)
	META_SMOKE_LIST(SMALL_FIRE_SHORT_DURATION)
	META_SMOKE_LIST(VEHICLE_DUST_TRAIL)
	META_SMOKE_LIST(REAR_SHIP_WAKE)
	META_SMOKE_LIST(FRONT_SHIP_WAKE)
	META_SMOKE_LIST(AIRCRAFT_LIGHT_DAMAGE_MOVING)
	META_SMOKE_LIST(AIRCRAFT_HEAVY_DAMAGE_MOVING)
	META_SMOKE_LIST(AIRCRAFT_LIGHT_DAMAGE_STATIC)
	META_SMOKE_LIST(AIRCRAFT_HEAVY_DAMAGE_STATIC)
	META_SMOKE_LIST(SMALL_GUN_SMOKE)
	META_SMOKE_LIST(MEDIUM_GUN_SMOKE)
	META_SMOKE_LIST(LARGE_GUN_SMOKE)

	META_SMOKE_LIST_(NUM_META_SMOKE_LIST_TYPES)

META_SMOKE_LIST_DECLARATION(} meta_smoke_list_types;)

#undef META_SMOKE_LIST_DECLARATION
#undef META_SMOKE_LIST
#undef META_SMOKE_LIST_


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
