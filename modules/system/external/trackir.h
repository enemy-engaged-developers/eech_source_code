/* CRH 030320 */
/* quick hack to get compile working with OpenWatcom */

extern void __cdecl InitTrackIR ( void );
extern void __cdecl ExitTrackIR ( void );

extern int __cdecl query_TIR_active ( void );
extern void TIR_SetTimeout(unsigned int frames);

extern void TIR_Poll();
extern float TIR_GetYaw();
extern float TIR_GetPitch();
extern float TIR_GetRoll();
extern float TIR_GetX();
extern float TIR_GetY();
extern float TIR_GetZ();

extern void TIR_SetMaxXY(const unsigned int value);
extern float TIR_GetMaxXY();

extern int __cdecl GetYaw ( void );
extern int __cdecl GetPitch ( void );

