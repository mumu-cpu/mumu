/*
 Name:		TIC_4.mumu2.ino
 Created:	01/07/2024 19:03:01
 Author:	Yalcin
 Modif: 11/08/24
  versions	sys clio:				3 |
			gestion	BOSCH |_		3 |
					230v  |           |___4
			gestion AUTO			2 |
			veille surchauffe sys	2 |

*/

byte testPh = A0;      // entree analog phase
byte testN = A1;       // entree analog neutre
byte testT = A2;       // entree analog terre
byte phase = 0;        // state phase
byte neutre = 0;       // state neutre
byte terre = 0;        // state terre
byte BATTERYPIN = A3;  // pin de la batterie
bool battLow = false;  // battLow
bool battLow_prew = false;
int batt = 0;  // batt
bool battOff = false;
bool alim_tst = false;
bool alim_State = false;  // state alim_State
bool alim_State_prew = false;
long curren_millis_alim = millis();         // tempo_alim_off
int BPmarche = 2;                // entree bp_marche
bool BPmarcheState = false;      // state bp_marche
bool Manu_auto = false;          // state auto_manu
bool tempo_State_On = false;     // cycle on

long unsigned int debut = millis();  // temp debu t duree cycle
long unsigned int veil_millis = millis();	 // tempo veil detection
bool selec_mode_GEN = false;	 // state veil detection
unsigned long selec_mode_GEN_millis = 0;
unsigned long clio_normal_millis = millis();// tempo clio normal
bool state_sortie = false;		 // state clio normal

bool fan_state = false;
long fan_millis = 0;
int photo = A4;   // cellule photo
int temrat = A5;  // cellule temperature

const int sirenC = 3;  // sortie siren con (continute)
const int alimOk = 4;  // entree control 230v OK
const int fan = 5;     // ventilateur
const int spot = 6;    // eclairage
//                  D7;
//                  D8;
const int sirenI = 9;        // sortie siren iso
const int alim = 10;         // sortie_Alim
const int flacheRouge = 11;  // sortie flacheRouge
const int flacheBleu = 12;   // sortie flacheBleu
const int bosch = 13;        // sortie batterie

int flache_b_r_s = 0;
int siren_c_i = 0;
int CcPhNeTe = 0;  // CcPhNeTe
int CcPhNeTe_prew = 0;
long sec = 1000;
long minut = 60 * sec;

unsigned long curmill = millis();  // temp ccphnt

unsigned long compteMillis1 = 0;

int sequance = 0;
//int selec_type;
/*					select type 1													*/
long ct1t_nbr[9] = { 0, 200, 2000, 0, 2000, 0, 2000, 0, 2000 };  // temp clio selec auto
long ct1t_total = (ct1t_nbr[0] + ct1t_nbr[1] + ct1t_nbr[2] + ct1t_nbr[3] + ct1t_nbr[4] + ct1t_nbr[5] + ct1t_nbr[6] + ct1t_nbr[7] + ct1t_nbr[8]) * 4;
/*					select type 2													*/
long ct2t_nbr[9] = { 0, 200, 200, 500, 0, 0, 400, 0, 0 };  // temp clio selec
long ct2t_total = (ct2t_nbr[0] + ct2t_nbr[1] + ct2t_nbr[2] + ct2t_nbr[3] + ct2t_nbr[4] + ct2t_nbr[5] + ct2t_nbr[6] + ct2t_nbr[7] + ct2t_nbr[8]) * 4;
/*					select type 3													*/
long ct3t_nbr[9] = { 0, 100, 300, 100, 300, 100, 100, 500, 100 };  // temps clio defaut batt defaut 230v
long ct3t_total = (ct3t_nbr[0] + ct3t_nbr[1] + ct3t_nbr[2] + ct3t_nbr[3] + ct3t_nbr[4] + ct3t_nbr[5] + ct3t_nbr[6] + ct3t_nbr[7] + ct3t_nbr[8]) * 4;
/*					select type 4													*/
long temps_clio[9];
long ct_ECL_nbr[9] = { 0, 1000, 0, 2000, 0, 2000, 0, 2000, 200 };  // temps clio defaut batt defaut 230v
long ct_ECL_total = (ct_ECL_nbr[0] + ct_ECL_nbr[1] + ct_ECL_nbr[2] + ct_ECL_nbr[3] + ct_ECL_nbr[4] + ct_ECL_nbr[5] + ct_ECL_nbr[6] + ct_ECL_nbr[7] + ct_ECL_nbr[8]) * 4;
/*					select type 5													*/
long ct_FAN_nbr[9] = { 1000, 1000, 500, 800, 400, 600, 300, 400, 100 };  // temps clio defaut batt defaut 230v
long ct_FAN_total = (ct_FAN_nbr[0] + ct_FAN_nbr[1] + ct_FAN_nbr[2] + ct_FAN_nbr[3] + ct_FAN_nbr[4] + ct_FAN_nbr[5] + ct_FAN_nbr[6] + ct_FAN_nbr[7] + ct_FAN_nbr[8]) * 4;
/*					select type 6													*/
long tempoECL[9];
long ct_SOS_nbr[9] = { 10, 100, 100, 0, 0, 0, 0, 0, 100 };  // temps clio defaut batt defaut 230v
long ct_SOS_total = (ct_SOS_nbr[0] + ct_SOS_nbr[1] + ct_SOS_nbr[2] + ct_SOS_nbr[3] + ct_SOS_nbr[4] + ct_SOS_nbr[5] + ct_SOS_nbr[6] + ct_SOS_nbr[7] + ct_SOS_nbr[8]) * 4;
/*					select type 7													*/
long ct_SOS1_nbr[9] = { 10, 1000, 1000, 0, 0, 0, 0, 0, 100 };  // temps clio defaut batt defaut 230v
long ct_SOS1_total = (ct_SOS1_nbr[0] + ct_SOS1_nbr[1] + ct_SOS1_nbr[2] + ct_SOS1_nbr[3] + ct_SOS1_nbr[4] + ct_SOS1_nbr[5] + ct_SOS1_nbr[6] + ct_SOS1_nbr[7] + ct_SOS1_nbr[8]) * 4;
int sos_niveau_2 = 0;
/*					select type 8													*/
long ct_GEN_nbr[9] = { 10, 1000, 1000, 0, 0, 0, 0, 0, minut };  // temps clio defaut batt defaut 230v
long ct_GEN_total = (ct_GEN_nbr[0] + ct_GEN_nbr[1] + ct_GEN_nbr[2] + ct_GEN_nbr[3] + ct_GEN_nbr[4] + ct_GEN_nbr[5] + ct_GEN_nbr[6] + ct_GEN_nbr[7] + ct_GEN_nbr[8]) * 4;

/*
chf_cyl chf_cyl_sos
1 ct1t_nbr
2 ct2t_nbr
3 ct3t_nbr
4 ct_ECL_nbr
5 ct_FAN_nbr
6 ct_SOS_nbr
7 ct_SOS1_nbr
*/


