/*
    Title: Movie Database

    Author: Catherine Diaz
            Marcus Van Clief
            Emma Langdon

*/
#include "BoxOfficeTree.h"
#include "MovieTree.h"
#include "AcademyAwardTree.h"
#include <iostream>
#include <fstream>  //allows istream/ostream
#include <stdlib.h> //allows atoi
#include <sstream>
#include <iomanip>
#include<limits>


using namespace std;

BoxOfficeTree::BoxOfficeTree()
{
    boxRoot = NULL;
    int ranking;
    int year;
    string title;
    int domestic;
    int international;
    unsigned int worldwide;

    string rankingSTR;
    string yearSTR;
    string domesticSTR;
    string internationalSTR;
    string worldwideSTR;

    ifstream infile;
    infile.open("top100BoxOffice.txt");
    while(infile.good())
    {
        getline(infile, rankingSTR, '.');
        getline(infile, yearSTR, '.');
        getline(infile, title, '.');
        getline(infile, domesticSTR, '.');
        getline(infile, internationalSTR, '.');
        getline(infile, worldwideSTR);

        if(!infile)
        {
            break;
        }

        ranking = atoi(rankingSTR.c_str());
        year = atoi(yearSTR.c_str());
        domestic = atoi(domesticSTR.c_str());
        international = atoi(internationalSTR.c_str());
        worldwide = atoi(worldwideSTR.c_str());

        /*cout << ranking << endl;
        cout <<  year <<endl;
        cout <<  title << endl;
        cout << "$" << domestic << endl;
        cout << "$" << international << endl;
        cout << "$" << worldwide << endl;
        cout << "-------------" << endl;*/

        addBoxOfficeNode(ranking, year, title, domestic, international, worldwide);

    }

}

BoxOfficeTree::~BoxOfficeTree()
{
    //cout << "Goodbye!" << endl;


}


//======================PRINT MOVIE INVENTORY=================================
void BoxOfficeTree::printBoxOfficeInventory()
{
    printBoxOfficeInventory(boxRoot);

}

void BoxOfficeTree::printBoxOfficeInventory(BoxOfficeNode *node)
{
    if(node->leftChild != NULL)
    {
        printBoxOfficeInventory(node->leftChild);
    }
    cout<<"Movie: "<< node->title <<endl;
    if(node->rightChild != NULL)
    {
        printBoxOfficeInventory(node->rightChild);
    }

}


