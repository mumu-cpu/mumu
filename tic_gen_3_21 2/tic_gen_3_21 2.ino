//------------------DECLARE INIT
  //------CONFIG INP_OUT
    byte testPh =       A0;     // entree analog phase
    byte testN =        A1;      // entree analog neutre
    byte testT =        A2;      // entree analog terre
    byte BATTERYPIN =   A3; // pin de la batterie
    byte photo =        A4;      // cellule photo
    int temrat =        A5;     // cellule temperature
    //                  D0;
    //                  D1;  
    byte BPmarche =     2;    // entree bp_marche
    byte welc_ctr_in =  2; // 8;  // entree control diagnostique
    byte sirenC =       3;       // sortie siren con (continute)
    byte alimOk =       4;      // entree control 230v OK
    byte fan =          5;          // ventilateur
    byte spot =         6;         // eclairage
    //                  D7;
    //                  D8;
    byte sirenI =       9;       // sortie siren iso
    byte alim =         10;        // sortie_Alim
    byte flacheRouge =  11; // sortie flacheRouge
    byte flacheBleu =   12;  // sortie flacheBleu
    byte bosch =        13;       // sortie batterie

    byte phase = 0;            // state phase
    byte neutre = 0;           // state neutre
    byte terre = 0;            // state terre
  //------GEN_TST
    long sec = 1000;
    long minut = 60 * sec;

    byte CcPhNeTe = 0;         // CcPhNeTe
    byte CcPhNeTe_prew = 0;
    byte fan_bch_cyl = 0;

    bool battLow = false; // battLow
    bool battLow_prew = false;
    int batt = 0;         // batt
    bool BPmarcheState = false;    // state bp_marche
    bool Manu_auto = false;        // state auto_manu
    bool alim_State = false;                // state alim_State
    bool alim_State_prew = 0;
    bool tempo_State_On = false;       // cycle on
    bool ecl_state = false;
    byte ecl_pos = 0;
    unsigned long debut = millis();   // temp debu t duree cycle
    unsigned long curmill = millis();       // temp ccphnt
    long cur_mil = millis();
  //------GEN
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
    long debut_ecl = 0;
    byte etalon[4] = {0, 0, 0, 0};


  //------INIT
    bool maz_int = false;
    bool mis_veil = false;

    byte ccphnete0_prew = 0;
    byte ccphnete0 = 0;

  //------TB COUN T
    byte switch_def_src = 0;
    unsigned long ct1t_millis = millis();
    bool ct1t_cycl_st[6] = {false, false, false, false, false, false};
    byte ct1t_posi_st[9] = {false, false, false, false, false, false, false, false, false};
    byte ct1t_switch;
    unsigned long ct2t_millis = millis();
    bool ct2t_cycl_st[6] = {false, false, false, false, false, false};
    byte ct2t_posi_st[9] = {false, false, false, false, false, false, false, false, false};
    byte ct2t_switch;
    unsigned long ct3t_millis = millis();
    bool ct3t_cycl_st[6] = {false, false, false, false, false, false};
    byte ct3t_posi_st[9] = {false, false, false, false, false, false, false, false, false};
    byte ct3t_switch;
    unsigned long ct3t_millis_fan = millis();
    bool ct3t_cycl_st_fan[6] = {false, false, false, false, false, false};
    byte ct3t_posi_st_fan[9] = {false, false, false, false, false, false, false, false, false};
    byte ct3t_switch_fan;
  	bool temp_sys=false ;
    bool temp_sys_prew=false ;



  //------chiffre type
      byte selc_aut[12]{91, 1, 81, 1, 92, 1, 82, 1, 0, 0, 0, 0};  //    selc 1
      byte selc_bat[12]{91, 2, 81, 2, 0, 0, 0, 0, 0, 0, 0, 0};  //    selc 2
      byte selc_230[12]{0, 0, 0, 0, 92, 3, 82, 3, 0, 0, 0, 0};  //    selc 3
    byte selc_ne_te[12]{3, 3, 61, 1, 4, 4, 71, 2, 0, 0, 0, 0};    //    selc 4
    byte selc_ph_te[12]{2, 2, 61, 1, 4, 4, 71, 2, 0, 0, 0, 0};    //    selc 5
    byte selc_ph_ne[12]{2, 2, 61, 1, 3, 3, 62, 2, 0, 0, 0, 0};    //    selc 6
   byte selc_cc_tst[12]{2, 2, 61, 1, 3, 3, 62, 1, 4, 4, 62, 2};  //    selc 7
    byte selc_cc_cc[12]{5, 5, 71, 1, 5, 5, 72, 2, 0, 0, 0, 0};   //    selc 8
    //    chiffre
    byte chf_cyl[12];
    byte flache_b_r_s = 0;
    byte siren_c_i = 0;
    byte sosSay = 0;
    byte selc = 0;
    byte typ = 0;           //


  //------WELC
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
  //------COUN T 1s
    byte ct1s_state = 0;
    bool ct1s_sta = false;
    bool ct1s_sta1 = false;

    byte ct05s_state = 0;
    bool ct05s_sta = false;
    bool ct05s_sta1 = false;

  //-------

    unsigned long cpt1s_millis = millis();

    unsigned long cpt05s_millis = millis();
//------------------SETUP
  void setup()
  {
    Serial.begin(115200);
    Serial.println("---- A U T O ---- D I A G N O S T I C ----"); //
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
      Serial.println("---- S Y S T E M ---- O K ----");
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
      Serial.println("---- S Y S T E M ---- A U T O ---- C O N F I G ----"); //
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
      Serial.println("	DEFAUT	----	0.f.");
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
      Serial.println("	DEFAUT	----	0.f.");
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
      Serial.println("	DEFAUT	----	0.f.");
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
      Serial.println("	DEFAUT	----	0.f.  ! HS");
      fan = 0;
    } // defaut fan --> hs
    if (welc_ctr_tb_st[4] == true)
    {
      Serial.print(welc_ctr_tb_id[4]);
      Serial.println("	DEFAUT	----	0.f.  ! HS");
      spot = 0;
    } // defaut spot --> hs
    // flacheRouge -> flacheBleu -> spot -> con -> iso ==> DEFAUT
    if (welc_ctr_tb_st[0] == true &&
        welc_ctr_tb_st[1] == true &&
        welc_ctr_tb_st[2] == true &&
        welc_ctr_tb_st[3] == true &&
        welc_ctr_tb_st[4] == true)
    {
      Serial.println("	DEFAUT ---- GENERAL ! viSon");
      while (1)
        ;
    }
    // alim 230v ==> DEFAUT
    if (welc_ctr_tb_st[5] == true)
    {
      Serial.println("	DEFAUT ---- GENERAL ! 230v");
      while (1)
        ;
    }
    // bat BOSCH ==> DEFAUT
    if (welc_ctr_tb_st[7] == true)
    {
      Serial.println("	DEFAUT ---- GENERAL ! BOSCH");
      while (1)
        ;
    }
    debut = millis(); // temp debu t duree cycle
  }
