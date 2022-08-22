
const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), onEvent, CHANGE);
  Serial.println(F("Système intialisé"));
}

void loop()
{

  int boutonPin = 2;
  int ledPin = 3;
  int compteur = 0;

  //  Pour qu'on puisse changer la valeur d'une variable depuis une fonction de
  //  gestion d'interruption, il faut que la variable soit déclaré "volatile"

  volatile boolean changed = false;

  void setup()
  {
    Serial.begin(9600);
    pinMode(boutonPin, INPUT);
    pinMode(ledPin, OUTPUT);
    // Attacher notre fonction ISR, detection de front descendant (5v vers 0v)
    attachInterrupt(0, doContact, FALLING);
  }

  void loop()
  {
    if (changed)
    {
      changed = false;
      Serial.print("Ha ! Action sur le BP ");
      Serial.print(compteur);
      Serial.println(" fois");
      // on allume la LED pendant 1 seconde
      digitalWrite(ledPin, HIGH);
      delay(1000);
      digitalWrite(ledPin, LOW);
    }
    delay(5000);
  }

  void doContact()
  {
    changed = true;
    compteur++;
  }

  digitalWrite(ledPin, state);
}

void onEvent()
{
  state = !state;
  Serial.print(F("Switch LED 13 : "));
  if (state)
  {
    Serial.println(F("ON"));
  }
  else
  {
    Serial.println(F("OFF"));
  }
}

unsigned long cpt1t_millis = millis();
int ct1t_state = 0;
int cpt_1t = 0; // compte cycle 2t
bool ct1t_sta0 = false;
bool ct1t_sta1 = false;
bool ct1t_sta2 = false;
bool ct1t_sta3 = false;
bool ct1t_sta4 = false;
bool ct1t_sta5 = false;
int cpt_1t_sta[8] = {false, false, false, false, false, false, false, false};

int count_1t(int ct1t_state)
{
  int ct1t_ste = ct1t_state;
  unsigned long rlt1t = millis() - cpt1t_millis;

  // cycle x1
  // allum 0
  if (rlt1t > 0 &&
      ct1t_sta0 == false &&
      ct1t_sta2 == false)
  {
    cpt1t_millis = millis();
    ct1t_ste = ct1t_ste + 1;
    ct1t_sta0 = true;
    cpt_1t_sta[0] = true;
    ct1t_sta2 = false;
  }
  // etein 1
  rlt1t = millis() - cpt1t_millis;
  if (rlt1t > 10 &&
      ct1t_sta0 == true &&
      ct1t_sta1 == false)
  {
    cpt1t_millis = millis();
    ct1t_ste = ct1t_ste + 1;
    cpt_1t_sta[0] = false;
    cpt_1t_sta[1] = true;
    ct1t_sta1 = true;
  }
  /*
    // cycle x2
    // allum 2
    rlt1t = millis() - cpt1t_millis;
    if (rlt1t > 10 &&
        ct1t_sta0 == true &&
        ct1t_sta1 == true &&
        ct1t_sta2 == false)
    {
      cpt1t_millis = millis();
      ct1t_ste = ct1t_ste + 1;
      cpt_1t_sta[1] = false;
      cpt_1t_sta[2] = true;
      ct1t_sta2 = true;
    }
    // etein 3
    rlt1t = millis() - cpt1t_millis;
    if (rlt1t > 10 &&
        ct1t_sta0 == true &&
        ct1t_sta1 == true &&
        ct1t_sta2 == true &&
        ct1t_sta3 == false)
    {
      cpt1t_millis = millis();
      ct1t_ste = ct1t_ste + 1;
      cpt_1t_sta[2] = false;
      cpt_1t_sta[3] = true;
      ct1t_sta3 = true;
    }
    */
  /*
   // cycle x3
   // allum 4
   rlt1t = millis() - cpt1t_millis;
   if (rlt1t > 10 && ct1t_sta1 == true && ct1t_sta2 == true && ct1t_sta3 == true && ct1t_sta4 == false && ct1t_sta0 == true)
   {
     cpt1t_millis = millis();
     ct1t_ste = ct1t_ste + 1;
     cpt_1t_sta[3] = false;
     cpt_1t_sta[4] = true;
     ct1t_sta4 = true;
   }
   // etein 5
   rlt1t = millis() - cpt1t_millis;
   if (rlt1t > 10 &&
   ct1t_sta1 == true &&
   ct1t_sta2 == true &&
   ct1t_sta3 == true &&
   ct1t_sta4 == true &&
   ct1t_sta5 == false &&
   ct1t_sta0 == true)
   {
     cpt1t_millis = millis();
     ct1t_ste = ct1t_ste + 1;
     ct1t_sta5 = true;
     cpt_1t_sta[4] = false;
     cpt_1t_sta[5] = true;
   }
   */
  // fin cycle maz
  rlt1t = millis() - cpt1t_millis;
  if (rlt1t > 10 &&
      ct1t_sta0 == true &&
      ct1t_sta1 == true &&)
  // ct1t_sta2 == true &&
  // ct1t_sta3 == true &&
  // ct1t_sta4 == true &&
  // ct1t_sta5 == true
  {
    cpt1t_millis = millis();
    ct1t_ste = ct1t_ste + 1;
    ct1t_sta0 = false;
    ct1t_sta1 = false;
    // ct1t_sta2 = false;
    // ct1t_sta3 = false;
    // ct1t_sta4 = false;
    // ct1t_sta5 = false;
    cpt_1t_sta[1] = false;
    cpt_1t_sta[2] = true;
  }
  return (ct1t_ste);
}

