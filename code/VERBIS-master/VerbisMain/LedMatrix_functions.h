#ifndef LEDMATRIX_FUNCTIONS_H
#define LEDMATRIX_FUNCTIONS_H

#define DATA_PIN    2
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    64
CRGB leds[NUM_LEDS];
#define BRIGHTNESS         120
#define FRAMES_PER_SECOND  30

uint8_t gHue = 0;
int color_array[3];

void HEX2RGB(String hex_value) {
	int number = (int) strtol( &hex_value[1], NULL, 16);
	color_array[0] = number >> 16;
	color_array[1] = number >> 8 & 0xFF;
	color_array[2] = number & 0xFF;
}

void hour() {
	//Serial.println(HOUR);
	int i = 0;
	int led_nr;
	HEX2RGB(config.startColor);
	CRGB start_C(color_array[0],color_array[1],color_array[2]);
	while ( i<HOUR.length() ) {
		if (HOUR.charAt(i) != '*') {
			led_nr = 10*(HOUR.charAt(i)-48)+(HOUR.charAt(i+1)-48);
			leds[led_nr] = start_C;
			i=i+2;
			server.handleClient();
		}
		else {
			i=i+1;
		}
	}
}

void star() {
	while (DateTime.second != 0) {
		fadeToBlackBy( leds, NUM_LEDS, 10);
		int pos = random16(NUM_LEDS);
		leds[pos] += CHSV( gHue + random8(230,250), 200, 255);
		FastLED.show();
		if (gHue == 255) {
			gHue = 0;
		}
		gHue++;
		server.handleClient();
	}
}

//===============

void afisare_led_no_wifi () {
	fadeToBlackBy( leds, NUM_LEDS, 20);
	int pos = beatsin16(13,0,NUM_LEDS-1);
	leds[pos] += CHSV( gHue, 255, 192);
	server.handleClient();
	if (gHue == 255) {
		gHue = 0;
	}
	gHue++;
}

//=================
void afisare_led_no_ntp () {
	uint8_t BeatsPerMinute = 62;
	CRGBPalette16 palette = RainbowColors_p;
	uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
	for( int i = 0; i < NUM_LEDS; i++) { //9948
		leds[i] = ColorFromPalette(palette, i*2, beat+(i*10));
	}
	server.handleClient();
}

//=================

void clear_display() {
	fill_solid( leds, NUM_LEDS, CRGB(0,0,0));
	FastLED.show();
}

//=================


void flash() {
	int i=0;
	int j=0;
	int led_nr=0;
	int elemente[32];
	HEX2RGB(config.startColor);
	CRGB start_C(color_array[0],color_array[1],color_array[2]);
	HEX2RGB(config.endColor);
	CRGB end_C(color_array[0],color_array[1],color_array[2]);
	while ( i<HOUR.length() ) {
		if (HOUR.charAt(i) != '*') {
			led_nr = 10*(HOUR.charAt(i)-48)+(HOUR.charAt(i+1)-48);
			elemente[j]=led_nr;
			i=i+2;
			j=j+1;
		}
		else {
			for( int k = 1; k < 255; k=k+1) {
				uint8_t amountOfBlending = k * 255;
				CRGB pixelColor = blend( end_C, start_C, amountOfBlending);
				for (int y=0;y<j;y++) {
					leds[elemente[y]] = pixelColor;
				}
				FastLED.show();
				server.handleClient();
				yield();
				if (DateTime.second > 57) {
					star();
					return;
				}
			}
			//delay(20);
			//server.handleClient();
			for( int k = 1; k < 255; k=k+2) {
				uint8_t amountOfBlending = k * 255;
				CRGB pixelColor = blend( start_C, end_C, amountOfBlending);
				for (int y=0;y<j;y++) {
					leds[elemente[y]] = pixelColor;
				}
				FastLED.show();
				server.handleClient();
				//yield();
				if (DateTime.second > 57) {
					star();
					return;
				}
			}
			// server.handleClient();
			i=i+1;
			j=0;
		}
	}
}

//=============



#endif /* LEDMATRIX_FUNCTIONS_H */
