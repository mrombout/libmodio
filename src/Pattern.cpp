#include <stdexcept>
#include "Pattern.h"

namespace modio {
    Pattern::Pattern() {

    }

    Pattern::Pattern(unsigned int channelCount) :
        mChannelCount(channelCount),
        mChannels(mChannelCount) {

    }

    void Pattern::set(unsigned int channelIndex, unsigned int division, const Period &period, unsigned int sampleIndex) {
        channel(channelIndex).set(division, period, sampleIndex);
    }

    void Pattern::set(unsigned int channelIndex, unsigned int division, const Period &period, unsigned int sampleIndex, const Effect effect) {
        channel(channelIndex).set(division, period, sampleIndex);
    }

    const Channel &Pattern::channel(unsigned int channelIndex) const {
        if(mChannelCount && channelIndex > mChannelCount)
            throw std::invalid_argument("Channel index '" + std::to_string(channelIndex) + " may not exceed '" + std::to_string(mChannelCount) + "'.");
        return mChannels[channelIndex];
    }

    Channel &Pattern::channel(unsigned int channelIndex) {
        return mChannels[channelIndex];
    }
}