int def_1t(int sosSay, int cpt_1t)
{
  // cycle count_1t
  int ct1t_ste;
  count_1t(ct1t_state);
  if (cpt_1t_sta[0] == true)
  {
    ct1t_ste = 0;
  }
  if (cpt_1t_sta[1] == true)
  {
    ct1t_ste = 1;
  }
  if (cpt_1t_sta[2] == true)
  {
    ct1t_ste = 2;
    cpt_1t_sta[2] = false;
    cpt_1t_sta[7]++;
  }
  /*
    if (cpt_1t_sta[3] == true)
    {
      ct1t_ste = 3;
    }
    if (cpt_1t_sta[4] == true)
    {
      ct1t_ste = 4;
    cpt_1t_sta[4] = false;
      cpt_1t_sta[7]++;
    }
  */
  /*
    if (cpt_1t_sta[5] == true)
    {
      ct1t_ste = 5;
    }
    if (cpt_1t_sta[6] == true)
    {
      ct1t_ste = 6;
      cpt_1t_sta[6] = false;
      // cpt_1t_sta[6]=false;
      // cpt_1t++;
      cpt_1t_sta[7]++;
    }
  */
  int flache = 0;
  int siren_c_i = 0;
  if (sosSay == 2 || sosSay == 3)
  {
    flache = flacheBleu; // sortie 12
    siren_c_i = sirenC;  // 3 sortie siren con (continute)
  }

  if (sosSay == 4 || sosSay == 5)
  {
    flache = flacheRouge; // 11 sortie flacheRouge
    siren_c_i = sirenI;   // 9 sortie siren iso
  }

  // return(ct1t_ste);

  switch (ct1t_ste)
  {
  case 0:
    digitalWrite(siren_c_i, true);
    break;
  case 1:
    digitalWrite(siren_c_i, false);
    break;
  case 2:
    ct1t_ste = 0;
    // digitalWrite(flache, true);
    break;
  case 3:
    ct1t_ste = 0;
    // digitalWrite(flache, false);
    break;
  case 4:
    ct1t_ste = 0;
    // digitalWrite(siren_c_i, true);
    break;
  case 5:
    ct1t_ste = 0;
    // digitalWrite(siren_c_i, false);
    break;
  case 6:
    ct1t_ste = 0;
    break;
  case 7:
    ct1t_ste = 0;
    break;
  }

  return (cpt_1t_sta[7]);
}


