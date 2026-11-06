/* s02's own part of src/stage/sys/svc.c, included there at this place (scripts/objtree.py). */

/* the engine's com_dat.fac (player fuchikoma, shadow, test model, message and target sprites) as a stored
   record: built from src/stage/assets/com_dat by scripts/fac.py */
INCBIN_RODATA(d_800A0000, "build/stage/com_dat.rec");

char str_enemy_ctl2_data[20] RODATA = "..\\enemy\\ctl2\\data\\";

char str_enemy_oct_data[20] RODATA = "..\\enemy\\noct\\data\\";

char str_enemy_hou2_data[20] RODATA = "..\\enemy\\HOU2\\data\\";

char str_enemy_sel1_data[20] RODATA = "..\\enemy\\sel1\\data\\";

char str_enemy_jira_data[20] RODATA = "..\\enemy\\jira\\data\\";

char str_enemy_kira_data[20] RODATA = "..\\enemy\\kira\\data\\";

char str_enemy_mfir_data[20] RODATA = "..\\enemy\\mfir\\data\\";

char str_s02_ene_fac[12] RODATA = "s02_ene.fac";

char str_s02_dat_fac[12] RODATA = "s02_dat.fac";

char str_s02_joy_bin[12] RODATA = "s02_joy.bin";

char str_sew_apdea3[12] RODATA = "sew_apd.ea3";

char str_sew_cnf_bcf[12] RODATA = "sew_cnf.bcf";

char str_s02_stage[16] RODATA = "..\\s02\\stage\\";

char str_m02_dat_fac[12] RODATA = "m02_dat.fac";

char str_m12_joy_bin[12] RODATA = "m12_joy.bin";

char str_m12_cnf_bcf[12] RODATA = "m12_cnf.bcf";

char str_s02_miss[16] RODATA = "..\\s02\\miss\\";

char str_enemy_msgs_data[20] RODATA = "..\\enemy\\msgs\\data\\";

char str_enemy_bos2_data[20] RODATA = "..\\enemy\\bos2\\data\\";

char str_b02_ene_fac[12] RODATA = "b02_ene.fac";

char str_b02_dat_fac[12] RODATA = "b02_dat.fac";

char str_b02_joy_bin[12] RODATA = "b02_joy.bin";

char str_b12_apdea3[12] RODATA = "b12_apd.ea3";

char str_b12_cnf_bcf[12] RODATA = "b12_cnf.bcf";

char str_s02_boss[16] RODATA = "..\\s02\\boss\\";
