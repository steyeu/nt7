// tufei6.c
#include <ansi.h>
inherit NPC;

void create()
{
        set_name("仙鹤花纹", ({ "picture"}) );
        set("gender", "男性" );
        set("age", 34);
        set("long",
                "这是全身都罩在黑纱中的神秘人，全身散发着一股阴森的气息。\n");
        set("max_qi", 5000);
        set("max_jing", 5000);
        set("max_neili", 5000);
        set("jiali", 500);
        set("combat_exp", 4000000);
        set("attitude", "friendly");
        set("str", 30);
        set("dex", 20);
        set("con", 20);
        set("int", 20);
        set_skill("dodge", 500);
        set_skill("unarmed",500);
        set_skill("parry", 500);
        set_skill("force",500);
        set_skill("sword", 500);
        set_skill("hand", 500);
        set_skill("cuff", 500);
        set_skill("changquan", 500);
        set_skill("sanshou", 500);
        set_skill("yunlong-shengong", 500);
        set_skill("yunlong-jian", 500);
        set_skill("yunlong-shenfa", 500);

        set("no_see", 1);
        set_weight(5);
        map_skill("force", "yunlong-shengong");
        map_skill("dodge", "yunlong-shenfa");
        map_skill("sword", "yunlong-jian");
        map_skill("parry", "yunlong-jian");
        map_skill("hand", "sanshou");
        map_skill("cuff", "changquan");
        prepare_skill("hand", "sanshou");
        prepare_skill("cuff", "changquan");
        set("chat_chance_combat", 30);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );
        setup();
}

int do_look(string arg)
{
        if( arg == "picture" && query("id", this_object()) == "picture" )
    {
            write("这是一张官府的"+query("name", this_object())+"。\n");
            destruct(this_object());
      return 1;
    }
  return 0;
}
void init()
{
        object ob,obj;
        mapping skl;
        string *skillname;
        int maxskill,j;
  ob = this_player();
        obj = this_object();
  add_action("do_look","look");
        if( !query_temp("bt_inited") && interactive(ob) && query("id", ob) == query_temp("bt_ownname", obj) )
        {
                
    maxskill=query("maxskill");
    if (!maxskill)
    {
                   skl = ob->query_skills();
                   maxskill =10;
                  if (sizeof(skl))
                  { 
                    skillname = sort_array( keys(skl), (: strcmp :) );
                          for (j=0; j<sizeof(skl); j++)
                          {
                                  if (maxskill < skl[skillname[j]])
                                          maxskill = skl[skillname[j]];
                          }
                  }
          }
                addn_temp("bt_inited", 1, obj);
                set_skill("dodge", maxskill);
                set_skill("unarmed", maxskill);
                set_skill("parry", maxskill);
                set_skill("sword", maxskill);
                set_skill("force", maxskill);
                set_skill("hand", maxskill);
                set_skill("cuff", maxskill);
                set_skill("yunlong-jian", maxskill);
                set_skill("changquan", maxskill);
                set_skill("sanshou", maxskill);
                set_skill("yunlong-shenfa", maxskill);
                set_skill("yunlong-shengong", maxskill);
                if (!present("long sword",obj))
                        carry_object("/clone/weapon/changjian")->wield();
                set("title", "替天行道", obj);
                obj->set_weight(500000);
                set_name("神秘人", ({ "shenmi ren","sr"}) );
                remove_call_out ("destroy_npc");
                call_out ("destroy_npc", 900); // 15 min
        }
        if( query("id", ob) == query_temp("bt_ownname", obj) )
        obj->kill_ob(ob);
}
void destroy_npc()
{
        message_vision(query("name", this_object())+"忽然打了个哆嗦，不由心生惧意，身形一晃，顿时混入莽莽人海之中。\n",environment(this_object()));
        destruct(this_object());
}
void die()
{
        object ob,me;
        string own;
        message_vision("$N倒在地上，死了！\n", this_object());
        ob = this_object();
        own=query_temp("bt_ownname", ob);
        if(own) me = find_player(own);
        if( me && query_temp("last_damage_from", ob) == me
         && (!query_temp("faint_by", ob) || query_temp("faint_by", ob) == me )
         && query_temp("bt_npc", ob) == query_temp("bt/npc", me) )
                        set_temp("bt/finish", 1, me);
        destruct(this_object());
}
varargs int receive_damage(string type, int damage, mixed from)
{
  if (query_leader())
   set_leader(0);
        return ::receive_damage(type,damage,from);
}