//------chiffre type
int selc_ECL[9]{ 60, 1, 60, 1, 60, 1, 60, 2, 4 };			//  selc 0
int selc_aut[9]{ 91, 1, 0, 1, 0, 1, 0, 1, 1 };				//  selc 1
int selc_bat[9]{ 91, 2, 91, 1, 1, 1, 81, 1, 1 };			//  selc 2
int selc_230[9]{ 92, 3, 82, 1, 1, 1, 1, 1, 3 };				//  selc 3
int selc_ne_te[9]{ 3, 3, 61, 1, 4, 4, 71, 2, 2 };			//  selc 4
int selc_ph_te[9]{ 2, 2, 61, 1, 4, 4, 71, 2, 2 };			//  selc 5
int selc_ph_ne[9]{ 2, 2, 60, 1, 3, 3, 60, 2, 2 };			//  selc 6
int selc_cc_tst[9]{ 5, 1, 61, 1, 5, 1, 62, 2, 2 };			//  selc 7
int selc_cc_cc[9]{ 5, 5, 71, 1, 5, 5, 72, 2, 3 };			//  selc 8
int selc_FAN_d[9]{ 50, 1, 50, 1, 50, 1, 50, 2, 5 };			//  selc 9
int selc_SOS[9]{ 60, 3, 0, 1, 0, 1, 0, 1, 6 };				//  selc 10
int selc_SOS1[9]{ 60, 3, 0, 1, 0, 1, 0, 1, 7 };				//  selc 11
int selc_aut_veil[9]{ 82, 1, 81, 1, 82, 1, 81, 1, 3 };		//  selc 12
int selc_GEN_SYS[9]{ 82, 1, 81, 1, 82, 1, 81, 1, 8 };		//  selc 13

int chf_cyl[9]{};
/*						0 sortie      1 chr
					   1 nbr         1 chr
					   2 sortie      2 chr
					   3 nbr         2 chr
					   4 sortie      3 chr
					   5 nbr         3 chr
					   6 sortie      4 chr
					   7 nbr         4 chr
					   8 selec type clio
*/
int chf_cyl_sos[9]{};
int selc_FAN[9]{};
int tempo[9]{};//selec tempo fan
long tempo_total = (sec * 10) + ct_ECL_total;

int compteurchf1 = 0;
int compteurchf2 = 0;
int compteurspot1 = 0;
int compteurspot2 = 0;

int compteurECL = 0;
int compteurFAN = 0;
int sequanceECL = 0;
int sequanceFAN = 0;
unsigned long compteFANMillis1 = 0;
unsigned long compteFANMillis2 = 0;
unsigned long compteECLMillis1 = 0;
unsigned long compteECLMillis2 = 0;
int compt_alim_off = 0;
int niveau = 0;// fan fonction
int niveauECL = 0;
//unsigned long tempo = 0;//

int sys_etat = 30;									// init valeur
int sys_etat_prew = 30;

int get_temp_sys = 0;
int get_lux_sys = 0;
bool SYS_SURCHAUFFE = false;
bool temp_sys = false;
bool lux_env = false;
//						variables GENERATEUR 230v
bool GENERATEUR_230v_stat = false;
long gen_debut = millis();
long gen_tmp_230 = 2 * minut;

//						SYS_ARRET
int sys_clio_arret_tempo_compt = 0;
int sys_clio_arret_compt = 0;
unsigned long sys_arret_millis_1 = millis();
unsigned long clio_arret_millis = millis();
bool clio_arret_stat = false;

unsigned long clio_arret_tempo_millis = millis();
bool clio_arret_tempo_stat = false;

void setup() {
	Serial.begin(115200);
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
	//pinMode(welc_ctr_in, INPUT_PULLUP);
}

// the loop function runs over and over again until power down or reset
void loop()
{
	getBattery();
	sys_temp_lux();
	sys_inital();
	sys_veille();// loop init
}  //				fin loop

/*--------------etat system

				1	gen test en cours
				2	gen test attente test
				3	battLow -20%
				4	getAlim defaut
				5	tempo attente off
				6	batt 0ff
				7	suchauffe systeme
				8	generateur 230v en cours
				30	init sys
				20	veille sys_ok
				21	generateur 230v fin
				22	gen test fin
				23	veille sys_ok fin
				24	veille sys_defaut
				25	veille sys_defaut fin
				26	detection mode en cours

*/
/*--------------getAlim code option fonction

	getAlim(**)	1	alim en cours
				2	alim en cours
				20	alim arret
				30	alim test ok-->en pause

	sys_etat 	30		alim test initial
				6 || 7	alim arret
				20		alim veille test --> 5 sec

*/
/*--------------fan code option fonction

	fan(**)		1	fan sequence normal || battLow sequence +1minut en cours
				2	fan sequence surchauffe impulsion 10sec/1minut en cours
				20	fan arret

*/
/*------------------clio_normal code option fonction

 clio_normal(**)	1	clio batt off !spot - fl.Bleu - fl.Rouge - sirenC
					2	clio alim off !spot - fl.Rouge - sirenI
					3	clio surchauf !spot - fl.Bleu - fl.Rouge - sirenC - sirenI
					4	detection mode
					20	clio arret
*/

