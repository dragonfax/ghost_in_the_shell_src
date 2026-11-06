/* s07's own part of src/stage/sys/svc.c, included there at this place (scripts/objtree.py). */

/* the engine's com_dat.fac (player fuchikoma, shadow, test model, message and target sprites) as a stored
   record: built from src/stage/assets/com_dat by scripts/fac.py */
INCBIN_RODATA(d_800A0000, "build/stage/com_dat.rec");

char str_enemy_msgs_data[20] RODATA = "..\\enemy\\msgs\\data\\";

char str_enemy_ctl7_data[20] RODATA = "..\\enemy\\ctl7\\data\\";

char str_enemy_bos7_data[20] RODATA = "..\\enemy\\bos7\\data\\";

char str_enemy_mth2_data[20] RODATA = "..\\enemy\\mth2\\data\\";

char str_enemy_hou2_data[20] RODATA = "..\\enemy\\hou2\\data\\";

char str_enemy_nk2_data[20] RODATA = "..\\enemy\\tnk2\\data\\";

char str_enemy_fap2_data[20] RODATA = "..\\enemy\\fap2\\data\\";

char str_enemy_horo_data[20] RODATA = "..\\enemy\\horo\\data\\";

char str_enemy_arkb_data[20] RODATA = "..\\enemy\\arkb\\data\\";

char str_enemy_kitt_data[20] RODATA = "..\\enemy\\kitt\\data\\";

char str_s07_ene_fac[12] RODATA = "s07_ene.fac";

char str_s07_dat_fac[12] RODATA = "s07_dat.fac";

char str_cty_joy_bin[12] RODATA = "cty_joy.bin";

char str_cty_apdea3[12] RODATA = "cty_apd.ea3";

char str_cty_cnf_bcf[12] RODATA = "cty_cnf.bcf";

char str_s07_stage[16] RODATA = "..\\s07\\stage\\";

char str_m07_dat_fac[12] RODATA = "m07_dat.fac";

char str_m31_joy_bin[12] RODATA = "m31_joy.bin";

char str_m31_cnf_bcf[12] RODATA = "m31_cnf.bcf";

char str_s07_miss[16] RODATA = "..\\s07\\miss\\";

char str_s07_boss[16] RODATA = "..\\s07\\boss\\";
