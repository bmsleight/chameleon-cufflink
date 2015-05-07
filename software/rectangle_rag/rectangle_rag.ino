/* 
*/

#include <avr/pgmspace.h>

#define RED_PIN 1
#define AMBER_PIN 3
#define GREEN_PIN 4
#define BUTTON_PIN 0
#define MAX_LOOPS 7
#define PRESS_INTERVAL 750

// Hello PVG - a perversion of your look-up.
#define ALL_OFF 0
#define RED 1
#define AMBER 2
#define GREEN 4
#define RED_FLASH 8
#define AMBER_FLASH 16
#define GREEN_FLASH 32
#define END_SEQUENCE 64

#define FLASH_INTERVAL_MILLIS 375
#define FLASH_ON 255

#define SEQUENCE_TYPES 6
#define MAX_STEPS 30
// see http://www.arduino.cc/en/Reference/PROGMEM
// https://github.com/lilspikey/arduino_sketches/blob/master/attiny/xmas/xmas.ino
// bitrate = pgm_read_word_near ( &(bitrate_table[temp][row_num]) );
// PROGMEM const uint16_t bitrate_table[15][6] = 

const uint8_t sequence[SEQUENCE_TYPES][MAX_STEPS][2] PROGMEM =
{
  { // Normal Traffic RAG
    {RED, 3},
    {RED + AMBER, 2},
    {GREEN, 7},
    {AMBER, 2},
    {RED, 3},
    {END_SEQUENCE, 1},
  },
  { // Vehicle RAG in Pelican only 
    //http://www.legislation.gov.uk/uksi/1997/2400/schedule/2/made?view=plain
    {RED, 3},
    {AMBER_FLASH, 3},
    {GREEN, 4},
    {AMBER, 3},
    {RED, 3},
    {END_SEQUENCE, 1},
  },
  { // Long Normal Traffic RAG
    {RED, 3},
    {RED + AMBER, 2},
    {GREEN, 7},
    {AMBER, 2},
    {RED, 5},
    {RED + AMBER, 2},
    {GREEN, 8},
    {AMBER, 2},
    {RED, 3},
    {RED + AMBER, 2},
    {GREEN, 7},
    {AMBER, 2},
    {RED, 6},
    {RED + AMBER, 2},
    {GREEN, 9},
    {AMBER, 2},
    {RED, 8},
    {RED + AMBER, 2},
    {GREEN, 12},
    {AMBER, 2},
    {RED, 3},
    {END_SEQUENCE, 1},
  },
  { // US RAG 
    {RED, 3},
    {AMBER, 2},
    {GREEN, 4},
    {AMBER, 3},
    {RED, 3},
    {END_SEQUENCE, 1},
  },
  { // Silly RAG 
    {RED, 1},
    {RED + AMBER, 1},
    {AMBER, 1},
    {AMBER + GREEN, 1},
    {GREEN, 1},
    {AMBER + GREEN, 1},
    {AMBER, 2},
    {RED + AMBER, 1},
    {RED, 1},
    {AMBER, 1},
    {AMBER + GREEN, 1},
    {GREEN, 1},
    {AMBER + GREEN, 1},
    {AMBER, 2},
    {RED + AMBER, 1},
    {RED, 1},
    {RED_FLASH , 1},
    {RED_FLASH + AMBER_FLASH, 2},
    {RED_FLASH + AMBER_FLASH + GREEN_FLASH, 3},
    {AMBER_FLASH + GREEN_FLASH, 2},
    {GREEN_FLASH, 1},
    {AMBER_FLASH + GREEN_FLASH, 2},
    {RED_FLASH + AMBER_FLASH + GREEN_FLASH, 3},
    {RED_FLASH + AMBER_FLASH, 2},
    {RED_FLASH , 1},
    {END_SEQUENCE, 1},
  },
  { // Long Pelican 
    {RED, 3},
    {AMBER_FLASH, 3},
    {GREEN, 4},
    {AMBER, 3},
    {RED, 3},
    {AMBER_FLASH, 4},
    {GREEN, 7},
    {AMBER, 3},
    {RED, 3},
    {AMBER_FLASH, 5},
    {GREEN, 8},
    {AMBER, 3},
    {RED, 3},
    {AMBER_FLASH, 4},
    {GREEN, 7},
    {AMBER, 3},    
    {RED, 3},    
    {END_SEQUENCE, 1},
  },
};

void setup() {                
  // initialize the digital pin as an output.
  pinsToOutput();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}


void loop() {

  uint8_t presses = 0;
  if(pressed())  {
    presses = getPresses(1, 1, 5, MAX_LOOPS);
    doSequence(presses-1);
  }


}


uint8_t getPresses(uint8_t presses, uint8_t min_press, uint8_t max_press, uint8_t max_loops) {
  uint8_t leds = pgm_read_byte_near( &(sequence[0][(presses-1)%4][0])); // Show Traffic Sequence 0 as pressed indicator 
  writeLEDs(leds, FLASH_ON); // Actually FLASH_ON is not used here, but I need to send two variables.
  delay(PRESS_INTERVAL);
  while(pressed() )  {
    presses++;
    if (presses > max_press)  {
        presses = min_press;
        max_loops--;
    }
    if (max_loops <= 0)  {
      return (max_press);
    }
    leds = pgm_read_byte_near( &(sequence[0][(presses-1)%4][0]));
    writeLEDs(leds, FLASH_ON); // Actually FLASH_ON is not used here, but I need to send two variables.
    delay(PRESS_INTERVAL);
  }
  return (presses);
}  



void doSequence(uint8_t s)  {
  uint8_t current_step = 0;
  // Look up what the LED should be doing based upon the stored sequences
  uint8_t leds = pgm_read_byte_near( &(sequence[s][current_step][0]));
  unsigned long start_milliseconds, length_of_step, last_flash_milliseconds;
  uint8_t flash = FLASH_ON; // Start with FLASH ON or HIGH
  last_flash_milliseconds = millis();
  while(leds != END_SEQUENCE )  {
    start_milliseconds = millis();
    length_of_step = 1000 * pgm_read_byte_near( &(sequence[s][current_step][1]));
    while((millis() - start_milliseconds) < (length_of_step) )  {
      writeLEDs(leds, flash);
      if ((millis() - last_flash_milliseconds) > FLASH_INTERVAL_MILLIS)  {
        last_flash_milliseconds = millis();
        flash = ~flash;
      }
    }
    //Restart Flash if finished a non-flashing step
    if (leds < RED_FLASH)
    {
      flash = FLASH_ON;
      last_flash_milliseconds = millis();
    }
    current_step++;
    leds = pgm_read_byte_near( &(sequence[s][current_step][0]));
  }
  writeLEDs(ALL_OFF, ALL_OFF);
}

void writeLEDs(uint8_t leds, uint8_t flash) {
  digitalWrite(RED_PIN,   (leds & RED)   | (leds & RED_FLASH   & flash));
  digitalWrite(AMBER_PIN, (leds & AMBER) | (leds & AMBER_FLASH & flash));
  digitalWrite(GREEN_PIN, (leds & GREEN) | (leds & GREEN_FLASH & flash));
}

bool pressed() {
   return !digitalRead(BUTTON_PIN);
}


void pinsToOutput()  {
  pinMode(RED_PIN,   OUTPUT);
  pinMode(AMBER_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}

