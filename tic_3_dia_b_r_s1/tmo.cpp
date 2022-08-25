void manu()
{
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
}

//					FINI A REMETTRE
void cyl_def_source()
{
		if (welc_ctr_err == true)
		{
			switch_def = ct3t_posi_st[8];
		}
		else
		{
			switch_def = ct1t_posi_st[8];
		}
		switch (switch_def) //(sosNbr == 2_61_3_61_4_72)
		{
		case 0:
		def_3t(3);
			break;
		case 1:
				def_3t(61);
			break;
		case 2:
		def_2t(2);
			break;
		case 3:
				def_3t(71);
			break;
		case 4:
				def_1t(1);
			break;
		case 5:
				def_3t(62);
			break;
		case 6:
				for (int i = 0; i < 9; i++)
				{
					ct1t_posi_st[i] = false;
					ct2t_posi_st[i] = false;
					ct3t_posi_st[i] = false;
				}
			break;
		}

}

//					FINI A REMETTRE
int def_source(int sosSay)
{	
	int flache = 0;
	int siren_c_i = 0;
	if (sosSay == 2 || sosSay == 3)
	{
		flache = flacheBleu; // sortie 12
		siren_c_i = sirenC;	 // 3 sortie siren con (continute)
	}
	if (sosSay == 4 || sosSay == 5)
	{
		flache = flacheRouge; // 11 sortie flacheRouge
		siren_c_i = sirenI;		// 9 sortie siren iso
	}
	if (sosSay == 61)
	{
		sosSay=1;
		flache = spot;			// 11 sortie flacheRouge
		siren_c_i = sirenI; // 9 sortie siren iso
	}
	if (sosSay == 62)
	{
		sosSay=2;
		flache = spot;			// 11 sortie flacheRouge
		siren_c_i = sirenI; // 9 sortie siren iso
	}
	if (sosSay == 71)
	{
				sosSay=1;

		flache = spot;			// 11 sortie flacheRouge
		siren_c_i = sirenC; // 9 sortie siren iso
	}
	if (sosSay == 72)
	{
				sosSay=2;

		flache = spot;			// 11 sortie flacheRouge
		siren_c_i = sirenC; // 9 sortie siren iso
	}

	// cycle count_3t
	count_3t();
	for (int i = 0; i < 6; i++)
	{
		if (ct3t_posi_st[i] == true)
		{
			ct3t_switch = i;
		}
	}
	if (ct3t_posi_st[6] == true)
	{
		ct3t_posi_st[6] = false;
		ct3t_posi_st[7]++; // compteur cycle
		if (ct3t_posi_st[7] == sosSay)
		{
			ct3t_posi_st[8]++; // compteur
			ct3t_posi_st[7] = 0;
		}
	}

	switch (ct3t_switch)
	{
	case 0:
		digitalWrite(flache, true);
		digitalWrite(siren_c_i, true);
		break;
	case 1:
		digitalWrite(flache, true);
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
		digitalWrite(siren_c_i, false);
		break;
	case 5:
		digitalWrite(flache, false);
		digitalWrite(siren_c_i, false);
		break;
	case 6:
		ct3t_switch = 0;
		for (int i = 0; i < 9; i++)
		{
			ct1t_posi_st[i] = false;
			ct2t_posi_st[i] = false;
			ct3t_posi_st[i] = false;
		}

		ct3t_millis = millis();
		ct2t_millis = millis();
		ct1t_millis = millis();

		break;
	case 7:
		ct3t_switch = 0;
		break;
	}
	int CcPhNeTe_switch = ct3t_posi_st[8];
	return (CcPhNeTe_switch);
}





//					EN COURS

void veilleF(int alim_State, bool BPmarcheState, int batt)
{
	if (alim_State == 20 || BPmarcheState == false)
	{
		Serial.print("defaut 230v ");
		Serial.println("appuille BP");
		digitalWrite(alim, false);
		digitalWrite(flacheBleu, false);
		digitalWrite(sirenC, false);
		digitalWrite(sirenI, false);
		digitalWrite(flacheRouge, false);
		sosSay = 0; // code arret ecl & fane veilleF()
		sosTmp = 0;
		spot_cl(sosSay, sosTmp); // arret eclairage veille_F()
		fane(sosSay);						 // arret fan  veille_F()
		



    // boucle TEMPO
    while (BPmarcheState == false)
		{
			BPmarcheState = digitalRead(BPmarche);
			tempx = (millis() - temp1);
			if (tempx >= 5000)
			{
				veille_def=3;
				Serial.println("defaut alim appuille BP");
				temp1 = millis();
				sosSay = 3;
				sosTmp = 3;
				// f_b_cl(sosSay);
				// f_r_cl(sosSay);
				spot_cl(sosSay, sosTmp);
			}
		}

    // boucle 230v
		while (alim_State == 20)
		{
			veille_def=4;
			alim_State = controlAlimFonc();
			tempx = (millis() - temp1);
			if (tempx >= 5000)
			{
				Serial.println("defaut 230v appuille BP");
				temp1 = millis();
				sosSay = 3;
				sosTmp = 3;
				f_b_cl(sosSay);
				f_r_cl(sosSay);
				spot_cl(sosSay, sosTmp);
			}
		}
	}

  // boucle BOSCH
	while (batt <= 5)
	{
		veille_def=5;
		batt = getBattery(batt, battLow);
		tempx = (millis() - temp1);
		if (tempx >= 5000)
		{
			Serial.println("batt LOW appuille BP");
			temp1 = millis();
			sosSay = 3;							 // battLow 5%
			sosTmp = 3;							 // battLow 5%
			f_b_cl(sosSay);					 // battLow 5%
			f_r_cl(sosSay);					 // battLow 5%
			spot_cl(sosSay, sosTmp); // battLow 5%
		}
	}
	debut = millis();
}







