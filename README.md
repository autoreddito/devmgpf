devgoatse
=========

(VSFW) (V is for very)

Linux Kernel module for creating /dev/mgpf character device.

/dev/mgpf creates a mgpf gif.

This device could be very useful for sbirrinfamia.
    
Dependencies
=======

In order to compile the kernel module you should have the latest version of your Linux kernel headers.

On Ubuntu/Debian you can install them using:

    sudo apt-get install linux-headers-$(uname -r)

Installation and use
=======

    make
    ./mgpf_register.sh
