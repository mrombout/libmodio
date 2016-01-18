#include <c++/stdexcept>
#include "Effect.h"

namespace modio {
    Effect::Effect() :
        Effect(0, 0, 0) {

    }

    Effect::Effect(unsigned int effect, unsigned int param1) {
        setEffect(effect);
        setParam1(param1);
    }

    Effect::Effect(unsigned int effect, unsigned int param1, unsigned int param2) {
        setEffect(effect);
        setParam1(param1);
        setParam2(param2);
    }

    unsigned int Effect::effect() const {
        return mEffect;
    }

    void Effect::setEffect(unsigned int effect) {
        if(effect > 0xFFF)
            throw std::invalid_argument("Effect number must not be larger than 4096.");
        mEffect = effect;
    }

    unsigned int Effect::param1() const {
        return mParam1;
    }

    void Effect::setParam1(unsigned int param1) {
        if(param1 > 0xFF)
            throw std::invalid_argument("Parameter 1 must not be larger than 255.");
        mParam1 = param1;
    }

    unsigned int Effect::param2() const {
        return mParam2;
    }

    void Effect::setParam2(unsigned int param2) {
        if(param2 > 0xF)
            throw std::invalid_argument("Parameter 2 must not be larger than 15.");
        mParam2 = param2;
    }
}