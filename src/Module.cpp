#include <c++/stdexcept>
#include "Module.h"

namespace modio {
    Module::Module() :
        Module("") {

    }

    Module::Module(const std::string &name) :
        Module("", "") {

    }

    Module::Module(const std::string &name, const std::string &signature) :
        mName(name),
        mSignature(name) {

    }

    const std::string &Module::name() const {
        return mName;
    }

    void Module::setName(const std::string &name) {
        if(name.length() > 20)
            throw std::invalid_argument("Name must not exceed 20 characters.");
        mName = name;
    }

    const std::string &Module::signature() const {
        return mSignature;
    }

    void Module::setSignature(const std::string &signature) {
        if(signature.length() > 4)
            throw std::invalid_argument("Signature must not exceed 4 characters.");
        mSignature = signature;
    }
}
