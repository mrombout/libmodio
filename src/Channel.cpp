#include "Channel.h"

namespace modio {
    Channel::Channel() :
        mDivisions(64) {

    }

    void Channel::set(unsigned int division, const Period &period, unsigned int sampleIndex) {
        mDivisions.at(division).set(period, sampleIndex);
    }

    void Channel::set(unsigned int division, const Period &period, unsigned int sampleIndex, const Effect effect) {
        mDivisions.at(division).set(period, sampleIndex, effect);
    }

    const Division &Channel::get(unsigned int division) const {
        return mDivisions.at(division);
    }
}