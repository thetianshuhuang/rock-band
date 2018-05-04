/*
 * splash.h
 *
 * Splash screen display routine
 */
#ifndef SPLASH_H
#define SPLASH_H


// --------showSplash--------
// Show the splash screen
void showSplash(char* image);


// --------menuSplash--------
// Show the main menu splash screen
void menuSplash(void);


// --------scoreSplash--------
// Show the song end score splash screen
void scoreSplash(uint16_t score);


// --------multiplayerSplash--------
// Show the multiplayer splash screen
void multiSplash(void);


#endif
