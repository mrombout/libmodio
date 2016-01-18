#ifndef LIBMODIO_SAMPLE_H
#define LIBMODIO_SAMPLE_H

#include <string>

namespace modio {
    class Sample {
    public:
        Sample();
        Sample(const std::string &name);
        Sample(const std::string &name, unsigned int volume);
        Sample(const std::string &name, unsigned int volume, unsigned int repeatStart, unsigned int repeatLength);

        void setName(const std::string &name);
        const std::string &name() const;

        unsigned int length() const;

        void setVolume(unsigned int volume);
        unsigned int volume() const;

        void setRepeatStart(unsigned int repeatStart);
        unsigned int repeatStart() const;

        void setRepeatLength(unsigned int repeatLength);
        unsigned int repeatLength() const;

    private:
        std::string mName;

        unsigned int mLength; // TODO: Should get from actual sample data
        unsigned int mVolume;

        unsigned int mRepeatStart;
        unsigned int mRepeatLength;

        char mData[];
    };
}

#endif //LIBMODIO_SAMPLE_H
