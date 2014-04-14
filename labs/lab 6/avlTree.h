//
//  avlTree.h
//  project 6
//
//  Created by Arthur Hatfield on 23/03-2014.
//  Copyright (c) 2014 Arthur Hatfield. All rights reserved.
//

#ifndef __project_6__avlTree__
#define __project_6__avlTree__

#include <iostream>
#include "LinkedList.h"

using namespace std;

template <typename obj>

class avlTree {
public:
    
    avlTree<obj>(){
        size = 0;
        root = NULL;
    }
    
    virtual ~avlTree(){
        clear();
    }
    
    class node {
    public:
        obj item;
        node* left;
        node* right;
        int height;

    };
    
    
    node* root;
    int size;
    
    void clear(){ 	// redo
        if(size != 0){

        }
    }
    
    LinkedList<node*> level(LinkedList<node*> & current){
    	LinkedList<node*> next;
    	for(int i = 1; i < current.bigness(); i++){
    		node* at = current.get(i);
    		if(at->left != NULL)
    			next.insert(next.bigness(),at->left);
    		if(at->right != NULL)
    			next.insert(next.bigness(),at->right);
    	}
    	return next;
    }
    
    void print(LinkedList<node*> & level, int & no, ofstream & to){
    	for(int i = 0; i < level.bigness(); i++){
        	if (i % 8 == 0){
        		cout << endl << "level " << no << ": ";
        		cout << "DONGS";
        	}
        	node* at = level.get(i);
        	cout << at->item << "(" << at->height << ") ";
    	}
    }

    void print(ofstream & to){// redo
    	if(size != 0){
    		LinkedList<node*> zero;
    		zero.insert(0,root);
    		int depth = 0;
    		print(zero,depth,to);
    		LinkedList<node*> next = level(zero);
    		while(next.bigness() != 0){
    			print(next,depth,to);
    			depth++;
    			next = level(next);
    		}
    	}
    }

    void add(const obj& item) {
    	if (size == 0){
    		node* first = new node;
    		root = first;
    		first -> item = item;
    		first -> left = NULL;
    		first -> right = NULL;
    		first -> height = 1;
    		size++;
    	}
    	else {
    		add(item, root);
    	}
    }

    void add(const obj& item, node* where) {
    	if (item < where -> item){
    		if (where -> left == NULL){
    			node* temp = new node;
    			temp -> item = item;
    			temp -> left = NULL;
    			temp -> right = NULL;
    			temp -> height = 1;	// is always added as leaf, h = 1
    			where -> left = temp;
    			size++;
    		}
    		else {
    			add(item, where->left);
    		}
    	}
    	if (item > where -> item){
    		if (where -> right == NULL){
    			node* temp = new node;
    			temp -> item = item;
    			temp -> left = NULL;
    			temp -> right = NULL;
    			temp -> height = 1;	//	is always added as leaf, h = 1
    			size++;
    			where -> right = temp;
    		}
    		else {
    			add(item, where->right);
    		}
    	}
    	if (item == where -> item){
    		return;
    	}//if this doesn't work, parentheses
//    	if ((where -> left) -> height > (where -> right) -> height){
//    		where -> height = (where -> left) -> height + 1;
//    	}
//    	else {
//    		where -> height = (where -> right) -> height + 1;
//    	}
    }


    void remove(const obj& item){
    	if(size != 0){
    		remove(item, root);
    	}
    }

    
    void remove(const obj& item, node* where) {


        
    }
    
    bool find(const obj& item) {
    	node* src = root;
    	while(src != NULL){
    		if (item == src -> item){
    			return true;
    		}
    		if (item > src -> item){
    			src = src -> right;
    		}
    		if (item < src -> item){
    			src = src -> left;
    		}
    	}
    	return false;
    }

    


};






#endif /* defined(__project_6__avlTree__) */
