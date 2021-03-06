// Create by BUNCH_D written by Lonely
// quester.c

#include <ansi.h>
inherit NPC;
#define PLACE          "yz"
#define TYPE           "bad"
#define WAIT_TIME      60

mapping bunch_bad = ([
	"bunch_name" : "菊花圣门",
	"id" : "juhua",
	"place" : "yz",
	"boss" : "红莲老祖",
	"place_name" : "扬州城",
	"type"  : "bad",
	]);

void create()
{
        set_name("任务使者", ({ "quester" }));
        set("gender", "男性");
        set("age", 23);
        set("long", "他是一个长得很英俊的男子，看上去风流倜傥。\n");
        set("bunch/bunch_name", bunch_bad["bunch_name"]);
        set("shen_type", -1);
        set("per", 29);
        set("combat_exp", 1000000);

        set("attitude", "peaceful");

        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 2);
}

#include <boss_bad.h>