int count_1t(int ct3t_state)
{
  int ct3t_ste = ct3t_state;
  unsigned long rlt3t = millis() - cpt3t_millis;

  // cycle x1
  // allum 0
  if (rlt3t > 0 && ct3t_sta5 == false && ct3t_sta0 == false)
  {
    cpt3t_millis = millis();
    ct3t_ste = ct3t_ste + 1;
    ct3t_sta0 = true;
    cpt_3t_sta[0] = true;
    ct3t_sta5 = false;
  }
  // etein 1
  rlt3t = millis() - cpt3t_millis;
  if (rlt3t > 10 && ct3t_sta1 == false && ct3t_sta0 == true)
  {
    cpt3t_millis = millis();
    ct3t_ste = ct3t_ste + 1;
    cpt_3t_sta[0] = false;
    cpt_3t_sta[1] = true;
    ct3t_sta1 = true;
  }

  // cycle x2
  // allum 2
  rlt3t = millis() - cpt3t_millis;
  if (rlt3t > 10 && ct3t_sta1 == true && ct3t_sta2 == false && ct3t_sta0 == true)
  {
    cpt3t_millis = millis();
    ct3t_ste = ct3t_ste + 1;
    cpt_3t_sta[1] = false;
    cpt_3t_sta[2] = true;
    ct3t_sta2 = true;
  }
  // etein 3
  rlt3t = millis() - cpt3t_millis;
  if (rlt3t > 10 && ct3t_sta1 == true && ct3t_sta2 == true && ct3t_sta3 == false && ct3t_sta0 == true)
  {
    cpt3t_millis = millis();
    ct3t_ste = ct3t_ste + 1;
    cpt_3t_sta[2] = false;
    cpt_3t_sta[3] = true;
    ct3t_sta3 = true;
  }
  // cycle x3
  // allum 4
  rlt3t = millis() - cpt3t_millis;
  if (rlt3t > 10 && ct3t_sta1 == true && ct3t_sta2 == true && ct3t_sta3 == true && ct3t_sta4 == false && ct3t_sta0 == true)
  {
    cpt3t_millis = millis();
    ct3t_ste = ct3t_ste + 1;
    cpt_3t_sta[3] = false;
    cpt_3t_sta[4] = true;
    ct3t_sta4 = true;
  }
  // etein 5
  rlt3t = millis() - cpt3t_millis;
  if (rlt3t > 10 && ct3t_sta1 == true && ct3t_sta2 == true && ct3t_sta3 == true && ct3t_sta4 == true && ct3t_sta5 == false && ct3t_sta0 == true)
  {
    cpt3t_millis = millis();
    ct3t_ste = ct3t_ste + 1;
    ct3t_sta5 = true;
    cpt_3t_sta[4] = false;
    cpt_3t_sta[5] = true;
  }
  // fin cycle maz
  rlt3t = millis() - cpt3t_millis;
  if (rlt3t > 10 && ct3t_sta0 == true && ct3t_sta1 == true && ct3t_sta2 == true && ct3t_sta3 == true && ct3t_sta4 == true && ct3t_sta5 == true)
  {
    cpt3t_millis = millis();
    ct3t_ste = ct3t_ste + 1;
    ct3t_sta0 = false;
    ct3t_sta1 = false;
    ct3t_sta2 = false;
    ct3t_sta3 = false;
    ct3t_sta4 = false;
    ct3t_sta5 = false;
    cpt_3t_sta[5] = false;
    cpt_3t_sta[6] = true;
  }
  return (ct3t_ste);
}

