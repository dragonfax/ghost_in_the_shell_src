/* s08's own part of src/stage/sys/svc.c, included there at this place (scripts/objtree.py). */

/* the engine's com_dat.fac (player fuchikoma, shadow, test model, message and target sprites) as a stored
   record: built from src/stage/assets/com_dat by scripts/fac.py */
INCBIN_RODATA(d_800A0000, "build/stage/com_dat.rec");

char str_enemy_dor8_data[20] RODATA = "..\\enemy\\dor8\\data\\";

char str_enemy_oct_data[20] RODATA = "..\\enemy\\noct\\data\\";

char str_enemy_msgs_data[20] RODATA = "..\\enemy\\msgs\\data\\";

char str_enemy_ctl8_data[20] RODATA = "..\\enemy\\ctl8\\data\\";

char str_enemy_maxe_data[20] RODATA = "..\\enemy\\MAXE\\data\\";

char str_enemy_stk2_data[20] RODATA = "..\\enemy\\STK2\\data\\";

char str_enemy_msub_data[20] RODATA = "..\\enemy\\MSUB\\data\\";

char str_enemy_sel2_data[20] RODATA = "..\\enemy\\SEL2\\data\\";

char str_s08_ene_fac[12] RODATA = "s08_ene.fac";

char str_s08_dat_fac[12] RODATA = "s08_dat.fac";

char str_ume_joy_bin[12] RODATA = "ume_joy.bin";

char str_ume_apdea3[12] RODATA = "ume_apd.ea3";

char str_ume_cnf_bcf[12] RODATA = "ume_cnf.bcf";

char str_s08_stage[16] RODATA = "..\\s08\\stage\\";

char str_m08_dat_fac[12] RODATA = "m08_dat.fac";

char str_m32_joy_bin[12] RODATA = "m32_joy.bin";

char str_m32_cnf_bcf[12] RODATA = "m32_cnf.bcf";

char str_s08_miss[16] RODATA = "..\\s08\\miss\\";

char str_enemy_bos8_data[20] RODATA = "..\\enemy\\BOS8\\data\\";

char str_b08_ene_fac[12] RODATA = "b08_ene.fac";

char str_b08_dat_fac[12] RODATA = "b08_dat.fac";

char str_ubs_joy_bin[12] RODATA = "ubs_joy.bin";

char str_ubs_apdea3[12] RODATA = "ubs_apd.ea3";

char str_ubs_cnf_bcf[12] RODATA = "ubs_cnf.bcf";

char str_s08_boss[16] RODATA = "..\\s08\\boss\\";
