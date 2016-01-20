#ifndef LIBMODIO_PATTERN_H
#define LIBMODIO_PATTERN_H

#include <vector>
#include "Period.h"
#include "Sample.h"
#include "Effect.h"
#include "Channel.h"
#include "Division.h"

namespace modio {
    class Pattern {
    public:
        Pattern();
        Pattern(unsigned int numChannels);

        void set(unsigned int channel, unsigned int divisionIndex, const Period &period, unsigned int sampleIndex);
        void set(unsigned int channel, unsigned int divisionIndex, const Period &period, unsigned int sampleIndex, const Effect effect);

        const Division &get(unsigned int channelIndex, unsigned int divisionIndex) const;

        const Channel &channel(unsigned int channelIndex) const;
        unsigned int numChannels();

    private:
        Channel &channel(unsigned int channelIndex);

    private:
        unsigned int mNumChannels;
        std::vector<Channel> mChannels;
    };
}

#endif //LIBMODIO_PATTERN_H
