/*
 Name:		TIC_3_3.ino
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
bool alim_State = false;  // state alim_State
bool alim_State_prew = false;
long cur_mil = millis();         // tempo_alim_off
int BPmarche = 2;                // entree bp_marche
bool BPmarcheState = false;      // state bp_marche
bool Manu_auto = false;          // state auto_manu
bool tempo_State_On = false;     // cycle on
unsigned long debut = millis();  // temp debu t duree cycle

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
//long 5minut = minut * 5;

unsigned long curmill = millis();  // temp ccphnt

int detection_status = false;
int detection_status_prew = false;
unsigned long compteMillis1 = 0;

int sequance = 0;
int selec_type;
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
long ct_SOS1_total = (ct_SOS_nbr[0] + ct_SOS1_nbr[1] + ct_SOS1_nbr[2] + ct_SOS1_nbr[3] + ct_SOS1_nbr[4] + ct_SOS1_nbr[5] + ct_SOS1_nbr[6] + ct_SOS1_nbr[7] + ct_SOS1_nbr[8]) * 4;
int sos_niveau_2 = 0;

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
int selc_ECL[9]{ 60, 1, 60, 1, 60, 1, 60, 2, 4 };       //  selc 0
int selc_aut[9]{ 91, 1, 0, 1, 0, 1, 0, 1, 1 };          //  selc 1
int selc_bat[9]{ 91, 2, 91, 1, 1, 1, 81, 1, 1 };        //  selc 2
int selc_230[9]{ 92, 3, 82, 1, 1, 1, 1, 1, 3 };         //  selc 3
int selc_ne_te[9]{ 3, 3, 61, 1, 4, 4, 71, 2, 2 };       //  selc 4
int selc_ph_te[9]{ 2, 2, 61, 1, 4, 4, 71, 2, 2 };       //  selc 5
int selc_ph_ne[9]{ 2, 2, 60, 1, 3, 3, 60, 2, 2 };       //  selc 6
int selc_cc_tst[9]{ 5, 1, 61, 1, 5, 1, 62, 2, 2 };      //  selc 7
int selc_cc_cc[9]{ 5, 5, 71, 1, 5, 5, 72, 2, 3 };       //  selc 8
int selc_FAN[9]{ 50, 1, 50, 1, 50, 1, 50, 2, 5 };       //  selc 9
int selc_SOS[9]{ 60, 3, 0, 1, 0, 1, 0, 1, 6 };          //  selc 10
int selc_SOS1[9]{ 60, 3, 0, 1, 0, 1, 0, 1, 7 };         //  selc 11
int selc_aut_veil[9]{ 82, 1, 81, 1, 82, 1, 81, 1, 3 };  //  selc 12
int selc_GEN_SYS[9]{ 82, 1, 81, 1, 82, 1, 81, 1, 3 };   //  selc 13


int chf_cyl[9]; /*      0 sortie      1 chr
						1 nbr         1 chr
						2 sortie      2 chr
						3 nbr         2 chr
						4 sortie      3 chr
						5 nbr         3 chr
						6 sortie      4 chr
						7 nbr         4 chr
						8 selec type clio
			   */
int chf_cyl_sos[9];
int compteurchf1;
int compteurchf2;
int compteurspot1;
int compteurspot2;

int compteurECL;
int compteurFAN;
int sequanceECL = 0;
int sequanceFAN = 0;
unsigned long compteFANMillis1 = 0;
unsigned long compteFANMillis2 = 0;
unsigned long compteECLMillis1 = 0;
unsigned long compteECLMillis2 = 0;

int niveau = 0;
int niveauECL = 0;

bool maz_int = false;
bool mis_veil = false;
int etat_sys = 0;
int etat_sys_prew = 0;
/*	etat system
1 test en cours
2 sys Bsh ok 230v ok attente test
3 battLow
4 alim defaut
5 tempo attente off
6 batt 0ff
7 suchauffe systeme
*/

int get_temp_sys = 0;
int get_lux_sys = 0;
bool SYS_SUR_CHAUFFE = false;
bool temp_sys;
bool lux_env;

