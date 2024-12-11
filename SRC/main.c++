#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

// Load user ratings from a CSV file
vector<vector<int>> loadRatingsFromFile(const string &fileName) {
    ifstream file(fileName);
    vector<vector<int>> ratings;
    string line;

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << fileName << endl;
        exit(1);
    }

    while (getline(file, line)) {
        stringstream lineStream(line);
        string cell;
        vector<int> userRatings;

        while (getline(lineStream, cell, ',')) {
            try {
                userRatings.push_back(stoi(cell));
            } catch (const invalid_argument&) {
                cerr << "Error: Invalid data in file." << endl;
                exit(1);
            }
        }

        ratings.push_back(userRatings);
    }

    return ratings;
}

// Calculate cosine similarity between two users
double calculateCosineSimilarity(const vector<int>& ratings1, const vector<int>& ratings2) {
    double dotProduct = 0.0, norm1 = 0.0, norm2 = 0.0;

    for (size_t i = 0; i < ratings1.size(); ++i) {
        if (ratings1[i] != 0 && ratings2[i] != 0) {
            dotProduct += ratings1[i] * ratings2[i];
            norm1 += ratings1[i] * ratings1[i];
            norm2 += ratings2[i] * ratings2[i];
        }
    }

    if (norm1 == 0 || norm2 == 0) return 0.0;

    return dotProduct / (sqrt(norm1) * sqrt(norm2));
}

// Predict a user's rating for a movie
double predictUserRating(const vector<vector<int>>& ratings, int targetUser, int movieIndex, const vector<vector<double>>& similarityMatrix) {
    double weightedSum = 0.0, totalSimilarity = 0.0;

    for (size_t i = 0; i < ratings.size(); ++i) {
        if (i != targetUser && ratings[i][movieIndex] != 0) {
            double similarity = similarityMatrix[targetUser][i];
            weightedSum += similarity * ratings[i][movieIndex];
            totalSimilarity += abs(similarity);
        }
    }

    if (totalSimilarity == 0) return 0.0;

    return weightedSum / totalSimilarity;
}

// Recommend top N movies for a user
vector<int> getTopNRecommendations(const vector<vector<int>>& ratings, int targetUser, int N, const vector<vector<double>>& similarityMatrix) {
    vector<pair<int, double>> predictedRatings;

    for (size_t movieIndex = 0; movieIndex < ratings[0].size(); ++movieIndex) {
        if (ratings[targetUser][movieIndex] == 0) {
            double predictedRating = predictUserRating(ratings, targetUser, movieIndex, similarityMatrix);
            predictedRatings.push_back({movieIndex, predictedRating});
        }
    }

    sort(predictedRatings.begin(), predictedRatings.end(), [](const pair<int, double>& a, const pair<int, double>& b) {
        return a.second > b.second;
    });

    vector<int> topMovies;
    for (int i = 0; i < N && i < predictedRatings.size(); ++i) {
        topMovies.push_back(predictedRatings[i].first);
    }

    return topMovies;
}

// Calculate RMSE for the recommendation system
double calculateRMSE(const vector<vector<int>>& ratings, const vector<vector<double>>& similarityMatrix) {
    double errorSum = 0.0;
    int ratedMoviesCount = 0;

    for (size_t userIndex = 0; userIndex < ratings.size(); ++userIndex) {
        for (size_t movieIndex = 0; movieIndex < ratings[userIndex].size(); ++movieIndex) {
            if (ratings[userIndex][movieIndex] != 0) {
                double predictedRating = predictUserRating(ratings, userIndex, movieIndex, similarityMatrix);
                errorSum += pow(ratings[userIndex][movieIndex] - predictedRating, 2);
                ++ratedMoviesCount;
            }
        }
    }

    if (ratedMoviesCount == 0) return 0.0;

    return sqrt(errorSum / ratedMoviesCount);
}

int main() {
    string fileName = "../data/ratings.csv";
    vector<vector<int>> ratings = loadRatingsFromFile(fileName);

    if (ratings.empty()) {
        cerr << "Error: No ratings data loaded." << endl;
        return 1;
    }

    int userCount = ratings.size();
    int movieCount = ratings[0].size();

    for (const auto& userRatings : ratings) {
        if (userRatings.size() != movieCount) {
            cerr << "Error: Inconsistent ratings data." << endl;
            return 1;
        }
    }

    vector<vector<double>> similarityMatrix(userCount, vector<double>(userCount, 0.0));

    for (int i = 0; i < userCount; ++i) {
        for (int j = 0; j < userCount; ++j) {
            similarityMatrix[i][j] = calculateCosineSimilarity(ratings[i], ratings[j]);
        }
    }

    int topN = 3;
    vector<int> topRecommendations = getTopNRecommendations(ratings, 0, topN, similarityMatrix);

    cout << "Top " << topN << " movie recommendations for user 0: ";
    for (int movieIndex : topRecommendations) {
        cout << "Movie " << movieIndex + 1 << " ";
    }
    cout << endl;

    double rmse = calculateRMSE(ratings, similarityMatrix);
    cout << "RMSE of the system: " << rmse << endl;

    return 0;
}
