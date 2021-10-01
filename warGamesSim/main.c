#include <iostream>
#include <fstream>
#include <vector>


int checkNeighbours(std::vector<std::vector<char>> &board, int j, int k, char target) {
    int height = board.size();
    int width = board.at(0).size();
    int counter = 0;
    if (k - 1 >= 0) {
        if (board[j][k - 1] == target)
            ++counter;
        if (j - 1 >= 0 && board[j - 1][k - 1] == target)
            ++counter;
        if (j + 1 < height && board[j + 1][k - 1] == target)
            ++counter;
    }

    if (k + 1 < width) {
        if (board[j][k + 1] == target)
            ++counter;
        if (j - 1 >= 0 && board[j - 1][k + 1] == target)
            ++counter;
        if (j + 1 < height && board[j + 1][k + 1] == target)
            ++counter;
    }

    if (j - 1 >= 0 && board[j - 1][k] == target)
        ++counter;
    if (j + 1 < height && board[j + 1][k] == target)
        ++counter;

    return counter;
}

int checkNetworkNeighbours(std::vector<std::vector<char>> &board, int j, int k) {
    return checkNeighbours(board, j, k, '.');
}

int checkMalwareNeighbours(std::vector<std::vector<char>> &board, int j, int k) {
    return checkNeighbours(board, j, k, '*');
}

int checkFirewallNeighbours(std::vector<std::vector<char>> &board, int j, int k) {
    return checkNeighbours(board, j, k, 'f');
}

int checkHealthyNeighbours(std::vector<std::vector<char>> &board, int j, int k) {
    return checkNeighbours(board, j, k, 'o');
}

int checkInfectedServerNeighbours(std::vector<std::vector<char>> &board, int j, int k) {
    return checkNeighbours(board, j, k, 'x');
}

void networkCellOptions(std::vector<std::vector<char>>& board,
                        std::vector<std::vector<char>>& newBoard,
                        int j, int k) {
    int malwareNeighbours = checkMalwareNeighbours(board, j, k);
    if (malwareNeighbours >= 2 && malwareNeighbours < 5) {
        newBoard[j][k] = '*';
    }
    if (checkHealthyNeighbours(board, j, k) == 2)
        newBoard[j][k] = 'f';
    if (checkInfectedServerNeighbours(board, j, k) >= 1) {
        newBoard[j][k] = '*';
    }
}



void malwareCellOptions(std::vector<std::vector<char>>& board,
                        std::vector<std::vector<char>>& newBoard,
                        int j, int k) {
    if (checkNetworkNeighbours(board, j, k) == 8)
        newBoard[j][k] = '.';
    if (checkFirewallNeighbours(board, j, k) >= 2) {
        newBoard[j][k] = 'f';
    }
    if (checkMalwareNeighbours(board, j, k) > 5 ) {
        newBoard[j][k] = '.';
    }
    if (checkHealthyNeighbours(board, j, k) >= 1) {
        newBoard[j][k] = '.';
    }
}

void firewallCellOptions(std::vector<std::vector<char>>& board,
                         std::vector<std::vector<char>>& newBoard,
                         int j, int k) {
    if (checkMalwareNeighbours(board, j, k) >= 5 ) {
        newBoard[j][k] = '.';
    }
}

void healthyServerOptions(std::vector<std::vector<char>>& board,
                          std::vector<std::vector<char>>& newBoard,
                          int j, int k) {
    if (checkMalwareNeighbours(board, j, k) >= 1 ) {
        newBoard[j][k] = 'x';
    }
}

void infectedServerOptions(std::vector<std::vector<char>>& board,
                           std::vector<std::vector<char>>& newBoard,
                           int j, int k) {
    if (checkFirewallNeighbours(board, j, k) == 8) {
        newBoard[j][k] = 'o';
    }
}

void mutate(std::vector<std::vector<char>>& board,
            std::vector<std::vector<char>>& newBoard,
            int j, int k) {

    char current = board[j][k];
    switch (current) {
        case '.' : networkCellOptions(board, newBoard, j, k);    break;
        case '*' : malwareCellOptions(board, newBoard, j, k);    break;
        case 'f' : firewallCellOptions(board, newBoard, j, k);   break;
        case 'o' : healthyServerOptions(board, newBoard, j, k);  break;
        case 'x' : infectedServerOptions(board, newBoard, j, k); break;
        default: std::cerr << "invalid cell\n" << j << " " << k << " " << current;
    }
}

void printBoard(std::vector<std::vector<char>> &board){
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
        board = newBoard;
    }

    printBoard(board);
    return 0;
}
