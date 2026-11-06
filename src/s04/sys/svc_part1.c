/* s04's own part of src/stage/sys/svc.c, included there at this place (scripts/objtree.py). */

/* the engine's com_dat.fac (player fuchikoma, shadow, test model, message and target sprites) as a stored
   record: built from src/stage/assets/com_dat by scripts/fac.py */
INCBIN_RODATA(d_800A0000, "build/stage/com_dat.rec");

char str_enemy_bos4_data[20] RODATA = "..\\enemy\\bos4\\data\\";

char str_enemy_ctl4_data[20] RODATA = "..\\enemy\\ctl4\\data\\";

char str_enemy_msgs_data[20] RODATA = "..\\enemy\\msgs\\data\\";

char str_enemy_kira_data[20] RODATA = "..\\enemy\\kira\\data\\";

char str_enemy_sea2_data[20] RODATA = "..\\enemy\\sea2\\data\\";

char str_enemy_lan2_data[20] RODATA = "..\\enemy\\lan2\\data\\";

char str_enemy_mjet_data[20] RODATA = "..\\enemy\\mjet\\data\\";

char str_enemy_flip_data[20] RODATA = "..\\enemy\\flip\\data\\";

char str_s04_ene_fac[12] RODATA = "s04_ene.fac";

char str_s04_dat_fac[12] RODATA = "s04_dat.fac";

char str_s04_joy_bin[12] RODATA = "s04_joy.bin";

char str_mrn_apdea3[12] RODATA = "mrn_apd.ea3";

char str_mrn_cnf_bcf[12] RODATA = "mrn_cnf.bcf";

char str_s04_stage[16] RODATA = "..\\s04\\stage\\";

char str_m04_dat_fac[12] RODATA = "m04_dat.fac";

char str_m21_joy_bin[12] RODATA = "m21_joy.bin";

char str_m21_cnf_bcf[12] RODATA = "m21_cnf.bcf";

char str_s04_miss[16] RODATA = "..\\s04\\miss\\";

char str_s04_boss[16] RODATA = "..\\s04\\boss\\";
