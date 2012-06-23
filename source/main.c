#include <PA9.h>       // Include for PA_Lib
#include "fr3ndlib.h"

/*************************************
*** INCLUDES
*************************************/

// Sons
#include "classic_sound1.h"
#include "classic_sound2.h"
#include "classic_sound3.h"
#include "classic_sound4.h"
#include "Razz.h"
#include "Popup.h"

// Backgrounds
#include "gfx/splash1.pal.c"
#include "gfx/splash1.raw.c"
#include "gfx/splash1.map.c"

#include "gfx/splash2.pal.c"
#include "gfx/splash2.raw.c"
#include "gfx/splash2.map.c"

#include "gfx/menu.pal.c"
#include "gfx/menu.raw.c"
#include "gfx/menu.map.c"

#include "gfx/options.pal.c"
#include "gfx/options.raw.c"

#include "gfx/credits.map.c"
#include "gfx/credits.raw.c"
#include "gfx/thanks.map.c"
#include "gfx/thanks.raw.c"

#include "gfx/help1.map.c"
#include "gfx/help1.raw.c"
#include "gfx/help2.map.c"
#include "gfx/help2.raw.c"

#include "gfx/scores1.map.c"
#include "gfx/scores1.raw.c"
#include "gfx/scores2.map.c"
#include "gfx/scores2.raw.c"

#include "gfx/newscore.map.c"
#include "gfx/newscore.raw.c"

#include "gfx/simon_2.pal.c"
#include "gfx/simon2_anim_000.map.c"
#include "gfx/simon2_anim_000.raw.c"
#include "gfx/simon2_anim_001.map.c"
#include "gfx/simon2_anim_001.raw.c"
#include "gfx/simon2_anim_002.map.c"
#include "gfx/simon2_anim_002.raw.c"
#include "gfx/simon2_anim_003.map.c"
#include "gfx/simon2_anim_003.raw.c"
#include "gfx/simon2_anim_004.map.c"
#include "gfx/simon2_anim_004.raw.c"

#include "gfx/simon3.pal.c"
#include "gfx/simon3.raw.c"
#include "gfx/simon3.map.c"

#include "gfx/simon_zoom.pal.c"
#include "gfx/simon_zoom_000.raw.c"
#include "gfx/simon_zoom_000.map.c"
#include "gfx/simon_zoom_001.raw.c"
#include "gfx/simon_zoom_001.map.c"
#include "gfx/simon_zoom_002.raw.c"
#include "gfx/simon_zoom_002.map.c"
#include "gfx/simon_zoom_003.raw.c"
#include "gfx/simon_zoom_003.map.c"
#include "gfx/simon_zoom_004.raw.c"
#include "gfx/simon_zoom_004.map.c"
#include "gfx/simon_zoom_005.raw.c"
#include "gfx/simon_zoom_005.map.c"
#include "gfx/simon_zoom_006.raw.c"
#include "gfx/simon_zoom_006.map.c"
#include "gfx/simon_zoom_007.raw.c"
#include "gfx/simon_zoom_007.map.c"
#include "gfx/simon_zoom_008.raw.c"
#include "gfx/simon_zoom_008.map.c"
#include "gfx/simon_zoom_009.raw.c"
#include "gfx/simon_zoom_009.map.c"

#include "gfx/leds.pal.c"
#include "gfx/leds.raw.c"

#include "gfx/textgran.pal.c"
#include "gfx/textgran.raw.c"

#include "popcorn3.h"

/*************************************
*** DEFINES
*************************************/

#define swap(a,b,t) ((t)=(a),(a)=(b),(b)=(t))
#define BGZOOM	0
#define BGNORM	1

#define NOCOLOR 0
#define RED		1
#define	BLUE	2
#define	YELLOW	3
#define GREEN	4
// define per el so del menu
#define BLIP	5

// Definim els estats del joc
#define	S_LOAD_MENU		1
#define	S_USE_MENU		2
#define	S_LOADGAME		3
#define	S_FREEGAME		4
#define	S_GAME			5
#define S_STARTGAME		6
#define S_GAMEOVER		7
#define S_OPTIONS		8
#define S_LOADCREDITS	9
#define S_CREDITS		10
#define	S_LOADHELP		11
#define	S_HELP			12
#define S_LOADSCORE		13
#define S_SCORE			14
#define	S_LOADNEWSCORE	15
#define	S_NEWSCORE		16
#define S_SAVESCORE		17

