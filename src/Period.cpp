#include <c++/stdexcept>
#include "Period.h"

namespace modio {
    Period::Period() :
        mPeriod(0) {

    }

    Period::Period(unsigned int period) :
        mPeriod(period) {

    }

    Period::Period(char note, unsigned int octave) {
        setNote(note);
        setPeriod(period());
    }

    unsigned int Period::period() const {
        return mPeriod;
    }

    void Period::setPeriod(unsigned int period) {
        mPeriod = period;
    }

    char Period::note() const {
        // TODO: Deduce from period
        return '\n';
    }

    void Period::setNote(char note) {
        // TODO: Change period to match note
    }

    unsigned int Period::octave() const {
        // TODO: Deduce from period
        return 0;
    }

    void Period::setOctave(unsigned int octave) {
        // TODO: Change period to match octave
    }
}