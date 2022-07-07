/*
  Master.h
  dec2021

  Author: Jeremy Medow (jeremy@tungstencustoms.com)
*/

const char PedestalNames[10][10] = {"Ops", "Vault", "Driver", "Laser", "Guards", "Seismic", "Hacker", "Final", "Sweeps", "Ark"};
const char StateNames[10][10] = {"RESET","READY","PEDESTALS","SWEEP","FAIL","HELP","FINAL","TRIDENT","TRIPLE","ESCAPE"};

// Ops Stuff
#define pRESET 0
#define pENABLE 1
#define pOPEN 2
#define pSOLVE 3
#define pSTART 4

#define pHEIST 10
#define SEND_STATUS 0xB0
#define SEND_TIME 0xC0
#define SEND_GAMESTATE 0xD0

// Game States
#define HEIST_RESET 0
#define HEIST_READY 1
#define HEIST_PEDESTALS 2
#define HEIST_SWEEP 3
#define HEIST_FAIL 4
#define HEIST_HELP 5
#define HEIST_FINAL 6
#define HEIST_TRIDENT 7
#define HEIST_TRIPLE 8
#define HEIST_ESCAPE 9

// Video files
#define NUM_BS_PINS 6
#define BS_INTRO 0
#define BS_GUARDS 1
#define BS_CAVEAT 2
#define BS_FINALE 3
#define BS_EXEUNT 4
#define BS_RESET 5
#define BS_INTRO_PIN 48
#define BS_GUARDS_PIN 46
#define BS_CAVEAT_PIN 44
#define BS_FINALE_PIN 42
#define BS_EXEUNT_PIN 49
#define BS_RESET_PIN 47
#define BS_OUT1 45
#define BS_OUT2 43

#define FAIL_SECONDS 50*60
#define TRIPLE_SECONDS 50*60