int GEN_mode()
{
  debut_gen_inp = millis();
  debut_gen_cyl = millis();
  unsigned long rlt_gen_inp = millis() - debut_gen_inp;
  unsigned long rlt_gen_cyl = millis() - debut_gen_cyl;
  while (rlt_gen_cyl <= sec * 3)
  {
    rlt_gen_cyl = millis() - debut_gen_cyl;

    if (etalon[0][0] == 0 && etalon[0][1] == 0 && phase > 1 && rlt_gen_inp < 100)
    {
      debut_gen_inp = millis();
      etalon[0][0] = 1;
    }
    if (etalon[0][0] == 1 && etalon[0][1] == 0 && phase < 1 && rlt_gen_inp < 100)
    {
      debut_gen_inp = millis();
      etalon[0][1] = 1;
    }
    if (etalon[0][0] == 1 && etalon[0][1] == 1)
    {
      etalon[0][2]++;
    }

    if (etalon[0][2] == 1)
    {
      etalon[0][3] = etalon[0][2];
    }
    if (etalon[0][2] == 2)
    {
      etalon[0][3] = etalon[0][2];
    }

    if (etalon[0][2] == 3)
    {
      etalon[0][3] = etalon[0][2];
      for (int i = 0; i < 3; i++)
      {
        etalon[0][i] = 0;
      }
    }
    for (int i = 0; i < 4; i++)
    {
      etalon[0][i] = 0;
    }
  }
  if (etalon[0][3] == 3)
  {
    // GEN(); // active 230v pendent 15min
    break;
  }
  if (etalon[0][3] == 2)
  {
    GEN(); // active 230v pendent 15min
    break;
  }
  if (etalon[0][3] == 1)
  {
    // GEN();
    break;
  }
  debut_gen_inp = millis();
  debut_gen_cyl = millis();
}

void GEN()
{
  long gen_rlt = millis() - gen_debut;
  if (gen_rlt <= gen_tmp_230)
  {
    GEN_ste = true;
    digitalWrite(alim, true);
    digitalWrite(bosch, true);
		
    long rlt_3m=millis()-debut_3m;
    if (rlt_3m > minut * 3)
    {
      def_3t(60);
      def_3t(4);
      def_3t(2);
      if (ct3t_posi_st[7] == 2)
      {
        ct3t_posi_st[8]++; // compteur
        ct3t_posi_st[7] = 0;
        debut_3m = millis();
        for (int i = 0; i < 8; i++)
        {
          ct3t_posi_st[i] = false;
        }
      }
      // def_3t(4);
      // if (ct3t_posi_st[7] == 2)
      // {
      //   ct3t_posi_st[8]++; // compteur
      //   ct3t_posi_st[7] = 0;
      //   gen_debut = millis();
      //   for (int i = 0; i < 8; i++)
      //   {
      //     ct3t_posi_st[i] = false;
      //   }
      // }
      // def_3t(60);
      // if (ct3t_posi_st[7] == 2)
      // {
      //   ct3t_posi_st[8]++; // compteur
      //   ct3t_posi_st[7] = 0;
      //   // gen_debut = millis();
      //   for (int i = 0; i < 8; i++)
      //   {
      //     ct3t_posi_st[i] = false;
      //   }
      // }
      // def_1t(4);
      // if (ct1t_posi_st[7] == 2)
      // {
      //   ct1t_posi_st[8]++; // compteur
      //   ct1t_posi_st[7] = 0;
      //   gen_debut = millis();
      //   for (int i = 0; i < 8; i++)
      //   {
      //     ct1t_posi_st[i] = false;
      //   }
      // }
    }

    long rlt_1m=millis()-debut_1m;
    if (rlt_1m > minut)
    {
      def_3t(60);
      if (ct3t_posi_st[7] == 3)
      {
        ct3t_posi_st[8]++; // compteur
        ct3t_posi_st[7] = 0;
        debut_1m = millis();
        for (int i = 0; i < 8; i++)
        {
          ct3t_posi_st[i] = false;
        }
      }
      def_1t(4);
      if (ct1t_posi_st[7] == 2)
      {
        ct1t_posi_st[8]++; // compteur
        ct1t_posi_st[7] = 0;
        // debut_1m = millis();
        for (int i = 0; i < 8; i++)
        {
          ct1t_posi_st[i] = false;
        }
      }
    }
  }
  else
  {
    GEN_ste = false;
  }
}


