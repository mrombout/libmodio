#ifndef LIBMODIO_SAMPLE_H
#define LIBMODIO_SAMPLE_H

#include <string>
#include <vector>

namespace modio {
    /**
     * \brief Sample of a Module
     */
    class Sample {
    public:
        /**
         * \brief Constructs a new Sample
         */
        Sample();

        /**
         * \brief Constructs a new Sample
         */
        Sample(const std::string &name);

        /**
         * \brief Constructs a new Sample
         */
        Sample(const std::string &name, unsigned int volume);

        /**
         * \brief Constructs a new Sample
         */
        Sample(const std::string &name, unsigned int volume, unsigned int repeatStart, unsigned int repeatLength);

        /**
         * \brief Sets the name of this Sample, may not exceed 22 characters
         *
         * \throws std::invalid_argument if name exceeds 22 characters
         * \param name name to set, may not exceed 22 characters
         */
        void setName(const std::string &name);

        /**
         * \brief Gets the name of this Sample
         *
         * \returns name of this sample
         */
        const std::string &name() const;

        /**
         * \brief Resize this sample to a new size in words (1 word = 2 bytes)
         *
         * \param length new size in words (1 word = 2 bytes)
         */
        void resize(unsigned int length);

        /**
         * \brief Gets the length is this Sample in words (1 word = 2 bytes)
         *
         * \returns length of this sample in words (1 word = 2 bytes)
         */
        unsigned int length() const;

        /**
         * \brief Sets the volume of this sample, may not exceed 64
         *
         * \throws std::invalid_argument if volume exceeds 64
         * \param volume volume to set for this sample
         */
        void setVolume(unsigned int volume);

        /**
         * \brief Gets the volume of this Sample
         *
         * \returns volume of this sample
         */
        unsigned int volume() const;

        /**
         * \brief Sets the samples repeat start offset in words (1 word = 2 bytes)
         *
         * Sets the sample repeat offset in words (1 word = 2 bytes). Once the
         * sample has been played all the way through, it will loop if the
         * repeat length is greater than one. It repeats by jumping to this
         * position in the sample and playing for the repeat length, then
         * jumping back to this position, and playing for the repeat length,
         * etc.
         *
         * \throws std::invalid_argument if repeat length is greater than length of this sample
         * \param repeatStart samples repeat start offset
         */
        void setRepeatStart(unsigned int repeatStart);

        /**
         * \brief Gets the samples repeat start offset
         */
        unsigned int repeatStart() const;

        /**
         * \brief Sets the samples repeat length in words (1 word = 2 bytes)
         *
         * Sets the sample repeat length in words (1 word = 2 bytes). This
         * value defaults to 1. If this value is greater than 1 it will loop
         * when played.
         *
         * \throws std::invalid_argument if repeatLength is greater than sample length
         * \param repeatLength
         */
        void setRepeatLength(unsigned int repeatLength);

        /**
         * \brief Gets the samples repeat length
         */
        unsigned int repeatLength() const;

        /**
         * \brief Sets the data of this sample
         *
         * The samples data is stores as a collection of bytes, containing the
         * number of bytes set as the length of this sample (note that the
         * length of a sample is set in words, see ::setLength, so the data
         * should contain double that amount of bytes). Each byte is a signed
         * value (-128..127) which is the channel data.
         *
         * \throws std::invalid_argument is length of data is not exactly that of samples length
         * \param data to set
         */
        void setData(std::vector<unsigned char> data);

        /**
         * \brief Gets the data of this sample
         */
        const std::vector<unsigned char> data() const;

    private:
        std::string mName;

        unsigned int mVolume;

        unsigned int mRepeatStart;
        unsigned int mRepeatLength;

        std::vector<unsigned char> mData;
    };
}

#endif //LIBMODIO_SAMPLE_H
