/* s05's own part of src/stage/sys/svc.c, included there at this place (scripts/objtree.py). */

/* the engine's com_dat.fac (player fuchikoma, shadow, test model, message and target sprites) as a stored
   record: built from src/stage/assets/com_dat by scripts/fac.py */
INCBIN_RODATA(d_800A0000, "build/stage/com_dat.rec");

char str_enemy_bos5_data[20] RODATA = "..\\enemy\\bos5\\data\\";

char str_enemy_msgs_data[20] RODATA = "..\\enemy\\msgs\\data\\";

char str_enemy_seaf_data[20] RODATA = "..\\enemy\\seaf\\data\\";

char str_enemy_hou1_data[20] RODATA = "..\\enemy\\hou1\\data\\";

char str_enemy_mbaz_data[20] RODATA = "..\\enemy\\mbaz\\data\\";

char str_enemy_mth2_data[20] RODATA = "..\\enemy\\mth2\\data\\";

char str_enemy_horo_data[20] RODATA = "..\\enemy\\horo\\data\\";

char str_enemy_ctl5_data[20] RODATA = "..\\enemy\\ctl5\\data\\";

char str_s05_ene_fac[12] RODATA = "s05_ene.fac";

char str_s05_dat_fac[12] RODATA = "s05_dat.fac";

char str_s05_joy_bin[12] RODATA = "s05_joy.bin";

char str_oct_apdea3[12] RODATA = "oct_apd.ea3";

char str_oct_cnf_bcf[12] RODATA = "oct_cnf.bcf";

char str_s05_stage[16] RODATA = "..\\s05\\stage\\";

char str_m05_dat_fac[12] RODATA = "m05_dat.fac";

char str_m22_joy_bin[12] RODATA = "m22_joy.bin";

char str_m22_cnf_bcf[12] RODATA = "m22_cnf.bcf";

char str_s05_miss[16] RODATA = "..\\s05\\miss\\";

char str_s05_boss[16] RODATA = "..\\s05\\boss\\";
