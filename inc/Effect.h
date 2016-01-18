#ifndef LIBMODIO_EFFECT_H
#define LIBMODIO_EFFECT_H

namespace modio {
    class Effect {
    public:
        Effect();
        Effect(unsigned int effect, unsigned int param1);
        Effect(unsigned int effect, unsigned int param1, unsigned int param2);

        unsigned int effect() const;
        void setEffect(unsigned int effect);

        unsigned int param1() const;
        void setParam1(unsigned int param1);

        unsigned int param2() const;
        void setParam2(unsigned int param2);

    private:
        unsigned int mEffect;
        unsigned int mParam1;
        unsigned int mParam2;
    };
}

#endif //LIBMODIO_EFFECT_H
