#include "Pattern.h"

namespace modio {
    void Pattern::set(unsigned int channelIndex, unsigned int division, const Note &note, Sample &sample) {
        channel(channelIndex).set(division, note, sample);
    }

    void Pattern::set(unsigned int channelIndex, unsigned int division, const Note &note, Sample &sample, Effect effect) {
        channel(channelIndex).set(division, note, sample);
    }

    const Channel &Pattern::channel(unsigned int channelIndex) const {
        return mChannels[channelIndex];
    }

    Channel &Pattern::channel(unsigned int channelIndex) {
        return mChannels[channelIndex];
    }
}