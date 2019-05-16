#include "lib.h"
#include "printk.h"
#include "gate.h"
#include "trap.h"
#include "memory.h"

struct Global_Memory_Descriptor memory_management_struct = {{0},0};

void Start_Kernel()
{
    int *addr = (int *)0xffff800000a00000; //帧缓存地址
    int i = 0;

    //1440 * 20个像素点
    for (i = 0; i < 1440 * 20; ++i)
    {
        //char占一个字节
        *((char *)addr + 0) = (char)0x00; //一次读取一个字节 写入数值
        *((char *)addr + 1) = (char)0x00;
        *((char *)addr + 2) = (char)0xff;
        *((char *)addr + 3) = (char)0x00;

        addr += 1; //int * 类型 一次偏移4个字节
    }

    for (i = 0; i < 1440 * 20; i++)
    {
        *((char *)addr + 0) = (char)0x00;
        *((char *)addr + 1) = (char)0xff;
        *((char *)addr + 2) = (char)0x00;
        *((char *)addr + 3) = (char)0x00;
        addr += 1;
    }
    for (i = 0; i < 1440 * 20; i++)
    {
        *((char *)addr + 0) = (char)0xff;
        *((char *)addr + 1) = (char)0x00;
        *((char *)addr + 2) = (char)0x00;
        *((char *)addr + 3) = (char)0x00;
        addr += 1;
    }
    for (i = 0; i < 1440 * 20; i++)
    {
        *((char *)addr + 0) = (char)0xff;
        *((char *)addr + 1) = (char)0xff;
        *((char *)addr + 2) = (char)0xff;
        *((char *)addr + 3) = (char)0x00;
        addr += 1;
    }

    Pos.XResolution = 1440;
	Pos.YResolution = 900;

	Pos.XPosition = 0;
	Pos.YPosition = 0;

	Pos.XCharSize = 8;
	Pos.YCharSize = 16;

	Pos.FB_addr = (int *)0xffff800000a00000;
	Pos.FB_length = (Pos.XResolution * Pos.YResolution * 4);

    color_printk(YELLOW,BLACK,"Hello\t\t World!\n");
    color_printk(WHITE,BLACK,"TEST %s","HAHAHHA\n\n");

    load_TR(8);

	set_tss64(0xffff800000007c00, 0xffff800000007c00, 0xffff800000007c00, 0xffff800000007c00, 0xffff800000007c00, 0xffff800000007c00, 0xffff800000007c00, 0xffff800000007c00, 0xffff800000007c00, 0xffff800000007c00);

	sys_vector_init();

	// i = 1/0;
	// i = *(int *)0xffff80000aa00000;
    
    color_printk(RED, BLACK, "memory init \n");
    init_memory();

    while(1);

}