bool GENERATEUR_230v_stat = false;
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
void loop() {

	if (mis_veil == true)  //					VEILLE SYSTEME
	{
		veil_mis();
	}
	if (GENERATEUR_230v_stat == true)
	{
		GENERATEUR_230v();
	}
	else
	{
		init_sys();

		CcPhNeTe = test();
		if (CcPhNeTe >= 4 && CcPhNeTe <= 8) 
		{
			etat_sys = 1;
			gen_tst();
		}
		else
		{
			if (battLow == false && alim_State == true)
			{
				etat_sys = 2;
			}
		}
		/*  CcPhNeTe
			   4:Ne <-> Te
			   5:Ph <-> Te
			   6:Ph <-> Ne
			   7:Cc-Ph-Ne-Te. test
			   8:Cc_Ph_Ne_Te. cuci
		 */
		if (CcPhNeTe < 4 || CcPhNeTe > 8) {
			if ((battLow == true && battOff == false) || alim_State == false) {
				ecl_fonct(10);  // SOS
				if (battLow == true) 
				{
					etat_sys = 3;
				}
				if (alim_State == false) 
				{
					etat_sys = 4;
				}
			}
			else
			{
				ecl_fonct(2);
			}
		}
		switch (etat_sys) {
		case 1:  // ETAT SYSTEME OK TEST EN COURS
			break;
		case 2:  // ETAT SYSTEME OK ECLAIRAGE ON
			if (lux_env == true) {
				CcPhNeTe = 0;
			}
			else {
				CcPhNeTe = 1;
			}
			ecl_veil(CcPhNeTe);
			break;
		case 3:  // ETAT SYSTEME BATTLOW -20%
			CcPhNeTe = 2;
			ecl_veil(CcPhNeTe);
			break;
		case 4:  // ETAT SYSTEME ALIM 230V OFF
		case 5:  // ETAT SYSTEME TEMPO OFF
		case 6:  // ETAT SYSTEME BATT OFF
		case 7:  // ETAT SYSTEME SURCHAUFFE SYSTEME
			mis_veil = true;
			break;
		}

	}


}  //				fin loop


void init_sys() {
	manu_auto_tempo();
	getBattery();
	temp_lux_systeme();

	if (battOff == true) {
		getAlim(20);
		fan_fonct(20);
	}
	else {
		getAlim(1);
		fan_fonct(1);
	}

	if (CcPhNeTe_prew != CcPhNeTe || battLow_prew != battLow || alim_State_prew != alim_State || etat_sys_prew != etat_sys) {
		CcPhNeTe_prew = CcPhNeTe;
		battLow_prew = battLow;
		alim_State_prew = alim_State;
		etat_sys_prew = etat_sys;
		maz_int = false;
		maz_int_f();
	}

	if (SYS_SUR_CHAUFFE == true)  //				ARRET SYSTEME MISE EN VEILLE
	{
		etat_sys = 7;
		getAlim(20);
		fan_fonct(20);
		maz_int = false;
		maz_int_f();
		mis_veil = true;
		veil_mis();
	}
}

