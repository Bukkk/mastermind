mastermind.a: mastermind.o mastermind_representation.o heuristics_data.o
	# ar \
	# rcs build/mastermind.a \
	# build/mastermind.o \
	# build/mastermind_representation.o \
	# build/heuristics_data.o

mastermind.o:
	clang $(FLAGS) \
	-c -o build/mastermind.o \
	impl/mastermind.c

mastermind_representation.o:
	clang $(FLAGS) \
	-c -o build/mastermind_representation.o \
	impl/mastermind_representation.c

heuristics_data.o:
	clang $(FLAGS) \
	-c -o build/heuristics_data.o \
	impl/heuristics_data.c

clean:
	rm build/*.o build/*.a