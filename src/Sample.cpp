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

    unsigned int Sample::length() const {
        return mLength;
    }

    void Sample::setVolume(unsigned int volume) {
        mVolume = volume;
    }

    unsigned int Sample::volume() const {
        return mVolume;
    }

    void Sample::setRepeatStart(unsigned int repeatStart) {
        mRepeatStart = repeatStart;
    }

    unsigned int Sample::repeatStart() const {
        return mRepeatStart;
    }

    void Sample::setRepeatLength(unsigned int repeatLength) {
        mRepeatLength = repeatLength;
    }

    unsigned int Sample::repeatLength() const {
        return mRepeatLength;
    }
}