




          FONCTION SYSTEM
veilleFonc - demare (fin tempo)
veilleF    - alimOffFonc + battOffFonc
f_b_cl.    - veilleF + alimOffFonc + battOffFonc
controlAlimFonc - veilleF + demare
f_r_cl.    - veilleF + veilleFonc + alimOffFonc + battOffFonc
spot_cl.   - veilleF * veilleFonc + alimOffFonc + battOffFonc + sosNbr10



          TIMER SYSTEM
demare        –>  sec*20    tempt pause
cc0 bosch low ->  sec*10    def_source
cc0 sys ok    ->  sec*5     def_1t  ||  def_3t
cc0 tempo5m   –>  minut*5   ** en attente **
GEN_mode      –>  sec*3     debut_gen_cyl
GEN_mode      –>  100m      debut_gen_inp
GEN           –>  minut*15  en cours…
GEN           –>  minut*3   def_3t
GEN           –>  minut     def_3t & def_1t


sosSay  sosSay_slc    //selection flache siren
        ecl_auto      // 0 art 1 a
        fane          // 0 art 1 s-a 51 a
        spot_cl       // 0 art 10 a
        def_1t        // sosSay_slc
        def_2t        // sosSay_slc
        def_3t        // sosSay_slc
        def_source    // sosSay_slc







        |–––––|
        |     |
        |–––––|