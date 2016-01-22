// 
// 	 Enemy Engaged RAH-66 Comanche Versus KA-52 Hokum
// 	 Copyright (C) 2000 Empire Interactive (Europe) Ltd,
// 	 677 High Road, North Finchley, London N12 0DA
// 
// 	 Please see the document LICENSE.TXT for the full licence agreement
// 
// 2. LICENCE
//  2.1 	
//  	Subject to the provisions of this Agreement we now grant to you the 
//  	following rights in respect of the Source Code:
//   2.1.1 
//   	the non-exclusive right to Exploit  the Source Code and Executable 
//   	Code on any medium; and 
//   2.1.2 
//   	the non-exclusive right to create and distribute Derivative Works.
//  2.2 	
//  	Subject to the provisions of this Agreement we now grant you the
// 	following rights in respect of the Object Code:
//   2.2.1 
// 	the non-exclusive right to Exploit the Object Code on the same
// 	terms and conditions set out in clause 3, provided that any
// 	distribution is done so on the terms of this Agreement and is
// 	accompanied by the Source Code and Executable Code (as
// 	applicable).
// 
// 3. GENERAL OBLIGATIONS
//  3.1 
//  	In consideration of the licence granted in clause 2.1 you now agree:
//   3.1.1 
// 	that when you distribute the Source Code or Executable Code or
// 	any Derivative Works to Recipients you will also include the
// 	terms of this Agreement;
//   3.1.2 
// 	that when you make the Source Code, Executable Code or any
// 	Derivative Works ("Materials") available to download, you will
// 	ensure that Recipients must accept the terms of this Agreement
// 	before being allowed to download such Materials;
//   3.1.3 
// 	that by Exploiting the Source Code or Executable Code you may
// 	not impose any further restrictions on a Recipient's subsequent
// 	Exploitation of the Source Code or Executable Code other than
// 	those contained in the terms and conditions of this Agreement;
//   3.1.4 
// 	not (and not to allow any third party) to profit or make any
// 	charge for the Source Code, or Executable Code, any
// 	Exploitation of the Source Code or Executable Code, or for any
// 	Derivative Works;
//   3.1.5 
// 	not to place any restrictions on the operability of the Source 
// 	Code;
//   3.1.6 
// 	to attach prominent notices to any Derivative Works stating
// 	that you have changed the Source Code or Executable Code and to
// 	include the details anddate of such change; and
//   3.1.7 
//   	not to Exploit the Source Code or Executable Code otherwise than
// 	as expressly permitted by  this Agreement.
// 



