test.exe: test.c vendor
	i586-pc-msdosdjgpp-gcc -Wall -otest.exe test.c vendor/svasync/libsv.a

copy: test.exe
	cp test.exe /Volumes/XFER/

vendor/svasync/libsv.a:
	cd vendor/svasync; make libsv.a