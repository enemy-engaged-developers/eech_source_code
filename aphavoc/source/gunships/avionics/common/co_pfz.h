// Priorty Fire Zones - written by arneh, nov 2006

#define NO_PFZ -1

typedef struct
{
	vec3d corner1;
	vec3d corner2;
	vec3d corner3;
	vec3d corner4;
} pfz;

/// currently selected PFZ
extern int current_pfz;

/// all pfz/nfzs lower in number are filled
extern unsigned int next_free_pfz, next_free_nfz;


extern pfz* get_pfz(unsigned int pfz_number);
extern pfz* get_nfz(unsigned int nfz_number);

extern void delete_pfz(unsigned int pfz_number);
extern void delete_nfz(unsigned int nfz_number);

extern void add_pfz(vec3d* corner1, vec3d* corner2, vec3d* corner3, vec3d* corner4);
extern void add_nfz(vec3d* corner1, vec3d* corner2, vec3d* corner3, vec3d* corner4);

extern void relative_position_to_world_coordinate (vec3d* relative_position, vec3d* world_coordinate, matrix3x3 rotation_matrix);
extern void world_coordinate_to_relative_position (vec3d* world_coordinate, vec3d* relative_vector, matrix3x3 rotation_matrix);

/// returns TRUE if the coordinate lies inside the given pfz/nfz
extern int coordinate_is_inside_pfz(vec3d* coordinate, unsigned int pfz_number, int is_nfz);
extern int coordinate_is_inside_square(vec3d* coordinate, vec3d* corner1, vec3d* corner2, vec3d* corner3, vec3d* corner4);

extern void select_next_pfz(void);
extern void select_previous_pfz(void);

extern void deselect_pfz(void);
extern void delete_current_pfz(void);

extern int is_valid_pfz_target(vec3d* target_position);

extern int pfz_active();