// Opcions del menu
#define O_START		0
#define O_HELP		1
#define O_CREDITS	2
#define O_SCORE		3

// Temps disponible per repetir la seqüencia
#define TIMELEFT	5

/*************************************
*** TYPEDEFS
*************************************/

typedef struct {
	char name[11];
	int turn;
} record ;


/*************************************
*** PROTOTYPES
*************************************/

void query_buttons();    // Query for user input
void query_stylus();
void switchScreen(); // Intercambia les dues pantalles
void switchColor(short int color);
void switchColorErrorSound(short int color, bool error);
void playSound(int color);
bool inside(int touch[]);
void startGame();
void doCpuTurn();
void doPlayerTurn();
void finishGame();
void F_InitLeds(void);
void F_WriteNum(int num,int x,int y,int numSprite);
void F_WriteBigNum(int num,int x, int y, int sep,int numSprite);
void textGran(int numtext);
void loadRecords();
void sort(record *array, int length);
void saveRecords();


/*************************************
*** VARIABLES
*************************************/


// Definicions de les arees a on es pot apretar amb la stylus
// [X,Y,Ample,Alt]
// Pantalla de joc
int touchRed[4] = {134,7,82,82};
int touchBlue[4] = {134,101,82,82};
int touchYellow[4] = {39,101,82,82};
int touchGreen[4] = {39,8,82,82};
int touchPanel[4] = {102,97,50,50};
// Menu dins del joc
int touchReset[4] = {75,78,50,50};
int touchExit[4] = {130,78,50,50};
int touchReturn[4] = {103,130,50,50};
// Pantalla de opcions
int touchRedButton[4] = {119,109,16,16};

// Variables Globals
short int activeScreen;
short int activeColor;
unsigned int turn; // El torn actual. =0: encara no ha començat el joc; >=1: El joc ha començat
int sequence[128];
int playerTurn;
int state;
bool modPlaying;
int lastSoundChan = 0;
int vblanks; // comptador dels vblanks per calcular el temps que queda
bool savingEnabled = true; // Per saber si hem de guardar els records o no

#define MAXRECORDS	9
record records[MAXRECORDS], recordActual;


/*************************************
*** MAIN
*************************************/

