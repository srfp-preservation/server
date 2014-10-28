# SRFP Server for DOS

A SRFP server, written in C, for 32-bit DOS machines.

## Building

In order to build, you will need to download DJGPP, which can be downloaded from [GitHub Releases](https://github.com/andrewwutw/build-djgpp/releases), and make sure the directory containing the `i586-pc-msdosdjgpp-gcc` binary is on your `$PATH`.

Then, simply type `make`.

## Running

To run binaries compiled with DJGPP, your target machine needs a DPMI server. Download `csdpmi4b.zip` (you can get it from a number of sources, including [here](ftp://ftp.pl.freebsd.org/vol/rzm1/coast/vendors/djgpp/v2misc/csdpmi4b.zip)), extract it, and transfer it to your DOS machine along with the binary you just built. (The best way to do this is probably a FAT32-formatted 3.25" floppy, as you can buy USB 3.25" drives still.)

Once copied, run `CSDPMI4B.EXE` (from the ...)