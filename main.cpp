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

#define TO_CHAR(x) static_cast<char>(x)

static char logo[] = "the\n"
    "  ___  ____\n"
    " / _ \\/ ___| \n"
    "| | | \\___ \\ \n"
    "| |_| |___) |\n"
    " \\___/|____/ compiler";


static double version = 0.01;
static char build_type[] = "alpha";

//The compile function transforms the source code (basic-type language) into a hex array
void compile(char* out, const std::string& source) {            //assumes the out parameter is 512 bytes long
    if constexpr (sizeof(out)!=512) {
        std::cerr<<"out array too long"<<std::endl;
    }
    //filling the whole out with zeroes
    for (int i = 0;i<509;i++) {
        out[i] = 0x00;
    }
    //operating systems must end with signature 0x55AA
    out[510] = TO_CHAR(0x55);
    out[511] = TO_CHAR(0xAA);
}

static void write_hex_file(std::ofstream* output_file, const char* source) {
    output_file->write(source, 512);
}

static int get_user_action(const int argc, char** argv) {
    if (argc==1) {
        return 0;               // no argument selected
    }if (std::string(argv[1])=="version"||std::string(argv[1])=="-v") {
        return 1;               //shows version and build
    }return 2;                  //just compile the project
}


static std::string get_source_from_file(std::ifstream* input_file) {
    std::string source;
    source.assign(std::istreambuf_iterator(*input_file),std::istreambuf_iterator<char>());
    return source;
}

int main(const int argc, char** argv) {
    switch (get_user_action(argc, argv)) {
        case 0: {
            std::cout<<logo<<"\n"<<std::endl;
            std::cerr<<"No action selected."<<std::endl;
            return 1;
        }
        case 1: {
            std::cout<<logo<<"\n"<<std::endl;
            std::cout<<"The Os Compiler is currently on "<<build_type<<" and on build "<<version<<std::endl;
            return 0;
        }
        case 2: {
            std::ofstream output("out.bin", std::ios::binary);
            std::ifstream input(argv[1]);
            std::string source = get_source_from_file(&input);
            char out_hex[512];
            compile(out_hex, source);
            write_hex_file(&output, out_hex);
            input.close();
            output.close();
            return 0;
        }
        default:
            std::cerr<<"no idea of what is supposed to be here..."<<std::endl;
    }
    return 0;
}
