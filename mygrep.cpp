#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>

std::string ignoreCase(std::string s){
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

void inputSearch () {
    std::string orgStr, searchStr;

    std::cout << "Give a string to search from: ";
    std::getline (std::cin, orgStr);

    std::cout << "Give a string to search for: ";
    std::getline (std::cin, searchStr);

    size_t match = orgStr.find(searchStr);

    if (match != std::string::npos) {
        std::cout << searchStr << " found in " << orgStr << " position " << match << std::endl;
    } else {
        std::cout << searchStr << " NOT found in " << orgStr << std::endl; 
    }
}

int main (int argc, char* argv[]){
    
    /*--- INKRAMENTTI 1 ---*/
    inputSearch();

    /*--- INKRAMENTTI 2, 3, 4 ---*/
    std::string file;
    std::string fileSearchStr;


    bool linenumbering, occurance, reverse;
    bool found = false;
    
    // if there is option selected, find what options were selected
    if (argc == 4){
       file = argv [3];
       fileSearchStr = argv[2];

        for (int i = 2; i <= strlen(argv[1]); i++){
            if (argv [1][i] == 'i'){
                fileSearchStr = ignoreCase (argv[2]);
            } 
            
            if (argv [1][i] == 'l') {
                linenumbering = true;
            }

            if (argv [1][i] == 'o') {
                occurance = true;
            } 

            if (argv [1][i] == 'r') {
                reverse = true;
            } 
        }
    }

    // if there are no option selected
    else if (argc == 3) {
        file = argv [2];
        fileSearchStr = argv[1];
    }

    std::ifstream in (file);
    
    // check file is open
    if (!in.is_open()) {
        std::cerr << "An exception occurred. Exception Nr. -1\nCould not find out the size of file '" << file << std::endl;
        return 1;
    }

    std::string line;
    
    // numbers of line and occurences
    int linenum, occurence, reverseOccurence = 0;

    while (getline(in,line)){
        linenum++;

        // search string line finding
        if (line.find(fileSearchStr) != std::string::npos && !reverse) {
        
            if (linenumbering){
                std::cout << linenum << ": ";
            }

            if (occurance) {
                occurence++;
            }

            std::cout << line << std::endl;
            found = true;
        }
        
        // reversed line
        else if ((line.find(fileSearchStr) == std::string::npos) && reverse) {
            
            if (linenumbering){
                std::cout << linenum << ": ";
            }

            if (occurance) {
                reverseOccurence++;
            }

            std::cout << line << std::endl;
            found = true;
        }

    }

    in.close();

    // occurance output of found line with search string
    if (occurance && !reverse) {
        std::cout << "Occurrences of lines containing " << '"' << fileSearchStr << '"' << ": " << occurence << std::endl;
    } 
    
    // occurance output of reserved line
    if (reverse && occurance) {
        std::cout << "Occurrences of line NOT containing " << '"' << fileSearchStr << '"' << ": " << reverseOccurence << std::endl;
    }

    if (!found) {
        std::cerr << "Searched string was not found on document. Check spelling." << std::endl;
    }

    return 0;
}