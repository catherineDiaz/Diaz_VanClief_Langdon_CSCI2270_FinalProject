/*
    Title: Movie Database

    Author: Catherine Diaz
            Marcus Van Clief
            Emma Langdon

*/

#include "MovieTree.h"
#include "BoxOfficeTree.h"
#include "AcademyAwardTree.h"
#include <iostream>
using namespace std;
#include <fstream>  //allows istream/ostream
#include <stdlib.h> //allows atoi
#include<limits>

void printMenu()
{
    cout << "======Main Menu======" << endl;
    cout << "1. Find a movie" << endl;
    cout << "2. Print the inventory" << endl;
    cout << "3. Delete a movie" << endl;
    cout << "4. Count the movies" << endl;
    cout << "5. Top 100 Rated Movie Tree Methods" << endl;
    cout << "6. Top 100 Grossing Movie Tree Methods" << endl;
    cout << "7. All Academy Award Winning Movie Tree Methods" << endl;
    cout << "8. Quit" << endl;
}
void nonNumber()
{
    cout << "Please enter a number between 1 and 8" << endl;
}



MovieTree callMovie;
BoxOfficeTree callBox;
AcademyAwardTree callAward;


int main()
{
    printMenu();
    int userInput;
    cin >> userInput;
    int whichTree;
    int rateTree;
    int boxTree;
    int academyTree;

    while(userInput <= 1000000000000000)
    {
            if(userInput == 1)
            {
                cout << "Which Tree?" << endl;
                cout << "1. Top 100 Rated Movies" << endl;
                cout << "2. Top 100 Grossing Movies" << endl;
                cout << "3. All Academy Award Winning Movies" << endl;
                cout << "4. All 3 Trees" << endl;

                cin >> whichTree;

                if(whichTree == 1)
                {
                    //Top Rated Tree
                    string title;
                    callMovie.findMovie(title);
                    printMenu();
                    cin >> userInput;
                }
                if(whichTree == 2)
                {
                    //Top Grossing Tree
                    string title;
                    callBox.findBoxOfficeMovie(title);
                    printMenu();
                    cin >> userInput;
                }
                if(whichTree == 3)
                {
                    //Academy Award Tree
                    string title;
                    callAward.findAcademyAwardMovie(title);
                    printMenu();
                    cin >> userInput;
                }
                if(whichTree == 4)
                {
                    string title;
                    cout << "Enter title:" << endl;
                    cin.clear();
                    cin.ignore(100,'\n');
                    getline(cin,title);

                    cout << "Top 100 Rated Movies: " << callMovie.searchAllMovies(title) << endl;
                    cout << "Top 100 Grossing Movies: " << callBox.searchAllMovies(title) << endl;
                    cout << "All Academy Award Wining Movies: " << callAward.searchAllMovies(title) << endl;
                    printMenu();
                    cin >> userInput;
                }


            }
            else if(userInput == 2)
            {
                cout << "Which Tree?" << endl;
                cout << "1. Top 100 Rated Movies" << endl;
                cout << "2. Top 100 Grossing Movies" << endl;
                cout << "3. All Academy Award Winning Movies" << endl;

                cin >> whichTree;
                if(whichTree == 1)
                {
                    //Top Rated Tree
                    callMovie.printMovieInventory();
                    printMenu();
                    cin >> userInput;
                }
                if(whichTree == 2)
                {
                    //Top Grossing Tree
                    callBox.printBoxOfficeInventory();
                    printMenu();
                    cin >> userInput;
                }
                if(whichTree == 3)
                {
                    //Academy Award Tree
                    callAward.printAcademyAwardInventory();
                    printMenu();
                    cin >> userInput;

                }

            }
            else if(userInput == 3)
            {

                cout << "Which Tree?" << endl;
                cout << "1. Top 100 Rated Movies" << endl;
                cout << "2. Top 100 Grossing Movies" << endl;
                cout << "3. All Academy Award Winning Movies" << endl;

                cin >> whichTree;
                if(whichTree == 1)
                {
                    //Top Rated Tree
                    //Delete nodes
                    string title;
                    callMovie.deleteMovieNode(title);
                    printMenu();
                    cin >> userInput;
                }
                if(whichTree == 2)
                {
                    //Top Grossing Tree
                    //Delete nodes
                    string title;
                    callBox.deleteBoxOfficeNode(title);
                    printMenu();
                    cin >> userInput;

                }
                if(whichTree == 3)
                {
                    //Academy Award Tree
                    string title;
                    callAward.deleteAcademyAwardNode(title);
                    printMenu();
                    cin >> userInput;
                }

            }
            else if(userInput == 4)
            {
                cout << "Which Tree?" << endl;
                cout << "1. Top 100 Rated Movies" << endl;
                cout << "2. Top 100 Grossing Movies" << endl;
                cout << "3. All Academy Award Winning Movies" << endl;


                cin >> whichTree;
                if(whichTree == 1)
                {
                    //Top Rated Tree
                    int count1 = callMovie.countMovieNodes();
                    cout << "Tree contains: " << count1 << " movies." << endl;
                    printMenu();
                    cin >> userInput;
                }
                if(whichTree == 2)
                {
                    //Top Grossing Tree
                    int count1 = callBox.countBoxOfficeNodes();
                    cout << "Tree contains: " << count1 << " movies." << endl;
                    printMenu();
                    cin >> userInput;

                }
                if(whichTree == 3)
                {
                    //Academy Award Tree
                    int count1 = callAward.countAcademyAwardNodes();
                    cout << "Tree contains: " << count1 << " movies." << endl;
                    printMenu();
                    cin >> userInput;
                }

            }
            else if(userInput == 5)
            {
                //Methods for Top 100 rated movies Tree
                cout << "Which Method?" << endl;
                cout << "1. Search Movies by Era" << endl;
                cout << "2. Search by Rank" << endl;
                cout << "3. Search by Director" << endl;
                cin >> rateTree;


                if(rateTree == 1)
                {
                    callMovie.era();
                    printMenu();
                    cin >> userInput;

                }
                if(rateTree == 2)
                {
                    callMovie.rank();
                    printMenu();
                    cin >> userInput;

                }
                if(rateTree == 3)
                {
                    callMovie.searchByDirector();
                    printMenu();
                    cin >> userInput;
                }


            }
            else if(userInput == 6)
            {
                //Methods for Top 100 Box office tree
                cout << "Which Method?" << endl;
                cout << "1. List All Movies for a Given Year" << endl;
                cout << "2. Get Average of All pProfits" << endl;
                cout << "3. Round Profit Amount " << endl;
                cin >> boxTree;


                if(boxTree == 1)
                {
                    callBox.searchByYear();
                    printMenu();
                    cin >> userInput;

                }
                if(boxTree == 2)
                {
                    callBox.getAverageBox();
                    printMenu();
                    cin >> userInput;

                }
                if(boxTree == 3)
                {
                    callBox.simplify();
                    printMenu();
                    cin >> userInput;
                }
            }
            else if(userInput == 7)
            {
                cout << "Which Method?" << endl;
                cout << "1. Percentage of Awards Won" << endl;
                cout << "2. Add Genre" << endl;
                cout << "3. Search by Year" << endl;
                cout << "4. Search by Year Range and Minimum amount of Awards Won" << endl;
                cin >> academyTree;

                if(academyTree == 1)
                {
                    string title;
                    callAward.percentageWon(title);
                    printMenu();
                    cin >> userInput;

                }
                if(academyTree == 2)
                {
                    string title;
                    callAward.addGenre(title);
                    printMenu();
                    cin >> userInput;

                }
                if(academyTree == 3)
                {
                    callAward.searchByYear();
                    printMenu();
                    cin >> userInput;
                }
                if(academyTree == 4)
                {
                    callAward.winnerSearch();
                    printMenu();
                    cin >> userInput;

                }

            }
            else if(userInput == 8)
            {
                cout << "Goodbye!" << endl;
                return 0;

            }
            /*if(cin.fail())
            {
                cin.clear();
                cin.ignore();
                cout << "Please enter a number between 1 and 8" << endl;
                //printMenu();
                //cin >> userInput;
            }*/
            else
            {
                cout << "Enter a number between 1 and 8" << endl;
                printMenu();
                cin >> userInput;

            }



        }






}


