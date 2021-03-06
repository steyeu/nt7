#include <ansi.h>

inherit NPC;
inherit F_DEALER;

string ask_job();

int  do_cook(string arg);
int  cooking(object me);
int  halt_cooking(object me);

void create()
{
        set_name("厨娘", ({"chu niang", "chu", "niang"}));
        set("long", @LONG
她是一个看上去普普通通的厨娘，常年累月的在厨房烧菜作饭，一双
粗糙的大手，油腻的围裙，貌不惊人，可是她做的饭菜深得却是川中
一绝，为人似乎十分傲慢，看来不是一般的人物。
LONG );
        set("gender", "女性");
        set("age", 35);
        set("no_get", 0);
        set("attitude", "friendly");

        set("inquiry",([
                "job" : (: ask_job :),
                "工作" : (: ask_job :),
        ]));

        set("age", 30);

        set("str", 21);
        set("int", 22);
        set("con", 30);
        set("dex", 21);

        set("max_qi", 450);
        set("max_jing", 200);
        set("neili", 350);
        set("max_neili", 350);
        set("jiali", 30);
        set("combat_exp", 5000);
        set("score", 100);

        set_skill("force", 30);
        set_skill("dodge", 50);
        set_skill("cooking", 200);
        set_skill("chuancai-jiyi", 200);
        set_skill("unarmed", 50);

        set("vendor_goods", ({
                "/clone/misc/cailiao",
        }));

        setup();
}

