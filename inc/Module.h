#ifndef LIBMODIO_MODULE_H
#define LIBMODIO_MODULE_H

#include <string>

namespace modio {
    class Module {
    public:
        Module();
        Module(const std::string &name);
        Module(const std::string &name, const std::string &signature);

        const std::string &name() const;
        void setName(const std::string &name);

        const std::string &signature() const;
        void setSignature(const std::string &signature);

    private:
        std::string mName;
        std::string mSignature;
    };
}

#endif //LIBMODIO_MODULE_H
