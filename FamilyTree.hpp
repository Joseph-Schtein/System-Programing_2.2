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
			
		
	
		void addFather(Node* current, string son, string father);
		void addMother(Node *current ,string son, string mother);
		string relation(Node *current ,string namesSearch, int depth);
		string find(Node *current ,string related, int depth);
		void remove(Node *current);
		void display(Node *current);
		Node* search(Node *current, string son);
		int depth(Node *current, int height);

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
			remove(root->name);
		}

		void addFather(string son, string father);
		void addMother(string son, string mother);
		string relation(string namesSearch);
		string find(string related);
		void remove(string name);		
		void display();	


};

