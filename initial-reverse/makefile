TARGET = reverse
TEST_SCRIPT = test-reverse.sh
TEST_OUTPUT_DIR = tests-out

CC = gcc
CFLAGS = -Wall -Wextra -O2

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $@ $<

test: $(TARGET)
	./$(TEST_SCRIPT) $(TEST_FLAGS)

clean:
	rm -f $(TARGET) $(TARGET).o
	rm -rf $(TEST_OUTPUT_DIR)
	rm 2.out

.PHONY: all test clean
