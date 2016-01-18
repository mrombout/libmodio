#ifndef LIBMODIO_DIVISION_H
#define LIBMODIO_DIVISION_H

#include "Sample.h"
#include "Effect.h"
#include "Note.h"

namespace modio {
    class Division {
    public:
        void set(const Note &note, Sample &sample);
        void set(const Note &note, Sample &sample, Effect effect);

        const Note &note() const;
        void setNote(Note note);

        const Sample &sample() const;
        void setSample(Sample &sample);

        const Effect &effect() const;
        void setEffect(Effect &effect);

    private:
        Note mNote;
        Sample mSample;
        Effect mEffect;
    };
}

#endif //LIBMODIO_DIVISION_H
