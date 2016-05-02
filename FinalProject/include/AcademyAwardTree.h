/*
    Title: Movie Database

    Author: Catherine Diaz
            Marcus Van Clief
            Emma Langdon

*/
#ifndef ACADEMYAWARDTREE_H
#define ACADEMYAWARDTREE_H
#include <iostream>


struct AcademyAwardNode{
    std::string title;
    int year;
    int wins;
    int nominations;
    std::string genre;
    AcademyAwardNode *parent;
    AcademyAwardNode *leftChild;
    AcademyAwardNode *rightChild;

    AcademyAwardNode(){};

    AcademyAwardNode(std::string in_title, int in_year, int in_wins, int in_nominations)
    {
        title = in_title;
        year = in_year;
        wins = in_wins;
        nominations = in_nominations;
        parent = NULL;
        leftChild = NULL;
        rightChild = NULL;
    }

};


class AcademyAwardTree
{

    public:
        AcademyAwardTree();
        ~AcademyAwardTree();
        void printAcademyAwardInventory();
        int countAcademyAwardNodes();
        void deleteAcademyAwardNode(std::string title);
        void addAcademyAwardNode(std::string title, int year, int wins, int nominations);
        AcademyAwardNode* findAcademyAwardMovie(std::string title);
        void searchByYear();
        void winnerSearch();
        std::string searchAllMovies(std::string title);
        void percentageWon(std::string title);
        void addGenre(std::string title);

    protected:

    private:
        void printAcademyAwardInventory(AcademyAwardNode * node);
        void countAcademyAwardNodes(AcademyAwardNode *node, int *c);
        AcademyAwardNode* search(std::string title);
        AcademyAwardNode* treeMinimum(AcademyAwardNode *node);
        AcademyAwardNode *awardRoot;
        void searchByYear(AcademyAwardNode *node, int year);
        void winnerSearch(AcademyAwardNode *node, int numAwards, int year1, int year2);
        AcademyAwardNode* searchAll(std::string title);
        bool found = false;
};



#endif // ACADEMYAWARDTREE_H

