/*
    Title: Movie Database

    Author: Catherine Diaz
            Marcus Van Clief
            Emma Langdon

*/
#include "AcademyAwardTree.h"
#include "BoxOfficeTree.h"
#include "MovieTree.h"
#include <iostream>
#include <fstream>  //allows istream/ostream
#include <stdlib.h> //allows atoi
#include <sstream>
#include<limits>

using namespace std;

AcademyAwardTree::AcademyAwardTree()
{
    awardRoot = NULL;
    string title;
    int year;
    int wins;
    int nominations;

    string yearSTR;
    string winsSTR;
    string nominationsSTR;

    ifstream infile;
    infile.open("academyAwards.txt");
    while(infile.good())
    {
        getline(infile, title, '.');
        getline(infile, yearSTR, '.');
        getline(infile, winsSTR, '.');
        getline(infile, nominationsSTR);

        if(!infile)
        {
            break;
        }

        year = atoi(yearSTR.c_str());
        wins = atoi(winsSTR.c_str());
        nominations = atoi(nominationsSTR.c_str());

        /*cout <<  title << endl;
        cout <<  year <<endl;
        cout << wins << endl;
        cout << nominations << endl;
        cout << "-------------" << endl;*/

        addAcademyAwardNode(title, year, wins, nominations);

    }
    infile.close();
}

AcademyAwardTree::~AcademyAwardTree()
{
    //dtor
    //cout << "Goodbye!" << endl;
}


//======================PRINT MOVIE INVENTORY=================================
void AcademyAwardTree::printAcademyAwardInventory()
{
    printAcademyAwardInventory(awardRoot);

}

void AcademyAwardTree::printAcademyAwardInventory(AcademyAwardNode *node)
{
    if(node->leftChild != NULL)
    {
        printAcademyAwardInventory(node->leftChild);
    }
    cout<<"Movie: "<< node->title <<endl;
    if(node->rightChild != NULL)
    {
        printAcademyAwardInventory(node->rightChild);
    }

}


//===============================ADD MOVIE NODE ============================================
void AcademyAwardTree::addAcademyAwardNode(string title, int year, int wins, int nominations)
{
        AcademyAwardNode *tmp = awardRoot;
        AcademyAwardNode *parent = NULL;
        AcademyAwardNode *node = new AcademyAwardNode;
        node->leftChild = NULL;
        node->rightChild = NULL;
        node->parent = NULL;
        node->title = title;
        node->year = year;
        node->wins = wins;
        node->nominations = nominations;

    while(tmp != NULL)
        {
            parent = tmp;
            node -> parent = tmp;

                if(node->title.compare(tmp->title) < 0) //compare input value to root key
                {
                    tmp = tmp->leftChild;
                }
                else
                {
                    tmp = tmp->rightChild;
                }
        }

        //=========ADD to tree==============
            if (parent == NULL) //check if tree is empty
            {
                awardRoot = node;
            }
            else if(node->title.compare(node->parent->title) < 0) //if left < parent, add to left
            {
                parent->leftChild = node;
                node->parent = parent;

            }
            else //otherwise, add to right
            {
                parent->rightChild = node;
                node->parent = parent;

            }
}

//========================================FIND MOVE ============================================
AcademyAwardNode* AcademyAwardTree::findAcademyAwardMovie(string title)
{
    AcademyAwardNode *node = search(title);
    if(node != NULL )
    {
        if(node->genre == "")
        {
            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Title:" << node->title << endl;
            cout << "Year: " << node->year << endl;
            cout << "Wins: " << node->wins << endl;
            cout << "Nominations: " << node->nominations << endl;
            return node;
        }
        else
        {
            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Title:" << node->title << endl;
            cout << "Year: " << node->year << endl;
            cout << "Wins: " << node->wins << endl;
            cout << "Nominations: " << node->nominations << endl;
            cout << "Genre: " << node->genre << endl;
            return node;

        }

    }
    else
    {
        cout << "Movie not found." << endl;
        return NULL;
    }





}

AcademyAwardNode* AcademyAwardTree::search(string title)
{
    AcademyAwardNode *node;
    cout << "Enter title:" << endl;
    cin.clear();
    cin.ignore(100,'\n');
    getline(cin,title);

    node = awardRoot;

        while(node != NULL)
        {
            if (title.compare(node->title) < 0)
            {
               node = node->leftChild;

            }
            else if(title.compare(node->title) > 0)
            {
                node = node->rightChild;

            }
            else
            {
                 return node;
            }

        }

        return NULL;

}