#ifndef OGRE_EE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include	"graphics.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// This contains all the scaning of software drawn polygons. For the actual drawing of them, see polysoft.c
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void scan_plain_line ( vertex *point1, vertex *point2 )
{

	int
		x,
		y,
		x2,
		y2,
		dx,
		dy,
		error;

	convert_float_to_int ( point1->i, &x );

	convert_float_to_int ( point1->j, &y );

	convert_float_to_int ( point2->i, &x2 );

	convert_float_to_int ( point2->j, &y2 );

//	x = point1->i;
//	y = point1->j;
//	x2 = point2->i;
//	y2 = point2->j;
//
	if ( y2 < y_min )
	{

		y_min = y2;
	}
	else if ( y2 > y_max )
	{

		y_max = y2;
	}

	if ( y > y2 )
	{

		//
		// Write to the RHS buffer
		//

		dy = ( y - y2 );

		dx = ( x2 - x );

		if ( dx < 0 )
		{

			dx = -dx;
	
			if ( dx > dy )
			{

				error = ( ( dx  ) >> 1 );
			
				while ( x > x2 )
				{

					if ( ( error -= dy ) < 0 )
					{

						error += dx;
			
						lhs_x[y] = x;

						y--;
					}

					x--;
				}

				lhs_x[y] = x;
			}
			else
			{

				error = ( ( dy  ) >> 1 );
			
				while ( y > y2 )
				{

					lhs_x[y] = x;
	
					if ( ( error -= dx ) < 0 )
					{

						error += dy;
			
						x--;
					}
	
					y--;
				}
	
				lhs_x[y] = x;
			}
		}
		else
		{

			if ( dx > dy )
			{

				// Octant 1.

				error = ( ( dx ) >> 1 );

				lhs_x[y] = x;

				while ( x < x2 )
				{

					x++;

					if ( ( error -= dy ) < 0 )
					{

						error += dx;

						y --;

						lhs_x[y] = x;
					}

				}
			}
			else
			{

				error = ( ( dy ) >> 1 );
			
				while ( y > y2 )
				{

					lhs_x[y] = x;
	
					if ( ( error -= dx ) < 0 )
					{

						error += dy;
			
						x ++;
					}
	
					y--;
				}
	
				lhs_x[y] = x;
			}
		}
	}
	else
	{

		//
		// Write to the LHS buffer
		//


		dy = ( y2 - y );

		if ( dy == 0 )
		{

			return;
		}

		dx = ( x2 - x );

		if ( dx < 0 )
		{

			dx = -dx;
	
			if ( dx > dy )
			{

				//
				// Octant 5.
				//

				error = (  dx >> 1 );

				rhs_x[y] = x;

				while ( x > x2 )
				{

					x--;

					if ( ( error -= dy ) < 0 )
					{

						error += dx;
			
						y++;

						rhs_x[y] = x;
					}
				}
			}
			else
			{

				error = ( ( dy  ) >> 1 );
			
				while ( y < y2 )
				{

					rhs_x[y] = x;
	
					if ( ( error -= dx ) < 0 )
					{

						error += dy;
			
						x--;
					}
	
					y++;
				}
	
				rhs_x[y] = x;
			}
		}
		else
		{

			if ( dx > dy )
			{

				error = ( ( dx ) >> 1 );
			
				while ( x < x2 )
				{

					if ( ( error -= dy ) < 0 )
					{

						error += dx;
			
						rhs_x[y] = x;

						y ++;
					}

					x++;
				}

				rhs_x[y] = x;
			}
			else
			{

				error = ( ( dy ) >> 1 );
			
				while ( y < y2 )
				{

					rhs_x[y] = x;
	
					if ( ( error -= dx ) < 0 )
					{

						error += dy;
			
						x ++;
					}
	
					y++;
				}
	
				rhs_x[y] = x;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void scan_zbuffer_plain_line ( vertex *point1, vertex *point2 )
{

	int
		x,
		y,
		x2,
		y2,
		dx,
		dy,
		error;

	float
		q,
		dq;

	convert_float_to_int ( point1->i, &x );

	convert_float_to_int ( point1->j, &y );

	convert_float_to_int ( point2->i, &x2 );

	convert_float_to_int ( point2->j, &y2 );

	q = point1->q;

	dq = point2->q - q;

	if ( y2 < y_min )
	{

		y_min = y2;
	}
	else if ( y2 > y_max )
	{

		y_max = y2;
	}

	if ( y > y2 )
	{

		//
		// Write to the LHS buffer
		//

		dy = ( y - y2 );

		dx = ( x2 - x );

		if ( dx < 0 )
		{

			dx = -dx;
	
			if ( dx > dy )
			{

				error = ( ( dx  ) >> 1 );

				dq /= ( dx + 1 );
			
				while ( x > x2 )
				{

					if ( ( error -= dy ) < 0 )
					{

						error += dx;
			
						lhs_x[y] = x;

						lhs_q[y] = q;

						y--;
					}

					x--;

					q += dq;
				}

				lhs_x[y] = x;

				lhs_q[y] = q;
			}
			else
			{

				error = ( ( dy  ) >> 1 );
			
				dq /= ( dy + 1 );
			
				while ( y > y2 )
				{

					lhs_x[y] = x;

					lhs_q[y] = q;
	
					if ( ( error -= dx ) < 0 )
					{

						error += dy;

						x--;
					}
	
					y--;

					q += dq;
				}
	
				lhs_x[y] = x;

				lhs_q[y] = q;
			}
		}
		else
		{

			if ( dx > dy )
			{

				// Octant 1.

				error = ( ( dx ) >> 1 );

				dq /= ( dx + 1 );

				lhs_x[y] = x;

				lhs_q[y] = q;

				while ( x < x2 )
				{

					x++;

					q += dq;

					if ( ( error -= dy ) < 0 )
					{

						error += dx;

						y --;

						lhs_x[y] = x;

						lhs_q[y] = q;
					}
				}
			}
			else
			{

				error = ( ( dy ) >> 1 );

				dq /= ( dy + 1 );
			
				while ( y > y2 )
				{

					lhs_x[y] = x;

					lhs_q[y] = q;
	
					if ( ( error -= dx ) < 0 )
					{

						error += dy;
			
						x ++;
					}
	
					y--;

					q += dq;
				}
	
				lhs_x[y] = x;

				lhs_q[y] = q;
			}
		}
	}
	else
	{

		//
		// Write to the LHS buffer
		//


		dy = ( y2 - y );

		if ( dy == 0 )
		{

			return;
		}

		dx = ( x2 - x );

		if ( dx < 0 )
		{

			dx = -dx;
	
			if ( dx > dy )
			{

				//
				// Octant 5.
				//

				error = (  dx >> 1 );

				dq /= ( dx + 1 );

				rhs_x[y] = x;

				rhs_q[y] = q;

				while ( x > x2 )
				{

					x--;

					q += dq;

					if ( ( error -= dy ) < 0 )
					{

						error += dx;
			
						y++;

						rhs_x[y] = x;

						rhs_q[y] = q;
					}
				}
			}
			else
			{

				error = ( ( dy  ) >> 1 );

				dq /= ( dy + 1 );
			
				while ( y < y2 )
				{

					rhs_x[y] = x;

					rhs_q[y] = q;
	
					if ( ( error -= dx ) < 0 )
					{

						error += dy;
			
						x--;
					}
	
					y++;

					q += dq;
				}
	
				rhs_x[y] = x;

				rhs_q[y] = q;
			}
		}
		else
		{

			if ( dx > dy )
			{

				error = ( ( dx ) >> 1 );

				dq /= ( dx + 1 );
			
				while ( x < x2 )
				{

					if ( ( error -= dy ) < 0 )
					{

						error += dx;
			
						rhs_x[y] = x;

						rhs_q[y] = q;

						y ++;
					}

					x++;

					q += dq;
				}

				rhs_x[y] = x;

				rhs_q[y] = q;
			}
			else
			{

				error = ( ( dy ) >> 1 );

				dq /= ( dy + 1 );
			
				while ( y < y2 )
				{

					rhs_x[y] = x;

					rhs_q[y] = q;
	
					if ( ( error -= dx ) < 0 )
					{

						error += dy;
			
						x ++;
					}
	
					y++;

					q += dq;
				}
	
				rhs_x[y] = x;

				rhs_q[y] = q;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void scan_gouraud_shaded_line ( vertex *point1, vertex *point2 )
{

	int
		x,
		y,
		x2,
		y2,
		dx,
		dy,
		error;

	float
		intensity,
		dintensity;

	convert_float_to_int ( point1->i, &x );

	convert_float_to_int ( point1->j, &y );

	convert_float_to_int ( point2->i, &x2 );

	convert_float_to_int ( point2->j, &y2 );

	if ( y2 < y_min )
	{

		y_min = y2;
	}
	else if	( y2 > y_max )
	{

		y_max = y2;
	}

	intensity = point1->intensity;

	dintensity = point2->intensity - intensity;

	if ( y > y2 )
	{
		// Write to the RHS buffer

		dy = ( y - y2 );
	
		if ( ( dx = x2 - x ) < 0 )
		{

			dx = -dx;
	
			if ( dx > dy )
			{

				error = ( ( dx  ) >> 1 );

				dintensity /= dx;
			
				while ( x > x2 )
				{

					if ( ( error -= dy ) < 0 )
					{

						error += dx;
			
						lhs_x[y] = x;

						lhs_i[y] = intensity;

						y--;
					}

					x--;

					intensity += dintensity;
				}

				lhs_x[y] = x;

				lhs_i[y] = intensity;
			}
			else
			{

				error = ( ( dy  ) >> 1 );

				dintensity /= dy;
			
				while ( y > y2 )
				{

					lhs_x[y] = x;

					lhs_i[y] = intensity;
	
					if ( ( error -= dx ) < 0 )
					{

						error += dy;
			
						x--;
					}
	
					y--;

					intensity += dintensity;
				}
	
				lhs_x[y] = x;

				lhs_i[y] = intensity;
			}
		}
		else
		{
			if ( dx > dy )
			{
				// Octant 1.

				error = ( ( dx ) >> 1 );

				dintensity /= dx;

				lhs_x[y] = x;

				lhs_i[y] = intensity;

				while ( x < x2 )
				{

					x++;

					intensity += dintensity;

					if ( ( error -= dy ) < 0 )
					{

						error += dx;

						y --;

						lhs_x[y] = x;

						lhs_i[y] = intensity;
					}

				}
			}
			else
			{
				error = ( ( dy ) >> 1 );

				dintensity /= dy;
			
				while ( y > y2 )
				{

					lhs_x[y] = x;

					lhs_i[y] = intensity;
	
					if ( ( error -= dx ) < 0 )
					{

						error += dy;
			
						x ++;
					}
	
					y--;

					intensity += dintensity;
				}
	
				lhs_x[y] = x;

				lhs_i[y] = intensity;
			}
		}
	}
	else
	{
		
		//
		// Write to the LHS buffer
		//

		dy = ( y2 - y );

		if ( dy == 0 )
		{

			return;
		}

		dx = ( x2 - x );

		if ( dx < 0 )
		{

			dx = -dx;
	
			if ( dx > dy )
			{

				//
				// Octant 5.
				//

				error = (  dx >> 1 );

				dintensity /= dx;

				rhs_x[y] = x;

				rhs_i[y] = intensity;

				while ( x > point2->i )
				{

					x--;

					intensity += dintensity;

					if ( ( error -= dy ) < 0 )
					{

						error += dx;
			
						y++;

						rhs_x[y] = x;

						rhs_i[y] = intensity;
					}
				}
			}
			else
			{

				error = ( ( dy  ) >> 1 );

				dintensity /= dy;
			
				while ( y < point2->j )
				{

					rhs_x[y] = x;
	
					rhs_i[y] = intensity;

					if ( ( error -= dx ) < 0 )
					{

						error += dy;
			
						x--;
					}
	
					y++;

					intensity += dintensity;
				}
	
				rhs_x[y] = x;

				rhs_i[y] = intensity;
			}
		}
		else
		{

			if ( dx > dy )
			{

				error = ( ( dx ) >> 1 );

				dintensity /= dx;
			
				while ( x < point2->i )
				{

					if ( ( error -= dy ) < 0 )
					{

						error += dx;
			
						rhs_x[y] = x;

						rhs_i[y] = intensity;

						y ++;
					}

					x++;

					intensity += dintensity;
				}

				rhs_x[y] = x;

				rhs_i[y] = intensity;
			}
			else
			{

				error = ( ( dy ) >> 1 );

				dintensity /= dy;
			
				while ( y < point2->j )
				{

					rhs_x[y] = x;

					rhs_i[y] = intensity;
	
					if ( ( error -= dx ) < 0 )
					{

						error += dy;
			
						x ++;
					}
	
					y++;

					intensity += dintensity;
				}
	
				rhs_x[y] = x;

				rhs_i[y] = intensity;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void scan_plain_textured_line ( vertex *point1, vertex *point2 )
{

	int
		x,
		y,
		x2,
		y2,
		dx,
		dy,
		error;

	float
		u,
		v,
		du,
		dv;

	convert_float_to_int ( point1->i, &x );

	convert_float_to_int ( point1->j, &y );

	convert_float_to_int ( point2->i, &x2 );

	convert_float_to_int ( point2->j, &y2 );

	if ( y2 < y_min )
	{

		y_min = y2;
	}
	else if	( y2 > y_max )
	{

		y_max = y2;
	}

	u = point1->u;

	v = point1->v;

	du = point2->u - u;

	dv = point2->v - v;

	if ( y > y2 )
	{
		// Write to the RHS buffer

		dy = ( y - y2 );
	
		if ( ( dx = x2 - x ) < 0 )
		{

			dx = -dx;
	
			if ( dx > dy )
			{

				error = ( ( dx  ) >> 1 );

				du /= dx;
				dv /= dx;

				while ( x > x2 )
				{

					if ( ( error -= dy ) < 0 )
					{

						error += dx;
			
						lhs_x[y] = x;
						lhs_u[y] = u;
						lhs_v[y] = v;

						y--;
					}

					x--;
					u += du;
					v += dv;
				}

				lhs_x[y] = x;
				lhs_u[y] = u;
				lhs_v[y] = v;
			}
			else
			{

				error = ( ( dy  ) >> 1 );

				du /= dy;
				dv /= dy;
			
				while ( y > y2 )
				{

					lhs_x[y] = x;
					lhs_u[y] = u;
					lhs_v[y] = v;
	
					if ( ( error -= dx ) < 0 )
					{

						error += dy;
			
						x--;
					}
	
					y--;
					u += du;
					v += dv;
				}
	
				lhs_x[y] = x;
				lhs_u[y] = u;
				lhs_v[y] = v;
			}
		}
		else
		{
			if ( dx > dy )
			{
				// Octant 1.

				error = ( ( dx ) >> 1 );

				du /= dx;
				dv /= dx;

				lhs_x[y] = x;
				lhs_u[y] = u;
				lhs_v[y] = v;

				while ( x < x2 )
				{

					x++;
					u += du;
					v += dv;

					if ( ( error -= dy ) < 0 )
					{

						error += dx;

						y --;

						lhs_x[y] = x;
						lhs_u[y] = u;
						lhs_v[y] = v;
					}

				}
			}
			else
			{
				error = ( ( dy ) >> 1 );

				du /= dy;
				dv /= dy;
			
				while ( y > y2 )
				{

					lhs_x[y] = x;
					lhs_u[y] = u;
					lhs_v[y] = v;
	
					if ( ( error -= dx ) < 0 )
					{

						error += dy;
			
						x ++;
					}
	
					y--;

					u += du;
					v += dv;
				}
	
				lhs_x[y] = x;
				lhs_u[y] = u;
				lhs_v[y] = v;
			}
		}
	}
	else
	{
		
		//
		// Write to the LHS buffer
		//

		dy = ( y2 - y );

		if ( dy == 0 )
		{

			return;
		}

		dx = ( x2 - x );

		if ( dx < 0 )
		{

			dx = -dx;
	
			if ( dx > dy )
			{

				//
				// Octant 5.
				//

				error = (  dx >> 1 );

				du /= dx;
				dv /= dx;

				rhs_x[y] = x;
				rhs_u[y] = u;
				rhs_v[y] = v;

				while ( x > point2->i )
				{

					x--;
					u += du;
					v += dv;

					if ( ( error -= dy ) < 0 )
					{

						error += dx;
			
						y++;

						rhs_x[y] = x;
						rhs_u[y] = u;
						rhs_v[y] = v;
					}
				}
			}
			else
			{

				error = ( ( dy  ) >> 1 );

				du /= dy;
				dv /= dy;
			
				while ( y < point2->j )
				{

					rhs_x[y] = x;
					rhs_u[y] = u;
					rhs_v[y] = v;

					if ( ( error -= dx ) < 0 )
					{

						error += dy;
			
						x--;
					}
	
					y++;
					u += du;
					v += dv;
				}
	
				rhs_x[y] = x;
				rhs_u[y] = u;
				rhs_v[y] = v;
			}
		}
		else
		{

			if ( dx > dy )
			{

				error = ( ( dx ) >> 1 );

				du /= dx;
				dv /= dx;
			
				while ( x < point2->i )
				{

					if ( ( error -= dy ) < 0 )
					{

						error += dx;
			
						rhs_x[y] = x;
						rhs_u[y] = u;
						rhs_v[y] = v;

						y ++;
					}

					x++;
					u += du;
					v += dv;
				}

				rhs_x[y] = x;
				rhs_u[y] = u;
				rhs_v[y] = v;
			}
			else
			{

				error = ( ( dy ) >> 1 );

				du /= dy;
				dv /= dy;
			
				while ( y < point2->j )
				{

					rhs_x[y] = x;
					rhs_u[y] = u;
					rhs_v[y] = v;
	
					if ( ( error -= dx ) < 0 )
					{

						error += dy;
			
						x ++;
					}
	
					y++;
					u += du;
					v += dv;
				}
	
				rhs_x[y] = x;
				rhs_u[y] = u;
				rhs_v[y] = v;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void scan_gouraud_shaded_textured_line ( vertex *point1, vertex *point2 )
{

	int
		x,
		y,
		x2,
		y2,
		dx,
		dy,
		error;

	float
		u,
		v,
		du,
		dv,
		intensity,
		dintensity;

	convert_float_to_int ( point1->i, &x );

	convert_float_to_int ( point1->j, &y );

	convert_float_to_int ( point2->i, &x2 );

	convert_float_to_int ( point2->j, &y2 );

	if ( y2 < y_min )
	{

		y_min = y2;
	}
	else if	( y2 > y_max )
	{

		y_max = y2;
	}

	u = point1->u;

	v = point1->v;

	intensity = point1->intensity;

	du = point2->u - u;

	dv = point2->v - v;

	dintensity = point2->intensity - intensity;

	if ( y > y2 )
	{
		// Write to the RHS buffer

		dy = ( y - y2 );
	
		if ( ( dx = x2 - x ) < 0 )
		{

			dx = -dx;
	
			if ( dx > dy )
			{

				error = ( ( dx  ) >> 1 );

				du /= dx;
				dv /= dx;
				dintensity /= dx;

				while ( x > x2 )
				{

					if ( ( error -= dy ) < 0 )
					{

						error += dx;
			
						lhs_x[y] = x;
						lhs_u[y] = u;
						lhs_v[y] = v;
						lhs_i[y] = intensity;

						y--;
					}

					x--;
					u += du;
					v += dv;
					intensity += dintensity;
				}

				lhs_x[y] = x;
				lhs_u[y] = u;
				lhs_v[y] = v;
				lhs_i[y] = intensity;
			}
			else
			{

				error = ( ( dy  ) >> 1 );

				du /= dy;
				dv /= dy;
				dintensity /= dy;
			
				while ( y > y2 )
				{

					lhs_x[y] = x;
					lhs_u[y] = u;
					lhs_v[y] = v;
					lhs_i[y] = intensity;
	
					if ( ( error -= dx ) < 0 )
					{

						error += dy;
			
						x--;
					}
	
					y--;
					u += du;
					v += dv;
					intensity += dintensity;
				}
	
				lhs_x[y] = x;
				lhs_u[y] = u;
				lhs_v[y] = v;
				lhs_i[y] = intensity;
			}
		}
		else
		{
			if ( dx > dy )
			{
				// Octant 1.

				error = ( ( dx ) >> 1 );

				du /= dx;
				dv /= dx;
				dintensity /= dx;

				lhs_x[y] = x;
				lhs_u[y] = u;
				lhs_v[y] = v;
				lhs_i[y] = intensity;

				while ( x < x2 )
				{

					x++;
					u += du;
					v += dv;
					intensity += dintensity;

					if ( ( error -= dy ) < 0 )
					{

						error += dx;

						y --;

						lhs_x[y] = x;
						lhs_u[y] = u;
						lhs_v[y] = v;
						lhs_i[y] = intensity;
					}

				}
			}
			else
			{
				error = ( ( dy ) >> 1 );

				du /= dy;
				dv /= dy;
				dintensity /= dy;
			
				while ( y > y2 )
				{

					lhs_x[y] = x;
					lhs_u[y] = u;
					lhs_v[y] = v;
					lhs_i[y] = intensity;
	
					if ( ( error -= dx ) < 0 )
					{

						error += dy;
			
						x ++;
					}
	
					y--;

					u += du;
					v += dv;
					intensity += dintensity;
				}
	
				lhs_x[y] = x;
				lhs_u[y] = u;
				lhs_v[y] = v;
				lhs_i[y] = intensity;
			}
		}
	}
	else
	{
		
		//
		// Write to the LHS buffer
		//

		dy = ( y2 - y );

		if ( dy == 0 )
		{

			return;
		}

		dx = ( x2 - x );

		if ( dx < 0 )
		{

			dx = -dx;
	
			if ( dx > dy )
			{

				//
				// Octant 5.
				//

				error = (  dx >> 1 );

				du /= dx;
				dv /= dx;
				dintensity /= dx;

				rhs_x[y] = x;
				rhs_u[y] = u;
				rhs_v[y] = v;
				rhs_i[y] = intensity;

				while ( x > point2->i )
				{

					x--;
					u += du;
					v += dv;
					intensity += dintensity;

					if ( ( error -= dy ) < 0 )
					{

						error += dx;
			
						y++;

						rhs_x[y] = x;
						rhs_u[y] = u;
						rhs_v[y] = v;
						rhs_i[y] = intensity;
					}
				}
			}
			else
			{

				error = ( ( dy  ) >> 1 );

				du /= dy;
				dv /= dy;
				dintensity /= dy;
			
				while ( y < point2->j )
				{

					rhs_x[y] = x;
					rhs_u[y] = u;
					rhs_v[y] = v;
					rhs_i[y] = intensity;

					if ( ( error -= dx ) < 0 )
					{

						error += dy;
			
						x--;
					}
	
					y++;
					u += du;
					v += dv;
					intensity += dintensity;
				}
	
				rhs_x[y] = x;
				rhs_u[y] = u;
				rhs_v[y] = v;
				rhs_i[y] = intensity;
			}
		}
		else
		{

			if ( dx > dy )
			{

				error = ( ( dx ) >> 1 );

				du /= dx;
				dv /= dx;
				dintensity /= dx;
			
				while ( x < point2->i )
				{

					if ( ( error -= dy ) < 0 )
					{

						error += dx;
			
						rhs_x[y] = x;
						rhs_u[y] = u;
						rhs_v[y] = v;
						rhs_i[y] = intensity;

						y ++;
					}

					x++;
					u += du;
					v += dv;
					intensity += dintensity;
				}

				rhs_x[y] = x;
				rhs_u[y] = u;
				rhs_v[y] = v;
				rhs_i[y] = intensity;
			}
			else
			{

				error = ( ( dy ) >> 1 );

				du /= dy;
				dv /= dy;
				dintensity /= dy;
			
				while ( y < point2->j )
				{

					rhs_x[y] = x;
					rhs_u[y] = u;
					rhs_v[y] = v;
					rhs_i[y] = intensity;
	
					if ( ( error -= dx ) < 0 )
					{

						error += dy;
			
						x ++;
					}
	
					y++;
					u += du;
					v += dv;
					intensity += dintensity;
				}
	
				rhs_x[y] = x;
				rhs_u[y] = u;
				rhs_v[y] = v;
				rhs_i[y] = intensity;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
