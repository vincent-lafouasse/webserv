#include <fcntl.h>
#include <unistd.h>

#include "gtest/gtest.h"

#include "getline.h"

typedef Option<std::string> S;

struct File {
    File(const std::string& path) : fd(open(path.c_str(), O_RDONLY)) {}
    File(int fd) : fd(fd) {}
    ~File() { close(fd); }
    int fd;
};

TEST(Getline, Nonexistant) {

    File f("./does_not_exist");
    ASSERT_EQ(f.fd, -1);

    ASSERT_FALSE(getline(f.fd));
}
