#ifndef LIBMODIO_PERIOD_H
#define LIBMODIO_PERIOD_H

namespace modio {
    enum Note {
        C1  = 856,
        CS1 = 808,
        D1  = 762,
        DS1 = 720,
        E1  = 678,
        F1  = 640,
        FS1 = 604,
        G1  = 570,
        GS1 = 538,
        A1  = 508,
        AS1 = 480,
        B1  = 453,

        C2  = 428,
        CS2 = 404,
        D2  = 381,
        DS2 = 360,
        E2  = 339,
        F2  = 320,
        FS2 = 302,
        G2  = 285,
        GS2 = 269,
        A2  = 254,
        AS2 = 240,
        B2  = 226,

        C3  = 214,
        CS3 = 202,
        D3  = 190,
        DS3 = 180,
        E3  = 170,
        F3  = 160,
        FS3 = 151,
        G3  = 143,
        GS3 = 135,
        A3  = 127,
        AS3 = 120,
        B3  = 113,
    };

    class Period {
    public:
        Period();
        Period(unsigned int period);
        Period(int period);

        unsigned int period() const;
        void setPeriod(unsigned int period);

        operator int() const;

    private:
        unsigned int mPeriod;
    };
}

#endif //LIBMODIO_PERIOD_H
