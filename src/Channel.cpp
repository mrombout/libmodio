#include "Channel.h"

namespace modio {
    Channel::Channel() :
        mDivisions(64) {

    }

    void Channel::set(unsigned int division, const Period &period, unsigned int sampleIndex) {
        mDivisions[division].set(period, sampleIndex);
    }

    void Channel::set(unsigned int division, const Period &period, unsigned int sampleIndex, const Effect effect) {
        mDivisions[division].set(period, sampleIndex, effect);
    }
}