#pragma once 
 
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

namespace family{
	struct Node;
	class Tree;
}



struct family::Node{
	string name;
	Node* father;
	Node* mother;
	bool male;
};



class family::Tree{
		
	private:
			
		
	
		Tree& addFather(Node* current, string son, string father);
		Tree& addMother(Node *current ,string son, string mother);
		string relation(Node *current ,string namesSearch, int depth);
		string find(Node *current , int depth, bool gender);
		void remove(Node* current);
		void display(Node *current);
		Node* search(Node *current, string parent);
		Node* searchChiled(Node *current, string parent);
		void destroyTree(Node *current);
		

	public:

		


		Node* root;
		
		Tree(string me){
			root = new Node;
			root->name=me;
			root->father=NULL;
			root->mother=NULL;
			root->male=true;
		}

		~Tree(){
			destroyTree(root);
		}

		Tree& addFather(string son, string father);
		Tree& addMother(string son, string mother);
		string relation(string namesSearch);
		string find(string related);
		void remove(string name);		
		void display();	


};
