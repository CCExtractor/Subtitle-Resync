int count_words(std::string string) {
    // count the number of words in a given string
    return std::regex_match(string, std::regex("\\w+")).size();
}

int count_chars(std::string string) {
    // count the number of characters in a given string
    return string.length();
}

int count_lines(std::string file) {
    // count the number of lines in a given file
    std::ifstream f(file);
    std::string line;
    int num_lines = 0;
    while (std::getline(f, line)) {
        num_lines++;
    }
    return num_lines;
}

int count_blank_lines(std::string file) {
    // count the number of blank lines in a given file
    std::ifstream f(file);
    std::string line;
    int num_blank_lines = 0;
    while (std::getline(f, line)) {
        if (line.length() == 0) {
            num_blank_lines++;
        }
    }
    return num_blank_lines;
}

std::map<std::string, int> subtitle_quality(std::string file) {
    // calculate the subtitle quality metrics for a given file
    int num_lines = count_lines(file);
    int num_blank_lines = count_blank_lines(file);
    int num_words = 0;
    int num_chars = 0;
    std::ifstream f(file);
    std::string line;
    while (std::getline(f, line)) {
        if (line.length() != 0) {
            num_words += count_words(line);
            num_chars += count_chars(line);
        }
    }
    float avg_chars_per_line = (float)num_chars / (num_lines - num_blank_lines);
    float avg_words_