// Function: main()
int main(int argc, char ** argv) {
	int x, y = 0;
	int scroll = 0;
	char letter;
	s32 nletter = 0;

	
	PA_Init();    // Initializes PA_Lib
	PA_InitVBL(); // Initializes a standard VBL
	PA_InitSound(); // Inicialitzem el so
	PA_InitRand(); // Inicialitzem el random
	
	loadRecords();
	// Carreguem la splash screen
	PA_LoadPal(PAL_BG1, splash1_Palette); // Backgrounds
	PA_LoadPal(PAL_BG0, splash2_Palette); // Backgrounds
	PA_PlayMod(popcorn3);
	modPlaying = true;
	PA_Splash((void*)splash2_Tiles,(void*)splash2_Map,(void*)splash1_Tiles,(void*)splash1_Map,0,1,300);
	
	

	
	// Inicialitzem algunes variables
	activeColor = NOCOLOR;
	scroll=0;
	state = S_LOAD_MENU;
	// Infinite loop to keep the program running
	while (1)
	{		
		query_buttons();
		query_stylus();
		switch (state) {
			// Carrega el menu
			case S_LOAD_MENU:
				if (modPlaying == false) {
					PA_PlayMod(popcorn3);
					modPlaying = true;
				}
				PA_ResetSpriteSys();
				PA_ResetBgSys();
				PA_ResetBg(1);
				PA_ResetBg(0);
				PA_LoadPal(PAL_BG0, menu_Palette);
				PA_LoadPal(PAL_BG1, menu_Palette);
				PA_LoadSimpleBg(0,3,menu_Tiles,menu_Map,BG_256X256,1,1);
				PA_LoadSimpleBg(1,3,menu_Tiles,menu_Map,BG_256X256,1,1);
				PA_LoadPal(PAL_SPRITE0, options_Palette);
				PA_LoadPal(PAL_SPRITE1, options_Palette);
					
				// Sprites menu
				for (x=0; x<4; x++) {
					PA_CreateSprite(0,x,(void*)&options_Bitmap[4096*x],OBJ_SIZE_64X64,1,0,96,43*x);
				}
				
				// Sprites taulell
				for (x=0; x<3; x++) 
					PA_CreateSprite(1,8+x,(void*)&options_Bitmap[4096*(6+x)],OBJ_SIZE_64X64,1,0,32+64*x,0);
				for (x=0; x<3; x++) 
					PA_CreateSprite(1,12+x,(void*)&options_Bitmap[4096*(9+x)],OBJ_SIZE_64X64,1,0,32+64*x,64);
				for (x=0; x<3; x++) 
					PA_CreateSprite(1,16+x,(void*)&options_Bitmap[4096*(12+x)],OBJ_SIZE_64X64,1,0,32+64*x,64*2);
					
				// Sprite versió
				PA_CreateSprite(0,20,(void*)&options_Bitmap[4096*4],OBJ_SIZE_64X64,1,0,64*3,64*2);
				
				
				y=0;
				state = S_USE_MENU;
				break;
			// Espera acció per el menu
			case S_USE_MENU:
				PA_BGScrollY(0,3,scroll);
				PA_BGScrollY(1,3,scroll);
				
				if (scroll < 512)
					 scroll++;
				else
					scroll=0;
				// Mirem si hem tocat algun sprite
				if (Stylus.Newpress){ 
					for (x=0; x<4; x++) {
						if (PA_SpriteTouched(x) || Pad.Released.Select) {
							playSound(BLIP);
							switch (x) {
								case O_START:
									// Start Game
									PA_StopMod();
									modPlaying = false;
									PA_ResetSpriteSys();
									state = S_LOADGAME;
									break;
								case O_CREDITS:
									PA_ResetSpriteSys();
									state = S_LOADCREDITS;
									break;
								case O_HELP:
									PA_ResetSpriteSys();
									state = S_LOADHELP;
									break;
								case O_SCORE:
									PA_ResetSpriteSys();
									state = S_LOADSCORE;
									//state = S_LOADNEWSCORE;
									break;
								default:
									state = S_LOAD_MENU;
									break;
							}
						}
					} 
				}
			break;
			// Carrega els fondos inicials del joc i passa el control al sistema de torns
			case S_LOADGAME:
				// Carreguem els fondos
				PA_ResetBg(1);
				PA_ResetBg(0);
				PA_LoadPal(PAL_BG0, simon_2_Palette); // Fondo tablero
				PA_LoadPal(PAL_BG1, simon3_Palette); // Fondo puntuació
				   
				PA_LoadSimpleBg(1,2,simon3_Tiles,simon3_Map,BG_256X256,1,1); // Tablero
				PA_LoadSimpleBg(0,3,simon2_anim_000_Tiles,simon2_anim_000_Map,BG_256X256,1,1);
				
				F_InitLeds();
				F_WriteNum(10,63,92,2);
				F_WriteBigNum(turn,79,91,19,0);
				F_WriteNum(TIMELEFT,79,127,4);
				F_WriteNum(0,98,127,5);
				
				textGran(1); // Are You Ready?
				Fsleep(40);
				textGran(0);
				
				F_InitLeds();
				F_WriteNum(10,63,92,2);
				F_WriteBigNum(turn,79,91,19,0);
				F_WriteNum(TIMELEFT,79,127,4);
				F_WriteNum(0,98,127,5);
				
				textGran(2); // Start!
				Fsleep(40);
				textGran(0);
				
				F_InitLeds();
				F_WriteNum(10,63,92,2);
				F_WriteBigNum(turn,79,91,19,0);
				F_WriteNum(TIMELEFT,79,127,4);
				F_WriteNum(0,98,127,5);
				
				Fsleep(20);
				state = S_STARTGAME;
				break;
			// Deixa tocar el joc al jugador fins que el joc comenci (apretar start o amb stylus
			case S_FREEGAME:
				doPlayerTurn();				
				break;
			// El joc ja ha començat. La maquina ha fet la seva jugada i el jugador ha de repetir la seqüencia
			case S_GAME:
				doPlayerTurn();		
				break;
			case S_STARTGAME:
				startGame();
				break;
			case S_GAMEOVER:
				if (Stylus.Newpress) {
					state = S_LOAD_MENU;
				}
				break;
			case S_OPTIONS:
				// no fem res
				break;
			case S_LOADCREDITS:
				// Credits del joc
				PA_LoadSimpleBg(1,1,credits_Tiles,credits_Map,BG_256X256,1,1);
				PA_LoadSimpleBg(0,1,thanks_Tiles,thanks_Map,BG_256X256,1,1);
				state = S_CREDITS;
				break;
			case S_CREDITS:
				PA_BGScrollY(0,3,scroll);
				PA_BGScrollY(1,3,scroll);
				if (scroll < 512)
					 scroll++;
				else
					scroll=0;
				if (Stylus.Newpress) {
					playSound(BLIP);
					state = S_LOAD_MENU;
				}
				break;
			case S_LOADHELP:
				PA_LoadSimpleBg(1,1,help1_Tiles,help1_Map,BG_256X256,1,1);
				PA_LoadSimpleBg(0,1,help2_Tiles,help2_Map,BG_256X256,1,1);
				state = S_HELP;
				break;
			case S_HELP:
				PA_BGScrollY(0,3,scroll);
				PA_BGScrollY(1,3,scroll);
				if (scroll < 512)
					 scroll++;
				else
					scroll=0;
				if (Stylus.Newpress) {
					playSound(BLIP);
					state = S_LOAD_MENU;
				}
				break;
			case S_LOADSCORE:
				PA_InitText(1,0); // Inicialitzem el text
				PA_InitText(0,0); // Inicialitzem el text
				
				PA_LoadSimpleBg(1,1,scores1_Tiles,scores1_Map,BG_256X256,1,1);
				PA_LoadSimpleBg(0,1,scores2_Tiles,scores2_Map,BG_256X256,1,1);
				PA_SetTextFont (1, 0);
				PA_SetTextFont (0, 0);
				PA_SetTextCol(0,31,31,31);
				PA_SetTextCol(1,31,31,31);
				
				for (x=0; x<MAXRECORDS; x++) {
					PA_OutputText(0,4,4+x*2,"%d",x+1);
					PA_OutputText(0,2+4,4+x*2,"  %s",records[MAXRECORDS-x-1].name);
					PA_OutputText(0,2+4+14,4+x*2,"  %d",records[MAXRECORDS-x-1].turn);
				}
				
				state = S_SCORE;
				break;
			case S_SCORE:
				PA_BGScrollY(0,3,scroll);
				PA_BGScrollY(1,3,scroll);
				if (scroll < 512)
					 scroll++;
				else
					scroll=0;
				if (Stylus.Newpress) {
					playSound(BLIP);
					state = S_LOAD_MENU;
				}
				break;
			case S_LOADNEWSCORE:
				PA_ResetSpriteSys();
				PA_ResetBg(1);
				PA_ResetBg(0);
				PA_LoadPal(PAL_BG0, menu_Palette);
				PA_LoadPal(PAL_BG1, menu_Palette);
				PA_LoadSimpleBg(0,3,menu_Tiles,menu_Map,BG_256X256,1,1);
				PA_LoadSimpleBg(1,3,menu_Tiles,menu_Map,BG_256X256,1,1);
				PA_LoadSimpleBg(0,2,newscore_Tiles,newscore_Map,BG_256X256,1,1);
				
				PA_InitText(0,0); // Inicialitzem el text
				PA_SetTextFont (0, 0);
				PA_SetTextCol(0,0,0,0);
				PA_WaitForVBL();
				textGran(4);
				PA_InitKeyboard(1);
				PA_KeyboardIn (25, 90);
				strcpy (recordActual.name,"         ");
				nletter = 0;
				recordActual.turn = turn;
				state = S_NEWSCORE;
				break;
			case S_NEWSCORE:				
				letter = PA_CheckKeyboard ();
				
				if ((letter > 31) && (nletter<10)) { // there is a new letter
					playSound(BLIP);
					recordActual.name[nletter] = letter;
					nletter++;
				} else if ((letter == PA_BACKSPACE) && (nletter>0)) { // Backspace pressed
					playSound(BLIP);
					nletter--;
					recordActual.name[nletter] = ' '; // Erase the last letter
				} else if (letter == '\n'){ // Enter pressed
					playSound(BLIP);
					textGran(0);
					state = S_SAVESCORE;
					PA_KeyboardOut();
					PA_DeleteBg(0,2);
				}
				PA_OutputText(0,9,6,"  %s",recordActual.name);
				
				if (scroll < 512)
					 scroll++;
				else
					scroll=0;
					
				PA_BGScrollY(0,3,scroll);
				PA_BGScrollY(1,3,scroll);
				break;
			case S_SAVESCORE:
				records[0] = recordActual;
				sort (records,MAXRECORDS);
				saveRecords();
				state = S_LOADSCORE;
				break;
		}
		PA_CheckLid();
		PA_WaitForVBL();
	}
	return 0;
} // End of main()



