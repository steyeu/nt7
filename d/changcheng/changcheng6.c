// Room: /d/changcheng/changcheng6.c
// Last Modified by Lonely on Aug. 25 2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "长城");
        set("long", WHT @LONG
这里就是举世闻名的----长城。站在长城上，你可以看到四周群山
环绕，山上可以看见不少矮矮的灌木丛，但不少的树也被砍光了，很多
地方已经露出了一片片的黄土，举目望去，你脚下的长城顺着山脊象一
条巨龙般蜿蜒的向西北，向东延伸出去。
LONG
NOR );
        set("outdoors", "changcheng");
        set("exits", ([
                "northwest" :__DIR__"changcheng7.c",
                "east"      :__DIR__"changcheng5.c",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -5000);
        set("coor/y", 5000);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}
