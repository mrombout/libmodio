#ifndef LIBMODIO_CHANNEL_H
#define LIBMODIO_CHANNEL_H

#include <vector>
#include "Division.h"
#include "Period.h"
#include "Sample.h"
#include "Effect.h"

namespace modio {
    class Channel {
    public:
        Channel();

        void set(unsigned int division, const Period &period, unsigned int sampleIndex);
        void set(unsigned int division, const Period &period, unsigned int sampleIndex, const Effect effect);

        const Division &get(unsigned int division) const;

    private:
        std::vector<Division> mDivisions;
    };
}

#endif //LIBMODIO_CHANNEL_H