/*************************************
*** FUNCTIONS
*************************************/

// Funcions d'agafar opcions per teclat
void query_buttons() {
	if ((state == S_FREEGAME) || (state == S_GAME) || (state == S_OPTIONS)) {
		if (Pad.Released.Select) {
			switchScreen();
		}
	}
}

// Funcions d'agafar les opcions amb stylus
void query_stylus() {
	if (state == S_GAME) {
		if (Stylus.Newpress) {
			if (inside(touchPanel)) {
				playSound(BLIP);
				switchScreen();
			}
		}
	} else if (state == S_OPTIONS) {
		if (Stylus.Newpress) {
			if (inside (touchReturn)) {
				playSound(BLIP);
				switchScreen();
			} else if (inside (touchExit)) {
				playSound(BLIP);
				state = S_LOAD_MENU;
			} else if (inside (touchReset)) {
				playSound(BLIP);
				state = S_LOADGAME;
			}
		}
	}
}

void switchScreen() {
	//PA_SwitchScreens();
	if (state == S_GAME) {
		PA_LoadPal(PAL_BG0, simon_zoom_Palette);
		PA_LoadSimpleBg(0,2,simon_zoom_009_Tiles,simon_zoom_009_Map,BG_256X256,1,1);
		PA_WaitForVBL();
		PA_LoadSimpleBg(0,2,simon_zoom_008_Tiles,simon_zoom_008_Map,BG_256X256,1,1);
		PA_WaitForVBL();
		PA_LoadSimpleBg(0,2,simon_zoom_007_Tiles,simon_zoom_007_Map,BG_256X256,1,1);
		PA_WaitForVBL();
		PA_LoadSimpleBg(0,2,simon_zoom_006_Tiles,simon_zoom_006_Map,BG_256X256,1,1);
		PA_WaitForVBL();
		PA_LoadSimpleBg(0,2,simon_zoom_005_Tiles,simon_zoom_005_Map,BG_256X256,1,1);
		PA_WaitForVBL();
		PA_LoadSimpleBg(0,2,simon_zoom_004_Tiles,simon_zoom_004_Map,BG_256X256,1,1);
		PA_WaitForVBL();
		PA_LoadSimpleBg(0,2,simon_zoom_003_Tiles,simon_zoom_003_Map,BG_256X256,1,1);
		PA_WaitForVBL();
		PA_LoadSimpleBg(0,2,simon_zoom_002_Tiles,simon_zoom_002_Map,BG_256X256,1,1);
		PA_WaitForVBL();
		PA_LoadSimpleBg(0,2,simon_zoom_001_Tiles,simon_zoom_001_Map,BG_256X256,1,1);
		PA_WaitForVBL();
		PA_LoadSimpleBg(0,2,simon_zoom_000_Tiles,simon_zoom_000_Map,BG_256X256,1,1);
		PA_WaitForVBL();
		
		state = S_OPTIONS;
	} else if (state == S_OPTIONS) {
		PA_LoadPal(PAL_BG0, simon_zoom_Palette);
		PA_LoadSimpleBg(0,2,simon_zoom_000_Tiles,simon_zoom_000_Map,BG_256X256,1,1);
		PA_WaitForVBL();
		PA_LoadSimpleBg(0,2,simon_zoom_001_Tiles,simon_zoom_001_Map,BG_256X256,1,1);
		PA_WaitForVBL();
		PA_LoadSimpleBg(0,2,simon_zoom_002_Tiles,simon_zoom_002_Map,BG_256X256,1,1);
		PA_WaitForVBL();
		PA_LoadSimpleBg(0,2,simon_zoom_003_Tiles,simon_zoom_003_Map,BG_256X256,1,1);
		PA_WaitForVBL();
		PA_LoadSimpleBg(0,2,simon_zoom_004_Tiles,simon_zoom_004_Map,BG_256X256,1,1);
		PA_WaitForVBL();
		PA_LoadSimpleBg(0,2,simon_zoom_005_Tiles,simon_zoom_005_Map,BG_256X256,1,1);
		PA_WaitForVBL();
		PA_LoadSimpleBg(0,2,simon_zoom_006_Tiles,simon_zoom_006_Map,BG_256X256,1,1);
		PA_WaitForVBL();
		PA_LoadSimpleBg(0,2,simon_zoom_007_Tiles,simon_zoom_007_Map,BG_256X256,1,1);
		PA_WaitForVBL();
		PA_LoadSimpleBg(0,2,simon_zoom_008_Tiles,simon_zoom_008_Map,BG_256X256,1,1);
		PA_WaitForVBL();
		PA_LoadSimpleBg(0,2,simon_zoom_009_Tiles,simon_zoom_009_Map,BG_256X256,1,1);
		PA_WaitForVBL();
		
		PA_LoadPal(PAL_BG0, simon_2_Palette); // Fondo tablero
		PA_LoadSimpleBg(0,2,simon2_anim_000_Tiles,simon2_anim_000_Map,BG_256X256,1,1);
		state = S_GAME;
	}
}

