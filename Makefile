srfp.exe: srfp.c vendor/svasync/libsv.a
	i586-pc-msdosdjgpp-gcc -Wall -osrfp.exe srfp.c vendor/svasync/libsv.a

copy: srfp.exe
	cp srfp.exe /Volumes/XFER/

vendor/svasync/libsv.a:
	cd vendor/svasync; make libsv.a

clean:
	rm -f srfp.exe
	cd vendor/svasync; make clean
