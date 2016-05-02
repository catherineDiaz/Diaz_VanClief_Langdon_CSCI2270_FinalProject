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



MovieTree callMovie;
BoxOfficeTree callBox;
AcademyAwardTree callAward;


int main()
{
    int userInput;
    int whichTree;
    int rateTree;
    int boxTree;
    int academyTree;
    bool quit = false;

    while(!quit)
    {
        printMenu();
        cin >> userInput;
        //cin.clear();
        //cin.ignore(100000, '\n');
        string title;

            switch (userInput)
            {
                case 1:
                        cout << "Which Tree?" << endl;
                        cout << "1. Top 100 Rated Movies" << endl;
                        cout << "2. Top 100 Grossing Movies" << endl;
                        cout << "3. All Academy Award Winning Movies" << endl;
                        cout << "4. All 3 Trees" << endl;

                        cin >> whichTree;

                        switch(whichTree){
                        case 1:
                            //Top Rated Tree
                            callMovie.findMovie(title);
                            break;

                        case 2:
                            //Top Grossing Tree
                            callBox.findBoxOfficeMovie(title);
                            break;

                        case 3:
                            //Academy Award Tree
                            callAward.findAcademyAwardMovie(title);
                            break;

                        case 4:
                            cout << "Enter title:" << endl;
                            cin.clear();
                            cin.ignore(100,'\n');
                            getline(cin,title);

                            cout << "Top 100 Rated Movies: " << callMovie.searchAllMovies(title) << endl;
                            cout << "Top 100 Grossing Movies: " << callBox.searchAllMovies(title) << endl;
                            cout << "All Academy Award Wining Movies: " << callAward.searchAllMovies(title) << endl;
                            break;
                        default:
                            cout << "invalid input" << endl;
                            break;

                            }

                        break;


            case 2:
                    cout << "Which Tree?" << endl;
                    cout << "1. Top 100 Rated Movies" << endl;
                    cout << "2. Top 100 Grossing Movies" << endl;
                    cout << "3. All Academy Award Winning Movies" << endl;

                    cin >> whichTree;

                    switch (whichTree)
                    {
                        case 1:
                            //Top Rated Tree
                            callMovie.printMovieInventory();
                            break;

                        case 2:
                            //Top Grossing Tree
                            callBox.printBoxOfficeInventory();
                            break;

                        case 3:
                            //Academy Award Tree
                            callAward.printAcademyAwardInventory();
                            break;
                        default:
                            cout << "invalid input" << endl;
                            break;
                    }
                break;


            case 3:
                    cout << "Which Tree?" << endl;
                    cout << "1. Top 100 Rated Movies" << endl;
                    cout << "2. Top 100 Grossing Movies" << endl;
                    cout << "3. All Academy Award Winning Movies" << endl;

                    cin >> whichTree;

                    switch(whichTree)
                    {

                        case 1:
                            //Top Rated Tree
                            //Delete nodes
                            //string title;
                            callMovie.deleteMovieNode(title);
                            break;

                        case 2:
                            //Top Grossing Tree
                            //Delete nodes
                            //string title;
                            callBox.deleteBoxOfficeNode(title);
                            break;

                        case 3:
                            //Academy Award Tree
                            //string title;
                            callAward.deleteAcademyAwardNode(title);
                            break;
                        default:
                            cout << "invalid input" << endl;
                            break;
                    }
                break;

            case 4:
                    cout << "Which Tree?" << endl;
                    cout << "1. Top 100 Rated Movies" << endl;
                    cout << "2. Top 100 Grossing Movies" << endl;
                    cout << "3. All Academy Award Winning Movies" << endl;

                    cin >> whichTree;
                    switch(whichTree)
                    {
                        case 1:
                            //Top Rated Tree
                            int count1;
                            count1 = callMovie.countMovieNodes();
                            cout << "Tree contains: " << count1 << " movies." << endl;
                            break;

                        case 2:
                            //Top Grossing Tree
                            int count2;
                            count2 = callBox.countBoxOfficeNodes();
                            cout << "Tree contains: " << count2 << " movies." << endl;
                            break;

                        case 3:
                            //Academy Award Tree
                            int count3;
                            count3 = callAward.countAcademyAwardNodes();
                            cout << "Tree contains: " << count3 << " movies." << endl;
                            break;
                        default:
                            cout << "invalid input" << endl;
                            break;
                    }
                break;


            case 5:
                    //Methods for Top 100 rated movies Tree
                    cout << "Which Method?" << endl;
                    cout << "1. Search Movies by Era" << endl;
                    cout << "2. Search by Rank" << endl;
                    cout << "3. Search by Director" << endl;
                    cin >> rateTree;

                    switch(rateTree)
                    {
                        case 1:
                            callMovie.era();
                            break;

                        case 2:
                            callMovie.rank();
                            break;

                        case 3:
                            callMovie.searchByDirector();
                            break;
                        default:
                            cout << "invalid input" << endl;
                            break;
                    }
                break;



            case 6:
                    //Methods for Top 100 Box office tree
                    cout << "Which Method?" << endl;
                    cout << "1. List All Movies for a Given Year" << endl;
                    cout << "2. Get Average of All Profits" << endl;
                    cout << "3. Round Profit Amount " << endl;
                    cin >> boxTree;

                    switch(boxTree)
                    {
                        case 1:
                            callBox.searchByYear();
                            break;

                        case 2:
                            callBox.getAverageBox();
                            break;

                        case 3:
                            callBox.simplify();
                            break;
                        default:
                            cout << "invalid input" << endl;
                            break;
                    }
                break;

            case 7:
                    cout << "Which Method?" << endl;
                    cout << "1. Percentage of Awards Won" << endl;
                    cout << "2. Add Genre" << endl;
                    cout << "3. Search by Year" << endl;
                    cout << "4. Search by Year Range and Minimum amount of Awards Won" << endl;
                    cin >> academyTree;
                    switch(academyTree)
                    {
                        case 1:
                            //string title;
                            callAward.percentageWon(title);
                            break;

                        case 2:
                            //string title;
                            callAward.addGenre(title);
                            break;

                        case 3:
                            callAward.searchByYear();
                            break;

                        case 4:
                            callAward.winnerSearch();
                            break;
                        default:
                            cout << "invalid input" << endl;
                            break;
                    }
                break;


            case 8:
                cout << "Goodbye!" << endl;
                quit = true;
                break;

            default:
                cout << "Please enter a number between 1 and 8" << endl;
                break;
            }



        }
        return 0;

}


