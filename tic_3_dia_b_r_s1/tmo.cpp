void manu()
{
   if ()
   {

   }
const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), onEvent, CHANGE);
  Serial.println(F("Système intialisé"));
}

void loop() {
  digitalWrite(ledPin, state);
}

void onEvent() {
  state = !state;
  Serial.print(F("Switch LED 13 : "));
  if(state){
    Serial.println(F("ON"));
  }else{
    Serial.println(F("OFF"));
  }
}
