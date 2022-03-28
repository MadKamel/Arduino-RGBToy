// Code written by MadKamel. Hello!
// TODO: get a 10K ohm resistor and fix the button lmao
// TODO: figure out how to get the IR receiver to work
int R = 9;
int G = 10;
int B = 11;
int BTN = 2;
int BRIGHTNESS = 32;
bool EXPECTED_BTN_STATE = false;
int COLOUR = 0;

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
//9: bluey white
void setcolour(int colour) {
	switch(colour) {
		case 0:
			analogWrite(R, 255/BRIGHTNESS);
			analogWrite(G, 255/BRIGHTNESS);
			analogWrite(B, 255/BRIGHTNESS);
		break;
		case 1:
			analogWrite(R, 255/BRIGHTNESS);
			analogWrite(G, 0/BRIGHTNESS);
			analogWrite(B, 0/BRIGHTNESS);
		break;
		case 2:
			analogWrite(R, 0/BRIGHTNESS);
			analogWrite(G, 255/BRIGHTNESS);
			analogWrite(B, 0/BRIGHTNESS);
		break;
		case 3:
			analogWrite(R, 0/BRIGHTNESS);
			analogWrite(G, 0/BRIGHTNESS);
			analogWrite(B, 255/BRIGHTNESS);
		break;
		case 4:
			analogWrite(R, 0/BRIGHTNESS);
			analogWrite(G, 255/BRIGHTNESS);
			analogWrite(B, 255/BRIGHTNESS);
		break;
		case 5:
			analogWrite(R, 255/BRIGHTNESS);
			analogWrite(G, 255/BRIGHTNESS);
			analogWrite(B, 0/BRIGHTNESS);
		break;
		case 6:
			analogWrite(R, 255/BRIGHTNESS);
			analogWrite(G, 0/BRIGHTNESS);
			analogWrite(B, 255/BRIGHTNESS);
		break;
		case 7:
			analogWrite(R, 255/BRIGHTNESS);
			analogWrite(G, 80/BRIGHTNESS);
			analogWrite(B, 0/BRIGHTNESS);
		break;
		case 8:
			analogWrite(R, 0/BRIGHTNESS);
			analogWrite(G, 80/BRIGHTNESS);
			analogWrite(B, 255/BRIGHTNESS);
		break;
		case 9:
			analogWrite(R, 80/BRIGHTNESS);
			analogWrite(G, 80/BRIGHTNESS);
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
void flashcolour(int relative_delay, int main_delay, int colour) {
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

//this is the mainloop function.
//current configuration: switch between colours.
void loop() {
	flashcolour(10, 1000, 0);
	flashcolour(10, 1000, 1);
	flashcolour(10, 1000, 2);
	flashcolour(10, 1000, 3);
	flashcolour(10, 1000, 4);
	flashcolour(10, 1000, 5);
	flashcolour(10, 1000, 6);
	flashcolour(10, 1000, 7);
	flashcolour(10, 1000, 8);
	flashcolour(10, 1000, 9);
}