//===============================ADD MOVIE NODE ============================================
void BoxOfficeTree::addBoxOfficeNode(int ranking, int year, string title, int domestic, int international,  unsigned int worldwide)
{
        BoxOfficeNode *tmp = boxRoot;
        BoxOfficeNode *parent = NULL;
        BoxOfficeNode *node = new BoxOfficeNode;
        node->leftChild = NULL;
        node->rightChild = NULL;
        node->parent = NULL;
        node->ranking = ranking;
        node->year = year;
        node->title = title;
        node->domestic = domestic;
        node->international = international;
        node->worldwide = worldwide;




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
                boxRoot = node;
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
void BoxOfficeTree::findBoxOfficeMovie(string title)
{
    BoxOfficeNode *node = search(title);
    if(node != NULL )
    {
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking: " << node->ranking << endl;
        cout << "Year: " << node->year << endl;
        cout << "Title: " << node->title << endl;
        cout << "Domestic: $" << node->domestic << endl;
        cout << "International: $" << node->international << endl;
        cout << "Worldwide: $" << node->worldwide << endl;

    }
    else
    {
        cout << "Movie not found." << endl;
    }





}

BoxOfficeNode* BoxOfficeTree::search(string title)
{
    BoxOfficeNode *node;
    cout << "Enter title:" << endl;
    cin.clear();
    cin.ignore(100,'\n');
    getline(cin,title);

    node = boxRoot;

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
void BoxOfficeTree::countBoxOfficeNodes(BoxOfficeNode *node, int *c)
{
    if(node->leftChild != NULL)
    {
        countBoxOfficeNodes(node->leftChild, c);
    }
    *c = *c +1;
    if(node->rightChild != NULL)
    {
        countBoxOfficeNodes(node->rightChild, c);
    }
}

int BoxOfficeTree::countBoxOfficeNodes()
{
    int *c = new int;
    *c=0;
    countBoxOfficeNodes(boxRoot, c);
    return *c;

}


//==================================DELETE MOVIE NODE=========================================
void BoxOfficeTree::deleteBoxOfficeNode(string title)
{
    BoxOfficeNode * foundMovie = search(title);

        // If the movie exists
        if (foundMovie != NULL)
        {
            // If it has no children
            if (foundMovie->leftChild == NULL && foundMovie->rightChild == NULL)
            {
                // If this node is the left child, set the parents left child to NULL
                if (foundMovie->parent->leftChild == foundMovie)
                    foundMovie->parent->leftChild = NULL;
                // Else, this node is the right child, set that to NULL
                else
                    foundMovie->parent->rightChild = NULL;
                // Delete the node
                delete foundMovie;

            }
            // If it only has a left child
            else if (foundMovie->rightChild == NULL)
            {
                if (foundMovie->parent->leftChild == foundMovie)
                    foundMovie->parent->leftChild = foundMovie->leftChild;
                else
                     foundMovie->parent->rightChild = foundMovie->leftChild;

                delete foundMovie;

            }
            // If it only has a right child
            else if (foundMovie->leftChild == NULL)
            {
                if (foundMovie->parent->leftChild == foundMovie)
                    foundMovie->parent->leftChild = foundMovie->rightChild;
                else
                     foundMovie->parent->rightChild = foundMovie->rightChild;

                delete foundMovie;
            }

            // Node has two children, we need the smallest node from the right child
            else
            {
                // Start on the right sub-tree
                BoxOfficeNode * replacementNode = foundMovie->rightChild;

                // search for the smallest left child
                while (replacementNode->leftChild != NULL)
                {
                    replacementNode = replacementNode->leftChild;
                }

                // Swap in all the info from the replacement to this node we are "deleting"
                foundMovie->ranking = replacementNode->ranking;
                foundMovie->year = replacementNode->year;
                foundMovie->title = replacementNode->title;
                foundMovie->domestic = replacementNode->domestic;
                foundMovie->international = replacementNode->international;
                foundMovie->worldwide = replacementNode->worldwide;


                // If the replacement node has a right child, update the parent
                if (replacementNode->rightChild != NULL)
                    replacementNode->rightChild->parent = replacementNode->parent;

                // If the replacement node is a left child
                if (replacementNode->parent->leftChild == replacementNode)
                    replacementNode->parent->leftChild = replacementNode->rightChild;
                // If it is a right child
                else
                    replacementNode->parent->rightChild = replacementNode->rightChild;

                // Delete the node
                delete replacementNode;
            }
        }
        // If it doesn't exist
        else
        {
            cout << "Movie not found." << endl;
        }


}


BoxOfficeNode* BoxOfficeTree::treeMinimum(BoxOfficeNode *node)
{
    while(node->leftChild != NULL)
    {
        node = node->leftChild;
    }
    return node;

}

BoxOfficeNode* BoxOfficeTree::searchAll(string title)
{
    BoxOfficeNode *node;
    node = boxRoot;

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

string BoxOfficeTree::searchAllMovies(string title)
{
    BoxOfficeNode* node = searchAll(title);

    if(node != NULL)
    {
        return "Movie Found";
    }
    else
    {
        return "Movie NOT Found";
    }
}

void BoxOfficeTree::searchByYear(BoxOfficeNode *node, int year)
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

void BoxOfficeTree::searchByYear()
{
    int year;
    cout << "Enter what year: " << endl;
    cin >> year;
    cout << endl;
    cout << "Displaying all top Grossing movies made in " << year << "..." << endl;
    searchByYear(boxRoot,year);
    if(found == false)
    {
        cout << "The year " << year << " is not in this list please try again" << endl;
    }
    else
    {
        found = false;
    }

}
void BoxOfficeTree::getAverageBox(BoxOfficeNode *node, unsigned int *domestic, unsigned int *international, unsigned int *worldwide)
{
    if(node->leftChild != NULL)
    {
        getAverageBox(node->leftChild, domestic, international, worldwide);
    }
    *domestic = node->domestic + *domestic;
    *international = node->international + *international;
    *worldwide = node->worldwide + *worldwide;
    if(node->rightChild != NULL)
    {
        getAverageBox(node->rightChild, domestic, international, worldwide);
    }
}

void BoxOfficeTree::getAverageBox()
{

    unsigned int *domestic = new unsigned int;
    unsigned int *international = new unsigned int;
    unsigned int *worldwide = new unsigned int;
    *domestic=0;
    *international = 0;
    *worldwide = 0;
    getAverageBox(boxRoot, domestic, international, worldwide);
    int total = countBoxOfficeNodes();
    unsigned int domesticAVG = *domestic/total;
    unsigned int internationalAVG = *international/total;
    unsigned int worldwideAVG = *worldwide/total;
    cout<<"Average domestic profit: " << domesticAVG<<endl;
    cout<<"Average international profit: " << internationalAVG<<endl;
    cout<<"Average worldwide profit: " << worldwideAVG<<endl;

}

void BoxOfficeTree::simplify()
{
    string title;
    BoxOfficeNode *node = search(title);
    if(node != NULL)
    {

    //domestic length
    /*int domesticLength = 1;
    int x = node->domestic;
    while ( x /= 10 )
        domesticLength++;*/
    //international length
    int worldwideLength = 1;
    int y = node->worldwide;
    while ( y /= 10 )
        worldwideLength++;
    //worldwide length

   /*
    //==========
    float simpleDomestic = node->domestic;
    for(int i = 0; i< domesticLength-1; i++)
    {
        simpleDomestic = simpleDomestic/10;
    }*/
    float simpleWorldwide = node->worldwide;
    for(int i = 0; i< worldwideLength-1; i++)
    {
        simpleWorldwide = simpleWorldwide/10;
    }


    int simpleDomestic;
    int simpleInternational;
    unsigned int simpleWorld;
    //int simpleWorldwide;

        if(node->domestic > 1000000 && node->domestic < 1000000000)
        {
            simpleDomestic = node->domestic;
            simpleDomestic = simpleDomestic/1000000;
            cout<<"Simplified domestic: $"<< simpleDomestic << " million" << endl;

        }
        else
        {
            simpleDomestic = node->domestic;
            simpleDomestic = simpleDomestic/1000000000;
            cout<<"Simplified domestic: $"<< simpleDomestic << " billion" << endl;
        }
        if(node->international > 1000000 && node->international < 1000000000)
        {
            simpleInternational = node->international;
            simpleInternational = simpleInternational/1000000;
            cout<<"Simplified international: $"<< simpleInternational << " million" << endl;

        }
        else
        {
            simpleInternational = node->international;
            simpleInternational = simpleInternational/1000000000;
            cout<<"Simplified international: $"<< simpleInternational << " billion" << endl;
        }
        if(node->worldwide > 1000000 && node->worldwide < 1000000000)
        {
            simpleWorld = node->worldwide;
            simpleWorld = simpleWorld/1000000;
            cout<<"Simplified worldwide: $" <<simpleWorld << " million" << endl;

        }
        else
        {
            //simpleWorld = node->worldwide;
            //simpleWorld = simpleWorld/1000000000;
            cout<<"Simplified worldwide: $"<<setprecision(2) << simpleWorldwide << " billion" << endl;
        }
    }
    else
    {
        cout << "Movie not Found" << endl;
    }

}