int def_3t(int sosSay)
{
  // cycle count_2t
  int ct3t_ste;
  count_3t(ct3t_state);
  if (cpt_3t_sta[0] == true)
  {
    ct3t_ste = 0;
  }
  if (cpt_3t_sta[1] == true)
  {
    ct3t_ste = 1;
  }
  if (cpt_3t_sta[2] == true)
  {
    ct3t_ste = 2;
  }
  if (cpt_3t_sta[3] == true)
  {
    ct3t_ste = 3;
  }
  if (cpt_3t_sta[4] == true)
  {
    ct3t_ste = 4;
  }
  if (cpt_3t_sta[5] == true)
  {
    ct3t_ste = 5;
  }
  if (cpt_3t_sta[6] == true)
  {
    ct3t_ste = 6;
    cpt_3t_sta[6] = false;
    cpt_3t_sta[7]++;
    if (cpt_3t_sta[7] == sosSay)
    {
      cpt_3t_sta[8]++;
    }
  }

  int flache = 0;
  int siren_c_i = 0;
  if (sosSay == 2 || sosSay == 3)
  {
    flache = flacheBleu; // sortie 12
    siren_c_i = sirenC;  // 3 sortie siren con (continute)
  }

  if (sosSay == 4 || sosSay == 5)
  {
    flache = flacheRouge; // 11 sortie flacheRouge
    siren_c_i = sirenI;   // 9 sortie siren iso
  }
  if (sosSay == 6)
  {
    flache = spot;      // 11 sortie flacheRouge
    siren_c_i = sirenI; // 9 sortie siren iso
  }
  if (sosSay == 7)
  {
    flache = spot;      // 11 sortie flacheRouge
    siren_c_i = sirenC; // 9 sortie siren iso
  }

  // return(ct3t_ste);

  switch (ct3t_ste)
  {
  case 0:
    digitalWrite(flache, true);
    digitalWrite(siren_c_i, true);
    break;
  case 1:
    digitalWrite(flache, false);
    digitalWrite(siren_c_i, false);
    break;
  case 2:
    digitalWrite(siren_c_i, true);
    digitalWrite(flache, true);
    break;
  case 3:
    digitalWrite(siren_c_i, false);
    digitalWrite(flache, false);
    break;
  case 4:
    digitalWrite(flache, true);
    digitalWrite(siren_c_i, true);
    break;
  case 5:
    digitalWrite(flache, false);
    digitalWrite(siren_c_i, false);
    break;
  case 6:
    ct3t_ste = 0;
    break;
  case 7:
    ct3t_ste = 0;
    break;
  }

  return (cpt_3t_sta[8]);
}









int count_1t()
{
  unsigned long rlt3t = millis() - cpt3t_millis;

  // cycle x1
  // allum 0
  if (rlt3t > 0 && 
      ct3t_sta[0] == false && 
      ct3t_sta[5] == false)
  {
    cpt3t_millis = millis();
    cpt_3t_sta[0] = true;
    ct3t_sta[0] = true;
    ct3t_sta[5] = false;
  }
  // etein 1
  rlt3t = millis() - cpt3t_millis;
  if (rlt3t > 10 && 
      ct3t_sta[0] ==  true && 
      ct3t_sta[1] == false)
  {
    cpt3t_millis = millis();
    cpt_3t_sta[0] = false;
    cpt_3t_sta[1] = true;
    ct3t_sta[1] = true;
  }

  // cycle x2
  // allum 2
  rlt3t = millis() - cpt3t_millis;
  if (rlt3t > 10 && 
      ct3t_sta[0] == true && 
      ct3t_sta[1] == true && 
      ct3t_sta[2] == false
      )
  {
     cpt3t_millis = millis();
    cpt_3t_sta[1] = false;
    cpt_3t_sta[2] = true;
      ct3t_sta[2] = true;
  }
  // etein 3
  rlt3t = millis() - cpt3t_millis;
  if (rlt3t > 10 && 
      ct3t_sta[0] == true && 
      ct3t_sta[1] == true && 
      ct3t_sta[2] == true && 
      ct3t_sta[3] == false
      )
  {
     cpt3t_millis = millis();
    cpt_3t_sta[2] = false;
    cpt_3t_sta[3] = true;
      ct3t_sta[3] = true;
  }
  // cycle x3
  // allum 4
  rlt3t = millis() - cpt3t_millis;
  if (rlt3t > 10 && 
      ct3t_sta[0] == true && 
      ct3t_sta[1] == true && 
      ct3t_sta[2] == true && 
      ct3t_sta[3] == true && 
      ct3t_sta[4] == false)
  {
    cpt3t_millis = millis();
    cpt_3t_sta[3] = false;
    cpt_3t_sta[4] = true;
    ct3t_sta[4] = true;
  }
  // etein 5
  rlt3t = millis() - cpt3t_millis;
  if (rlt3t > 10 && 
      ct3t_sta[0] == true && 
      ct3t_sta[1] == true && 
      ct3t_sta[2] == true && 
      ct3t_sta[3] == true && 
      ct3t_sta[4] == true && 
      ct3t_sta[5] == false
      )
  {
    cpt3t_millis = millis();
    cpt_3t_sta[4] = false;
    cpt_3t_sta[5] = true;
      ct3t_sta[5] = true;
}
  // fin cycle maz
  rlt3t = millis() - cpt3t_millis;
  if (rlt3t > 10 && 
      ct3t_sta[0] == true && 
      ct3t_sta[1] == true && 
      ct3t_sta[2] == true && 
      ct3t_sta[3] == true && 
      ct3t_sta[4] == true && 
      ct3t_sta[5] == true)
  {
    cpt3t_millis = millis();
    for (int i = 0; i < 6; i++)
    {
    ct3t_sta[i] = false;
    }
    
    cpt_3t_sta[5] = false;
    cpt_3t_sta[6] = true;
  }
  //return (ct3t_switch);
}

