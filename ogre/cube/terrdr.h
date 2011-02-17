//
// Ordinary rendering functions
//

void terrain_unclipped ( int number_of_points );
// x, y, z, ?, color, (0, 0, 0, fog? ), x * xz_texture_scale, z * xz_texture_scale

#define draw_3d_terrain_unclipped_fan_word_face terrain_unclipped

#define draw_3d_terrain_unclipped_fan_byte_face terrain_unclipped

#define draw_3d_terrain_unclipped_strip_word_face terrain_unclipped

#define draw_3d_terrain_unclipped_strip_byte_face terrain_unclipped

void terrain_texture_x_unclipped ( int number_of_points );
// x, y, z, ?, color, (0, 0, 0, fog? ), z * xz_texture_scale, y * y_texture_scale

#define draw_3d_terrain_texture_x_unclipped_strip_word_face terrain_texture_x_unclipped

#define draw_3d_terrain_texture_x_unclipped_strip_byte_face terrain_texture_x_unclipped

#define draw_3d_terrain_texture_x_unclipped_fan_word_face terrain_texture_x_unclipped

#define draw_3d_terrain_texture_x_unclipped_fan_byte_face terrain_texture_x_unclipped

void terrain_texture_z_unclipped ( int number_of_points );
// x, y, z, ?, color, (0, 0, 0, fog? ), x * xz_texture_scale, y * y_texture_scale

#define draw_3d_terrain_texture_z_unclipped_strip_word_face terrain_texture_z_unclipped

#define draw_3d_terrain_texture_z_unclipped_strip_byte_face terrain_texture_z_unclipped

#define draw_3d_terrain_texture_z_unclipped_fan_word_face terrain_texture_z_unclipped

#define draw_3d_terrain_texture_z_unclipped_fan_byte_face terrain_texture_z_unclipped


void terrain_colour_unclipped ( int number_of_points );

#define draw_3d_terrain_colour_unclipped_fan_word_face terrain_colour_unclipped

#define draw_3d_terrain_colour_unclipped_fan_byte_face terrain_colour_unclipped

#define draw_3d_terrain_colour_unclipped_strip_word_face terrain_colour_unclipped

#define draw_3d_terrain_colour_unclipped_strip_byte_face terrain_colour_unclipped

void terrain_texture_x_colour_unclipped ( int number_of_points );

#define draw_3d_terrain_texture_x_colour_unclipped_fan_word_face terrain_texture_x_colour_unclipped

#define draw_3d_terrain_texture_x_colour_unclipped_fan_byte_face terrain_texture_x_colour_unclipped

#define draw_3d_terrain_texture_x_colour_unclipped_strip_word_face terrain_texture_x_colour_unclipped

#define draw_3d_terrain_texture_x_colour_unclipped_strip_byte_face terrain_texture_x_colour_unclipped

void terrain_texture_z_colour_unclipped ( int number_of_points );

#define draw_3d_terrain_texture_z_colour_unclipped_fan_word_face terrain_texture_z_colour_unclipped

#define draw_3d_terrain_texture_z_colour_unclipped_fan_byte_face terrain_texture_z_colour_unclipped

#define draw_3d_terrain_texture_z_colour_unclipped_strip_word_face terrain_texture_z_colour_unclipped

#define draw_3d_terrain_texture_z_colour_unclipped_strip_byte_face terrain_texture_z_colour_unclipped


//
// Two pass rendering functions
//

void terrain_twopass_unclipped ( int number_of_points );
// x, y, z, ?, color, (0, 0, 0, fog? ), x * xz_texture_scale, z * xz_texture_scale
// if (color.alpha != 0 for any point drawn)
// x, y, z, ?, color, (0, 0, 0, 0), x * xz_texture_scale, z * xz_texture_scale

#define draw_3d_terrain_twopass_unclipped_fan_word_face terrain_twopass_unclipped

#define draw_3d_terrain_twopass_unclipped_fan_byte_face terrain_twopass_unclipped

#define draw_3d_terrain_twopass_unclipped_strip_word_face terrain_twopass_unclipped

#define draw_3d_terrain_twopass_unclipped_strip_byte_face terrain_twopass_unclipped

void terrain_twopass_texture_x_unclipped ( int number_of_points );

#define draw_3d_terrain_twopass_texture_x_unclipped_strip_word_face terrain_twopass_texture_x_unclipped

#define draw_3d_terrain_twopass_texture_x_unclipped_strip_byte_face terrain_twopass_texture_x_unclipped

#define draw_3d_terrain_twopass_texture_x_unclipped_fan_word_face terrain_twopass_texture_x_unclipped

#define draw_3d_terrain_twopass_texture_x_unclipped_fan_byte_face terrain_twopass_texture_x_unclipped

void terrain_twopass_texture_z_unclipped ( int number_of_points );

#define draw_3d_terrain_twopass_texture_z_unclipped_strip_word_face terrain_twopass_texture_z_unclipped

#define draw_3d_terrain_twopass_texture_z_unclipped_strip_byte_face terrain_twopass_texture_z_unclipped

#define draw_3d_terrain_twopass_texture_z_unclipped_fan_word_face terrain_twopass_texture_z_unclipped

#define draw_3d_terrain_twopass_texture_z_unclipped_fan_byte_face terrain_twopass_texture_z_unclipped

void terrain_twopass_colour_unclipped ( int number_of_points );

#define draw_3d_terrain_twopass_colour_unclipped_fan_word_face terrain_twopass_colour_unclipped

#define draw_3d_terrain_twopass_colour_unclipped_fan_byte_face terrain_twopass_colour_unclipped

#define draw_3d_terrain_twopass_colour_unclipped_strip_word_face terrain_twopass_colour_unclipped

#define draw_3d_terrain_twopass_colour_unclipped_strip_byte_face terrain_twopass_colour_unclipped

void terrain_twopass_texture_x_colour_unclipped ( int number_of_points );

#define draw_3d_terrain_twopass_texture_x_colour_unclipped_fan_word_face terrain_twopass_texture_x_colour_unclipped

#define draw_3d_terrain_twopass_texture_x_colour_unclipped_fan_byte_face terrain_twopass_texture_x_colour_unclipped

#define draw_3d_terrain_twopass_texture_x_colour_unclipped_strip_word_face terrain_twopass_texture_x_colour_unclipped

#define draw_3d_terrain_twopass_texture_x_colour_unclipped_strip_byte_face terrain_twopass_texture_x_colour_unclipped

void terrain_twopass_texture_z_colour_unclipped ( int number_of_points );

#define draw_3d_terrain_twopass_texture_z_colour_unclipped_fan_word_face terrain_twopass_texture_z_colour_unclipped

#define draw_3d_terrain_twopass_texture_z_colour_unclipped_fan_byte_face terrain_twopass_texture_z_colour_unclipped

#define draw_3d_terrain_twopass_texture_z_colour_unclipped_strip_word_face terrain_twopass_texture_z_colour_unclipped

#define draw_3d_terrain_twopass_texture_z_colour_unclipped_strip_byte_face terrain_twopass_texture_z_colour_unclipped

//
// Three pass rendering functions
//

//#define draw_3d_terrain_threepass_colour_unclipped_fan_word_face terrain_threepass_colour_unclipped

//#define draw_3d_terrain_threepass_colour_unclipped_fan_byte_face terrain_threepass_colour_unclipped

//
// Debug functions
//

//extern void draw_3d_terrain_line_clipped_strip_byte_face ( int number_of_points );

//extern void draw_3d_terrain_line_clipped_strip_word_face ( int number_of_points );
