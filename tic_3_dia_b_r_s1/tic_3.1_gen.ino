//–––––––––––––––CONFIG INP_OUT
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
//–––––––––––––––GEN_TST
  int sosSay = 0;           //
  int CcPhNeTe = 0;         // CcPhNeTe
  int CcPhNeTe_prew = 0;

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
  unsigned long tempo = (sec * 20); // temp duree cycle
  unsigned long debut = millis();   // temp debut duree cycle
  unsigned long interval = 1000;    // interval cligniot
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

//–––––––––––––––GEN
  long minut = 60000;
  long sec = 1000;
  long gen_debut = 0;
  long gen_tmp_230 = 15 * minut;
  bool GEN_ste = false;
  long debut_3m = 0;
  long debut_1m = 0;
  long debut_gen_inp = 0;
  long debut_gen_cyl = 0;
  long debut_cc0_lop = 0;
  long debut_gen_lop = 0;
  long debut_fan_bch = 0;
  int etalon[4] = {0, 0, 0, 0};


//–––––––––––––––INIT
  bool maz_int = false;
  bool mis_veil = false;

  int ccphnete_0_st = 0;
  int ccphnete0 = 0;
  int veille_def_st = 0;
  int veille_def = 0;

//–––––––––––––––TB COUNT
  int switch_def_src = 0;
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

//–––––––––––––––chiffre type
  int selc_aut[6]{91, 81, 92, 82, 60, 50};  //    selc 1
  int selc_bat[6]{91, 81, 92, 82, 60, 50};  //    selc 2
  int selc_230[6]{91, 81, 92, 82, 60, 50};  //    selc 3
  int selc_ne_te[6]{3, 61, 4, 71, 0, 0};    //    selc 4
  int selc_ph_te[6]{2, 61, 4, 71, 0, 0};    //    selc 5
  int selc_ph_ne[6]{2, 61, 3, 62, 0, 0};    //    selc 6
  int selc_cc_tst[6]{2, 60, 3, 60, 4, 50};  //    selc 7
  int selc_cc_cc[6]{5, 71, 5, 72, 0, 50};   //    selc 8
  //    chiffre
  int chf_cyl[6];
  int flache_b_r_s = 0;
  int siren_c_i = 0;


//–––––––––––––––WELC
  bool welc_ctr_err = false;
  String rouge = "flache	ROUGE";       // welc_ID_index  0
  String bleu = "flache	BLEU";          // welc_ID_index  1
  String con = "siren	CONT";            // welc_ID_index  2
  String iso = "siren	ISO";             // welc_ID_index  3
  String spt = "ecl	SPOT";              // welc_ID_index  4
  String alm = "alim	230v";            // welc_ID_index  5
  String fn = "vent	FAN";               // welc_ID_index  6
  String bch = "bat	BOSCH";             // welc_ID_index  7

  bool welc_ctr_tb_st[8] = {false, false, false, false, false, false, false, false};
  String welc_ctr_tb_id[8] = {rouge, bleu, con, iso, spt, alm, fn, bch};
//–––––––––––––––COUNT 1s
  int ct1s_state = 0;
  bool ct1s_sta = false;
  bool ct1s_sta1 = false;

  int ct05s_state = 0;
  bool ct05s_sta = false;
  bool ct05s_sta1 = false;

