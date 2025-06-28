NAME = webserv

SRCS = $(shell find src -name '*.cpp')

CXX ?= c++
CXXFLAGS += -Wall -Wextra -Werror -g3
CXXFLAGS += -std=c++98 -pedantic
CPPFLAGS += -Isrc -MMD -MP

OBJS := $(SRCS:%=build/%.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all
all: build

.PHONY: build
build: $(NAME)

.PHONY: run
run: build
	./$(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

# compiling stage
build/%.cpp.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: re
re: fclean build

.PHONY: clean
clean:
	rm -rf build/src

.PHONY: fclean
fclean: clean
	rm -rf build
	rm -rf $(NAME)

.PHONY: test
test:
	cmake -DCMAKE_BUILD_TYPE=DEBUG -S test -B build/test
	cmake --build build/test
	GTEST_COLOR=1 ctest --test-dir build/test $(CTEST_OPT)

.PHONY: vtest
ifneq ($(TEST_WITH_MEMCHECK),)
vtest: CTEST_OPT += -T memcheck
endif
vtest: CTEST_OPT += -V
vtest: test

.PHONY: run_memcheck
run_memcheck: SUPPRESSIONS_FILE = aux/rl_leaks.supp
run_memcheck: VALGRIND_FLAGS += --leak-check=full
run_memcheck: VALGRIND_FLAGS += --show-leak-kinds=all
run_memcheck: VALGRIND_FLAGS += --track-origins=yes
run_memcheck: VALGRIND_FLAGS += --suppressions=$(SUPPRESSIONS_FILE)
run_memcheck: VALGRIND_FLAGS += --trace-children=yes
run_memcheck: build
	valgrind $(VALGRIND_FLAGS) ./$(NAME)

.PHONY: update
update: clean
	mkdir -p build
	bear  --output build/compile_commands.json -- make build

# aliases
.PHONY: b c u r rm t vt
b: build
c: clean
u: update
r: run
rm: run_memcheck
t: test
vt: vtest

-include $(DEPS)
