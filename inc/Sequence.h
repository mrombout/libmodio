#ifndef LIBMODIO_SEQUENCE_H
#define LIBMODIO_SEQUENCE_H

namespace modio {
    class Sequence {
    public:
        void addPattern();
        void removePattern();

        unsigned int length() const;
    };
}

#endif //LIBMODIO_SEQUENCE_H
