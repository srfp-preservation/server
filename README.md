# SRFP Server for DOS

A SRFP server, written in C, for 32-bit DOS machines.

## Building

In order to build, you will need to download DJGPP, which can be downloaded from [GitHub Releases](https://github.com/andrewwutw/build-djgpp/releases), and make sure the directory containing the `i586-pc-msdosdjgpp-gcc` binary is on your `$PATH`.

Then, simply type `make`.

## Running

To run binaries compiled with DJGPP, your target machine needs a DPMI server. Download `csdpmi4b.zip` (you can get it from a number of sources, including [here](ftp://ftp.pl.freebsd.org/vol/rzm1/coast/vendors/djgpp/v2misc/csdpmi4b.zip)), and extract the `CWSDPMI.EXE` file.

Copy `SRFP.EXE` and `CWSDPMI.EXE` to your DOS machine. Connect the modern machine to `COM1`, and run `SRFP`.

### Running in Virtualbox

To run the SRFP server in Virtualbox, you'll need to set up a DOS virtual machine, then go to **Ports** &rarr; **Serial Ports** &rarr; **Port 1**. Enable it, set the port mode to **Host Pipe**, ensure **Create Pipe** is checked, then type any path you like in **Port/File Path**.

This will create a Unix domain socket for your client to connect to at the path you specified.

Finally, copy the files onto a floppy drive image, and mount it in Virtualbox.

## Contributors and Licensing

### SRFP Server for DOS

Written by by Adam Brenecki, with project management assistance from Adrian Colbert.

It is licensed under the GNU AGPL - see the file `LICENSE`.

### SVAsync

SRFP Server for DOS uses the SVAsync serial library, which was created by Samuel Vincent.

For licensing details, see the file `vendor/svasync/SVASYNC.DOC` (which, despite the file extension, is a plain text file and not a Word document).