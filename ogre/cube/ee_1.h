float
	object_3d_sin_heading[256],
	object_3d_cos_heading[256],
	object_3d_sin_pitch[256],
	object_3d_cos_pitch[256];
void initialise_object_3d_lookup_tables ( void )
{

	int
		count;

	for ( count = 0; count < 256; count++ )
	{

		float
			heading,
			pitch;

		pitch = heading = (float)count;

		heading /= 256.0;
		pitch /= 256.0;

		heading *= PI2;
		pitch *= PI;

		heading -= PI;
		pitch -= PI/2;

		object_3d_sin_heading[count] = sin(heading);
		object_3d_cos_heading[count] = cos(heading);

		object_3d_sin_pitch[count] = sin(pitch);
		object_3d_cos_pitch[count] = cos(pitch);
	}
}
int a = (initialise_object_3d_lookup_tables(), 0);

void generate_object_3d_point_normal(object_3d_heading_pitch_normal *normal, vec3d *result)
{
	float
		sin_heading,
		cos_heading,
		sin_pitch,
		cos_pitch;

	sin_heading = object_3d_sin_heading[normal->heading];
	cos_heading = object_3d_cos_heading[normal->heading];

	sin_pitch = object_3d_sin_pitch[normal->pitch];
	cos_pitch = object_3d_cos_pitch[normal->pitch];
	result->x = cos_pitch * sin_heading;
	result->y = sin_pitch;
	result->z = cos_pitch * cos_heading;
}
