// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "鸟类的一种。[2;37;0m
它是摩托罗拉的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "motolora");
        set("owner_name", "摩托罗拉");
        set_temp("owner", "motolora");
        set_temp("owner_name", "摩托罗拉");
        ::setup();
}