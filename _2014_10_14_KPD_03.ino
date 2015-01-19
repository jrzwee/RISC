/*******************  Keypad  *******************

	- Codeeingabe fertiggestellt.
	- Maximal 3 Versuche?
	
	- Ausstehende Bugfixes		[f] ... fixed
		- 
	
****** Andreas Zapfl  5.CHELI  Bulme Graz ******/

#include <Keypad.h>
#define length 3	// Codelänge = length + 1

const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns

char temp[] = "0000";
char code[] = "3141";
char key;

unsigned char i = 0;

// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = { 5, 4, 3, 2 };
byte colPins[COLS] = { 8, 7, 6 }; 

// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//#define ledpin 13

void setup()
{
	//pinMode(ledpin,OUTPUT);
	//digitalWrite(ledpin, LOW);
	Serial.begin(9600);
}

void loop()
{
	key = keypad.getKey();
	
	if(key)  // Check for a valid key.
	{
		switch (key)
		{
		case '*':
			abort();
			break;
		case '#':
			verify();
			break;
		default:
			if(i <= length) {
			temp[i] = key;
			Serial.print(key); 
			i++; }
		}	
	}
}

void verify()
{
	if (i>0) 
	{
		if (compare()) 
		{
			//digitalWrite(ledpin, HIGH);
			Serial.print(" - YES"); 
		}
		else 
		{
			//digitalWrite(ledpin, LOW);
			Serial.print(" - NO");
		}
	Serial.println(); 
	}
	clear();
	delay(50);
}

bool compare()
{
	for(char j = 0; j <= length; j++)
	{
		if(temp[j] != code[j])
			return false;
	}
			return true;
}

void abort()
{
	if(i!=0) 
	{
	i = 0;
	Serial.print(" - ABORT");
	Serial.println(); 
	}
}

void clear()
{
	i = 0;
	
	for(char c = 0; c <= length; c++)
		temp[c] = '0';
}
