#ifndef LIBMODIO_MODWRITER_H
#define LIBMODIO_MODWRITER_H

#include "ModuleWriter.h"
#include "Module.h"

namespace modio {
    /**
     * \brief Writes a Module to a '.mod' file
     *
     * Writes a Module to a 'M.K.' compatible '.mod' file. In this case, that
     * means this ModWriter supports the writing of 31 samples, 64 patterns and
     * 4 channels at most. Any more are simply ignored.
     *
     * Other populate mods will be supported in the future including:
     *  - M!K!, for more than 64 patterns
     *  - 6CHN, 8CHN, for 6-channel or 8-channel respectively
     *  - CD81, OKTA, OCTA, for 8-channel
     *  - xxCH, for 10+ channel, xx being a decimal number.
     *  - TDZ1, TDZ2, TDZ3, for 1, 2 and 3 channels respectively
     *  - 5CHN, 7CHN, 9CHN, for 5, 7 and 9 channels respectively
     *  - FLT4, for 4 channels
     *  - FLT8, for 8 channels
     */
    class ModWriter : public ModuleWriter {
    public:
        /**
         * \brief Writes the Module to the output stream in '.mod' format
         */
        virtual void write(const Module &module, std::ostream &out) const;

    private:
        void writeSampleHeaders(std::ostream &out, const Module &module) const;
        void writeSampleHeader(std::ostream &out, const Sample &sample) const;

        void writePatterns(std::ostream &out, const Module &module) const;
        void writePattern(std::ostream &out, Pattern &pattern) const;
    };
}

#endif //LIBMODIO_MODWRITER_H
