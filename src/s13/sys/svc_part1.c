/* s13's own part of src/stage/sys/svc.c, included there at this place (scripts/objtree.py). */

/* the engine's com_dat.fac (player fuchikoma, shadow, test model, message and target sprites) as a stored
   record: built from src/stage/assets/com_dat by scripts/fac.py */
INCBIN_RODATA(d_800A0000, "build/stage/com_dat.rec");

char str_enemy_arg_data[20] RODATA = "..\\enemy\\targ\\data\\";

char str_enemy_bosd_data[20] RODATA = "..\\enemy\\bosd\\data\\";

char str_enemy_ctlt_data[20] RODATA = "..\\enemy\\ctlt\\data\\";

char str_enemy_door_data[20] RODATA = "..\\enemy\\door\\data\\";

char str_enemy_msgs_data[20] RODATA = "..\\enemy\\msgs\\data\\";

char str_s13_ene_fac[12] RODATA = "s13_ene.fac";

char str_s13_dat_fac[12] RODATA = "s13_dat.fac";

char str_tre_joy_bin[12] RODATA = "tre_joy.bin";

char str_tre_apdea3[12] RODATA = "tre_apd.ea3";

char str_tre_cnf_bcf[12] RODATA = "tre_cnf.bcf";

char str_s13_stage[16] RODATA = "..\\s13\\stage\\";

char str_s13_miss[16] RODATA = "..\\s13\\miss\\";

char str_s13_boss[16] RODATA = "..\\s13\\boss\\";