//================================COUNT MOVIE NODES=================================
void AcademyAwardTree::countAcademyAwardNodes(AcademyAwardNode *node, int *c)
{
    if(node->leftChild != NULL)
    {
        countAcademyAwardNodes(node->leftChild, c);
    }
    *c = *c +1;
    if(node->rightChild != NULL)
    {
        countAcademyAwardNodes(node->rightChild, c);
    }
}

int AcademyAwardTree::countAcademyAwardNodes()
{
    int *c = new int;
    *c=0;
    countAcademyAwardNodes(awardRoot, c);
    return *c;

}


//==================================DELETE MOVIE NODE=========================================
void AcademyAwardTree::deleteAcademyAwardNode(string title)
{
   AcademyAwardNode *nodeDelete = search(title);

    if(nodeDelete != NULL)
    {

        if((nodeDelete->leftChild == NULL) && (nodeDelete->rightChild == NULL))// node to delete has no children
        {
            AcademyAwardNode *node;
            node = nodeDelete;
            if(node->parent->leftChild == node)
            {
                node->parent->leftChild = NULL;
            }
            else
            {
                node->parent->rightChild = NULL;
            }
            delete node;
            //cout << "node with no children deleted" << endl;

        }
        else if((nodeDelete->leftChild == NULL) && (nodeDelete->rightChild != NULL))//node to delete has only right child
        {
            AcademyAwardNode *node;
            //cout << "in the else if" << endl;
            if(nodeDelete->parent->rightChild == nodeDelete)
            {
                node = nodeDelete->rightChild;
                nodeDelete->parent->rightChild = node;
                node->parent = nodeDelete->parent;
                //cout << "node deleted was right child" << endl;
                delete nodeDelete;
            }
            else
            {
                node = nodeDelete->rightChild;
                nodeDelete->parent->leftChild = node;
                node->parent = nodeDelete->parent;
                //cout << "node deleted was left child" << endl;
                delete nodeDelete;
            }
            //delete nodeDelete;
            //cout << "node with right child deleted "<< endl;

        }
        else if(nodeDelete->leftChild != NULL && nodeDelete->rightChild == NULL)// node to delete only has left child
        {
            AcademyAwardNode *node;
            //cout << "in the else if" << endl;
            if(nodeDelete->parent->rightChild == nodeDelete)
            {
                node = nodeDelete->leftChild;
                nodeDelete->parent->leftChild = node;
                node->parent = nodeDelete->parent;
                delete nodeDelete;

            }
            else
            {
                node = nodeDelete->leftChild;
                nodeDelete->parent->rightChild = node;
                node->parent = nodeDelete->parent;
                delete nodeDelete;
            }

            //delete nodeDelete;
            //cout << "node with left child deleted "<< endl;

        }
        else//(nodeDelete->leftChild != NULL && nodeDelete->rightChild != NULL)// node to delete has 2 children
        {
            //cout << "nodeDelete has 2 children" << endl;
           // MovieNode *node;
            //node = nodeDelete;
            AcademyAwardNode *minimum = treeMinimum(nodeDelete->rightChild);
            //cout << minimum->title << endl;

                if(nodeDelete->parent == NULL)
                {
                    //cout << "The nodeDelete is the ROOT of the tree" << endl;
                    //cout << "The minimum has NO children" << endl;
                   // cout << nodeDelete->title << " is going to be replaced by: " << minimum->title << endl;
                    minimum->parent->leftChild = NULL;
                    awardRoot = minimum;
                    minimum->leftChild = awardRoot->leftChild;
                    minimum->rightChild = awardRoot->rightChild;
                    awardRoot->rightChild->parent = minimum;
                    awardRoot->leftChild->parent = minimum;


                }
                else if(nodeDelete->rightChild == minimum)
                {
                    //cout << "nodeDelete is being replaced by right child" << endl;
                    if(nodeDelete->parent->rightChild == nodeDelete)
                    {

                        if(minimum->rightChild == NULL)// if min has no right child
                        {
                            //cout << "The nodeDelete is a right child" << endl;
                            //cout << "The minimum has no right child" << endl;
                            //cout << nodeDelete->title << "is going to be replaced by: " << minimum->title << endl;
                            nodeDelete->parent->rightChild = minimum;
                            nodeDelete->leftChild->parent = minimum;
                            minimum->parent = nodeDelete->parent;
                            minimum->leftChild = nodeDelete->leftChild;
                            delete nodeDelete;

                        }
                        else
                        {
                            // the minimum has a right child
                            //cout << "The nodeDelete is a right child" << endl;
                            //cout << "The minimum has right child" << endl;
                            //cout << nodeDelete->title << "is going to be replaced by: " << minimum->title << endl;
                            nodeDelete->parent->rightChild = minimum;
                            nodeDelete->leftChild->parent = minimum;
                            minimum->parent = nodeDelete->parent;
                            minimum->leftChild = nodeDelete->leftChild;
                            delete nodeDelete;

                        }
                    }
                    else// node delete is a left child
                    {
                        if(minimum->rightChild == NULL)// has no right child
                        {
                            //cout << "The nodeDelete is a left child" << endl;
                            //cout << "The minimum has no right child" << endl;
                            //cout << nodeDelete->title << " is going to be replaced by: " << minimum->title << endl;
                            nodeDelete->parent->leftChild = minimum;
                            nodeDelete->leftChild->parent = minimum;
                            minimum->parent = nodeDelete->parent;
                            minimum->leftChild = nodeDelete->leftChild;
                            delete nodeDelete;

                        }
                        else
                        {
                            // the minimum has a right child
                            //cout << "The nodeDelete is a left child" << endl;
                            //cout << "The minimum has right child" << endl;
                            //cout << nodeDelete->title << " is going to be replaced by: " << minimum->title << endl;
                            nodeDelete->parent->leftChild = minimum;
                            nodeDelete->leftChild->parent = minimum;
                            minimum->parent = nodeDelete->parent;
                            minimum->leftChild = nodeDelete->leftChild;
                            delete nodeDelete;

                        }

                    }

                }

                else// replace with minimum that is not the right child
                {
                    //cout << "nodeDelete is being replaced by lowest value in right subtree" << endl;

                    if(nodeDelete->parent->rightChild == nodeDelete)// if the node to delete is a right child
                    {

                        if(minimum->rightChild == NULL)// if min has no right child
                        {
                            //cout << "The nodeDelete is a right child" << endl;
                            //cout << "The minimum has NO children" << endl;
                            //cout << nodeDelete->title << " is going to be replaced by: " << minimum->title << endl;
                            minimum->parent->leftChild = NULL;
                            minimum->parent = nodeDelete->parent;
                            //minimum->rightChild->parent = minimum->parent;
                            nodeDelete->parent->rightChild = minimum; // HERERE
                            minimum->leftChild = nodeDelete->leftChild;
                            minimum->rightChild = nodeDelete->rightChild;
                            nodeDelete->rightChild->parent = minimum;
                            nodeDelete->leftChild->parent = minimum;
                            delete nodeDelete;

                        }
                        else
                        {
                            // the minimum has a right child
                            //cout << "The nodeDelete is a right child" << endl;
                            //cout << "The minimum has right child(ren)" << endl;
                            //cout << nodeDelete->title << " is going to be replaced by: " << minimum->title << endl;
                            minimum->parent->leftChild = minimum->rightChild;
                            minimum->parent = nodeDelete->parent;
                            minimum->rightChild->parent = minimum->parent;
                            nodeDelete->parent->rightChild = minimum; // HERERE
                            minimum->leftChild = nodeDelete->leftChild;
                            minimum->rightChild = nodeDelete->rightChild;
                            nodeDelete->rightChild->parent = minimum;
                            nodeDelete->leftChild->parent = minimum;
                           delete nodeDelete;

                        }
                    }
                    else// node delete is a left child
                    {
                        if(minimum->rightChild == NULL)// has no right child
                        {
                            //cout << "The nodeDelete is a left child" << endl;
                            //cout << "The minimum has NO children" << endl;
                            //cout << nodeDelete->title << " is going to be replaced by: " << minimum->title << endl;
                            minimum->parent->leftChild = NULL;
                            minimum->parent = nodeDelete->parent;
                            nodeDelete->parent->leftChild = minimum; // HERERE
                            minimum->leftChild = nodeDelete->leftChild;
                            minimum->rightChild = nodeDelete->rightChild;
                            nodeDelete->rightChild->parent = minimum;
                            nodeDelete->leftChild->parent = minimum;
                            delete nodeDelete;

                        }
                        else
                        {
                            // the minimum has a right child
                            //cout << "The nodeDelete is a left child" << endl;
                            //cout << "The minimum has right child(ren)" << endl;
                            //cout << nodeDelete->title << " is going to be replaced by: " << minimum->title << endl;
                            minimum->parent->leftChild = minimum->rightChild;
                            minimum->parent = nodeDelete->parent;
                            minimum->rightChild->parent = minimum->parent;
                            nodeDelete->parent->leftChild = minimum; // HERERE
                            minimum->leftChild = nodeDelete->leftChild;
                            minimum->rightChild = nodeDelete->rightChild;
                            nodeDelete->rightChild->parent = minimum;
                            nodeDelete->leftChild->parent = minimum;
                            delete nodeDelete;

                        }

                    }
                }



        }

    }
    else
    {
        cout << "Movie not found." << endl;
    }

}


