# Rating Prediction

Rating Prediction is a project that involves predicting movie ratings based on user similarities. The system reads user ratings from a training dataset and predicts ratings for a test dataset using the cosine similarity between users.

## Project Overview

Rating Prediction is developed using C++ and provides a system for predicting movie ratings based on collaborative filtering. The project uses cosine similarity to find the most similar users and predict ratings accordingly.

### Features

The project includes:
1. **Collaborative Filtering**: Predict ratings based on the similarity between users.
2. **Cosine Similarity**: Calculate the cosine similarity between user ratings.
3. **Command Line Interface**: Read input data from files and write predictions to an output file.
4. **Efficient Data Structures**: Use of hash maps for efficient storage and retrieval of user ratings.

## Technologies Used

- **C++**: The primary programming language used for developing the rating prediction system.

## Project Structure

The project structure includes several directories and files organized as follows:

- **`main.cpp`**: The main file that contains the implementation of the rating prediction system.
- **`input.txt`**: The input file containing the training dataset and test dataset.
- **`output_predictions.txt`**: The output file containing the predicted ratings.

## Usage

### Prerequisites

To run the project, you need to have the following installed:
- **C++ Compiler**: Ensure you have a C++ compiler installed on your system.

### Running the Project

1. Clone the repository:

    ```bash
    git clone https://github.com/barissolcay/rating-prediction.git
    cd rating-prediction
    ```

2. Compile the C++ file:

    ```bash
    g++ main.cpp -o rating-prediction
    ```

3. Run the Rating Prediction System with input and output files:

    ```bash
    ./rating-prediction input.txt output_predictions.txt
    ```

## Contributing

We welcome contributions to improve the Rating Prediction project. Feel free to open issues or submit pull requests if you have suggestions for improvements or find any bugs.

## License

MIT License

```markdown
MIT License

Copyright (c) 2025 Baris Solcay

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
