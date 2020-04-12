#include "FamilyTree.hpp"

using namespace std;
using namespace family;




	void Tree::destroyTree(Node* current){
		if(current != NULL){
			destroyTree(current->father);
			destroyTree(current->mother);
			delete current;	
			
		}
	}



	Node* Tree::search(Node *current, string parent){
		Node* output = NULL;		
		if(current != NULL){	
			if(current->name == parent)			
				return current;
		
			else if(current->father != NULL)
				output= search(current->father,parent);
			

			else if(output == NULL && current->mother != NULL){			
				output = search(current->mother,parent);
			}
				
			return output;
		}
		return NULL;
	}

	Node* Tree::searchChiled(Node *current, string parent){		
		Node* output = NULL;		
		if(current != NULL){	
			if(current->father->name == parent || current->mother->name == parent)			
				return current;
		
			else if(current->father != NULL){
				output = searchChiled(current->father,parent);
			}

			else if(output == NULL && current->mother != NULL){			
				output = searchChiled(current->mother,parent);
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

	string Tree::find(Node *current , int depth, bool gender){
		string output = "";		
		if(current != NULL){
			if(depth == 0){
				return current->name;
			}

			else if (depth == 1){
				if(gender == true)
					return find(current->father, depth-1, gender);
				

				else
					return find(current->mother, depth-1, gender);
		
			}

			else{
				output = find(current->father, depth-1, gender);
				if(output == "")				
					output = find(current->mother, depth-1, gender);
			}
		}
		
		return output;

	
	}

	string Tree::find(string related){
		
		string output = "";
		bool male; 

		if(related == "me"){
			return root->name;
		}

		else if(related == "father")
			return root->father->name;

		else if(related == "mother")
			return root->mother->name;


		else{
			int length = related.length();
			string tmp = "";			
			for(int i = length-6; i < length; i++){			
				tmp = tmp + related[i];
			}
	
			if(tmp == "father")
				male = true;
	
			else
				male = false;

			length = length-11;
			length = length/6;			
			int depth = 2+length;
			if (related.find("father") != std::string::npos || related.find("mother") != std::string::npos){	
				output = find(root->father, depth-1, male);
				if(output == "")
					output = find(root->mother, depth-1, male);	
			}
		
		}

		if(output == ""){
			throw invalid_argument("The tree cannot handle the '"+related + "' relation");
		}

		else
			return output;
	}



	void Tree::remove(Node *current){		
		if(current != NULL){
			remove(current->father);
			remove(current->mother);
			current->father = NULL;
			current->mother = NULL;			
			
		}
	}



	void Tree::remove(string name){					
		Node *current  = searchChiled(root,name);
		if(current != NULL){
			remove(current);
		}	
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


