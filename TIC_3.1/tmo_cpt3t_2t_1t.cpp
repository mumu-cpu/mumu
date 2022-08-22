







int count_2t()
{
  unsigned long rlt2t = millis() - cpt2t_millis;

  // cycle x1
  // allum 0
  if (rlt2t > 0 && 
      ct2t_cycl_st[0] == false && 
      ct2t_cycl_st[5] == false)
  {
    cpt2t_millis = millis();
    ct2t_posi_st[0] = true;
    ct2t_cycl_st[0] = true;
    ct2t_cycl_st[5] = false;
  }
  // etein 1
  rlt2t = millis() - cpt2t_millis;
  if (rlt2t > 200 && 
      ct2t_cycl_st[0] ==  true && 
      ct2t_cycl_st[1] == false)
  {
    cpt2t_millis = millis();
    ct2t_posi_st[0] = false;
    ct2t_posi_st[1] = true;
    ct2t_cycl_st[1] = true;
  }

  // cycle x2
  // allum 2
  rlt2t = millis() - cpt2t_millis;
  if (rlt2t > 200 && 
      ct2t_cycl_st[0] == true && 
      ct2t_cycl_st[1] == true && 
      ct2t_cycl_st[2] == false
      )
  {
       cpt2t_millis = millis();
    ct2t_posi_st[1] = false;
    ct2t_posi_st[2] = true;
    ct2t_cycl_st[2] = true;
  }
  // etein 3
  rlt2t = millis() - cpt2t_millis;
  if (rlt2t > 500 && 
      ct2t_cycl_st[0] == true && 
      ct2t_cycl_st[1] == true && 
      ct2t_cycl_st[2] == true && 
      ct2t_cycl_st[3] == false
      )
  {
       cpt2t_millis = millis();
    ct2t_posi_st[2] = false;
    ct2t_posi_st[3] = true;
    ct2t_cycl_st[3] = true;
  }
  // cycle x3
  // allum 4
  rlt2t = millis() - cpt2t_millis;
  if (rlt2t > 0 && 
      ct2t_cycl_st[0] == true && 
      ct2t_cycl_st[1] == true && 
      ct2t_cycl_st[2] == true && 
      ct2t_cycl_st[3] == true && 
      ct2t_cycl_st[4] == false)
  {
       cpt2t_millis = millis();
    ct2t_posi_st[3] = false;
    ct2t_posi_st[4] = true;
    ct2t_cycl_st[4] = true;
  }
  // etein 5
  rlt2t = millis() - cpt2t_millis;
  if (rlt2t > 0 && 
      ct2t_cycl_st[0] == true && 
      ct2t_cycl_st[1] == true && 
      ct2t_cycl_st[2] == true && 
      ct2t_cycl_st[3] == true && 
      ct2t_cycl_st[4] == true && 
      ct2t_cycl_st[5] == false
      )
  {
       cpt2t_millis = millis();
    ct2t_posi_st[4] = false;
    ct2t_posi_st[5] = true;
    ct2t_cycl_st[5] = true;
}
  // fin cycle maz
  rlt2t = millis() - cpt2t_millis;
  if (rlt2t > 400 && 
      ct2t_cycl_st[0] == true && 
      ct2t_cycl_st[1] == true && 
      ct2t_cycl_st[2] == true && 
      ct2t_cycl_st[3] == true && 
      ct2t_cycl_st[4] == true && 
      ct2t_cycl_st[5] == true)
  {
    cpt2t_millis = millis();
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
    ct2t_posi_st[7]++;// compteur cycle
    if (ct2t_posi_st[7] == sosSay)
    {
      ct2t_posi_st[8]++;// compteur 
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
    int ct1t_posi_st[9] = {false, false, false, false, false, false, false, false, false};
    int ct2t_posi_st[9] = {false, false, false, false, false, false, false, false, false};
    int ct3t_posi_st[9] = {false, false, false, false, false, false, false, false, false};
        cpt1t_millis = millis();
        cpt2t_millis = millis();
        cpt3t_millis = millis();

    break;
  case 7:
    ct2t_switch = 0;
    break;
  }
int CcPhNeTe_switch=ct2t_posi_st[8];
  return (CcPhNeTe_switch);
}

