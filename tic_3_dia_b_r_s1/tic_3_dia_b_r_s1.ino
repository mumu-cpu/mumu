const int testPh = A0;     // entree analog phase
const int testN = A1;      // entree analog neutre
const int testT = A2;      // entree analog terre
const int BATTERYPIN = A3; // pin de la batterie
const int photo = A4;      // cellule photo
const int temrat = A5;     // cellule temperature
const int BPmarche = 2;    // entree bp_marche
const int alimOk = 4;      // entree control 230v OK
const int welc_ctr_in = 2; // 8;  // entree control diagnostique

int flacheRouge = 11; // sortie flacheRouge
int flacheBleu = 12;  // sortie flacheBleu
int sirenC = 3;       // sortie siren con (continute)
int sirenI = 9;       // sortie siren iso
int spot = 6;         // eclairage
int alim = 10;        // sortie_Alim
int fan = 5;          // ventilateur
int bosch = 13;       // sortie batterie

int phase = 0;            // state phase
int neutre = 0;           // state neutre
int terre = 0;            // state terre
int seuil_pot = 10;       // seuil_pot detection
int seuil_lux = 30;       // seuil_lux
int seuil_term = 30;      // seuil_term
int sosNbr = 1;           // code on_off_cl
unsigned long sosTmp = 1; // tempt cliososNbr40 x1000
int sosSay = 1;           //
int CcPhNeTe = 0;         // CcPhNeTe
int CcPhNeTe_prew = 0;
int cmpB = 0;
bool battLow = false; // battLow
int batt = 0;         // batt
int eclr = 0;
int fanee = 0;
const float TensionMin = 10.5; // tension min
const float TensionMax = 20.0; // tension max
bool BPmarcheState = false;    // state bp_marche
bool Manu_auto = false;        // state auto_manu
bool spotState = false;
bool flacheRougeState = false;     // state flache_rouge
bool flacheBleuState = false;      // state flache_rouge
bool sirenCState = false;          // state sirenC
bool sirenIState = false;          // state sirenI
int alim_State = 0;                // state alim_State
bool tempo_State_On = false;       // cycle on
unsigned long tempo = (2000 * 10); // temp duree cycle
unsigned long debut = millis();    // temp debut duree cycle
unsigned long interval = 1000;     // interval cligniot
unsigned long inter = 1;
unsigned long chro = 0;                 // temp ccphnete
unsigned long chroi = 0;                // temp bat low
unsigned long curmill = millis();       // temp ccphnt
unsigned long tempi = 2000;             // temp ccphnt
unsigned long temp1 = 0;                // temp memo depannage terrePhaseNeutre
unsigned long temp2 = 0;                // temp memo depannage terrePhaseNeutre
unsigned long tempx = 1000;             // temp duree delay affiche defaut alim
unsigned long currentMillis = millis(); // stocke la valeur courante de la fonction millis()
int ct_state = 0;

//                GEN
long minut = 60000;
long sec = 1000;
long gen_debut = 0;
long gen_tmp_230 = 15 * minut;
bool GEN_ste = false;
long debut_3m = 0;
long debut_1m = 0;
int ct1s_state = 0;
bool ct1s_sta = false;
bool ct1s_sta1 = false;

bool maz_int = false;
int ccphnete_0_st = 0;
int ccphnete0 = 0;
int veille_def_st = 0;
int veille_def = 0;

unsigned long ct1t_millis = millis();
bool ct1t_cycl_st[6] = {false, false, false, false, false, false};
int ct1t_posi_st[9] = {false, false, false, false, false, false, false, false, false};
int ct1t_switch;
unsigned long ct2t_millis = millis();
bool ct2t_cycl_st[6] = {false, false, false, false, false, false};
int ct2t_posi_st[9] = {false, false, false, false, false, false, false, false, false};
int ct2t_switch;
unsigned long ct3t_millis = millis();
bool ct3t_cycl_st[6] = {false, false, false, false, false, false};
int ct3t_posi_st[9] = {false, false, false, false, false, false, false, false, false};
int ct3t_switch;

int ct05s_state = 0;
bool ct05s_sta = false;
bool ct05s_sta1 = false;

bool welc_ctr_err = false;
String rouge = "flache	ROUGE"; // welc_ID_index  0
String bleu = "flache	BLEU";    // welc_ID_index  1
String con = "siren	CONT";      // welc_ID_index  2
String iso = "siren	ISO";       // welc_ID_index  3
String spt = "ecl	SPOT";        // welc_ID_index  4
String alm = "alim	230v";      // welc_ID_index  5
String fn = "vent	FAN";         // welc_ID_index  6
String bch = "bat	BOSCH";       // welc_ID_index  7

bool welc_ctr_tb_st[8] = {false, false, false, false, false, false, false, false};
String welc_ctr_tb_id[8] = {rouge, bleu, con, iso, spt, alm, fn, bch};

int etalon[3][4] = {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0};

unsigned long cpt_millis = millis();
unsigned long cpt1s_millis = millis();