//–––––––––––––––
  //int sosNbr = 0;           // code on_off_cl
  unsigned long sosTmp = 1; // tempt cliosos_Nbr40 x1000

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
//––––––––––––––––––––––––SETUP
  void setup()
  {
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
//––––––––––––––––––––––––LOOP
 void loop()
 {
  //–––––––––––––GEN_VEILLE–––––––EN COURS
    if (GEN_ste == true) // source en cours
    {
      GEN_ALM();
    }
    if(mis_veil==true )
    {
      veil_mis();
      mis_veil==false;
    }
    
  manu_auto_tempo();
  CcPhNeTe = test();

  //–––––––––––––––––––––––––––––––RESET

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
  //–––––––––––––––––––––––––––––––SYS OK  
    unsigned long rlt_cc0_lop = millis() - debut_cc0_lop;
    if (ccphnete0 == 1)
    {
      if (rlt_cc0_lop > sec * 5)
      {
        if (welc_ctr_err == true)
        {
          def_3t(60, 2);
          def_3t(81, 2);

          if (ct3t_posi_st[8] == 1)
          {
            // ct3t_posi_st[8]++; // compteur
            ct3t_posi_st[8] = 0;
            debut_cc0_lop = millis();
            for (int i = 0; i < 8; i++)
            {
              ct3t_posi_st[i] = false;
            }
          }
        }
        else
        {
          def_1t(60, 2);
          if (ct1t_posi_st[7] == 2)
          {
            ct1t_posi_st[8]++; // compteur
            ct1t_posi_st[7] = 0;
            debut_cc0_lop = millis();
            for (int i = 0; i < 8; i++)
            {
              ct1t_posi_st[i] = false;
            }
          }
        }
      }
      unsigned long rlt_gen_lop = millis() - debut_gen_lop;
      if (rlt_gen_lop > minut) // GEN_mode
      {
        GEN_mode();
      }
    }
    if (ccphnete0 == 2)
    {
      if (rlt_cc0_lop > sec * 10)
      {
        def_source(2, 2);
        def_source(4, 2);
        def_source(60, 2);
        if (ct3t_posi_st[8] == 1)
        {
          // ct3t_posi_st[8]++; // compteur
          ct3t_posi_st[8] = 0;
          debut_cc0_lop = millis();
          for (int i = 0; i < 8; i++)
          {
            ct3t_posi_st[i] = false;
          }
        }
      }
    }
    if (ccphnete0 == 3)
    {
      if (welc_ctr_err == true)
      {
        def_3t(62, 2);
        if (ct3t_posi_st[8] == 1)
        {
          // ct3t_posi_st[8]++; // compteur
          ct3t_posi_st[8] = 0;
          debut_cc0_lop = millis();
          for (int i = 0; i < 8; i++)
          {
            ct3t_posi_st[i] = false;
          }
        }
      }
      else
      {
        def_1t(62, 2);
        if (ct1t_posi_st[8] == 1)
        {
          // ct1t_posi_st[8]++; // compteur
          ct1t_posi_st[8] = 0;
          debut_cc0_lop = millis();
          for (int i = 0; i < 8; i++)
          {
            ct1t_posi_st[i] = false;
          }
        }
      }
    }

  maz_int_f();

  //–––––––––––––––––––––––––––––––TEST
    for (int i = 0; i < 9; i++)
    {
      Serial.print(ct1t_posi_st[i]);
    }
    Serial.println(" ");
    for (int i = 0; i < 9; i++)
    {

      Serial.print(ct2t_posi_st[i]);
    }
    Serial.println(" ");
    for (int i = 0; i < 9; i++)
    {
      Serial.print(ct3t_posi_st[i]);
    }
    Serial.println(" ");
    //–––––––––––––––––––––––––––––––TEST
    GEN_TST();
  //–––––––––––––––––––––––––––––––TEST
 }
//––––––––––––––––––––––––FIN LOOP
//––––––––––––––––––––––––FONCTION
//–––––––––––––SLC––SOSSAY––––––––––––––––––––––––––––––
  //
  //––––––––––––––––––SOSSAY	SLC                     
    //			1   tempo off						 		              
    //			2   bosch off								              
    //			3   230v  off 	                          
    //			4   ne_te   						 		              
    //			5   ph_te     							              
    //			6   ph_ne      	                          
    //			7   cc_tst     							              
    //			6   cc_cc      	                          
    //                                                
  //––––––––––––––––––SOSSAY	TYPE                    
    //			1   def_1t        ct1t								    
    //			2   def_2t        ct2t								    
    //			3   def_3t        ct3t               	    
    //			4   def_source    ct3t               	    
    //                                                
  //––––––––––––––––——SOSSAY										      
    //			0   arret      		fan   		spot_cl			  
    //			1   active		    fan	si battLow –> 51 52 
    //			2-3 flacheBleu		sirenC								  
    //			4-5 flacheRouge		sirenI								  
    //			51	fan 					tot_auto		 	  
    //			52	fan 					semi_auto							  
    //			611	spot                      sosSay 1
    //			612	spot                      sosSay 2
    //			61	spot					sirenI			sosSay 1	          
    //			62	spot					sirenI			sosSay 2	          
    //			71	spot					sirenC			sosSay 1
    //			72	spot					sirenC			sosSay 2		          
    //			81	sirenC															  
    //			82	sirenI															  
    //			91	flacheBleu													  
    //			92	flacheRouge													  
    //                                                
 //––––––––––––––––SOSSAY–––––––––––––––––––––––––––––

//––––––––––––––––––––––––GEN_mode_tst_alim
  void GEN_mode()
  {
    debut_gen_inp = millis();
    debut_gen_cyl = millis();
    unsigned long rlt_gen_inp = millis() - debut_gen_inp;
    unsigned long rlt_gen_cyl = millis() - debut_gen_cyl;
    while (rlt_gen_cyl <= sec * 3)
    {
      rlt_gen_cyl = millis() - debut_gen_cyl;

      if (etalon[0] == 0 && etalon[1] == 0 && phase > 1 && rlt_gen_inp < 100)
      {
        debut_gen_inp = millis();
        etalon[0] = 1;
      }
      if (etalon[0] == 1 && etalon[1] == 0 && phase < 1 && rlt_gen_inp < 100)
      {
        debut_gen_inp = millis();
        etalon[1] = 1;
      }
      if (etalon[0] == 1 && etalon[1] == 1)
      {
        etalon[2]++;
      }

      if (etalon[2] == 1)
      {
        etalon[3] = etalon[2];
      }
      if (etalon[2] == 2)
      {
        etalon[3] = etalon[2];
      }

      if (etalon[2] == 3)
      {
        etalon[3] = etalon[2];
        for (int i = 0; i < 3; i++)
        {
          etalon[i] = 0;
        }
      }
      for (int i = 0; i < 4; i++)
      {
        etalon[i] = 0;
      }
    }
    if (etalon[3] == 3)
    {
      GEN_TST();
    }  
    if (etalon[3] == 2)
    {
      GEN_ALM();
    }
    if (etalon[3] == 1)
    {
      // break;
    }
    debut_gen_inp = millis();
    debut_gen_cyl = millis();
  }
  void GEN_TST()
  {
    int switch_def;
    switch (CcPhNeTe)
    {
    case 1: // Ne <-> Te
      Serial.print("Ne <-> Te ");
      Serial.println(CcPhNeTe);
      // sosNbr34();
      cyl_def_source(4,);
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
          def_3t(3, 3);
        }
        else
        {
          def_1t(3, 3);
        }
        break;
      case 1:
        if (welc_ctr_err == true)
        {
          def_3t(61, 1);
        }
        else
        {
          def_1t(61, 1);
        }
        break;
      case 2:
        if (welc_ctr_err == true)
        {
          def_3t(4, 4);
        }
        else
        {
          def_1t(4, 4);
        }
        break;
      case 3:
        if (welc_ctr_err == true)
        {
          def_3t(72, 2);
        }
        else
        {
          def_1t(72, 2);
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
          def_3t(2, 2);
        }
        else
        {
          def_1t(2, 2);
        }
        break;
      case 1:
        if (welc_ctr_err == true)
        {
          def_3t(61, 1);
        }
        else
        {
          def_1t(61, 1);
        }
        break;
      case 2:
        if (welc_ctr_err == true)
        {
          def_3t(4, 4);
        }
        else
        {
          def_1t(4, 4);
        }
        break;
      case 3:
        if (welc_ctr_err == true)
        {
          def_3t(72, 2);
        }
        else
        {
          def_1t(72, 2);
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
          def_3t(2, 2);
        }
        else
        {
          def_1t(2, 2);
        }
        break;
      case 1:
        if (welc_ctr_err == true)
        {
          def_3t(61, 1);
        }
        else
        {
          def_1t(61, 1);
        }
        break;
      case 2:
        if (welc_ctr_err == true)
        {
          def_3t(3, 3);
        }
        else
        {
          def_1t(3, 3);
        }
        break;
      case 3:
        if (welc_ctr_err == true)
        {
          def_3t(62, 2);
        }
        else
        {
          def_1t(62, 2);
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
          def_3t(2, 2);
        }
        else
        {
          def_1t(2, 2);
        }
        break;
      case 1:
        if (welc_ctr_err == true)
        {
          def_3t(61, 1);
        }
        else
        {
          def_1t(61, 1);
        }
        break;
      case 2:
        if (welc_ctr_err == true)
        {
          def_3t(3, 3);
        }
        else
        {
          def_1t(3, 3);
        }
        break;
      case 3:
        if (welc_ctr_err == true)
        {
          def_3t(61, 1);
        }
        else
        {
          def_1t(61, 1);
        }
        break;
      case 4:
        if (welc_ctr_err == true)
        {
          def_3t(4, 4);
        }
        else
        {
          def_1t(4, 4);
        }
        break;
      case 5:
        if (welc_ctr_err == true)
        {
          def_3t(72, 2);
        }
        else
        {
          def_1t(72, 2);
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
          def_3t(5, 5);
        }
        else
        {
          def_1t(5, 5);
        }
        break;
      case 1:
        if (welc_ctr_err == true)
        {
          def_3t(71, 1);
        }
        else
        {
          def_1t(71, 1);
        }
        break;
      case 2:
        if (welc_ctr_err == true)
        {
          def_3t(5, 5);
        }
        else
        {
          def_1t(5, 5);
        }
        break;
      case 3:
        if (welc_ctr_err == true)
        {
          def_3t(72, 2);
        }
        else
        {
          def_1t(72, 2);
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
      //                  SYSTEM 0K
      if ((alim_State == 10 || alim_State == 30) && battLow == false && CcPhNeTe == false)
      {
        ccphnete0 = 1;
      }
      //                  BOSCH LOW
      if (CcPhNeTe == 0 && battLow == true)
      {
        ccphnete0 = 2;
      }
      //                  TEMPO 5 minutes
      unsigned long rlt_cc0_lop = millis() - debut_cc0_lop;

      if (rlt_cc0_lop > minut * 5)
      {
        ccphnete0 = 3;
      }
      compteB = 0; // CcPhNeTe == 0
      cp_cl = 1;
      comptespot = 1;
      chro = millis();
      break;
    }
  }
  void GEN_ALM()
  {
    long gen_rlt = millis() - gen_debut;
    if (gen_rlt <= gen_tmp_230)
    {
      GEN_ste = true;
      digitalWrite(alim, true);
      digitalWrite(bosch, true);

      long rlt_3m = millis() - debut_3m;
      if (rlt_3m > minut * 3)
      {
        def_3t(60, 2);
        def_3t(4, 2);
        def_3t(2, 2);
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
      }

      long rlt_1m = millis() - debut_1m;
      if (rlt_1m > minut)
      {
        def_3t(60, 2);
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
        def_1t(4, 4);
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
void manu_auto_tempo(){
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
    veille_def = 1;
    mis_veil = true;
    // veilleFonc(tempo_State_On, BPmarcheState, battLow, batt);
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
//––––––––––––––––––––––––AUTO COFIG
//––––––––––––––––––––––––TEST CCPHNETE
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
      CcPhNeTe = 0;
    }
    return (CcPhNeTe);
  }
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
//––––––––––DEF 1t_–––––––COMPTEUR 1t_2t_3t 
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
  int def_1t(int sosSay, int cl)
  {
    sosSay_slc(selc, sosSay, typ);
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
      if (ct1t_posi_st[7] == cl)
      {
        ct1t_posi_st[8]++; // compteur
      }
    }

    switch (ct1t_switch)
    {
    case 0:
      digitalWrite(flache_b_r_s, true);
      digitalWrite(siren_c_i, true);
      break;
    case 1:
      digitalWrite(flache_b_r_s, false);
      digitalWrite(siren_c_i, false);
      break;
    case 2:
      digitalWrite(siren_c_i, true);
      digitalWrite(flache_b_r_s, true);
      break;
    case 3:
      digitalWrite(siren_c_i, false);
      digitalWrite(flache_b_r_s, false);
      break;
    case 4:
      digitalWrite(flache_b_r_s, true);
      digitalWrite(siren_c_i, true);
      break;
    case 5:
      digitalWrite(flache_b_r_s, false);
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
  int def_2t(int sosSay, int cl)
  {
    sosSay_slc(selc, sosSay, typ);
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
      if (ct2t_posi_st[7] == cl)
      {
        ct2t_posi_st[8]++; // compteur
      }
    }

    switch (ct2t_switch)
    {
    case 0:
      digitalWrite(flache_b_r_s, true);
      digitalWrite(siren_c_i, true);
      break;
    case 1:
      digitalWrite(flache_b_r_s, false);
      digitalWrite(siren_c_i, false);
      break;
    case 2:
      digitalWrite(siren_c_i, true);
      digitalWrite(flache_b_r_s, true);
      break;
    case 3:
      digitalWrite(siren_c_i, false);
      digitalWrite(flache_b_r_s, false);
      break;
    case 4:
      digitalWrite(flache_b_r_s, true);
      digitalWrite(siren_c_i, true);
      break;
    case 5:
      digitalWrite(flache_b_r_s, false);
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
  int def_3t(int sosSay, int cl)
  {
    sosSay_slc(selc, sosSay, typ);
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
      if (ct3t_posi_st[7] == cl)
      {
        ct3t_posi_st[8]++; // compteur
        ct3t_posi_st[7] = 0;
      }
    }

    switch (ct3t_switch)
    {
    case 0:
      digitalWrite(flache_b_r_s, true);
      digitalWrite(siren_c_i, true);
      break;
    case 1:
      digitalWrite(flache_b_r_s, false);
      digitalWrite(siren_c_i, false);
      break;
    case 2:
      digitalWrite(siren_c_i, true);
      digitalWrite(flache_b_r_s, true);
      break;
    case 3:
      digitalWrite(siren_c_i, false);
      digitalWrite(flache_b_r_s, false);
      break;
    case 4:
      digitalWrite(flache_b_r_s, true);
      digitalWrite(siren_c_i, true);
      break;
    case 5:
      digitalWrite(flache_b_r_s, false);
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
  void cyl_def_source(int selc, int sosSay, int typ)
  {
    sosSay_slc(selc, sosSay, typ);
    switch (switch_def_src) //(sosNbr == 2_61_3_61_4_72)
    {
    case 0:
      if (typ == 1)
      {
        def_1t(chf_cyl[0], sosSay);
      }
      if (typ == 2)
      {
        def_2t(chf_cyl[0], sosSay);
      }
      if (typ == 3)
      {
        def_3t(chf_cyl[0], sosSay);
      }
      if (typ == 4)
      {
        def_source(chf_cyl[0], sosSay);
      }
      break;
    case 1:
      if (typ == 1)
      {
        def_1t(chf_cyl[0], sosSay);
      }
      if (typ == 2)
      {
        def_2t(chf_cyl[0], sosSay);
      }
      if (typ == 3)
      {
        def_3t(chf_cyl[0], sosSay);
      }
      if (typ == 4)
      {
        def_source(chf_cyl[0], sosSay);
      }
      break;
    case 2:
      if (typ == 1)
      {
        def_1t(chf_cyl[2], sosSay);
      }
      if (typ == 2)
      {
        def_2t(chf_cyl[2], sosSay);
      }
      if (typ == 3)
      {
        def_3t(chf_cyl[2], sosSay);
      }
      if (typ == 4)
      {
        def_source(chf_cyl[2], sosSay);
      }
      break;
    case 3:
      if (typ == 1)
      {
        def_1t(chf_cyl[3], sosSay);
      }
      if (typ == 2)
      {
        def_2t(chf_cyl[3], sosSay);
      }
      if (typ == 3)
      {
        def_3t(chf_cyl[3], sosSay);
      }
      if (typ == 4)
      {
        def_source(chf_cyl[3], sosSay);
      }
      break;
    case 4:
      if (typ == 1)
      {
        def_1t(chf_cyl[4], sosSay);
      }
      if (typ == 2)
      {
        def_2t(chf_cyl[4], sosSay);
      }
      if (typ == 3)
      {
        def_3t(chf_cyl[4], sosSay);
      }
      if (typ == 4)
      {
        def_source(chf_cyl[4], sosSay);
      }
      break;
    case 5:
      if (typ == 1)
      {
        def_1t(chf_cyl[5], sosSay);
      }
      if (typ == 2)
      {
        def_2t(chf_cyl[5], sosSay);
      }
      if (typ == 3)
      {
        def_3t(chf_cyl[5], sosSay);
      }
      if (typ == 4)
      {
        def_source(chf_cyl[5], sosSay);
      }
      def_source(2, 2);
      def_source(4, 2);

      break;
    case 6:
        if (typ == 1)
      {
        for (int i = 0; i < 9; i++)
      {
        ct1t_posi_st[i] = false;
      }
      }
      if (typ == 2)
      {
      for (int i = 0; i < 9; i++)
      {
        ct2t_posi_st[i] = false;
      }
      }
      if (typ == 3)
      {
      for (int i = 0; i < 9; i++)
      {
        ct3t_posi_st[i] = false;
      }
      }
      if (typ == 4)
      {
      for (int i = 0; i < 9; i++)
      {
        ct3t_posi_st[i] = false;
      }
      }

      break;
    }
  }
  int def_source(int sosSay, int cl)
  {
    sosSay_slc(selc, sosSay, typ);  
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
      if (ct3t_posi_st[7] == cl)
      {
        ct3t_posi_st[8]++; // compteur
        ct3t_posi_st[7] = 0;
      }
    }
    switch (ct3t_switch)
    {
    case 0:
      digitalWrite(flache_b_r_s, true);
      digitalWrite(siren_c_i, true);
      break;
    case 1:
      digitalWrite(flache_b_r_s, true);
      digitalWrite(siren_c_i, false);
      break;
    case 2:
      digitalWrite(siren_c_i, true);
      digitalWrite(flache_b_r_s, true);
      break;
    case 3:
      digitalWrite(siren_c_i, false);
      digitalWrite(flache_b_r_s, false);
      break;
    case 4:
      digitalWrite(flache_b_r_s, true);
      digitalWrite(siren_c_i, false);
      break;
    case 5:
      digitalWrite(flache_b_r_s, false);
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
  void sosSay_slc(int selc, int sosSay, int typ)
  {
    if (sosSay == 2 || sosSay == 3) // flacheBleu,sirenC
    {
      flache_b_r_s = flacheBleu; // sortie 12
      siren_c_i = sirenC;        // 3 sortie siren con (continute)
    }
    if (sosSay == 4 || sosSay == 5) // flacheRouge,sirenI
    {
      flache_b_r_s = flacheRouge; // 11 sortie flacheRouge
      siren_c_i = sirenI;         // 9 sortie siren iso
    }
    if (sosSay == 50) // fan
    {
      flache_b_r_s = fan; // 5 ventilateur
      siren_c_i = fan;    // 5 ventilateur
    }
    if (sosSay == 60) // spot
    {
      flache_b_r_s = spot; // 6 sortie spot
      siren_c_i = false;   // "<&>"
    }
    if (sosSay == 61) // spot,sirenI
    {
      flache_b_r_s = spot; // 6 sortie spot
      siren_c_i = sirenI;  // 9 sortie siren iso
    }
    if (sosSay == 62) // spot,sirenI
    {
      flache_b_r_s = spot; // 6 sortie spot
      siren_c_i = sirenI;  // 9 sortie siren iso
    }
    if (sosSay == 71) // spot,sirenC
    {
      flache_b_r_s = spot; // 6 sortie spot
      siren_c_i = sirenC;  // 3 sortie siren con
    }
    if (sosSay == 72) // spot,sirenC
    {
      flache_b_r_s = spot; // 6 sortie spot
      siren_c_i = sirenC;  // 3 sortie siren con
    }
    if (sosSay == 81) // sirenC
    {
      flache_b_r_s = false; // "<&>"
      siren_c_i = sirenC;   // 3 sortie siren con
    }
    if (sosSay == 82) // sirenI
    {
      flache_b_r_s = false; // "<&>"
      siren_c_i = sirenI;   // 9 sortie siren iso
    }
    if (sosSay == 91) // flacheBleu
    {
      flache_b_r_s = flacheBleu; // 12 sortie flacheBleu
      siren_c_i = false;         // "<&>"
    }
    if (sosSay == 92) // flacheRouge
    {
      flache_b_r_s = flacheRouge; // 11 sortie flacheRouge
      siren_c_i = false;          // "<&>"
    }
      if (selc == 1) // tempo manu auto   off
    {
      for (int i = 0; i < 7; i++)
      {
        chf_cyl[i] = selc_aut[i];
      }
    }
    if (selc == 2) // bosch             off
    {
      for (int i = 0; i < 7; i++)
      {
        chf_cyl[i] = selc_bat[i];
      }
    }
    if (selc == 3) // 230v              off
    {
      for (int i = 0; i < 7; i++)
      {
        chf_cyl[i] = selc_230[i];
      }
    }
    if (typ == 1) // def_1t
    {
      switch_def_src = ct1t_posi_st[8];
    }
    if (typ == 2) // def_2t
    {
      switch_def_src = ct2t_posi_st[8];
    }
    if (typ == 3) // def_3t
    {
      switch_def_src = ct3t_posi_st[8];
    }
    if (typ == 4) // def_source
    {
      switch_def_src = ct3t_posi_st[8];
    }

  }
//––––––––––––––––––––––––AUTO COFIG 
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
//––––––––––––––––––––––––BOSCH_230V 
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
    const float voltt = (pctr * (TensionMax - TensionMin));
    const float volty = (voltt / 100);
    const float volt = (volty + TensionMin);

    if (pctr > 100)
    {
      pctr = 100;
    }
    if (pctr < 0)
    {
      pctr = 0;
    }
    if (pctr > 1 && pctr <= 20) // max is 20%
    {
      
      Serial.print(volt);
      Serial.print("v !");
      battLow = true;
      Serial.println(" !!! bat BOSCH LOW !!! ");
      battLow = true;
      /*
        unsigned long curmil = millis();
        if (curmil - chroi >= sec*2)
        {
          
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
        */
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
    if (pctr <= 1)
    {
      veille_def = 2;
      mis_veil = true;
    }
    return (pctr);
  }
  int controlAlimFonc()
  {
    alim_State = 10;
    digitalWrite(alim, true);            // 230v sous tention
    int alimState = digitalRead(alimOk); // control 230v sous tention
    if (alimState == false)
    {                                    // si entree actif
      Serial.println("TENTION 230V 0n"); // affiche 230v On
      if(battLow==false)
      {
      sosSay = 1;                        // code active fane  controlAlimFonc()
      fane(sosSay);                      // active ventilateur controlAlimFonc()
      }
      else
      {
        sosSay = 52;                        // code active fane  controlAlimFonc()
        fane(sosSay);                      // active ventilateur controlAlimFonc()

      }
      
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
      mis_veil = true;
      veille_def = 3;
      alim_State = 20;
      Serial.println("DEFAUT 230V 0ff"); // affiche 230v Off
      sosSay = 0;                        // code arret fane controlAlimFonc()  off
      fane(sosSay);                      // arret ventilateur controlAlimFonc()
      digitalWrite(alim, false); // arret 230v

      return (alim_State);
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
    if ((battLow == false && sosSay == 1) || sosSay == 51)
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
    if (battLow == true && sosSay == 1 || sosSay == 52)
    {
      unsigned long rlt_fan_bch = millis() - debut_fan_bch;
      unsigned long rlt1_fan_bch = millis() - debut_fan_bch;
      int fan_bch_cyl = 0;
      if (fan_bch_cyl == 0 && rlt_fan_bch > sec * 10)
      {
        def_3t(50, 5); // active FAN
        if (ct3t_posi_st[8] > 0)
        {
          // ct3t_posi_st[8]++; // compteur
          ct3t_posi_st[8] = 0;
          debut_fan_bch = millis();
          fan_bch_cyl = 1;
          for (int i = 0; i < 8; i++)
          {
            ct3t_posi_st[i] = false;
          }
        }
      }
      if (fan_bch_cyl == 1 && rlt_fan_bch > sec * 10)
      {
        def_3t(50, 4); // active FAN
        if (ct3t_posi_st[8] > 0)
        {
          // ct3t_posi_st[8]++; // compteur
          ct3t_posi_st[8] = 0;
          debut_fan_bch = millis();
          fan_bch_cyl = 2;
          for (int i = 0; i < 8; i++)
          {
            ct3t_posi_st[i] = false;
          }
        }
      }
      if (fan_bch_cyl == 2 && rlt_fan_bch > sec * 10)
      {
        def_3t(50, 3); // active FAN
        if (ct3t_posi_st[8] > 0)
        {
          // ct3t_posi_st[8]++; // compteur
          ct3t_posi_st[8] = 0;
          debut_fan_bch = millis();
          fan_bch_cyl = 3;
          for (int i = 0; i < 8; i++)
          {
            ct3t_posi_st[i] = false;
          }
        }
      }
      if (fan_bch_cyl == 3 && rlt_fan_bch > sec * 10)
      {
        def_3t(50, 2); // active FAN
        if (ct3t_posi_st[8] > 0)
        {
          // ct3t_posi_st[8]++; // compteur
          ct3t_posi_st[8] = 0;
          debut_fan_bch = millis();
          fan_bch_cyl = 0;
          for (int i = 0; i < 8; i++)
          {
            ct3t_posi_st[i] = false;
          }
        }
      }
    }
  }
void veil_mis()
{
  BPmarcheState = digitalRead(BPmarche);
  batt = getBattery(batt, battLow);
  alim_State = controlAlimFonc();

  while (BPmarcheState == true || batt <= 1 || alim_State == 20)
  {
    Serial.println("veil_mis  appuille BP");
    if (BPmarcheState == true)
    {
      Serial.println("veil_mis  tempo off");
      cyl_def_source(1, 1, 1);
    }
    if (batt <= 1)
    {
      Serial.println("veil_mis  bosch off");
      cyl_def_source(2, 2, 2);
    }
    if (alim_State == 20)
    {
      Serial.println("veil_mis  230v off");
      cyl_def_source(3, 3, 3);

    }
  }
}
//––––––––––––––––––––––––VEILLE
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
      sosSay = 0;   // code arret ecl & fane veille_F()
      fane(sosSay); // arret fan  veille_F()
      while (BPmarcheState == false)
      {
        BPmarcheState = digitalRead(BPmarche);
        tempx = (millis() - temp1);
        if (tempx >= 5000)
        {
          Serial.println("defaut alim appuille BP");
          temp1 = millis();
          sosSay = 3;
          sosTmp = 3;
          spot_cl(sosSay, sosTmp);
        }
      }
      while (alim_State == 20)
      {
        alim_State = controlAlimFonc();
        tempx = (millis() - temp1);
        if (tempx >= 5000)
        {
          Serial.println("defaut 230v appuille BP");
          temp1 = millis();
          sosSay = 3;
          sosTmp = 3;
          spot_cl(sosSay, sosTmp);
        }
      }
    }
    while (batt <= 5)
    {
      batt = getBattery(batt, battLow);
      tempx = (millis() - temp1);
      if (tempx >= 5000)
      {
        Serial.println("batt LOW appuille BP");
        temp1 = millis();
        sosSay = 3;              // battLow 5%
        sosTmp = 3;              // battLow 5%
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
        BPmarcheState = digitalRead(BPmarche);
        tempx = (millis() - temp1);
        if (tempx >= 3000)
        {
          Serial.println("veille appuille BP");
          temp1 = millis();
          sosSay = 3;
          sosTmp = 2;
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
      digitalWrite(alim, true);        // 230v sous tention
      alimState = digitalRead(alimOk); // control 230v sous tention
      if (alimState == true)
      { // si entree actif
        digitalWrite(alim, false);
        alim_State = 20;
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
      if (batState == false)
      { // si entree actif
        batState = getBattery(batt, battLow);
        digitalWrite(alim, false);
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
 