void sys_inital()
{
	if (alim_tst == false)
	{
		getAlim(30);
	}
	if (battOff == true)
	{
		sys_etat = 6;								// batt off
		getAlim(sys_etat);
		return;
	}
	if (battLow_prew != battLow || sys_etat_prew != sys_etat)
	{
		battLow_prew = battLow;
		sys_etat_prew = sys_etat;
		sys_raz(sys_etat);									// defaut - batt - alim - ch.sys_etat
	}
	if (SYS_SURCHAUFFE == true)  //				ARRET SYSTEME MISE EN VEILLE
	{
		sys_etat = 7;								// sys surchauffe
		getAlim(sys_etat);
		fan_fonct(2);
		sys_raz(sys_etat);									// sys surchauffe
		return;
	}
}
void sys_temp_lux() {
	get_temp_sys = analogRead(temrat);
	get_lux_sys = analogRead(photo);
	if (get_temp_sys >= 150) {
		temp_sys = true;
	}
	else
	{
		temp_sys = false;
	}

	if (get_lux_sys >= 10) {
		lux_env = true;
	}
	else
	{
		lux_env = false;
	}

	if (get_temp_sys >= 250)  // ARRET SYSTEME
	{
		SYS_SURCHAUFFE = true;
	}
	else
	{
		SYS_SURCHAUFFE = false;
	}
	if (SYS_SURCHAUFFE == true)
	{
		if (temp_sys == false)
		{
			SYS_SURCHAUFFE = false;
		}
	}
}
void GENERATEUR_230v()
{
	GENERATEUR_230v_stat = true;
	gen_debut = millis();
	while (GENERATEUR_230v_stat == true)
	{
		getBattery();
		sys_temp_lux();
		sys_inital();
		if (battOff == true || SYS_SURCHAUFFE == true)
		{
			return;
		}
		sys_etat = 8;								// generateur en cours
		sys_clio_4t(13);							// generateur en cours
		if (millis() - gen_debut <= gen_tmp_230)
		{
			GENERATEUR_230v_stat = true;
			getAlim(1);
			if (lux_env == true)
			{
				selc_mode_clio(0, 2);
				ecl_fonct(0);
			}
			else
			{
				ecl_fonct(20);
			}
		}
		else
		{
			GENERATEUR_230v_stat = false;
			getAlim(20);
			ecl_fonct(20);
		}
		digitalWrite(bosch, GENERATEUR_230v_stat);
	}
	sys_etat = 21;									// sortie generateur 230v
}
void gen_tst()
{
	while (tempo_State_On == true)
	{
		getBattery();
		sys_temp_lux();
		sys_inital();
		if (battOff == true || SYS_SURCHAUFFE == true)
		{
			return;
		}
		getAlim(1);
		CcPhNeTe = test();
		if (CcPhNeTe_prew != CcPhNeTe)
		{
			CcPhNeTe_prew = CcPhNeTe;
			sys_raz(sys_etat);								// gent_test ch. ccphnete
		}
		sys_clio_4t(CcPhNeTe);
		if (CcPhNeTe >= 4 && CcPhNeTe <= 8)	/*	TEST  EN COURS	CcPhNeTe 4-8	*/
		{
			sys_etat = 1;								// gen_test en cours
			debut = millis();
		}
		else								/*	TEST  EN COURS	CcPhNeTe 0		*/
		{
			manu_auto_tempo();
			if (battLow == false && alim_State == true)
			{
				sys_etat = 2;						// gen_test en cours ccphnete=0
				if (lux_env == true)
				{
					selc_mode_clio(0, 2);
					ecl_fonct(0);
				}
				else
				{
					ecl_fonct(20);
				}
			}
			if ((battLow == true && battOff == false) || alim_State == false)
			{
				selc_mode_clio(10, 2);
				ecl_fonct(10);						// SOS
				if (battLow == true)
				{
					sys_etat = 3;					// battlow -20% gen_tst
				}
				if (alim_State == false)
				{
					sys_etat = 4;					// alim off gen_tst
				}
			}
		}
	}
	getAlim(30);
	fan_fonct(20);
	sys_etat = 22;									// sortie gen_tst
}
//------------------TEST CCPHNETE
int test()
{
	if (alim_State == false)
	{
		CcPhNeTe = 0;
		return CcPhNeTe;
	}
	detect_mode(1);
	if (CcPhNeTe == 0)
	{
		return (CcPhNeTe);
	}
	if (CcPhNeTe == 7)
	{
		unsigned long ct_total = 0;
		switch (chf_cyl[8])
		{
		case 1:
			ct_total = ct1t_total;
			break;
		case 2:
			ct_total = ct2t_total;
			break;
		case 3:
			ct_total = ct3t_total;
			break;
		}
		if (millis() - curmill >= ct_total)
		{
			CcPhNeTe = 8;  // sosNbr234()
		}
		else
		{
			CcPhNeTe = 7;  //sosNbr55()
		}
	}
	return (CcPhNeTe);
}
void detect_mode(int retour_foncf)
{
	if (retour_foncf == 2)
	{
		if (millis() - selec_mode_GEN_millis > 500)
		{
			selec_mode_GEN_millis = millis();
			getAlim(1);
		}
	}
	test_CcPhNeTe();
	switch (CcPhNeTe)
	{
	case 0:											// CcPhNeTe 0
		if (retour_foncf == 1)
		{
			return;
		}
		if (retour_foncf == 2)
		{
			if (millis() - selec_mode_GEN_millis > 1 * sec)
			{
				selec_mode_GEN_millis = millis();
				getAlim(20);
				return;
			}
		}
		break;
	case 4:											// CcPhNeTe 4 TE-NE
		if (retour_foncf == 2)
		{
			do
			{
				clio_normal(4); // detect_mode 
				test_CcPhNeTe();
				if (CcPhNeTe == 0)
				{
					getAlim(20);
					clio_normal(20);				// detect_mode
				}
			} while (CcPhNeTe != 0);
			if (CcPhNeTe == 0)
			{
				tempo_State_On = true;
				debut = millis();
				sys_etat = 1;						//generateur en cours
				gen_tst();
			}
			return;
		}
		break;
	case 5:											// CcPhNeTe 5 TE-PH
		if (retour_foncf == 2)
		{
			do
			{
				clio_normal(4); // detect_mode 
				test_CcPhNeTe();
				if (CcPhNeTe == 0)
				{
					getAlim(20);
					clio_normal(20);				// detect_mode
				}
			} while (CcPhNeTe != 0);
			if (CcPhNeTe == 0)
			{
				sys_etat = 8;						//generateur en cours
				GENERATEUR_230v();
			}
			return;
		}
		break;
	case 6:											// CcPhNeTe 6 PH-NE
		if (retour_foncf == 2)
		{
			do
			{
				clio_normal(4); // detect_mode 
				test_CcPhNeTe();
				if (CcPhNeTe == 0)
				{
					getAlim(20);
					clio_normal(20);				// detect_mode
				}
			} while (CcPhNeTe != 0);
			if (CcPhNeTe == 0)
			{
				sys_etat = 30;						//generateur en cours
				//GENERATEUR_230v();
			}
			return;
		}
		break;
	case 7:											// CcPhNeTe 7 PN-NE-TE
		if (retour_foncf == 2)
		{
			do
			{
				clio_normal(4); // detect_mode 
				test_CcPhNeTe();
				if (CcPhNeTe == 0)
				{
					getAlim(20);
					clio_normal(20);				// detect_mode
				}
			} while (CcPhNeTe != 0);
			if (CcPhNeTe == 0)
			{
				sys_etat = 30;						//generateur en cours
				sys_arret();
			}
			return;
		}
		break;
	}
}
void test_CcPhNeTe()
{
	phase = analogRead(testPh);
	neutre = analogRead(testN);
	terre = analogRead(testT);
	if (phase >= 10) { phase = true; }
	else { phase = false; }
	if (neutre >= 10) { neutre = true; }
	else { neutre = false; }
	if (terre >= 10) { terre = true; }
	else { terre = false; }
	if ((phase == false && neutre == false && terre == false) || (phase == true && neutre == false && terre == false) || (phase == false && neutre == true && terre == false) || (phase == false && neutre == false && terre == true))
	{
		CcPhNeTe = 0;
	}
	if (phase == true && neutre == true && terre == true)	// detect_PH__NE__TE
	{
		CcPhNeTe = 7;
	}
	if (phase == true && neutre == true && terre == false)	// detect_PH__NE
	{
		CcPhNeTe = 6;
	}
	if (phase == true && neutre == false && terre == true)	// detect_TE__PH
	{
		CcPhNeTe = 5;
	}
	if (phase == false && neutre == true && terre == true)	// detect_TE__NE
	{
		CcPhNeTe = 4;
	}
}
void sys_raz(int etat)				// mise a zer0
{
	digitalWrite(flacheRouge, false);
	digitalWrite(flacheBleu, false);
	digitalWrite(sirenC, false);
	digitalWrite(sirenI, false);
	if (sys_etat != 30)
	{
		digitalWrite(spot, false);
	}
	if (sys_etat != 1 && sys_etat != 2 && sys_etat != 3)
	{
		digitalWrite(alim, false);
		digitalWrite(bosch, false);
	}
	compteurchf1 = 0;
	compteurchf2 = 0;
	compteurspot1 = 0;
	compteurspot2 = 0;
	sequance = 0;
	compteurECL = 0;
	sequanceECL = 0;
	compteECLMillis1 = 0;
	compteECLMillis2 = 0;
	niveauECL = 0;
	if (CcPhNeTe != 8)
	{
		curmill = millis();
	}
	if ((sys_etat == 20 || sys_etat == 6) && SYS_SURCHAUFFE == false)
	{
		digitalWrite(fan, false);
		compteurFAN = 0;
		sequanceFAN = 0;
		compteFANMillis1 = 0;
		compteFANMillis2 = 0;
		niveau = 0;// fan fontion
	}
	if (sys_etat == 20 || sys_etat == 21 || sys_etat == 22 || sys_etat == 23 || sys_etat == 25)
	{
		veil_millis = millis();
		selec_mode_GEN_millis = millis();
	}
}
void manu_auto_tempo() {
	//            MANU_AUTO_VEILLE
	if (sys_etat == 30 || sys_etat == 8)			// init manu_auto
	{
		tempo_State_On = false;
		return;
	}
	// si BPmarcheState (off)  on
	BPmarcheState = digitalRead(BPmarche);
	Manu_auto = !BPmarcheState;
	// si tempo_State_On (off)  on
	if ((millis() - debut) <= (20 * sec))
	{
		tempo_State_On = true;
	}
	else
	{
		tempo_State_On = false;
	}
	if (tempo_State_On == true && Manu_auto == false)
	{
		long tempCycle = (20 * sec) - (millis() - debut);
		//Serial.print("temp cylce restant : ");
		tempCycle = tempCycle / sec;
		//Serial.print(tempCycle);
		//Serial.println(" s.");
	}
	if (tempo_State_On == false && Manu_auto == true)
	{
		long temp_manu = millis() / sec;
		//Serial.println("Manu  on");
		//Serial.print("temp cycle :");
		//Serial.println(temp_manu);
		debut = millis();
	}
	if (tempo_State_On == false && Manu_auto == false)
	{
		sys_etat = 5;								// tempo auto off
		// veilleFonc(tempo_State_On, BPmarcheState, battLow, batt);
	}
	if (tempo_State_On == true && Manu_auto == true)
	{
		long dbut = debut;
		long temp_manu = millis() / sec;
		//Serial.println("Manu  on");
		//Serial.print("temp cycle :");
		//Serial.println(temp_manu);
		long tempCycle = (20 * sec) - (millis() - dbut);
		//Serial.print("temp cylce restant : ");
		tempCycle = tempCycle / sec;
		//Serial.print(tempCycle);
		//Serial.println(" s.");
		debut = millis();
	}
}
//------------------SYS_VEILLE
void sys_veille()
{
	if (battOff == false && alim_tst == true && SYS_SURCHAUFFE == false)
	{
		sys_veille_sysOK();
	}
	if (battOff == true || alim_State == false || SYS_SURCHAUFFE == true)
	{
		sys_veille_sysDEFAUT();
		sys_raz(sys_etat);
	}
}
void sys_veille_sysOK()
{
	unsigned long interval_veil_1 = 5 * sec;			//	temps arret
	unsigned long interval_veil_2 = 5 * sec;			//	temps marche
	sys_etat = 20;							// veille en cours SYS_OK
	while (battOff == false && alim_tst == true && SYS_SURCHAUFFE == false)
	{
		if (millis() - debut > 5 * minut)
		{
			sys_raz(sys_etat);
			debut = millis();
			sys_arret();
		}
		getBattery();
		sys_temp_lux();
		sys_inital();
		if (selec_mode_GEN == false)
		{
			if (millis() - veil_millis >= interval_veil_1)
			{
				selec_mode_GEN = true;
				veil_millis = millis();
			}
		}
		if (selec_mode_GEN == true)
		{
			if (millis() - veil_millis >= interval_veil_2)
			{
				selec_mode_GEN = false;
				veil_millis = millis();
			}
		}
		if (selec_mode_GEN == true)
		{
			sys_etat = 26;
			sys_clio_4t(7);			//	select mode en cours gen_test || GENERATEUR 230v
			detect_mode(2);
		}
		else
		{
			sys_etat = 30;
			sys_clio_4t(20);		//	select mode en pause gen_test || GENERATEUR 230v
			if (lux_env == true)
			{
				selc_mode_clio(0, 2);
				ecl_fonct(0);
			}
			else
			{
				ecl_fonct(20);
			}
			fan_fonct(20);
		}
	}
	sys_etat = 23;									// sortie veille SYS_OK
}
void sys_veille_sysDEFAUT()
{
	byte switch_veil = 0;
	byte switch_veil_prew = 0;
	sys_etat = 24;									// veille en cours SYS_DEFAUT
	while (battOff == true || alim_tst == false || SYS_SURCHAUFFE == true)
	{
		getBattery();
		sys_temp_lux();
		if (alim_tst == false)
		{
			getAlim(30);	// init getalim
		}
		sys_inital();
		if (battOff == true)
		{
			switch_veil = 6;
		}
		if (alim_State == false)
		{
			switch_veil = 4;
		}

		if (SYS_SURCHAUFFE == true)
		{
			switch_veil = 7;
		}
		if (switch_veil_prew != switch_veil)
		{
			switch_veil_prew = switch_veil;
			//veil_millis = millis();
			sys_raz(sys_etat);								// sys_veilleDEFAUT ch.etat
		}
		switch (switch_veil)
		{
		case 5:							 // TEMPO OFF
			/*BPmarcheState = digitalRead(BPmarche);
			if (BPmarcheState == false)
			{
				tempo_State_On = true;
			}*/
			break;
		case 6:							// BATT BOSCH OFF
			selc_mode_clio(10, 2);
			ecl_fonct(10);
			sys_clio_4t(2);				// sys veille battoff
			break;
		case 4:							// ALIM 230v OFF
			selc_mode_clio(10, 2);
			ecl_fonct(10);
			sys_clio_4t(3);				// sys veille alim off
			break;
		case 7:							// SUR_CHAUFFE SYS
			getAlim(30);
			clio_normal(3);				// veille surchauffe
			if (temp_sys == true)
			{
				fan_fonct(2);			// fan marche force SYS SURCHAUFFE
			}
			else
			{
				fan_fonct(20);			// fan marche force SYS SURCHAUFFE
			}
			break;
		case 8:

			break;
		}
	}
	sys_etat = 25;									// sortie veille SYS_DEFAUT
}
void sys_arret()
{
	bool clio_state_tempo_arret = false;
	bool clio_state_arret = false;
	BPmarcheState = digitalRead(BPmarche);
	while (BPmarcheState == true)
	{
		BPmarcheState = digitalRead(BPmarche);
		clio_state_arret = clio_arret();
		clio_state_tempo_arret = clio_arret_tempo();
		if (sys_clio_arret_tempo_compt % 8 == false && sys_clio_arret_compt % 8 == true)
		{
			clio_normal(5);							//	sys arret
		}
		else
		{
			clio_normal(20);						//	sys arret
		}
		if (sys_clio_arret_tempo_compt == 1)
		{
			do
			{
				test_CcPhNeTe();
				//BPmarcheState = digitalRead(BPmarche);
				clio_state_arret = clio_arret();
				if (sys_clio_arret_compt % 2 == true)
				{
					clio_normal(3);
				}
				if (CcPhNeTe == 0)
				{
					sys_clio_arret_tempo_compt = 0;
					sys_clio_arret_compt = 0;
					clio_normal(20);				// detect_mode
				}
			} while (CcPhNeTe != 0); //while (BPmarcheState == true);
		}
	}
}
bool clio_arret()
{
	if (clio_arret_stat == false)
	{
		if (millis() - clio_arret_millis > 3 * sec)
		{
			clio_arret_millis = millis();
			clio_arret_stat = true;
		}
	}
	if (clio_arret_stat == true)
	{
		if (millis() - clio_arret_millis > 1 * sec)
		{
			clio_arret_millis = millis();
			clio_arret_stat = false;
			sys_clio_arret_compt++;
		}
	}
	return clio_arret_stat;
}
bool clio_arret_tempo()
{
	if (clio_arret_tempo_stat == false)
	{
		if (millis() - clio_arret_tempo_millis > 15 * sec)
		{
			clio_arret_tempo_millis = millis();
			clio_arret_tempo_stat = true;
		}
	}
	if (clio_arret_tempo_stat == true)
	{
		if (millis() - clio_arret_tempo_millis > 8 * sec)
		{
			clio_arret_tempo_millis = millis();
			clio_arret_tempo_stat = false;
			sys_clio_arret_tempo_compt++;
		}
	}
	return clio_arret_tempo_stat;
}
void sys_clio_4t(int ecl_defaut)
{
	if (ecl_defaut == 20)
	{
		sys_raz(sys_etat);									// sys_clio_4t arret
		return;
	}
	selc_mode_clio(ecl_defaut, 0);
	detection(ecl_defaut);
}
void clio_normal(int sys_defaut)
{
	if (state_sortie == false)
	{
		if (millis() - clio_normal_millis >= 500)
		{
			clio_normal_millis = millis();
			state_sortie = true;
		}
	}
	if (state_sortie == true)
	{
		if (millis() - clio_normal_millis >= 200)
		{
			clio_normal_millis = millis();
			state_sortie = false;
		}
	}
	switch (sys_defaut)
	{
	default:
		break;
	case 1:					// batt off
		digitalWrite(spot, !state_sortie);
		digitalWrite(flacheBleu, state_sortie);
		digitalWrite(flacheRouge, state_sortie);
		digitalWrite(sirenC, state_sortie);
		digitalWrite(sirenI, false);
		break;
	case 2:					// alim off
		digitalWrite(spot, !state_sortie);
		digitalWrite(flacheBleu, false);
		digitalWrite(flacheRouge, state_sortie);
		digitalWrite(sirenC, false);
		digitalWrite(sirenI, state_sortie);
		break;
	case 3:					// surchauffe
		digitalWrite(spot, !state_sortie);
		digitalWrite(flacheBleu, state_sortie);
		digitalWrite(flacheRouge, state_sortie);
		digitalWrite(sirenC, state_sortie);
		digitalWrite(sirenI, state_sortie);
		break;
	case 4:					// detection mode
		digitalWrite(spot, !state_sortie);
		digitalWrite(flacheBleu, false);
		digitalWrite(flacheRouge, state_sortie);
		digitalWrite(sirenC, state_sortie);
		digitalWrite(sirenI, false);
		break;
	case 5:					// detection mode
		digitalWrite(spot, !state_sortie);
		digitalWrite(flacheBleu, false);
		digitalWrite(flacheRouge, state_sortie);
		digitalWrite(sirenC, false);
		digitalWrite(sirenI, false);
		break;


	case 20:				// arret clio
		digitalWrite(spot, false);
		digitalWrite(flacheBleu, false);
		digitalWrite(flacheRouge, false);
		digitalWrite(sirenC, false);
		digitalWrite(sirenI, false);
		break;
	}
}
//------------------CONTROLE SOURCES BOSCH  230V
void getBattery()
{
	float b = analogRead(BATTERYPIN);       // valeur analogique
	float minValue = (1023 * 10.5) / 20.0;  // Arduino
	float maxValue = (1023 * 20.0) / 20.0;  // Arduino
	float moy = maxValue - minValue;
	float val = b - minValue;
	float res = val / moy;
	float pct = res * 100;					// valeur en pourcent
	batt = pct;
	if (batt >= 100)
	{
		batt = 100;
	}
	if (batt <= 0)
	{
		batt = 0;
		sys_etat = 6;								// batt off
	}
	/*
	 float volt = (((batt * (20.0 - 10.5)) / 100) + 10.5);	// valeur en Volts
	 */
	if (batt >= 3 && batt <= 20)
	{
		battLow = true;
		sys_etat = 3;								// battlow -20% getBatt
	}
	else
	{
		battLow = false;
	}
	if (batt < 3)
	{
		battOff = true;
		battLow = true;
		sys_etat = 6;								// batt off
	}
	if (batt > 2)
	{
		battOff = false;
	}
}
void getAlim(int Mar_Arr)
{
	unsigned long rlt_alim = millis() - curren_millis_alim;
	if (sys_etat == 30 || sys_etat == 6 || sys_etat == 7)				// 6-batt_off || 7-surchauffe
	{
		get_Alim_test(Mar_Arr);
		return;
	}
	if (sys_etat == 20)								// getAlim --> veille
	{
		if (alim_tst == true)
		{
			rlt_alim = millis() - curren_millis_alim;
			if (rlt_alim >= 5 * sec)
			{
				curren_millis_alim = millis();
				get_Alim_test(Mar_Arr);
				return;
			}
		}
	}
	switch (Mar_Arr)
	{
	case 1:			// alim en cours
	case 2:
		get_Alim_test(Mar_Arr);
		if (alim_tst == true)
		{
			digitalWrite(alim, true);
			if (temp_sys == true)
			{
				selc_mode_clio(9, 1);// 
				fan_fonct(1);		// fan active getAlim
			}
			else
			{
				fan_fonct(20);		// fan arret getAlim
			}
		}
		else
		{
			digitalWrite(alim, false);
			fan_fonct(20);
			sys_etat = 4;							// alim off
		}
		break;
	case 20:										// alim arret
		digitalWrite(alim, false);
		alim_State = !digitalRead(alimOk);
		alim_State_prew = alim_State;
		fan_fonct(20);								// arret ventilateur getAlim(20)
		break;
	case 30:										// alim test ok-- > en pause
		get_Alim_test(Mar_Arr);
		break;
	}
	rlt_alim = millis() - curren_millis_alim;
	if (rlt_alim > sec && alim_tst == false)
	{
		compt_alim_off++;
		curren_millis_alim = millis();
		get_Alim_test(Mar_Arr);
		if (alim_tst == false)
		{
			fan_fonct(20);							// arret ventilateur getAlim()
			sys_etat = 4;							// ALIM 230v OFF
		}
		else
		{
			selc_mode_clio(9, 1);//
			fan_fonct(1);		// active ventilateur getAlim
		}
	}
	if (compt_alim_off == 5)
	{
		sys_veille();							// alim off
	}
}
void get_Alim_test(int Mar_Arr)
{
	if (alim_tst == false)
	{
		digitalWrite(alim, true);
		alim_State = !digitalRead(alimOk);
		alim_State_prew = alim_State;
		if (Mar_Arr != 1)
		{
			digitalWrite(alim, false);
		}
	}
	if (alim_State == true)
	{
		if (Mar_Arr == 1)
		{
			digitalWrite(alim, true);
		}
		alim_tst = true;
	}
	else
	{
		alim_tst = false;
	}
}
//			cliognot CcPhNeTe
void detection(int mode_type)
{
	// compte 1 chiffre
	if (compteurchf1 < chf_cyl[1] && compteurchf2 == 0 && compteurspot1 == 0 && compteurspot2 == 0)
	{
		detection_1(chf_cyl[0], chf_cyl[1], compteurchf1, sequance);
	}
	// compte spot1 chiffre
	if (compteurchf1 == chf_cyl[1] && compteurchf2 == 0 && compteurspot1 < chf_cyl[3] && compteurspot2 == 0)
	{
		detection_1(chf_cyl[2], chf_cyl[3], compteurspot1, sequance);
	}
	// compte 2 chiffre
	if (compteurchf1 == chf_cyl[1] && compteurchf2 < chf_cyl[5] && compteurspot1 == chf_cyl[3] && compteurspot2 == 0)
	{
		detection_1(chf_cyl[4], chf_cyl[5], compteurchf2, sequance);
	}
	// compte spot2 chiffre
	if (compteurchf1 == chf_cyl[1] && compteurchf2 == chf_cyl[5] && compteurspot1 == chf_cyl[3] && compteurspot2 < chf_cyl[7])
	{
		detection_1(chf_cyl[6], chf_cyl[7], compteurspot2, sequance);
	}
	// compte remise a zero
	if (compteurchf1 == chf_cyl[1] && compteurchf2 == chf_cyl[5] && compteurspot1 == chf_cyl[3] && compteurspot2 == chf_cyl[7])
	{
		compteurchf1 = 0;
		compteurchf2 = 0;
		compteurspot1 = 0;
		compteurspot2 = 0;
		sequance = 0;
	}
}
void detection_1(int& sortie, int& nbr_compteur, int& compteur_fonc, int& sequance) {

	slc_sortie(sortie);
	compte(sequance, compteur_fonc);
	activite(sequance);
	if (compteur_fonc == nbr_compteur) {
		sequance = 0;
	}
}
void compte(int& sequance, int& compteur) {
	unsigned long resul1 = millis() - compteMillis1;
	if (resul1 >= temps_clio[0] && (sequance == 0)) {
		compteMillis1 = millis();
		sequance = 1;
	}
	resul1 = millis() - compteMillis1;
	if (resul1 >= temps_clio[1] && sequance == 1) {
		compteMillis1 = millis();
		sequance = 2;
	}
	resul1 = millis() - compteMillis1;
	if (resul1 >= temps_clio[2] && sequance == 2) {
		compteMillis1 = millis();
		sequance = 3;
	}
	resul1 = millis() - compteMillis1;
	if (resul1 >= temps_clio[3] && sequance == 3) {
		compteMillis1 = millis();
		sequance = 4;
	}
	resul1 = millis() - compteMillis1;
	if (resul1 >= temps_clio[4] && sequance == 4) {
		compteMillis1 = millis();
		sequance = 5;
	}
	resul1 = millis() - compteMillis1;
	if (resul1 >= temps_clio[5] && sequance == 5) {
		compteMillis1 = millis();
		sequance = 6;
	}
	resul1 = millis() - compteMillis1;
	if (resul1 >= temps_clio[6] && sequance == 6) {
		compteMillis1 = millis();
		sequance = 7;
	}
	resul1 = millis() - compteMillis1;
	if (resul1 >= temps_clio[7] && sequance == 7) {
		compteMillis1 = millis();
		sequance = 8;
	}
	resul1 = millis() - compteMillis1;
	if (resul1 >= temps_clio[8] && sequance == 8) {
		compteMillis1 = millis();
		sequance = 0;
		compteur++;
	}
}
//			cliognot CcPhNeTe
//			fonction commun
void slc_sortie(int sortie) {
	switch (sortie) {
	case 0:
	case 1:
		flache_b_r_s = false;
		siren_c_i = false;
		break;
	case 2:
	case 3:                       // flacheBleu,sirenC
		flache_b_r_s = flacheBleu;  // sortie 12
		siren_c_i = sirenC;         // 3 sortie siren con (continute)
		break;
	case 4:
	case 5:                        // flacheRouge,sirenI
		flache_b_r_s = flacheRouge;  // 11 sortie flacheRouge
		siren_c_i = sirenI;          // 9 sortie siren iso
		break;
	case 10:
		flache_b_r_s = spot;  // 6 sortie spot
		break;
	case 11:
		flache_b_r_s = flacheBleu;  // sortie 12
		break;
	case 12:
		flache_b_r_s = flacheRouge;  // 11 sortie flacheRouge
		break;
	case 13:

		break;
	case 50:               // fan
		flache_b_r_s = fan;  // 5 ventilateur
		siren_c_i = fan;     // 5 ventilateur
		break;
	case 60:                // spot
		flache_b_r_s = spot;  // 6 sortie spot
		siren_c_i = false;    // "<&>"
		break;
	case 611:  // spot
		sortie = 1;
		flache_b_r_s = spot;  // 6 sortie spot
		siren_c_i = false;    // "<&>"
		break;
	case 612:               // spot
		flache_b_r_s = spot;  // 6 sortie spot
		siren_c_i = false;    // "<&>"
		break;
	case 61:                // spot,sirenI
		flache_b_r_s = spot;  // 6 sortie spot
		siren_c_i = sirenI;   // 9 sortie siren iso
		break;
	case 62:                // spot,sirenI
		flache_b_r_s = spot;  // 6 sortie spot
		siren_c_i = sirenI;   // 9 sortie siren iso
		break;
	case 71:                // spot,sirenC
		flache_b_r_s = spot;  // 6 sortie spot
		siren_c_i = sirenC;   // 3 sortie siren con
		break;
	case 72:                // spot,sirenC
		flache_b_r_s = spot;  // 6 sortie spot
		siren_c_i = sirenC;   // 3 sortie siren con
		break;
	case 81:                 // sirenC
		flache_b_r_s = false;  // "<&>"
		siren_c_i = sirenC;    // 3 sortie siren con
		break;
	case 82:                 // sirenI
		flache_b_r_s = false;  // "<&>"
		siren_c_i = sirenI;    // 9 sortie siren iso
		break;
	case 91:                      // flacheBleu
		flache_b_r_s = flacheBleu;  // 12 sortie flacheBleu
		siren_c_i = false;          // "<&>"
		break;
	case 92:                       // flacheRouge
		flache_b_r_s = flacheRouge;  // 11 sortie flacheRouge
		siren_c_i = false;           // "<&>"
		break;
	}
}
void selc_mode_clio(int selection, int fonction)
{
	switch (selection)
	{
	case 0:  // eclairage ECL
		for (int i = 0; i < 9; i++)
		{
			chf_cyl[i] = selc_ECL[i];
		}
		break;
	case 1:  // temp o manu auto   off
		for (int i = 0; i < 9; i++)
		{
			chf_cyl[i] = selc_aut[i];
		}
		break;
	case 2:  // bosch             off
		for (int i = 0; i < 9; i++)
		{
			chf_cyl[i] = selc_bat[i];
		}
		break;
	case 3:  // 230v              off
		for (int i = 0; i < 9; i++)
		{
			chf_cyl[i] = selc_230[i];
		}
		break;
	case 4:  // ne_te
		for (int i = 0; i < 9; i++)
		{
			chf_cyl[i] = selc_ne_te[i];
		}
		break;
	case 5:  // ph_te
		for (int i = 0; i < 9; i++)
		{
			chf_cyl[i] = selc_ph_te[i];
		}
		break;
	case 6:  // ph_ne
		for (int i = 0; i < 9; i++)
		{
			chf_cyl[i] = selc_ph_ne[i];
		}
		break;
	case 7:  // cc_tst
		for (int i = 0; i < 9; i++)
		{
			chf_cyl[i] = selc_cc_tst[i];
		}
		break;
	case 8:  // cc_cc
		for (int i = 0; i < 9; i++)
		{
			chf_cyl[i] = selc_cc_cc[i];
		}
		break;
	case 9:  // ventilateur FAN
		for (int i = 0; i < 9; i++)
		{
			chf_cyl[i] = selc_FAN_d[i];
		}
		break;
	case 10:  // S O S
		for (int i = 0; i < 9; i++)
		{
			chf_cyl[i] = selc_SOS[i];
		}
		break;
	case 11:  // S O S 1
		for (int i = 0; i < 9; i++)
		{
			chf_cyl[i] = selc_SOS1[i];
		}
		break;
	case 12:  // VEIL AUTO OFF
		for (int i = 0; i < 9; i++)
		{
			chf_cyl[i] = selc_aut_veil[i];
		}
		break;
	case 13:  // GENERATEUR 230v
		for (int i = 0; i < 9; i++)
		{
			chf_cyl[i] = selc_GEN_SYS[i];
		}
		break;
	}
	switch (chf_cyl[8])
	{
	case 1:
		for (int i = 0; i < 9; i++)
		{
			temps_clio[i] = ct1t_nbr[i];
		}
		break;
	case 2:
		for (int i = 0; i < 9; i++)
		{
			temps_clio[i] = ct2t_nbr[i];
		}
		break;
	case 3:
		for (int i = 0; i < 9; i++)
		{
			temps_clio[i] = ct3t_nbr[i];
		}
		break;
	case 4:
		for (int i = 0; i < 9; i++)
		{
			temps_clio[i] = ct_ECL_nbr[i];
		}
		break;
	case 5:
		for (int i = 0; i < 9; i++)
		{
			temps_clio[i] = ct_FAN_nbr[i];
		}
		break;
	case 6:
		for (int i = 0; i < 9; i++)
		{
			temps_clio[i] = ct_SOS_nbr[i];
		}
		break;
	case 7:
		for (int i = 0; i < 9; i++)
		{
			temps_clio[i] = ct_SOS1_nbr[i];
		}
		break;
	case 8:
		for (int i = 0; i < 9; i++)
		{
			temps_clio[i] = ct_GEN_nbr[i];
		}
		break;
	}
	switch (fonction)
	{
	case 0:			//	sys_clio_4t
		//	chf_cyl[i]---temps_clio[i]
		break;
	case 1:			//	fan_fonct
		for (int i = 0; i < 9; i++)
		{
			selc_FAN[i] = chf_cyl[i];
			tempo[i] = temps_clio[i];
		}
		break;
	case 2:			//	ecl_fonct SOS
		for (int i = 0; i < 9; i++)
		{
			chf_cyl_sos[i] = chf_cyl[i];
			tempoECL[i] = temps_clio[i];
		}
		break;
	case 3:

		break;
	}
}
void activite(int& sequance) {
	switch (sequance) {
	case 0:
		break;
	case 1:
	case 3:
	case 5:
	case 7:
		digitalWrite(flache_b_r_s, true);
		digitalWrite(siren_c_i, true);
		break;
	case 2:
	case 4:
	case 6:
	case 8:
	case 9:
		digitalWrite(flache_b_r_s, false);
		digitalWrite(siren_c_i, false);
		break;
	}
}
//			fonction commun
//			ventilateur
void fan_fonct(int mode_type)
{
	unsigned long resul_fan = 0;
	unsigned long rlt_fan = 0;
	long interval1 = 10 * sec;
	long interval2 = 1 * minut;
	unsigned long fan_tempo = 0;
	if (mode_type == 1)
	{
		if (temp_sys == true)
		{
			if (battLow == true)
			{
				mode_type = 1;
				fan_tempo = (1 * minut) + ct_FAN_total;
			}
			else
			{
				mode_type = 1;
				fan_tempo = 0;
			}
		}
	}
	if (SYS_SURCHAUFFE == true)
	{
		mode_type = 2;
	}
	switch (mode_type)
	{
	case 20:
		digitalWrite(fan, false);
		return;
		break;
	case 1:
		// compte 1 chiffre
		if (compteurFAN < selc_FAN[1] && niveau == 0) {
			fan_fonct_1(selc_FAN[0], selc_FAN[1], compteurFAN, sequanceFAN);
			if (compteurFAN == selc_FAN[1]) {
				compteurFAN = 0;
				niveau = 1;
			}
		}
		// compte spot1 chiffre
		if (compteurFAN < selc_FAN[3] && niveau == 1) {
			fan_fonct_1(selc_FAN[2], selc_FAN[3], compteurFAN, sequanceFAN);
			if (compteurFAN == selc_FAN[3]) {
				compteurFAN = 0;
				niveau = 2;
			}
		}
		// compte 2 chiffre
		if (compteurFAN < selc_FAN[5] && niveau == 2) {
			fan_fonct_1(selc_FAN[4], selc_FAN[5], compteurFAN, sequanceFAN);
			if (compteurFAN == selc_FAN[5]) {
				compteurFAN = 0;
				niveau = 3;
			}
		}
		// compte spot2 chiffre
		if (compteurFAN < selc_FAN[7] && niveau == 3) {
			fan_fonct_1(selc_FAN[6], selc_FAN[7], compteurFAN, sequanceFAN);
			if (compteurFAN == selc_FAN[7]) {
				compteurFAN = 0;
				niveau = 4;
			}
		}
		// compte remise a zero
		if (compteurFAN == selc_FAN[7] && niveau == 4) {
			//compteurFAN = 0;
			//niveau = 0;
			//sequanceFAN = 0;
		}
		resul_fan = millis() - compteFANMillis2;
		if (niveau == 4 && resul_fan >= fan_tempo)
		{
			compteFANMillis2 = millis();
			compteFANMillis1 = 0;
			compteurFAN = 0;
			niveau = 0;
			sequanceFAN = 0;
		}
		break;
	case 2:
		if (fan_state == false)
		{
			rlt_fan = millis() - fan_millis;
			if (rlt_fan >= interval1)
			{
				fan_millis = millis();
				fan_state = true;
			}
		}
		if (fan_state == true)
		{
			rlt_fan = millis() - fan_millis;
			if (rlt_fan >= interval2)
			{
				fan_millis = millis();
				fan_state = false;
			}
		}
		digitalWrite(fan, fan_state);
		break;
	}
}
void fan_fonct_1(int& sortie1, int& nbr_compteur1, int& compteurFAN, int& sequanceFAN)
{
	slc_sortie(sortie1);
	compte_fan_fonct(sequanceFAN, compteurFAN);
	activite(sequanceFAN);
	if (compteurFAN == nbr_compteur1)
	{
		sequanceFAN = 0;
	}
}
void compte_fan_fonct(int& sequanceFAN, int& compteurFAN)
{
	unsigned long resul1 = millis() - compteFANMillis1;
	if (resul1 >= tempo[0] && (sequanceFAN == 0))
	{
		compteFANMillis1 = millis();
		sequanceFAN = 1;
	}
	resul1 = millis() - compteFANMillis1;
	if (resul1 >= tempo[1] && sequanceFAN == 1)
	{
		compteFANMillis1 = millis();
		sequanceFAN = 2;
	}
	resul1 = millis() - compteFANMillis1;
	if (resul1 >= tempo[2] && sequanceFAN == 2)
	{
		compteFANMillis1 = millis();
		sequanceFAN = 3;
	}
	resul1 = millis() - compteFANMillis1;
	if (resul1 >= tempo[3] && sequanceFAN == 3)
	{
		compteFANMillis1 = millis();
		sequanceFAN = 4;
	}
	resul1 = millis() - compteFANMillis1;
	if (resul1 >= tempo[4] && sequanceFAN == 4)
	{
		compteFANMillis1 = millis();
		sequanceFAN = 5;
	}
	resul1 = millis() - compteFANMillis1;
	if (resul1 >= tempo[5] && sequanceFAN == 5)
	{
		compteFANMillis1 = millis();
		sequanceFAN = 6;
	}
	resul1 = millis() - compteFANMillis1;
	if (resul1 >= tempo[6] && sequanceFAN == 6)
	{
		compteFANMillis1 = millis();
		sequanceFAN = 7;
	}
	resul1 = millis() - compteFANMillis1;
	if (resul1 >= tempo[7] && sequanceFAN == 7)
	{
		compteFANMillis1 = millis();
		sequanceFAN = 8;
	}
	resul1 = millis() - compteFANMillis1;
	if (resul1 >= tempo[8] && sequanceFAN == 8)
	{
		compteFANMillis1 = millis();
		sequanceFAN = 0;
		compteurFAN++;
	}
}
//			ventilateur
//			Eclairage
void ecl_fonct(int mode_type)
{
	unsigned long resul_ecl;
	unsigned long resul_ecl_tot = 0;

	if (mode_type == 20)
	{
		digitalWrite(spot, false);
		return;
	}
	//					compte 1 chiffre
	if (compteurECL < chf_cyl_sos[1] && niveauECL == 0)
	{
		ecl_fonct_1(chf_cyl_sos[0], chf_cyl_sos[1], compteurECL, sequanceECL);
		if (compteurECL == chf_cyl_sos[1])
		{
			compteurECL = 0;
			niveauECL = 1;
		}
	}
	//					compte spot1 chiffre
	if (compteurECL < chf_cyl_sos[3] && niveauECL == 1)
	{
		ecl_fonct_1(chf_cyl_sos[2], chf_cyl_sos[3], compteurECL, sequanceECL);
		if (compteurECL == chf_cyl_sos[3])
		{
			compteurECL = 0;
			niveauECL = 2;
		}
	}
	//					compte 2 chiffre
	if (compteurECL < chf_cyl_sos[5] && niveauECL == 2)
	{
		ecl_fonct_1(chf_cyl_sos[4], chf_cyl_sos[5], compteurECL, sequanceECL);
		if (compteurECL == chf_cyl_sos[5])
		{
			compteurECL = 0;
			niveauECL = 3;
		}
	}
	//					compte spot2 chiffre
	if (compteurECL < chf_cyl_sos[7] && niveauECL == 3)
	{
		ecl_fonct_1(chf_cyl_sos[6], chf_cyl_sos[7], compteurECL, sequanceECL);
		if (compteurECL == chf_cyl_sos[7])
		{
			compteurECL = 0;
			niveauECL = 4;
		}
	}

	//					compte remise a zero
	if (compteurECL == chf_cyl_sos[7] && niveauECL == 4)
	{
		//compteurECL = 0;
		//niveauECL = 0;
		//sequanceECL = 0;
	}
	resul_ecl = millis() - compteECLMillis2;
	/*if (sos_niveau_2 == 0)
	  {
		  resul_ecl_tot = resul_ecl;
	  }
	  if (sos_niveau_2 == 1)
	  {
		  resul_ecl_tot = resul_ecl;
	  }*/
	if (niveauECL == 4 && resul_ecl > tempo_total)
	{
		compteECLMillis2 = millis();
		compteECLMillis1 = 0;
		compteurECL = 0;
		niveauECL = 0;
		sequanceECL = 0;
		if (sos_niveau_2 == 1)
		{
			sos_niveau_2 = 0;
			return;
		}
		if (sos_niveau_2 == 0)
		{
			sos_niveau_2 = 1;
			return;
		}
	}
}
void ecl_fonct_1(int& sortie2, int& nbr_compteur2, int& compteurECL, int& sequanceECL) {
	slc_sortie(sortie2);
	compte_ecl_fonct(sequanceECL, compteurECL);
	activite(sequanceECL);
	if (compteurECL == nbr_compteur2) {
		sequanceECL = 0;
	}
}
void compte_ecl_fonct(int& sequanceECL, int& compteurECL) {
	unsigned long resul1ECL = millis() - compteECLMillis1;
	if (resul1ECL >= tempoECL[0] && (sequanceECL == 0)) {
		compteECLMillis1 = millis();
		sequanceECL = 1;
	}
	resul1ECL = millis() - compteECLMillis1;
	if (resul1ECL >= tempoECL[1] && sequanceECL == 1) {
		compteECLMillis1 = millis();
		sequanceECL = 2;
	}
	resul1ECL = millis() - compteECLMillis1;
	if (resul1ECL >= tempoECL[2] && sequanceECL == 2) {
		compteECLMillis1 = millis();
		sequanceECL = 3;
	}
	resul1ECL = millis() - compteECLMillis1;
	if (resul1ECL >= tempoECL[3] && sequanceECL == 3) {
		compteECLMillis1 = millis();
		sequanceECL = 4;
	}
	resul1ECL = millis() - compteECLMillis1;
	if (resul1ECL >= tempoECL[4] && sequanceECL == 4) {
		compteECLMillis1 = millis();
		sequanceECL = 5;
	}
	resul1ECL = millis() - compteECLMillis1;
	if (resul1ECL >= tempoECL[5] && sequanceECL == 5) {
		compteECLMillis1 = millis();
		sequanceECL = 6;
	}
	resul1ECL = millis() - compteECLMillis1;
	if (resul1ECL >= tempoECL[6] && sequanceECL == 6) {
		compteECLMillis1 = millis();
		sequanceECL = 7;
	}
	resul1ECL = millis() - compteECLMillis1;
	if (resul1ECL >= tempoECL[7] && sequanceECL == 7) {
		compteECLMillis1 = millis();
		sequanceECL = 8;
	}
	resul1ECL = millis() - compteECLMillis1;
	if (resul1ECL >= tempoECL[8] && sequanceECL == 8) {
		compteECLMillis1 = millis();
		sequanceECL = 0;
		compteurECL++;
	}
}
//			Eclairage
