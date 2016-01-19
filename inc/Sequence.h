#ifndef LIBMODIO_SEQUENCE_H
#define LIBMODIO_SEQUENCE_H

#include <vector>

namespace modio {
    class Sequence {
    public:
        unsigned int length() const;
        void setLength(unsigned int length);

        void set(unsigned int orderIndex, unsigned int patternIndex);
        unsigned int get(unsigned int orderIndex);

    private:
        unsigned int mLength;

        std::vector<unsigned int> mOrder;
    };
}

#endif //LIBMODIO_SEQUENCE_H
