#include "List.hpp"

bool List::isEqual(Board* b1, Board* b2){
    for(int x = 0; x < b1->width; x++){
        for(int y = 0; y < b1->height; y++){
            if(b1->getTile(x, y)->player != b2->getTile(x, y)->player || b1->getTile(x, y)->walls != b2->getTile(x, y)->walls) {
                return false;
            }
        }
    }
    return true;
}

Item * List::find(Board * board){
    for(int i=size()-1;i>=0;i--){
        if(isEqual(Li[i]->board,board)) return Li[i];
    }
    return NULL;
}

Item * List::popBest(){
    double f=Li[0]->f;
    int p=0;
    for(int i=1;i<(int)Li.size();i++){
        if(Li[i]->f<f){
        f=Li[i]->f;
        p=i;
        };
    }
    swap(Li[p], Li.back());
    trans = Li.back();
    Li.pop_back();
    return trans;
}

void List::delList(Item*temp){
    for(int i=0;i<(int)Li.size();i++){
        if(Li[i]==temp){
            trans=Li.back();
            Li.back()=Li[i];
            Li[i]=trans;
            Li.pop_back();  
        }
    }
}

void List::addLast(Item * node){
    Li.push_back(node);
}

Item * List::popFirst(){
    std::swap(Li[0], Li.back());
    return popLast();
}

Item * List::popLast(){
    trans=Li.back();
    Li.pop_back();
    return trans;
}

int List::size(){
    return (int)Li.size();
}

void List::clean(){
    for(int i=0;i<size();i++){
        Li[i]->board->Delete();
        delete Li[i];
    }
}