unsigned long cpt05s_millis = millis();
bool f_b_cl_state = false;
unsigned long f_b_cl_Tmp = 0;
unsigned long f_b_cl_Say = 0;
bool f_r_cl_state = false;
unsigned long f_r_cl_Tmp = 0;
unsigned long f_r_cl_Say = 0;
bool spot_cl_state = false;
unsigned long spot_cl_Tmp = 0;
unsigned long spot_cl_Say = 0;
bool s_c_cl_state = false;
unsigned long s_c_cl_Tmp = 0;
bool s_i_cl_state = false;
unsigned long s_i_cl_Tmp = 0;
int cp_cl = 1;            // int declaration
volatile int compteB = 0; // init declaration
int compteR = 0;
int comptesC = 1;
int comptesI = 1;
int compte30B = 0;
int compte30R = 0;
int comptespot = 1;
int compte30spot = 0;
int compte30sI = 1;
int compte30sC = 1;
unsigned long millisSc_BR_CLon = 0;
unsigned long millisSi_BR_CLon = 0;
unsigned long millisF_B_CL_5 = 0;
void setup()
{ //                              SETUP
  Serial.begin(115200);
  Serial.println("      A U T O     D I A G N O S T I C"); //
  Serial.println("     ");                                 //
  pinMode(flacheRouge, OUTPUT);
  pinMode(flacheBleu, OUTPUT);
  pinMode(sirenC, OUTPUT);
  pinMode(sirenI, OUTPUT);
  pinMode(spot, OUTPUT);
  pinMode(alim, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(bosch, OUTPUT);

  pinMode(alimOk, INPUT_PULLUP);
  pinMode(BPmarche, INPUT_PULLUP);
  pinMode(welc_ctr_in, INPUT_PULLUP);

  //  **********************TEST********************************
  //                      A REMETTRE
  // welc diagnostique
  // for (int compt = ct1s_state; ct1s_state <= 18; compt)
  //{    ct1s_state = welc_1s(ct1s_state);  }
  //                      A REMETTRE

  // welc listing ID err

  //  **********************TEST********************************
  //
  // 					              roge, bleu, sirC, sirI,	spot,	alime, fanne,	bsch
  bool welc_ctr_tb_st[8] = {false, false, false, false, false, false, false, false};
  //
  //  **********************TEST********************************

  if (welc_ctr_tb_st[0] == false && welc_ctr_tb_st[1] == false && welc_ctr_tb_st[2] == false && welc_ctr_tb_st[3] == false && welc_ctr_tb_st[4] == false && welc_ctr_tb_st[5] == false && welc_ctr_tb_st[6] == false && welc_ctr_tb_st[7] == false)
  {
    Serial.println("    S Y S T E M    O K");
    welc_ctr_err = false;
    // welc listing ID 0k
    for (int i = 0; i < 8; i++)
    {
      if (welc_ctr_tb_st[i] == false)
      {
        Serial.print(welc_ctr_tb_id[i]);
        Serial.println("	RAS	0.k."); //
      }
    }
  }
  else
  {
    Serial.println("	");                                         //
    Serial.println("    S Y S T E M    A U T O     C O N F I G"); //
    welc_ctr_err = true;
  }

  //      A U T O     C O N F I G

  // flacheRouge ->defaut ==>flacheBleu
  if (welc_ctr_tb_st[0] == true) // && welc_ctr_tb_st[1] == false)
  {
    Serial.print(welc_ctr_tb_id[0]);
    Serial.println("	DEFAUT	0.f.");
    if (welc_ctr_tb_st[1] == false)
    {
      flacheRouge = flacheBleu;
      Serial.println("	Rouge => Bleu");
    } // defaut flacheRouge --> flacheBleu
  }
  // flacheBleu ->defaut ==> flacheRouge
  if (welc_ctr_tb_st[1] == true) // && welc_ctr_tb_st[1] == false)
  {
    Serial.print(welc_ctr_tb_id[1]);
    Serial.println("	DEFAUT	0.f.");
    if (welc_ctr_tb_st[0] == false)
    {
      flacheBleu = flacheRouge;
      Serial.println("	Bleu => Rouge");
    } // defaut flacheBleu --> flacheRouge
  }
  // sirenC ->defaut ==> sirenI
  if (welc_ctr_tb_st[2] == true) // && welc_ctr_tb_st[1] == false)
  {
    Serial.print(welc_ctr_tb_id[2]);
    Serial.println("	DEFAUT	0.f.");
    if (welc_ctr_tb_st[3] == false)
    {
      sirenC = sirenI;
      Serial.println("	sirenC => SirenI");
    } // defaut sirenC --> sirenI
  }
  // sirenI ->defaut ==> sirenC
  if (welc_ctr_tb_st[3] == true) // && welc_ctr_tb_st[1] == false)
  {
    Serial.print(welc_ctr_tb_id[3]);
    Serial.println("	DEFAUT	0.f.");
    if (welc_ctr_tb_st[2] == false)
    {
      sirenI = sirenC;
      Serial.println("	SirenI => sirenC");
    } // defaut sirenI --> sirenC
  }
  // flacheRouge -> flacgeBleu ==> spot
  if (welc_ctr_tb_st[0] == true && welc_ctr_tb_st[1] == true)
  {
    if (welc_ctr_tb_st[4] == false)
    {
      flacheRouge = spot;
      flacheBleu = spot;
      Serial.println("	Rouge = Bleu => spot");
    } // defaut flacheRouge --> flacheBleu ==> spot
    else
    {
      if (welc_ctr_tb_st[2] == false)
      {
        flacheRouge = sirenC;
        flacheBleu = sirenC;
        Serial.println("	Rouge = Bleu => sirenC");
      } // defaut flacheRouge --> flacheBleu = spot ==> sirenC
      else
      {
        if (welc_ctr_tb_st[3] == false)
        {
          flacheRouge = sirenI;
          flacheBleu = sirenI;
          Serial.println("	Rouge = Bleu => sirenI");
        } // defaut flacheRouge --> flacheBleu = spot ==> sirenI
      }
    }
  }
  // sirenC -> sirenI ==> spot
  if (welc_ctr_tb_st[2] == true && welc_ctr_tb_st[3] == true)
  {
    if (welc_ctr_tb_st[4] == false)
    {
      sirenC = spot;
      sirenI = spot;
      Serial.println("	sirenC = sirenI => spot");
    } // defaut sirenC --> sirenI ==> spot
    else
    {
      if (welc_ctr_tb_st[0] == false)
      {
        sirenC = flacheRouge;
        sirenI = flacheRouge;
        Serial.println("	sirenC = sirenI => rouge");
      } // defaut flacheRouge --> flacheBleu = spot ==> sirenC
      else
      {
        if (welc_ctr_tb_st[1] == false)
        {
          sirenC = flacheBleu;
          sirenI = flacheBleu;
          Serial.println("	sirenC = sirenI => bleu");
        } // defaut flacheRouge --> flacheBleu = spot ==> sirenI
      }
    }
  }
  if (welc_ctr_tb_st[6] == true)
  {
    Serial.print(welc_ctr_tb_id[6]);
    Serial.println("	DEFAUT	0.f.  ! HS");
    fan = 0;
  } // defaut fan --> hs
  if (welc_ctr_tb_st[4] == true)
  {
    Serial.print(welc_ctr_tb_id[4]);
    Serial.println("	DEFAUT	0.f.  ! HS");
    spot = 0;
  } // defaut spot --> hs
  // flacheRouge -> flacheBleu -> spot -> con -> iso ==> DEFAUT
  if (welc_ctr_tb_st[0] == true &&
      welc_ctr_tb_st[1] == true &&
      welc_ctr_tb_st[2] == true &&
      welc_ctr_tb_st[3] == true &&
      welc_ctr_tb_st[4] == true)
  {
    Serial.println("	DEFAUT GENERAL ! viSon");
    while (1)
      ;
  }
  // alim 230v ==> DEFAUT
  if (welc_ctr_tb_st[5] == true)
  {
    Serial.println("	DEFAUT GENERAL ! 230v");
    while (1)
      ;
  }
  // bat BOSCH ==> DEFAUT
  if (welc_ctr_tb_st[7] == true)
  {
    Serial.println("	DEFAUT GENERAL ! BOSCH");
    while (1)
      ;
  }
  debut = millis(); // temp debut duree cycle
}
void loop()
{ //                               LOOP
  demare();
  CcPhNeTe = test();

  //  **********************RESET********************************

  if (veille_def_st != veille_def)
  {
    veille_def_st = veille_def;
    maz_int = false;
  }

  if (CcPhNeTe_prew != CcPhNeTe)
  {
    CcPhNeTe_prew = CcPhNeTe;
    maz_int = false;
  }

  if (ccphnete_0_st != ccphnete0)
  {
    ccphnete_0_st = ccphnete0;
    maz_int = false;
  }

  if (CcPhNeTe > 0)
  {
    debut = millis();
  }

  maz_int_f();

  //  **********************TEST********************************
  for (int i = 0; i < 9; i++)
  {
    Serial.print(ct1t_posi_st[i]);
  }
  for (int i = 0; i < 9; i++)
  {
    Serial.print(ct2t_posi_st[i]);
  }
  for (int i = 0; i < 9; i++)
  {
    Serial.print(ct3t_posi_st[i]);
  }
  //  **********************TEST********************************

  int switch_def;
  switch (CcPhNeTe)
  {
  case 1: // Ne <-> Te
    Serial.print("Ne <-> Te ");
    Serial.println(CcPhNeTe);
    // sosNbr34();
    if (welc_ctr_err == true)
    {
      switch_def = ct3t_posi_st[8];
    }
    else
    {
      switch_def = ct1t_posi_st[8];
    }
    switch (switch_def) //(sosNbr == 3_61_4_72)
    {
    case 0:
      if (welc_ctr_err == true)
      {
        def_3t(3);
      }
      else
      {
        def_1t(3);
      }
      break;
    case 1:
      if (welc_ctr_err == true)
      {
        def_3t(61);
      }
      else
      {
        def_1t(61);
      }
      break;
    case 2:
      if (welc_ctr_err == true)
      {
        def_3t(4);
      }
      else
      {
        def_1t(4);
      }
      break;
    case 3:
      if (welc_ctr_err == true)
      {
        def_3t(72);
      }
      else
      {
        def_1t(72);
      }
      break;
    case 4:
      if (welc_ctr_err == true)
      {
        for (int i = 0; i < 9; i++)
        {
          ct1t_posi_st[i] = false;
          ct2t_posi_st[i] = false;
          ct3t_posi_st[i] = false;
        }
      }
      else
      {
        for (int i = 0; i < 9; i++)
        {
          ct1t_posi_st[i] = false;
          ct2t_posi_st[i] = false;
          ct3t_posi_st[i] = false;
        }
      }
      break;
    }
    break;

  case 2: // Ph <-> Te
    Serial.print("Ph <-> Te ");
    Serial.println(CcPhNeTe);
    // sosNbr24();
    if (welc_ctr_err == true)
    {
      switch_def = ct3t_posi_st[8];
    }
    else
    {
      switch_def = ct1t_posi_st[8];
    }
    switch (switch_def) //(sosNbr == 2_61_4_72)
    {
    case 0:
      if (welc_ctr_err == true)
      {
        def_3t(2);
      }
      else
      {
        def_1t(2);
      }
      break;
    case 1:
      if (welc_ctr_err == true)
      {
        def_3t(61);
      }
      else
      {
        def_1t(61);
      }
      break;
    case 2:
      if (welc_ctr_err == true)
      {
        def_3t(4);
      }
      else
      {
        def_1t(4);
      }
      break;
    case 3:
      if (welc_ctr_err == true)
      {
        def_3t(72);
      }
      else
      {
        def_1t(72);
      }
      break;
    case 4:
      if (welc_ctr_err == true)
      {
        for (int i = 0; i < 9; i++)
        {
          ct1t_posi_st[i] = false;
          ct2t_posi_st[i] = false;
          ct3t_posi_st[i] = false;
        }
      }
      else
      {
        for (int i = 0; i < 9; i++)
        {
          ct1t_posi_st[i] = false;
          ct2t_posi_st[i] = false;
          ct3t_posi_st[i] = false;
        }
      }
      break;
    }
    break;

  case 3: // Ph <-> Ne
    Serial.print("Ph <-> Ne ");
    Serial.println(CcPhNeTe);
    if (welc_ctr_err == true)
    {
      switch_def = ct3t_posi_st[8];
    }
    else
    {
      switch_def = ct1t_posi_st[8];
    }
    switch (switch_def) //(sosNbr == 2_61_3_62)
    {
    case 0:
      if (welc_ctr_err == true)
      {
        def_3t(2);
      }
      else
      {
        def_1t(2);
      }
      break;
    case 1:
      if (welc_ctr_err == true)
      {
        def_3t(61);
      }
      else
      {
        def_1t(61);
      }
      break;
    case 2:
      if (welc_ctr_err == true)
      {
        def_3t(3);
      }
      else
      {
        def_1t(3);
      }
      break;
    case 3:
      if (welc_ctr_err == true)
      {
        def_3t(62);
      }
      else
      {
        def_1t(62);
      }
      break;
    case 4:
      if (welc_ctr_err == true)
      {
        for (int i = 0; i < 9; i++)
        {
          ct1t_posi_st[i] = false;
          ct2t_posi_st[i] = false;
          ct3t_posi_st[i] = false;
        }
      }
      else
      {
        for (int i = 0; i < 9; i++)
        {
          ct1t_posi_st[i] = false;
          ct2t_posi_st[i] = false;
          ct3t_posi_st[i] = false;
        }
      }
      break;
    }
    break;

  case 4: // Cc-Ph-Ne-Te. test
    Serial.print("Cc-Ph-Ne-Te. test ");
    Serial.println(CcPhNeTe);
    // sosNbr234();
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
      if (welc_ctr_err == true)
      {
        def_3t(2);
      }
      else
      {
        def_1t(2);
      }
      break;
    case 1:
      if (welc_ctr_err == true)
      {
        def_3t(61);
      }
      else
      {
        def_1t(61);
      }
      break;
    case 2:
      if (welc_ctr_err == true)
      {
        def_3t(3);
      }
      else
      {
        def_1t(3);
      }
      break;
    case 3:
      if (welc_ctr_err == true)
      {
        def_3t(61);
      }
      else
      {
        def_1t(61);
      }
      break;
    case 4:
      if (welc_ctr_err == true)
      {
        def_3t(4);
      }
      else
      {
        def_1t(4);
      }
      break;
    case 5:
      if (welc_ctr_err == true)
      {
        def_3t(72);
      }
      else
      {
        def_1t(72);
      }
      break;
    case 6:
      if (welc_ctr_err == true)
      {
        for (int i = 0; i < 9; i++)
        {
          ct1t_posi_st[i] = false;
          ct2t_posi_st[i] = false;
          ct3t_posi_st[i] = false;
        }
      }
      else
      {
        for (int i = 0; i < 9; i++)
        {
          ct1t_posi_st[i] = false;
          ct2t_posi_st[i] = false;
          ct3t_posi_st[i] = false;
        }
      }
      break;
    }
    break;

  case 5: // Cc_Ph_Ne_Te. cuci
    Serial.print("Cc_Ph_Ne_Te. cuci");
    Serial.println(CcPhNeTe);
    // sosNbr55();
    if (welc_ctr_err == true)
    {
      switch_def = ct3t_posi_st[8];
    }
    else
    {
      switch_def = ct1t_posi_st[8];
    }
    switch (switch_def) //(sosNbr == 5_71_5_72)
    {
    case 0:
      if (welc_ctr_err == true)
      {
        def_3t(5);
      }
      else
      {
        def_1t(5);
      }
      break;
    case 1:
      if (welc_ctr_err == true)
      {
        def_3t(71);
      }
      else
      {
        def_1t(71);
      }
      break;
    case 2:
      if (welc_ctr_err == true)
      {
        def_3t(5);
      }
      else
      {
        def_1t(5);
      }
      break;
    case 3:
      if (welc_ctr_err == true)
      {
        def_3t(72);
      }
      else
      {
        def_1t(72);
      }
      break;
    case 4:
      if (welc_ctr_err == true)
      {
        for (int i = 0; i < 9; i++)
        {
          ct1t_posi_st[i] = false;
          ct2t_posi_st[i] = false;
          ct3t_posi_st[i] = false;
        }
      }
      else
      {
        for (int i = 0; i < 9; i++)
        {
          ct1t_posi_st[i] = false;
          ct2t_posi_st[i] = false;
          ct3t_posi_st[i] = false;
        }
      }
      break;
    }
    break;

  default:
    unsigned long rlt_int = millis() - temp1;
    //		if (ccphnete_0_st != ccphnete0)
    //		{
    //			ccphnete_0_st = ccphnete0;
    //			maz_int = false;
    //		}
    if ((alim_State == 10 || alim_State == 30) && battLow == false && CcPhNeTe == false)
    {
      ccphnete0 = 1;
      // pause cl x2
      if (rlt_int > 1000 * 3)
      {
        if (welc_ctr_err == true)
        {
          def_3t(2);
          if (ct3t_posi_st[7] == 2)
          {
            ct3t_posi_st[8]++; // compteur
            ct3t_posi_st[7] = 0;
            temp1 = millis();
            for (int i = 0; i < 8; i++)
            {
              ct3t_posi_st[i] = false;
            }
          }
        }
        else
        {
          def_1t(2);
          if (ct1t_posi_st[7] == 2)
          {
            ct1t_posi_st[8]++; // compteur
            ct1t_posi_st[7] = 0;
            temp1 = millis();
            for (int i = 0; i < 8; i++)
            {
              ct1t_posi_st[i] = false;
            }
          }
        }
      }
    }
    if (CcPhNeTe == 0 && battLow == true)
    {
      ccphnete0 = 2;
      // pause cl x2
      unsigned long rlt_int = millis() - temp1;
      if (rlt_int > 1000 * 3)
      {
        if (welc_ctr_err == true)
        {
          def_3t(2);
          def_2t(4);
          def_1t(61);
          if (ct3t_posi_st[7] == 2)
          {
            ct3t_posi_st[8]++; // compteur
            ct3t_posi_st[7] = 0;
            temp1 = millis();
            for (int i = 0; i < 8; i++)
            {
              ct3t_posi_st[i] = false;
              ct2t_posi_st[i] = false;
              ct1t_posi_st[i] = false;
            }
          }
        }
        else
        {
          def_1t(2);
          def_2t(4);
          def_3t(72);
          if (ct1t_posi_st[7] == 2)
          {
            ct1t_posi_st[8]++; // compteur
            ct1t_posi_st[7] = 0;
            temp1 = millis();
            for (int i = 0; i < 8; i++)
            {
              ct1t_posi_st[i] = false;
              ct2t_posi_st[i] = false;
              ct3t_posi_st[i] = false;
            }
          }
        }
      }
    }
    if (rlt_int > 1000 * 50)
    {
      ccphnete0 = 3;
      if (welc_ctr_err == true)
      {
        def_3t(62);
        if (ct3t_posi_st[7] == 2)
        {
          ct3t_posi_st[8]++; // compteur
          ct3t_posi_st[7] = 0;
          temp1 = millis();
          for (int i = 0; i < 8; i++)
          {
            ct3t_posi_st[i] = false;
          }
        }
      }
      else
      {
        def_1t(62);
        if (ct1t_posi_st[7] == 2)
        {
          ct1t_posi_st[8]++; // compteur
          ct1t_posi_st[7] = 0;
          temp1 = millis();
          for (int i = 0; i < 8; i++)
          {
            ct1t_posi_st[i] = false;
          }
        }
      }
    }

    compteB = 0; // CcPhNeTe == 0
    cp_cl = 1;
    comptespot = 1;
    chro = millis();
    break;
  }
  //  **********************TEST**********************
}
//                                   FIN LOOP
//                                   FONCTION