void switchColor(short int color) {
	switchColorErrorSound(color,false);
}

void switchColorErrorSound(short int color, bool error) {
	activeColor = color;
	switch (color) {
		case NOCOLOR:
			PA_DeleteBg(0,2);
			break;
		case RED:
			PA_LoadSimpleBg(0,2,simon2_anim_001_Tiles,simon2_anim_001_Map,BG_256X256,1,1);
			if (!error)
				playSound(RED);
			break;
		case BLUE:
			PA_LoadSimpleBg(0,2,simon2_anim_002_Tiles,simon2_anim_002_Map,BG_256X256,1,1);
			if (!error)
				playSound(BLUE);
			break;
		case YELLOW:
			PA_LoadSimpleBg(0,2,simon2_anim_003_Tiles,simon2_anim_003_Map,BG_256X256,1,1);
			if (!error)
				playSound(YELLOW);
			break;
		case GREEN:
			PA_LoadSimpleBg(0,2,simon2_anim_004_Tiles,simon2_anim_004_Map,BG_256X256,1,1);
			if (!error)
				playSound(GREEN);
			break;
	}
	if (error) {
		playSound(NOCOLOR);
	}

}

void playSound(int color) {
	switch (color) {
		case NOCOLOR:
			PA_PlaySound(lastSoundChan, (void*)Razz, (u32)Razz_size,120,11025);
			break;
		case RED:
			PA_PlaySound(lastSoundChan, (void*)classic_sound1, (u32)classic_sound1_size,120,11025);
			break;
		case BLUE:
			PA_PlaySound(lastSoundChan, (void*)classic_sound2, (u32)classic_sound2_size,120,11025);
			break;
		case YELLOW:
			PA_PlaySound(lastSoundChan, (void*)classic_sound3, (u32)classic_sound3_size,120,11025);
			break;
		case GREEN:
			PA_PlaySound(lastSoundChan, (void*)classic_sound4, (u32)classic_sound4_size,120,11025);
			break;
		case BLIP:
			PA_PlaySound(lastSoundChan, Popup, (u32)Popup_size,120,11025);
			break;
	}
	
	if (lastSoundChan < 3)
		lastSoundChan++;
	else
		lastSoundChan = 0;
}
bool inside(int toucharea[]) {
	if ((Stylus.X > toucharea[0]) && 
		(Stylus.X < toucharea[0]+toucharea[2]) && 
		(Stylus.Y > toucharea[1]) &&
		(Stylus.Y < toucharea[1]+toucharea[3])) {
			return true;
		} else {
			return false;
		}
}

