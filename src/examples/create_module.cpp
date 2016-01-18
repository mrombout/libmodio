#include "Note.h"
#include "Pattern.h"
#include "Sample.h"
#include "Module.h"

int main(int argc, char **argv) {
    modio::Sample sample1{"Name"};

    modio::Module module;

    modio::Pattern pattern1;
    pattern1.set(0, 1, modio::Note('C', 6), sample1);
}