int GEN_mode()
{
  temp1 = millis();
  temp2 = millis();
  unsigned long rlt_int = millis() - temp1;
  unsigned long rlt_inp = millis() - temp2;
  while (rlt_inp <= sec * 3)
  {
    rlt_inp = millis() - temp2;
    if (etalon[0][0] == 0 && etalon[0][1] == 0 && phase > 1 && temp1 - millis() < 100)
    {
      temp1 = millis();
      etalon[0][0] = 1;
    }
    if (etalon[0][0] == 1 && etalon[0][1] == 0 && phase < 1 && temp1 - millis() < 100)
    {
      temp1 = millis();
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
  temp1 = millis();
  temp2 = millis();
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
    if (rlt_int > minut * 3)
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

    if (rlt_int > minut)
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

void demare()
{
  //            MANU_AUTO_VEILLE
  // si BPmarcheState (off)  on
  BPmarcheState = digitalRead(BPmarche);
  Manu_auto = !BPmarcheState;
  // si tempo_State_On (off)  on
  if ((millis() - debut) <= tempo && Manu_auto == false)
  {
    tempo_State_On = true;
    long tempCycle = tempo - (millis() - debut);
    Serial.print("temp cylce restant : ");
    tempCycle = tempCycle / 1000;
    Serial.print(tempCycle);
    Serial.println(" s.");
  }
  else
  {
    tempo_State_On = false;
  }
  if (Manu_auto == true)
  {
    if (tempx >= 100 || tempx < 5)
    {
      Serial.println("Manu  on");
      if (tempx >= 100)
      {
        temp1 = millis();
      }
    }
  }
  if ((Manu_auto == false) && (tempo_State_On == false))
  {
    veilleFonc(tempo_State_On, BPmarcheState, battLow, batt);
  }

  // **********************DEBUT**********************

  batt = getBattery(batt, battLow);
  const float voltt = (batt * (TensionMax - TensionMin));
  const float volty = (voltt / 100);
  const float volt = (volty + TensionMin);
  if (batt <= 20)
  {
    Serial.print(volt);
    Serial.print("v !");
    battLow = true;
    Serial.println(" !!! bat BOSCH LOW !!! ");
  }
  else
  {
    Serial.print("bat BOSCH : ");
    Serial.print(batt);
    Serial.print("%_");
    Serial.print(volt);
    Serial.println("v");
    battLow = false;
  }
  if (batt <= 1)
  {
    battOffFonc();
  }
  alim_State = controlAlimFonc();
  if (alim_State == 20)
  {
    alimOffFonc();
  }
}
void maz_int_f()
{
  // mise a zer0
  if (maz_int == false)
  {
    maz_int = true;
    digitalWrite(flacheRouge, false);
    digitalWrite(flacheBleu, false);
    digitalWrite(sirenC, false);
    digitalWrite(sirenI, false);
    digitalWrite(spot, false);
    digitalWrite(alim, false);
    digitalWrite(fan, false);
    digitalWrite(bosch, false);
    for (int i = 0; i < 9; i++)
    {
      ct1t_posi_st[i] = false;
      ct2t_posi_st[i] = false;
      ct3t_posi_st[i] = false;
    }

    ct1t_millis = millis();
    ct2t_millis = millis();
    ct3t_millis = millis();
    // chro = millis();
  }
}
void ecl_auto(int sosSay)
{
  eclr = analogRead(photo);
  if (sosSay == 0)
  { // arret ecl_Auto()
    digitalWrite(spot, false);
    Serial.println("eclairage off");
  }
  if (sosSay == 1)
  { // active ecl_Auto()
    if (eclr >= seuil_lux)
    {
      digitalWrite(spot, true);
      Serial.println("eclairage on_auto");
    }
    else
    {
      digitalWrite(spot, false);
      Serial.println("eclairage off_auto");
    }
  }
}
void fane(int sosSay)
{
  fanee = analogRead(temrat);
  if (sosSay == 0)
  { // arret fane()
    digitalWrite(fan, false);
    Serial.println("ventilateur off");
  }
  if (sosSay == 1)
  { // auto fane()
    if (fanee >= seuil_term)
    {
      digitalWrite(fan, true);
      Serial.println("ventilateur on_auto");
    }
    else
    {
      digitalWrite(fan, false);
      Serial.println("ventilateur off_auto");
    }
  }
}
int phaseF()
{
  int phase = analogRead(testPh);

  return (phase);
}
int neutreF()
{
  neutre = analogRead(testN);
  return (neutre);
}
int terreF()
{
  terre = analogRead(testT);
  return (terre);
}
int test()
{

  // sosNbr = 234;    // Ph Ne Te
  // sosNbr = 23;     // Ph Ne
  // sosNbr = 34;   	// Ne Te
  // sosNbr = 42;   	// Ph Te
  // sosNbr = 55;     //

  phase = phaseF();
  neutre = neutreF();
  terre = terreF();
  if (phase >= seuil_pot)
  {
    phase = true;
  }
  if (neutre >= seuil_pot)
  {
    neutre = true;
  }
  if (terre >= seuil_pot)
  {
    terre = true;
  }
  if (phase == true && neutre == true && terre == true)
  {
    if (curmill - chro >= tempi)
    {
      CcPhNeTe = 5; // sosNbr55()
    }
    else
    {
      CcPhNeTe = 4; // sosNbr234()
    }
  }
  if (phase == true && neutre == true && terre == false)
  {
    CcPhNeTe = 3; // sosNbr23()
  }
  if (phase == true && neutre == false && terre == true)
  {
    CcPhNeTe = 2; // sosNbr24()
  }
  if (phase == false && neutre == true && terre == true)
  {
    CcPhNeTe = 1; // sosNbr34()
  }
  if ((phase == false && neutre == false && terre == false) || (phase == true && neutre == false && terre == false) || (phase == false && neutre == true && terre == false) || (phase == false && neutre == false && terre == true))
  {
    CcPhNeTe = 0; // sosNbr10()
  }
  return (CcPhNeTe);
}
/**************FONCTION****spot_cl*/
int spot_cl(int sosSay, unsigned long sosTmp)
{
  unsigned long mil = millis() - spot_cl_Say;
  unsigned long tp = 1000 * sosTmp;
  int say10 = sosSay;
  sosTmp = sosSay;
  if (say10 == 10)
  {
    sosSay = 2;
  }
  if (sosSay == 0)
  { // || f_b_cl_state == false || f_r_cl_state == false) { // arret spot
    sosTmp = 1;
    digitalWrite(spot, false); // modifie l'état de la LED
  }
  if (mil < tp)
  {
    spot_cl_state = false;
    if (compte30spot < sosSay)
    {
      if (spotState == LOW)
      {
        if ((millis() - spot_cl_Tmp) >= 200)
        {
          spotState = HIGH; // change the state of LED
          spot_cl_Tmp = millis();
          if (say10 == 0)
          {
            digitalWrite(spot, false); // modifie l'état de la LED
            Serial.println("eclairage off");
          }
          else
          {
            if (say10 == 10)
            {
              digitalWrite(spot, false); // modifie l'état de la LED
              Serial.println("eclairage off");
            }
            else
            {
              digitalWrite(spot, spotState); // remember Current millis() time
            }
          }
        }
      }
      else
      {
        if ((millis() - spot_cl_Tmp) >= 600)
        {
          compte30spot = compte30spot + 1;
          spotState = LOW; // change the state of LED
          spot_cl_Tmp = millis();
          if (say10 == 10)
          {
            eclr = analogRead(photo);
            if (eclr >= seuil_lux)
            {
              digitalWrite(spot, true);
              Serial.println("eclairage on_auto");
            }
            else
            {
              digitalWrite(spot, false); // modifie l'état de la LED
              Serial.println("eclairage off_auto");
            }
          }
          else
          {
            if (sosSay == 0)             // || f_b_cl_state == false || f_r_cl_state == false)
            {                            // arret spot
              digitalWrite(spot, false); // modifie l'état de la LED
            }
            else
            {
              digitalWrite(spot, spotState);
            }
          }
        }
      }
      if (compte30spot == sosSay)
      {
        spot_cl_state = true;
      }
    }
  }
  else
  {
    spot_cl_Say = millis(); // mémorise la valeur de la fonction millis()
    spot_cl_Tmp = millis();
    // cp_cl = cp_cl + 1; // spot_cl
    // comptespot = comptespot + 1;

    if (f_b_cl_state == true || f_r_cl_state == true)
    {
    }
    else
    {
    }
    if (compte30spot == sosSay)
    {
      compte30spot = 0;
      compteB = compteB + 1;
      ct_state = 0;
      cpt_millis = millis();
    }
  }
  return compteB;
}
/**************FONCTION****spot_cl****final*/

/*              COMPTEUR 1t_2t_3t               */
int count_1t()
{
  unsigned long ct1t_resu = millis() - ct1t_millis;

  // cycle x1
  // allum 0
  if (ct1t_resu > 0 &&
      ct1t_cycl_st[0] == false &&
      ct1t_cycl_st[5] == false)
  {
    ct1t_millis = millis();
    ct1t_posi_st[0] = true;
    ct1t_cycl_st[0] = true;
    ct1t_cycl_st[5] = false;
  }
  // etein 1
  ct1t_resu = millis() - ct1t_millis;
  if (ct1t_resu > 500 &&
      ct1t_cycl_st[0] == true &&
      ct1t_cycl_st[1] == false)
  {
    ct1t_millis = millis();
    ct1t_posi_st[0] = false;
    ct1t_posi_st[1] = true;
    ct1t_cycl_st[1] = true;
  }

  // cycle x2
  // allum 2
  ct1t_resu = millis() - ct1t_millis;
  if (ct1t_resu > 0 &&
      ct1t_cycl_st[0] == true &&
      ct1t_cycl_st[1] == true &&
      ct1t_cycl_st[2] == false)
  {
    ct1t_millis = millis();
    ct1t_posi_st[1] = false;
    ct1t_posi_st[2] = true;
    ct1t_cycl_st[2] = true;
  }
  // etein 3
  ct1t_resu = millis() - ct1t_millis;
  if (ct1t_resu > 0 &&
      ct1t_cycl_st[0] == true &&
      ct1t_cycl_st[1] == true &&
      ct1t_cycl_st[2] == true &&
      ct1t_cycl_st[3] == false)
  {
    ct1t_millis = millis();
    ct1t_posi_st[2] = false;
    ct1t_posi_st[3] = true;
    ct1t_cycl_st[3] = true;
  }
  // cycle x3
  // allum 4
  ct1t_resu = millis() - ct1t_millis;
  if (ct1t_resu > 0 &&
      ct1t_cycl_st[0] == true &&
      ct1t_cycl_st[1] == true &&
      ct1t_cycl_st[2] == true &&
      ct1t_cycl_st[3] == true &&
      ct1t_cycl_st[4] == false)
  {
    ct1t_millis = millis();
    ct1t_posi_st[3] = false;
    ct1t_posi_st[4] = true;
    ct1t_cycl_st[4] = true;
  }
  // etein 5
  ct1t_resu = millis() - ct1t_millis;
  if (ct1t_resu > 0 &&
      ct1t_cycl_st[0] == true &&
      ct1t_cycl_st[1] == true &&
      ct1t_cycl_st[2] == true &&
      ct1t_cycl_st[3] == true &&
      ct1t_cycl_st[4] == true &&
      ct1t_cycl_st[5] == false)
  {
    ct1t_millis = millis();
    ct1t_posi_st[4] = false;
    ct1t_posi_st[5] = true;
    ct1t_cycl_st[5] = true;
  }
  // fin cycle maz
  ct1t_resu = millis() - ct1t_millis;
  if (ct1t_resu > 400 &&
      ct1t_cycl_st[0] == true &&
      ct1t_cycl_st[1] == true &&
      ct1t_cycl_st[2] == true &&
      ct1t_cycl_st[3] == true &&
      ct1t_cycl_st[4] == true &&
      ct1t_cycl_st[5] == true)
  {
    ct1t_millis = millis();
    for (int i = 0; i < 6; i++)
    {
      ct1t_cycl_st[i] = false;
    }

    ct1t_posi_st[5] = false;
    ct1t_posi_st[6] = true;
  }
}
int def_1t(int sosSay)
{
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
  if (sosSay == 60)
  {
    sosSay = 2;
    flache = spot; // 11 sortie flacheRouge
    siren_c_i = false; // 9 sortie siren iso
  }
  if (sosSay == 61)
  {
    sosSay = 1;
    flache = spot;      // 11 sortie flacheRouge
    siren_c_i = sirenI; // 9 sortie siren iso
  }
  if (sosSay == 62)
  {
    sosSay = 2;
    flache = spot;      // 11 sortie flacheRouge
    siren_c_i = sirenI; // 9 sortie siren iso
  }
  if (sosSay == 71)
  {
    sosSay = 1;
    flache = spot;      // 11 sortie flacheRouge
    siren_c_i = sirenC; // 9 sortie siren iso
  }
  if (sosSay == 72)
  {
    sosSay = 2;
    flache = spot;      // 11 sortie flacheRouge
    siren_c_i = sirenC; // 9 sortie siren iso
  }
  if (sosSay == 81)
  {
    sosSay = 2;
    flache = false;      // 11 sortie flacheRouge
    siren_c_i = sirenC; // 9 sortie siren iso
  }
  if (sosSay == 82)
  {
    sosSay = 2;
    flache = false;      // 11 sortie flacheRouge
    siren_c_i = sirenI; // 9 sortie siren iso
  }

  // cycle count_1t
  count_1t();
  for (int i = 0; i < 6; i++)
  {
    if (ct1t_posi_st[i] == true)
    {
      ct1t_switch = i;
    }
  }
  if (ct1t_posi_st[6] == true)
  {
    ct1t_posi_st[6] = false;
    ct1t_posi_st[7]++; // compteur cycle
    if (ct1t_posi_st[7] == sosSay)
    {
      ct1t_posi_st[8]++; // compteur
    }
  }

  switch (ct1t_switch)
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
    ct1t_switch = 0;
    for (int i = 0; i < 9; i++)
    {
      ct1t_posi_st[i] = false;
      ct2t_posi_st[i] = false;
      ct3t_posi_st[i] = false;
    }

    ct1t_millis = millis();
    ct2t_millis = millis();
    ct3t_millis = millis();

    break;
  case 7:
    ct1t_switch = 0;
    break;
  }
  int CcPhNeTe_switch = ct1t_posi_st[8];
  return (CcPhNeTe_switch);
}
int count_2t()
{
  unsigned long ct2t_resu = millis() - ct2t_millis;

  // cycle x1
  // allum 0
  if (ct2t_resu > 0 &&
      ct2t_cycl_st[0] == false &&
      ct2t_cycl_st[5] == false)
  {
    ct2t_millis = millis();
    ct2t_posi_st[0] = true;
    ct2t_cycl_st[0] = true;
    ct2t_cycl_st[5] = false;
  }
  // etein 1
  ct2t_resu = millis() - ct2t_millis;
  if (ct2t_resu > 200 &&
      ct2t_cycl_st[0] == true &&
      ct2t_cycl_st[1] == false)
  {
    ct2t_millis = millis();
    ct2t_posi_st[0] = false;
    ct2t_posi_st[1] = true;
    ct2t_cycl_st[1] = true;
  }

  // cycle x2
  // allum 2
  ct2t_resu = millis() - ct2t_millis;
  if (ct2t_resu > 200 &&
      ct2t_cycl_st[0] == true &&
      ct2t_cycl_st[1] == true &&
      ct2t_cycl_st[2] == false)
  {
    ct2t_millis = millis();
    ct2t_posi_st[1] = false;
    ct2t_posi_st[2] = true;
    ct2t_cycl_st[2] = true;
  }
  // etein 3
  ct2t_resu = millis() - ct2t_millis;
  if (ct2t_resu > 500 &&
      ct2t_cycl_st[0] == true &&
      ct2t_cycl_st[1] == true &&
      ct2t_cycl_st[2] == true &&
      ct2t_cycl_st[3] == false)
  {
    ct2t_millis = millis();
    ct2t_posi_st[2] = false;
    ct2t_posi_st[3] = true;
    ct2t_cycl_st[3] = true;
  }
  // cycle x3
  // allum 4
  ct2t_resu = millis() - ct2t_millis;
  if (ct2t_resu > 0 &&
      ct2t_cycl_st[0] == true &&
      ct2t_cycl_st[1] == true &&
      ct2t_cycl_st[2] == true &&
      ct2t_cycl_st[3] == true &&
      ct2t_cycl_st[4] == false)
  {
    ct2t_millis = millis();
    ct2t_posi_st[3] = false;
    ct2t_posi_st[4] = true;
    ct2t_cycl_st[4] = true;
  }
  // etein 5
  ct2t_resu = millis() - ct2t_millis;
  if (ct2t_resu > 0 &&
      ct2t_cycl_st[0] == true &&
      ct2t_cycl_st[1] == true &&
      ct2t_cycl_st[2] == true &&
      ct2t_cycl_st[3] == true &&
      ct2t_cycl_st[4] == true &&
      ct2t_cycl_st[5] == false)
  {
    ct2t_millis = millis();
    ct2t_posi_st[4] = false;
    ct2t_posi_st[5] = true;
    ct2t_cycl_st[5] = true;
  }
  // fin cycle maz
  ct2t_resu = millis() - ct2t_millis;
  if (ct2t_resu > 400 &&
      ct2t_cycl_st[0] == true &&
      ct2t_cycl_st[1] == true &&
      ct2t_cycl_st[2] == true &&
      ct2t_cycl_st[3] == true &&
      ct2t_cycl_st[4] == true &&
      ct2t_cycl_st[5] == true)
  {
    ct2t_millis = millis();
    for (int i = 0; i < 6; i++)
    {
      ct2t_cycl_st[i] = false;
    }

    ct2t_posi_st[5] = false;
    ct2t_posi_st[6] = true;
  }
}
int def_2t(int sosSay)
{
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
  if (sosSay == 60)
  {
    sosSay = 2;
    flache = spot; // 11 sortie flacheRouge
    siren_c_i = false; // 9 sortie siren iso
  }
  if (sosSay == 61)
  {
    sosSay = 1;
    flache = spot;      // 11 sortie flacheRouge
    siren_c_i = sirenI; // 9 sortie siren iso
  }
  if (sosSay == 62)
  {
    sosSay = 2;
    flache = spot;      // 11 sortie flacheRouge
    siren_c_i = sirenI; // 9 sortie siren iso
  }
  if (sosSay == 71)
  {
    sosSay = 1;

    flache = spot;      // 11 sortie flacheRouge
    siren_c_i = sirenC; // 9 sortie siren iso
  }
  if (sosSay == 72)
  {
    sosSay = 2;

    flache = spot;      // 11 sortie flacheRouge
    siren_c_i = sirenC; // 9 sortie siren iso
  }
  if (sosSay == 81)
  {
    sosSay = 2;
    flache = false;      // 11 sortie flacheRouge
    siren_c_i = sirenC; // 9 sortie siren iso
  }
  if (sosSay == 82)
  {
    sosSay = 2;
    flache = false;      // 11 sortie flacheRouge
    siren_c_i = sirenI; // 9 sortie siren iso
  }

  // cycle count_2t
  count_2t();
  for (int i = 0; i < 6; i++)
  {
    if (ct2t_posi_st[i] == true)
    {
      ct2t_switch = i;
    }
  }
  if (ct2t_posi_st[6] == true)
  {
    ct2t_posi_st[6] = false;
    ct2t_posi_st[7]++; // compteur cycle
    if (ct2t_posi_st[7] == sosSay)
    {
      ct2t_posi_st[8]++; // compteur
    }
  }

  switch (ct2t_switch)
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
    ct2t_switch = 0;
    for (int i = 0; i < 9; i++)
    {
      ct1t_posi_st[i] = false;
      ct2t_posi_st[i] = false;
      ct3t_posi_st[i] = false;
    }

    ct1t_millis = millis();
    ct2t_millis = millis();
    ct3t_millis = millis();

    break;
  case 7:
    ct2t_switch = 0;
    break;
  }
  int CcPhNeTe_switch = ct2t_posi_st[8];
  return (CcPhNeTe_switch);
}
int count_3t()
{
  unsigned long ct3t_resu = millis() - ct3t_millis;

  // cycle x1
  // allum 0
  if (ct3t_resu > 0 &&
      ct3t_cycl_st[0] == false &&
      ct3t_cycl_st[5] == false)
  {
    ct3t_millis = millis();
    ct3t_posi_st[0] = true;
    ct3t_cycl_st[0] = true;
    ct3t_cycl_st[5] = false;
  }
  // etein 1
  ct3t_resu = millis() - ct3t_millis;
  if (ct3t_resu > 20 &&
      ct3t_cycl_st[0] == true &&
      ct3t_cycl_st[1] == false)
  {
    ct3t_millis = millis();
    ct3t_posi_st[0] = false;
    ct3t_posi_st[1] = true;
    ct3t_cycl_st[1] = true;
  }

  // cycle x2
  // allum 2
  ct3t_resu = millis() - ct3t_millis;
  if (ct3t_resu > 20 &&
      ct3t_cycl_st[0] == true &&
      ct3t_cycl_st[1] == true &&
      ct3t_cycl_st[2] == false)
  {
    ct3t_millis = millis();
    ct3t_posi_st[1] = false;
    ct3t_posi_st[2] = true;
    ct3t_cycl_st[2] = true;
  }
  // etein 3
  ct3t_resu = millis() - ct3t_millis;
  if (ct3t_resu > 50 &&
      ct3t_cycl_st[0] == true &&
      ct3t_cycl_st[1] == true &&
      ct3t_cycl_st[2] == true &&
      ct3t_cycl_st[3] == false)
  {
    ct3t_millis = millis();
    ct3t_posi_st[2] = false;
    ct3t_posi_st[3] = true;
    ct3t_cycl_st[3] = true;
  }
  // cycle x3
  // allum 4
  ct3t_resu = millis() - ct3t_millis;
  if (ct3t_resu > 20 &&
      ct3t_cycl_st[0] == true &&
      ct3t_cycl_st[1] == true &&
      ct3t_cycl_st[2] == true &&
      ct3t_cycl_st[3] == true &&
      ct3t_cycl_st[4] == false)
  {
    ct3t_millis = millis();
    ct3t_posi_st[3] = false;
    ct3t_posi_st[4] = true;
    ct3t_cycl_st[4] = true;
  }
  // etein 5
  ct3t_resu = millis() - ct3t_millis;
  if (ct3t_resu > 20 &&
      ct3t_cycl_st[0] == true &&
      ct3t_cycl_st[1] == true &&
      ct3t_cycl_st[2] == true &&
      ct3t_cycl_st[3] == true &&
      ct3t_cycl_st[4] == true &&
      ct3t_cycl_st[5] == false)
  {
    ct3t_millis = millis();
    ct3t_posi_st[4] = false;
    ct3t_posi_st[5] = true;
    ct3t_cycl_st[5] = true;
  }
  // fin cycle maz
  ct3t_resu = millis() - ct3t_millis;
  if (ct3t_resu > 40 &&
      ct3t_cycl_st[0] == true &&
      ct3t_cycl_st[1] == true &&
      ct3t_cycl_st[2] == true &&
      ct3t_cycl_st[3] == true &&
      ct3t_cycl_st[4] == true &&
      ct3t_cycl_st[5] == true)
  {
    ct3t_millis = millis();
    for (int i = 0; i < 6; i++)
    {
      ct3t_cycl_st[i] = false;
    }

    ct3t_posi_st[5] = false;
    ct3t_posi_st[6] = true;
  }
}
int def_3t(int sosSay)
{
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
  if (sosSay == 60)
  {
    sosSay = 2;
    flache = spot; // 11 sortie flacheRouge
    siren_c_i = false; // 9 sortie siren iso
  }
  if (sosSay == 61)
  {
    sosSay = 1;
    flache = spot;      // 11 sortie flacheRouge
    siren_c_i = sirenI; // 9 sortie siren iso
  }
  if (sosSay == 62)
  {
    sosSay = 2;
    flache = spot;      // 11 sortie flacheRouge
    siren_c_i = sirenI; // 9 sortie siren iso
  }
  if (sosSay == 71)
  {
    sosSay = 1;
    flache = spot;      // 11 sortie flacheRouge
    siren_c_i = sirenC; // 9 sortie siren iso
  }
  if (sosSay == 72)
  {
    sosSay = 2;
    flache = spot;      // 11 sortie flacheRouge
    siren_c_i = sirenC; // 9 sortie siren iso
  }
  if (sosSay == 81)
  {
    sosSay = 2;
    flache = false;      // 11 sortie flacheRouge
    siren_c_i = sirenC; // 9 sortie siren iso
  }
  if (sosSay == 82)
  {
    sosSay = 2;
    flache = false;      // 11 sortie flacheRouge
    siren_c_i = sirenI; // 9 sortie siren iso
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
/*              AUTO COFIG                     */
int welc_1s(int ct1s_state)
{
  int ct1s_ste = ct1s_state;
  unsigned long rlt1s = millis() - cpt1s_millis;
  if (rlt1s > 100 && ct1s_sta == false)
  {
    ct1s_sta = true;
    ct1s_ste = ct1s_ste + 1;
    cpt1s_millis = millis();
  }
  else
  {
  }
  rlt1s = millis() - cpt1s_millis;
  if (ct1s_sta == true && ct1s_sta1 == false && rlt1s > 100)
  {
    ct1s_sta1 = true;
    cpt1s_millis = millis();
    ct1s_ste = ct1s_ste + 1;
  }
  if (ct1s_sta == true && ct1s_sta1 == true)
  {
    ct1s_sta = false;
    ct1s_sta1 = false;
    cpt1s_millis = millis();
  }
  // Serial.print("ct1s_ste : ");
  //  Serial.println(ct1s_ste);
  switch (ct1s_ste)
  {

    // chiffre 1
  case 1:
    if (welc_ctr_tb_st[0] == false)
    {
      digitalWrite(flacheRouge, true);
    }
    if (digitalRead(welc_ctr_in) == false)
    {
      welc_ctr_tb_st[0] = true;
      ct05s_state = count05s(ct05s_state);
      switch (ct05s_state)
      {
      case 1:
        digitalWrite(flacheRouge, true);
        break;
      case 2:
        digitalWrite(flacheRouge, false);
        break;
      case 3:
        ct05s_state = 0;
        break;
      default:
        digitalWrite(flacheRouge, false);
        ct05s_state = 1;
        break;
      }
    }
    break;
  case 2:
    digitalWrite(flacheRouge, false);
    break;

    // chiffre 2
  case 3:
    if (welc_ctr_tb_st[1] == false)
    {
      digitalWrite(flacheBleu, true);
    }
    if (digitalRead(welc_ctr_in) == false)
    {
      welc_ctr_tb_st[1] = true;
      ct05s_state = count05s(ct05s_state);
      switch (ct05s_state)
      {
      case 1:
        digitalWrite(flacheBleu, true);
        break;
      case 2:
        digitalWrite(flacheBleu, false);
        break;
      case 3:
        ct05s_state = 0;
        break;
      default:
        digitalWrite(flacheBleu, false);
        ct05s_state = 1;
        break;
      }
    }
    break;
  case 4:
    digitalWrite(flacheBleu, false);
    break;

    // chiffre 3
  case 5:
    if (welc_ctr_tb_st[2] == false)
    {
      digitalWrite(sirenC, true);
    }
    if (digitalRead(welc_ctr_in) == false)
    {
      welc_ctr_tb_st[2] = true;
      ct05s_state = count05s(ct05s_state);
      switch (ct05s_state)
      {
      case 1:
        digitalWrite(sirenC, true);
        break;
      case 2:
        digitalWrite(sirenC, false);
        break;
      case 3:
        ct05s_state = 0;
        break;
      default:
        digitalWrite(sirenC, false);
        ct05s_state = 1;
        break;
      }
    }
    break;
  case 6:
    digitalWrite(sirenC, false);
    break;

    // chiffre 4
  case 7:
    if (welc_ctr_tb_st[3] == false)
    {
      digitalWrite(sirenI, true);
    }
    if (digitalRead(welc_ctr_in) == false)
    {
      welc_ctr_tb_st[3] = true;
      ct05s_state = count05s(ct05s_state);
      switch (ct05s_state)
      {
      case 1:
        digitalWrite(sirenI, true);
        break;
      case 2:
        digitalWrite(sirenI, false);
        break;
      case 3:
        ct05s_state = 0;
        break;
      default:
        digitalWrite(sirenI, false);
        ct05s_state = 1;
        break;
      }
    }
    break;
  case 8:
    digitalWrite(sirenI, false);
    break;

    // chiffre 5
  case 9:
    if (welc_ctr_tb_st[4] == false)
    {
      digitalWrite(spot, true);
    }
    if (digitalRead(welc_ctr_in) == false)
    {
      welc_ctr_tb_st[4] = true;
      ct05s_state = count05s(ct05s_state);
      switch (ct05s_state)
      {
      case 1:
        digitalWrite(spot, true);
        break;
      case 2:
        digitalWrite(spot, false);
        break;
      case 3:
        ct05s_state = 0;
        break;
      default:
        digitalWrite(spot, false);
        ct05s_state = 1;
        break;
      }
    }
    break;
  case 10:
    digitalWrite(spot, false);
    break;

  // chiffre 6
  case 11:
    if (welc_ctr_tb_st[5] == false)
    {
      digitalWrite(alim, true);
    }
    if (digitalRead(welc_ctr_in) == false)
    {
      welc_ctr_tb_st[5] = true;
      ct05s_state = count05s(ct05s_state);
      switch (ct05s_state)
      {
      case 1:
        digitalWrite(alim, true);
        break;
      case 2:
        digitalWrite(alim, false);
        break;
      case 3:
        ct05s_state = 0;
        break;

      default:
        digitalWrite(alim, false);
        ct05s_state = 1;
        break;
      }
    }
    break;
  case 12:
    digitalWrite(alim, false);
    break;

  // chiffre 7
  case 13:
    if (welc_ctr_tb_st[6] == false)
    {
      digitalWrite(fan, true);
    }
    if (digitalRead(welc_ctr_in) == false)
    {
      welc_ctr_tb_st[6] = true;
      ct05s_state = count05s(ct05s_state);
      switch (ct05s_state)
      {
      case 1:
        digitalWrite(fan, true);
        break;
      case 2:
        digitalWrite(fan, false);
        break;
      case 3:
        ct05s_state = 0;
        break;
      default:
        digitalWrite(fan, false);
        ct05s_state = 1;
        break;
      }
    }
    break;
  case 14:
    digitalWrite(fan, false);
    break;

  // chiffre 8
  case 15:
    if (welc_ctr_tb_st[7] == false)
    {
      digitalWrite(bosch, true);
    }
    if (digitalRead(BATTERYPIN) == false)
    {
      welc_ctr_tb_st[7] = true;
      ct05s_state = count05s(ct05s_state);
      switch (ct05s_state)
      {
      case 1:
        digitalWrite(bosch, true);
        break;
      case 2:
        digitalWrite(bosch, false);
        break;
      case 3:
        ct05s_state = 0;
        break;

      default:
        digitalWrite(bosch, false);
        ct05s_state = 1;
        break;
      }
    }
    break;
  case 16:
    digitalWrite(bosch, false);
    break;

  // chiffre 9
  case 17:
    digitalWrite(flacheRouge, false);
    digitalWrite(flacheBleu, false);
    digitalWrite(sirenC, false);
    digitalWrite(sirenI, false);
    digitalWrite(spot, false);
    digitalWrite(alim, false);
    digitalWrite(fan, false);
    digitalWrite(bosch, false);

    // digitalWrite(fan, true);
    break;
  case 18:
    // digitalWrite(fan, false);
    break;

  // chiffre 10
  case 19:
    digitalWrite(alim, true);
    break;
  case 20:
    digitalWrite(alim, false);
    break;

    // chiffre 11
  case 21:
    digitalWrite(spot, true);
    break;
  case 22:
    digitalWrite(spot, false);
    break;

    // chiffre 12
  case 23:
    digitalWrite(sirenI, true);
    break;
  case 24:
    digitalWrite(sirenI, false);
    break;

    // chiffre 13
  case 25:
    digitalWrite(sirenC, true);
    break;
  case 26:
    digitalWrite(sirenC, false);
    break;

    // chiffre 14
  case 27:
    digitalWrite(flacheBleu, true);
    break;
  case 28:
    digitalWrite(flacheBleu, false);
    break;

    // chiffre 15
  case 29:
    digitalWrite(flacheRouge, true);
    break;
  case 30:
    digitalWrite(flacheRouge, false);
    break;

  case 31:
    digitalWrite(flacheRouge, false);
    digitalWrite(flacheBleu, false);
    digitalWrite(sirenC, false);
    digitalWrite(sirenI, false);
    digitalWrite(spot, false);
    digitalWrite(alim, false);
    digitalWrite(fan, false);
    digitalWrite(bosch, false);
    break;

  // fin boucle
  case 32:
    // ct1s_ste = 0;
    break;
  case 33:
    digitalWrite(flacheRouge, false);
    digitalWrite(flacheBleu, false);
    digitalWrite(sirenC, false);
    digitalWrite(sirenI, false);
    digitalWrite(spot, false);
    digitalWrite(alim, false);
    digitalWrite(fan, false);
    digitalWrite(bosch, false);
    break;
  default:
    ct1s_ste = 1;
    digitalWrite(flacheRouge, false);
    digitalWrite(flacheBleu, false);
    digitalWrite(sirenC, false);
    digitalWrite(sirenI, false);
    digitalWrite(spot, false);
    digitalWrite(alim, false);
    digitalWrite(fan, false);
    digitalWrite(bosch, false);
    break;
  }
  ct1s_state = ct1s_ste;
  return ct1s_state;
}
int count(int ct_state, int compteB)
{
  unsigned long rlt = millis() - cpt_millis;
  if ((compteB == 1 || compteB == 0) && (ct_state > 2 && ct_state < 11))
  {
    cpt_millis = millis();
  }

  if (rlt > 0 && rlt < 600)
  {
    ct_state = 1;
  }
  if (rlt > 600 && rlt < 1000)
  {
    ct_state = 11;
    if (rlt > 950 && rlt < 1000)
    {
      ct_state = 2;
    }
  } // on_off x1

  if (rlt > 1050 && rlt < 1300)
  {
    ct_state = 3;
    if (rlt > 1250 && rlt < 1300)
    {
      ct_state = 3;
    }
  }
  if (rlt > 1300 && rlt < 1600)
  {
    ct_state = 11;
    if (rlt > 1550 && rlt < 1600)
    {
      ct_state = 4;
    }
  } // on_off x2
  if (rlt > 1650 && rlt < 2200)
  {
    ct_state = 5;
    if (rlt > 2150 && rlt < 2200)
    {
      ct_state = 5;
    }
  }
  if (rlt > 2200 && rlt < 2500)
  {
    ct_state = 11;
    if (rlt > 2450 && rlt < 2500)
    {
      ct_state = 6;
    }
  } // on_off x3
  if (rlt > 2550 && rlt < 3100)
  {
    ct_state = 7;
    if (rlt > 3050 && rlt < 3100)
    {
      ct_state = 7;
    }
  }
  if (rlt > 3150 && rlt < 3400)
  {
    ct_state = 11;
    if (rlt > 3350 && rlt < 3400)
    {
      ct_state = 8;
    }
  } // on_off x4
  if (rlt > 3450 && rlt < 4000)
  {
    ct_state = 9;
    if (rlt > 3950 && rlt < 4000)
    {
      ct_state = 9;
    }
  }
  if (rlt > 4050 && rlt < 4300)
  {
    ct_state = 11;
    if (rlt > 4250 && rlt < 4300)
    {
      ct_state = 10;
    }
  } // on_off x5
  if (rlt > 4350 && rlt < 4500)
  {
    ct_state = 0;
    cpt_millis = millis();
  }
  return (ct_state);
}
int count05s(int ct05s_state)
{
  int ct05s_ste = ct05s_state;
  unsigned long rlt05s;

  rlt05s = millis() - cpt05s_millis;
  if (rlt05s > 200 && ct05s_sta == false)
  {
    ct05s_sta = true;
    ct05s_ste = ct05s_ste + 1;
    cpt05s_millis = millis();
  }

  rlt05s = millis() - cpt05s_millis;
  if (rlt05s > 100 && ct05s_sta1 == false && ct05s_sta == true)
  {
    cpt05s_millis = millis();
    ct05s_ste = ct05s_ste + 1;
    ct05s_sta1 = true;
  }

  if (ct05s_sta == true && ct05s_sta1 == true)
  {
    ct05s_sta = false;
    ct05s_sta1 = false;
    cpt05s_millis = millis();
  }
  return (ct05s_ste);
}

int f_b_cl_2(int sosSay, int compteB)
{
  int flache = 0;
  int siren_c_i = 0;
  if (sosSay == 2 || sosSay == 3)
  {
    flache = flacheBleu; // sortie 12
    siren_c_i = sirenC;  // 3 sortie siren con (continute)
  }
  if (compteB == 2) //|| compteB == 4 || compteB == 6)
  {
    flache = spot;      // 6 eclairage
    siren_c_i = sirenI; // 9 sortie siren iso
  }
  if (compteB == 4 || compteB == 6)
  {
    flache = spot;
    siren_c_i = sirenC;
  }

  if (sosSay == 4 || sosSay == 5)
  {
    flache = flacheRouge; // 11 sortie flacheRouge
    siren_c_i = sirenI;   // 9 sortie siren iso
  }

  int cont_st = count(ct_state, compteB);
  switch (cont_st)
  {
  case 1:
  case 3:
  case 5:
  case 7:
  case 9:
    digitalWrite(siren_c_i, true);
    digitalWrite(flache, true);
    break;
  case 2:
    cmpB = 1;
    break;
  case 4:
    cmpB = 2;
    break;
  case 6:
    cmpB = 3;
    break;
  case 8:
    cmpB = 4;
    break;
  case 10:
    cmpB = 5;
    break;
  case 11:
    digitalWrite(siren_c_i, false);
    digitalWrite(flache, false);
    break;
  default:
    digitalWrite(siren_c_i, false);
    digitalWrite(flache, false);
    cmpB = 0;
    break;
  }

  if (sosSay == cmpB)
  {
    ct_state = 0; // on_off x5
    cpt_millis = millis();
    cmpB = 0;
    sosSay = compteB + 1;
    return (sosSay);
  }
  else
  {
    // if(compteB == 2||compteB == 4)

    return (compteB);
  }
  // return(cmpB);
}

int getBattery(int batt, bool battLow)
{
  float b = analogRead(BATTERYPIN);                  // valeur analogique
  float minValue = (1023 * TensionMin) / TensionMax; // Arduino
  float maxValue = (1023 * TensionMax) / TensionMax; // Arduino
  float moy = maxValue - minValue;
  float val = b - minValue;
  float res = val / moy;
  float pct = res * 100; // mettre en pourcentage
  int pctr = pct;
  if (pctr > 100)
  {
    pctr = 100;
  }
  if (pctr < 0)
  {
    pctr = 0;
  }
  if (pctr > 0)
  {
    if (pctr > 1 && pctr <= 20) // max is 20%
    {
      batt = 20;
      battLow = true;
      unsigned long curmil = millis();
      if (curmil - chroi >= 2000)
      {
        veille_def = 1;
        chroi = curmil;
        Serial.print("BOSCH 18V LOW ");
        Serial.print(pctr);
        Serial.print("% ");
        Serial.print("_|_|- ");
        const float voltt = (batt * (TensionMax - TensionMin));
        const float volty = (voltt / 100);
        const float volt = (volty + TensionMin);
        Serial.print(volt);
        Serial.println("V");
      }
    }
  }
  return (pctr);
}
int controlAlimFonc()
{
  digitalWrite(alim, true);            // 230v sous tention
  int alimState = digitalRead(alimOk); // control 230v sous tention
  if (alimState == false)
  {                                    // si entree actif
    Serial.println("TENTION 230V 0n"); // affiche 230v On
    sosNbr = 1;                        // code active fane  controlAlimFonc()
    fane(sosNbr);                      // active ventilateur controlAlimFonc()
    if (alim_State == 20)
    { // state alim 230v on off
      alim_State = 30;
    }
    else
    {
      alim_State = 10;
    }
    return (alim_State);
  }
  else
  {
    veille_def = 2;
    Serial.println("DEFAUT 230V 0ff"); // affiche 230v Off
    sosNbr = 0;                        // code arret fane controlAlimFonc()  off
    fane(sosNbr);                      // arret ventilateur controlAlimFonc()
    alim_State = 20;
    digitalWrite(alim, false); // arret 230v
    return (alim_State);
  }
}
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
    fane(sosSay);            // arret fan  veille_F()
    while (BPmarcheState == false)
    {
      BPmarcheState = digitalRead(BPmarche);
      tempx = (millis() - temp1);
      if (tempx >= 5000)
      {
        veille_def = 3;
        Serial.println("defaut alim appuille BP");
        temp1 = millis();
        sosSay = 3;
        sosTmp = 3;
        // f_b_cl(sosSay);
        // f_r_cl(sosSay);
        spot_cl(sosSay, sosTmp);
      }
    }
    while (alim_State == 20)
    {
      veille_def = 4;
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
  while (batt <= 5)
  {
    veille_def = 5;
    batt = getBattery(batt, battLow);
    tempx = (millis() - temp1);
    if (tempx >= 5000)
    {
      Serial.println("batt LOW appuille BP");
      temp1 = millis();
      sosSay = 3;              // battLow 5%
      sosTmp = 3;              // battLow 5%
      f_b_cl(sosSay);          // battLow 5%
      f_r_cl(sosSay);          // battLow 5%
      spot_cl(sosSay, sosTmp); // battLow 5%
    }
  }
  debut = millis();
}
void veilleFonc(bool tempo_State_On, bool BPmarcheState, bool battLow, int batt)
{
  batt = getBattery(batt, battLow);
  if (tempo_State_On == false && BPmarcheState == true)
  {
    Serial.println("veille appuille BP");
    digitalWrite(alim, false);
    digitalWrite(flacheBleu, false);
    digitalWrite(sirenC, false);
    digitalWrite(sirenI, false);
    digitalWrite(flacheRouge, false);
    sosSay = 0; //  code arret ecl & fane  veilleFon_c()
    sosTmp = 0;
    spot_cl(sosSay, sosTmp); //  arret ecl veilleFon_c()
    fane(sosSay);            //  arret fane veilleFon_c()
    while (BPmarcheState == true)
    {
      veille_def = 6;
      BPmarcheState = digitalRead(BPmarche);
      tempx = (millis() - temp1);
      if (tempx >= 3000)
      {
        Serial.println("veille appuille BP");
        temp1 = millis();
        sosSay = 3;
        sosTmp = 2;
        // f_b_cl(sosSay);
        // f_r_cl(sosSay);
        spot_cl(sosSay, sosTmp);
      }
    }
    debut = millis();
  }
  if (battLow == true)
  {
    Serial.print("DEFAUT  Batterie  ");
    Serial.print(batt);
    Serial.print("%_");
    const float voltt = (batt * (TensionMax - TensionMin));
    const float volty = (voltt / 100);
    const float volt = (volty + TensionMin);
    Serial.print(volt);
    Serial.print("V");
    Serial.println("Changer Batterie");
    digitalWrite(alim, false);
    digitalWrite(flacheBleu, false);
    digitalWrite(sirenC, false);
    digitalWrite(sirenI, false);
    digitalWrite(flacheRouge, false);
    digitalWrite(spot, false);
    digitalWrite(fan, false);
    while (BPmarcheState == true)
    {
      veille_def = 6;
      BPmarcheState = digitalRead(BPmarche);
      tempx = (millis() - temp1);
      if (tempx >= 2000)
      {
        Serial.println("changer Batterie  appuille BP");
        temp1 = millis();
      }
    }
  }
  debut = millis();
}
void alimOffFonc()
{
  digitalWrite(alim, true);
  int alimState = digitalRead(alimOk);
  while (alimState == true)
  {
    veille_def = 7;
    digitalWrite(alim, true);        // 230v sous tention
    alimState = digitalRead(alimOk); // control 230v sous tention
    if (alimState == true)
    { // si entree actif
      digitalWrite(alim, false);
      alim_State = 20;
      sosSay = 2;
      sosTmp = 2;
      f_b_cl(sosSay);
      sosSay = 3;
      sosTmp = 3;
      f_r_cl(sosSay);
      sosSay = 1;
      sosTmp = 1;
      spot_cl(sosSay, sosTmp);
    }
    else
    {
      digitalWrite(alim, true);
      alim_State = 30;
    }
  }
  if (cp_cl > 1)
  {
    cp_cl = 1; // alimOffFonc
    veilleF(alim_State, BPmarcheState, batt);
  }
  debut = millis();
}
void battOffFonc()
{
  int batState = getBattery(batt, battLow);
  sosSay = 0; // code arret ecl & fane battOffFonc()
  sosTmp = 0;
  spot_cl(sosSay, sosTmp); // arret ecl battOffFonc()
  fane(sosSay);            // arret fanebattOffFonc()
  while (batState == false)
  {
    veille_def = 8;
    if (batState == false)
    { // si entree actif
      batState = getBattery(batt, battLow);
      digitalWrite(alim, false);
      sosSay = 1;
      sosTmp = 2;
      f_b_cl(sosSay);
      sosSay = 2;
      f_r_cl(sosSay);
      sosSay = 1;
      spot_cl(sosSay, sosTmp);
    }
    else
    {
      digitalWrite(alim, true);
      sosSay = 1;   //  code actif fane  battOffFonc()
      fane(sosSay); //  actif fane  battOffFonc()
      alim_State = 30;
    }
  }
  if (cp_cl > 3)
  {
    cp_cl = 1; // battOffFonc
    veilleF(alim_State, BPmarcheState, batt);
  }
  debut = millis();
}

/**************FONCTION****s_i_cl*/
int s_i_cl(int sosSay, int sosTmp)
{
  int say10 = sosSay;
  if (say10 == 10)
  {
    sosSay = 2;
  }
  if (sosSay == 0)
  { // arret s_i_cl
    sosTmp = 1;
    digitalWrite(sirenC, false); // modifie l'état de la LED
  }
  if (millis() - s_i_cl_Tmp < 1000 * sosTmp)
  {
    s_i_cl_state = false;
    if (compte30sI <= sosSay)
    {
      if (sirenIState == LOW)
      {
        if ((millis() - millisSi_BR_CLon) >= 300)
        {
          sirenIState = HIGH; // change the state of LED
          millisSi_BR_CLon = millis();
          if (say10 == 0)
          {
            digitalWrite(sirenI, false); // modifie l'état de la LED
          }
          else
          {
            if (say10 == 10)
            {
              digitalWrite(sirenI, false); // modifie l'état de la LED
            }
            else
            {
              digitalWrite(sirenI, sirenIState);
            }
          }
        }
      }
      else
      {
        if ((millis() - millisSi_BR_CLon) >= 550)
        {
          compte30sI = compte30sI + 1;
          sirenIState = LOW; // change the state of LED
          millisSi_BR_CLon = millis();
          if (say10 == 10)
          {
            digitalWrite(sirenI, true);
          }
          else
          {
            if (sosSay == 0) // arret s_i_cl
            {
              // modifie l'état de la LED
            }
            else
            {
              digitalWrite(sirenI, sirenIState); // modifie l'état de la LED
            }
          }
        }
      }
      if (compte30sI >= sosSay)
      {
        s_i_cl_state = true;
      }
    }
  }
  else
  {
    s_i_cl_Tmp = millis(); // mémorise la valeur de la fonction millis()
    millisSi_BR_CLon = millis();
    comptesI = comptesI + 1;
    if (compte30sI >= sosSay)
    {
      compte30sI = 1;
    }
  }
}
/**************FONCTION****s_i_cl****final*/
/**************FONCTION****s_c_cl*/
int s_c_cl(int sosSay, int sosTmp)
{
  int say10 = sosSay;
  if (say10 == 10)
  {
    sosSay = 2;
  }
  if (sosSay == 0)
  {
    sosTmp = 1;
    digitalWrite(sirenC, false); // modifie l'état de la LED
  }
  if (compte30sC <= sosSay)
  {
    s_c_cl_state = false;
    if (sirenCState == LOW)
    {
      if ((millis() - millisSc_BR_CLon) >= 300)
      {
        sirenCState = HIGH; // change the state of LED
        millisSc_BR_CLon = millis();
        if (say10 == 0 || say10 == 10)
        {
          digitalWrite(sirenC, false); // modifie l'état de la LED
        }
        else
        {
          digitalWrite(sirenC, sirenCState); // remember Current millis() time
                                             // if ()
                                             // {
                                             //   digitalWrite(sirenC, false); // modifie l'état de la LED
                                             // }
                                             // else
                                             // {
                                             // }
        }
      }
    }
    else
    {
      if ((millis() - millisSc_BR_CLon) >= 500)
      {
        compte30sC = compte30sC + 1;
        sirenCState = LOW; // change the state of LED
        millisSc_BR_CLon = millis();
        if (say10 == 10)
        {
          digitalWrite(sirenC, true);
        }
        else
        {
          if (sosSay == 0)
          {
            digitalWrite(sirenC, false);
          }
          else
          {
            digitalWrite(sirenC, sirenCState);
          }
        }
      }
    }
  }
  else
  {
    s_c_cl_state = true;
    compte30sC = 1;
    s_c_cl_Tmp = millis();
    millisSc_BR_CLon = millis();
    comptesC = comptesC + 1;
    if (compte30sC >= sosSay)
    {
    }
  }
  if (millis() - s_c_cl_Tmp < 1000 * sosTmp)
  {
  }
  else
  {
    // compte30=0;
    if (compte30sC >= sosSay)
    {
    }
  }
}
/**************FONCTION****s_c_cl****final*/
/**************FONCTION****f_r_cl*/
int f_r_cl(int sosSay) //, int sosTmp)
{
  int say10 = sosSay;
  if (say10 == 10)
  {
    sosSay = 2;
  }
  if (say10 == 0)
  {
    sosSay = 1;
    sosTmp = 1;
    flacheRougeState = false;
    digitalWrite(flacheRouge, flacheRougeState); // modifie l'état de la LED
  }
  sosTmp = sosSay + 1;
  if (millis() - f_r_cl_Tmp <= 1000 * sosTmp)
  {
    if (compte30R < sosSay)
    {
      f_r_cl_state = false;
      if (flacheRougeState == LOW)
      { // inverse la variable d''état de la LED
        if (millis() - f_r_cl_Say >= 300)
        {
          f_r_cl_Say = millis();
          flacheRougeState = HIGH;
          if (say10 == 0)
          {
            flacheRougeState = false;
            digitalWrite(flacheRouge, flacheRougeState); // modifie l'état de la LED
          }
          else
          {
            if (say10 == 10)
            {
              flacheRougeState = false;
              digitalWrite(flacheRouge, flacheRougeState); // modifie l'état de la LED
            }
            else
            {
              digitalWrite(flacheRouge, flacheRougeState);
            }
          }
        }
      }
      else
      {
        if (millis() - f_r_cl_Say >= 400)
        {
          flacheRougeState = LOW;
          compte30R = compte30R + 1;
          f_r_cl_Say = millis();
          if (say10 == 10)
          {
            flacheRougeState = true;
            digitalWrite(flacheRouge, flacheRougeState);
          }
          else
          {
            if (say10 == 0)
            {
              flacheRougeState = false;
              digitalWrite(flacheRouge, flacheRougeState); // modifie l'état de la LED
            }
            else
            {
              digitalWrite(flacheRouge, flacheRougeState); // modifie l'état de la LED
            }
          }
        }
      }
    }
    else
    {
      f_r_cl_Say = millis(); // mémorise millis()
      compte30R = 0;
      f_r_cl_Tmp = millis() + (1000 * (sosTmp + 1)); // mémorise millis()
    }
  }
  else
  {
    if (say10 == true)
    {
      compteB = compteB + 1; // f_r_cl
    }
    f_r_cl_Tmp = millis(); // mémorise millis()
    f_r_cl_state = true;
  }
}
/*************FONCTION*****f_r_cl****final*/
/*************FONCTION*****f_b_cl*/
int f_b_cl(int sosSay)
{
  int say10 = sosSay;
  if (say10 == 10)
  {
    sosSay = 2;
  }
  if (say10 == 0)
  {
    sosSay = 1;
    // sosTmp = 1;
    digitalWrite(flacheBleu, flacheBleuState); // modifie l'état de la LED
  }
  sosTmp = sosSay + 1;
  if (millis() - f_b_cl_Tmp <= 1000 * sosTmp)
  {
    flacheBleuState = false;
    if (compte30B < sosSay)
    {
      f_b_cl_state = false; // cycle en cours
      if (flacheBleuState == LOW)
      { // inverse la variable d''état de la LED
        if (millis() - f_b_cl_Say >= 300)
        {
          f_b_cl_Say = millis();
          flacheBleuState = HIGH;
          if (say10 == 0)
          {
            flacheBleuState = false;
            digitalWrite(flacheBleu, flacheBleuState); // modifie l'état de la LED
          }
          else
          {
            if (say10 == 10)
            {
              flacheBleuState = false;
              digitalWrite(flacheBleu, flacheBleuState); // modifie l'état de la LED
            }
            else
            {
              digitalWrite(flacheBleu, flacheBleuState);
            }
          }
        }
      }
      else
      {
        if (millis() - f_b_cl_Say >= 400)
        {
          flacheBleuState = LOW;
          compte30B = compte30B + 1;
          f_b_cl_Say = millis(); // mémorise millis()
          if (say10 == 10)
          {
            flacheBleuState = true;
            digitalWrite(flacheBleu, flacheBleuState);
          }
          else
          {
            if (sosSay == 0)
            {
              flacheBleuState = false;
              digitalWrite(flacheBleu, flacheBleuState); // modifie l'état de la LED
            }
            else
            {
              digitalWrite(flacheBleu, flacheBleuState);
            }
          }
        }
      }
      // if (compte30B > sosSay)
      // {
      //   f_b_cl_Tmp = millis() + (1050 * sosTmp); // mémorise millis()
      // }
    }
    else
    {
      compte30B = 0;
      f_b_cl_Say = millis();                         // mémorise millis()
      f_b_cl_Tmp = millis() + (1000 * (sosTmp + 1)); // mémorise millis()
    }
  }
  else
  {
    if (say10 == true)
    {
      compteB = compteB + 1; // f_b_cl
    }
    f_b_cl_Tmp = millis(); // mémorise millis()
    f_b_cl_state = true;   // f_b_cl fin cycle
  }
}
/*************FONCTION*****f_b_cl////final*/
/*************FONCTION*****sosNbr10*/
int sosNbr10() // spot_cl + s_c_cl
{
  switch (comptespot) //(sosNbr == 10)
  {

  case 1:
    sosSay = 2;
    sosTmp = 5;
    spot_cl(sosSay, sosTmp); // (sosNbr == 10)
    break;
  case 2:
    sosSay = 1;
    sosTmp = 1;
    spot_cl(sosSay, sosTmp); // (sosNbr == 10)
    break;
  case 3:
    sosSay = 2;
    sosTmp = 5;
    spot_cl(sosSay, sosTmp); // (sosNbr == 10)
  case 4:
    sosSay = 1;
    sosTmp = 1;
    spot_cl(sosSay, sosTmp); // (sosNbr == 10)
  default:
    comptespot = 1; // sosNbr == 10
  }
}
/*************FONCTION*****sosNbr10****final*/

/*************FONCTION*****T E S T****/
