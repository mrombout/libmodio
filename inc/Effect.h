#ifndef LIBMODIO_EFFECT_H
#define LIBMODIO_EFFECT_H

namespace modio {
    class Effect {
    public:
        Effect();
        Effect(unsigned int raw);

        unsigned int raw() const;
        void setRaw(unsigned int raw);

        operator unsigned int() const;

    private:
        unsigned int mRaw;
    };
}

#endif //LIBMODIO_EFFECT_H
