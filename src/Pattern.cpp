#include <stdexcept>
#include "Pattern.h"

namespace modio {
    Pattern::Pattern() :
        mNumChannels(4),
        mChannels(4) {

    }

    Pattern::Pattern(unsigned int numChannels) :
        mNumChannels(numChannels),
        mChannels(mNumChannels) {

    }

    void Pattern::set(unsigned int channelIndex, unsigned int divisionIndex, const Period &period, unsigned int sampleIndex) {
        channel(channelIndex).set(divisionIndex, period, sampleIndex);
    }

    void Pattern::set(unsigned int channelIndex, unsigned int divisionIndex, const Period &period, unsigned int sampleIndex, const Effect effect) {
        channel(channelIndex).set(divisionIndex, period, sampleIndex, effect);
    }

    const Division &Pattern::get(unsigned int channelIndex, unsigned int divisionIndex) const {
        return channel(channelIndex).get(divisionIndex);
    }

    const Channel &Pattern::channel(unsigned int channelIndex) const {
        if(mNumChannels && channelIndex > mNumChannels)
            throw std::invalid_argument("Channel index '" + std::to_string(channelIndex) + " may not exceed '" + std::to_string(mNumChannels) + "'.");
        return mChannels[channelIndex];
    }

    Channel &Pattern::channel(unsigned int channelIndex) {
        return mChannels[channelIndex];
    }

    unsigned int Pattern::numChannels() {
        return mNumChannels;
    }
}