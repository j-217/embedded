#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>

#define DEV_PATH "/dev/input/event1"   //根据需要修改为你的键盘对应的设备文件，可以直接sudo cat /dev/input/event5并按键盘，看是否有输出，见附图

int main()
{
    int keys_fd;  //文件标志
    char ret[2];
    struct input_event t;  //读取到的input设备数据是一个结构体
    
    keys_fd = open(DEV_PATH, O_RDONLY);  //权限不通过的时候一般会返回-1
    if(keys_fd <= 0)
    {
        printf("open /dev/input/event1 device error!\n");
        return -1;
    }
    while(1)
    {
        if(
            read(keys_fd, &t, sizeof(t)) == sizeof(t)
            )  /*keys_fd指向打开的设备文件，read将从设备文件传送sizeof(t)个字节的数据到&t这个内存地址。函数执行顺利的话返回值是实际读取的字节数*/
        {
            if(t.type == EV_KEY)
            {
                if(t.value==0 || t.value==1)
                {
                    printf("key %d %s\n", t.code, (t.value) ? "Pressed" : "Released");  //t.code值所对应的按键在/usr/include/linux/input-event-codes.h可以查到  
                }
            }
        }
    }
    close(keys_fd);
    
    return 0;
}