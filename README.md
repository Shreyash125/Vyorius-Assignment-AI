# Vyorius Assignment AI: Movie Recommendation System in C++

Welcome to the **Vyorius Assignment AI** repository! This project implements a movie recommendation system in C++ that predicts the ratings a user would give to movies based on collaborative filtering. It uses historical user ratings to provide personalized movie recommendations.

The system uses **Collaborative Filtering** with **Cosine Similarity** to suggest movies that a user might enjoy. It ranks movies based on their predicted ratings for the user and also evaluates the recommendations' accuracy with **Root Mean Squared Error (RMSE)**.

## Features

- **Personalized Movie Recommendations**: Suggests movies based on your past ratings and similar users’ preferences.
- **Collaborative Filtering**: Uses **Cosine Similarity** to find similar users based on their ratings.
- **Movie Rating Predictions**: Predicts what ratings you would give to movies you haven't rated.
- **Evaluation**: Calculates **RMSE** to measure the quality of recommendations.
- **User-Friendly Interface**: Easy-to-use command-line interface to interact with the program.

## Getting Started

### 1. **Prepare Your Ratings Data**

The system requires a **CSV file** with ratings from multiple users for different movies. The CSV file should have movies as columns, users as rows, and their ratings in the matrix.

**Example data**:
```bash
Movie1, Movie2, Movie3, Movie4, Movie5
5, 3, 0, 1, 4
4, 0, 0, 1, 2
0, 1, 2, 4, 0
3, 0, 4, 0, 3

Where `0` means the user has not rated the movie, and any value between 1 and 5 represents the rating given by the user.
```

Where `0` means the user has not rated the movie, and any value between 1 and 5 represents the rating given by the user.

### 2. **Clone the Repository**

Clone the repository to your local machine:

```bash
git clone https://github.com/Shreyash125/Vyorius-Assignment-AI.git
```
3. Setup and Build the Project
Change to the project directory:
```bash
cd Vyorius-Assignment-AI
```
Compile the code (using g++ for example):
```bash
g++ -o movie_recommendation src/main.cpp
```
Run the program:
```bash
./movie_recommendation
```



Functions
Here’s a quick overview of what the program does behind the scenes:

loadRatingsFromFile(): Loads the ratings data from a CSV file.

calculateCosineSimilarity(): Compares two users and calculates how similar their ratings are.

predictUserRating(): Predicts a user’s rating for a movie they haven’t rated yet.

getTopNRecommendations(): Generates a list of top N recommended movies for a user.

calculateRMSE(): Computes the RMSE to evaluate how good the recommendations are.





