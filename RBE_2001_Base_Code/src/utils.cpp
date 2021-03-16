#include <utils.h>
int sign(float num){
    if(num==0){
        return 0;
    }
    else{
        return abs(num)/num;
    }
}