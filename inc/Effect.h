#ifndef LIBMODIO_EFFECT_H
#define LIBMODIO_EFFECT_H

namespace modio {
    class Effect {
    public:
        Effect();
        explicit Effect(unsigned int effect);
        Effect(unsigned int effect, unsigned int param);
        Effect(unsigned int effect, unsigned int param1, unsigned int param2);

        unsigned int effect() const;
        void setEffect(unsigned int effect);

        unsigned int param() const;
        void setParam(unsigned int param);

        unsigned int param1() const;
        void setParam1(unsigned int param1);

        unsigned int param2() const;
        void setParam2(unsigned int param2);

    private:
        unsigned int mEffect;
    };
}

#endif //LIBMODIO_EFFECT_H
