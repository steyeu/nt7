// right.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        function f;

        seteuid(getuid());

        if (! arg)
                return notify_fail("你要答应谁？\n");

        notify_fail("这人没有向你提出什么要求啊？\n");
        if (! functionp(f = query_temp("pending/answer/" + arg + "/right", me)))
                return 0;

        delete_temp("pending/answer/"+arg, me);
        return evaluate(f);
}

int help(object me)
{
   write( @HELP
指令格式: right <someone>

同意某人向你提出的要求。
HELP );
   return 1;
}
