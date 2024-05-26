#ifndef _TERMINAL_4WAY_H_
#define _TERMINAL_4WAY_H_

class Terminal_4Way{
    public:
        int id;
        float value;
        Terminal_4Way(float v);
        float voltage();
        float current();
        float impedance();
};

#endif