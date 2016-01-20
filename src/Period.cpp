#include "Period.h"

namespace modio {
    Period::Period() :
        mPeriod(0) {

    }

    Period::Period(unsigned int period) :
        mPeriod(period) {

    }

    Period::Period(int period) :
        mPeriod(period) {

    }

    unsigned int Period::period() const {
        return mPeriod;
    }

    void Period::setPeriod(unsigned int period) {
        mPeriod = period;
    }

    Period::operator int() const {
        return mPeriod;
    }
}