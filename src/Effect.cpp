#include <c++/stdexcept>
#include "Effect.h"

namespace modio {
    Effect::Effect() :
        mEffect(0) {

    }

    Effect::Effect(unsigned int effect) :
        mEffect(effect) {

    }

    Effect::Effect(unsigned int effect, unsigned int param) {
        setEffect(effect);
        setParam(param);
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
        mEffect = effect;
    }

    unsigned int Effect::param() const {
        return (mEffect & 0x0FF);
    }

    void Effect::setParam(unsigned int param) {
        // TODO: Set last 2 bytes of mEffect
    }

    unsigned int Effect::param1() const {
        return (mEffect & 0x0F0) >> 4;
    }

    void Effect::setParam1(unsigned int param1) {
        // TODO: Set middle byte of mEffect
    }

    unsigned int Effect::param2() const {
        return (mEffect & 0x00F);
    }

    void Effect::setParam2(unsigned int param2) {
        // TODO: Set last byte of mEffect
    }
}