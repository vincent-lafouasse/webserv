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

const std::string dir = "../../test/GetlineTest";

TEST(Getline, ShortLines) {
    File f(dir + "/short_lines.txt");
    ASSERT_NE(f.fd, -1);

    S s = getline(f.fd);
    ASSERT_TRUE(s);
    ASSERT_TRUE(s.get() == "444");

    s = getline(f.fd);
    ASSERT_TRUE(s);
    ASSERT_TRUE(s.get() == "222");

    s = getline(f.fd);
    ASSERT_TRUE(s);
    ASSERT_TRUE(s.get() == "000");

    s = getline(f.fd);
    ASSERT_FALSE(s);

    s = getline(f.fd);
    ASSERT_FALSE(s);

    s = getline(f.fd);
    ASSERT_FALSE(s);

    s = getline(f.fd);
    ASSERT_FALSE(s);
}
