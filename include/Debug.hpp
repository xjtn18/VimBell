//////////////////////////////////////////////////////
//  Author: Jacob Nardone
//  Date created: 6/17/2020
//  File type: C++ header file
//  Description: Helper functions I made to debug/print objects, strings, etc. and to create/initialize common data structures. This helps especially when creating test cases.
//////////////////////////////////////////////////////

#pragma once
#include <unistd.h>
#include <thread>
#include <vector>
#include <iostream>
#include <queue>
#include <cmath>
#include <sstream>

#define kDEBUG 1 // set this to 0 if you dont want to see any of your dlogs


////////////////////////////////////////
// Log functions
////////////////////////////////////////

template <typename T>
void buffer(T input){
	std::cout << input << std::endl;
	std::string _;
	std::getline(std::cin, _);
}


// this template prints anything (singular value)
template <typename T>
void dlog(T x, bool nl = true, unsigned int sleeptime = 0){
	if (!kDEBUG)
		return;
	std::cout << x;
	if (nl)
		std::cout << "\n";
	//usleep(sleeptime * 100000);
}


// this template prints arrays
template <typename T>
void dlog(T* x, int len){
	for (int y = 0; y < len; y++){
		dlog(x[y], false);
		if (y != len-1){
			dlog(", ", false);
		}
	}
	dlog("");

}

// this template prints vectors
template <typename T>
void dlog(std::vector<T> v, bool nl = true){
	std::cout << '[';
	for (int i = 0; i < v.size(); ++i){
		dlog (v[i], false);
		if (i != v.size()-1)
			std::cout << ", ";
	}
	std::cout << ']';
	if (nl) std::cout << "\n";
}





////////////////////////////////////////
// Linked Lists
////////////////////////////////////////


// standard (LeetCode) linked list node structure
struct ListNode {
	int val;
	ListNode* next;
	ListNode();
	ListNode(int x);
	ListNode(int x, ListNode *next);
};


// template to intitialize and fill a linked list from a given vector
template <typename T>
ListNode* createLL(std::vector<T> v){
	if (v.empty()){
		return nullptr;
	}
	ListNode* head = new ListNode(v[0]);
	ListNode* curr = head;
	for (int i = 1; i < v.size(); ++i){
		curr->next = new ListNode(v[i]);
		curr = curr->next;
	}
	return head;
}


// Print a Linked List
void dlog(ListNode* head);


////////////////////////////////////////
// Binary Trees
////////////////////////////////////////


// standard (LeetCode) binary tree node structure
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode();
	TreeNode(int x);
	TreeNode(int x, TreeNode *left, TreeNode *right);
};


// recursive function that fills binary tree row by row left to right
void fill(TreeNode* node, std::vector<std::string> v, int i);

// initialize and fill a binary tree (row by row) from a given vector
TreeNode* createBinaryTree(std::string vstr);


