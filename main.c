#include <iostream>
#include <fstream>
#include <vector>
#include <map>

const char NETWORK = '.';
const char MALWARE = '*';
const char FIREWALL = 'f';
const char HEALTHY = 'o';
const char INFECTED = 'x';

int checkNeighbours(std::map<char, int> &neighbours, char target) {
    auto foundElem = neighbours.find(target);

    if (neighbours.end() != foundElem) {
        return foundElem->second;
    }
    return 0;
}

auto checkNeighbours(std::vector<std::vector<char>> &board, int j, int k) {
    std::map<char, int> neighbours;
    int height = board.size();
    int width = board.at(0).size();
    if (k - 1 >= 0) {
        neighbours[board[j][k - 1]]++;
        if (j - 1 >= 0) {
            neighbours[board[j - 1][k - 1]]++;
        }
        if (j + 1 < height) {
            neighbours[board[j + 1][k - 1]]++;
        }
    }

    if (k + 1 < width) {
        neighbours[board[j][k + 1]]++;

        if (j - 1 >= 0) {
            neighbours[board[j - 1][k + 1]]++;
        }
        if (j + 1 < height) {
            neighbours[board[j + 1][k + 1]]++;
        }
    }

    if (j - 1 >= 0) {
        neighbours[board[j - 1][k]]++;
    }
    if (j + 1 < height) {
        neighbours[board[j + 1][k]]++;
    }

    return neighbours;
}

char networkCellOptions(std::map<char, int> &neighbours) {

    int malwareNeighbours = checkNeighbours(neighbours, MALWARE);
    if (malwareNeighbours >= 2 && malwareNeighbours < 5) {
        return '*';
    }
    if (checkNeighbours(neighbours, HEALTHY) == 2)
        return 'f';
    if (checkNeighbours(neighbours, INFECTED) >= 1) {
        return '*';
    }
    return '.';
}

char malwareCellOptions(std::map<char, int> &neighbours) {

    if (checkNeighbours(neighbours, NETWORK) == 8)
        return '.';
    if (checkNeighbours(neighbours, FIREWALL) >= 2) {
        return 'f';
    }
    if (checkNeighbours(neighbours, MALWARE) > 5 ) {
        return '.';
    }
    if (checkNeighbours(neighbours, HEALTHY) >= 1) {
        return '.';
    }
    return '*';
}

char firewallCellOptions(std::map<char, int> &neighbours) {

    if (checkNeighbours(neighbours, MALWARE) >= 5 ) {
        return '.';
    }
    return 'f';
}

char healthyServerOptions(std::map<char, int> &neighbours) {

    if (checkNeighbours(neighbours, MALWARE) >= 1 ) {
        return 'x';
    }
    return 'o';
}

char infectedServerOptions(std::map<char, int> &neighbours) {

    if (checkNeighbours(neighbours, FIREWALL) == 8) {
        return 'o';
    }
    return 'x';
}


void mutate(std::vector<std::vector<char>>& board,
            std::vector<std::vector<char>>& newBoard,
            int j, int k) {

    char current = board[j][k];
    char newCell = ' ';

    std::map<char, int> checkedNeighbours = checkNeighbours(board, j, k);

    switch (current) {
        case '.' :
            newCell = networkCellOptions(checkedNeighbours);    break;
        case '*' :
            newCell = malwareCellOptions(checkedNeighbours);    break;
        case 'f' :
            newCell = firewallCellOptions(checkedNeighbours);   break;
        case 'o' :
            newCell = healthyServerOptions(checkedNeighbours);  break;
        case 'x' :
            newCell = infectedServerOptions(checkedNeighbours); break;
        default: std::cerr << "invalid cell\n" << j << " " << k << " "
                           << current << "new cell:[" << newCell << "]\n";
    }

    newBoard[j][k] = newCell;
}

void printBoard(std::vector<std::vector<char>> &board) {
    for (int j = 0; j < board.size(); ++j) {
        for (int k = 0; k < board[0].size() + 1; ++k) {
            char c = board[j][k];
            std::cout << c;
        }
        std::cout << '\n';
    }
}

int main( int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "input file not provided\n";
        return 1;
    }

    std::ifstream file;
    file.open(argv[1], std::ios_base::binary | std::ios_base::in);

    int iterationCount = 0;
    int width = 0;
    int height = 0;
    if (file.is_open()) {
        file >> iterationCount;
        file >> width;
        file >> height;
        file.get(); // last '\n'
    } else {
        return 1;
    }


    std::vector<std::vector<char>> board(height);
    for (auto& row : board) {
        row.resize(width);
        for(int i = 0; i < width; ++i) {
            row[i] = file.get();
//            std::cout << row[i];
        }
        file.get();
    }

    std::vector<std::vector<char>> newBoard = board;

    std::vector<std::vector<char>>* editingBoard = &newBoard;
    std::vector<std::vector<char>>* oldBoard = &board;

    for (int i = 0; i < iterationCount; ++i) {
        for (int j = 0; j < height; ++j) {
            for (int k = 0; k < width; ++k) {
                mutate(*oldBoard, *editingBoard, j, k);
            }
        }
        std::swap(oldBoard, editingBoard);
    }

    printBoard(board);
    return 0;
}
