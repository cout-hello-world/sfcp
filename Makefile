CFLAGS = -std=c11 -Wall -Wextra -O3 -march=native

sfcp: sfcp.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	$(RM) sfcp
