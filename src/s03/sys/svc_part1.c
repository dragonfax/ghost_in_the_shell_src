/* s03's own part of src/stage/sys/svc.c, included there at this place (scripts/objtree.py). */

/* the engine's com_dat.fac (player fuchikoma, shadow, test model, message and target sprites) as a stored
   record: built from src/stage/assets/com_dat by scripts/fac.py */
INCBIN_RODATA(d_800A0000, "build/stage/com_dat.rec");

char str_enemy_bos3_data[20] RODATA = "..\\enemy\\bos3\\data\\";

char str_enemy_part_data[20] RODATA = "..\\enemy\\part\\data\\";

char str_enemy_bomb_data[20] RODATA = "..\\enemy\\bomb\\data\\";

char str_enemy_mbaz_data[20] RODATA = "..\\enemy\\mbaz\\data\\";

char str_enemy_fap2_data[20] RODATA = "..\\enemy\\fap2\\data\\";

char str_enemy_mth1_data[20] RODATA = "..\\enemy\\mth1\\data\\";

char str_enemy_hou2_data[20] RODATA = "..\\enemy\\hou2\\data\\";

char str_enemy_msgs_data[20] RODATA = "..\\enemy\\msgs\\data\\";

char str_s03_ene_fac[12] RODATA = "s03_ene.fac";

char str_s03_dat_fac[12] RODATA = "s03_dat.fac";

char str_s03_joy_bin[12] RODATA = "s03_joy.bin";

char str_cob_apdea3[12] RODATA = "cob_apd.ea3";

char str_cob_cnf_bcf[12] RODATA = "cob_cnf.bcf";

char str_s03_stage[16] RODATA = "..\\s03\\stage\\";

char str_m03_dat_fac[12] RODATA = "m03_dat.fac";

char str_m13_joy_bin[12] RODATA = "m13_joy.bin";

char str_m13_cnf_bcf[12] RODATA = "m13_cnf.bcf";

char str_s03_miss[16] RODATA = "..\\s03\\miss\\";

char str_s03_boss[16] RODATA = "..\\s03\\boss\\";
