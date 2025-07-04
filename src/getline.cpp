#include "getline.h"

#include <map>

typedef std::string::size_type usize;

static const usize bufferSize = 64;

std::string getline(int fd) {
    static std::map<int, std::string> remainders;

    if (fd < 0) {
        return NULL;
    }

    std::string& rem = remainders[fd];  // what if there's nothing there

    usize newline = rem.find('\n');
    if (newline != std::string::npos) {
        const std::string out = rem.substr(0, newline);
        rem = rem.substr(newline + 1, rem.size() - 1 - newline);
        return out;
    }

    std::string out = rem;
    rem.clear();

    return out;
}
