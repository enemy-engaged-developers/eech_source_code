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



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "graphics.h"

#include "misc.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum pictypes
{

	NO_TYPE,
	PIC_ILBM,
	PIC_PBM,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void pixelise ( unsigned char *pix, unsigned char *p, int length );

static void ilbm_convert ( unsigned char *source, unsigned char *destination );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static lbm_image
	*current_lbm = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int load_lbm_image ( const char *filename, lbm_image *lbm )
{
	
	FILE
		*fp_in;
		
	int
		type,
		form_length,
		rounded_width,
		header_length = 0,
		body_length = 0,
		cmap_length = 0,
		colours = 0,
		i = 0,
		block_length = 0,
		picture_type = NO_TYPE;

	unsigned char
		*ilbm_data = NULL,
		*body = NULL;

	// JB 030311 Enable running out of separate directories
	if ( ( fp_in = safe_fopen ( filename, "rb" ) ) == NULL )
	{

		debug_log ( "Unable to open file %s during load_lbm_image", filename );

		return (FALSE);
	}

	if ( ( get_iff_type ( fp_in ) ) != FORM)
	{

		fclose ( fp_in );

		debug_log ( "File not an IFF file in load_lbm_image, file: %s", filename );
		
		return ( FALSE );
	}

	form_length = iff_int_read (fp_in);

	current_lbm = lbm;

	while ( ( form_length >0 ) && ( ( type = get_iff_type ( fp_in ) ) != BODY ) )
	{
		
		switch ( type )
		{
			
			case	ILBM:
			{
				
				picture_type = PIC_ILBM;
				
				break;
			}

			case	PBM:
			{
				
				picture_type = PIC_PBM;
				
				break;
			}

			case	BMHD:
			{
				
				header_length = iff_int_read ( fp_in );
				
				lbm->header.width = iff_short_int_read (fp_in);
			
				lbm->header.height = iff_short_int_read (fp_in);
			
				lbm->header.x = iff_short_int_read (fp_in);
			
				lbm->header.y = iff_short_int_read (fp_in);
			
				fread (&lbm->header.nPlanes, 1, 1, fp_in);
			
				fread (&lbm->header.masking, 1, 1, fp_in);
			
				fread (&lbm->header.compression, 1, 1, fp_in);
			
				fread (&lbm->header.reserved1, 1, 1, fp_in);
			
				lbm->header.transparentColour = iff_short_int_read (fp_in);
			
				fread (&lbm->header.xAspect, 1, 1, fp_in);
			
				fread (&lbm->header.yAspect, 1, 1, fp_in);
			
				lbm->header.pageWidth = iff_short_int_read (fp_in);
			
				lbm->header.pageHeight = iff_short_int_read (fp_in);

				form_length -= ( header_length + 4 );
				
				break;
			}

			case	CMAP:
			{
				
				cmap_length = iff_int_read ( fp_in );
				
				form_length -= ( cmap_length + 4 );

				colours = ( cmap_length / 3 );
				
				for ( i = 0; i < colours; i++ )
				{

					fread ( &lbm->palette[i].peRed, 1, 1, fp_in );
					fread ( &lbm->palette[i].peGreen, 1, 1, fp_in );
					fread ( &lbm->palette[i].peBlue, 1, 1, fp_in );
				}
				
				break;
			}

			default:
			{
				
				block_length = iff_int_read ( fp_in );
				
				if ( ( block_length & 1 ) == 1 )
				{

					block_length++;
				}
				
				fseek ( fp_in, block_length, SEEK_CUR );
				
				form_length -= ( block_length + 4 );
				
				break;
			}
		}
	}

	if ( type == BODY )
	{
		
		body_length = iff_int_read ( fp_in );
		
		form_length -= ( body_length + 4 );

		if ( ( body = safe_malloc ( body_length ) ) == NULL )
		{
			
			debug_log ( "No memory for source image data while loading %s in load_lbm_image", filename );

			fclose ( fp_in );

			return ( FALSE );
		}

		fread ( body, body_length, 1, fp_in );

		if ( ( lbm->image = safe_malloc ( lbm->header.width * lbm->header.height ) ) == NULL )
		{

			debug_log ("No memory for lbm image while loading %s", filename );

			fclose ( fp_in );

			return ( FALSE );
		}

		if ( picture_type == PIC_ILBM )
		{

			rounded_width = ( lbm->header.width + ( lbm->header.width % 8 ) );

			if ( ( ilbm_data = safe_malloc ( rounded_width * ( lbm->header.height + 16 ) ) ) == NULL )
			{

				debug_log ("No memory for ilbm data while loading %s", filename );

				fclose ( fp_in );

				return ( FALSE );
			}

			if ( lbm->header.compression )
			{

				pixelise ( ilbm_data, body, body_length );
			}
			else
			{

				memcpy ( ilbm_data, body, body_length );
			}

			ilbm_convert ( ilbm_data, lbm->image );

			safe_free ( ilbm_data );
		}
		else
		{
			
			if ( lbm->header.compression )
			{

				pixelise ( lbm->image, body, body_length );
			}
			else
			{

				memcpy ( lbm->image, body, body_length );
			}
		}

		safe_free ( body );

		body = NULL;
	}
	else
	{

		debug_log ( "No BODY data in load_lbm_image, during file %s", filename );

		fclose ( fp_in );
	
		return ( FALSE );
	}

	fclose ( fp_in );

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ilbm_convert ( unsigned char *source, unsigned char *destination )
{
	
	int
		byte_width;

	int
		rounded_width;

	int
		x,
		y;
		
	unsigned char
		*plane0,
		*plane1,
		*plane2,
		*plane3,
		*plane4,
		*plane5,
		*plane6,
		*plane7;

	rounded_width = ( ( current_lbm->header.width ) + ( current_lbm->header.width % 8 ) );

	byte_width = rounded_width / 8;

	for ( y = 0; y < current_lbm->header.height; y++ )
	{
		
		plane0 = source + (rounded_width * y);
		
		plane1 = plane0 + byte_width;

		plane2 = plane1 + byte_width;

		plane3 = plane2 + byte_width;

		plane4 = plane3 + byte_width;

		plane5 = plane4 + byte_width;

		plane6 = plane5 + byte_width;

		plane7 = plane6 + byte_width;

		for ( x=0; x < current_lbm->header.width; x+= 8 )
		{
			
			*destination++ = ( ( ( *plane7 & 0x80 ) ) |
									 ( ( *plane6 & 0x80 ) >> 1 ) |
									 ( ( *plane5 & 0x80 ) >> 2 ) |
									 ( ( *plane4 & 0x80 ) >> 3 ) |
									 ( ( *plane3 & 0x80 ) >> 4 ) |
									 ( ( *plane2 & 0x80 ) >> 5 ) |
									 ( ( *plane1 & 0x80 ) >> 6 ) |
									 ( ( *plane0 & 0x80 ) >> 7 ) );

			*destination++ = ( ( ( *plane7 & 0x40 ) << 1 ) |
									 ( ( *plane6 & 0x40 ) ) |
									 ( ( *plane5 & 0x40 ) >> 1 ) |
									 ( ( *plane4 & 0x40 ) >> 2 ) |
									 ( ( *plane3 & 0x40 ) >> 3 ) |
									 ( ( *plane2 & 0x40 ) >> 4 ) |
									 ( ( *plane1 & 0x40 ) >> 5 ) |
									 ( ( *plane0 & 0x40 ) >> 6 ) );

			*destination++ = ( ( ( *plane7 & 0x20 ) << 2 ) |
									 ( ( *plane6 & 0x20 ) << 1 ) |
									 ( ( *plane5 & 0x20 ) ) |
									 ( ( *plane4 & 0x20 ) >> 1 ) |
									 ( ( *plane3 & 0x20 ) >> 2 ) |
									 ( ( *plane2 & 0x20 ) >> 3 ) |
									 ( ( *plane1 & 0x20 ) >> 4 ) |
									 ( ( *plane0 & 0x20 ) >> 5 ) );

			*destination++ = ( ( ( *plane7 & 0x10 ) << 3 ) |
									 ( ( *plane6 & 0x10 ) << 2 ) |
									 ( ( *plane5 & 0x10 ) << 1 ) |
									 ( ( *plane4 & 0x10 ) ) |
									 ( ( *plane3 & 0x10 ) >> 1 ) |
									 ( ( *plane2 & 0x10 ) >> 2 ) |
									 ( ( *plane1 & 0x10 ) >> 3 ) |
									 ( ( *plane0 & 0x10 ) >> 4 ) );

			*destination++ = ( ( ( *plane7 & 0x08 ) << 4 ) |
									 ( ( *plane6 & 0x08 ) << 3 ) |
									 ( ( *plane5 & 0x08 ) << 2 ) |
									 ( ( *plane4 & 0x08 ) << 1 ) |
									 ( ( *plane3 & 0x08 ) ) |
									 ( ( *plane2 & 0x08 ) >> 1 ) |
									 ( ( *plane1 & 0x08 ) >> 2 ) |
									 ( ( *plane0 & 0x08 ) >> 3 ) );

			*destination++ = ( ( ( *plane7 & 0x04 ) << 5 ) |
									 ( ( *plane6 & 0x04 ) << 4 ) |
									 ( ( *plane5 & 0x04 ) << 3 ) |
									 ( ( *plane4 & 0x04 ) << 2 ) |
									 ( ( *plane3 & 0x04 ) << 1 ) |
									 ( ( *plane2 & 0x04 ) ) |
									 ( ( *plane1 & 0x04 ) >> 1 ) |
									 ( ( *plane0 & 0x04 ) >> 2 ) );

			*destination++ = ( ( ( *plane7 & 0x02 ) << 6 ) |
									 ( ( *plane6 & 0x02 ) << 5 ) |
									 ( ( *plane5 & 0x02 ) << 4 ) |
									 ( ( *plane4 & 0x02 ) << 3 ) |
									 ( ( *plane3 & 0x02 ) << 2 ) |
									 ( ( *plane2 & 0x02 ) << 1 ) |
									 ( ( *plane1 & 0x02 ) ) |
									 ( ( *plane0 & 0x02 ) >> 1 ) );

			*destination++ = ( ( ( *plane7 & 0x01 ) << 7) |
									 ( ( *plane6 & 0x01 ) << 6) |
									 ( ( *plane5 & 0x01 ) << 5) |
									 ( ( *plane4 & 0x01 ) << 4) |
									 ( ( *plane3 & 0x01 ) << 3) |
									 ( ( *plane2 & 0x01 ) << 2) |
									 ( ( *plane1 & 0x01 ) << 1) |
									 ( ( *plane0 & 0x01 )));

			plane0 ++;
			plane1 ++;
			plane2 ++;
			plane3 ++;
			plane4 ++;
			plane5 ++;
			plane6 ++;
			plane7 ++;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pixelise ( unsigned char *pix, unsigned char *p, int length )
{

	unsigned char
		v,
		c;

	while ( length > 0 )
	{
		
		c = *p ++;
		
		length --;
		
		if ( c >= 128 )
		{

			c --;

			v = *p;

			while ( c )
			{

				c ++;

				*pix ++ = *p;
			}

			p ++;

			length --;
		}
		else
		{	

			c ++;
			
			while ( c )
			{

				c --;

				*pix ++ = *p ++;

				length --;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

