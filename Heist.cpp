/*
 heist.cpp
 dec2021

 Author: Jeremy Medow (jeremy@tungstencustoms.com)
*/

#include "Heist.h"
#include <Arduino.h>

// Pedestal Class definitions

pedestal::pedestal(SoftwareSerial *theSoftSerial){
    _mySerial = theSoftSerial;
    _mySerial->begin(UART_SPEED);
};

bool pedestal::setState(uint8_t state){
    unsigned long start = millis();
    bool noEcho = true;
    uint8_t tempState = _lastState;

    _mySerial->listen();
    _mySerial->write(state);

    while( noEcho && ((millis()-start)<ECHO_TIME) ){       // Wait for echo or timeout
        if(_mySerial->available())
            noEcho = false;
        delay(2);
    }

    if(!noEcho)     // There's an echo
        _lastState = _mySerial->read();
    else
        _lastState = ERROR;

    if(_lastState != tempState)
      _newState = true;

    /*Serial.print("Sent: ");
    Serial.print(state);
    Serial.print("  Echo'd: ");
    Serial.println(_lastState);*/

    return (_lastState == state);
};

void pedestal::sendString(char* theString){
  _mySerial->print(theString);
  _mySerial->print('\r');
}

void pedestal::sendDouble(uint8_t highByte, uint8_t lowByte){
  _mySerial->write(highByte);
  _mySerial->write(lowByte);
}

uint8_t pedestal::getState(){
    uint8_t tempState = _lastState;

    if((_lastAskTime-millis())>STATE_TIME){     // Time to ask again
        _lastAskTime = millis();
        unsigned long start = millis();
        bool noEcho = true;

        _mySerial->listen();
        _mySerial->write(ECHO);

        while( noEcho && ((millis()-start)<ECHO_TIME) ){       // Wait for echo or timeout
            if(_mySerial->available())
                noEcho = false;
            delay(2);
        }

        if(!noEcho)     // There's an echo
            _lastState = _mySerial->read();
        else
            _lastState = ERROR;

    }

    if(_lastState != tempState)
      _newState = true;

    return _lastState;
};                 // checks for status, subject to a timeout


uint8_t pedestal::getID(){

    if(_myID == ERROR){      // Only if it's  not already been fetched
        unsigned long start = millis();
        bool noEcho = true;

        _mySerial->listen();
        _mySerial->write(ID);

        while( noEcho && ((millis()-start)<ECHO_TIME) ){       // Wait for echo or timeout
            if(_mySerial->available())
                noEcho = false;
            delay(2);
        }

        if(!noEcho)     // There's an echo
            _myID = _mySerial->read();
        else
            _myID = ERROR;
    }

    return (_myID);
}

bool pedestal::isNewState(){      // Clear _newState, return whether it was true
  bool tempFlag = _newState;
  _newState = false;
  return tempFlag;
}

/*
  END FILE
*/
