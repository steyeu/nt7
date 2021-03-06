// ITEM Made by player(西瓜:xigua) /data/item/x/xigua-yye.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sat Jan 19 08:26:01 2019
#include <ansi.h>
#include <armor.h>

inherit WRISTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("研研[2;37;0m", ({ "yye" }));
	set_weight(5000);
	set("item_make", 1);
	set("unit", "对");
	set("long", "这是由[1;35m无名之物[2;37;0m炼制而成的一对护腕。
");
	set("makeinfo", "[1;31m
西瓜(xigua)[1;31m 出品
[2;37;0m");
	set("value", 35520000);
	set("point", 442);
	set("max_consistence", 100);
	set("material", "no name");
	set("material_file", "/clone/goods/noname2");
	set("quality_level", 6);
	set("wear_msg", "[33m$N[33m装备[33m$n[33m。[2;37;0m\n");
	set("remove_msg", "[33m$N[33m脱下了[33m$n[33m。[2;37;0m\n");
	if( !check_clone() ) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/reduce_damage", 2.500000);
	set("armor_prop/research_effect", 6);
	set("armor_prop/avoid_die", 2.500000);

	setup();
}

string long() { return short() + query_makeinfo() + query("long") + item_long(); }
