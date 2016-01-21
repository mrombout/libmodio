#ifndef LIBMODIO_SEQUENCE_H
#define LIBMODIO_SEQUENCE_H

#include <vector>

namespace modio {
    /**
     * \brief Sequence of a Module
     *
     * A Sequence, also known as the order list or pattern table contains the
     * order of patterns to be played. It is stored as a simple list of indices
     * ranging from 0 to a maximum of 128, and a pattern index (varies per
     * module format).
     */
    class Sequence {
    public:
        /**
         * \brief Constructs a new Sequence
         */
        Sequence();

        /**
         * \brief Returns the length of this Sequence
         *
         * Note that the length of the sequence must explicitly be set by the
         * user.
         */
        unsigned int length() const;

        /**
         * \brief Sets the Sequence length
         *
         * \param length new length of this sequence
         */
        void setLength(unsigned int length);

        /**
         * \brief Sets the pattern to play at order index
         *
         * TODO: Maximum amount of patternIndex should be determined by the current format (varies between formats)
         *
         * \throws std::invalid_argument if orderIndex exceeds sequence length
         * \throws std::invalid_argument if patternIndex exceeds 64, the maximum amount of patterns
         * \param orderIndex order index to set
         * \param patternIndex pattern to play at orderIndex
         */
        void set(unsigned int orderIndex, unsigned int patternIndex);

        /**
         * \brief Gets the pattern index at a specific orderIndex
         *
         * \throws std::invalid_argument if orderIndex exceeds sequence length
         * \param orderIndex order index to retrieve pattern index from
         */
        unsigned int get(unsigned int orderIndex);

        /**
         * \brief Gets the order of patterns to play
         */
        const std::vector<unsigned int> order() const;

    private:
        unsigned int mLength;

        std::vector<unsigned int> mOrder;
    };
}

#endif //LIBMODIO_SEQUENCE_H
