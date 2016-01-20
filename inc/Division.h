#ifndef LIBMODIO_DIVISION_H
#define LIBMODIO_DIVISION_H

#include "Sample.h"
#include "Effect.h"
#include "Period.h"

namespace modio {
    class Division {
    public:
        Division();

        void set(const Period &period, unsigned int sampleIndex);
        void set(const Period &period, unsigned int sampleIndex, const Effect effect);

        const Period &period() const;
        void setPeriod(Period period);

        unsigned int sampleIndex() const;
        void setSampleIndex(unsigned int sampleIndex);

        const Effect &effect() const;
        void setEffect(const Effect &effect);

    private:
        Period mPeriod;
        unsigned int mSampleIndex;
        Effect mEffect;
    };
}

#endif //LIBMODIO_DIVISION_H
