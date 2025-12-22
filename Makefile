CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRC = Mastermind_principal.c mastermind_utilities.c mastermind_storage.c
OBJ = $(SRC:.c=.o)
EXEC = programme

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)