void temp_lux_systeme() {
	get_temp_sys = analogRead(temrat);
	get_lux_sys = analogRead(photo);
	if (get_temp_sys >= 150) {
		temp_sys = true;
	}
	else {
		temp_sys = false;
	}

	if (get_lux_sys >= 10) {
		lux_env = true;
	}
	else {
		lux_env = false;
	}

	if (get_temp_sys >= 250)  // ARRET SYSTEME
	{
		SYS_SUR_CHAUFFE = true;

	}
	else {
		SYS_SUR_CHAUFFE = false;
	}
}
void GENERATEUR_230v()
{
	GENERATEUR_230v_stat = true;
	digitalWrite(bosch, true);
	ecl_veil(12);
}
void gen_tst() {
	selc_mode_clio(CcPhNeTe);
	detection(CcPhNeTe);
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
	/*
	phase = analogRead(testPh);
	neutre = analogRead(testN);
	terre = analogRead(testT);
	if (phase >= 10)
	{
		phase = true;
	}
	else
	{
		phase = false;
	}
	if (neutre >= 10)
	{
		neutre = true;
	}
	else
	{
		neutre = false;
	}
	if (terre >= 10)
	{
		terre = true;
	}
	else
	{
		terre = false;
	}
	*/

	if (CcPhNeTe == 0)
	{
		return (CcPhNeTe);
	}


	if (CcPhNeTe == 7) {
		long ct_total;
		long resul_tst = millis() - curmill;
		if (CcPhNeTe == 8) { goto fin_tst_8; }
		switch (chf_cyl[8]) {
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
		if (resul_tst >= ct_total)
		{
			CcPhNeTe = 8;  // sosNbr234()
		}
		else
		{
			CcPhNeTe = 7;  //sosNbr55()
		}
	}
fin_tst_8:
	return (CcPhNeTe);
}
void maz_int_f() {
	// mise a zer0
	if (maz_int == false) {
		maz_int = true;
		digitalWrite(flacheRouge, false);
		digitalWrite(flacheBleu, false);
		digitalWrite(sirenC, false);
		digitalWrite(sirenI, false);
		digitalWrite(spot, false);
		digitalWrite(alim, false);
		digitalWrite(fan, false);
		digitalWrite(bosch, false);
		compteurchf1 = 0;
		compteurchf2 = 0;
		compteurspot1 = 0;
		compteurspot2 = 0;
		sequance = 0;
		compteurECL;
		//compteurFAN;
		sequanceECL = 0;
		//sequanceFAN = 0;
		//compteFANMillis1 = 0;
		//compteFANMillis2 = 0;
		compteECLMillis1 = 0;
		compteECLMillis2 = 0;

		niveau = 0;
		niveauECL = 0;

		detection_status = false;


		if (CcPhNeTe != 8) { curmill = millis(); }
	}
}
void manu_auto_tempo() {
	//            MANU_AUTO_VEILLE
	// si BPmarcheState (off)  on
	BPmarcheState = digitalRead(BPmarche);
	Manu_auto = !BPmarcheState;
	// si tempo_State_On (off)  on
	if ((millis() - debut) <= (20 * sec)) {
		tempo_State_On = true;
	}
	else {
		tempo_State_On = false;
	}
	if (tempo_State_On == true && Manu_auto == false) {
		long tempCycle = (20 * sec) - (millis() - debut);
		//Serial.print("temp cylce restant : ");
		tempCycle = tempCycle / sec;
		//Serial.print(tempCycle);
		//Serial.println(" s.");
	}
	if (tempo_State_On == false && Manu_auto == true) {
		long temp_manu = millis() / sec;
		//Serial.println("Manu  on");
		//Serial.print("temp cycle :");
		//Serial.println(temp_manu);
		debut = millis();
	}
	if (tempo_State_On == false && Manu_auto == false) {
		etat_sys = 5;
		mis_veil = true;
		// veilleFonc(tempo_State_On, BPmarcheState, battLow, batt);
	}
	if (tempo_State_On == true && Manu_auto == true) {
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
void veil_mis() {
	byte switch_veil;
	byte switch_veil_prew = 0;
	long veil_millis = 0;
	long rlt_veil = millis() - veil_millis;
	bool debut_tempo = false;
	mis_veil = true;
	maz_int = false;
	maz_int_f();
	veil_millis = millis();
	while (tempo_State_On == false || battOff == true || alim_State == false || SYS_SUR_CHAUFFE == true) {
		getAlim(1);
		getBattery();
		temp_lux_systeme();
		if (tempo_State_On == false) {
			switch_veil = 5;
		}
		if (battOff == true) {
			switch_veil = 6;
		}
		if (alim_State == false) {
			switch_veil = 4;
		}
		if (SYS_SUR_CHAUFFE == true) {
			switch_veil = 7;
		}
		if (switch_veil_prew != switch_veil) {
			maz_int = false;
			maz_int_f();
			rlt_veil = millis() - veil_millis;
			if (rlt_veil < sec) {
				goto fin;
			}
			else {
				switch_veil_prew = switch_veil;
				veil_millis = millis();
			}
		}
		else {
			veil_millis = millis();
		}
		switch (switch_veil) {
		case 5:  // TEMPO OFF
			switch_veil_prew = switch_veil;
			BPmarcheState = digitalRead(BPmarche);
			detect_mode(2);

			if (BPmarcheState == false)
			{
				tempo_State_On = true;
			}
			if (millis() - debut >= 5 * sec || debut_tempo == false)
			{
				ecl_veil(1);
			}

			break;
		case 6:  // BATT BOSCH OFF
			switch_veil_prew = switch_veil;

			tempo_State_On = false;
			ecl_fonct(10);

			if (millis() - debut >= 5 * sec || debut_tempo == false) {
				ecl_veil(12);
			}
			break;
		case 4:  // ALIM 230v OFF
			switch_veil_prew = switch_veil;

			tempo_State_On = false;
			ecl_fonct(10);

			if (millis() - debut >= 5 * sec || debut_tempo == false) {
				ecl_veil(12);
			}
			break;
		case 7:
			switch_veil_prew = switch_veil;
			tempo_State_On = false;
			digitalWrite(spot, true);
			digitalWrite(flacheBleu, true);
			digitalWrite(flacheRouge, true);
			digitalWrite(sirenC, true);
			digitalWrite(sirenI, true);
			digitalWrite(fan, true);
			break;
		}
	fin:
		switch_veil = switch_veil;
	}
	debut = millis();
	mis_veil = false;
	etat_sys = 0;
}
void ecl_veil(int ecl_defaut) {
	selc_mode_clio(ecl_defaut);
	detection(ecl_defaut);
}
void detect_mode(int retour_foncf)
{
	if (retour_foncf == 2)
	{
		getAlim(2);

	}

	phase = analogRead(testPh);
	neutre = analogRead(testN);
	terre = analogRead(testT);
	if (phase >= 10)
	{
		phase = true;
	}
	else
	{
		phase = false;
	}
	if (neutre >= 10)
	{
		neutre = true;
	}
	else
	{
		neutre = false;
	}
	if (terre >= 10)
	{
		terre = true;
	}
	else
	{
		terre = false;
	}
	if ((phase == false && neutre == false && terre == false) || (phase == true && neutre == false && terre == false) || (phase == false && neutre == true && terre == false) || (phase == false && neutre == false && terre == true))
	{
		if (retour_foncf == 1)
		{
			CcPhNeTe = 0;
			return;
		}
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
		if (retour_foncf == 2)
		{
			tempo_State_On = true;
			debut = millis();
			mis_veil = false;
			GENERATEUR_230v();
			return;
		}


	}
	if (phase == false && neutre == true && terre == true)	// detect_TE__NE
	{
		CcPhNeTe = 4;
		if (retour_foncf == 2)
		{
			tempo_State_On = true;
			debut = millis();
			mis_veil = false;
			gen_tst();
			return;
		}
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
	float pct = res * 100;  // valeur en pourcent
	batt = pct;
	if (batt >= 100)
	{
		batt = 100;
	}
	if (batt <= 0)
	{
		batt = 0;
		etat_sys = 6;
	}
	/*
	 float volt = (((batt * (20.0 - 10.5)) / 100) + 10.5);	// valeur en Volts
	 */
	if (batt >= 3 && batt <= 20)
	{
		battLow = true;
	}
	else
	{
		battLow = false;
	}
	if (batt < 3) 
	{
		battOff = true;
		battLow = true;
	}
	if (batt > 2)
	{
		battOff = false;
	}
}
void getAlim(int Mar_Arr) {
	long rlt_alim = millis() - cur_mil;
	if (Mar_Arr == 2)
	{
		digitalWrite(alim, true);
		alim_State = !digitalRead(alimOk);
		alim_State_prew = alim_State;
		digitalWrite(alim, alim_State);
		fan_fonct(1);
		return;
	}
	if (Mar_Arr == 20 || etat_sys == 5 || etat_sys == 6 || etat_sys == 7) {
		digitalWrite(alim, false);
		if (etat_sys != 4) {
			alim_State = true;
		}
		if (etat_sys != 7) {
			fan_fonct(20);  // arret ventilateur getAlim(20)
		}
		return;
	}
	if (alim_State == false || mis_veil == true) {
		goto alim_off;
	}

	digitalWrite(alim, true);
	alim_State = !digitalRead(alimOk);
	alim_State_prew = alim_State;
	digitalWrite(alim, alim_State);

	if (alim_State == false) {
		fan_fonct(20);  // arret ventilateur getAlim(20)
		mis_veil = true;
		etat_sys = 4;
		goto alim_off;
	}
	else {
		cur_mil = millis();
		if (battLow == true) {
			fan_fonct(52);  // active ventilateur getAlim
		}
		else {
			fan_fonct(52);  // active ventilateur getAlim
		}
		return;
	}

alim_off:
	rlt_alim = millis() - cur_mil;
	if (rlt_alim > sec && alim_State == false) {
		cur_mil = millis();
		digitalWrite(alim, true);
		alim_State = !digitalRead(alimOk);
		alim_State_prew = alim_State;
		digitalWrite(alim, alim_State);
		if (alim_State == false) {
			fan_fonct(20);  // arret ventilateur getAlim()
			mis_veil = true;
			etat_sys = 4;  // ALIM 230v OFF
		}
	}
}

//			cliognot CcPhNeTe
void detection(int mode_type) {
	/*switch (mode_type)
	  {
	  case 0: //
		  selec_type = 0;
		  break;
	  case 1: // Auto_manu
		  selec_type = 1;
		  break;
	  case 2: // Bat_BOCH
		  selec_type = 2;
		  break;
	  case 3: // 230v
		  selec_type = 3;
		  break;
	  case 4: // Ne <-> Te
		  selec_type = 4;
		  break;
	  case 5: // Ph <-> Te
		  selec_type = 5;
		  break;
	  case 6: // Ph <-> Ne
		  selec_type = 6;
		  break;
	  case 7: // Cc-Ph-Ne-Te. test
		  selec_type = 7;
		  break;
	  case 8: // Cc_Ph_Ne_Te. cuci
		  selec_type = 8;
		  break;
	  }*/

	  //selc_mode_clio(mode_type);
	detection_status = true;

	// compte 1 chiffre
	if (compteurchf1 < chf_cyl[1] && compteurchf2 == 0 && compteurspot1 == 0 && compteurspot2 == 0) {
		detection_1(chf_cyl[0], chf_cyl[1], compteurchf1, sequance);
	}
	// compte spot1 chiffre
	if (compteurchf1 == chf_cyl[1] && compteurchf2 == 0 && compteurspot1 < chf_cyl[3] && compteurspot2 == 0) {
		detection_1(chf_cyl[2], chf_cyl[3], compteurspot1, sequance);
	}
	// compte 2 chiffre
	if (compteurchf1 == chf_cyl[1] && compteurchf2 < chf_cyl[5] && compteurspot1 == chf_cyl[3] && compteurspot2 == 0) {
		detection_1(chf_cyl[4], chf_cyl[5], compteurchf2, sequance);
	}
	// compte spot2 chiffre
	if (compteurchf1 == chf_cyl[1] && compteurchf2 == chf_cyl[5] && compteurspot1 == chf_cyl[3] && compteurspot2 < chf_cyl[7]) {
		detection_1(chf_cyl[6], chf_cyl[7], compteurspot2, sequance);
	}
	// compte remise a zero
	if (compteurchf1 == chf_cyl[1] && compteurchf2 == chf_cyl[5] && compteurspot1 == chf_cyl[3] && compteurspot2 == chf_cyl[7]) {
		compteurchf1 = 0;
		compteurchf2 = 0;
		compteurspot1 = 0;
		compteurspot2 = 0;
		sequance = 0;
		detection_status = false;
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
void selc_mode_clio(int selection) {
	//if (detection_status == false)
	//{
	switch (selection) {
	case 0:  // eclairage ECL
		for (int i = 0; i < 9; i++) {
			chf_cyl[i] = selc_ECL[i];
		}
		break;
	case 1:  // temp o manu auto   off
		for (int i = 0; i < 9; i++) {
			chf_cyl[i] = selc_aut[i];
		}
		break;
	case 2:  // bosch             off
		for (int i = 0; i < 9; i++) {
			chf_cyl[i] = selc_bat[i];
		}
		break;
	case 3:  // 230v              off
		for (int i = 0; i < 9; i++) {
			chf_cyl[i] = selc_230[i];
		}
		break;
	case 4:  // ne_te
		for (int i = 0; i < 9; i++) {
			chf_cyl[i] = selc_ne_te[i];
		}
		break;
	case 5:  // ph_te
		for (int i = 0; i < 9; i++) {
			chf_cyl[i] = selc_ph_te[i];
		}
		break;
	case 6:  // ph_ne
		for (int i = 0; i < 9; i++) {
			chf_cyl[i] = selc_ph_ne[i];
		}
		break;
	case 7:  // cc_tst
		for (int i = 0; i < 9; i++) {
			chf_cyl[i] = selc_cc_tst[i];
		}
		break;
	case 8:  // cc_cc
		for (int i = 0; i < 9; i++) {
			chf_cyl[i] = selc_cc_cc[i];
		}
		break;
	case 9:  // ventilateur FAN
		for (int i = 0; i < 9; i++) {
			chf_cyl[i] = selc_FAN[i];
		}
		break;
	case 10:  // S O S
		for (int i = 0; i < 9; i++) {
			chf_cyl[i] = selc_SOS[i];
		}
		break;
	case 11:  // S O S 1
		for (int i = 0; i < 9; i++) {
			chf_cyl[i] = selc_SOS1[i];
		}
		break;
	case 12:  // VEIL AUTO OFF
		for (int i = 0; i < 9; i++) {
			chf_cyl[i] = selc_aut_veil[i];
		}
		break;
	case 13:  // GENERATEUR 230v
		for (int i = 0; i < 9; i++) {
			chf_cyl[i] = selc_GEN_SYS[i];
		}
		break;

	}

	switch (chf_cyl[8]) {
	case 1:
		for (int i = 0; i < 9; i++) {
			temps_clio[i] = ct1t_nbr[i];
		}
		break;
	case 2:
		for (int i = 0; i < 9; i++) {
			temps_clio[i] = ct2t_nbr[i];
		}
		break;
	case 3:
		for (int i = 0; i < 9; i++) {
			temps_clio[i] = ct3t_nbr[i];
		}
		break;
	case 4:
		for (int i = 0; i < 9; i++) {
			temps_clio[i] = ct_ECL_nbr[i];
		}
		break;
	case 5:
		for (int i = 0; i < 9; i++) {
			temps_clio[i] = ct_FAN_nbr[i];
		}
		break;
	case 6:
		for (int i = 0; i < 9; i++) {
			temps_clio[i] = ct_SOS_nbr[i];
		}
		break;
	case 7:
		for (int i = 0; i < 9; i++) {
			temps_clio[i] = ct_SOS1_nbr[i];
		}
		break;
	}










	//}
}
void activite(int& sequance) {
	switch (sequance) {
	case 0:
		break;
	case 1:
	case 3:
	case 5:
	case 7:
		if (GENERATEUR_230v_stat == false)
		{
			digitalWrite(flache_b_r_s, true);
			digitalWrite(siren_c_i, true);

		}
		else
		{
			digitalWrite(flacheBleu, true);
			digitalWrite(flacheRouge, true);
			digitalWrite(sirenC, true);
			digitalWrite(sirenI, true);

		}
		break;
	case 2:
	case 4:
	case 6:
	case 8:
	case 9:
		if (GENERATEUR_230v_stat == false)
		{
			digitalWrite(flache_b_r_s, false);
			digitalWrite(siren_c_i, false);

		}
		else
		{
			digitalWrite(flacheBleu, false);
			digitalWrite(flacheRouge, false);
			digitalWrite(sirenC, false);
			digitalWrite(sirenI, false);

		}
		break;
	}
}
//			fonction commun

//			ventilateur
void fan_fonct(int mode_type) {
	long resul_fan;

	if (mode_type == 20) {
		digitalWrite(fan, false);
		return;
	}
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
	if (niveau == 4 && resul_fan > (sec * 40) + ct_FAN_total) {
		compteFANMillis2 = millis();
		compteFANMillis1 = 0;
		compteurFAN = 0;
		niveau = 0;
		sequanceFAN = 0;
	}
}
void compte_fan_fonct(int& sequanceFAN, int& compteurFAN) {
	unsigned long resul1 = millis() - compteFANMillis1;
	long tempo[9]{};
	switch (selc_FAN[8]) {
	case 1:
		for (int i = 0; i < 9; i++) {
			tempo[i] = ct1t_nbr[i];
		}
		break;
	case 2:
		for (int i = 0; i < 9; i++) {
			tempo[i] = ct2t_nbr[i];
		}
		break;
	case 3:
		for (int i = 0; i < 9; i++) {
			tempo[i] = ct3t_nbr[i];
		}
		break;
	case 4:
		for (int i = 0; i < 9; i++) {
			tempo[i] = ct_ECL_nbr[i];
		}
		break;
	case 5:
		for (int i = 0; i < 9; i++) {
			tempo[i] = ct_FAN_nbr[i];
		}
		break;
	}
	if (resul1 >= tempo[0] && (sequanceFAN == 0)) {
		compteFANMillis1 = millis();
		sequanceFAN = 1;
	}
	resul1 = millis() - compteFANMillis1;
	if (resul1 >= tempo[1] && sequanceFAN == 1) {
		compteFANMillis1 = millis();
		sequanceFAN = 2;
	}
	resul1 = millis() - compteFANMillis1;
	if (resul1 >= tempo[2] && sequanceFAN == 2) {
		compteFANMillis1 = millis();
		sequanceFAN = 3;
	}
	resul1 = millis() - compteFANMillis1;
	if (resul1 >= tempo[3] && sequanceFAN == 3) {
		compteFANMillis1 = millis();
		sequanceFAN = 4;
	}
	resul1 = millis() - compteFANMillis1;
	if (resul1 >= tempo[4] && sequanceFAN == 4) {
		compteFANMillis1 = millis();
		sequanceFAN = 5;
	}
	resul1 = millis() - compteFANMillis1;
	if (resul1 >= tempo[5] && sequanceFAN == 5) {
		compteFANMillis1 = millis();
		sequanceFAN = 6;
	}
	resul1 = millis() - compteFANMillis1;
	if (resul1 >= tempo[6] && sequanceFAN == 6) {
		compteFANMillis1 = millis();
		sequanceFAN = 7;
	}
	resul1 = millis() - compteFANMillis1;
	if (resul1 >= tempo[7] && sequanceFAN == 7) {
		compteFANMillis1 = millis();
		sequanceFAN = 8;
	}
	resul1 = millis() - compteFANMillis1;
	if (resul1 >= tempo[8] && sequanceFAN == 8) {
		compteFANMillis1 = millis();
		sequanceFAN = 0;
		compteurFAN++;
	}
}
void fan_fonct_1(int& sortie1, int& nbr_compteur1, int& compteurFAN, int& sequanceFAN) {
	slc_sortie(sortie1);
	compte_fan_fonct(sequanceFAN, compteurFAN);
	activite(sequanceFAN);
	if (compteurFAN == nbr_compteur1) {
		sequanceFAN = 0;
	}
}
//			ventilateur

//			Eclairage
void ecl_fonct(int mode_type) {
	long resul_ecl;
	long resul_ecl_tot = 0;
	long tempo_total = (sec * 10) + ct_ECL_total;

	if (mode_type == 20) {
		digitalWrite(spot, false);
		return;
	}
	//					selc_mode_clio(mode_type);
	switch (mode_type) {
	case 0:  // eclairage ECL
		for (int i = 0; i < 9; i++) {
			chf_cyl_sos[i] = selc_ECL[i];
		}
		break;
	case 1:  // temp o manu auto   off
		for (int i = 0; i < 9; i++) {
			chf_cyl_sos[i] = selc_aut[i];
		}
		break;
	case 2:  // bosch             off
		for (int i = 0; i < 9; i++) {
			chf_cyl_sos[i] = selc_bat[i];
		}
		break;
	case 3:  // 230v              off
		for (int i = 0; i < 9; i++) {
			chf_cyl_sos[i] = selc_230[i];
		}
		break;
	case 4:  // ne_te
		for (int i = 0; i < 9; i++) {
			chf_cyl_sos[i] = selc_ne_te[i];
		}
		break;
	case 5:  // ph_te
		for (int i = 0; i < 9; i++) {
			chf_cyl_sos[i] = selc_ph_te[i];
		}
		break;
	case 6:  // ph_ne
		for (int i = 0; i < 9; i++) {
			chf_cyl_sos[i] = selc_ph_ne[i];
		}
		break;
	case 7:  // cc_tst
		for (int i = 0; i < 9; i++) {
			chf_cyl_sos[i] = selc_cc_tst[i];
		}
		break;
	case 8:  // cc_cc
		for (int i = 0; i < 9; i++) {
			chf_cyl_sos[i] = selc_cc_cc[i];
		}
		break;
	case 9:  // ventilateur FAN
		for (int i = 0; i < 9; i++) {
			chf_cyl_sos[i] = selc_FAN[i];
		}
		break;
	case 10:
		switch (sos_niveau_2) {
		case 0:
			for (int i = 0; i < 9; i++) {
				chf_cyl_sos[i] = selc_SOS[i];
			}
			//tempo_total = (sec * 10) + ct_SOS_total;
			tempo_total = ct_SOS_total;

			break;
		case 1:
			for (int i = 0; i < 9; i++) {
				chf_cyl_sos[i] = selc_SOS1[i];
			}
			tempo_total = (sec * 10) + ct_SOS1_total;
			break;
		}


		break;
	case 11:


		break;
	}
	/*
	  switch (chf_cyl_sos[8])
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
	  }
	  */
	  //					compte 1 chiffre
	if (compteurECL < chf_cyl_sos[1] && niveauECL == 0) {
		ecl_fonct_1(chf_cyl_sos[0], chf_cyl_sos[1], compteurECL, sequanceECL);

		if (compteurECL == chf_cyl_sos[1]) {
			compteurECL = 0;
			niveauECL = 1;
		}
	}
	//					compte spot1 chiffre
	if (compteurECL < chf_cyl_sos[3] && niveauECL == 1) {
		ecl_fonct_1(chf_cyl_sos[2], chf_cyl_sos[3], compteurECL, sequanceECL);

		if (compteurECL == chf_cyl_sos[3]) {
			compteurECL = 0;
			niveauECL = 2;
		}
	}
	//					compte 2 chiffre
	if (compteurECL < chf_cyl_sos[5] && niveauECL == 2) {
		ecl_fonct_1(chf_cyl_sos[4], chf_cyl_sos[5], compteurECL, sequanceECL);

		if (compteurECL == chf_cyl_sos[5]) {
			compteurECL = 0;
			niveauECL = 3;
		}
	}
	//					compte spot2 chiffre
	if (compteurECL < chf_cyl_sos[7] && niveauECL == 3) {
		ecl_fonct_1(chf_cyl_sos[6], chf_cyl_sos[7], compteurECL, sequanceECL);
		if (compteurECL == chf_cyl_sos[7]) {
			compteurECL = 0;
			niveauECL = 4;
		}
	}

	//					compte remise a zero
	if (compteurECL == chf_cyl_sos[7] && niveauECL == 4) {
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
	if (niveauECL == 4 && resul_ecl > tempo_total) {
		compteECLMillis2 = millis();
		compteECLMillis1 = 0;
		compteurECL = 0;
		niveauECL = 0;
		sequanceECL = 0;
		if (sos_niveau_2 == 1) {
			sos_niveau_2 = 0;
			return;
		}
		if (sos_niveau_2 == 0) {
			sos_niveau_2 = 1;
			return;
		}
	}
}
void compte_ecl_fonct(int& sequanceECL, int& compteurECL) {
	unsigned long resul1ECL = millis() - compteECLMillis1;
	switch (chf_cyl_sos[8]) {
	case 1:
		for (int i = 0; i < 9; i++) {
			tempoECL[i] = ct1t_nbr[i];
		}
		break;
	case 2:
		for (int i = 0; i < 9; i++) {
			tempoECL[i] = ct2t_nbr[i];
		}
		break;
	case 3:
		for (int i = 0; i < 9; i++) {
			tempoECL[i] = ct3t_nbr[i];
		}
		break;
	case 4:
		for (int i = 0; i < 9; i++) {
			tempoECL[i] = ct_ECL_nbr[i];
		}
		break;
	case 5:
		for (int i = 0; i < 9; i++) {
			tempoECL[i] = ct_FAN_nbr[i];
		}
		break;
	case 6:
		for (int i = 0; i < 9; i++) {
			tempoECL[i] = ct_SOS_nbr[i];
		}
		break;
	case 7:
		for (int i = 0; i < 9; i++) {
			tempoECL[i] = ct_SOS1_nbr[i];
		}
		break;
	}
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
void ecl_fonct_1(int& sortie2, int& nbr_compteur2, int& compteurECL, int& sequanceECL) {
	slc_sortie(sortie2);
	compte_ecl_fonct(sequanceECL, compteurECL);
	activite(sequanceECL);
	if (compteurECL == nbr_compteur2) {
		sequanceECL = 0;
	}
}
//			Eclairage