AcademyAwardNode* AcademyAwardTree::treeMinimum(AcademyAwardNode *node)
{
    while(node->leftChild != NULL)
    {
        node = node->leftChild;
    }
    return node;

}

void AcademyAwardTree::searchByYear(AcademyAwardNode *node, int year)
{
    if(node != NULL)
    {
        if(node->year == year)
        {
            cout << node->title << " " << node->year << endl;
            found = true;
        }
        searchByYear(node->leftChild, year);
        searchByYear(node->rightChild, year);
    }

}

void AcademyAwardTree::searchByYear()
{
    int year;
    cout << "Enter what year of the Academy Awards you want to see between 1929-2015: " << endl;
    cin >> year;
    cout << endl;
    cout << "Displaying all Academy Award nominated films in " << year << "..." << endl;
    searchByYear(awardRoot,year);
    if(found == false)
    {
        cout << "This year is not in the list" << endl;

    }
    else
    {
        found = false;
    }

}

AcademyAwardNode* AcademyAwardTree::winnerSearch(AcademyAwardNode *node, int numAwards, int year1, int year2)
{
    if(node != NULL)
    {
        if(node->year >= year1 && node->year <= year2 && node->wins >= numAwards)
        {
            cout << node->title << " " << node->year << " " << node->wins << endl;
            return node;
        }
        winnerSearch(node->leftChild, numAwards, year1, year2);
        winnerSearch(node->rightChild, numAwards, year1, year2);
    }
    return NULL;


}
void AcademyAwardTree::winnerSearch()
{
    int numAwards;
    int year1;
    int year2;
    cout << "Enter minimum amount of awards won: " << endl;
    cin >> numAwards;
    cout << "Enter range of years you want to see: " << endl;
    cout << "Year 1: ";
    cin >> year1;
    cout << "Year 2: ";
    cin >> year2;
    AcademyAwardNode *node = winnerSearch(awardRoot,numAwards, year1, year2);

    if(node == NULL)
    {
        cout << "No movies found for your search" << endl;
    }

}