void startGame() {
	int x;
	
	state = S_GAME;
	turn = 1;
	for (x=0;x<128;x++) {
		sequence[x] = 0;
	}
	doCpuTurn();
}

// El torn de la maquina
void doCpuTurn() {
	int x;
	int sleeptime = 40; //Comencem amb un valor de 40 per sleeptime

	//F_InitLeds();
	F_WriteNum(10,63,92,2);
	F_WriteBigNum(turn,79,91,19,0);
	
	if (turn < 11) {
		sleeptime = 40 - turn*3;
	} else {
		sleeptime = 40 - 10*3;
	}
	
	sequence[turn-1] = PA_Rand() % 4 + 1;
	turn++;
	x= 1;
	while (x<turn) { 
		Fsleep(sleeptime);
		switchColor(sequence[x-1]);
		Fsleep(sleeptime);
		switchColor(NOCOLOR);
		x++;
	}
	// Posem playerTurn a 0 perque el jugador pugui repetir la seqüencia	
	playerTurn = 0;
	F_WriteNum(11,63,92,2);
	vblanks = 0;
	PA_WaitForVBL();
}

// El torn del jugador
void doPlayerTurn() {
	// Mira si estem fent be la seqüencia

	if (Stylus.Newpress) {
		if (inside(touchRed)) {
			if (turn > 0) {
				if (sequence[playerTurn] == RED) {
					switchColor(RED);
					playerTurn++;
				} else {
					switchColorErrorSound(RED,true);
					finishGame();
				}
			} else {
				switchColor(RED);
			}
		} else if (inside(touchBlue)) {
			if (turn > 0) {
				if (sequence[playerTurn] == BLUE) {
					switchColor(BLUE);
					playerTurn++;
				} else {
					switchColorErrorSound(BLUE,true);
					finishGame();
				} 
			} else {
				switchColor(BLUE);
			}
		} else if (inside(touchYellow)) {
			if (turn > 0) {
				if (sequence[playerTurn] == YELLOW) {
					switchColor(YELLOW);
					playerTurn++;
				} else {
					switchColorErrorSound(YELLOW,true);
					finishGame();
				}
			} else {
				switchColor(YELLOW);
			}
		} else if (inside(touchGreen)) {
			if (turn > 0) {
				if (sequence[playerTurn] == GREEN) {
					switchColor(GREEN);
					playerTurn++;
				} else {
					switchColorErrorSound(GREEN,true);
					finishGame();
				}
			} else {
				switchColor(GREEN);
			}
		}
	} else if (Stylus.Released) {
		switchColor(NOCOLOR);
		vblanks = 0;
		// Inicialitzem el comptador de temps
		F_WriteNum(TIMELEFT,79,127,4);
		F_WriteNum(0,98,127,5);
	} else if (Stylus.Held == 0) {
		// 1 segon ==  60 vblanks
		if (vblanks%6 == 0) {
			F_WriteNum(TIMELEFT -1 - (vblanks/60),79,127,4);
			F_WriteNum(9-(vblanks%60*10/60),98,127,5);
			if (TIMELEFT -1 - (vblanks/60) + 9-(vblanks%60*10/60) == 0) {
				playSound(NOCOLOR);
				finishGame();
			}
		}	
		vblanks++;
	}
	
	
	// Mirem si s'ha completat correctament tota la seqüencia i que s'ha deixat anar el stylus
	if (Stylus.Released) {
		PA_WaitForVBL();  // Fem que s'actualitzin els leds de temps
		if (playerTurn == turn-1)
			doCpuTurn();
	}
}

