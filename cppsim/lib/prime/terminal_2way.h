#ifndef _TERMINAL_2WAY_H_
#define _TERMINAL_2WAY_H_

class Terminal_2Way{
    public:
        int id;
        float value;
        Terminal_2Way(float v);
        float voltage();
        float current();
        float impedance();
};

#endif