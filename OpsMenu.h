
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

// Menu options
#define pRESET 0
#define pENABLE 1
#define pOPEN 2
#define pSOLVE 3
#define pSTART 4

// For master communications
#define SEND_STATUS 0xB0
#define SEND_TIME 0xC0
#define SEND_GAMESTATE 0xD0

// For line refreshes
#define TIME_ONLY 0xFF
#define TOP_LINE      0b00000001
#define RESERVED_LINE 0b00000010
#define PEDESTAL_LINE 0b00000100
#define OPTION_LINE   0b00001000
#define ALL_LINES     0b00001111

#define ENABLED_HUE 32
#define OPEN_HUE 64
#define SOLVED_HUE 96
#define DEFAULT_HUE 160
#define RESET_HUE	0

#define NUM_MENU_NAMES 5
const char *menuNames[NUM_MENU_NAMES]{
	"RESET",
	"ENABLE",
	"OPEN",
	"SOLVE",
	"START"
};

#define pHEIST 10

#define NUM_PEDESTAL_NAMES 11
const char *pedestalNames[NUM_PEDESTAL_NAMES]{
  "OPS",
  "VAULT",
  "DRIVER",
  "LASER",
  "GUARDS",
  "SEISMIC",
  "HACKER",
  "FINAL",
  "SECURITY",
  "ARK",
  "HEIST"
};

const uint16_t PEDESTAL_OPTIONS[NUM_PEDESTAL_NAMES] = {
  0b0000000000000001,   // ops
  0b0000000000001111,   // vault
  0b0000000000001111,   // driver
  0b0000000000001111,   // laser
  0b0000000000001111,   // guards
  0b0000000000001111,   // seismic
  0b0000000000001111,   // hacker
  0b0000000000001111,   // final
  0b0000000000001011,   // security sweeps
  0b0000000000001011,   // ark
  0b0000000000010001,   // heist (game)
};

class pedestalMenu{
public:
	pedestalMenu();
	void initPedestalMenu(uint8_t propNum, uint16_t whichOptions);
	// Set up the pedestalMenu object with its corresponding prop number (according to the master) and available menu options
	void assignStatus(uint8_t aStatus);
	// Set status for the menu item
	void optionHelper(char buf[]);
	// Fill the buffer with the menu item text
  void statusHelper(char buf[]);
  // Fill the buffer with the status text
  void pedestalHelper(char buf[]);
  // Fill the buffer with the pedestal name
	bool isMe(uint8_t which);
	// Is a given prop the one that this menu item corresponds to?
	uint8_t menuOption();
	// returns the selected (numerical) menu option
	uint8_t pedestalNum();
	// Returns the propNum (master corresponding) for the menu item
	uint8_t lastStatus();
	// Returns the last updated status for the menu item
  void optionPlus();    // Advance the menu
  void optionMinus();   // Reverse the menu
private:
	uint8_t _status;
	uint16_t _availableOptions = 0;   // One bit for each option
	uint8_t _myPedestalNum;
  uint8_t _currentOption = 15;
};


//////////////////////

pedestalMenu::pedestalMenu(){
}

// Initialize the menu option with the prop number and menu options
void pedestalMenu::initPedestalMenu(uint8_t propNum, uint16_t whichOptions){
	_status = 0xFF;
	_availableOptions = whichOptions?whichOptions:1;   // Can always reset
  _myPedestalNum = propNum;
  optionPlus();     // Go to the first available option
}

// Return last status
uint8_t pedestalMenu::lastStatus(){
	return _status;
}

// Assign a new status
void pedestalMenu::assignStatus(uint8_t aStatus){
	_status = aStatus;
}

// Return TRUE if the given prop number is the number of the prop that this menu item corresponds with
bool pedestalMenu::isMe(uint8_t which){
	return which == _myPedestalNum;
}

// Return the prop number for this menu item
uint8_t pedestalMenu::pedestalNum(){
	return _myPedestalNum;
}

// Return the current menu option for this menu item
uint8_t pedestalMenu::menuOption(){
	return _currentOption;
}

// Fill the buffer with the text of the which'th menu option for this menu item
void pedestalMenu::optionHelper(char buf[]){
  if(_currentOption<NUM_MENU_NAMES)
	  strcpy(buf,menuNames[_currentOption]);
  else
    strcpy(buf,"NOT AVAILABLE");
}

void pedestalMenu::statusHelper(char buf[]){
	switch(_status){
		case ENABLED:
			strcpy(buf,"ENABLED");
			break;
		case RESET:
			strcpy(buf,"RESET");
			break;
		case SOLVED:
			strcpy(buf,"SOLVED");
			break;
		case OPEN:
			strcpy(buf,"OPEN");
			break;
		default:
			strcpy(buf,"NOT SET");
			break;
	}
}

void pedestalMenu::pedestalHelper(char buf[]){
  if(_myPedestalNum<NUM_PEDESTAL_NAMES)
	  strcpy(buf,pedestalNames[_myPedestalNum]);
  else
    strcpy(buf,"NO PEDESTAL");
}

void pedestalMenu::optionPlus(){
  if(_availableOptions)
    do{
      _currentOption = (_currentOption+1)%16;
    } while(!bitRead(_availableOptions,_currentOption));
}

void pedestalMenu::optionMinus(){
  if(_availableOptions)
    do{
      _currentOption = (_currentOption+15)%16;
    } while(!bitRead(_availableOptions,_currentOption));
}


///////////////////////

// Set the status of the menu item corresponding to the prop number
void assignMenuStatus(pedestalMenu p[], uint8_t num, uint8_t pedestalNum, uint8_t aStatus){
	for(uint8_t i = 0;i < num;i++)
		if(p[i].isMe(pedestalNum))
			p[i].assignStatus(aStatus);
}
