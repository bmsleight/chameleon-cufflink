/*

 Not possible to use SoftPWM Library

 
 */

 
#define RED_PIN 1
#define GREEN_PIN 3
#define BLUE_PIN 4
// Need for Speed so this will be
//   DDRD = B00011010; // 



// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(RED_PIN, OUTPUT);     
  pinMode(GREEN_PIN, OUTPUT);     
  pinMode(BLUE_PIN, OUTPUT);     
  //   DDRD = B00011010; //
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(RED_PIN, LOW);    
  delay(500);                 
  digitalWrite(RED_PIN, HIGH);    
  delay(500);               
  digitalWrite(RED_PIN, LOW);    
  delay(2000);               

  rgb(254, 32, 2, 4000, 4000, 4000);
  
  delay(1000);



}

void all_rgb(boolean state) {
  byte mask = 0;
  mask +=  1 << (RED_PIN);
  mask +=  1 << (GREEN_PIN);
  mask +=  1 << (BLUE_PIN);
  if (state) {
    PORTB |= mask;   // turns on 1,3,4 but leaves pins other pins alone
  }
  else {
    PORTB &= ~mask;
  }
}


void rgb(byte r_target, byte g_target, byte b_target, unsigned long fade_up_time, unsigned long on_time, unsigned long fade_off_time) {
  // Try and make the fade-up, on and fade-down do exectly the same thing in the pseudo PWM loop. 
  // Create a table with 
  //   Millseconds_for_this_part, r_value, g_value, b_value
  unsigned long totalOnTime;
  byte r_value;
  byte g_value;
  byte b_value;
  typedef struct
  {
    unsigned long milliseconds;
    byte r_value;
    byte g_value;
    byte b_value;
  }  pwmTiming_type;
  pwmTiming_type pwmTiming[17];
  for (byte l = 0; l < 7; l++) {
    pwmTiming[l].milliseconds = fade_up_time/7;
    pwmTiming[l].r_value = (r_target * (l+1) )/(8) ;
    pwmTiming[l].g_value = (g_target * (l+1) )/(8);
    pwmTiming[l].b_value = (b_target * (l+1) )/(8);
  }
  pwmTiming[8].milliseconds = on_time;
  pwmTiming[8].r_value = r_target;
  pwmTiming[8].g_value = g_target;
  pwmTiming[8].b_value = b_target;
  for (byte l = 9; l < 17; l++) {
    pwmTiming[l].milliseconds = fade_off_time/7;
    pwmTiming[l].r_value = (r_target * (17-l))/8;
    pwmTiming[l].g_value = (g_target * (17-l))/8;
    pwmTiming[l].b_value = (b_target * (17-l))/8;
  }
  for (byte l = 0; l < 17; l++) {
    r_value = pwmTiming[l].r_value;
    g_value = pwmTiming[l].g_value;
    b_value = pwmTiming[l].b_value;
    totalOnTime = millis() + pwmTiming[l].milliseconds;
    while (totalOnTime > millis())  {
      all_rgb(HIGH);
      // Not very scientific, but sping rounf quick...
      for (byte p = 0; p < 255; p++) {  
        if (p > r_value) {
          PORTB &= ~(1 << RED_PIN);
        }
        if (l > g_value) {
          PORTB &= ~(1 << GREEN_PIN);
        }
        if (l > b_value) {
          PORTB &= ~(1 << BLUE_PIN);
        }
      }
    }
  }
  all_rgb(LOW);
}

