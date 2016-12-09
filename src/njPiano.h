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

typedef enum Note {
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
} Note;

typedef enum Duration {
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
} Duration;

typedef struct Piecelet {
	Note note;
	Duration duration;
	int octave;
} Piecelet;

typedef struct MusicPiece {
	Piecelet* piecelets;
	int length;
} MusicPiece;

/* ======================================================================== */

/*
 * Initializes and/or resets the library. MUST be called before using it.
 *
 * bmp         -> the desired Beats Per Minute
 * enableSound -> if the lib should output sounds while creating a music piece
 * blockSize   -> amount of piecelets per block
 */
int init(int bpm, bool enableSound, int blockSize);

/*
 * Releases allocated resources and cleans up.
 */
int kill();

/* ======================================================================== */

/*
 * Appends a single Note measuring the desired Duration to the music piece.
 */
int append(Note, Duration);

/*
 * Removes the last Note that was added to the music piece.
 */
int remove();

/*
 * Removes all notes and leaves an empty music piece as if the init method had
 * been called.
 */
int clear();

/*
 * Returns the music piece as of this point in time.
 */
MusicPiece getMusicPiece();

/* ======================================================================== */

/*
 * Plays a music piece.
 */
int honeyTheyrePlayingOurSong(const MusicPiece*);

#endif /* NJPIANO_H_ */
