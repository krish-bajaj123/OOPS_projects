import <iostream>;
import <fstream>;
import <string>;
import <sstream>;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <start_word> <end_word> <words_file>" << std::endl;
        return 1;
    }
    std::ifstream file(argv[3]);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open the file" << std::endl;
        return 1;
    }
    std::string word, words;
    while (file >> word) words += word + " ";
    file.close();
    if (words.find(argv[1]) == std::string::npos || words.find(argv[2]) == std::string::npos) {
        std::cerr << "Error: Starting or ending word not found in word file" << std::endl;
        return 1;
    }
    std::string current = argv[1];
    int chain = 0, best = chain;
    std::cout << "Starting Word: " << argv[1] << std::endl;
    while (std::cin >> word) {
        if (words.find(word) == std::string::npos) {
            std::cerr << "Error: " << word << " does not belong to the word file" << std::endl;
            continue;
        }
        if (word == argv[2]) {
            std::cout << "Congratulations! Your Score: " << chain << " Best Score: " << best << std::endl;

            if (chain < best || best == 0) best = chain;

            chain = 0;
            std::cout << "Starting Word: " << argv[1] << std::endl;
            continue;
        }
        if (word.length() != current.length()) {
            std::cerr << "Error: Word length must be equal to start/end words" << std::endl;
            continue;
        }
        int diffs = 0;
        for (size_t i = 0; i < word.length(); ++i)
            if (word[i] != current[i]) ++diffs;

        if (diffs != 1) {
            std::cerr << "Error: " << word << " does not differ from " << current << " by one character" << std::endl;
            continue;
        }

        current = word;
        ++chain;
    }
    return 0;
}

