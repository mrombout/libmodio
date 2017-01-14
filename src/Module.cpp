#include <stdexcept>
#include "Module.h"

namespace modio {
    Module::Module() :
        Module("") {

    }

    Module::Module(const std::string &name) :
        Module(name, "") {

    }

    Module::Module(const std::string &name, const std::string &signature) :
        mName(name),
        mSignature(signature),
        mSamples(31),
        mPatterns(1) {

    }

    const std::string &Module::name() const {
        return mName;
    }

    void Module::setName(const std::string &name) {
        if(name.length() > 20)
            throw std::invalid_argument("Name must not exceed 20 characters.");
        mName = name;
    }

    const unsigned int Module::length() const {
        return mSequence.length();
    }

    void Module::setLength(unsigned int length) {
        mSequence.setLength(length);
    }

    const std::string &Module::signature() const {
        return mSignature;
    }

    void Module::setSignature(const std::string &signature) {
        if(signature.length() > 4)
            throw std::invalid_argument("Signature must not exceed 4 characters.");
        mSignature = signature;
    }

    const std::vector<Sample> Module::samples() const {
        return mSamples;
    }

    void Module::setSample(const unsigned int index, const Sample &sample) {
        if(index == 0)
            throw std::invalid_argument("Sample index '" + std::to_string(index) + "' does not exist. Sample indexes are zero-based.");

        const unsigned int targetIndex = index - 1;
        if(targetIndex > 31)
            throw std::invalid_argument("Sample index '" + std::to_string(index) + "' may not exceed '31'.");
        mSamples.at(targetIndex) = sample;
    }

    const std::vector<Pattern> Module::patterns() const {
        return mPatterns;
    }

    void Module::setPattern(unsigned int index, const Pattern &pattern) {
        if(index > 64)
            throw std::invalid_argument("Pattern index '" + std::to_string(index) + "' may not exceed '64'.");
        if(index > mPatterns.size() - 1)
            mPatterns.resize(index + 1);
        mPatterns.at(index) = pattern;
    }

    const Sequence &Module::sequence() const {
        return mSequence;
    }

    void Module::set(unsigned int orderIndex, unsigned int patternIndex) {
        mSequence.set(orderIndex, patternIndex);
    }

    unsigned int Module::get(unsigned int orderIndex) {
        return mSequence.get(orderIndex);
    }
}
