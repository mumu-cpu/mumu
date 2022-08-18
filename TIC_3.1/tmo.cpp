
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

int boutonPin  = 2 ;
int ledPin = 3 ;
int compteur = 0 ;

//  Pour qu'on puisse changer la valeur d'une variable depuis une fonction de
//  gestion d'interruption, il faut que la variable soit déclaré "volatile"

volatile boolean changed = false;



void setup() { 
  Serial.begin (9600);
  pinMode(boutonPin, INPUT);
  pinMode(ledPin,OUTPUT);
  // Attacher notre fonction ISR, detection de front descendant (5v vers 0v)
  attachInterrupt(0, doContact, FALLING);
} 

void loop() {
  if ( changed ) {
    changed = false;
    Serial.print("Ha ! Action sur le BP ");
    Serial.print(compteur);
    Serial.println(" fois");
    // on allume la LED pendant 1 seconde
    digitalWrite(ledPin,HIGH);
    delay(1000);
    digitalWrite(ledPin,LOW);
    }
  delay(5000);
}


void doContact() {
  changed = true;
  compteur++;
}

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



