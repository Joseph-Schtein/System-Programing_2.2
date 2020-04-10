#include "FamilyTree.hpp"

using namespace std;
using namespace family;



	Node* Tree::search(Node *current, string son){
		Node* output = NULL;		
		if(current != NULL){	
			if(current->name == son)			
				return current;
		
			if(current->father != NULL)
				output= search(current->father,son);
			

			if(output == NULL && current->mother != NULL){			
				output = search(current->mother,son);
			}
				
			return output;
		}
		return NULL;
	}
		

	void Tree::addFather(Node* current, string son, string father){
		Node *tmp = search(current, son);
		tmp->father = new Node;
		tmp->father->name = father;
		tmp->father->male = true;
		tmp->father->father = NULL;
		tmp->father->mother = NULL;
	}


	void Tree::addFather(string son, string father){ 
		if(root->name != son){
			addFather(root, son, father);		
		}

		else{
			root->father = new Node;
			root->father->name = father;
			root->father->male = true;
			root->father->father = NULL;
			root->father->mother = NULL;
		}
	}


	void Tree::addMother(Node* current, string son, string mother){
		Node *tmp = search(current, son);
		tmp->mother = new Node;
		tmp->mother->name = mother;
		tmp->mother->male = false;
		tmp->mother->father = NULL;
		tmp->mother->mother = NULL;
	}


	void Tree::addMother(string son, string mother){ 
		if(root->name != son){
			addMother(root, son, mother);		
		}

		else{
			root->mother = new Node;
			root->mother->name = mother;
			root->mother->male = false;
			root->mother->father = NULL;
			root->mother->mother = NULL;
		}
	}

	string Tree::relation(Node *current, string nameSearch, int depth){
		
		string output = "";
		if(current != NULL  && current->name == nameSearch){
			if(depth == 1){
				if(current->male == true)
					return "father";

				else
					return "mother";
			}

			
			else{

				if(depth>2){
					output = "great-";	
								

					for(int i = 3; i < depth ; i++){
						output += "great-"; 
					}
		
					if(current->male == true)
						return output + "grandfather";
	
					else
						return output + "grandmother";
				}
					
				else if(depth==2){

					if(current->male == true)
						return "grandfather";
	
					else
						return "grandmother";	
				}
						
			}

		}

		else if(current != NULL ){
			output = relation(current->father, nameSearch, depth+1);			
			if(output == "unrelated"){
				output = relation(current->mother, nameSearch, depth+1);
			}
		}		
		
		if(output != "")
			return output;	
		
		else{
			return "unrelated";			
		}
	}
	

	string Tree::relation(string nameSearch){
		string output = "";
		if(root->name == nameSearch){
			return "me";
		}

		else{
			output = relation(root->father, nameSearch, 1);
			if(output == "unrelated")
				output = relation(root->mother, nameSearch, 1);	
			return output;			
		}
	
		
	}

	string Tree::find(Node *current ,string related, int depth){
		string output = "";		
		if(current != NULL){
			if(depth > 1){			
				output = find(current->father, related, depth-1);
				if(output == "")
					output = find(current->mother, related, depth-1);
			}
			
			else{
				int length = related.length();
				string gender = related.substr(length-6, length);
				if(gender == "father"){
					if(current->father != NULL)
						return current->father->name;
				
					else if(current->mother != NULL)
						return current->mother->name;
					
				}	
			}	
		}
		throw invalid_argument("We did not find someone withe this "+related + " relation to you");
	
	}

	string Tree::find(string related){
		if(related == "you"){
			return root->name;
		}

		else if(related == "father")
			return root->father->name;

		else if(related == "mother")
			return root->mother->name;


		else{
			int length = related.length();
			int depth = 2;
			string tmp = "";
			for(int i = 0; i < length; i++){
				tmp = tmp + related[i];
				if(tmp == "great-"){
					tmp = "";
					depth++;
				}
			}

			return find(root, related, depth);			
		}
	}



	void Tree::remove(Node *current){
		if(current->father == NULL && current->mother == NULL){
			free(current);
			return;
		}
		
		else if(current != NULL){
			remove(current->father);
			remove(current->mother);
			free(current);
			return;
		}

		return;
	}



	void Tree::remove(string name){				
		Node *current  = search(root,name);
		if(current != NULL){
			remove(current);
		}	
	}

	int Tree::depth(Node *current, int height){
		int max = height, tmp;
		if(current != NULL){
			tmp = depth(current->father, height+1);
			
			if(max<tmp)
				max = tmp;
	
			tmp = depth(current->mother, height+1);
			
			if(max<tmp)
				max = tmp;
			
		}

		else
			return height-1;


		return 0;//Irrlevant return statment 
	}

	void Tree::display(Node *current){
		if(current != NULL && current->father != NULL && current->mother != NULL){
			cout << "( "<< current->name << ", " << current->father->name << ", " << current->mother->name << " )" << endl;
		}

		else if(current != NULL && current->father != NULL && current->mother == NULL){
			cout << "( "<< current->name << ", " << current->father->name << ", " << "unknown" << " )" << endl;
		} 

		else if(current != NULL && current->father == NULL && current->mother != NULL){
			cout << "( "<< current->name << ", " << "unknown" << ", " << current->mother->name  << " )" << endl;
		}

		else if(current != NULL && current->father == NULL && current->mother == NULL){
			cout << "( "<< current->name << ", " << "unknown" << ", " << "unknown"  << " )" << endl;
		}

		if(current != NULL){
			display(current->father);
			display(current->mother);
		}

		return; 
	}


	void Tree::display(){
		display(root);
	}



























