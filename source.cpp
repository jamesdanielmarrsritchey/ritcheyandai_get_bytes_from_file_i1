#include <fstream>
#include <iostream>
#include <vector>
#include <getopt.h>

int main(int argc, char *argv[]) {
    std::string filename;
    std::streampos min_byte, max_byte;

    struct option long_options[] = {
        {"file", required_argument, 0, 'f'},
        {"min_byte", required_argument, 0, 'm'},
        {"max_byte", required_argument, 0, 'M'},
        {0, 0, 0, 0}
    };

    int opt;
    int option_index = 0;
    while ((opt = getopt_long(argc, argv, "f:m:M:", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'f':
                filename = optarg;
                break;
            case 'm':
                min_byte = std::stoll(optarg);
                break;
            case 'M':
                max_byte = std::stoll(optarg);
                break;
            default:
                std::cerr << "Invalid arguments\n";
                return 1;
        }
    }

    if (min_byte > max_byte) {
        std::cerr << "Minimum byte number cannot be higher than maximum byte number\n";
        return 1;
    }

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    std::streamsize size = file.tellg();
    if (size < min_byte) {
        std::cerr << "File size is less than minimum byte number\n";
        return 1;
    }

    file.seekg(min_byte);
    std::vector<char> bytes(max_byte - min_byte);
    file.read(bytes.data(), bytes.size());

    for (char byte : bytes) {
        std::cout << byte;
    }

    return 0;
}