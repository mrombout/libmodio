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
            Sample(name, volume, 0, 0, std::vector<unsigned char>()) {

    }

    Sample::Sample(const std::string &name, unsigned int volume, unsigned int repeatStart, unsigned int repeatLength, const std::vector<unsigned char> &data) :
            mName(name),
            mVolume(volume),
            mRepeatStart(repeatStart),
            mRepeatLength(repeatLength),
            mData(data) {

    }

    void Sample::setName(const std::string &name) {
        if(name.length() > 22)
            throw std::invalid_argument("Sample name (which is " + name + ") may not exceed 22 characters.");
        mName = name;
    }

    const std::string &Sample::name() const {
        return mName;
    }

    void Sample::resize(unsigned int length) {
        // Allegedly, a value of 0 will crash an Amiga.
        //if(length < 1)
            //throw std::invalid_argument("Length (which is " + std::to_string(length) + ") must be larger than 1.");
        mData.resize(length * 2);
    }

    unsigned int Sample::length() const {
        return mData.size() / 2;
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
            throw std::invalid_argument("Sample repeat start (which is " + std::to_string(repeatStart) + ") must not be larger than sample length (which is " + std::to_string(length()) + ").");
        mRepeatStart = repeatStart;
    }

    unsigned int Sample::repeatStart() const {
        return mRepeatStart;
    }

    void Sample::setRepeatLength(unsigned int repeatLength) {
        // TODO: OpenMPT seems to enforce that length my not exceed (start + 16)
        if(repeatLength > length() + 1)
            throw std::invalid_argument("Sample repeat length (which is " + std::to_string(repeatLength) + ") must not be larger than sample length (which is " + std::to_string(length()) + ").");
        mRepeatLength = repeatLength;
    }

    unsigned int Sample::repeatLength() const {
        return mRepeatLength;
    }

    void Sample::setData(std::vector<unsigned char> data) {
        if(data.size() != length() * 2)
            throw std::invalid_argument("Sample data length (which is" + std::to_string(data.size()) + ") must be exactly that of length in bytes (which is " + std::to_string(length() * 2) + ").");
        mData = data;
    }

    const std::vector<unsigned char> Sample::data() const {
        return mData;
    }
}