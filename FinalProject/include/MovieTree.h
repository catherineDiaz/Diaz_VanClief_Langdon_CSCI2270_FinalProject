/*
    Title: Movie Database

    Author: Catherine Diaz
            Marcus Van Clief
            Emma Langdon

*/
#ifndef MOVIETREE_H
#define MOVIETREE_H
#include <iostream>


struct MovieNode{
    int ranking;
    std::string title;
    std::string director;
    int year;
    std::string studio;
    MovieNode *parent;
    MovieNode *leftChild;
    MovieNode *rightChild;

    MovieNode(){};

    MovieNode(int in_ranking, std::string in_title, std::string in_director, int in_year, std::string in_studio)
    {
        ranking = in_ranking;
        title = in_title;
        director = in_director;
        year = in_year;
        studio = in_studio;
        parent = NULL;
        leftChild = NULL;
        rightChild = NULL;
    }

};

class MovieTree
{

    public:
        MovieTree();
        ~MovieTree();
        void printMovieInventory();
        int countMovieNodes();
        void deleteMovieNode(std::string title);
        void addMovieNode(int ranking, std::string title,std::string director, int year, std::string studio);
        void findMovie(std::string title);
        void rentMovie(std::string title);
        std::string searchAllMovies(std::string title);
        void searchByDirector();

        void director();
        void era();
        void rank();
        void checkNode(MovieNode* node, std::string director);
        void directorCompare(MovieNode *node, std::string director);
        void findDirector(std::string director);
        void findEra(int lower, int upper);
        void checkEra(MovieNode *node, int lower, int upper);
        void findRank(int lower, int upper);
        void checkRank(MovieNode *node, int lower, int upper);

    protected:

    private:
        void printMovieInventory(MovieNode * node);
        void countMovieNodes(MovieNode *node, int *c);
        MovieNode* search(std::string title);
        MovieNode* treeMinimum(MovieNode *node);
        MovieNode *root;
        MovieNode* searchAll(std::string title);
        void searchStudio(MovieNode * node, std::string studio);
        MovieNode *order[100];
        void searchByDirector(MovieNode *node, std::string director);
        bool found = false;

};

#endif // MOVIETREE_H


