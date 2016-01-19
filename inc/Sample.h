#ifndef LIBMODIO_SAMPLE_H
#define LIBMODIO_SAMPLE_H

#include <string>
#include <vector>

namespace modio {
    class Sample {
    public:
        Sample();
        Sample(const std::string &name);
        Sample(const std::string &name, unsigned int volume);
        Sample(const std::string &name, unsigned int volume, unsigned int repeatStart, unsigned int repeatLength);

        void setName(const std::string &name);
        const std::string &name() const;

        void resize(unsigned int length);
        unsigned int length() const;

        void setVolume(unsigned int volume);
        unsigned int volume() const;

        void setRepeatStart(unsigned int repeatStart);
        unsigned int repeatStart() const;

        void setRepeatLength(unsigned int repeatLength);
        unsigned int repeatLength() const;

    private:
        std::string mName;

        unsigned int mVolume;

        unsigned int mRepeatStart;
        unsigned int mRepeatLength;

        std::vector<char> mData;
    };
}

#endif //LIBMODIO_SAMPLE_H
