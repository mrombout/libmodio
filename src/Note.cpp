#include <c++/stdexcept>
#include "Note.h"

namespace modio {
    Note::Note(char note) :
        Note(note, 5) {

    }

    Note::Note(char note, unsigned int octave) :
        mNote(note),
        mOctave(octave) {

    }

    const char Note::note() const {
        return mNote;
    }

    void Note::setNote(char note) {
        if(note > 0xFF)
            throw std::invalid_argument("Note must not be larger than 255.");
        mNote = note;
    }

    const unsigned int Note::octave() const {
        return mOctave;
    }

    void Note::setOctave(unsigned int octave) {
        if(octave > 0xFF)
            throw std::invalid_argument("Octave must not be larger than 255.");
        mOctave = octave;
    }
}