AcademyAwardNode* AcademyAwardTree::searchAll(string title)
{
    AcademyAwardNode *node;
    node = awardRoot;

        while(node != NULL)
        {
            if (title.compare(node->title) < 0)
            {
               node = node->leftChild;

            }
            else if(title.compare(node->title) > 0)
            {
                node = node->rightChild;

            }
            else
            {
                 return node;
            }

        }

        return NULL;
}

string AcademyAwardTree::searchAllMovies(string title)
{
    AcademyAwardNode* node = searchAll(title);

    if(node != NULL)
    {
        return "Movie Found";
    }
    else
    {
        return "Movie NOT Found";
    }
}

void AcademyAwardTree::percentageWon(string title)
{
    AcademyAwardNode *node = search(title);
    if(node!= NULL)
    {

    double noms = node->nominations;
    double wins = node->wins;
    double percentage = wins/noms;
    percentage = percentage * 100;
    int percent = percentage;

    cout << "Wins: " << node->wins << endl;
    cout << "Nominations: " << node->nominations << endl;

    cout << node->title << " won " << percent << "% of the awards it was nominated for." << endl;
    }
    else
    {
        cout << "Movie Not Found" << endl;
    }
}

void AcademyAwardTree::addGenre(string title)
{
    AcademyAwardNode *node = findAcademyAwardMovie(title);
    string genre;

    if(node != NULL)
    {
        if(node->genre == "")
        {
            cout << "Enter Genre: ";
            cin >> genre;
            node->genre = genre;

            cout << endl;
            cout << "UPDATED NODE:" << endl;
            cout << endl;

            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Title:" << node->title << endl;
            cout << "Year: " << node->year << endl;
            cout << "Wins: " << node->wins << endl;
            cout << "Nominations: " << node->nominations << endl;
            cout << "Genre: " << node->genre << endl;
        }
        else
        {
            cout << "This movie already has a genre assigned to it." << endl;
        }
    }
    else
    {
        cout << "Try again" << endl;
    }


}










