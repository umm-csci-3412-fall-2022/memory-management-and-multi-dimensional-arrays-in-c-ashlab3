test: array_merge.c array_merge_test.cpp array_merge.h
	g++ -Wall -g -o test array_merge.c array_merge_test.cpp ../mergesort/mergesort.c -lgtest -pthread -std=c++0x


main: array_merge.c main.c array_merge.h
	gcc -Wall -g -o main array_merge.c main.c ../mergesort/mergesort.c

clean:
	rm test
	rm main