//------------------LOOP
 void loop()
  {
    //--------GEN_VEILLE--------EN COURS
      if(mis_veil ==true )
      {
        veil_mis();
      }
      
    //lop     tst
      manu_auto_tempo();
      CcPhNeTe = test();
      batt = getBattery(battLow);
      if (batt >= 0 && batt <= 20){battLow = true;}else{battLow = false;}


      alim_State = getAlim(battLow);
      //GEN_ste=true;
   	  if (GEN_ste == true) // source en cours
      {
        GEN_ALM();
        //return;
      }

    //--------RESET

      if (CcPhNeTe_prew != CcPhNeTe || ccphnete0_prew != ccphnete0)
      {
        CcPhNeTe_prew = CcPhNeTe;
        ccphnete0_prew = ccphnete0;
        maz_int = false;
      if (CcPhNeTe > 0)
        {
          ecl_auto(0,battLow);
        } 
      
      
      }
    //lop     exe
      if (CcPhNeTe > 0)
        {
          //ecl_auto(0,battLow);
          GEN_TST();
          debut = millis();
        }
      else 
        {
          ecl_auto(11,battLow);
          //--------------SYS OK  
            unsigned long rlt_cc0_lop = millis() - debut_cc0_lop;
            //                  SYSTEM 0K
            if (alim_State == true && battLow == false && CcPhNeTe == false)
            {
              ccphnete0 = 1;
              if (rlt_cc0_lop > sec * 5)
              {
              if (welc_ctr_err == true)
              {
                //def_3t(60, 2);
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
                //def_1t(60, 2);
                if (ct1t_posi_st[8] == 1)
                {
                  ct1t_posi_st[8] = 0; // compteur
                  ct1t_posi_st[7] = 0;
                  debut_cc0_lop = millis();
                  for (int i = 0; i < 8; i++)
                  {
                    ct1t_posi_st[i] = false;
                  }
                }
              }
            }
          //--------------GEN_mode
            unsigned long rlt_gen_lop = millis() - debut_gen_lop;
            if (rlt_gen_lop > minut) // GEN_mode
            {
              ccphnete0 = 2;
              GEN_mode();
            }

            }
          //--------------BOSCH LOW  
            //                  
            if (CcPhNeTe == 0 && battLow == true)
            {
              ccphnete0 = 3;
            if (rlt_cc0_lop > sec * 10)
            {
              def_source(2, 2);
              def_source(4, 2);
              //def_source(60, 2);
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
          //--------------TEMPO 5 minutes
            //unsigned long rlt_cc0_lop = millis() - debut_cc0_lop;

            if (rlt_cc0_lop > minut * 5)
              {
                ccphnete0 = 4;
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


            
        }
      maz_int_f();

    //-----------------------------TEST
      /*
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
      */
    
      //-----------------------------TEST
    //-----------------------------TEST
  }
//------------------FIN LOOP
//------------------FONCTION
//------SLC----SOSSAY----TYPE---
  //
  //---------------------SOSSAY	SLC                     
    //			1   temp o off						 		              
    //			2   bosch off								              
    //			3   230v  off 	                          
    //			4   ne_te   						 		              
    //			5   ph_te     							              
    //			6   ph_ne      	                          
    //			7   cc_tst     							              
    //			8   cc_cc      	                          
    //                                                
  //---------------------SOSSAY	TYPE                    
    //			1   def_1t        ct1t								    
    //			2   def_2t        ct2t								    
    //			3   def_3t        ct3t               	    
    //			4   def_source    ct3t               	    
    //                                                
  //--------------------SOSSAY										      
    //			0   arret      		fan   		spot_c l			  
    //			1   active		    fan	si battLow -> 51 52 
    //			2-3 flacheBleu		sirenC								  
    //			4-5 flacheRouge		sirenI								  
    //			51	fan 					tot_auto		 	  
    //			52	fan 					semi_auto							  
    //			60	spot
    //			611	spot          intermitent
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
    //
 //--------SLC----SOSSAY----TYPE---------------------------------
//------GEN----mode----TST----ALM
  void GEN_mode()
    {
      debut_gen_inp = millis();
      debut_gen_cyl = millis();
      unsigned long rlt_gen_inp = millis() - debut_gen_inp;
      unsigned long rlt_gen_cyl = millis() - debut_gen_cyl;
      while (rlt_gen_cyl <= sec * 3)
      {
        digitalWrite(spot,true);
        rlt_gen_cyl = millis() - debut_gen_cyl;

        if (etalon[0] == 0 && etalon[1] == 0 && phase == 1 && rlt_gen_inp < 100)
        {
          digitalWrite(flacheBleu,true);
          debut_gen_inp = millis();
          etalon[0] = 1;
        }
        if (etalon[0] == 1 && etalon[1] == 0 && phase == 0 && rlt_gen_inp < 100)
        {
          debut_gen_inp = millis();
          etalon[1] = 1;
        }
        if (etalon[0] == 1 && etalon[1] == 1)
        {
          etalon[2]++;
          etalon[0] = 0;
          etalon[1] = 0;
        }
      }
      digitalWrite(spot,false);
        switch (etalon[2] ) {
            case 1:
              etalon[3] = etalon[2];
              // do something
              break;
            case 2:
              etalon[3] = etalon[2];
              GEN_ALM();
              // do something
              break;
            case 3:
              etalon[3] = etalon[2];
              for (int i = 0; i < 3; i++)
              {
                etalon[i] = 0;
              }
              GEN_TST();

              break;
        }
        if (etalon[2] == 1)
        {
        }
        if (etalon[2] == 2)
        {
        }

        if (etalon[2] == 3)
        {
        }
        for (int i = 0; i < 4; i++)
        {
          etalon[i] = 0;
        }
      //}
      if (etalon[3] == 3)
      {
      }  
      if (etalon[3] == 2)
      {
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
      byte switch_def;
      switch (CcPhNeTe)
      {
      case 1: // Ne <-> Te
        //Serial.print("Ne <-> Te ");
        //Serial.println(CcPhNeTe);
        selc=4;
        typ=1;
        selc_typ(selc,sosSay,typ);
        cyl_def_source(selc,sosSay,typ);
        break;
      case 2: // Ph <-> Te
        //Serial.print("Ph <-> Te ");
        //Serial.println(CcPhNeTe);
        selc=5;
        typ=1;
        selc_typ(selc,sosSay,typ);
        cyl_def_source(selc,sosSay,typ);
        break;
      case 3: // Ph <-> Ne
        //Serial.print("Ph <-> Ne ");
        //Serial.println(CcPhNeTe);
        selc=6;
        typ=1;
        selc_typ(selc,sosSay,typ);
        cyl_def_source(selc,sosSay,typ);
        break;
      case 4: // Cc-Ph-Ne-Te. test
        //Serial.print("Cc-Ph-Ne-Te. test ");
        //Serial.println(CcPhNeTe);
        selc=7;
        typ=1;
        selc_typ(selc,sosSay,typ);
        cyl_def_source(selc,sosSay,typ);
        break;
      case 5: // Cc_Ph_Ne_Te. cuci
        //Serial.print("Cc_Ph_Ne_Te. cuci");
        //Serial.println(CcPhNeTe);
        selc=8;
        typ=1;
        selc_typ(selc,sosSay,typ);
        cyl_def_source(selc,sosSay,typ);
      default:
        break;
      }
    }
  void GEN_ALM()
    {
      if(Manu_auto==false){maz_int=false;maz_int_f(); return ;}
      
      long gen_rlt = millis() - gen_debut;
      if (gen_rlt <= gen_tmp_230)
      {
        gen_rlt = millis() - gen_debut;
        GEN_ste = true;
        ecl_auto(11,battLow);
        
        //digitalWrite(alim, true);
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
            for (int i = 0; i < 9; i++)
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
//------DIV----manu_maz_ecl_veil
  void manu_auto_tempo(){
    //            MANU_AUTO_VEILLE
    // si BPmarcheState (off)  on
      BPmarcheState = digitalRead(BPmarche);
      Manu_auto = !BPmarcheState;
    // si tempo_State_On (off)  on
      if ((millis() - debut) <= (20*sec)){
          tempo_State_On = true;
        }
      else {
          tempo_State_On = false;
        }
    if (tempo_State_On == true && Manu_auto == false){
      long tempCycle = (20*sec) - (millis() - debut);
      //Serial.print("temp cylce restant : ");
      tempCycle = tempCycle / sec;
      //Serial.print(tempCycle);
      //Serial.println(" s.");

      }
    if (tempo_State_On == false && Manu_auto == true){
      long temp_manu = millis()/sec;
      //Serial.println("Manu  on");
      //Serial.print("temp cycle :");
      //Serial.println(temp_manu);
      debut = millis();
      }
    if (tempo_State_On == false && Manu_auto == false){
      ccphnete0 = 5;
      mis_veil = true;
      // veilleFonc(tempo_State_On, BPmarcheState, battLow, batt);
      }
    if(tempo_State_On == true && Manu_auto == true ){
        long dbut = debut;
        long temp_manu = millis()/sec;
        //Serial.println("Manu  on");
        //Serial.print("temp cycle :");
        //Serial.println(temp_manu);
        long tempCycle = (20*sec) - (millis() - dbut);
        //Serial.print("temp cylce restant : ");
        tempCycle = tempCycle / sec;
        //Serial.print(tempCycle);
        //Serial.println(" s.");
        debut = millis();
      }
    }
  void maz_int_f(){
    // mise a zer0
    if (maz_int == false)
    {
      maz_int = true;
      digitalWrite(flacheRouge, false);
      digitalWrite(flacheBleu,  false);
      digitalWrite(sirenC,      false);
      digitalWrite(sirenI,      false);
      digitalWrite(spot,        false);
      digitalWrite(alim,        false);
      digitalWrite(fan,         false);
      digitalWrite(bosch,       false);
      for (int i = 0; i < 9; i++)
        {
        ct1t_posi_st[i] = false;
        ct2t_posi_st[i] = false;
        ct3t_posi_st[i] = false;
        }
      for (int i = 0; i < 6; i++)
        {
        ct1t_cycl_st[i] = false;
        ct2t_cycl_st[i] = false;
        ct3t_cycl_st[i] = false;
        }
  
      ct1t_millis =   millis();
      ct2t_millis =   millis();
      ct3t_millis =   millis();
      gen_debut =     millis();
      debut_3m =      millis();
      debut_1m =      millis();
      debut_gen_inp = millis();
      debut_gen_cyl = millis();
      debut_cc0_lop = millis();
      debut_gen_lop = millis();
      //debut_fan_bch = millis();
      byte etalon[4] = {0, 0, 0, 0};
      if(CcPhNeTe != 5){curmill = millis();}
    }
    }
  void ecl_auto(byte sosSay, bool battLow){
    if(battLow == true){sosSay = 0;}
    
    if (sosSay == 0)
    { // arret ecl_ Auto()
      digitalWrite(spot, false);
      //Serial.println("eclairage off");
      goto sosSay0;
    }
    if (sosSay == 1 && battLow == false)
    { // active ecl_ Auto()
      if (analogRead(photo) >= 10)
      {
        digitalWrite(spot, true);
        //Serial.println("eclairage on_auto");
      }
      else
      {
        digitalWrite(spot, false);
        //Serial.println("eclairage off_auto");
      }
      goto sosSay0;
    }
    if (sosSay == 11) 
      {
        long ecl_mil = millis() - debut_ecl;
        if (ecl_pos == 0 && ecl_mil > 100){ //5 * sec
          ecl_state=false;
          ecl_pos = 1;
          debut_ecl = millis(); 
        }
        ecl_mil = millis() - debut_ecl; 
        if(ecl_pos == 1 && ecl_mil > 100) //2 * sec
          {
            ecl_state = false;
            ecl_pos = 0;
            debut_ecl = millis();
          }
        if(ecl_pos == 0)
        {
          ecl_pos = 0;
          if(analogRead(photo) >= 10)
          {
            ecl_state = true;
          }else {ecl_state = false;}
        }

        digitalWrite(spot, ecl_state);
      }


    sosSay0:
    sosSay=sosSay;
    }
  void veil_mis()  {
    byte switch_veil_prew=0;
    long veil_millis = 0;
    long rlt_veil = millis()-veil_millis;
    bool debut_tempo = false;
    byte switch_veil;

    maz_int = false;
	  maz_int_f(); 
    veil_millis = millis(); 
    while (tempo_State_On == false || batt <= 1 || alim_State == false){
      ccphnete0 = 0;
      BPmarcheState = digitalRead(BPmarche);
      alim_State = getAlim(battLow);
      batt = getBattery(battLow);
      if (batt >= 1 && batt <= 20){battLow = true;}else{battLow = false;}
      if(tempo_State_On == false ){switch_veil =1;}
      if (batt <= 1 ){switch_veil =2;}
      if (alim_State == false) {switch_veil =3;}
      if (switch_veil_prew != switch_veil){
        maz_int = false;
        maz_int_f();
        rlt_veil = millis()-veil_millis; 
        if(rlt_veil<sec){
          goto fin;
          }else{
          switch_veil_prew = switch_veil;
          veil_millis = millis(); 
          }
      }else{veil_millis = millis();}
      switch (switch_veil) {
        case 1:
          if(BPmarcheState == false){tempo_State_On = true;}
          if (millis() - debut >= 5*sec || debut_tempo == false)
          {
            //ecl_auto(0,battLow); 
            selc=1;
            typ=1;
            selc_typ(selc,sosSay,typ);
            cyl_def_source(selc, sosSay, typ);
            if (ct1t_posi_st[8] == 6)
              {
                //ecl_auto(11,battLow); 
                debut = millis();
                debut_tempo = true;
              }
          }
          //for(int i = 0; i < 7; i++)
          //{
            if (ct1t_posi_st[0]== false &&
                ct1t_posi_st[1]== false &&
                ct1t_posi_st[2]== false &&
                ct1t_posi_st[3]== false &&
                ct1t_posi_st[4]== false &&
                ct1t_posi_st[5]== false &&
                ct1t_posi_st[6]== false &&
                ct1t_posi_st[7]== false){
              ecl_auto(11,battLow);
            }else{
              ecl_auto(0,battLow);
            }
            
          //}
          
          break;
        case 2:
          tempo_State_On = false; 
          if (millis() - debut >= 5*sec || debut_tempo == false)
            {
              //ecl_auto(0,battLow); 
              selc=2;
              typ=2;
              selc_typ(selc,sosSay,typ);
              cyl_def_source(selc, sosSay, typ);
              if (ct2t_posi_st[8] == 6)
                {
                  //ecl_auto(11,battLow); 
                  debut = millis();
                  debut_tempo = true;
                }
            }
            if (ct2t_posi_st[0]== false &&
                ct2t_posi_st[1]== false &&
                ct2t_posi_st[2]== false &&
                ct2t_posi_st[3]== false &&
                ct2t_posi_st[4]== false &&
                ct2t_posi_st[5]== false &&
                ct2t_posi_st[6]== false &&
                ct2t_posi_st[7]== false){
              ecl_auto(11,battLow);
            }else{
              ecl_auto(0,battLow);
            }
          break;
        case 3:
          tempo_State_On = false; 
          if(millis() - debut >= 15*sec || debut_tempo == false)
          {
            //ecl_auto(0,battLow); 
            selc=3;
            typ=3;
            selc_typ(selc,sosSay,typ);
            cyl_def_source(selc, sosSay, typ);
            if (ct3t_posi_st[8] == 6)
              {
                //ecl_auto(11,battLow); 
                debut = millis();
                debut_tempo = true;
              }
          }
            if (ct3t_posi_st[0]== false &&
                ct3t_posi_st[1]== false &&
                ct3t_posi_st[2]== false &&
                ct3t_posi_st[3]== false &&
                ct3t_posi_st[4]== false &&
                ct3t_posi_st[5]== false &&
                ct3t_posi_st[6]== false &&
                ct3t_posi_st[7]== false){
              ecl_auto(11,battLow);
            }else{
              ecl_auto(0,battLow);
            }

          break;
        }
        fin:
      switch_veil = switch_veil; 
      }
    debut = millis();
    mis_veil = false;
    }
//------------------TEST CCPHNETE
  int test()
    {
      phase = analogRead(testPh) ;
      neutre = analogRead(testN);
      terre = analogRead(testT);
      if (phase >= 10)
      {
        phase = true;
      }
      if (neutre >= 10)
      {
        neutre = true;
      }
      if (terre >= 10)
      {
        terre = true;
      }
      if (phase == true && neutre == true && terre == true)
      {
        if (millis() - curmill < 2*sec)
        {
          CcPhNeTe = 4; // sosNbr234()
        }
        else
        {
          CcPhNeTe = 5; //sosNbr55() 
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
//------------------DEF--|--COUN T----1t_2t_3t 
  
  int count_1t()
    {
      unsigned long ct1t_resu = millis() - ct1t_millis;

      // cycle x1                       1
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
      // etein 1                          2
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

      // cycle x2                           3
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
      // etein 3                            4
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
      // cycle x3                           5
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
      // etein 5                            6
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
      // fin cycle maz                      7
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
      if (ct3t_resu > 200 &&
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
      if (ct3t_resu > 200 &&
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
      if (ct3t_resu > 500 &&
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
      if (ct3t_resu > 200 &&
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
      if (ct3t_resu > 200 &&
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
      if (ct3t_resu > 400 &&
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
  int count_3t_fan()
    {
      unsigned long ct3t_resu_fan = millis() - ct3t_millis_fan;

      // cycle x1
      // allum 0
      if (ct3t_resu_fan > 0 &&
          ct3t_cycl_st_fan[0] == false &&
          ct3t_cycl_st_fan[5] == false)
      {
        ct3t_millis_fan = millis();
        ct3t_posi_st_fan[0] = true;
        ct3t_cycl_st_fan[0] = true;
        ct3t_cycl_st_fan[5] = false;
      }
      // etein 1
      ct3t_resu_fan = millis() - ct3t_millis_fan;
      if (ct3t_resu_fan > 200 &&
          ct3t_cycl_st_fan[0] == true &&
          ct3t_cycl_st_fan[1] == false)
      {
        ct3t_millis_fan = millis();
        ct3t_posi_st_fan[0] = false;
        ct3t_posi_st_fan[1] = true;
        ct3t_cycl_st_fan[1] = true;
      }

      // cycle x2
      // allum 2
      ct3t_resu_fan = millis() - ct3t_millis_fan;
      if (ct3t_resu_fan > 200 &&
          ct3t_cycl_st_fan[0] == true &&
          ct3t_cycl_st_fan[1] == true &&
          ct3t_cycl_st_fan[2] == false)
      {
        ct3t_millis_fan = millis();
        ct3t_posi_st_fan[1] = false;
        ct3t_posi_st_fan[2] = true;
        ct3t_cycl_st_fan[2] = true;
      }
      // etein 3
      ct3t_resu_fan = millis() - ct3t_millis_fan;
      if (ct3t_resu_fan > 500 &&
          ct3t_cycl_st_fan[0] == true &&
          ct3t_cycl_st_fan[1] == true &&
          ct3t_cycl_st_fan[2] == true &&
          ct3t_cycl_st_fan[3] == false)
      {
        ct3t_millis_fan = millis();
        ct3t_posi_st_fan[2] = false;
        ct3t_posi_st_fan[3] = true;
        ct3t_cycl_st_fan[3] = true;
      }
      // cycle x3
      // allum 4
      ct3t_resu_fan = millis() - ct3t_millis_fan;
      if (ct3t_resu_fan > 200 &&
          ct3t_cycl_st_fan[0] == true &&
          ct3t_cycl_st_fan[1] == true &&
          ct3t_cycl_st_fan[2] == true &&
          ct3t_cycl_st_fan[3] == true &&
          ct3t_cycl_st_fan[4] == false)
      {
        ct3t_millis_fan = millis();
        ct3t_posi_st_fan[3] = false;
        ct3t_posi_st_fan[4] = true;
        ct3t_cycl_st_fan[4] = true;
      }
      // etein 5
      ct3t_resu_fan = millis() - ct3t_millis_fan;
      if (ct3t_resu_fan > 200 &&
          ct3t_cycl_st_fan[0] == true &&
          ct3t_cycl_st_fan[1] == true &&
          ct3t_cycl_st_fan[2] == true &&
          ct3t_cycl_st_fan[3] == true &&
          ct3t_cycl_st_fan[4] == true &&
          ct3t_cycl_st_fan[5] == false)
      {
        ct3t_millis_fan = millis();
        ct3t_posi_st_fan[4] = false;
        ct3t_posi_st_fan[5] = true;
        ct3t_cycl_st_fan[5] = true;
      }
      // fin cycle maz
      ct3t_resu_fan = millis() - ct3t_millis_fan;
      if (ct3t_resu_fan > 400 &&
          ct3t_cycl_st_fan[0] == true &&
          ct3t_cycl_st_fan[1] == true &&
          ct3t_cycl_st_fan[2] == true &&
          ct3t_cycl_st_fan[3] == true &&
          ct3t_cycl_st_fan[4] == true &&
          ct3t_cycl_st_fan[5] == true)
      {
        ct3t_millis_fan = millis();
        for (int i = 0; i < 6; i++)
        {
          ct3t_cycl_st_fan[i] = false;
        }

        ct3t_posi_st_fan[5] = false;
        ct3t_posi_st_fan[6] = true;
      }
    }
  
  int def_1t(byte sosSay, byte cl)
    {
    if(sosSay == 0 || cl == 0){goto no_count;}
    count_1t();
    no_count:
    if (ct1t_posi_st[6] == true || cl == 0)
        {
          //ct1t_posi_st[6] = false;
      if (cl > 0){ct1t_posi_st[7]++;}  // compteur cycle


          if (ct1t_posi_st[7] == cl)
          {
            ct1t_posi_st[7]=0;
            ct1t_posi_st[8]++; // compteur
            if(sosSay==0)
            {
              goto sosSay0;
            }
            
          } else {
          //ct1t_posi_st[7]++; // compteur cycle

          }
        }
    /**
    if (sosSay == 0){
      ct1t_posi_st[6] = true;
      ct1t_posi_st[7]=0;
      ct1t_posi_st[8]++; // compteur

      ct1t_switch = 6;
      goto inter;
      } 
    */
    //sosSay_slc(selc, sosSay, typ);
    // cycle count_1t
    for (int i = 0; i < 7; i++)
        {
          if (ct1t_posi_st[i] == true)
          {
            ct1t_switch = i;
          }//else{ct1t_switch = 0;} 
        }
    inter:
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
          //ct1t_switch = 0;
          for (int i = 0; i < 7; i++)
          {
            ct1t_posi_st[i] = false;
            //ct2t_posi_st[i] = false;
            //ct3t_posi_st[i] = false;
          }

          ct1t_millis = millis();
          //ct2t_millis = millis();
          //ct3t_millis = millis();

          break;
        case 7:
          ct1t_switch = 0;
          break;
        }
      sosSay0:
      //byte CcPhNeTe_switch = ct1t_posi_st[8];
      return (ct1t_posi_st[8]);
    }
  int def_2t(byte sosSay, byte cl)
    {
    if(sosSay == 0 || cl == 0){goto no_count;}
    count_2t();
    no_count:
      if (ct2t_posi_st[6] == true || cl == 0)
        {
      if (cl > 0){ct2t_posi_st[7]++;}  // compteur cycle
        //ct2t_posi_st[6] = false;
        if (ct2t_posi_st[7] == cl)
          {
            ct2t_posi_st[7] = 0;
            ct2t_posi_st[8]++; // compteur
            if(sosSay==0){goto sosSay0;}
          } //else {ct2t_posi_st[7]++;} // compteur cycle
          }
      //sosSay_slc(selc, sosSay, typ);
      // cycle count_2t
      //count_2t();
      for (int i = 0; i < 7; i++)
        {
        if (ct2t_posi_st[i] == true)
          {
            ct2t_switch = i;
          }
        }
    inter:
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
          //ct2t_switch = 0;
          for (int i = 0; i < 7; i++)
          {
            //ct1t_posi_st[i] = false;
            ct2t_posi_st[i] = false;
            //ct3t_posi_st[i] = false;
          }

          //ct1t_millis = millis();
          ct2t_millis = millis();
          //ct3t_millis = millis();

          break;
        case 7:
          ct2t_switch = 0;
          break;
        }
      sosSay0:  
      //byte CcPhNeTe_switch = 
      return (ct2t_posi_st[8]);
    }
  int def_3t(byte sosSay, byte cl)
    {
    if(sosSay == 0 || cl == 0){goto no_count;}
    count_3t();
    no_count:
      if (ct3t_posi_st[6] == true || cl == 0)
        {
          if (cl > 0){ct3t_posi_st[7]++;}  // compteur cycle
          //ct3t_posi_st[6] = false;
          if (ct3t_posi_st[7] == cl)
          {
            ct3t_posi_st[8]++; // compteur
            ct3t_posi_st[7] = 0;
            if(sosSay==0)
            {
              goto sosSay0;
            }
          }else {
          //ct3t_posi_st[7]++; // compteur cycle
          }
        }
      //sosSay_slc(selc, sosSay, typ);
      //count_3t();
      for (int i = 0; i < 7; i++)
        {
          if (ct3t_posi_st[i] == true)
          {
            ct3t_switch = i;
          }
        }
    inter:
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
          //ct3t_switch = 0;
          for (int i = 0; i < 7; i++)
          {
            //ct1t_posi_st[i] = false;
            //ct2t_posi_st[i] = false;
            ct3t_posi_st[i] = false;
          }

          ct3t_millis = millis();
          //ct2t_millis = millis();
          //ct1t_millis = millis();

          break;
        case 7:
          ct3t_switch = 0;
          break;
        }
      sosSay0:  
      //byte CcPhNeTe_switch = ct3t_posi_st[8];
      return (ct3t_posi_st[8]);
    }
  int fan_3t(byte sosSay, byte cl)
    {
      if (sosSay == 0){
        ct3t_posi_st_fan[8]++;
        ct3t_switch_fan = 6;
        goto inter;
        }

      sosSay_slc(selc, sosSay, typ);
      count_3t_fan();
      for (int i = 0; i < 6; i++)
        {
          if (ct3t_posi_st_fan[i] == true)
          {
            ct3t_switch_fan = i;
          }
        }
      if (ct3t_posi_st_fan[6] == true)
        {
          ct3t_posi_st_fan[6] = false;
          ct3t_posi_st_fan[7]++; // compteur cycle
          if (ct3t_posi_st_fan[7] == cl)
          {
            ct3t_posi_st_fan[8]++; // compteur
            ct3t_posi_st_fan[7] = 0;
          }
        }
    inter:
      switch (ct3t_switch_fan){
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
          ct3t_switch_fan = 0;
          for (int i = 0; i < 9; i++){
            ct3t_posi_st_fan[i] = false;
           }
          ct3t_millis_fan = millis();
          break;
        case 7:
          ct3t_switch_fan = 0;
          break;
       }
      byte CcPhNeTe_switch = ct3t_posi_st_fan[8];
      return (CcPhNeTe_switch);
    }

  int def_source(byte sosSay, byte cl)
    {
      if (sosSay == 0){
        ct3t_posi_st[8]++;
        ct3t_switch = 6;
        goto inter;
        }

      sosSay_slc(selc, sosSay, typ);  
      count_3t();
      for (int i = 0; i < 6; i++){
        if (ct3t_posi_st[i] == true){
          ct3t_switch = i;
          }
        }
      if (ct3t_posi_st[6] == true){
        ct3t_posi_st[6] = false;
        ct3t_posi_st[7]++; // compteur cycle
        if (ct3t_posi_st[7] == cl){
          ct3t_posi_st[8]++; // compteur
          ct3t_posi_st[7] = 0;
          }
        }
    inter:
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
            //ct1t_posi_st[i] = false;
            //ct2t_posi_st[i] = false;
            ct3t_posi_st[i] = false;
          }

          ct3t_millis = millis();
          //ct2t_millis = millis();
          //ct1t_millis = millis();

          break;
        case 7:
          ct3t_switch = 0;
          break;
        }
      byte CcPhNeTe_switch = ct3t_posi_st[8];
      return (CcPhNeTe_switch);
    }
//------------------CYL CcPhNeTe    
  void cyl_def_source(byte selc, byte sosSay, byte typ){
      switch (switch_def_src){
        case 0://0 1
          switch (typ) {
          case 1:
            sosSay=chf_cyl[0];
            sosSay_slc(selc, sosSay, typ);
            def_1t(chf_cyl[0], chf_cyl[1]);
            break;
          case 2:
            sosSay=chf_cyl[0];
            sosSay_slc(selc, sosSay, typ);
            def_2t(chf_cyl[0], chf_cyl[1]);
            break;
          case 3:
            sosSay=chf_cyl[0];
            sosSay_slc(selc, sosSay, typ);
            def_3t(chf_cyl[0], chf_cyl[1]);
            break;
          case 4:
            sosSay=chf_cyl[0];
            sosSay_slc(selc, sosSay, typ);
            def_source(chf_cyl[0], chf_cyl[1]);
            break;
          }
          break;
        case 1://2 3
          switch(typ){
            case 1:
              sosSay=chf_cyl[2];
              sosSay_slc(selc, sosSay, typ);
              def_1t(chf_cyl[2], chf_cyl[3]);
              break;
            case 2:
              sosSay=chf_cyl[2];
              sosSay_slc(selc, sosSay, typ);
              def_2t(chf_cyl[2], chf_cyl[3]);
              break;
            case 3:
              sosSay=chf_cyl[2];
              sosSay_slc(selc, sosSay, typ);
              def_3t(chf_cyl[2], chf_cyl[3]);
              break;
            case 4:
              sosSay=chf_cyl[2];
              sosSay_slc(selc, sosSay, typ);
              def_source(chf_cyl[2], chf_cyl[3]);
              break;
            }
          break;
        case 2://4 5
          switch(typ){
            case 1:
              sosSay=chf_cyl[4];
              sosSay_slc(selc, sosSay, typ);
              def_1t(chf_cyl[4], chf_cyl[5]);
              break;
            case 2:
              sosSay=chf_cyl[4];
              sosSay_slc(selc, sosSay, typ);
              def_2t(chf_cyl[4], chf_cyl[5]);
              break;
            case 3:
              sosSay=chf_cyl[4];
              sosSay_slc(selc, sosSay, typ);
              def_3t(chf_cyl[4], chf_cyl[5]);
              break;
            case 4:
              sosSay=chf_cyl[4];
              sosSay_slc(selc, sosSay, typ);
              def_source(chf_cyl[4], chf_cyl[5]);
              break;
              }
              break;
        case 3://6 7
          switch(typ){
            case 1:
              sosSay=chf_cyl[6];
              sosSay_slc(selc, sosSay, typ);
              def_1t(chf_cyl[6], chf_cyl[7]);
              break;
            case 2:
              sosSay=chf_cyl[6];
              sosSay_slc(selc, sosSay, typ);
              def_2t(chf_cyl[6], chf_cyl[7]);
              break;
            case 3:
              sosSay=chf_cyl[6];
              sosSay_slc(selc, sosSay, typ);
              def_3t(chf_cyl[6], chf_cyl[7]);
              break;
            case 4:
              sosSay=chf_cyl[6];
              sosSay_slc(selc, sosSay, typ);
              def_source(chf_cyl[6], chf_cyl[7]);
              break;
              }
            break;
        case 4://8 9
          switch(typ){
            case 1:
              sosSay=chf_cyl[8];
              sosSay_slc(selc, sosSay, typ);
              def_1t(chf_cyl[8], chf_cyl[9]);
              break;
            case 2:
              sosSay=chf_cyl[8];
              sosSay_slc(selc, sosSay, typ);
              def_2t(chf_cyl[8], chf_cyl[9]);
              break;
            case 3:
              sosSay=chf_cyl[8];
              sosSay_slc(selc, sosSay, typ);
              def_3t(chf_cyl[8], chf_cyl[9]);
              break;
            case 4:
              sosSay=chf_cyl[8];
              sosSay_slc(selc, sosSay, typ);
              def_source(chf_cyl[8], chf_cyl[9]);
              break;
          }
          break;
        case 5://10 11
          switch(typ){
          case 1:
              sosSay=chf_cyl[10];
              sosSay_slc(selc, sosSay, typ);
              def_1t(chf_cyl[10], chf_cyl[11]);
            break;
          case 2:
              sosSay=chf_cyl[10];
              sosSay_slc(selc, sosSay, typ);
              def_2t(chf_cyl[10], chf_cyl[11]);
            break;
          case 3:
              sosSay=chf_cyl[10];
              sosSay_slc(selc, sosSay, typ);
              def_3t(chf_cyl[10], chf_cyl[11]);
            break;
          case 4:
              sosSay=chf_cyl[10];
              sosSay_slc(selc, sosSay, typ);
              def_source(chf_cyl[10], chf_cyl[11]);
            break;
            }
          break;
        case 6:
          switch(typ){
          case 1:
              for (int i = 0; i < 9; i++)
            {
              ct1t_posi_st[i] = false;
            }
            break;
          case 2:
            for (int i = 0; i < 9; i++)
            {
              ct2t_posi_st[i] = false;
            }
            break;
          case 3:
            for (int i = 0; i < 9; i++)
            {
              ct3t_posi_st[i] = false;
            }
            break;
          case 4:
            for (int i = 0; i < 9; i++)
            {
              ct3t_posi_st[i] = false;
            }
            break;
            }
          break;
        }
    }
  void sosSay_slc(byte selc, byte sosSay, byte typ)
    {
    switch(sosSay){
      case 0:
        flache_b_r_s = false;
        siren_c_i = false;
        break;
      case 2:
      case 3: // flacheBleu,sirenC
        flache_b_r_s = flacheBleu; // sortie 12
        siren_c_i = sirenC;        // 3 sortie siren con (continute)
        break;
      case 4:
      case 5: // flacheRouge,sirenI
        flache_b_r_s = flacheRouge; // 11 sortie flacheRouge
        siren_c_i = sirenI;         // 9 sortie siren iso
        break;
      case 50: // fan
        flache_b_r_s = fan; // 5 ventilateur
        siren_c_i = fan;    // 5 ventilateur
        break;
      case 60: // spot
        flache_b_r_s = spot; // 6 sortie spot
        siren_c_i = false;   // "<&>"
        break;
      case 611: // spot
        sosSay = 1;
        flache_b_r_s = spot; // 6 sortie spot
        siren_c_i = false;   // "<&>"
        break;
      case 612: // spot
        sosSay = 2;
        flache_b_r_s = spot; // 6 sortie spot
        siren_c_i = false;   // "<&>"
        break;
      case 61: // spot,sirenI
        flache_b_r_s = spot; // 6 sortie spot
        siren_c_i = sirenI;  // 9 sortie siren iso
        break;
      case 62: // spot,sirenI
        flache_b_r_s = spot; // 6 sortie spot
        siren_c_i = sirenI;  // 9 sortie siren iso
        break;
      case 71: // spot,sirenC
        flache_b_r_s = spot; // 6 sortie spot
        siren_c_i = sirenC;  // 3 sortie siren con
        break;
      case 72: // spot,sirenC
        flache_b_r_s = spot; // 6 sortie spot
        siren_c_i = sirenC;  // 3 sortie siren con
        break;
      case 81: // sirenC
        flache_b_r_s = false; // "<&>"
        siren_c_i = sirenC;   // 3 sortie siren con
        break;
      case 82: // sirenI
        flache_b_r_s = false; // "<&>"
        siren_c_i = sirenI;   // 9 sortie siren iso
        break;
      case 91: // flacheBleu
        flache_b_r_s = flacheBleu; // 12 sortie flacheBleu
        siren_c_i = false;         // "<&>"
        break;
      case 92: // flacheRouge
        flache_b_r_s = flacheRouge; // 11 sortie flacheRouge
        siren_c_i = false;          // "<&>"
        break;
     }
    }
  void selc_typ(byte selc, byte sosSay, byte typ)
    {
    switch(selc){
      case 1: // temp o manu auto   off
        for (int i = 0; i < 13; i++)
        {
          chf_cyl[i] = selc_aut[i];
        }
        break;
      case 2: // bosch             off
        for (int i = 0; i < 13; i++)
        {
          chf_cyl[i] = selc_bat[i];
        }
        break;
      case 3: // 230v              off
        for (int i = 0; i < 13; i++)
        {
          chf_cyl[i] = selc_230[i];
        }
        break;
      case 4: // ne_te
        for (int i = 0; i < 13; i++)
        {
          chf_cyl[i] = selc_ne_te[i];
        }
        break;
      case 5: // ph_te
        for (int i = 0; i < 13; i++)
        {
          chf_cyl[i] = selc_ph_te[i];
        }
        break;
      case 6: // ph_ne
        for (int i = 0; i < 13; i++)
        {
          chf_cyl[i] = selc_ph_ne[i];
        }
        break;
      case 7: // cc_tst
        for (int i = 0; i < 13; i++)
        {
          chf_cyl[i] = selc_cc_tst[i];
        }
        break;
      case 8: // cc_cc
        for (int i = 0; i < 13; i++)
        {
          chf_cyl[i] = selc_cc_cc[i];
        }
        break;
       }
    switch(typ){
      case 1: // def_1t
        switch_def_src = ct1t_posi_st[8];
        break;
      case 2: // def_2t
        switch_def_src = ct2t_posi_st[8];
        break;
      case 3: // def_3t
        switch_def_src = ct3t_posi_st[8];
        break;
      case 4: // def_source
        switch_def_src = ct3t_posi_st[8];
        break;
      }
    }
//------------------AUTO COFIG 
  int welc_1s(byte ct1s_state)
  {
    byte ct1s_ste = ct1s_state;
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
  int count05s(byte ct05s_state)
  {
    byte ct05s_ste = ct05s_state;
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
//------------------BOSCH_230V_FAN
  int getBattery(bool battLow)
    {
      float b = analogRead(BATTERYPIN);                  // valeur analogique
      float minValue = (1023 * 10.5) / 20.0; // Arduino
      float maxValue = (1023 * 20.0) / 20.0; // Arduino
      float moy = maxValue - minValue;
      float val = b - minValue;
      float res = val / moy;
      float pct = res * 100; // mettre en pourcentage
      batt = pct;
      //const float voltt = (batt * (20.0 - 10.5));
      //const float volty = (voltt) / 100);
      //const float volt = (volty + 10.5);
      if (batt >= 100)
      {
        batt = 100;
      }
      if (batt <= 0)
      {
        batt = 0;
        ccphnete0 = 6;
        mis_veil = true;
      }

      // float volt = (((batt * (20.0 - 10.5)) / 100) + 10.5);
      float volt = (((batt * (20.0 - 10.5)) / 100) + 10.5);

        //if (batt > 0 && batt < 20){battLow = true;}else{battLow = false;}
      if (batt >= 1 && batt <= 20) // max is 20%
      {
        if (mis_veil == false ){
          //Serial.print(volt);
          //Serial.print("v !");
          //Serial.println(" !!! bat BOSCH LOW !!! ");
          }
      }
      else  {
        if (mis_veil == false){
          //Serial.print("bat BOSCH : ");
          //Serial.print(batt);
          //Serial.print("%_");
          //Serial.print(volt);
          //Serial.println("v");
          }
      }

      return (batt);
    }
  int controlAlimFonc(bool battLow)
    {
      if(alim_State_prew != alim_State)
      {
        alim_State_prew = alim_State;

      }
      
      digitalWrite(alim, true);            // 230v sous tention
      
      
      
      
      
      byte alimState = digitalRead(alimOk); // control 230v sous tention
      
      if (alimState == false)
      {                                    // si entree actif
        alim_State = 10;
        if (mis_veil == false ){
        //Serial.println("TENTION 230V 0n"); // affiche 230v On
        }
        if (battLow == true)
        {
          sosSay = 52;                        // code active fan e   controlAlimFon c()
          fane(sosSay,battLow);                      // active ventilateur controlAlimFon c()
        }
        else
        {
          sosSay = 1;                        // code active fan e  controlAlimFon c()
          fane(sosSay,battLow);                      // active ventilateur controlAlimFon c()

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
        ccphnete0 = 7;
        alim_State = 20;
        if (mis_veil == false ){

          //Serial.println("DEFAUT 230V 0ff"); // affiche 230v Off
        }
        sosSay = 0;                        // code arret fan e controlAlimFon c()  off
        fane(sosSay,battLow);                      // arret ventilateur controlAlimFon c()
        digitalWrite(alim, false); // arret 230v

        return (alim_State);
      }
    }
  int getAlim(bool battLow)
    {
      long rlt_alim = millis() - cur_mil;
      if(mis_veil==true){goto alim_off;}
      digitalWrite(alim,true);
      alim_State = !digitalRead(alimOk);
      digitalWrite(alim, alim_State);
      if(alim_State == false)
      {
        ///digitalWrite(alim, alim_State);
        fane(0,battLow);                      // arret ventilateur controlAlimFon c()
        mis_veil = true;
        ccphnete0 = 7;
        goto alim_off;

      }else 
      {
        cur_mil = millis();
        if (battLow == true) {
            //sosSay = 52;                   // code active fan e   controlAlimFon c()
            fane(52,battLow);                      // active ventilateur controlAlimFon c()
          }
        else {
          //sosSay = 1;                      // code active fan e  controlAlimFon c()
          fane(52,battLow);                      // active ventilateur controlAlimFon c()
          }
       goto alim_fin;

      }
      
       alim_off:
          if(rlt_alim > sec && alim_State == false)
            {
              cur_mil = millis();
              digitalWrite(alim, true);
              alim_State = !digitalRead(alimOk);
              digitalWrite(alim, alim_State);
              if(alim_State == false ){
                //digitalWrite(alim, false);
                //sosSay = 0;                        // code arret fan e controlAlimFon c()  off
                fane(0,battLow);                      // arret ventilateur controlAlimFon c()
                mis_veil = true;
                ccphnete0 = 7;
                }
            }
      alim_fin:    
      return alim_State ;
    }


  void fane(byte sosSay,bool battLow){
    if(battLow == true){sosSay = 0;}

      if (sosSay == 0)
        { // arret fan e()
          digitalWrite(fan, false);
          if (mis_veil == false ){
          //Serial.println("ventilateur off");
          }
        }
      if ((battLow == false && sosSay == 1) || sosSay == 51)
        { // auto fan e()
          if (analogRead(temrat) >= 10){
            digitalWrite(fan, true);
            if (mis_veil == false ){
              //Serial.println("ventilateur on_auto");
              }
          }
          else {
            digitalWrite(fan, false);
            if (mis_veil == false ){
              //Serial.println("ventilateur off_auto");
              }
          }
        }
    //--------------reset ct3t-fan  
    	if (temp_sys_prew != temp_sys){ 
        //if (battLow_prew != battLow){
        battLow_prew = battLow;
        temp_sys_prew = temp_sys;
        for (int i = 0; i < 9; i++)
          {
          ct3t_posi_st_fan[i] = false;
          }
        for (int i = 0; i < 6; i++)
          {
          ct3t_cycl_st_fan[i] = false;
          }
        ct3t_millis_fan = millis();
        debut_fan_bch = millis();
        fan_bch_cyl = 0;
        digitalWrite(fan,false);



        }
    
    
    int get_temp_sys = analogRead(temrat);
      // 200 int. -> 50°c
    if (get_temp_sys >= 100){temp_sys = true;}else{temp_sys = false;}
      if (sosSay == 52 && temp_sys == true)
        {
          unsigned long rlt_fan_bch = millis() - debut_fan_bch;
          if (fan_bch_cyl == 0 && rlt_fan_bch > sec)
          {
            //Serial.println("ventilateur BCH LOW cyl 1 on_auto");
            fan_3t(50, 5); // active FAN
            if (ct3t_posi_st_fan[8] > 0)
            {
              // ct3t_posi_st[8]++; // compteur
              ct3t_posi_st_fan[8] = 0;
              debut_fan_bch = millis();
              fan_bch_cyl = 1;
              for (int i = 0; i < 8; i++)
              {
                ct3t_posi_st_fan[i] = false;
              }
            }
          }
          rlt_fan_bch = millis() - debut_fan_bch;
          if (fan_bch_cyl == 1 && rlt_fan_bch > sec * 10)
          {
            //Serial.println("ventilateur BCH LOW cyl 2 on_auto");
            fan_3t(50, 4); // active FAN
            if (ct3t_posi_st_fan[8] > 0)
            {
              // ct3t_posi_st[8]++; // compteur
              ct3t_posi_st_fan[8] = 0;
              debut_fan_bch = millis();
              fan_bch_cyl = 2;
              for (int i = 0; i < 8; i++)
              {
                ct3t_posi_st_fan[i] = false;
              }
            }
          }
          rlt_fan_bch = millis() - debut_fan_bch;
          if (fan_bch_cyl == 2 && rlt_fan_bch > sec * 10)
          {
            //Serial.println("ventilateur BCH LOW cyl 3 on_auto");
            fan_3t(50, 3); // active FAN
            if (ct3t_posi_st_fan[8] > 0)
            {
              // ct3t_posi_st[8]++; // compteur
              ct3t_posi_st_fan[8] = 0;
              debut_fan_bch = millis();
              fan_bch_cyl = 3;
              for (int i = 0; i < 8; i++)
              {
                ct3t_posi_st_fan[i] = false;
              }
            }
          }
          rlt_fan_bch = millis() - debut_fan_bch;
          if (fan_bch_cyl == 3 && rlt_fan_bch > sec * 10)
          {
            //Serial.println("ventilateur BCH LOW cyl 4 on_auto");
            fan_3t(50, 2); // active FAN
            if (ct3t_posi_st_fan[8] > 0)
            {
              // ct3t_posi_st[8]++; // compteur
              ct3t_posi_st_fan[8] = 0;
              debut_fan_bch = millis();
              fan_bch_cyl = 0;
              for (int i = 0; i < 8; i++)
              {
                ct3t_posi_st_fan[i] = false;
              }
            }
          }
        }
    }





