#include <stdio.h>
#include <termios.h>

int main(int argc, char const *argv[])
{
    struct termios new_setting,init_setting;
    char pwd[16];
    tcgetattr(0,&init_setting);
    new_setting=init_setting;
    //get termios setting and save it

    new_setting.c_lflag&=~ECHO;
    tcsetattr(0,TCSANOW,&new_setting);
    printf("please enter password: \n");  
    fgets(pwd,sizeof(pwd),stdin);

    printf("you enter %d\n",pwd);
    //restore the setting

    tcsetattr(0,TCSANOW,&init_setting);
    // printf("\033[2J");                              // clear terminal
    
    return 0;
}
