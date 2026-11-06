/* Shared by s01, s03, s07, s08, s11, s13: spark_record_draw (1 function); not yet decompiled. */

#include "stage.h"

void spark_record_draw(Object *obj) {
    s32 pos[3];
    u16 rot[3];
    s32 colour;
    u16 rz;
    s32 x;
    SparkRec *s;
    u8 *tail;
    s32 n;
    s32 y;
    u16 ry;
    u16 rx;
    s32 z;
    SparkList *list;
    s32 word;

    if (obj->vars.words[1] < 7) {
        list = &spark_list;
        x = obj->x >> 12;
        pos[0] = x;
        y = obj->y >> 12;
        pos[1] = y;
        colour = 0x60C0FF;
        z = obj->z >> 12;
        pos[2] = z;
        n = spark_count;
        rx = obj->pitch;
        rot[0] = rx;
        ry = obj->yaw;
        rot[1] = ry;
        rz = obj->roll;
        rot[2] = rz;
        word = obj->vars.words[0];
        if (n < 0xFF) {
            s = &list->items[n];
            n++;
            spark_count = n;
            *(s32 *)s->colour = colour;
            tail = spark_list_tail;
            spark_list_tail = &s->next;
            *tail = n;
            s->next = 0;
            s->x = x;
            s->y = y;
            s->z = z;
            s->unk_12 = word;
            s->yaw = ry;
            s->pitch = rx;
            s->roll = rz;
        }
    }
}
