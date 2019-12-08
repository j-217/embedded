#include <stdio.h>

int main(){
    unsigned int i = 0;
    for(; i<=127; i++){
        printf("%c", i);
        if(i % 10 == 0 || i == 127){
            printf("\n");
        }
    }
    return 0;
}
