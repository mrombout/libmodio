#ifndef LIBMODIO_PATTERN_H
#define LIBMODIO_PATTERN_H

#include <vector>
#include "Note.h"
#include "Sample.h"
#include "Effect.h"
#include "Channel.h"

namespace modio {
    class Pattern {
    public:
        void set(unsigned int channel, unsigned int division, const Note &note, Sample &sample);
        void set(unsigned int channel, unsigned int division, const Note &note, Sample &sample, Effect effect);

        const Channel &channel(unsigned int channelIndex) const;

    private:
        Channel &channel(unsigned int channelIndex);

    private:
        std::vector<Channel> mChannels;
    };
}

#endif //LIBMODIO_PATTERN_H
