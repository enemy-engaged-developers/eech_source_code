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

extern LPD3DTLVERTEX get_d3d_execute_buffer_vertices_address ( vertex *polygon, int *return_number_of_vertices );

extern LPD3DTLVERTEX get_d3d_execute_buffer_vertices_points_address ( int number_of_vertices );

extern void d3d_check_execute_size ( int vsize, int isize );

extern void d3d_flush_execute_buffer ( void );

extern void d3d_adjust_execute_size ( int num_vertices, int instruction_size );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// All the execute buffer helper macros
//

#define MAKE_MATRIX(lpDev, handle, data) \
    if (lpDev->lpVtbl->CreateMatrix(lpDev, &handle) != D3D_OK) \
        return FALSE; \
    if (lpDev->lpVtbl->SetMatrix(lpDev, handle, &data) != D3D_OK) \
        return FALSE
#define RELEASE(x) if (x != NULL) {x->lpVtbl->Release(x); x = NULL;}

#define PUTD3DINSTRUCTION(op, sz, cnt, ptr) \
    ((LPD3DINSTRUCTION) ptr)->bOpcode = op; \
    ((LPD3DINSTRUCTION) ptr)->bSize = sz; \
    ((LPD3DINSTRUCTION) ptr)->wCount = cnt; \
    ptr = (void *)(((LPD3DINSTRUCTION) ptr) + 1)

#define VERTEX_DATA(loc, cnt, ptr) \
    if ((ptr) != (loc)) memcpy((ptr), (loc), sizeof(D3DVERTEX) * (cnt)); \
    ptr = (void *)(((LPD3DVERTEX) (ptr)) + (cnt))

// OP_MATRIX_MULTIPLY size: 4 (sizeof D3DINSTRUCTION)
#define OP_MATRIX_MULTIPLY(cnt, ptr) \
    PUTD3DINSTRUCTION(D3DOP_MATRIXMULTIPLY, sizeof(D3DMATRIXMULTIPLY), cnt, ptr)

// MATRIX_MULTIPLY_DATA size: 12 (sizeof MATRIXMULTIPLY)
#define MATRIX_MULTIPLY_DATA(src1, src2, dest, ptr) \
    ((LPD3DMATRIXMULTIPLY) ptr)->hSrcMatrix1 = src1; \
    ((LPD3DMATRIXMULTIPLY) ptr)->hSrcMatrix2 = src2; \
    ((LPD3DMATRIXMULTIPLY) ptr)->hDestMatrix = dest; \
    ptr = (void *)(((LPD3DMATRIXMULTIPLY) ptr) + 1)

// OP_STATE_LIGHT size: 4 (sizeof D3DINSTRUCTION)
#define OP_STATE_LIGHT(cnt, ptr) \
    PUTD3DINSTRUCTION(D3DOP_STATELIGHT, sizeof(D3DSTATE), cnt, ptr)

// OP_STATE_TRANSFORM size: 4 (sizeof D3DINSTRUCTION)
#define OP_STATE_TRANSFORM(cnt, ptr) \
    PUTD3DINSTRUCTION(D3DOP_STATETRANSFORM, sizeof(D3DSTATE), cnt, ptr)

// OP_STATE_RENDER size: 4 (sizeof D3DINSTRUCTION)
#define OP_STATE_RENDER(cnt, ptr) \
    PUTD3DINSTRUCTION(D3DOP_STATERENDER, sizeof(D3DSTATE), cnt, ptr)

// STATE_DATA size: 8 (sizeof D3DSTATE)
#define STATE_DATA(type, arg, ptr) \
    ((LPD3DSTATE) ptr)->drstRenderStateType = (D3DRENDERSTATETYPE)type; \
    ((LPD3DSTATE) ptr)->dwArg[0] = arg; \
    ptr = (void *)(((LPD3DSTATE) ptr) + 1)

// STATE_FLOAT_DATA size: 8 (sizeof D3DSTATE)
#define STATE_FLOAT_DATA(type, arg, ptr) \
    ((LPD3DSTATE) ptr)->drstRenderStateType = (D3DRENDERSTATETYPE)type; \
    ((LPD3DSTATE) ptr)->dvArg[0] = arg; \
    ptr = (void *)(((LPD3DSTATE) ptr) + 1)

// OP_PROCESS_VERTICES size: 4 (sizeof D3DINSTRUCTION)
#define OP_PROCESS_VERTICES(cnt, ptr) \
    PUTD3DINSTRUCTION(D3DOP_PROCESSVERTICES, sizeof(D3DPROCESSVERTICES), cnt, ptr)

// PROCESSVERTICES_DATA size: 16 (sizeof D3DPROCESSVERTICES)
#define PROCESSVERTICES_DATA(flgs, strt, cnt, ptr) \
    ((LPD3DPROCESSVERTICES) ptr)->dwFlags = flgs; \
    ((LPD3DPROCESSVERTICES) ptr)->wStart = strt; \
    ((LPD3DPROCESSVERTICES) ptr)->wDest = strt; \
    ((LPD3DPROCESSVERTICES) ptr)->dwCount = cnt; \
    ((LPD3DPROCESSVERTICES) ptr)->dwReserved = 0; \
    ptr = (void *)(((LPD3DPROCESSVERTICES) ptr) + 1)

