FLAGS= -g -o2 -std=c17 -Wpedantic

export

all: test zadanie2

zadanie2: mastermind.a
	clang $(FLAGS) \
	-o build/zadanie2 \
	mastermind/build/*.o \
	main.c

test: mastermind.a
	clang $(FLAGS) \
	-o build/test \
	mastermind/build/*.o \
	test_mastermind.c

mastermind.a:
	$(MAKE) -C mastermind

clean:
	rm build/*.o build/zadanie2 build/test;