inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIG "碧海残镢" NOR, ({"bihai canjue", "bihai", "canjue" }));
        set_weight(1000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "颗");
                set("value", 500000);
                set("enchase/name", "碧海残镢");
                set("enchase/point", 5);
                set("enchase/type", "medal2");
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}
