#ifndef RED_H
    #define RED_H
    #include "Context.h"
    #include <Arduino.h>

    class Red : public State
    {
    public:
        void on_do() override
        {
        }

        void on_entry() override
        {
            Serial.println("RedLight->ON");
        }

        void on_exit() override
        {
            Serial.println("RedLight->OFF");
        }
    };
#endif
