#include "njPiano.h"

#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>

static const int defaultOctave = 1;

static int bpm;
static bool soundEnabled;
static int octave;

static Piecelet* piecelets;
static int currentPiecelet;
static int currentBatch;
static int blockSize;

static void reset();
static int initPiecelets();

int init(int bpm_, bool enableSound_, int blockSize_) {
	bpm = bpm_;
	soundEnabled = enableSound_;
	blockSize = blockSize_;
	octave = defaultOctave;

	reset();
	if (initPiecelets()) {
		return 1;
	}

	return 0;
}

int kill() {
	free(piecelets);
	piecelets = NULL;

	return 0;
}

static void reset() {
	kill();

	currentPiecelet = 0;
	currentBatch = 1;
}

static int initPiecelets() {
	piecelets = (Piecelet*) calloc(blockSize, sizeof(Piecelet));
	if (piecelets == NULL) {
		return 1;
	}
	return 0;
}

int append(Note note, Duration duration) {
	if (currentPiecelet > (currentBatch * blockSize)) {
		currentBatch++;
		piecelets = (Piecelet*) realloc(piecelets, currentBatch * blockSize);
		if (piecelets == NULL) {
			return 1;
		}
	}

	Piecelet piecelet = {note, duration, octave };
	piecelets[currentPiecelet] = piecelet;

	currentPiecelet++;

	return 0;
}

int remove() {
	if (currentPiecelet > 0) {
		currentPiecelet--;
	}
	return 0;
}

int clear() {
	reset();
	if (initPiecelets()) {
		return 1;
	}

	currentPiecelet = 0;
	currentBatch = 1;

	return 0;
}

MusicPiece getMusicPiece() {
	MusicPiece musicPiece = { piecelets, currentPiecelet };
	return musicPiece;
}

int honeyTheyrePlayingOurSong(const MusicPiece* musicPiece) {


	return 0;
}
