/*
 *OS Compiler
 *by Nolan Bazin (rguy83667@gmail.com)
 *
 *Credits:
 *asciiart.eu for the ascii art
 */

#include <iostream>
#include <fstream>

static char logo[] = "the\n"
    "  ___  ____\n"
    " / _ \\/ ___| \n"
    "| | | \\___ \\ \n"
    "| |_| |___) |\n"
    " \\___/|____/ compiler";



static bool generate_compilation_file(char* filename) {                    //SO-Compiler uses nasm, later, it could use other things
    std::ofstream cfile("./compile.bat");
    cfile<<"nasm -f BIN "<<filename<<" -o ./output.bin"<<std::endl;

    return false;
}


static int get_user_action(int argc, char** argv) {
    if (argc==1) {
        return 0;               // no argument selected
    }if (argv[1]=="--version"||argv[1]=="-v") {
        return 1;
    }
}


int main(int argc, char** argv) {
    int choice = get_user_action(argc, argv);
    switch (choice) {
        case 0:
        case 1:
            std::cout<<logo;
    }
    return 0;
}
