#ifndef LIBMODIO_PATTERN_H
#define LIBMODIO_PATTERN_H

#include <vector>
#include "Period.h"
#include "Sample.h"
#include "Effect.h"
#include "Channel.h"

namespace modio {
    class Pattern {
    public:
        Pattern();
        Pattern(unsigned int channelCount);

        void set(unsigned int channel, unsigned int division, const Period &period, unsigned int sampleIndex);
        void set(unsigned int channel, unsigned int division, const Period &period, unsigned int sampleIndex, const Effect effect);

        const Channel &channel(unsigned int channelIndex) const;

    private:
        Channel &channel(unsigned int channelIndex);

    private:
        unsigned int mChannelCount;
        std::vector<Channel> mChannels;
    };
}

#endif //LIBMODIO_PATTERN_H
