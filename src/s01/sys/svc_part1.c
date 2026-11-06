/* s01's own part of src/stage/sys/svc.c, included there at this place (scripts/objtree.py). */

/* the engine's com_dat.fac (player fuchikoma, shadow, test model, message and target sprites) as a stored
   record: built from src/stage/assets/com_dat by scripts/fac.py */
INCBIN_RODATA(d_800A0000, "build/stage/com_dat.rec");

char str_enemy_ctl1_data[20] RODATA = "..\\enemy\\ctl1\\data\\";

char str_enemy_dor1_data[20] RODATA = "..\\enemy\\dor1\\data\\";

char str_enemy_msgs_data[20] RODATA = "..\\enemy\\msgs\\data\\";

char str_enemy_ohel_data[20] RODATA = "..\\enemy\\ohel\\data\\";

char str_enemy_mth1_data[20] RODATA = "..\\enemy\\mth1\\data\\";

char str_enemy_msub_data[20] RODATA = "..\\enemy\\msub\\data\\";

char str_enemy_arka_data[20] RODATA = "..\\enemy\\arka\\data\\";

char str_s01_ene_fac[12] RODATA = "s01_ene.fac";

char str_s01_dat_fac[12] RODATA = "s01_dat.fac";

char str_bay_joy_bin[12] RODATA = "bay_joy.bin";

char str_bay_apdea3[12] RODATA = "bay_apd.ea3";

char str_bay_cnf_bcf[12] RODATA = "bay_cnf.bcf";

char str_s01_stage[16] RODATA = "..\\s01\\stage\\";

char str_m01_dat_fac[12] RODATA = "m01_dat.fac";

char str_m01_joy_bin[12] RODATA = "m01_joy.bin";

char str_m11_cnf_bcf[12] RODATA = "m11_cnf.bcf";

char str_s01_miss[16] RODATA = "..\\s01\\miss\\";

char str_enemy_bos1_data[20] RODATA = "..\\enemy\\bos1\\data\\";

char str_b01_ene_fac[12] RODATA = "b01_ene.fac";

char str_b01_dat_fac[12] RODATA = "b01_dat.fac";

char str_b01_joy_bin[12] RODATA = "b01_joy.bin";

char str_b11_apdea3[12] RODATA = "b11_apd.ea3";

char str_b11_cnf_bcf[12] RODATA = "b11_cnf.bcf";

char str_s01_boss[16] RODATA = "..\\s01\\boss\\";
