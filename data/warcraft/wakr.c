// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火麒麟[2;37;0m[2;37;0m", ({"xiaoq"}));        
        set("gender", "男性");                
        set("long", "火麒麟[2;37;0m
它是罗捌的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wakr");
        set("owner_name", "罗捌");
        set_temp("owner", "wakr");
        set_temp("owner_name", "罗捌");
        ::setup();
}
