#include "Division.h"

namespace modio {
    void Division::set(const Period &period, unsigned int sampleIndex) {
        set(period, sampleIndex, Effect());
    }

    void Division::set(const Period &period, unsigned int sampleIndex, const Effect effect) {
        setPeriod(period);
        setSampleIndex(sampleIndex);
        setEffect(effect);
    }

    const Period &Division::period() const {
        return mPeriod;
    }

    void Division::setPeriod(Period period) {
        mPeriod = period;
    }

    unsigned int Division::sampleIndex() const {
        return mSampleIndex;
    }

    void Division::setSampleIndex(unsigned int sampleIndex) {
        mSampleIndex = sampleIndex;
    }

    const Effect &Division::effect() const {
        return *mEffect;
    }

    void Division::setEffect(const Effect &effect) {
        mEffect = &effect;
    }
}