void init()
{
        add_action("do_cook", "cooking");
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

string ask_job()
{
        object *uob;
        object me;
        me = this_player();
        if( query("gender", me) != "女性" )
                return "你一个大老爷们，来炒什么菜啊？";

        if( query("combat_exp", me)<100 )
                return "呦，你这点本事啊，端得动盘子么？";

        if( query("jing", me)<100 )
                return "你还是休息会儿吧，小心把身子累垮了！";

        if( query("combat_exp", me)>180000 )
                return "这位女侠，你这不是折杀小的吗！你还是去前面用餐吧！饭菜马上就好！";

        if (me->query_skill("cooking") < 30)
                return "你的炒菜手艺那么差，那里能帮我？";

        if (me->query_skill_mapped("cooking") != "chuancai-jiyi")
                return "我说你知不知道来的客人可都是吃川菜的，亮出你川菜的活儿再说！";

        if (random(30) == 0)
        {
        uob = filter_array(users(), (: query_ip_name($1) == $(query_ip_name(me)) :));
        uob=filter_array(uob,(:objectp($1) && query_temp("job/cook", $1):));

        if (sizeof(uob) > 5)
        {
                me->start_busy(180);
                return "对不起，您这个IP做炒菜工作的ID太多了！";
        }
        }

        set_temp("job/cook", 1, me);
        return "好吧,你就帮我炒菜(cooking)吧！菜在这儿，灶台在那边。";
}

int recognize_apprentice(object ob, string skill)
{
        if( query_temp("mark/厨娘", ob)<1 )
                return 0;

        if (skill != "cooking" && skill != "chuancai-jiyi")
        {
                command("say 你打住...我可只会做菜烧饭。");
                return -1;
        }

        addn_temp("mark/厨娘", -1, ob);
        return 1;
}

int accept_object(object who, object ob)
{
//      object me = this_player();

        if( query_temp("mark/厨娘", who)<1 )
                set_temp("mark/厨娘", 0, who);

        if( query("money_id", ob) && ob->value() >= 2000 )
        {
                message_vision("厨娘同意指点$N一些关于炒菜的常识和技巧。\n", who);
                addn_temp("mark/厨娘", ob->value()/50, who);
                destruct(ob);
                return 1;
        }

        command("say 虽说炒菜对闯荡江湖没什么用，我也不能白白教你"
                "啊！拿来，辛苦费纹银二十两，童叟无欺！");
        return 0;
}

int do_cook(string arg)
{
        object me;

        me = this_player();
        if (me->is_busy())
                return notify_fail("你正忙着呢，别着急。\n");

        if( !query_temp("job/cook", me) )
        {
                tell_object(me, "厨娘喝道：你要干什么？不要来捣乱，我忙着呢！\n");
                return 1;
        }

        set_temp("job/step", 1, me);
        me->start_busy((: cooking :), (: halt_cooking :));
        tell_object(me, "你拿起蔬菜，走到一边坐下，开始拣菜。\n");
        return 1;
}

int cooking(object me)
{
        string msg;
        int finish;
        int gain_exp, gain_pot, gain_money;

        if( !query_temp("job/step", me) )
                set_temp("job/step", 1, me);

        if (! living(me))
        {
                delete_temp("job/cook", me);
                delete_temp("job/step", me);
                return 0;
        }

        finish = 0;
        me->receive_damage("jing", 10);
        switch(query_temp("job/step", me) )
        {
        case 1:
                msg = "$N看看菜差不多够了，站起身来走到水盆边开始洗菜。";
                break;
        case 2:
                msg = "哗----，$N将水盆中的污水倒掉，菜也洗干净了。";
                break;
        case 3:
                msg = "$N走到灶台前开始切菜，嚓----嚓-----。";
                break;
        case 4:
        case 6:
                msg = "$N将油到入锅中，继续切菜。";
                break;
        case 5:
                msg = "油热了，冒出阵阵清烟，$N将切好的菜到入锅中！滋------";
                break;
        case 7:
                msg = "$N不断翻动锅中的菜，慢慢的，一阵香味散发出来。";
                break;
        default:
                msg = "$N在锅中加入调料，又翻动了几下，将炒好的菜铲到盘中，拿给$n。";
                finish = 1;
                break;
        }
        msg += "\n";

        if (finish)
        {
                object ob;
                msg += "$n看了$N炒的菜，又夹了两片尝了尝，满意的点点头"
                       "这是给你的报酬！你可以在我这里学点炒菜技术。\n";
                delete_temp("job/cook", me);
                delete_temp("job/step", me);
                gain_money = 60 + random(60);
                addn_temp("mark/厨娘", random(30), me);
                me->improve_skill("cooking", 10 + random(10));

                // 奖励的经验为10加20的随机数（较多）， money为100加炒菜技
                // 术的等级取随机数（较多），潜能为不超过3点，主要还是以加
                // silver为主。

                /*
                if( query("potential", me)>me->query_potential_limit() )
                        set("potential", me->query_potential_limit(), me);
                */
                ob = new("/clone/money/coin");
                ob->set_amount(gain_money);
                ob->move(this_object());

        }

        msg = replace_string(msg, "$N", "你");
        msg = replace_string(msg, "$n", name());
        tell_object(me, msg);

        if (finish)
        {
                if( query("combat_exp", me) >= 50000 )
                {
                        write(MAG "你隐隐约约的发现炒菜居然和武功有一些相通之处，真是奇妙。\n" NOR);
                        gain_exp = 5 + random(15);
                        gain_pot = gain_exp / 3;
                        /*
                        if( query("potential", me) >= me->query_potential_limit() )
                                gain_pot = 0;
                        */
                        addn("combat_exp", gain_exp, me);
                        addn("potential", gain_pot, me);
                        msg = HIC "你获得了" + chinese_number(gain_exp) +
                              "点经验";
                        if (gain_pot)
                                msg += "和" + chinese_number(gain_pot) +
                                       "点潜能。\n" NOR;
                        else
                                msg += "。\n" NOR;
                        tell_object(me,  msg);
                }
                command("givecointo"+query("id", me));
                command("drop coin");
                return 0;
        }

        addn_temp("job/step", 1, me);
        return 1;
}

int halt_cooking(object me)
{
        message_vision("$N揉揉腰部，又扭了扭，叹到："
                       "这也太难了，我还是去闯荡江湖吧！\n", me);
        delete_temp("job/cook", me);
        delete_temp("job/step", me);
        return 1;
}