#include "Division.h"

namespace modio {
    void Division::set(const Note &note, Sample &sample) {
        set(note, sample, Effect());
    }

    void Division::set(const Note &note, Sample &sample, Effect effect) {
        setNote(note);
        setSample(sample);
        setEffect(effect);
    }

    const Note &Division::note() const {
        return mNote;
    }

    void Division::setNote(Note note) {
        mNote = note;
    }

    const Sample &Division::sample() const {
        return mSample;
    }

    void Division::setSample(Sample &sample) {
        mSample = sample;
    }

    const Effect &Division::effect() const {
        return mEffect;
    }

    void Division::setEffect(Effect &effect) {
        mEffect = effect;
    }
}