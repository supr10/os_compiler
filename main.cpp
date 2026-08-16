/*
 *OS Compiler
 *by Nolan Bazin (rguy83667@gmail.com)
 *
 *Credits:
 *asciiart.eu for the ascii art
 */

#include <iostream>
#include <fstream>
#include <string>

static char logo[] = "the\n"
    "  ___  ____\n"
    " / _ \\/ ___| \n"
    "| | | \\___ \\ \n"
    "| |_| |___) |\n"
    " \\___/|____/ compiler";

static double version = 0.01;
static char build_type[] = "alpha";

static bool generate_compilation_file(char* filename) {                    //SO-Compiler uses nasm, later, it could use other things
    std::ofstream cfile("./compile.bat");
    cfile<<"nasm -f BIN "<<filename<<" -o ./output.bin"<<std::endl;

    return false;
}


static int get_user_action(int argc, char** argv) {
    if (argc==1) {
        return 0;               // no argument selected
    }if (std::string(argv[1])=="version"||std::string(argv[1])=="-v") {
        return 1;               //shows version and build
    }return 2;                  //just compile the project
}


int main(int argc, char** argv) {
    int choice = get_user_action(argc, argv);
    switch (choice) {
        case 0:
            std::cout<<logo<<"\n"<<std::endl;
            std::cerr<<"No action selected."<<std::endl;
            return 1;
        case 1:
            std::cout<<logo<<"\n"<<std::endl;
            std::cout<<"The Os Compiler is currently on "<<build_type<<" and on build "<<version<<std::endl;
            return 0;

    }
    return 0;
}
