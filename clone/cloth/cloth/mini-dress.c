// mini-dress.c example cloth

#include <ansi.h>

inherit EQUIP;

void create()
{
        set_name(BLU"彩缎紧身袄"NOR, ({"jinshen ao", "mini-ao", "cloth"}));
        set_weight(700);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "件");
                set("value", 2000);
                set("material", "cloth");
                set("armor_type", "cloth");
                set("armor_prop/per", 2);
                set("armor_prop/armor", 3);
                set("female_only", 1);
                set("wear_msg","$N穿上一件$n。\n");
                set("remove_msg","$将$n脱了下来。\n");
        }
}