int def_3t(int sosSay)
{
  // cycle count_2t
  // int ct3t_switch;
  count_1t();
  for (int i = 0; i < 6; i++)
  {
   if (cpt_3t_sta[i] == true)
  {
    ct3t_switch = i;
  } 
  }
if (cpt_3t_sta[6] == true)
  {
    cpt_3t_sta[6] = false;
    cpt_3t_sta[7]++;// compteur cycle
    if (cpt_3t_sta[7] == sosSay)
    {
      cpt_3t_sta[8]++;// compteur 
    }
  }

  int flache = 0;
  int siren_c_i = 0;
  if (sosSay == 2 || sosSay == 3)
  {
    flache = flacheBleu; // sortie 12
    siren_c_i = sirenC;  // 3 sortie siren con (continute)
  }

  if (sosSay == 4 || sosSay == 5)
  {
    flache = flacheRouge; // 11 sortie flacheRouge
    siren_c_i = sirenI;   // 9 sortie siren iso
  }
  if (sosSay == 6)
  {
    flache = spot;      // 11 sortie flacheRouge
    siren_c_i = sirenI; // 9 sortie siren iso
  }
  if (sosSay == 7)
  {
    flache = spot;      // 11 sortie flacheRouge
    siren_c_i = sirenC; // 9 sortie siren iso
  }

  // return(ct3t_switch);

  switch (ct3t_switch)
  {
  case 0:
    digitalWrite(flache, true);
    digitalWrite(siren_c_i, true);
    break;
  case 1:
    digitalWrite(flache, false);
    digitalWrite(siren_c_i, false);
    break;
  case 2:
    digitalWrite(siren_c_i, true);
    digitalWrite(flache, true);
    break;
  case 3:
    digitalWrite(siren_c_i, false);
    digitalWrite(flache, false);
    break;
  case 4:
    digitalWrite(flache, true);
    digitalWrite(siren_c_i, true);
    break;
  case 5:
    digitalWrite(flache, false);
    digitalWrite(siren_c_i, false);
    break;
  case 6:
    ct3t_switch = 0;
    int cpt_3t_sta[9] = {false, false, false, false, false, false, false, false, false};
    int cpt_2t_sta[9] = {false, false, false, false, false, false, false, false, false};
    int cpt_1t_sta[9] = {false, false, false, false, false, false, false, false, false};
        cpt3t_millis = millis();
        cpt2t_millis = millis();
        cpt1t_millis = millis();

    break;
  case 7:
    ct3t_switch = 0;
    break;
  }
int CcPhNeTe_switch=cpt_3t_sta[8];
  return (CcPhNeTe_switch);
}

