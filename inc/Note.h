#ifndef LIBMODIO_NOTE_H
#define LIBMODIO_NOTE_H

namespace modio {
    class Note {
    public:
        Note(char note);
        Note(char note, unsigned int octave);

        const char note() const;
        void setNote(char note);

        const unsigned int octave() const;
        void setOctave(unsigned int octave);

    private:
        char mNote;
        unsigned int mOctave;
    };
}

#endif //LIBMODIO_NOTE_H
