.387
.386p
.model flat

		PUBLIC	fill_flat_shaded_textured_horizontal_line_
		PUBLIC	fill_gouraud_shaded_wrapped_textured_horizontal_line_
		
		EXTRN _stack_register_location:DWORD PTR
		EXTRN _zbuffer_x1:DWORD PTR
		EXTRN _zbuffer_x2:DWORD PTR
		EXTRN _idq2:DWORD PTR
		EXTRN _idq:DWORD PTR
		EXTRN _idu:DWORD PTR
		EXTRN _idv:DWORD PTR
		EXTRN _idufraction:DWORD PTR
		EXTRN _idvfraction:DWORD PTR
		EXTRN	_uvstepvcarry:DWORD PTR
		EXTRN _texture_data_ptr:DWORD PTR
		EXTRN _texture_shading_table_address:DWORD PTR
		EXTRN _idintensity:DWORD PTR
		EXTRN _stored_zbuffer_length:DWORD PTR
		EXTRN	_pixels_to_plot:DWORD PTR
		
_TEXT		SEGMENT
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
fill_flat_shaded_textured_horizontal_line_:

	; Entrance to routine:
	; esi = BYTE PTR texture_data
	; edi = WORD PTR screen
	; ecx = DWORD length
	; eax = DWORD u
	; ebx = DWORD v
	
	push	ebp
	mov	_stack_register_location, esp
	mov	esp, _texture_shading_table_address
	xor	edx, edx
	cmp	ecx, 2
	jle	endloop
loop1:
	add	ebx, _idvfraction
	mov	dl, [ esi ]
	sbb	ebp, ebp
	add	eax, _idufraction
	mov	dx, word ptr [ edx * 2 + esp ]
	lea	ecx, [ ecx - 2 ]
	adc	esi, [ _uvstepvcarry + ebp*4 + 4 ]
	mov	[ edi ], dx
	xor	edx, edx
	mov	dl, [ esi ]
	add	ebx, _idvfraction
	sbb	ebp, ebp
	lea	edi, [ edi + 4 ]
	mov	dx, word ptr [ edx * 2 + esp ]
	add	eax, _idufraction
	adc	esi, [ _uvstepvcarry + ebp*4 + 4 ]
	mov	[ edi - 2 ], dx
	xor	edx, edx
	cmp	ecx, 2
	jg	loop1
	
endloop:
	mov	dl, [ esi ]
	add	ebx, _idvfraction
	sbb	ebp, ebp
	lea	edi, [ edi + 2 ]
	mov	dx, word ptr [ edx * 2 + esp ]
	add	eax, _idufraction
	adc	esi, [ _uvstepvcarry + ebp*4 + 4 ]
	mov	[ edi - 2 ], dx
	xor	edx, edx
	dec	ecx
	jg		endloop
	mov	esp, _stack_register_location
	pop	ebp
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
fill_gouraud_shaded_wrapped_textured_horizontal_line_:

	; Entrance to routine:
	; edi = WORD PTR screen
	; ecx = DWORD length
	; eax = DWORD u
	; ebx = DWORD v
	; esi = DWORD intensity
	
	push	ebp
	mov	_stack_register_location, esp
	
	mov	ebp, ebx
	shr	ebp, 10
	
fill_gouraud_shaded_wrapped_textured_horizontal_line_loop1:
	mov	edx, eax
	and	ebp, 0xfc0
	
	shr	edx, 16
	add	ebp, _texture_data_ptr
	
	and	edx, 0x3f
	mov	esp, esi
	
	shr	esp, 7
	add	ebp, edx
	
	and	esp, 0x3e00
	xor	edx, edx
	
	mov	dl, [ ebp ]
	add	esp, _texture_shading_table_address
	
	add	ebx, _idv
	add	esi, _idintensity
	
	mov	dx, [ esp + edx * 2 ]
	add	eax, _idu
	
	mov	[ edi ], dx
	mov	ebp, ebx
	
	shr	ebp, 10
	lea	edi, [ edi + 2 ]
	
	dec	ecx
	jg		fill_gouraud_shaded_wrapped_textured_horizontal_line_loop1
	
	mov	esp, _stack_register_location
	pop	ebp
	ret
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
_TEXT		ENDS
		END
