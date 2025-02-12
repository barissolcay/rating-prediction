#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

//-----------------------------------------------------------------------------
// This structure stores each user's (UserID) movie ratings.
//-----------------------------------------------------------------------------
typedef std::unordered_map<int, double> MovieRatings;
typedef std::unordered_map<int, MovieRatings> UserMovieRatings;

static const int K_NEIGHBORS = 50;

// Cosine similarity calculation
double computeCosineSimilarity(const MovieRatings& userARatings,
                               const MovieRatings& userBRatings) {
    double dotProduct = 0.0;
    double normA = 0.0;
    double normB = 0.0;

    for (const auto& kv : userARatings) {
        int movieID = kv.first;
        double ratingA = kv.second;

        auto itB = userBRatings.find(movieID);
        if (itB != userBRatings.end()) {
            double ratingB = itB->second;
            dotProduct += (ratingA * ratingB);
        }
        normA += (ratingA * ratingA);
    }

    for (const auto& kv : userBRatings) {
        double ratingB = kv.second;
        normB += (ratingB * ratingB);
    }

    if (normA == 0.0 || normB == 0.0) {
        return 0.0;
    }

    return dotProduct / (std::sqrt(normA) * std::sqrt(normB));
}

// Predicts the rating for a specific user (targetUser) and movie (targetMovie).
double predictRating(int targetUser, int targetMovie,
                     const UserMovieRatings& allData) {
    auto targetUserIt = allData.find(targetUser);
    if (targetUserIt == allData.end()) {
        return 3.0;
    }

    std::vector<std::pair<int, double>> neighborSimilarities;
    neighborSimilarities.reserve(allData.size());
    const auto& targetUserRatings = targetUserIt->second;

    for (const auto& userPair : allData) {
        int otherUser = userPair.first;
        if (otherUser == targetUser) {
            continue;
        }

        const auto& otherUserRatings = userPair.second;
        if (otherUserRatings.find(targetMovie) == otherUserRatings.end()) {
            continue;
        }

        double sim = computeCosineSimilarity(targetUserRatings, otherUserRatings);
        neighborSimilarities.push_back({otherUser, sim});
    }

    std::sort(neighborSimilarities.begin(), neighborSimilarities.end(),
              [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
                  return a.second > b.second;
              });

    if (neighborSimilarities.empty()) {
        return 3.0;
    }

    double sumWeightedRatings = 0.0;
    double sumSimilarities = 0.0;

    for (int i = 0; i < (int)neighborSimilarities.size() && i < K_NEIGHBORS; i++) {
        int neighborID = neighborSimilarities[i].first;
        double similarity = neighborSimilarities[i].second;
        double neighborRating = allData.at(neighborID).at(targetMovie);

        sumWeightedRatings += similarity * neighborRating;
        sumSimilarities += similarity;
    }

    return (sumSimilarities > 0) ? sumWeightedRatings / sumSimilarities : 3.0;
}

// Reads the input format with "train dataset" and "test dataset" sections.
void loadInputData(const std::string& inputFile, UserMovieRatings& trainData,
                   std::vector<std::pair<int, int>>& testData) {
    std::ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        std::cerr << "Could not open input file: " << inputFile << std::endl;
        exit(1);
    }

    std::string line;
    bool isTrain = true;

    while (std::getline(inFile, line)) {
        if (line.empty()) {
            continue;
        }

        if (line == "train dataset") {
            isTrain = true;
            continue;
        } else if (line == "test dataset") {
            isTrain = false;
            continue;
        }

        std::stringstream ss(line);
        if (isTrain) {
            int userID, movieID;
            double rating;
            if (ss >> userID >> movieID >> rating) {
                trainData[userID][movieID] = rating;
            }
        } else {
            int userID, movieID;
            if (ss >> userID >> movieID) {
                testData.push_back({userID, movieID});
            }
        }
    }

    inFile.close();
}

// Main function
int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    UserMovieRatings trainData;
    std::vector<std::pair<int, int>> testData;

    loadInputData(inputFile, trainData, testData);

    std::ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        std::cerr << "Could not create output file: " << outputFile << std::endl;
        return 1;
    }

    for (const auto& test : testData) {
        int userID = test.first;
        int movieID = test.second;

        double predictedRating = predictRating(userID, movieID, trainData);
        outFile << predictedRating << std::endl;   // Write output to file
        std::cout << "Prediction written: " << predictedRating << std::endl; // Show output on terminal
    }

    outFile.close();
    std::cout << "Predictions written to '" << outputFile << "'." << std::endl;
    return 0;
}
