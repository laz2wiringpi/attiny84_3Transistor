

#include <Bounce2.h>
#include <EEPROM.h>
//#include "pitches.h"
 
 #if defined (__AVR_ATtiny85__)

#define  _OUT_BLUE  4   //  3   
#define  _OUT_BROWN  3  //  2
#define  _OUT_GRAY  1   //  6 ---  miso
#define  _OUT_GREEN  0  //  5 ---  mosi
#define IN_SWITCH 2  //  7 ---  sck

#else
#define  _OUT_BLUE  3    
#define  _OUT_BROWN  5   
#define  _OUT_GRAY  6    
#define  _OUT_GREEN  9   
#define IN_SWITCH 2   
#endif 

/*

// TINY 85
int OUT_BLUE = 4 ;   //  3   
int OUT_BROWN = 3 ;  //  2
int OUT_GRAY = 1 ;   //  6 ---  miso
int OUT_GREEN = 0 ;  //  5 ---  mosi

#define IN_SWITCH 2  //  7 ---  sck
*/ 
// UNO
int OUT_BLUE =  _OUT_BLUE;   //  3   
int OUT_BROWN = _OUT_BROWN;  //  2
int OUT_GRAY =  _OUT_GRAY;   //  6 ---  miso
int OUT_GREEN = _OUT_GREEN;  //  5 ---  mosi
 


 





// **********************************
#define BOUNCEINTRAVAL 12
 
Bounce BounceIN_SWITCH = Bounce();
int IN_SWITCH_status = 0;


 
int OUT_PINS[] = {OUT_BLUE,OUT_BROWN,OUT_GRAY,OUT_GREEN};

int OUT_status[] = { 0, 0, 0, 0 };


unsigned long previousMillis = 0;
unsigned long interval = 1000;

int DOALL = 0; 

int fadevalue = 0;
int fade_increment = 2;

// **********************************  
 
/*


// notes in the melody:
int melody[] = {
	NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
	4, 8, 8, 4, 4, 4, 4, 4
};






   for (int thisNote = 0; thisNote < 8; thisNote++) {

	   // to calculate the note duration, take one second
	   // divided by the note type.
	   //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
	   int noteDuration = 1000 / noteDurations[thisNote];
	   tone(OUT_GREEN, melody[thisNote], noteDuration);

	   // to distinguish the notes, set a minimum time between them.
	   // the note's duration + 30% seems to work well:
	   int pauseBetweenNotes = noteDuration * 1.30;
	   delay(pauseBetweenNotes);
	   // stop the tone playing:
	   noTone(OUT_GREEN);
   }
   
   
   */ 
  
void setup() {
for (int i = 0; i <= 3; i++){
	   pinMode(OUT_PINS[i], OUTPUT);
	   digitalWrite(OUT_PINS[i], LOW);
   }
// FLASH ALL  FOR 1/2 sec STATUS TEST 
for (int i = 0; i <= 3; i++){
   
	digitalWrite(OUT_PINS[i], HIGH);
}

delay(500);

for (int i = 0; i <= 3; i++){

	digitalWrite(OUT_PINS[i], LOW);
}
/////////////////////////////////

  pinMode(IN_SWITCH, INPUT_PULLUP);
  BounceIN_SWITCH.attach(IN_SWITCH);
  BounceIN_SWITCH.interval(BOUNCEINTRAVAL); // interval in ms

   IN_SWITCH_status = EEPROM.read(0);

   if (IN_SWITCH_status == 0){
	   IN_SWITCH_status++;
	   DOALL = 1;
   }
	 


  // put your setup code here, to run once:

}
// **********************************


void DOblinkJay( int delaytime ) {

	if (OUT_status[0] > 0)
	{
		digitalWrite(OUT_PINS[0], (LOW));
		digitalWrite(OUT_PINS[1], (HIGH));
		digitalWrite(OUT_PINS[2], (HIGH));
		OUT_status[0] = 0;
	}
	else
	//if (OUT_status[1] > 0)
	{
		digitalWrite(OUT_PINS[0], (HIGH));
		digitalWrite(OUT_PINS[1], (LOW));
		digitalWrite(OUT_PINS[2], (LOW));
		OUT_status[0] = 1;
	}
	 
	interval = delaytime;



}
int DELAYCHECKbutton(int delaytime) {

	 

unsigned long currentMillis = millis();
unsigned long tmppreviousMillis = currentMillis;
int tmp = 0;

while (currentMillis - tmppreviousMillis <= delaytime) {

	tmp = digitalRead(IN_SWITCH);
	if (  tmp = LOW  )
		return 1;
	currentMillis = millis();

	}
return 0;
 

//	delay(delaytime);
}

int dofade(int delaytime) {

	int val1 = 0;
	int val2 = 0;
	int val3 = 0;


	 fadevalue = fade_increment + fadevalue;
	if ((fadevalue >= 510) || (fadevalue <= 1)) fade_increment = fade_increment * -1;

	if ((fadevalue < 255) && (fadevalue >= 1)){
		val1 = 256 - fadevalue;

	 
	}
	
	if ((fadevalue >= 256) && (fadevalue <= 510)){
		val2 = fadevalue - 254;


	}
	if ((fadevalue >= 0) && (fadevalue <= 255)){
		val3 = fadevalue    ;


	}
	else
	if ((fadevalue >= 256) && (fadevalue <= 510)){
		val3 = ( 513  -  fadevalue )   ;
	}






	 

 


	analogWrite(OUT_PINS[0], val1);
	analogWrite(OUT_PINS[1], val2);
	analogWrite(OUT_PINS[2], val3);

	interval = delaytime;
	return 0;


}

