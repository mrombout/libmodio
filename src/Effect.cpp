#include "Effect.h"

namespace modio {
    Effect::Effect() :
        mRaw(0) {

    }

    Effect::Effect(unsigned int raw) :
        mRaw(raw) {

    }

    unsigned int Effect::raw() const {
        return mRaw;
    }

    void Effect::setRaw(unsigned int raw) {
        mRaw = raw;
    }

    Effect::operator unsigned int() const {
        return mRaw;
    }
}