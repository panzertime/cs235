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

	node(obj i){
		left = NULL;
		right = NULL;
		item = i;
		height = 1;
	}

        virtual ~node(){
        	left = NULL;
        	right = NULL;
        }

    };
    
    
    node* root;
    int size;
    
    void clear(){ 	// redo
        if(size != 0){
		remove(root->item);
        }
    }

	//following code is responsible for figuring out which
	//levels to print
    void level(LinkedList<node*> & current, int & no, ofstream & to){
    	LinkedList<node*> plus;
    	int k = current.size;
    	for(int i = 0; i < k; i++){
    		node* at = current.get(i);
    		if(at->right != NULL){
    			plus.append(at->right);
    		}
    		if(at->left != NULL){
    			plus.append(at->left);
    		}
    	}
    	if (plus.size != 0){
    		print(plus,no,to);
    		no++;
    		level(plus,no,to);
    	}
    	else {
    		return;
    	}
    }
    
    void print(LinkedList<node*> & lev, int & no, ofstream & to){
    	int k = lev.size;
    	for(int i = 0 ; i < k; i++){
        	if (i % 8 == 0){
        		to << endl << "level " << no << ": ";
        	}
        	node* at = lev.get((k-i)-1);
        	to << at->item << "(" << at->height << ") ";
    	}
    }

    void print(ofstream & to){// redo
    	if(size != 0){
    		LinkedList<node*> zero;
    		zero.insert(0,root);
    		int depth = 0;
    		print(zero,depth,to);
    		depth++;
    		level(zero,depth,to);
    		to << endl;
    	}
    	if(size == 0){
    		to << endl;
    	}
    }


    void fixHeight(node* lroot){
    	int l = heightAt(lroot->left);
	int r = heightAt(lroot->right);
	if (l > r)
		lroot->height = l+1;
	else if (l < r)
		lroot->height = r+1;
	else
		lroot->height = r+1;
	}

    bool find(const obj& item){
    	if(size!=0){
    		return find(item,root);
    	}
    	return false;
    }

    bool find(const obj& item, node* where) {
    	if(item == where->item){
    		return true;
    	}
    	if(item > where -> item && where -> right != NULL){
    		return find(item, where->right);
    	}
    	if(item < where -> item && where -> left != NULL){
    		return find(item, where->left);
    	}
    	return false;
    }

    void add(const obj& item){
    	if(!find(item)){
    		root = add(item, root);
		size++;
		}
	}

	
	node* add (const obj& item, node* lroot) {

	if (lroot == NULL)
	return new node(item);
	if (lroot -> item < item)
		lroot -> right = add(item, lroot->right);
	if (lroot -> item > item)
		lroot -> left = add(item, lroot-> left);

	//balance here
	lroot = balance(lroot);
	//height fixing
	fixHeight(lroot);
	return lroot;
	//returns the node, follow it thru the stack trace to Oz!
	}

	node* balance (node* lroot) {
		int bal = heightAt(lroot->left) - heightAt(lroot->right);
		if (bal > 1)
			//lroot = right(lroot);
			cout << "right" << endl;
		if (bal < -1)
		//	lroot = left(lroot);
			cout << "left" << endl;
		return lroot;
	}

	node* right(node* lroot) {
		if (heightAt(lroot->left->right) > heightAt(lroot->left->left))
			lroot->left = rotateLeft(lroot->left);
		lroot = rotateRight(lroot);
		return lroot;
	}

	node* left(node* lroot) {
		if (heightAt(lroot->left->right) > heightAt(lroot->left->left))
			lroot->right = rotateRight(lroot->right);
		lroot = rotateLeft(lroot);
		return lroot;
	}

	node* rotateRight(node* lroot) {
		// insert code here~!
		return lroot;
	}

	node* rotateLeft(node* lroot) {
		// insert code here~!
		return lroot;
	}


	void remove(const obj& item){
		if(find(item)){
			root = remove(item, root);
			size--;
	}

	node* remove(const obj& item, node* lroot){
		// insert code here~!
		return lroot;
	}


    int heightAt(node* where){
    	if(where == NULL){
    		return 0;
    	}
    	else{
    		return where->height;
    	}
    }


};






#endif /* defined(__project_6__avlTree__) */
