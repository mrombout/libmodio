#include <stdexcept>
#include "Sequence.h"

namespace modio {
    Sequence::Sequence() :
        mOrder(128) {

    }

    unsigned int Sequence::length() const {
        return mLength;
    }

    void Sequence::setLength(unsigned int length) {
        mLength = length;
    }

    void Sequence::set(unsigned int orderIndex, unsigned int patternIndex) {
        if(orderIndex > mLength)
            throw std::invalid_argument("Pattern order index '" + std::to_string(orderIndex) + "' must not exceed module length '" + std::to_string(mLength) + "'");
        if(patternIndex > 64)
            throw std::invalid_argument("Pattern order pattern index '" + std::to_string(patternIndex) + "' must not exceed '64'");
        mOrder[orderIndex] = patternIndex;
    }

    unsigned int Sequence::get(unsigned int orderIndex) {
        if(orderIndex >= mLength)
            throw std::invalid_argument("Pattern order index '" + std::to_string(orderIndex) + "' must not exceed module length '" + std::to_string(mLength) + "'");
        return mOrder.at(orderIndex);
    }

    const std::vector<unsigned int> Sequence::order() const {
        return mOrder;
    }
}