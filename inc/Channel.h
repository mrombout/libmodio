#ifndef LIBMODIO_CHANNEL_H
#define LIBMODIO_CHANNEL_H

#include <vector>
#include "Division.h"
#include "Period.h"
#include "Sample.h"
#include "Effect.h"

namespace modio {
    enum ChannelIndex {
        CHANNEL1 = 0,
        CHANNEL2 = 1,
        CHANNEL3 = 2,
        CHANNEL4 = 3
    };

    /**
     * \brief A single channel in a Pattern
     */
    class Channel {
    public:
        Channel();

        void set(unsigned int division, const Period &period, unsigned int sampleIndex);
        void set(unsigned int division, const Period &period, unsigned int sampleIndex, const Effect effect);

        const Division &get(unsigned int division) const;

        void clear();

    private:
        std::vector<Division> mDivisions;
    };
}

#endif //LIBMODIO_CHANNEL_H
