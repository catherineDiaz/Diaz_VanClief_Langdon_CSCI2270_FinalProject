/*
    Title: Movie Database

    Author: Catherine Diaz
            Marcus Van Clief
            Emma Langdon

*/
#ifndef BOXOFFICETREE_H
#define BOXOFFICETREE_H
#include <iostream>

struct BoxOfficeNode{
    int ranking;
    int year;
    std::string title;
    int domestic;
    int international;
    unsigned int worldwide;
    BoxOfficeNode *parent;
    BoxOfficeNode *leftChild;
    BoxOfficeNode *rightChild;

    BoxOfficeNode(){};

    BoxOfficeNode(int in_ranking, int in_year, std::string in_title,int in_domestic, int in_international, unsigned int in_worldwide)
    {
        ranking = in_ranking;
        year = in_year;
        title = in_title;
        domestic = in_domestic;
        international = in_international;
        worldwide = in_worldwide;
        parent = NULL;
        leftChild = NULL;
        rightChild = NULL;
    }

};


class BoxOfficeTree
{

    public:
        BoxOfficeTree();
        ~BoxOfficeTree();
        void printBoxOfficeInventory();
        int countBoxOfficeNodes();
        void deleteBoxOfficeNode(std::string title);
        void addBoxOfficeNode(int ranking, int year, std::string title, int domestic, int international,  unsigned int worldwide);
        void findBoxOfficeMovie(std::string title);
        std::string searchAllMovies(std::string title);
        void searchByYear();
        void getAverageBox();
        void simplify();

    protected:

    private:
        void printBoxOfficeInventory(BoxOfficeNode * node);
        void countBoxOfficeNodes(BoxOfficeNode *node, int *c);
        BoxOfficeNode* search(std::string title);
        BoxOfficeNode* treeMinimum(BoxOfficeNode *node);
        BoxOfficeNode *boxRoot;
        BoxOfficeNode* searchAll(std::string title);
        void searchByYear(BoxOfficeNode *node, int year);
        void getAverageBox(BoxOfficeNode *node, unsigned int *domestic, unsigned int *international, unsigned int *worldwide);
        bool found = false;
};





#endif // BOXOFFICETREE_H

