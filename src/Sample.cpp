#include <c++/stdexcept>
#include "Sample.h"

namespace modio {
    Sample::Sample() :
            Sample("") {

    }

    Sample::Sample(const std::string &name) :
            Sample(name, 64) {

    }

    Sample::Sample(const std::string &name, unsigned int volume) :
            Sample(name, volume, 0, 0) {

    }

    Sample::Sample(const std::string &name, unsigned int volume, unsigned int repeatStart, unsigned int repeatLength) :
            mName(name),
            mVolume(volume),
            mRepeatStart(repeatStart),
            mRepeatLength(repeatLength) {

    }

    void Sample::setName(const std::string &name) {
        mName = name;
    }

    const std::string &Sample::name() const {
        return mName;
    }

    void Sample::resize(unsigned int length) {
        mData.resize(length);
    }

    unsigned int Sample::length() const {
        return mData.size();
    }

    void Sample::setVolume(unsigned int volume) {
        if(volume > 64)
            throw std::invalid_argument("Volume must not be larger than 64.");
        mVolume = volume;
    }

    unsigned int Sample::volume() const {
        return mVolume;
    }

    void Sample::setRepeatStart(unsigned int repeatStart) {
        // TODO: OpenMPT seems to enforce that start my not exceed (length - 16)
        if(repeatStart > length())
            throw std::invalid_argument("Repeat start must not be larger than sample length(" + std::to_string(length()) + ").");
        mRepeatStart = repeatStart;
    }

    unsigned int Sample::repeatStart() const {
        return mRepeatStart;
    }

    void Sample::setRepeatLength(unsigned int repeatLength) {
        // TODO: OpenMPT seems to enforce that length my not exceed (start + 16)
        if(repeatLength - 1 > length())
            throw std::invalid_argument("Repeat length must not be larger than sample length(" + std::to_string(length()) + ").");
        mRepeatLength = repeatLength;
    }

    unsigned int Sample::repeatLength() const {
        return mRepeatLength;
    }
}