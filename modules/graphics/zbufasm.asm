.387
.386p
.model flat
		PUBLIC	construct_assembler_zbuffer_rle_
		EXTRN _zbuffer_x1:DWORD PTR
		EXTRN _zbuffer_x2:DWORD PTR
		EXTRN _idq2:DWORD PTR
		EXTRN _idq:DWORD PTR
		EXTRN _stored_zbuffer_length:DWORD PTR
		EXTRN	_pixels_to_plot:DWORD PTR
_TEXT		SEGMENT
		
construct_assembler_zbuffer_rle_:

	; Entrance to routine:
	; ebx = DWORD initial_q
	; ecx = DWORD length
	; esi = WORD PTR zbuffer_line
	; edi = WORD PTR rle_instructions
	; eax = DWORD x1
	; edx = DWORD x2
	
	push	ebp
	mov	ebp, dword ptr _idq2
	
	;
	; We need to figure out here how long the double pixel loop continues for.
	;		There will always BE a double pixel loop, as with lengths of 4 and more this is guaranteed
	;		and we have a precondition for this routine that it IS 4 or more pixels
	;
	;	The formula for the double pixel loop length is:
	;
	;		( length >> 1 ) - ( x1 | x2 ) & 1 )
	;			( ecx >> 1 ) - ( eax | edx & 1 )
	; 
	; We also need to store x2 for checking later on as to its odd or evenness
	;
	
	shr	ecx, 1
	mov	dword ptr _zbuffer_x2, edx
	
	or		eax, edx
	lea	edx, [ esi ]
	
	and	eax, 1
	sub	ecx, eax 					; ECX = length of double pixel loop ( GUARANTEED >= 1 )
	
	test	esi, 2						; Compare alignment of the first pixel
	je	start_zbuffer_rle_aligned
	
	;
	; first z pixel is unaligned.
	;
	
	mov	eax, ebx
	
	shr	eax, 16
	
	cmp	ax, [ esi ]
	jle	prestart_zless
	
prestart_zgreater:

		mov	[ esi ], ax
		add	ebx, dword ptr _idq
		
		neg	edx
		lea	esi, [ esi + 2 ]
		
		mov	_pixels_to_plot, esi
		jmp	draw_pixels_rle_inner_loop
		
		
prestart_zless:

		add	ebx, dword ptr _idq
		neg	edx
		
		lea	esi, [ esi + 2 ]
		jmp	skip_pixels_rle_inner_loop


start_zbuffer_rle_aligned:

	mov	eax, ebx
	shr	eax, 16
	
	cmp	ax, word ptr [ esi ]
	jle	start_otherz

		mov	eax, ebx
		add	ebx, ebp
		
		shr	eax, 16
		neg	edx
		
		mov	word ptr [ esi ], ax
		mov	_pixels_to_plot, esi
		
		mov	word ptr [ esi + 2 ], ax
		lea	esi, [ esi + 4 ]
		
		dec	ecx
		je		end_zgreater_rle_JUMP
		
		jmp	draw_pixels_rle_inner_loop
		
		
draw_pixels_rle_loop_init:

		mov	eax, ebx
		
		shr	eax, 16
		
		mov	word ptr [ esi - 4 ], ax
		neg	edx
		
		mov	word ptr [ esi - 2 ], ax
		
		mov	_pixels_to_plot, esi
		dec	ecx
		je		end_zgreater_rle_JUMP
		
draw_pixels_rle_inner_loop:

			mov	eax, ebx
			shr	eax, 16
			
			cmp	ax, [ esi ]
			lea	esi, [ esi + 4 ]
			
			mov	eax, ebx
			jle	change_zgreater_state
			
				shr	eax, 16
				lea	ebx, [ ebx + ebp ]
				
				mov	word ptr [ esi - 2 ], ax
				dec	ecx
				
				mov	word ptr [ esi - 4 ], ax
				jg		draw_pixels_rle_inner_loop
				
end_zgreater_rle_JUMP:
				jmp	end_zgreater_rle
				
change_zgreater_state:

				lea	edx, [ edx + esi - 4 ]
				add	ebx, ebp
				
				sar	edx, 1
				
				mov	word ptr [ edi ], dx
				lea	edi, [ edi + 2 ]
				
				lea	edx, [ esi - 4 ]
				neg	edx
				
				dec	ecx
				je		end_zless_rle
				
				jmp	skip_pixels_rle_inner_loop
				
start_otherz:

		add	ebx, ebp
		
		lea	esi, [ esi + 4 ]
		neg	edx
		
		dec	ecx
		je		end_zless_rle
		
skip_pixels_rle_inner_loop:

			mov	eax, ebx
			shr	eax, 16
			
			cmp	ax, [ esi ]
			lea	esi, [ esi + 4 ]
			
			lea	ebx, [ ebx + ebp ]
			jg	change_zless_state
			
				dec	ecx
				jg	skip_pixels_rle_inner_loop
				
