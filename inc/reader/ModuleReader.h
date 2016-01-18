#ifndef LIBMODIO_MODULEREADER_H_H
#define LIBMODIO_MODULEREADER_H_H

namespace modio {
    class ModuleReader {
    public:
        virtual ~ModuleReader() {

        }

        virtual void read() const = 0;
    };
}

#endif //LIBMODIO_MODULEREADER_H_H
