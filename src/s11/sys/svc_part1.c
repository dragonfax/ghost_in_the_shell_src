/* s11's own part of src/stage/sys/svc.c, included there at this place (scripts/objtree.py). */

/* the engine's com_dat.fac (player fuchikoma, shadow, test model, message and target sprites) as a stored
   record: built from src/stage/assets/com_dat by scripts/fac.py */
INCBIN_RODATA(d_800A0000, "build/stage/com_dat.rec");

char str_enemy_ctlb_data[20] RODATA = "..\\enemy\\ctlb\\data\\";

char str_enemy_dorb_data[20] RODATA = "..\\enemy\\dorb\\data\\";

char str_enemy_tnk1_data[20] RODATA = "..\\enemy\\TNK1\\data\\";

char str_enemy_jira_data[20] RODATA = "..\\enemy\\jira\\data\\";

char str_enemy_hou2_data[20] RODATA = "..\\enemy\\hou2\\data\\";

char str_enemy_arkb_data[20] RODATA = "..\\enemy\\arkb\\data\\";

char str_enemy_stk3_data[20] RODATA = "..\\enemy\\stk3\\data\\";

char str_enemy_etr_data[20] RODATA = "..\\enemy\\tetr\\data\\";

char str_s11_ene_fac[12] RODATA = "s11_ene.fac";

char str_s11_dat_fac[12] RODATA = "s11_dat.fac";

char str_dct_joy_bin[12] RODATA = "dct_joy.bin";

char str_dct_apdea3[12] RODATA = "dct_apd.ea3";

char str_dct_cnf_bcf[12] RODATA = "dct_cnf.bcf";

char str_s11_stage[16] RODATA = "..\\s11\\stage\\";

char str_m11_dat_fac[12] RODATA = "m11_dat.fac";

char str_m42_joy_bin[12] RODATA = "m42_joy.bin";

char str_m42_cnf_bcf[12] RODATA = "m42_cnf.bcf";

char str_s11_miss[16] RODATA = "..\\s11\\miss\\";

char str_enemy_bosb_data[20] RODATA = "..\\enemy\\bosb\\data\\";

char str_b11_ene_fac[12] RODATA = "b11_ene.fac";

char str_b11_dat_fac[12] RODATA = "b11_dat.fac";

char str_dbs_joy_bin[12] RODATA = "dbs_joy.bin";

char str_dbs_apdea3[12] RODATA = "dbs_apd.ea3";

char str_dbs_cnf_bcf[12] RODATA = "dbs_cnf.bcf";

char str_s11_boss[16] RODATA = "..\\s11\\boss\\";
