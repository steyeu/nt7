// powerup.c 扶桑内功

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        mapping buff, data;
        string msg;
        int skill;

        if (target != me)
                return notify_fail("你只能用扶桑内功来提升自己的战斗力。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的内力不够。\n");

        if( BUFF_D->check_buff(me, "powerup") )
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -90, me);
        me->receive_damage("qi", 0);

        msg = HIR "$N" HIR "大喝一声，运起扶桑内功，"
                        "全身骨节发出一阵爆豆般的声响！\n" NOR;

        data = ([
                "attack" : skill/3,
                "defense": skill/3,
        ]);
        
        buff = ([
                "caster": me,
                "target": me,
                "type"  : "powerup",
                "attr"  : "bless",
                "name"  : "扶桑内功·战神",
                "time"  : skill,
                "buff_data": data,      
                "buff_msg" : msg,
                "disa_msg" : "你的扶桑内功运行完毕，将内力收回丹田。\n",
                        
        ]);
        BUFF_D->buffup(buff);
        if( me->is_fighting() ) me->start_busy(3);

        return 1;       
}


