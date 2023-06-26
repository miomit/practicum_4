CC = gcc
CFLAGS = -Wall -g
SRCDIR = source
TESTDIR = test
BUILDDIR := build
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRCS))
TESTSRCS = $(wildcard $(TESTDIR)/*.c)
TESTOBJS = $(patsubst $(TESTDIR)/%.c, $(BUILDDIR)/%.o, $(TESTSRCS))
TARGET = $(BUILDDIR)/program
TESTTARGET = $(BUILDDIR)/tests
RUN_TESTS_ON_MAKE := 0

ifeq ($(filter test,$(MAKECMDGOALS)),test)
	RUN_TESTS_ON_MAKE := 1
	BUILDDIR := build/test
endif

ifeq ($(RUN_TESTS_ON_MAKE),1)
	CFLAGS += -DRUN_TESTS_ON_MAKE
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(TESTDIR)/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

$(TESTTARGET): $(TESTOBJS) $(OBJS)
	$(CC) $(CFLAGS) -o $(TESTTARGET) $(TESTOBJS) $(OBJS)

build:
	mkdir -p $(BUILDDIR)

test: $(TESTTARGET)
	./$(TESTTARGET)

run: all
	./$(TARGET)

clean:
	rm -rf $(BUILDDIR)

.PHONY: all build clean test
