CFLAGS= -Wall -fpic -coverage -lm 

testme: testme.c
	gcc -o testme -g  testme.c $(CFLAGS)

unittestresults: testme

	rm -rf unittestresults.out
	echo "testme: " >> unittestresults.out
	./testme >> unittestresults.out

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out *.dSYM testme