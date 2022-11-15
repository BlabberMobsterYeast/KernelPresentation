there are two parts of linux operating system
user space and kernel space

user space contains programs that are the least priviledged
(meaning they do not have direct access to hardware and instead communicate with hardware using api's exposed by kernel modules running in kernel space) Example of user space programs are Firefox, terminal, music player, notepadqq.

the purpose of kernel modules are to provide api to user space programs to talk to hardware.

The aforementioned hardware does not need to by real physical hardware (we can create a custom virtual device).

The loadable driver can be written in C language although most of the C libraries are not available. Instead we have to use linux kernel C libraries.

here are necessary libraries that must be included:

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

