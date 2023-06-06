/*  hello_tmd.c
    Based on hello_cube.c, by Schnappy, 12-2020
    2014 Meido-Tek Productions.
    Controls:
        Start                           - Toggle interactive/non-interactive mode.
        Select                          - Reset object's position and angles.
        L1/L2                           - Move object closer/farther.
        L2/R2                           - Rotate object (XY).
        Up/Down/Left/Right              - Rotate object (XZ/YZ).
        Triangle/Cross/Square/Circle    - Move object up/down/left/right.
*/
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libetc.h>
#include <stdio.h>
#define VMODE       0
#define SCREENXRES 320
#define SCREENYRES 240
#define CENTERX     SCREENXRES/2
#define CENTERY     SCREENYRES/2
#define OTLEN       2048        // Maximum number of OT entries
#define PRIMBUFFLEN 32768       // Maximum number of POLY_GT3 primitives
// Display and draw environments, double buffered
DISPENV disp[2];
DRAWENV draw[2];
u_long      ot[2][OTLEN];                   // Ordering table (contains addresses to primitives)
char        primbuff[2][PRIMBUFFLEN]; // Primitive list // That's our prim buffer
char * nextpri = primbuff[0];                       // Primitive counter
short           db  = 0;                        // Current buffer counter
// TMD files
// We're using GrumpyCoder's Nugget wrapper to compile the code with a modern GCC : https://github.com/grumpycoders/pcsx-redux/tree/main/src/mips/psyq
// To include binary files in the exe, add your TMD files to the SRCS variable in Makefile
// and in common.mk, add this rule to include *.tmf files :
//
//~ %.o: %.tmd
    //~ $(PREFIX)-objcopy -I binary --set-section-alignment .data=4 --rename-section .data=.rodata,alloc,load,readonly,data,contents -O elf32-tradlittlemips -B mips $< $@
// cube.tmd
extern unsigned char _binary_cube_tmd_start[]; // filename must begin with _binary_ followed by the full path, with . and / replaced, and then suffixed with _ and end with _start[]; or end[];
extern unsigned char _binary_cube_tmd_end[];   // Going up one directory level is 4 '_' : ____ as ./ is replaced by __ 
                                                            // https://discord.com/channels/642647820683444236/663664210525290507/780866265077383189
// Prototypes
void init(void);
void display(void);
//~ void LoadTexture(u_long * tim, TIM_IMAGE * tparam);
void init(){
    // Reset the GPU before doing anything and the controller
    PadInit(0);
    ResetGraph(0);
    // Initialize and setup the GTE
    InitGeom();
    SetGeomOffset(CENTERX, CENTERY);        // x, y offset
    SetGeomScreen(CENTERX);                 // Distance between eye and screen  
        // Set the display and draw environments
    SetDefDispEnv(&disp[0], 0, 0         , SCREENXRES, SCREENYRES);
    SetDefDispEnv(&disp[1], 0, SCREENYRES, SCREENXRES, SCREENYRES);
    SetDefDrawEnv(&draw[0], 0, SCREENYRES, SCREENXRES, SCREENYRES);
    SetDefDrawEnv(&draw[1], 0, 0, SCREENXRES, SCREENYRES);
    if (VMODE)
    {
        SetVideoMode(MODE_PAL);
        disp[0].screen.y += 8;
        disp[1].screen.y += 8;
    }
    SetDispMask(1);                 // Display on screen        
    setRGB0(&draw[0], 0, 128, 255);
    setRGB0(&draw[1], 0, 128, 255);
    draw[0].isbg = 1;
    draw[1].isbg = 1;
    PutDispEnv(&disp[db]);
    PutDrawEnv(&draw[db]);
    // Init font system
    FntLoad(960, 0);
    FntOpen(16, 16, 196, 64, 0, 256);
    }
void display(void){
    DrawSync(0);
    VSync(0);
    PutDispEnv(&disp[db]);
    PutDrawEnv(&draw[db]);
    DrawOTag(&ot[db][OTLEN - 1]);
    db = !db;
    nextpri = primbuff[db];
    }
