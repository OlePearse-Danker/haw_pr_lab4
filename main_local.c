// --------------------
// Tic-Tac-Toe
// Praktikumsaufgabe 4 
// Ole Pearse-Danker
// 19.11.2022
// Version 1.0
// --------------------

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>


void resetBoard(int[3][3]);         // setzt alle Zeilen und Spalten wieder auf ein leeres Kästchen
void printBoard(int[3][3]);         // Druckt das Board
int checkFreeSpaces (int[3][3]);    // überprüft, wie viele Kästchen/welche Kästchen noch frei sind
void playerMove (int[3][3]);        // fordert Benutzer:in auf Koordinaten anzugeben / überprüft ob diese Koordinaten schon vergeben sind
void computerMove (int[3][3]);      // generiert eine zufällige Koordinate (zwei Zahlen zwischen 0 und 2/ überprüft ob diese Koordinaten schon vergeben sind
char checkWinner (int[3][3]);       // überprüft ob es eine Spalte/Zeile oder Diagonale gibt, die  nur aus einem "X" oder "0" besteht
void printWinner (char);            // gibt gewinner aus


int main (void)
{

    int _board [3][3];              // mehrdimensionaler Vektor der das Board darstellt
    
    char ch;                        // Variable für die Wiederholungseingabe (erneutes Spiel)
    
    do
    {

        // clear terminal for better UX
        system("clear");

        printf("--------------------------------------------------------------------------\n");
        printf("Herzlich Willkommen bei Tic-Tac-Toe!\n");
        printf("Im folgenden können Sie gegen den Computer Tic-Tac-Toe spielen.\n");
        printf("--------------------------------------------------------------------------\n");
        printf("Geben Sie zuerst eine Zeile und dann eine Spalte an. Viel Spaß!\n");
        printf("--------------------------------------------------------------------------\n");
        

        char winner = ' '; // if winner is an empty space -> currently no winner -> if winner is X -> Player won

        resetBoard(_board); //gibt das leere Board am Anfang des Spiels aus

        while (winner == ' ' &&  checkFreeSpaces(_board) != 0) // if winner is currently equal to empty space -> means there currently is no winner 
        {                                                // there are still free spaces -> game has to go on!   
            
            printBoard(_board);

            
            // PLAYER ACTIONS
            playerMove(_board);
            winner = checkWinner(_board);
            if (winner != ' ' || checkFreeSpaces(_board) == 0)  // if winner does not equal an empty space -> there is a winner
            {                                             // if return value of checkFreeSpaces is equal to 0 -> break out of while loop
                break;
            }

        
            // COMPUTER ACTIONS
            computerMove(_board);
            winner = checkWinner(_board);
            if (winner != ' ' || checkFreeSpaces(_board) == 0)  // if winner does not equal an empty space -> there is a winner
            {                                                   // OR if return value of checkFreeSpaces is equal to 0 -> break out of while loop
                break;
            }
            
            system("clear");
        }
        
        printBoard(_board); //Board muss noch einmal gedruckt, sonst wird der letzte Schritt vor dem Gewinn nicht angezeigt
        printWinner(winner);

        // Zusatzaufgabe 2 -> Fragen ob man wiederholen möchte
        printf("Wollen Sie noch einmal spielen? (j/n)");
        scanf (" %c", &ch);                             //Leertaste zwischen vor %c ist wichtig!
    } while(ch == 'j');

    printf("Schade. Das Programm wird jetzt beendet.\n");

    return 0;
}

//---------------------
//Funkionsdefinitionen
//---------------------

void resetBoard(int _board[3][3]) //Funktion setzt alle Zeilen und Spalten wieder auf ein leeres Kästchen
{

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            _board[i][j] = ' '; // each element within this 2d array of charracters will be an empty space
        }
    }
}

void printBoard(int _board[3][3]) // Druckt das Board
{
   
    printf(" %c | %c | %c ", _board[0][0], _board[0][1], _board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", _board[1][0], _board[1][1], _board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", _board[2][0], _board[2][1], _board[2][2]);
    printf("\n");

}