int DOdblblinkJay(int delaytime) {

	if (OUT_status[0] > 0)
	{
		digitalWrite(OUT_PINS[0], (LOW));
		digitalWrite(OUT_PINS[1], (HIGH));
		digitalWrite(OUT_PINS[2], (HIGH));
		OUT_status[0] = 0;


		if 	(DELAYCHECKbutton(delaytime / 10)) return 1;



		digitalWrite(OUT_PINS[1], (LOW));
		if (DELAYCHECKbutton(delaytime / 10)) return 1;
	 
		digitalWrite(OUT_PINS[1], (HIGH));

		if (DELAYCHECKbutton(delaytime / 10)) return 1;
		digitalWrite(OUT_PINS[1], (LOW));
		if (DELAYCHECKbutton(delaytime / 10)) return 1;

		digitalWrite(OUT_PINS[1], (HIGH));

	}
	else
		//if (OUT_status[1] > 0)
	{
		digitalWrite(OUT_PINS[0], (HIGH));
		digitalWrite(OUT_PINS[1], (LOW));
		digitalWrite(OUT_PINS[2], (LOW));
		OUT_status[0] = 1;

		if (DELAYCHECKbutton(delaytime / 10)) return 1;

		digitalWrite(OUT_PINS[0], (LOW));
		if (DELAYCHECKbutton(delaytime / 10)) return 1;

		digitalWrite(OUT_PINS[0], (HIGH));
		if (DELAYCHECKbutton(delaytime / 10)) return 1;

		digitalWrite(OUT_PINS[0], (LOW));
		if (DELAYCHECKbutton(delaytime / 10)) return 1;

		digitalWrite(OUT_PINS[0], (HIGH));

	}

	interval = delaytime;
	return 0;


}
int DOdblblinkJayoff(int delaytime) {

	if (OUT_status[0] > 0)
	{
		digitalWrite(OUT_PINS[0], (LOW));
		digitalWrite(OUT_PINS[1], (HIGH));
		digitalWrite(OUT_PINS[2], (HIGH));
		OUT_status[0] = 0;


		if (DELAYCHECKbutton(delaytime / 10)) return 1;



		digitalWrite(OUT_PINS[1], (LOW));
		if (DELAYCHECKbutton(delaytime / 10)) return 1;

		digitalWrite(OUT_PINS[1], (HIGH));

		if (DELAYCHECKbutton(delaytime / 10)) return 1;
		digitalWrite(OUT_PINS[1], (LOW));
		if (DELAYCHECKbutton(delaytime / 10)) return 1;

	//	digitalWrite(OUT_PINS[1], (HIGH));

	}
	else
		//if (OUT_status[1] > 0)
	{
		digitalWrite(OUT_PINS[0], (HIGH));
		digitalWrite(OUT_PINS[1], (LOW));
		digitalWrite(OUT_PINS[2], (LOW));
		OUT_status[0] = 1;

		if (DELAYCHECKbutton(delaytime / 10)) return 1;

		digitalWrite(OUT_PINS[0], (LOW));
		if (DELAYCHECKbutton(delaytime / 10)) return 1;

		digitalWrite(OUT_PINS[0], (HIGH));
		if (DELAYCHECKbutton(delaytime / 10)) return 1;

		digitalWrite(OUT_PINS[0], (LOW));
		if (DELAYCHECKbutton(delaytime / 10)) return 1;

	//	digitalWrite(OUT_PINS[0], (HIGH));

	}

	interval = delaytime;
	return 0;


}

void loop() {
  // put your main code here, to run repeatedly:

	if  (BounceIN_SWITCH.update())  {

		int readpin = !BounceIN_SWITCH.read();
		DOALL = 0;

		if (readpin) {
			if (IN_SWITCH_status >= 10){
				IN_SWITCH_status = 0;

			}
			else
			{
				IN_SWITCH_status++;
			}
		}
		if (IN_SWITCH_status == 0)   {
			DOALL = 1;
			
		} 
		
		EEPROM.update(0, IN_SWITCH_status);

	}
	unsigned long currentMillis = millis();
 



	if (currentMillis - previousMillis > interval) {
		// save the last time you blinked the LED 
		previousMillis = currentMillis;
		
		if (DOALL != 0) {
			DOALL++;
			if (DOALL > 10){
			
			
				IN_SWITCH_status++;
				if (IN_SWITCH_status == 0){
					IN_SWITCH_status++;
				}
				DOALL = 1;

		    }
			 

			 
		}
		 
		 

		switch (IN_SWITCH_status) {
		case 0:
			 
		//	IN_SWITCH_status ++ ;
			interval = 10;
			break;

		case 1:

			DOblinkJay(1000);

			break;
		case 2:
			DOblinkJay(750);
			break;
		case 3:
			DOblinkJay(500);
			break;
		case 4:
			DOblinkJay(250);
			break;
		case 5:
			DOblinkJay(100);
			break;
		case 6:
			DOblinkJay(50);
			break;

		case 7:
			DOdblblinkJay(1000);
			//	IN_SWITCH_status++;
			
			 
			break;

		case 8:
			DOdblblinkJay(500);
			 
			break;

		case 9:
			DOdblblinkJayoff(1000);

			break;
 
		case 10:
			dofade(2);

			break;

		 default:
			// if nothing else matches, do the default
			// default is optional
		 	IN_SWITCH_status = 0;
			 
		}

		 
	 


	}

 

}
