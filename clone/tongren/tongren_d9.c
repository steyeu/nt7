
#include <ansi.h>

inherit ITEM;

int is_tongren() { return 1; }
void create()
{
        set_name(YEL "冲穴铜人·阳维脉·头临泣穴" NOR, ({ "tongren d9", "tongren" }));
        set_weight(50);
        
        set("unit", "个");
        set("long", NOR + YEL "这是一个冲穴铜人，上面绘制了一些经络穴位图案，以及冲穴使用方法。\n" NOR);
        set("value", 10000);
        set("material", "steal");

        set("jingmai_name", "阳维脉");
        set("xuewei_name", "头临泣穴");
        set("chongxue_xiaoguo", "POT:200");
        set("neili_cost", "600");
        setup();
}


