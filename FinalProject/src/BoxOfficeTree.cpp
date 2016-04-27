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
        cout << "Title:" << node->title << endl;
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
   BoxOfficeNode *nodeDelete = search(title);

    if(nodeDelete != NULL)
    {

        if((nodeDelete->leftChild == NULL) && (nodeDelete->rightChild == NULL))// node to delete has no children
        {
            BoxOfficeNode *node;
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
            BoxOfficeNode *node;
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
            BoxOfficeNode *node;
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
            BoxOfficeNode *minimum = treeMinimum(nodeDelete->rightChild);
            //cout << minimum->title << endl;

                if(nodeDelete->parent == NULL)
                {
                    //cout << "The nodeDelete is the ROOT of the tree" << endl;
                    //cout << "The minimum has NO children" << endl;
                   // cout << nodeDelete->title << " is going to be replaced by: " << minimum->title << endl;
                    minimum->parent->leftChild = NULL;
                    boxRoot = minimum;
                    minimum->leftChild = boxRoot->leftChild;
                    minimum->rightChild = boxRoot->rightChild;
                    boxRoot->rightChild->parent = minimum;
                    boxRoot->leftChild->parent = minimum;


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
    int domesticLength = 1;
    int x = node->domestic;
    while ( x /= 10 )
        domesticLength++;
    //international length
    int internationalLength = 1;
    int y = node->international;
    while ( y /= 10 )
        internationalLength++;
    //worldwide length
    int worldwideLength = 1;
    int z = node->worldwide;
    while ( z /= 10 )
        worldwideLength++;
    //==========
    float simpleDomestic = node->domestic;
    for(int i = 0; i< domesticLength-1; i++)
    {
        simpleDomestic = simpleDomestic/10;
    }
    float simpleInternational = node->international;
    for(int i = 0; i< internationalLength-1; i++)
    {
        simpleInternational = simpleInternational/10;
    }
    float simpleWorldwide = node->worldwide;
    for(int i = 0; i< worldwideLength-1; i++)
    {
        simpleWorldwide = simpleWorldwide/10;
    }
    cout<<"Simplified domestic: $"<<setprecision(2)<<simpleDomestic<<" billion."<<endl;
    cout<<"Simplified international: $"<<setprecision(2)<<simpleInternational<<" billion."<<endl;
    cout<<"Simplified worldwide: $"<<setprecision(2)<<simpleWorldwide<<" billion."<<endl;
    }
    else
    {
        cout << "Movie not Found" << endl;
    }

}




