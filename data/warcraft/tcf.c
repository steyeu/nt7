// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qingv"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是菜农六的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "tcf");
        set("owner_name", "菜农六");
        set_temp("owner", "tcf");
        set_temp("owner_name", "菜农六");
        ::setup();
}