void finishGame() {
	if (turn > records[0].turn) {
		state = S_LOADNEWSCORE;
	} else {
		state = S_GAMEOVER;
		textGran(3);
	}
	//turn = 0;
}


// LEDS
void F_InitLeds(void) {
	PA_LoadPal(PAL_SPRITE1, leds_Palette);
	//numSprites = 0;
}
void F_WriteNum(int num,int x,int y, int numSprite) {
	PA_CreateSprite(1,numSprite,(void*)&leds_Bitmap[1024*num],OBJ_SIZE_32X32,1,0,x,y);
	//numSprites = numSprites+1;
}

void F_WriteBigNum(int num,int x, int y, int sep, int numSprite) {
	// TODO: Make with a for and allow numbers > 2 digits
	F_WriteNum(num%100/10,x,y,numSprite);
	F_WriteNum(num%10,x+sep,y,numSprite+1);
}

void textGran(int numtext) {
	int x,y = 0;
	
	PA_LoadPal(PAL_SPRITE0, textgran_Palette);
	switch (numtext) {
		case 1:
			// Are you ready?
			for (y=0;y<2;y++) {
				for (x=0;x<3;x++) {
					PA_CreateSprite(0,x+3*y,(void*)&textgran_Bitmap[4096*(x+3*y)],OBJ_SIZE_64X64,1,0,64*x,64*y);
					PA_SetSpriteDblsize(0,x+3*y,1);
					PA_SetSpriteRotEnable(0,x+3*y,0);
				}
			}
			for (x=512;x>=256;x=x-8) {
				PA_SetRotset (0,0,256-x,x,x);
				PA_WaitForVBL();
			}
			break;
		case 2:
			// Start!
			for (y=4;y<6;y++) {
				for (x=0;x<3;x++) {
					PA_CreateSprite(0,x+(3*(y-4)),(void*)&textgran_Bitmap[4096*(x+3*y)],OBJ_SIZE_64X64,1,0,64*x,64*y);
					PA_SetSpriteDblsize(0,x+3*(y-4),1);
					PA_SetSpriteRotEnable(0,x+3*(y-4),0);
				}
			}
			for (x=512;x>=256;x=x-8) {
				PA_SetRotset (0,0,256-x,x,x);
				PA_WaitForVBL();
			}
			break;
		case 3:
			// Game Over
			for (y=2;y<4;y++) {
				for (x=0;x<3;x++) {
					PA_CreateSprite(0,x+3*(y-2),(void*)&textgran_Bitmap[4096*(x+3*y)],OBJ_SIZE_64X64,1,0,64*x,64*(y-2));
					PA_SetSpriteDblsize(0,x+3*(y-2),1);
					PA_SetSpriteRotEnable(0,x+3*(y-2),0);
				}
			}
			for (x=512;x>=256;x=x-8) {
				PA_SetRotset (0,0,256-x,x,x);
				PA_WaitForVBL();
			}
			break;
		case 4:
			// New record
			PA_LoadPal(PAL_SPRITE1, textgran_Palette);
			for (y=6;y<8;y++) {
				for (x=0;x<3;x++) {
					PA_CreateSprite(1,x+3*(y-6),(void*)&textgran_Bitmap[4096*(x+3*y)],OBJ_SIZE_64X64,1,0,64*x,64*(y-2));
					PA_SetSpriteDblsize(1,x+3*(y-6),1);
					PA_SetSpriteRotEnable(1,x+3*(y-6),0);
				}
			}
			for (x=512;x>=256;x=x-8) {
				PA_SetRotset (0,0,256-x,x,x);
				PA_WaitForVBL();
			}
			break;
		case 0:
			// Elimina el text que hi ha actualment
			PA_ResetSpriteSys();
			break;
	}

}

