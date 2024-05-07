#ifndef _LIST_H_
#define _LIST_H_

#include "struct.hpp"

class List{
    private:
        vector<Item*> Li;
        Item* trans;
    public:
        /*
        Item * find(Board * board){
            bool b;
            int x,y;
            Board* bo;
            for(int i=0;i<(int)Li.size();i++){
                bo=Li[i]->board;
                b=false;
                x=0;
                while(x<bo->height && b){
                    y=0;
                    while(y<bo->width && b){
                        if((bo->x == board->x) && (bo->y == board->y)) b=true;
                        y++;
                    }
                    x++;
                }
                if(b) return Li[i];
            }
            return NULL;
        }
        */

        Item * popBest(){
            double f=Li[0]->f;
            int p=0;
            for(int i=1;i<(int)Li.size();i++){
                if(Li[i]->f<f){
                f=Li[i]->f;
                p=i;
                };
            }
            trans=Li.back();
            Li.back()=Li[p];
            Li[p]=trans;
            trans=Li.back();
            Li.pop_back();
            return trans;
        }

        void delList(Item*temp){
            for(int i=0;i<(int)Li.size();i++){
                if(Li[i]==temp){
                    trans=Li.back();
                    Li.back()=Li[i];
                    Li[i]=trans;
                    Li.pop_back();  
                }
            }
        }

        void addLast(Item * node){
            Li.push_back(node);
        }

        Item * popFirst(){
            trans=Li.back();
            Li.back()=Li[0];
            Li[0]=trans;
            return popLast();
        }

        Item * popLast(){
            trans=Li.back();
            Li.pop_back();
            return trans;
        }
        
        int size(){
            return (int)Li.size();
        }

        void print(){
            cout<<"["<<ends;
            for(int i=0;i<(int)Li.size();i++){
                cout<<" "<<Li[i]->depth<<ends;
            }
            cout<<" ]"<<endl;
        }
};
#endif