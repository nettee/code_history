# setting compiler and compile options
CC      = gcc
LD      = ld
CFLAGS  = -ggdb -MD -Wall -Werror -fno-strict-aliasing -I./include -O2

# target to compile
CFILES  = $(shell find src/ -name "*.c")
OBJS    = $(CFILES:.c=.o)

# test files
TESTFILE = testcase/asm/mov
C_TEST_FILE_LIST = $(shell find testcase/c/ -name "*.c")
S_TEST_FILE_LIST = $(shell find testcase/asm/ -name "*.S")
TEST_FILE_LIST = $(C_TEST_FILE_LIST:.c=) $(S_TEST_FILE_LIST:.S=)

nemu: $(OBJS)
	$(CC) -o nemu $(OBJS) $(CFLAGS) -lreadline

$(TEST_FILE_LIST):
	cd `dirname $@` && make

loader: src/elf/loader.c

src/elf/loader.c: $(TESTFILE)
	objcopy -S -O binary -j .text $(TESTFILE) loader
	xxd -i loader > $@
	rm loader

run: nemu
	./nemu -d $(TESTFILE) 2>&1 | tee log.txt

gdb: nemu
	gdb --args ./nemu -dq $(TESTFILE)

test: nemu $(TEST_FILE_LIST)
	bash test.sh $(TEST_FILE_LIST)

-include $(OBJS:.o=.d)

clean:
	-rm -f nemu $(OBJS) $(OBJS:.o=.d) log.txt 2> /dev/null
