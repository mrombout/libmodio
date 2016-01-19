#ifndef LIBMODIO_PERIOD_H
#define LIBMODIO_PERIOD_H

namespace modio {
    class Period {
    public:
        Period();
        Period(unsigned int period);
        Period(char note, unsigned int octave);

        unsigned int period() const;
        void setPeriod(unsigned int period);

        char note() const;
        void setNote(char note);

        unsigned int octave() const;
        void setOctave(unsigned int octave);

    private:
        unsigned int mPeriod;
    };
}

#endif //LIBMODIO_PERIOD_H