int main() {
    int     i;
    int     PadStatus;
    int     TPressed=0;
    int     AutoRotate=1;
    long    t, p, OTz, Flag;                // t == vertex count, p == depth cueing interpolation value, OTz ==  value to create Z-ordered OT, Flag == see LibOver47.pdf, p.143
    POLY_G3 *poly = {0};                           // pointer to a POLY_G4 
    SVECTOR Rotate={ 232, 232, 0, 0 };                   // Rotation coordinates
    VECTOR  Trans={ 0, 0, CENTERX * 3, 0 };     // Translation coordinates
                                            // Scaling coordinates
    VECTOR  Scale={ ONE/2, ONE/2, ONE/2, 0 };     // ONE == 4096
    MATRIX  Matrix={0};                     // Matrix data for the GTE
    init();
    // Main loop
    while (1) {
        // Read pad status
        PadStatus = PadRead(0);
        if (AutoRotate == 0) {
            if (PadStatus & PADL1) Trans.vz -= 4;
            if (PadStatus & PADR1) Trans.vz += 4;
            if (PadStatus & PADL2) Rotate.vz -= 8;
            if (PadStatus & PADR2) Rotate.vz += 8;
            if (PadStatus & PADLup)     Rotate.vx -= 8;
            if (PadStatus & PADLdown)   Rotate.vx += 8;
            if (PadStatus & PADLleft)   Rotate.vy -= 8;
            if (PadStatus & PADLright)  Rotate.vy += 8;
            if (PadStatus & PADRup)     Trans.vy -= 2;
            if (PadStatus & PADRdown)   Trans.vy += 2;
            if (PadStatus & PADRleft)   Trans.vx -= 2;
            if (PadStatus & PADRright)  Trans.vx += 2;
            if (PadStatus & PADselect) {
                Rotate.vx = Rotate.vy = Rotate.vz = 0;
                Scale.vx = Scale.vy = Scale.vz = ONE/2;
                Trans.vx = Trans.vy = 0;
                Trans.vz = CENTERX * 3;
            }
        }
        if (PadStatus & PADstart) {
            if (TPressed == 0) {
                AutoRotate = (AutoRotate + 1) & 1;
                Rotate.vx = Rotate.vy = Rotate.vz = 0;
                Scale.vx = Scale.vy = Scale.vz = ONE/2;
                Trans.vx = Trans.vy = 0;
                Trans.vz = CENTERX * 3;
            }
            TPressed = 1;
        } else {
            TPressed = 0;
        }
        if (AutoRotate) {
            Rotate.vy += 28; // Pan
            Rotate.vx += 28; // Tilt
            //~ Rotate.vz += 8; // Roll
        }
        // Clear the current OT
        ClearOTagR(ot[db], OTLEN);
        // Convert and set the matrixes
        RotMatrix(&Rotate, &Matrix);
        TransMatrix(&Matrix, &Trans);
        ScaleMatrix(&Matrix, &Scale);
        SetRotMatrix(&Matrix);
        SetTransMatrix(&Matrix);
        // Render the sample vector model
        t=0;
        TMD_PRIM tmdprim;
        // Prepare TMD
        int n_prim = OpenTMD((u_long*)_binary_cube_tmd_start, 0);
        for (i = 0; i < n_prim && ReadTMD(&tmdprim) != 0; i++) {
            poly = (POLY_G3 *)nextpri;
            // Initialize the primitive and set its color values
            SetPolyG3(poly);
            setRGB0(poly, tmdprim.r0, tmdprim.g0, tmdprim.b0);
            setRGB1(poly, tmdprim.r1, tmdprim.g1, tmdprim.b1);
            setRGB2(poly, tmdprim.r2, tmdprim.g2, tmdprim.b2);
            // Rotate, translate, and project the vectors and output the results into a primitive
            OTz  = RotTransPers(&tmdprim.x0, (long*)&poly->x0, &p, &Flag);
            OTz += RotTransPers(&tmdprim.x1, (long*)&poly->x1, &p, &Flag);
            OTz += RotTransPers(&tmdprim.x2, (long*)&poly->x2, &p, &Flag);
            // Sort the primitive into the OT
            OTz /= 3;
            if ((OTz > 0) && (OTz < OTLEN))
                AddPrim(&ot[db][OTz-2], poly);
            nextpri += sizeof(POLY_G3);
            t+=3;
        }
        FntPrint("Hello gouraud shaded cube!\n");
        FntFlush(-1);
        display();
    }
    return 0;
}
