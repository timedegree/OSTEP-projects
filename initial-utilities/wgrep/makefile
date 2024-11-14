TARGET = wgrep
TEST_SCRIPT = test-wgrep.sh
TEST_OUTPUT_DIR = tests-out

CC = gcc
CFLAGS = -Wall -Wextra -O2

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $@ $<

test: $(TARGET)
	./$(TEST_SCRIPT)

clean:
	rm -f $(TARGET)
	rm -rf $(TEST_OUTPUT_DIR)

.PHONY: all test clean
