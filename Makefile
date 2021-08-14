EXEC = cata
SRC_DIRS = src
SRCS = $(shell find $(SRC_DIRS) -name *.c)
OBJDIR = obj
OBJS = $(SRCS:.c=.o)
CFLAGS = -g -Wall -lm -ldl -fPIC -rdynamic -Iinclude

CC = gcc

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)