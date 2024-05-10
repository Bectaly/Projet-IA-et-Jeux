#ifndef _LIST_H_
#define _LIST_H_

#include "struct.hpp"

class List{
    private:
        vector<Item*> Li;
        Item* trans;
        bool isEqual(Board* b1, Board* b2);

    public:
        Item * find(Board * board);
        Item * popBest();
        void delList(Item*temp);
        void addLast(Item * node);
        Item * popFirst();
        Item * popLast();
        int size();
        void clean();
};
#endif