int checkFreeSpaces (int _board[3][3]) //Funktion überprüft, welche Kästchen noch frei sind
{
  
    int freeSpaces = 9;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (_board[i][j] != ' ')    // checking if 2d array of characters is not equal to an empty space (occupied)
            {
                freeSpaces--;           // if 2d array of characters is occupied -> decrement freespaces by one
            }
            
        }
        
    }
    return freeSpaces;                  // if this return statements returns zero -> game is over because there is no place left the player can move to
}

void playerMove (int _board[3][3])      //
{

    int PLAYER = 'X';

    int x;                               //Variable für die Zeileneingabe
    int y;                               //Variable für die Spalteneingabe

    do
    {
        printf("Geben Sie eine Zeile ein #(1-3): ");
        scanf("%d", &x);
        x--;                             // whatever the user types, we will decrement x by one -> because computer starts counting at 0 not 1

        printf("Geben Sie eine Spalte ein #(1-3): ");
        scanf("%d", &y);
        y--;     

        if (_board[x][y] != ' ')         // checking to see if the coordinates the user gave us are occupied or not
        {
            printf("Ungültiger Zug, dieses Kästchen ist schon besetzt!\n");
        }
        else                             // spot is still available
        {
            _board[x][y] = PLAYER;
            break;                       // break out of the while loop beacause user entered valid input
        }
    } while (_board[x][y] != ' ');       // repeating input demand for as long as the user tries to fill out spots that are already occupied
                                   
}

void computerMove (int _board[3][3])
{

    int COMPUTER  = 'O';

    //creates a seed based on current time
    srand(1);
    int x;
    int y;

    if (checkFreeSpaces(_board) > 0)          // if FreeSpaces are greater than 0 -> generate random numbers
    {
        do
        {
            x = rand () % 3;            // generate random numbers between 0 and 2 
            y = rand () % 3;

        } while (_board[x][y] != ' ');   // checking to see if generated spot is even open
                                        // keep generating numbers until there is an open space

        _board[x][y] = COMPUTER;         // if there is an open space -> paste random numbers by Computer
    }
    else                                // if there are no more spaces avaiable -> invoke printWinner function
    {
        printWinner(' ');               // Free spaces -> there is no winner, it is a draw!
    }
    
}

char checkWinner (int _board[3][3])
{


    // check rows
    for (int i = 0; i < 3; i++)
    {
        if (_board[i][0] == _board[i][1] && _board[i][0] == _board[i][2] )      // checking to see if top left element is equal to middle element 
        {                                                                   // and if top left element is equal to top right element  
            return _board[i][0];                                             // return whatever character is in here -> character = winner!

        }      
    }

    // check columns
    for (int i = 0; i < 3; i++)
    {
        if (_board[0][i] == _board[1][i] && _board[0][i] == _board[2][i] )     
        {                                                                  
            return _board[0][i];                                             

        }      
    }

    // check diagonals (top left - bottom right)
    for (int i = 0; i < 3; i++)
    {
        if (_board[0][0] == _board[1][1] && _board[0][0] == _board[2][2] )     
        {                                                                  
            return _board[0][0];                                            
        }      
    }

    // check diagonals (bottom left - top right)
     for (int i = 0; i < 3; i++)
    {
        if (_board[0][2] == _board[1][1] && _board[0][2] == _board[2][0] )     
        {                                                                  
            return _board[0][2];                                            
        }     
    }

    return ' ';                                     // if after all this checking there still is not a winner -> return empty character

} 

void printWinner (char winner)
{

    int PLAYER = 'X';
    int COMPUTER = 'O';

    if (winner == PLAYER)
    {
        printf("--------------------------------\n");
        printf("Glückwunsch! Sie haben gewonnen!\n");
        printf("--------------------------------\n");
    }
    else if (winner == COMPUTER)
    {
        printf("------------------------------------------\n");
        printf("Das war leider nichts! Sie haben verloren.\n");
        printf("------------------------------------------\n");
    }
    else 
    {
        printf("--------------\n");
        printf("Unentschieden!\n");
        printf("--------------\n");
    }
    
}