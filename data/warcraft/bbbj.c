// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("啾啾挤挤[2;37;0m[2;37;0m", ({"myzuoqi"}));        
        set("gender", "女性");                
        set("long", "啾啾挤挤[2;37;0m
它是格格时的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "bbbj");
        set("owner_name", "格格时");
        set_temp("owner", "bbbj");
        set_temp("owner_name", "格格时");
        ::setup();
}
