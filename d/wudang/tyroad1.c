inherit ROOM;

void create()
{
        set("short", "石阶");
        set("long", @LONG
这是一条宽大坚实的石阶路，不时地有进香客和游人从你的身边
走过。抬头西望，雄伟的三清殿顶浮现在香烟袅绕之中，巍峨壮观。
东边一条石阶通往武当山脚下，隐约可见远处桃花片片，赏心悦目。
LONG );
        set("outdoors", "wudang");
        set("exits", ([
                "westup" : __DIR__"guangchang",
                "east" : __DIR__"tyroad2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -360);
        set("coor/y", -290);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}