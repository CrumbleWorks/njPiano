#include "njPiano.h"

#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>

#include <stdio.h>

const int defaultOctave = 1;

static int bpm;
static bool soundEnabled;
static int octave;

static njp_Piecelet* piecelets;
static int currentPiecelet;
static int currentBatch;
static int blockSize;

static void njp_reset();
static int njp_initPiecelets();
static int njp_playPiecelet(njp_Piecelet*);

int njp_init(int bpm_, bool enableSound_, int blockSize_) {
	bpm = bpm_;
	soundEnabled = enableSound_;
	blockSize = blockSize_;
	octave = defaultOctave;

	njp_reset();

	if (njp_initPiecelets()) {
		return 1;
	}

	return 0;
}

void njp_kill() {
	if(piecelets != NULL) {
		free(piecelets);
		piecelets = NULL;
	}
}

static void njp_reset() {
	njp_kill();

	currentPiecelet = 0;
	currentBatch = 1;
}

static int njp_initPiecelets() {
	piecelets = (njp_Piecelet*) calloc(blockSize, sizeof(njp_Piecelet));
	if (piecelets == NULL) {
		return 1;
	}
	return 0;
}

int njp_raiseOctave() {
    if(octave >= 7) {
    	return 3;
    }

    octave++;

    return 0;
}

int njp_lowerOctave() {
    if(octave <= 0) {
    	return 4;
    }

    octave--;

    return 0;
}

static int njp_playPiecelet(njp_Piecelet* piecelet) {
    if(!Beep(piecelet->note * piecelet->octave, piecelet->duration)) {
    	return 5;
    }

    return 0;
}

int njp_append(njp_Note note, njp_Duration duration) {
	if (currentPiecelet >= (currentBatch * blockSize)) {
		currentBatch++;

		piecelets = realloc(piecelets, (currentBatch * blockSize) * sizeof(njp_Piecelet));
		if (piecelets == NULL) {
			return 1;
		}
	}

	njp_Piecelet piecelet = {note, duration, octave};
	piecelets[currentPiecelet] = piecelet;

	currentPiecelet += 1;

	int ret;
	if(soundEnabled && (ret = njp_playPiecelet(&piecelet))) {
		return ret;
	}

	return 0;
}

int njp_remove() {
	if (currentPiecelet <= 0) {
		return 2;
	}

	currentPiecelet--;
	return 0;
}

int njp_clear() {
	njp_reset();
	if (njp_initPiecelets()) {
		return 1;
	}

	currentPiecelet = 0;
	currentBatch = 1;

	return 0;
}

njp_MusicPiece njp_getMusicPiece() {
	njp_Piecelet* tmp = (njp_Piecelet*) calloc(currentPiecelet, sizeof(njp_Piecelet));
	njp_MusicPiece musicPiece = { memcpy(tmp, piecelets, currentPiecelet * sizeof(njp_Piecelet)), currentPiecelet };
	return musicPiece;
}

int njp_honeyTheyrePlayingOurSong(njp_MusicPiece* musicPiece) {
	for (int i = 0; i < musicPiece->length; ++i) {
		int ret = njp_playPiecelet(&(musicPiece->piecelets[i]));
		if(ret) {
			return ret;
		}
	}

	return 0;
}
