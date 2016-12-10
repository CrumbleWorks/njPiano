/* ***************************************************************************
 * A small library that allows creating 'music pieces' on any modern computer.
 *
 * The library was originally written as a for-fun project back in school and
 * we decided to go over it once again and release it for the world to enjoy.
 *
 * Authors: Michael Stocker (dot_Sp0T) & Patrick Bächli (McDonnough)
 */

#ifndef NJPIANO_H_
#define NJPIANO_H_

#include <stdbool.h>

typedef enum njp_Note {
	Cl = 261,
	Cis = 277,
	D = 293,
	Dis = 311,
	E = 329,
	F = 349,
	Fis = 369,
	G = 391,
	Gis = 415,
	A = 440,
	Ais = 466,
	B = 493,
	Ch = 522
} njp_Note;

typedef enum njp_Duration {
	Semibreve = 10000,
	Minim = 5000,
	Crotchet = 2500,
	Quaver = 1250,
	Semiquaver = 625,
	Ganze = Semibreve,
	Halbe = Minim,
	Viertel = Crotchet,
	Achtel = Quaver,
	Sechzehntel = Semiquaver
} njp_Duration;

typedef struct njp_Piecelet {
	njp_Note note;
	njp_Duration duration;
	int octave;
} njp_Piecelet;

typedef struct njp_MusicPiece {
	njp_Piecelet* piecelets;
	int length;
} njp_MusicPiece;

/* ======================================================================== */

/*
 * Initializes and/or resets the library. MUST be called before using it.
 *
 * bmp         -> the desired Beats Per Minute
 * enableSound -> if the lib should output sounds while creating a music piece
 * blockSize   -> amount of piecelets per block
 *
 * Errorcodes:
 * 1 -> Memory Allocation failed
 */
int njp_init(int bpm, bool enableSound, int blockSize);

/*
 * Releases allocated resources and cleans up.
 */
void njp_kill();

/* ======================================================================== */

/*
 * Raises the octave used for notes by one
 *
 * Highest octave: 7
 *
 * Errorcodes:
 * 3 -> Octave already highest possible
 */
int njp_raiseOctave();

/*
 * Lowers the octave used for notes by one
 *
 * Lowest octave: 1
 *
 * Errorcodes:
 * 4 -> Octave already lowest possible
 */
int njp_lowerOctave();

/*
 * Appends a single Note measuring the desired Duration to the music piece.
 *
 * Errorcodes:
 * 1 -> Memory Allocation failed
 * 5 -> Could not play piecelet
 */
int njp_append(njp_Note, njp_Duration);

/*
 * Removes the last Note that was added to the music piece.
 *
 * Errorcodes:
 * 2 -> Nothing to remove
 */
int njp_remove();

/*
 * Removes all notes and leaves an empty music piece as if the init method had
 * been called.
 *
 * Errorcodes:
 * 1 -> Memory Allocation failed
 */
int njp_clear();

/*
 * Returns the music piece as of this point in time.
 */
njp_MusicPiece njp_getMusicPiece();

/* ======================================================================== */

/*
 * Plays a music piece.
 *
 * Errorcodes:
 * 5 -> Could not play
 */
int njp_honeyTheyrePlayingOurSong(njp_MusicPiece*);

#endif /* NJPIANO_H_ */
