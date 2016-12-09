#ifndef NJPIANO_H_
#define NJPIANO_H_

typedef enum {
	false = 0,
	true = !false
};

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

typedef struct Dynamite {
	Note note;
	Duration duration;
	int octave;
} Dynamite;


int init(int bpm, int enableSound);
int kill();

int append(Note, Duration);
int remove();
int clear();
const Dynamite* getDynamites();

int honeyTheyrePlayingOurSong(const Dynamite*);

#endif /* NJPIANO_H_ */
