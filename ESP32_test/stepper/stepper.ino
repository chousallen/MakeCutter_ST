#define DIR_PIN 4
#define STEP_PIN 5
#define MS_PIN_1 32
#define MS_PIN_2 33
#define MS_PIN_3 25
#define DELAY 1 //Each step will consume DELAY*2 milliseconds
#define STEPS 3200 //one revolution if sixteenth precision

void setup() 
{
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(MS_PIN_1, OUTPUT);
  pinMode(MS_PIN_2, OUTPUT);
  pinMode(MS_PIN_3, OUTPUT); 
  digitalWrite(MS_PIN_1, HIGH);
  digitalWrite(MS_PIN_2, HIGH);
  digitalWrite(MS_PIN_3, HIGH); //Let MS1, MS2, MS3 HIGH to sixteenth precise
  digitalWrite(DIR_PIN, HIGH); //DIR HIGH: counter clock wise
  digitalWrite(STEP_PIN, LOW);

}

void loop() {
  
  for (int i=0; i<STEPS; i++)
  {
    digitalWrite(STEP_PIN, HIGH);
    delay(DELAY);
    digitalWrite(STEP_PIN, LOW);
    delay(DELAY);
  }
  delay(2000);

}
