#ifndef LIBMODIO_MODULE_H
#define LIBMODIO_MODULE_H

#include <string>
#include <vector>
#include "Sample.h"
#include "Pattern.h"
#include "Sequence.h"

namespace modio {
    /**
     * \brief A music module
     *
     * A music module contains all data kept in a module file of any of the
     * popular formats along with several methods to manipulate it.
     *
     * Currently the following formats are supported or are to be supported
     * somewhere in the future (marked with a *):
     * - MOD (.mod), and the most popular format mods (i.e. 8CHN, M!K!, etc)
     * - *FastTracker 2 (.xm)
     * - *Impulse Tracker (.it)
     * - *ScreamTracker 3 (.s3m)
     */
    class Module {
    public:
        /**
         * \brief Creates a new Module using default values.
         *
         * By default 31 empty samples are created and 1 empty pattern.
         */
        Module();

        /**
         * \brief Creates a new Module with a name and using default values
         */
        Module(const std::string &name);

        /**
         * \brief Creates a new Module with a name and signature and default values
         */
        Module(const std::string &name, const std::string &signature);

        /**
         * \brief Returns the name of this module
         */
        const std::string &name() const;

        /**
         * \brief Sets the name oa this module
         *
         * \param name name to set, 20 characters max
         */
        void setName(const std::string &name);

        /**
         * \brief Returns the length of the sequence
         *
         * Returns the length of the (also known as the order list or
         * pattern table). See \see Sequence::setLength for more information.
         */
        const unsigned int length() const;

        /**
         * \brief Sets the length of the sequence
         *
         * Sets the length of the sequence (also known as the order list or
         * pattern table). See \see Sequence::setLength for more information.
         */
        void setLength(unsigned int length);

        /**
         * \brief Returns the signature of this module
         *
         * Returns the signature of this module. The signature of a module is
         * nothing more but 4 bytes that the user is free to set to anything
         * they like. Though mostly these 4 bytes are used communicate the mod
         * format. Please see ModWriter for more information.
         */
        const std::string &signature() const;

        /**
         * \brief Sets the signature of this module
         *
         * See ::signature and ModWriter for more information. The signature of
         * a module can be set to anything. Though some tracker and possibly
         * players might expect a certain string here.
         *
         * \param signature signature to set
         */
        void setSignature(const std::string &signature);

        /**
         * \brief Returns the samples of this Module
         */
        const std::vector<Sample> samples() const;

        /**
         * \brief Sets the sample at index to sample
         *
         * \param index  sample index
         * \param sample sample to set
         */
        void setSample(unsigned int index, const Sample &sample);

        /**
         * \brief Returns the patterns of this module
         */
        const std::vector<Pattern> patterns() const;

        /**
         * \brief Sets the pattern and index to pattern
         *
         * \param index   pattern index
         * \param pattern pattern to set
         */
        void setPattern(unsigned int index, const Pattern &pattern);

        /**
         * \brief Returns the sequence of this module
         *
         * TODO: I don't think we should expose this, rather let Module act as a facade?
         */
        const Sequence &sequence() const;

        /**
         * \brief Sets pattern to play at the orderIndex
         *
         * See Sequence for more information.
         *
         * \param orderIndex order index to set
         * \param patternIndex pattern index to set at orderIndex
         */
        void set(unsigned int orderIndex, unsigned int patternIndex);

        /**
         * \brief Get the pattern to play at orderIndex
         *
         * \param orderIndex order index to retrieve pattern from
         */
        unsigned int get(unsigned int orderIndex);

    private:
        std::string mName;
        std::string mSignature;

        Sequence mSequence;

        std::vector<Sample> mSamples;
        std::vector<Pattern> mPatterns;
    };
}

#endif //LIBMODIO_MODULE_H
