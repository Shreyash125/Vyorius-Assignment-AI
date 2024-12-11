#Movie Recommendation System in C++
Welcome to the Movie Recommendation System project! This is a simple C++ implementation that suggests movies to users based on their past ratings and the ratings of others. The goal is to predict what movies a user might enjoy, even if they haven’t rated them yet.

The system uses a technique called Collaborative Filtering to find similarities between users based on their ratings. It then predicts ratings for movies that the user hasn't seen, and generates a ranked list of recommendations.

Features
Personalized Movie Recommendations: Recommends movies based on your ratings and the preferences of similar users.
Collaborative Filtering: We use Cosine Similarity to calculate how similar users are to each other based on their movie ratings.
Movie Rating Predictions: The system predicts what rating you might give to a movie you haven't rated yet.
Evaluation: After generating recommendations, it calculates the Root Mean Squared Error (RMSE) to measure how accurate the predictions are.
User-Friendly Interface: The program is designed to be interactive and easy to use, with clear prompts and outputs.

1. Prepare Your Ratings Data
The system requires a CSV file containing the movie ratings. The file should have ratings for different users, with movies in columns and users in rows.

For example:

Copy code
Movie1, Movie2, Movie3, Movie4, Movie5
5, 3, 0, 1, 4
4, 0, 0, 1, 2
0, 1, 2, 4, 0
3, 0, 4, 0, 3
Where 0 means the user hasn't rated the movie, and any number between 1 and 5 represents a rating.

2. Download and Setup
Clone the repository to your local machine:

bash
Copy code
git clone https://github.com/your-username/movie-recommendation-cpp.git
Change to the project directory:

bash
Copy code
cd movie-recommendation-cpp
Compile the code: If you're using GCC:

bash
Copy code
g++ -o movie_recommendation src/main.cpp
Run the program:

bash
Copy code
./movie_recommendation
3. Run the Program
The program will ask for the following:

The path to your CSV file (e.g., data/ratings.csv).
The target user ID (Which user’s recommendations you want).
The number of movie recommendations (How many movies you want the system to suggest).
After you enter the information, the program will give you a ranked list of recommended movies for that user. It will also show the RMSE value to let you know how accurate the recommendations are.

Functions
Here’s a quick overview of what the program does behind the scenes:

loadRatingsFromFile(): Loads the ratings data from a CSV file.
calculateCosineSimilarity(): Compares two users and calculates how similar their ratings are.
predictUserRating(): Predicts a user’s rating for a movie they haven’t rated yet.
getTopNRecommendations(): Generates a list of top N recommended movies for a user.
calculateRMSE(): Computes the RMSE to evaluate how good the recommendations are.
