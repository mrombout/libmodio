#include <iostream>
#include <iomanip>
#include "reader/ModReader.h"

/**
 * \brief Tries to load the given .mod file and output some information
 *
 * This example tries to load the given .mod file and output some information
 * about that module if it was able to successfully load it. Everything should
 * be rather straightforward, however for clarity's sake the code is also
 * commented to further improve the understanding of what is happening exactly.
 */
int main(int argc, char *argv[]) {
    if(argc < 2) {
        std::cout << "usage: load_module <filename>" << std::endl;
        return -1;
    }

    std::ifstream in{argv[1]};
    modio::ModReader reader;
    modio::Module module{reader.read(in)};

    // output name
    std::cout << "Name: " << module.name() << "\n";

    // output signature
    std::cout << "Signature: " << module.signature() << "\n\n";

    // output samples
    std::cout << "Samples:\n";
    std::cout << std::string(67, '-') << "\n";
    std::cout << std::left << "| " << std::setw(22) << "File" << " | " << std::setw(6) << "Length" << " | " << std::setw(8) << "Finetune" << " | " << std::setw(6) << "Volume" << " | " << std::setw(9) << "Loop" << " |\n";
    std::cout << std::string(67, '-') << "\n";
    for(const modio::Sample &sample : module.samples()) {
        if(sample.length() != 0) {
            std::cout << std::left << "| " << std::setw(22) << sample.name() << " | " << std::setw(6) << sample.length() << " | " << std::setw(8) << 0 << " | " << std::setw(6) << sample.volume() << " | " << std::setw(4) << std::right << sample.repeatStart() << ":" << std::setw(4) << sample.repeatLength() << " |\n";
        }
    }
    std::cout << std::string(67, '-') << "\n\n";

    // output sequence
    std::cout << "Sequence:\n| ";
    for(unsigned int i = 0; i < module.length(); ++i) {
        std::cout << module.sequence().get(i) << " | ";
    }
    std::cout << "\n\n";

    // output patterns
    std::cout << "Patterns:\n";
    for(const modio::Pattern &pattern : module.patterns()) {
        std::cout << "   " << std::string(61, '-') << "\n";
        for(unsigned int j = 0; j < 64; ++j) {
            std::cout << std::setw(2) << std::right << std::dec << j << " | ";
            for(unsigned int i = 0; i < 4; ++i) {
                const modio::Channel &channel{pattern.channel(i)};
                const modio::Division &division{channel.get(j)};

                // output period
                std::cout << std::setw(2) << std::setfill('0') << std::hex << std::uppercase;
                if(division.period() == 0)
                    std::cout << "--";
                else
                    std::cout << division.period();
                std::cout << " ";

                // output sample
                if(division.sampleIndex() != 0) {
                    std::cout << std::setfill('0') << std::setw(2) << division.sampleIndex();

                    // output volume
                    std::cout << "v" << std::setfill('0') << std::setw(2) << module.samples().at(division.sampleIndex()).volume() << " ";
                } else {
                    std::cout << "-- -- ";
                }

                // output effect
                std::cout << std::hex;
                if(division.effect().raw() == 0)
                    std::cout << "---";
                else
                    std::cout << division.effect().raw();

                std::cout << " | ";
            }
            std::cout << "\n";
        }
        std::cout << "   " << std::string(61, '-') << "\n\n";
    }

    std::cin.ignore();
}
