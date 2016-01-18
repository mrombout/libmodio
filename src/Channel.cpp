#include "Channel.h"

namespace modio {
    void Channel::set(unsigned int division, const Note &note, Sample &sample) {
        mDivisions[division].set(note, sample);
    }

    void Channel::set(unsigned int division, const Note &note, Sample &sample, Effect effect) {
        mDivisions[division].set(note, sample, effect);
    }
}