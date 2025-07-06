#include <fcntl.h>
#include <unistd.h>

#include "gtest/gtest.h"

#include "IO/getline.h"

struct File {
    File(const std::string& path) : fd(open(path.c_str(), O_RDONLY)) {}
    File(int fd) : fd(fd) {}
    ~File() { close(fd); }
    int fd;
};

TEST(Getline, Nonexistant) {
    File f("./does_not_exist");
    ASSERT_EQ(f.fd, -1);

    ASSERT_FALSE(getline(f.fd).is());
}

const std::string dir = "../../test/GetlineTest/infiles";

TEST(Getline, ShortLines) {
    File f(dir + "/short_lines.txt");
    ASSERT_NE(f.fd, -1);

    Option<std::string> line = getline(f.fd);
    ASSERT_TRUE(line.is());
    ASSERT_TRUE(line.unwrap() == "444");

    line = getline(f.fd);
    ASSERT_TRUE(line.is());
    ASSERT_TRUE(line.unwrap() == "222");

    line = getline(f.fd);
    ASSERT_TRUE(line.is());
    ASSERT_TRUE(line.unwrap() == "000");

    line = getline(f.fd);
    ASSERT_FALSE(line.is());

    line = getline(f.fd);
    ASSERT_FALSE(line.is());

    line = getline(f.fd);
    ASSERT_FALSE(line.is());

    line = getline(f.fd);
    ASSERT_FALSE(line.is());
}

TEST(Getline, LongLines) {
    File f(dir + "/long_lines.txt");
    ASSERT_NE(f.fd, -1);

    const std::size_t length = 420;

    Option<std::string> line = getline(f.fd);
    ASSERT_TRUE(line.is());
    // std::cout << "line: " << line.unwrap() << std::endl;
    ASSERT_TRUE(line.unwrap() == std::string(length, '4'));

    line = getline(f.fd);
    ASSERT_TRUE(line.is());
    ASSERT_TRUE(line.unwrap() == std::string(length, '2'));

    line = getline(f.fd);
    ASSERT_TRUE(line.is());
    ASSERT_TRUE(line.unwrap() == std::string(length, '0'));

    line = getline(f.fd);
    ASSERT_FALSE(line.is());

    line = getline(f.fd);
    ASSERT_FALSE(line.is());

    line = getline(f.fd);
    ASSERT_FALSE(line.is());

    line = getline(f.fd);
    ASSERT_FALSE(line.is());
}
