#include "getline.h"

#include <unistd.h>
#include <map>

typedef std::string::size_type usize;

static const usize bufferSize = 64;

std::string getline(int fd) {
    static std::map<int, std::string> remainders;

    if (fd < 0) {
        return NULL;
    }

    std::string& rem = remainders[fd];  // inserts default cted if absent

    usize newline = rem.find('\n');
    if (newline != std::string::npos) {
        const std::string out = rem.substr(0, newline);
        rem = rem.substr(newline + 1, rem.size() - 1 - newline);
        return out;
    }

    std::string out = rem;
    rem.clear();

    char rawBuffer[bufferSize + 1] = {0};
    ssize_t bytesRead;
    std::string buffer;
    do {
        // might be possible to read directly into the std::string
        // but this is fine
        bytesRead = read(fd, rawBuffer, bufferSize);
        if (bytesRead < 0) {
            return NULL;
        } else if (bytesRead == 0 && out.empty()) {
            return NULL;
        }

        buffer = rawBuffer;
        std::memset(rawBuffer, 0, bufferSize);

        newline = buffer.find('\n');
        if (newline != std::string::npos) {
            const std::string out = buffer.substr(0, newline);
            rem = buffer.substr(newline + 1, buffer.size() - 1 - newline);
            return out;
        } else {
            out += buffer;
        }
    } while (bytesRead == bufferSize);

    return out;
}
