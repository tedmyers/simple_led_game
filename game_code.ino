// program for 
#define NUM_LEDS 8
uint8_t LED[]={
  12, // red
  11, // yellow
  10, // yellow
  9,  // green
  8,  // green
  7,  // yellow
  6,  // yellow
  5   // red
};
uint8_t buttonPin = 4;
int iii, jjj;
uint32_t start_interval = 50000;
uint32_t current_interval = start_interval;

void setup() {
  // put your setup code here, to run once:

  for (iii=0; iii<NUM_LEDS; iii++)
    { pinMode(LED[iii], OUTPUT); }

  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH); // enable pullup

  Serial.begin(9600); // debugging
}

// starts round of scrolling LEDs with delay between LED switching 
//   at interval clock cycles (ish)
// returns the LED# that was on when button pressed
uint8_t led_game(uint32_t interval)
{
  // initialize as off
  for (iii=0; iii<NUM_LEDS; iii++)
  {
    digitalWrite(LED[iii], LOW); 
  }
  
  while (1)
  {
    // scroll one way
    for (iii=0; iii<NUM_LEDS; iii++)
    {
      if (iii) {digitalWrite(LED[iii-1], LOW);}
      digitalWrite(LED[iii], HIGH);
      Serial.println(LED[iii]);
      for (jjj=0; jjj<interval; jjj++)
      {
        if (!digitalRead(buttonPin)) {return iii;} // return LED#
        //_delay_us(100);
      }
    }
    digitalWrite(LED[NUM_LEDS-1], LOW); // remove?
    // scroll the other way
    for (iii=1; iii<NUM_LEDS-1; iii++)
    {
      if (iii<NUM_LEDS-1) {digitalWrite(LED[NUM_LEDS-iii], LOW);}
      digitalWrite(LED[NUM_LEDS-iii-1], HIGH);
      Serial.println(LED[NUM_LEDS-iii-1]);
      for (jjj=0; jjj<interval; jjj++)
      {
        if (!digitalRead(buttonPin)) {return iii;} // return LED#
        //_delay_us(100);
      }
    }
    digitalWrite(LED[1], LOW); //remove?
  }
}

void success_flash(void)
{
    for (iii=0; iii<NUM_LEDS; iii++)
    { digitalWrite(LED[iii], HIGH); }
    delay(500);
    for (iii=0; iii<NUM_LEDS; iii++)
    { digitalWrite(LED[iii], LOW); }
    delay(500);
    for (iii=0; iii<NUM_LEDS; iii++)
    { digitalWrite(LED[iii], HIGH); }
    delay(500);
    for (iii=0; iii<NUM_LEDS; iii++)
    { digitalWrite(LED[iii], LOW); }
    delay(500);
}

void loop() {

  // flash all if in green
  uint8_t LED_pressed = led_game(start_interval);
  
  if (LED_pressed==3 || LED_pressed == 4) // green
  {
    success_flash();
    bool win = 1;
    while (win)
    {
      current_interval *= 0.75;
      LED_pressed = led_game(current_interval);
      if (LED_pressed==3 || LED_pressed == 4) {win=1;}
      else {win=0;}
      if (win) {success_flash();}
    }
    current_interval = start_interval;
  } 
}
