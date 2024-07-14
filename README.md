# Checkers Project

This project is a console-based implementation of the classic Checkers game using C++. It was developed as a final project for the Introduction to Programming Language course by Dr. Reza Entezari Maleki.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Rules](#rules)
- [Code Structure](#code-structure)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgements](#acknowledgements)

## Introduction

This Checkers game is designed to allow two players to enjoy the traditional game of Checkers through a console-based application. The game follows standard Checkers rules and includes functionality for moving pieces, capturing opponent pieces, and determining the winner.

## Features

- Console-based user interface
- Two-player mode
- Implementation of standard Checkers rules
- Clear and maintainable code structure
- Use of C++ Standard Library features such as vectors

## Installation

To run this project locally, follow these steps:

1. Clone the repository:
    ```sh
    git clone https://github.com/amirhosseineslami/checkers-project.git
    ```
2. Navigate to the project directory:
    ```sh
    cd checkers-project
    ```
3. Compile the code using a C++ compiler. For example, using g++:
    ```sh
    g++ checkers_main.cpp -o checkers
    ```

## Usage

After compiling the code, run the executable to start the game:
```sh
./checkers
```

Follow the on-screen instructions to play the game. Players take turns to move their pieces according to the rules of Checkers.

## Rules

1. **Movement**:
    - Pieces move diagonally forward.
    - Kings can move diagonally forward and backward.
2. **Capturing**:
    - Capture opponent pieces by jumping over them.
    - Multiple captures are allowed in a single turn.
3. **Winning**:
    - The game is won by capturing all opponent pieces or blocking them so they cannot move.

## Code Structure

- `Bead` Class: Represents a piece on the board with `x`, `y` coordinates and a `isKing` status.
- Main Functions:
  - `getExistBeadIndex(vector<Bead>, int, int)`: Gets the index of an existing bead.
  - `printBoard(vector<Bead>, vector<Bead>)`: Prints the current state of the board.
  - `addAllBeads(vector<Bead> *, vector<Bead> *)`: Initializes all beads on the board.
  - Various functions for checking valid moves and capturing pieces.
- `main()`: Initializes the game, prints the welcome message, and manages the game loop.

## Contributing

Contributions are welcome! If you have any suggestions or improvements, please create an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgements

- Dr. Reza Entezari Maleki for teaching the Introduction to Programming Language course.
- The C++ community for their valuable resources and support.
