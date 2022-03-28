/* Code written by MadKamel, the astounding computer jockey.

		This code will control a little RGB light with a button. Simple. I hope to also expand functionality with an
	IR remote control later on, once I figure out how it works.
	
		This project uses:

			*Arduino UNO R3
			*Breadboard, Wires, Doohickeys
			*220 Ohm Resistor
			*10K Ohm Resistor
			*4-pin Contact Push Button
			*Common Cathode RGB LED (May have used the wrong word; it has a common ground pin)
			*Maybe some Capacitors later on (Spoiler alert: no capacitors used)
			*IR Signal Reciever

		Here's some code:
*/
// TODO: get a 10K ohm resistor and fix the button lmao
// TODO: figure out how to get the IR receiver to work
// TODO: figure out how to fix button jitter... capacitors?

int R = 9;				// pin for RGB LED's red input
int G = 10;				// pin for RGB LED's green input
int B = 11;				// pin for RGB LED's blue input
int BTN = 2;				// pin for button
int BRIGHTNESS = 8;			// this variable tracks the actual number by which to reduce brightness.
bool EXPECTED_BTN_STATE = false;	// this variable tracks the current state of the button, whether it be up or down.
int COLOUR = 0;				// this variable tracks the current colour

void setup() {
	pinMode(R, OUTPUT);
	pinMode(G, OUTPUT);
	pinMode(B, OUTPUT);
	pinMode(BTN, INPUT);
	setcolour(0);
}

//this code is kind of hard to digest, let me break it down:
bool keypress() {
	if(digitalRead(BTN) == LOW) {			//if button pressed, 
		if(EXPECTED_BTN_STATE) {		//and if the button was pressed earlier, then
			return false;			//just ignore it.
		}
		else {					//if it was just pressed now, then
			EXPECTED_BTN_STATE = true;	//remember that it was pressed
			return true;			//and act, because it was just pressed.
		}
	}
	else {						//if the button is not pressed, then
	EXPECTED_BTN_STATE = false;			//remember that it was not pressed
		return false;				//and ignore it.
	}
}

//this sets the brightness, for an upcoming remote control feature i'll add in.
void setbrightness(int brightness) {
	switch(brightness) {
		case 0:
			BRIGHTNESS = 32;
		break;
		case 1:
			BRIGHTNESS = 16;
		break;
		case 2:
			BRIGHTNESS = 8;
		break;
		case 3:
			BRIGHTNESS = 4;
		break;
		case 4:
			BRIGHTNESS = 2;
		break;
		case 5:
			BRIGHTNESS = 1;
		break;
	}
}

//sets the colour. there are 10 to choose from:
//0: white
//1: red
//2: green
//3: blue
//4: cyan
//5: yellow(ish)
//6: magenta(ish)
//7: orange
//8: turquoise (actually good colour)
//9: bluey white (white, but it has more blue)
void setcolour(int colour) {
	switch(colour) {
		case 0: // white
			analogWrite(R, 255/BRIGHTNESS);
			analogWrite(G, 255/BRIGHTNESS);
			analogWrite(B, 255/BRIGHTNESS);
		break;
		case 1: // red
			analogWrite(R, 255/BRIGHTNESS);
			analogWrite(G, 0/BRIGHTNESS);
			analogWrite(B, 0/BRIGHTNESS);
		break;
		case 2: // green
			analogWrite(R, 0/BRIGHTNESS);
			analogWrite(G, 255/BRIGHTNESS);
			analogWrite(B, 0/BRIGHTNESS);
		break;
		case 3: // blue
			analogWrite(R, 0/BRIGHTNESS);
			analogWrite(G, 0/BRIGHTNESS);
			analogWrite(B, 255/BRIGHTNESS);
		break;
		case 4: // cyan
			analogWrite(R, 0/BRIGHTNESS);
			analogWrite(G, 255/BRIGHTNESS);
			analogWrite(B, 255/BRIGHTNESS);
		break;
		case 5: // yellow(ish)
			analogWrite(R, 255/BRIGHTNESS);
			analogWrite(G, 255/BRIGHTNESS);
			analogWrite(B, 0/BRIGHTNESS);
		break;
		case 6: // magenta(ish)
			analogWrite(R, 255/BRIGHTNESS);
			analogWrite(G, 0/BRIGHTNESS);
			analogWrite(B, 255/BRIGHTNESS);
		break;
		case 7: // orange
			analogWrite(R, 255/BRIGHTNESS);
			analogWrite(G, 80/BRIGHTNESS);
			analogWrite(B, 0/BRIGHTNESS);
		break;
		case 8: // turquoise
			analogWrite(R, 0/BRIGHTNESS);
			analogWrite(G, 80/BRIGHTNESS);
			analogWrite(B, 255/BRIGHTNESS);
		break;
		case 9: // bluey white
			analogWrite(R, 127/BRIGHTNESS);
			analogWrite(G, 127/BRIGHTNESS);
			analogWrite(B, 255/BRIGHTNESS);
		break;
		default:
			COLOUR = COLOUR + 1;
			if(COLOUR == 10) {
				COLOUR = 0;
			}
			setcolour(COLOUR);
		break;
	}
}

//this function smoothly brings up a colour.
//really only one downside to speak of- it cannot be configured to change brightness.
void flashcolour(int relative_delay, int main_delay, int colour, bool exit_flash) {
	setbrightness(0);
	setcolour(colour);
	delay(relative_delay);
	setbrightness(1);
	setcolour(colour);
	delay(relative_delay);
	setbrightness(2);
	setcolour(colour);
	delay(relative_delay);
	setbrightness(3);
	setcolour(colour);
	delay(relative_delay);
	setbrightness(4);
	setcolour(colour);
	delay(relative_delay);
	setbrightness(5);
	setcolour(colour);

	if(exit_flash) { // only run if the flash will not fade away.
		delay(main_delay);
		setbrightness(4);
		setcolour(colour);
		delay(relative_delay);
		setbrightness(3);
		setcolour(colour);
		delay(relative_delay);
		setbrightness(2);
		setcolour(colour);
		delay(relative_delay);
		setbrightness(1);
		setcolour(colour);
		delay(relative_delay);
		setbrightness(0);
		setcolour(colour);
		delay(relative_delay);
		setbrightness(0);
		setcolour(colour);
	}
}

//this is the mainloop function.
//current configuration: wait for the button to get pressed, then change colour.
void loop() {						// upon iterating mainloop-
	if(keypress()) {				// if button is pressed once
		setcolour(10);				// get the next colour (colour 10 cycles to the next one)
		flashcolour(10, 1000, COLOUR, false);	// display the current colour
		delay(100);				// wait a bit in case the button jitters.
	}
}
