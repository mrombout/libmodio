#ifndef LIBMODIO_CHANNEL_H
#define LIBMODIO_CHANNEL_H

#include <vector>
#include "Division.h"
#include "Note.h"
#include "Sample.h"
#include "Effect.h"

namespace modio {
    class Channel {
    public:
        void set(unsigned int division, const Note &note, Sample &sample);
        void set(unsigned int division, const Note &note, Sample &sample, Effect effect);

    private:
        std::vector<Division> mDivisions;
    };
}

#endif //LIBMODIO_CHANNEL_H
