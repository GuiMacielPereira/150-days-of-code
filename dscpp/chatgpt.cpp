/* 
 * It is damn insane that chatgpt managed to produce a cleaner and better solution than me 
 * This thing worked at the first try I am flabergasted what the actual fuck
 */

#include <iostream>
#include <random>

std::string generateRandomString(int length) {
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz ";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, alphabet.size() - 1);

    std::string result;
    for (int i = 0; i < length; ++i) {
        result += alphabet[dis(gen)];
    }
    return result;
}

int scoreString(const std::string& generated, const std::string& target) {
    int score = 0;
    for (size_t i = 0; i < target.size(); ++i) {
        if (generated[i] == target[i]) {
            score++;
        }
    }
    return score;
}

void simulateMonkeyTyping(const std::string& target) {
    const int targetLength = target.size();
    std::string bestString = generateRandomString(targetLength);
    int bestScore = scoreString(bestString, target);

    int tries = 0;
    while (bestScore < targetLength) {
        std::string newString = bestString;
        int indexToChange = std::rand() % targetLength;
        newString[indexToChange] = generateRandomString(1)[0]; // Change one character

        int newScore = scoreString(newString, target);

        // In the case where the character picked is already correct, the change is ignored
        if (newScore > bestScore) {
            bestString = newString;
            bestScore = newScore;
        }
        // Print progress every 1000 tries
        if (tries % 1000 == 0) {
            std::cout << "Try " << tries << ": " << bestString << " (Score: " << bestScore << "/" << targetLength << ")\n";
        }
        tries++;
    }

    std::cout << "Success! Found the target string: " << bestString << " (Score: " << bestScore << "/" << targetLength << ")\n";
}

int main() {
    std::string targetString = "methinks it is like a weasel";
    simulateMonkeyTyping(targetString);

    return 0;
}
