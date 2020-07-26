#include "FamilyTree.hpp"

using namespace std;
using namespace family;




	void Tree::destroyTree(Node* current){
		if(current){
			destroyTree(current->father);
			destroyTree(current->mother);
			current->father = NULL;
			current->mother = NULL;
			current = NULL;
			
		}
	}



	Node* Tree::search(Node *current, string parent){
		Node* output = NULL;		
		if(current){	
			if(current->name == parent)			
				return current;
		
			else if(current->father)
				output= search(current->father,parent);
			

			if(!output && current->mother){			
				output = search(current->mother,parent);
			}
				
			return output;
		}
		return NULL;
	}

	Node* Tree::searchChiled(Node *current, string parent){		
		Node* output = NULL;		
		if(current){	
	    if((current->father && current->father->name==parent)||(current->mother && current->mother->name== parent))			
				return current;
		
			else if(current->father){
				output = searchChiled(current->father,parent);
			}

			if( !output && current->mother){			
				output = searchChiled(current->mother,parent);
			}	
			return output;
		}
		return NULL;
	}
		

	Tree& Tree::addFather(Node* current, string son, string father){
		Node *tmp = search(current, son);
		if(tmp && !tmp->father){
			tmp->father = new Node;
			tmp->father->name = father;
			tmp->father->male = true;
			tmp->father->father = NULL;
			tmp->father->mother = NULL;
			return *this;
		}	
		throw invalid_argument("He have a father already");

	}


	Tree& Tree::addFather(string son, string father){ 
		if(root->name != son){
			return addFather(root, son, father);		
		}

		else{
			root->father = new Node;
			root->father->name = father;
			root->father->male = true;
			root->father->father = NULL;
			root->father->mother = NULL;
			return *this;

		}
	}


	Tree& Tree::addMother(Node* current, string son, string mother){
		Node *tmp = search(current, son);
		if(tmp && !tmp->mother){		
			tmp->mother = new Node;
			tmp->mother->name = mother;
			tmp->mother->male = false;
			tmp->mother->father = NULL;
			tmp->mother->mother = NULL;
			return *this;
		}
		throw invalid_argument("He have a father already");
	}


	Tree& Tree::addMother(string son, string mother){ 
		if(root->name != son){
			return addMother(root, son, mother);		
		}

		else{
			root->mother = new Node;
			root->mother->name = mother;
			root->mother->male = false;
			root->mother->father = NULL;
			root->mother->mother = NULL;
			return *this;
		}
	}

	string Tree::relation(Node *current, string nameSearch, int depth){
		
		string output = "";
		if(current  && current->name == nameSearch){
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

		else if(current){
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
		if( root && root->name == nameSearch){
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
		if(current){
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


	void Tree::remove(string name){					
		
		if(root && root->name == name){
			destroyTree(root);
			
		}
		else{
			Node *current  = search(root, name);
			if(current){
				destroyTree(current);
				
			}
		}	
	}

	


	void Tree::display(Node *current){
		
		if(!current)
			return;

		if(current && current->father && current->mother){
			cout << "( "<< current->name << ", " << current->father->name << ", " << current->mother->name << " )" << endl;
		}

		else if(current && current->father && !current->mother){
			cout << "( "<< current->name << ", " << current->father->name << ", " << "unknown" << " )" << endl;
		} 

		else if(current && !current->father && current->mother){
			cout << "( "<< current->name << ", " << "unknown" << ", " << current->mother->name  << " )" << endl;
		}

		else if(current && !current->father && !current->mother){
			cout << "( "<< current->name << ", " << "unknown" << ", " << "unknown"  << " )" << endl;
		}

		if(current){
			display(current->father);
			display(current->mother);
		}
 
	}


	void Tree::display(){
		display(root);
	}


