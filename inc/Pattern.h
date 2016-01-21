#ifndef LIBMODIO_PATTERN_H
#define LIBMODIO_PATTERN_H

#include <vector>
#include "Period.h"
#include "Sample.h"
#include "Effect.h"
#include "Channel.h"
#include "Division.h"

namespace modio {
    /**
     * \brief A Pattern in a Module
     */
    class Pattern {
    public:
        /**
         * \brief Constructs a new Pattern with 4 channels
         */
        Pattern();

        /**
         * \brief Constructs a new Pattern with numChannels channels
         */
        Pattern(unsigned int numChannels);

        /**
         * \brief Sets the period and sample of a division at a specific channel
         */
        void set(unsigned int channel, unsigned int divisionIndex, const Period &period, unsigned int sampleIndex);

        /**
         * \brief Sets the period, sample and effect of a division at a specific channel
         */
        void set(unsigned int channel, unsigned int divisionIndex, const Period &period, unsigned int sampleIndex, const Effect effect);

        /**
         * \brief Gets the Division at a specific channelIndex and divisionIndex
         */
        const Division &get(unsigned int channelIndex, unsigned int divisionIndex) const;

        /**
         * \brief Gets the Channel at a specific channelIndex
         */
        const Channel &channel(unsigned int channelIndex) const;

        /**
         * \brief Returns the number of channels
         */
        unsigned int numChannels();

    private:
        Channel &channel(unsigned int channelIndex);

    private:
        unsigned int mNumChannels;
        std::vector<Channel> mChannels;
    };
}

#endif //LIBMODIO_PATTERN_H