end_zless_rle_JUMP:
				jmp	end_zless_rle
				
change_zless_state:

				mov	eax, ebx
				sub	eax, _idq
				shr	eax, 16
				cmp	eax, [ esi - 6 ]
				jle	change_zless_zless_state


				lea	edx, [ esi + edx - 6 ]
				
				neg	edx
				sar	edx, 1
				
				mov	word ptr [ edi ], dx
				lea	edi, [ edi + 2 ]
				
				lea	edx, [ esi - 4 ]
		
				jmp	draw_pixels_rle_loop_init
				
change_zless_zless_state:
				
				lea	edx, [ esi + edx - 4 ]
				
				neg	edx
				sar	edx, 1
				
				mov	word ptr [ edi ], dx
				lea	edi, [ edi + 2 ]
				
				lea	edx, [ esi - 4 ]
		
				jmp	draw_pixels_rle_loop_init
				
end_zless_rle:

	test	dword ptr _zbuffer_x2, 1
	je		end_zless_rle_wordend

end_zless_rle_dwordend:

		mov	eax, ebx
		add	eax, _idq
		
		shr	eax, 16
		cmp	ax, [ esi + 2 ]
		jg	end_zless_rle_dword_zgreater
		
			; We have ended on a skip pixels run - so just put a END RUN code in the instruction buffer
			mov	word ptr [ edi ], 0
			pop	ebp
			ret
			
end_zless_rle_dword_zgreater:

			mov	_pixels_to_plot, 1
			mov	[ esi ], ax
			lea	edx, [ esi + edx ]
			mov	[ esi + 2 ], ax
			neg	edx
			sar	edx, 1
			mov	word ptr [ edi ], dx
			mov	word ptr [ edi + 2 ], 2
			mov	word ptr [ edi + 4 ], 0
			
			pop	ebp
			ret
			
end_zless_rle_wordend:

		mov	eax, ebx
		shr	eax, 16
		
		cmp	ax, [ esi ]
		jg	end_zless_rle_wordend_zgreater
		
			; We have ended on a skip pixels run - so just put a END RUN code in the instruction buffer
			mov	word ptr [ edi ], 0
			pop	ebp
			ret
			
end_zless_rle_wordend_zgreater:
			mov	_pixels_to_plot, esi
			mov	eax, ebx
			lea	edx, [ esi + edx ]
			shr	eax, 16
			neg	edx
			mov	word ptr [ esi ], ax
			sar	edx, 1
			mov	word ptr [ edi ], dx
			mov	word ptr [ edi + 2 ], 1
			mov	word ptr [ edi + 4 ], 0
			
			pop	ebp
			ret
			
			
end_zgreater_rle:
	test	dword ptr _zbuffer_x2, 1
	je		end_zgreater_rle_wordend
	
end_zgreater_rle_dwordend:
		mov	eax, ebx
		add	eax, _idq
		shr	eax, 16
		cmp	ax, [ esi + 2 ]
		jle	end_zgreater_rle_dwordend_zless
		
			mov	_pixels_to_plot, esi
			mov	[ esi ], ax
			lea	edx, [ esi + edx + 4 ]
			
			mov	[ esi + 2 ], ax
			sar	edx, 1
			mov	word ptr [ edi ], dx
			mov	word ptr [ edi + 2 ], 0
			pop	ebp
			ret
			
end_zgreater_rle_dwordend_zless:

		; Have to check the previous pixel in this case, otherwise our fill convention is fucked
		
			mov	eax, ebx
			shr	eax, 16
			cmp	ax, [ esi ]
			jle	end_zgreater_rle_dwordend_zless_zless
			
			mov	_pixels_to_plot, esi
			mov	[ esi ], ax
			lea	edx, [ esi + edx + 2 ]
			sar	edx, 1
			mov	word ptr [ edi ], dx
			mov	word ptr [ edi + 2 ], 0
			pop	ebp
			ret

end_zgreater_rle_dwordend_zless_zless:

			lea	edx, [ esi + edx ]
			sar	edx, 1
			mov	word ptr [ edi ], dx
			mov	word ptr [ edi + 2 ], 0
			pop	ebp
			ret


			
end_zgreater_rle_wordend:			
		mov	eax, ebx
		shr	eax, 16
		cmp	ax, [ esi ]
		jle	end_zgreater_rle_wordend_zless
		
			mov	_pixels_to_plot, esi
			mov	[ esi ], ax
			lea	edx, [ esi + edx + 2 ]
			sar	edx, 1
			mov	word ptr [ edi ], dx
			mov	word ptr [ edi + 2 ], 0
			pop	ebp
			ret
			
end_zgreater_rle_wordend_zless:

			lea	edx, [ esi + edx ]
			sar	edx, 1
			mov	word ptr [ edi ], dx
			mov	word ptr [ edi + 2 ], 0
			pop	ebp
			ret
			
			
		
_TEXT		ENDS
		END
