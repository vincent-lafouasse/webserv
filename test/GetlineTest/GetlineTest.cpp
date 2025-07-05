#include <unistd.h>
#include <fcntl.h>

#include "gtest/gtest.h"

#include "getline.h"

struct File {
    File(const std::string& path): fd(open(path.c_str(), O_RDONLY)) {}
    File(int fd): fd(fd) {}
    ~File() { close(fd); }
    int fd;
};

TEST(Getline, Dummy) {
    File f("./main.cpp");

    std::string line;
    SUCCEED();
}
