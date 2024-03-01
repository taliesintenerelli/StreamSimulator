# StreamSimulatorCPP: Streaming Service Simulation

## Project Overview
StreamSimulatorCPP is an academic project simulating a streaming service, similar to Netflix or Hulu, developed from scratch. This C++ application implements object-oriented programming principles to emulate real-world streaming service functionalities.

## Key Features
- **Memory Management:** Employed dynamic memory allocation and pointers for efficient data manipulation and object management.
- **Object-Oriented Design**: Utilizes inheritance and polymorphism for modeling movies, series, and user interactions.
- **Data Parsing and Management**: Custom parsers for JSON and a unique compact data format to initialize with varied datasets.
- **Algorithm Development**: Implements login, search, content viewing, review submissions, and content recommendation based on user history.
- **Exception Handling**: Ensures system integrity with custom exceptions for user and parsing errors.

## Technologies
- C++
- JSON
- Git

## Getting Started

### Prerequisites
- C++ compiler (e.g., g++, clang)
- Make (optional for building)
- Git (for version control)

### Installation

1. Clone the repository:
   git clone https://github.com/taliesintenerelli/StreamSimulatorCPP.git
   cd StreamSimulatorCPP

2. Build the project (if using Make):
   make all

   Or compile manually:
   g++ -std=c++11 -o streamapp content.cpp user.cpp main.cpp

## Usage

Run the application from the command line:
./streamapp datafile.cus
Replace "datafile.cus" with the path to your data file.

### Commands:
- `LOGIN`: Authenticate a user (e.g., 1 username)
- `LOGOUT`: Log out the current user (e.g., 2)
- `GET USER HISTORY`: Retrieve viewing history for the logged-in user (e.g., 3)
- `SEARCH`: Search for content (e.g., 4 * for all content or 4 MovieName for specific content)
- `WATCH`: View a movie or series (e.g., 5 content-id)
- `REVIEW`: Add a review (e.g., 6 content-id stars)
- `SUGGEST SIMILAR`: Get suggestions based on viewing history (e.g., 7 content-id)

## Contributions and Learning Outcomes
This project improved my expertise in programming, system design, and practical application of algorithms. It showcases my capability to convert complex specifications into functional software, reinforcing problem-solving and coding proficiencies.
