#include <iostream>
//No forced tie system in place. If so, we are assuming perfect play.
void printSeperator();
void clearScreen();
void displayBoard();
void makeHumanMove();
bool isAValidMove(int row, int column);
void getIcons();
void makeComputerMove();
int minMax(char arr[3][3], bool iscomputer);
int status(char arr[3][3]);
void checkTie(int n);

char board[3][3] = {{' ', ' ', ' '},
                    {' ', ' ', ' '},
                    {' ', ' ', ' '}};
char iconuser;
char iconcomputer;

int main(){
    int choice = -1;
    int moves = 0;
    getIcons();
    std::cout <<"This is the user: "<<iconuser<<std::endl;
    std::cout <<"This is the computer: "<<iconcomputer<<std::endl;
    do{
        clearScreen();
        std::cout <<"Do you Want to start first? \n 1 for Yes 0 for no: ";
        std::cin >>choice;
    }while(choice != 0 && choice != 1);

    while(status(board) != 1){
        choice %= 2;
        if(choice == 0){
            makeComputerMove();
            moves++;
            choice++;
            checkTie(moves);
            continue;
        }
        else{
            makeHumanMove();
            moves++;
            choice++;
            checkTie(moves);
            continue;
        }
        
    }
    displayBoard();
    std::cout <<"you losttt\n";
    std::cout <<"Hint: its impossible to win, as long as the laws of physics don't change.";
}

void checkTie(int n){
    if(n == 9){
        clearScreen();
        printSeperator();
        displayBoard();
        printSeperator();
        std::cout <<"You tied!!!!\nGood job.\n";
        std::exit(0);

    }
}

int status(char arr[3][3]){
    char temp = 'F';
    if(arr[0][0] != ' ' && arr[0][0] == arr[0][1] && arr[0][1] == arr[0][2]){
        temp = arr[0][0];
    }
    if(arr[1][0] != ' ' && arr[1][0] == arr[1][1] && arr[1][1] == arr[1][2]){
        temp = arr[1][0];
    }
    if(arr[2][0] != ' ' && arr[2][0] == arr[2][1] && arr[2][1] == arr[2][2]){
        temp = arr[2][0];
    }

    if(arr[0][0] != ' ' && arr[0][0] == arr[1][0] && arr[1][0] == arr[2][0]){
        temp = arr[0][0];
    }
    if(arr[0][1] != ' ' && arr[0][1] == arr[1][1] && arr[1][1] == arr[2][1]){
        temp = arr[0][1];
    }
    if(arr[0][2] != ' ' && arr[0][2] == arr[1][2] && arr[1][2] == arr[2][2]){
        temp = arr[0][2];
    }

    if(arr[0][0] != ' ' && arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2]){
        temp = arr[0][0];
    }
    if(arr[2][0] != ' ' && arr[2][0] == arr[1][1] && arr[1][1] == arr[0][2]){
        temp = arr[2][0];
    }
    if(temp == iconcomputer){
        return 1;
    }
    if(temp == iconuser){
        return 2;
    }

    for(int r = 0; r < 3; r++){
        for(int c = 0; c < 3; c++){
            if(arr[r][c] == ' '){
                return 69;
            }
        }
    }
    return 0;
}

int maximize(int first, int second){
    if(first > second){
        return first;
    }
    return second;
}

int minimize(int first, int second){
    if(first < second){
        return first;
    }
    return second;
}

int minMax(char arr[3][3], bool iscomputer){
    switch(status(arr)){
        case(0): return 0;
        case(1): return 10;
        case(2): return -10;
        case(69): {};
    }
    if(iscomputer){
        int best = -99999;
        for(int r = 0; r < 3; r++){
            for(int c = 0; c < 3; c++){
                if(arr[r][c] == ' '){
                    arr[r][c] = iconcomputer;
                    best = maximize(best, minMax(arr, !iscomputer));
                    arr[r][c] = ' ';
                }
            }
        }
        return best;
    }
    else{
        int best = 999999;
        for(int r = 0; r < 3; r++){
            for(int c = 0; c < 3; c++){
                if(arr[r][c] == ' '){
                    arr[r][c] = iconuser;
                    best = minimize(best, minMax(arr, !iscomputer));
                    arr[r][c] = ' ';
                }
            }
        }
        return best;
    }
}

void makeComputerMove(){
    int best_one_so_far = 0;
    int b_row;
    int b_column;
    for(int r = 0; r < 3; r++){
        for(int c = 0; c < 3; c++){
            if(board[r][c] == ' '){
                board[r][c] = iconcomputer;
                int currentOne = minMax(board, false);
                if(currentOne >= best_one_so_far){
                    best_one_so_far = currentOne;
                    b_row = r;
                    b_column = c;
                }
                board[r][c] = ' ';
            }

        }
    }
    board[b_row][b_column] = iconcomputer;
    
}

void makeHumanMove(){
    std::string message_to_be_displayed = "";
    while(true){
        int column = -1;
        int row = -1;
        int error = 0;
        do{
            clearScreen();
            printSeperator();
            displayBoard();
            printSeperator();
            std::cout <<message_to_be_displayed;
            if(error >0){
                std::cout <<"Put in actual cords pal.\n";
                printSeperator();
            }
            std::cout <<"Please enter your column and Row of choice in this format of coordinates 'CR': ";
            std::cin >>column;
            row = column % 10;
            column /= 10;
            error++;
        }while(row > 3 || row <= 0 || column > 3 || column <= 0);
        clearScreen();
        std::cout <<"column = "<<column<<'\n';
        std::cout <<"row = "<<row<<"\n";
        row -= 1;
        column -= 1;

        if(isAValidMove(row, column)){
            board[row][column] = iconuser;
            return;
        }
        else{
            message_to_be_displayed = "Last spot was full pal.\n";
            continue;
        }
    }
}

bool isAValidMove(int row, int column){
    if(board[row][column] == ' '){
        return true;
    }
    return false;
}

void getIcons(){
    int choice;
    char computer;
    do{
    clearScreen();
    std::cout <<"choose the icon u want to use for your player model.\n";
    std::cout <<"1 = X\n2 = O\n: ";
    std::cin >> choice;
    }while(choice != 1 && choice != 2);
    clearScreen();
    switch(choice){
        case(1):{
            iconuser = 'X';
            iconcomputer = 'O';
            break;
        }
        default:{
            iconuser = 'O';
            iconcomputer = 'X';
            break;
        }
    }
}

void clearScreen(){
    std::cout <<"\033[2J" <<std::flush;

    }

void printSeperator(){
    std::cout << "************************************\n";
    }

void displayBoard(){
    int counter = 1;
    std::cout <<"   1   2   3";
    for(int row = 0; row < 3; row++){
        std::cout <<'\n'<<counter<<" ";
        counter++;

        for(int i = 0; i < 3; i++){
            std::cout <<'['<<board[row][i]<<"] ";
        }
    }
    std::cout <<'\n';
}