void loadRecords() {
	#define SRAMHEADER	"DONSIMON"

	int x;
	char string[20];

	PA_LoadData(1,string,20);
	if (!PA_CompareText(string, SRAMHEADER)) {
		// Formategem la SRAM
		PA_InitText(0, 0); // Inicialitzem el text
		PA_SetTextCol(0, 31, 31, 31);
		PA_OutputSimpleText(0, 2, 2, "DonSimon not found in SRAM.");
		
		PA_OutputSimpleText(0, 2, 4, "It will be necessary to ");
		PA_OutputSimpleText(0, 2, 5, " format it to allow to save");
		PA_OutputSimpleText(0, 2, 6, " your records.");
		
		PA_OutputSimpleText(0, 2, 8, "It's safe to format SRAM if");
		PA_OutputSimpleText(0, 2, 9, " you don't have an original");
		PA_OutputSimpleText(0, 2, 10, " gba cartidge inserted");
		
		PA_OutputSimpleText(0, 2, 12, "http://fr3nd.net for + info");
		
		PA_OutputSimpleText(0, 2, 14, "Please select an option:");
		PA_OutputSimpleText(0, 2, 15, " A - Format SRAM");
		PA_OutputSimpleText(0, 2, 16, " B - Continue without saving");
		while ((!Pad.Newpress.A) && (!Pad.Newpress.B)) {
			PA_WaitForVBL();
		}
		if (Pad.Newpress.A) {
			PA_SaveData(1, (void*)Blank, 30000);
			PA_SaveString(1, SRAMHEADER);
			savingEnabled = true;
		} else {
			savingEnabled = false;
		}
		PA_ResetBgSys();
		// Generem els records inicials
		for (x=0; x<MAXRECORDS; x++) {
			strcpy(records[x].name,"fr3nd\0");
			records[x].turn = x+1;
		}
		
		// Guardem els records
		saveRecords();
	} else {
		// carregar les dade
		PA_LoadData(21,records,sizeof(records));
	}
}

void saveRecords() {
	if (savingEnabled == true) {
		PA_SaveData(21,records,sizeof(records));
	}
}

void sort(record *array, int length)
{
  int i, j;
  record temp;
  int test; /*use this only if unsure whether the list is already sorted or not*/
  for(i = length - 1; i > 0; i--)
  {
    test=0;
    for(j = 0; j < i; j++)
    {
      if(array[j].turn > array[j+1].turn) /* compare neighboring elements */
      {
        temp = array[j];    /* swap array[j] and array[j+1] */
        array[j] = array[j+1];
        array[j+1] = temp;
        test=1;
      }
    } /*end for j*/
    if(test==0) break; /*will exit if the list is sorted!*/
  } /*end for i*/
      
}
