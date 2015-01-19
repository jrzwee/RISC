/***************** RFID  Reader *****************

	- EEPROM wurde komplett Implementiert.
	
	- Ausstehende Bugfixes		[f] ... fixed
		- Wenn das EEPROM leer ist, gibt es bei start
		  leichte Fehler.
	
****** Andreas Zapfl  5.CHELI  Bulme Graz ******/

#include <SoftwareSerial.h>
#include <EEPROM.h>

SoftwareSerial RFID(2, 3); // RX and TX

#define STARTOFTEXT 0x02
#define ENDOFTEXT 0x03

char masteradd[] = "1300470B257A";
char card[12];

bool addcard = false;

char temp[12][20];

unsigned char adr = 0;		// DATENTYP?

unsigned char zanz = 0;		// KARTENANZAHL

unsigned char i = 0;

void setup()
{
  RFID.begin(9600);
  Serial.begin(9600);
  eesetup();				//EEPROM AUSLESEN
}

void loop()
{
  if (RFID.available() > 0) 
  {
	char c = RFID.read();

    switch(c)
    {  
    case STARTOFTEXT:
	  i = 0;
      break;
    case ENDOFTEXT:
      checkID();
      break;
    default:
      card[i] = c;
      Serial.print(card[i]);
	  i++;
    }
  }
}

void checkID()
{
  if(compareID(card, masteradd))
  {
    addcard = true;
	Serial.println("   ADDCARD TRUE");
  }
  else
  {
	if(addcard)
	{
		for(unsigned char spalte = 0; spalte < 12; spalte++)
		{
			temp[zanz][spalte] = card[spalte];
			EEPROM.write(zanz*12+spalte+1, card[spalte]);		// +1 UM KARTENANZAHL frei zu halten.
			delay(5);
		}
		zanz++;
		EEPROM.write(0, zanz);
		delay(5);
		Serial.print("   KOATN GSPEICHAT");
		addcard = false;
		delay(1250);
	}
	
	for(unsigned char zeile = 0; zeile < zanz; zeile++)
	{
		if(compareID(card, temp[zeile]))
		{
		Serial.println("   YES");
		return;
		}
		if(zeile == zanz - 1)
		Serial.println("   NO");
	}
  }
}

bool compareID(char arr1[], char arr2[])
{
  for(unsigned char j = 0; j<12; j++)
  {
    /*
	//DEBUG ----------------------
    Serial.print("   DEBUG ARR1: ");
    Serial.print(arr1[j]);
    Serial.print("   ");
    Serial.print("   DEBUG ARR2: ");
    Serial.print(arr2[j]);
    Serial.print("   ");
    // ---------------------------
	*/

    if(arr1[j] != arr2[j])
      return false;
  }
  return true;
}

void eesetup()
{
	zanz = EEPROM.read(0);

	for(unsigned char zeile = 0; zeile < zanz; zeile++)
	{														
		for(unsigned char spalte = 0; spalte < 12; spalte++)
		{
			temp[zeile][spalte] = EEPROM.read(adr+spalte+1);	// 0. Stelle = KARTENANZAHL
		}
		adr = adr + 12;
	}
	Serial.println("   *** SETUP DONE! ***   ");
}
