#include <iostream>
#include <sstream>

//Helper function used to check if the line is empty or has a whitespace.
bool helper1(const std::string& str) {
    if (str.empty()) {
        return true;
    }
    for (size_t i = 0; i < str.size(); ++i) {
        char c = str[i];
        if (!isspace(c)) {
            return false;
        }
    }

    return true;
}

//Helper function used to check if the line contains digits or not.
bool helper2(const std::string& str) {
    for (size_t i = 0; i < str.size(); ++i) {
        char c = str[i];
        if (isdigit(c)) {
            return true;
        }
    }
    return false;
}

//Helper function to convert string to int.
int helper3(const std::string& str) {
    std::stringstream ss(str);
    int result;
    ss >> result;
    return result;
}

int main(int argc, char* argv[]) {
    int x = (argc > 1) ? helper1(argv[1]) : 0;
    std::string names[10];
    int votes[100][10];
    int spoiled = 0;
    int valid = 0;
    int candidates = 0;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (!helper2(line) && !helper3(line)) {
            if (candidates < 10) {
                names[candidates] = line;
                ++candidates;
            } else {
                std::cerr << "Error." << std::endl;
                return 1;
            }
        } else {
            std::istringstream iss(line);
            int vote;
            int i = 0;

            while (iss >> vote && i < 10) {
                votes[valid][i] = vote;
                ++i;
            }
            if (i == candidates) {
                int sumvotes = 0;
                for (int j = 0; j < i; ++j) {
                    sumvotes += votes[valid][j];
                }
                if (sumvotes <= (x == 0 ? candidates : x)) {
                    ++valid;
                } else {
                    ++spoiled;
                }
            } else {
                ++spoiled;
            }
        }
    }
    std::cout << "Number of voters: " << valid + spoiled << std::endl;
    std::cout << "Number of valid ballots: " << valid << std::endl;
    std::cout << "Number of spoilt ballots: " << spoiled << std::endl;
    std::cout << "\nCandidate: Score" << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < candidates; ++i) {
        int score = 0;
        std::cout << names[i] << ": ";

        for (int j = 0; j < valid; ++j) {
            score += votes[j][i];
        }
        std::cout << score << std::endl;
    }
    return 0;
}