// OP_TRIANGLE_LIST size: 4 (sizeof D3DINSTRUCTION)
#define OP_TRIANGLE_LIST(cnt, ptr) \
    PUTD3DINSTRUCTION(D3DOP_TRIANGLE, sizeof(D3DTRIANGLE), cnt, ptr)

#define TRIANGLE_LIST_DATA(loc, count, ptr) \
    if ((ptr) != (loc)) memcpy((ptr), (loc), sizeof(D3DTRIANGLE) * (count)); \
    ptr = (void *)(((LPD3DTRIANGLE) (ptr)) + (count))

// OP_LINE_LIST size: 4 (sizeof D3DINSTRUCTION)
#define OP_LINE_LIST(cnt, ptr) \
    PUTD3DINSTRUCTION(D3DOP_LINE, sizeof(D3DLINE), cnt, ptr)

#define LINE_LIST_DATA(loc, count, ptr) \
    if ((ptr) != (loc)) memcpy((ptr), (loc), sizeof(D3DLINE) * (count)); \
    ptr = (void *)(((LPD3DLINE) (ptr)) + (count))

// OP_POINT_LIST size: 8 (sizeof D3DINSTRUCTION + sizeof D3DPOINT)
#define OP_POINT_LIST(first, cnt, ptr) \
    PUTD3DINSTRUCTION(D3DOP_POINT, sizeof(D3DPOINT), 1, ptr); \
    ((LPD3DPOINT)(ptr))->wCount = cnt; \
    ((LPD3DPOINT)(ptr))->wFirst = first; \
    ptr = (void*)(((LPD3DPOINT)(ptr)) + 1)

// OP_SPAN_LIST size: 8 (sizeof D3DINSTRUCTION + sizeof D3DSPAN)
#define OP_SPAN_LIST(first, cnt, ptr) \
    PUTD3DINSTRUCTION(D3DOP_SPAN, sizeof(D3DSPAN), 1, ptr); \
    ((LPD3DSPAN)(ptr))->wCount = cnt; \
    ((LPD3DSPAN)(ptr))->wFirst = first; \
    ptr = (void*)(((LPD3DSPAN)(ptr)) + 1)

// OP_BRANCH_FORWARD size: 18 (sizeof D3DINSTRUCTION + sizeof D3DBRANCH)
#define OP_BRANCH_FORWARD(tmask, tvalue, tnegate, toffset, ptr) \
    PUTD3DINSTRUCTION(D3DOP_BRANCHFORWARD, sizeof(D3DBRANCH), 1, ptr); \
    ((LPD3DBRANCH) ptr)->dwMask = tmask; \
    ((LPD3DBRANCH) ptr)->dwValue = tvalue; \
    ((LPD3DBRANCH) ptr)->bNegate = tnegate; \
    ((LPD3DBRANCH) ptr)->dwOffset = toffset; \
    ptr = (void *)(((LPD3DBRANCH) (ptr)) + 1)

// OP_SET_STATUS size: 20 (sizeof D3DINSTRUCTION + sizeof D3DSTATUS)
#define OP_SET_STATUS(flags, status, _x1, _y1, _x2, _y2, ptr) \
    PUTD3DINSTRUCTION(D3DOP_SETSTATUS, sizeof(D3DSTATUS), 1, ptr); \
    ((LPD3DSTATUS)(ptr))->dwFlags = flags; \
    ((LPD3DSTATUS)(ptr))->dwStatus = status; \
    ((LPD3DSTATUS)(ptr))->drExtent.x1 = _x1; \
    ((LPD3DSTATUS)(ptr))->drExtent.y1 = _y1; \
    ((LPD3DSTATUS)(ptr))->drExtent.x2 = _x2; \
    ((LPD3DSTATUS)(ptr))->drExtent.y2 = _y2; \
    ptr = (void *)(((LPD3DSTATUS) (ptr)) + 1)

// OP_TEXTURELOAD size: 4 (sizeof D3DINSTRUCTION)
#define OP_TEXTURELOAD(cnt, ptr) \
    PUTD3DINSTRUCTION(D3DOP_TEXTURELOAD, sizeof(D3DTEXTURELOAD), cnt, ptr)

// TEXTURELOAD_DATA size: 8 (sizeof D3DTEXTURELOAD)
#define TEXTURELOAD_DATA(dest, src, ptr) \
    ((LPD3DTEXTURELOAD) ptr)->hDestTexture = dest; \
    ((LPD3DTEXTURELOAD) ptr)->hSrcTexture = src; \
    ptr = (void *)(((LPD3DTEXTURELOAD) ptr) + 1)

// OP_NOP size: 4
#define OP_NOP(ptr) \
    PUTD3DINSTRUCTION(D3DOP_TRIANGLE, sizeof(D3DTRIANGLE), 0, ptr)

#define OP_EXIT(ptr) \
    PUTD3DINSTRUCTION(D3DOP_EXIT, 0, 0, ptr)

#define QWORD_ALIGNED(ptr) \
    !(0x00000007L & (ULONG)(ptr))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
