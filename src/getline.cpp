#include "getline.h"

#include <map>

typedef std::string::size_type usize;

static const usize bufferSize = 64;

std::string getline(int fd) {
    static std::map<int, std::string> remainders;

    if (fd < 0) {
        return NULL;
    }

    std::string& rem = remainders[fd];
    std::string out;

    usize maybeNewline = rem.find('\n');
    if (maybeNewline != std::string::npos) {
        out = rem.substr(0, maybeNewline);
        // rem = rem.subs
    }

    return out;
}
