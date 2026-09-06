# The Os Compiler 
**by Nolan Bazin**

- Please note that due to a strict school schedule, I will not be able to update the project for a while. This is also why the project is **still unfinished and probably full of bugs**

## Introduction
**The OS Compiler** is a special compiler that, instead of turning the original file into an executable file ran by the computer's os, turns the file into **The** os.

## How to use it:
* make a file. I prefer the .osc extension but, truly, you can use any.
* write your program. Please note that the program is still very broken, and that only very few instructions work.
* compile it using the syntax ``./os_compiler ./<your file name>.osc``
* This will produce an out.bin file.

## How to run the output?
### qemu:
**To run the file in qemu**, you have to run the command: ``qemu-system-i386 ./out.img`` (you can change the architecture if you want, but I don't recommend it)

### online: 
You can also run the file on online emulators such as https://www.v86.run/
To do that: 
* On the site, click "Floppy"
* When prompted to enter a file, put in the out.img file
* click "Start"
* enjoy.

