/*
  heist.h
  dec2021

  Author: Jeremy Medow (jeremy@tungstencustoms.com)
*/

#include <SoftwareSerial.h>

#define UART_SPEED 19200
#define ACK_TIME 100

// Pedestal Definitions
#define OPS 0
#define VAULT 1
#define DRIVER 2
#define LASER 3
#define GUARDS 4
#define SEISMIC 5
#define HACKER 6
#define FINAL 7
#define SWEEPS 8
#define ARK 9

// Message/Status definitions
#define RESET    0x00
#define ENABLED  0x10       // low nibble is level number if applicable
#define OPEN     0x20       // low nibble is level number
#define SOLVED   0x30
#define ALT_P    0x40

#define LEVELSET 0xE0	    // low nibble is how many levels to play
#define ECHO     0xF0       // to just ask for status
#define ID       0xFE       // for identification of pedestals
#define ERROR    0xFF

/*
 state 0x00 .. 0x0F are reset, i.e. nothing happens.  Only use 0x00.
 state 0x01 through 0x1F are enabled but puzzle cabinet not yet opened
 state 0x20 through 0x2F are puzzle levels, not yet fully solved
    master can skip difficulty levels by responding when pedestal sends the one before skip
    for example if a pedestal has 3 difficulty levels, it should advance 0x21, 0x22, 0x30
    but if master only wants to play 2, it should send 0x30 after the pedestal sends 0x22
 state 0x30 is puzzle solved, display case open
 */

#define STATE_TIME  200     // How often to ask for the state
#define ECHO_TIME 50         // How long to wait for an echo

// Pedestal Class

class pedestal{
public:
    pedestal(SoftwareSerial *_theSoftSerial);
    bool setState(uint8_t state);
    void sendString(char* theString);
    void sendDouble(uint8_t highByte, uint8_t lowByte);
    uint8_t getState();                 // checks for status, subject to a timeout
    uint8_t getID();
    bool isNewState();                  // return true and clear it if _newState == true
private:
    uint8_t _lastState = ERROR;
    uint8_t _myID = ERROR;
    SoftwareSerial *_mySerial;
    unsigned long _lastAskTime = 0;
    bool _newState = false;
};
