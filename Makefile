test.exe: test.c vendor/svasync/libsv.a
	i586-pc-msdosdjgpp-gcc -Wall -otest.exe test.c vendor/svasync/libsv.a

copy: test.exe
	cp test.exe /Volumes/XFER/

vendor/svasync/libsv.a:
	cd vendor/svasync; make libsv.a

clean:
	rm -f test.exe
	cd vendor/svasync; make clean
