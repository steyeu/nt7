// lansha-shou.c 蓝砂手 药王谷
// Edit By Vin On 26/2/2001

#include <ansi.h>
inherit SKILL;
int is_pbsk() { return 1; }

mapping *action = ({
([      "action" : "$N跨前一步，双掌陡然攻出，带着丝丝阴风击向$n的$l",
        "force" : 100,
        "attack": 25,
        "dodge" : 15,
        "parry" : 20,
        "damage": 10,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N左掌护胸，右掌掌心带着极寒之气拍向$n的$l",
        "force" : 130,
        "attack": 30,
        "dodge" : 10,
        "parry" : 15,
        "damage": 20,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N双掌拍出满天阴风，忽然右掌悄无声息的拍向$n的$l",
        "force" : 180,
        "attack": 50,
        "dodge" : 20,
        "parry" : 30,
        "damage": 30,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N怪叫一声，身形一跃，左掌快若疾电般击向$n的$l",
        "force" : 210,
        "attack": 65,
        "dodge" : 25,
        "parry" : 20,
        "damage": 35,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N阴笑一声，双掌一错，右掌忽然暴长数尺击向$n的$l",
        "force" : 210,
        "attack": 65,
        "dodge" : 25,
        "parry" : 20,
        "damage": 35,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N身形急晃，一跃而至$n跟前，右掌带着冲天寒气击向$n的$l",
        "force" : 210,
        "attack": 65,
        "dodge" : 25,
        "parry" : 20,
        "damage": 35,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N仰天长啸，双掌掌风似千古不化的寒冰般扑向$n的$l",
        "force" : 210,
        "attack": 65,
        "dodge" : 25,
        "parry" : 20,
        "damage": 35,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N身法陡然一变，掌影千变万幻，令$n无法躲闪",
        "force" : 250,
        "attack": 45,
        "dodge" : 15,
        "parry" : 20,
        "damage": 25,
        "damage_type" : "瘀伤"
]),
([      "action" : "$N仰天一声狂啸，双掌携带着万古冰坚直直贯向$n",
        "force" : 330,
        "attack": 35,
        "dodge" : 25,
        "parry" : 20,
        "damage": 15,
        "damage_type" : "瘀伤"
])
});

int valid_enable(string usage) { return usage == "hand" || usage == "parry"; }

int valid_combine(string combo) { return combo == "dusha-zhang"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("练蓝砂手必须空手。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功火候不够，无法练习蓝砂手。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的内力太弱，无法练习蓝砂手。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("lansha-shou", 1))
                return notify_fail("你的基本手法水平有限，无法领会更高深的蓝砂手。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("lansha-shou",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的体力太低了。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的内力不够练蓝砂手。\n");

        me->receive_damage("qi", 40);
        addn("neili", -60, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl;
        int flvl;

        lvl  = me->query_skill("lansha-shou", 1);
        flvl=query("jiali", me);
        if (lvl < 80 || flvl < 10 || ! damage_bonus)
                return;

        if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
           victim->affect_by("sha_poison",
                ([ "level" : flvl + random(flvl),
                   "id":query("id", me),
                   "duration" : lvl / 50 + random(lvl / 20) ])))
        {
                return HIB "$n" HIB "忽然感到一股莫名的恶心，全身瘫软，嘴皮乌紫。\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"lansha-shou/" + action;
}
