/* s10's own part of src/stage/sys/svc.c, included there at this place (scripts/objtree.py). */

/* the engine's com_dat.fac (player fuchikoma, shadow, test model, message and target sprites) as a stored
   record: built from src/stage/assets/com_dat by scripts/fac.py */
INCBIN_RODATA(d_800A0000, "build/stage/com_dat.rec");

char str_enemy_ctla_data[20] RODATA = "..\\enemy\\ctla\\data\\";

char str_enemy_dora_data[20] RODATA = "..\\enemy\\dora\\data\\";

char str_enemy_hou2_data[20] RODATA = "..\\enemy\\hou2\\data\\";

char str_enemy_mth1_data[20] RODATA = "..\\enemy\\mth1\\data\\";

char str_enemy_mfir_data[20] RODATA = "..\\enemy\\mfir\\data\\";

char str_enemy_ball_data[20] RODATA = "..\\enemy\\ball\\data\\";

char str_enemy_roi_data[20] RODATA = "..\\enemy\\troi\\data\\";

char str_enemy_msub_data[20] RODATA = "..\\enemy\\msub\\data\\";

char str_enemy_etr_data[20] RODATA = "..\\enemy\\tetr\\data\\";

char str_s10_ene_fac[12] RODATA = "s10_ene.fac";

char str_s10_dat_fac[12] RODATA = "s10_dat.fac";

char str_ofs_joy_bin[12] RODATA = "ofs_joy.bin";

char str_ofs_apdea3[12] RODATA = "ofs_apd.ea3";

char str_ofs_cnf_bcf[12] RODATA = "ofs_cnf.bcf";

char str_s10_stage[16] RODATA = "..\\s10\\stage\\";

char str_m10_dat_fac[12] RODATA = "m10_dat.fac";

char str_m41_joy_bin[12] RODATA = "m41_joy.bin";

char str_m41_cnf_bcf[12] RODATA = "m41_cnf.bcf";

char str_s10_miss[16] RODATA = "..\\s10\\miss\\";

char str_enemy_bosa_data[20] RODATA = "..\\enemy\\bosa\\data\\";

char str_enemy_msgs_data[20] RODATA = "..\\enemy\\msgs\\data\\";

char str_enemy_ctba_data[20] RODATA = "..\\enemy\\ctba\\data\\";

char str_b10_ene_fac[12] RODATA = "b10_ene.fac";

char str_b10_dat_fac[12] RODATA = "b10_dat.fac";

char str_obs_joy_bin[12] RODATA = "obs_joy.bin";

char str_obs_apdea3[12] RODATA = "obs_apd.ea3";

char str_obs_cnf_bcf[12] RODATA = "obs_cnf.bcf";

char str_s10_boss[16] RODATA = "..\\s10\\boss\\";
