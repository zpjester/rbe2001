#include <Arduino.h>
#include <Romi32U4.h>
#include <servo32u4.h>

class Gripper{
    private:
        const int openVal = 1100;
        const int closedVal = 1900;
    public:
        void open();
        void close();
        int getPosition();
        void init();
        void toggle();
        
};