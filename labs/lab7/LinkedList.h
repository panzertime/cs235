//
//  LinkedList.h
//  project 5
//
//  Created by Arthur Hatfield on 23/03-2014.
//  Copyright (c) 2014 Arthur Hatfield. All rights reserved.
//

#ifndef __project_5__LinkedList__
#define __project_5__LinkedList__

#include <iostream>

using namespace std;

template <typename obj>

class LinkedList {
public:
    
    LinkedList<obj>(){
        size = 0;

        head = NULL;
        tail = NULL;
    }
    
    virtual ~LinkedList(){
        clear();
    }
    
    class node {
    public:
        obj item;
        node* next;
        node* prev;

    };
    
    
    node* head;
    node* tail;
    int size;
    
    int bigness(){
    	return size;
    }

    void clear(){
        if(size != 0){
            for(int i = size - 1; i >= 0; i--) {
            	remove(i);
            }
        }
    }
    
    void print(ofstream & to){
    	if(size != 0){
            node *temp = head;
            int i = 0;
            for (i = 0; i < size; i++) {
            	temp = getptr(i);
                to << "node " << i << ": " << temp->item;
                cout << std::endl;

            }
    	}
    }
    
    void print(){
    	if(size != 0){
            node *temp = head;
            int i = 0;
            for (i = 0; i < size; i++) {
            	temp = getptr(i);
                cout << "node " << i << ": " << temp->item;
                cout << std::endl;

            }
    	}
    }

    void append(const obj & item) {
    	if (size == 0){
    		node *nov = new node;
    		nov->item = item;
    		head = nov;
    		tail = nov;
    		nov->next = NULL;
    		nov->prev = NULL;
    		size++;
    		return;
    	}

		node *nov = new node;
		node *pos = tail;
		nov->item = item;
		nov->next = NULL;
		nov->prev = pos;
		pos->next = nov;
		tail = nov;
		size++;
    }

    void insert(int index, const obj& item) {
    	if (size == 0){
    		node *nov = new node;
    		nov->item = item;
    		head = nov;
    		tail = nov;
    		nov->next = NULL;
    		nov->prev = NULL;
    		size++;
    		return;
    	}
    	if (index == 0){
    		node *nov = new node;
    		node *vto = head;
    		vto->prev = nov;
    		nov->item = item;
    		nov->next = vto;
    		nov->prev = NULL;
    		head = nov;
    		size++;
    		return;
    	}
    	if (index == size){
    		node *nov = new node;
    		node *pos = tail;
    		nov->item = item;
    		nov->next = NULL;
    		nov->prev = pos;
    		pos->next = nov;
    		tail = nov;
    		size++;
    		return;
    	}
        if (index < size ) {
            
            node *temp = getptr(index);
          //  cout << "  ! ! ! " << temp->item << endl;
            node *nov = new node;
            nov->item = item;
            
            node *bef = temp->prev;
            bef->next = nov;
            nov->prev = bef;
            nov->next = temp;
            temp->prev = nov;
            
            size++;
            
            //think thru this carefully for first and last node

        }
    }
    
    void remove(int index) {
        

    	if (index == 0){
    		node *temp = head;
    		head = temp->next;
    		size--;
    		delete temp;
    	}
    	if (index == size - 1){
    		node *temp = tail;
    		tail = temp->prev;
    		size--;
    		delete temp;
    	}
        if (index < size){
            node *temp = getptr(index);
            node *bef = temp->prev;
            node *aft = temp->next;
            bef->next = aft;
            aft->prev = bef;
            size--;
            delete temp;
        }

        
    }
    
    int find(const obj& item) {
        node *temp = head;
        int i = 0;
        while (i < size){
        	if(temp->item == item){
        		return i;
        	}
        	i++;
        	temp = temp->next;
        }

        return -1;
        
    }
    
    node* getptr(int & index){

    	if (index == 0){
    		return head;
    	}

    	if (index == size - 1){
    		return tail;
    	}

    	if (index < size / 2){
            node *temp = head;
            int i = 0;
            while (i < index){
            	i++;
            	temp = temp->next;
            }
            return temp;
    	}
    	else {
            node *temp = tail;
            int i = size - 1;
            while (i > index){
            	i--;
            	temp = temp->prev;
            }
            return temp;
    	}
    }

    obj get(int index){

    	if (index == 0){
    		return head->item;
    	}

    	if (index == size - 1){
    		return tail->item;
    	}

    	if (index < size / 2){
            node *temp = head;
            int i = 0;
            while (i < index){
            	i++;
            	temp = temp->next;
            }
            return temp->item;
    	}
    	else {
            node *temp = tail;
            int i = size - 1;
            while (i > index){
            	i--;
            	temp = temp->prev;
            }
            return temp->item;
    	}
    }
    

};






#endif /* defined(__project_5__LinkedList__) */
