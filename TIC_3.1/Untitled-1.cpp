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

