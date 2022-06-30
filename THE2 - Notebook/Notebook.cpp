#include <iostream>
#include <string>
#include "AvlTree.cpp"
#include "BinaryTree.cpp"
#include "BinaryTree.h"
#include "AvlTree.h"
#include <fstream>
#pragma comment(linker, "/STACK:2000000")
#include <chrono>
using namespace std;


/*Main file, Ege Demirci - HW2 */

/*First struct is for the nodes of the trees inside of the notebook. */
struct item{
	string title;
	string information;
	item(){}
	item(string title):title(title){}
	item(string title,string info):title(title),information(info){}
	bool operator < (const item & rhs) const{
		return title < rhs.title;
	}
	bool operator > (const item& rhs) const{
		return title > rhs.title;
	}
	bool operator == (const item& rhs) const{
		return title == rhs.title;
	}
	friend ostream & operator <<( ostream & of, const item &s ){
		of << s.title;
		return of;
	}
};

/*This struct for the AVL Notebook, it will construct tree of tree structure and additionally
it has title string. */
struct AVLSection{
	AvlTree<item>  avlSectionTree;
	string sectionTitle;
	AVLSection(){}
	AVLSection(string title):sectionTitle(title), avlSectionTree(){}
	bool operator < (const AVLSection & rhs) const{
		return sectionTitle < rhs.sectionTitle;
	}
	bool operator > (const AVLSection& rhs) const{
		return sectionTitle > rhs.sectionTitle;
	}
	bool operator == (const AVLSection& rhs) const{
		return sectionTitle == rhs.sectionTitle;
	}
	friend ostream & operator <<( ostream & of, const AVLSection &s ) {
		of << s.sectionTitle;
		return of;
	}
};
/*This struct for the BST Notebook, it will construct tree of tree structure and additionally
it has title string. */
struct BSTSection{
	BinarySearchTree <item>  bstSectionTree;
	string sectionTitle;
	BSTSection(){}
	BSTSection(string title):sectionTitle(title), bstSectionTree(){};
	bool operator < (const BSTSection & rhs) const{
		return sectionTitle < rhs.sectionTitle;
	}
	bool operator > (const BSTSection & rhs) const{
		return sectionTitle > rhs.sectionTitle;
	}
	bool operator == (const BSTSection & rhs) const{
		return sectionTitle == rhs.sectionTitle;
	}
	friend ostream & operator <<( ostream & of, const BSTSection &s ) {
		of << s.sectionTitle;
		return of;
	}
};

/*This function helps to read data from notebook and construct the main notebooks. */
void readData(BinarySearchTree<BSTSection> & bst, AvlTree<AVLSection> & avl){
	ifstream input;
	string filename = "data.txt",line;
	BSTSection bstSectionAdded = BSTSection();
	AVLSection avlSectionAdded = AVLSection();
	input.open(filename.c_str());
	getline(input,line);
	string currentLine = line;
	long long avlTime=0, bstTime=0;
	input.clear();
	input.seekg(0);
	while(getline(input,line)){ /*File will be read line by line. */
		if (line[0] != '-' && line != currentLine){ /*Add the sections. */
			auto start_1 = chrono::high_resolution_clock::now();
			bst.insert(bstSectionAdded);  /*measure insertion. */
			auto end_1 = chrono::high_resolution_clock::now();
			bstTime += (end_1 - start_1).count() / 1000.0;  
			auto start_2 = chrono::high_resolution_clock::now();
			avl.insert(avlSectionAdded);  /*measure insertion. */
			auto end_2 = chrono::high_resolution_clock::now();
			avlTime += (end_2 - start_2).count() / 1000.0;
			cout << "Section \"" << currentLine << "\" has been inserted into the AVL notebook." << endl;
			cout << "[AVL] Elapsed time: " << avlTime << " microseconds" << endl;
			cout << "Section \"" << currentLine << "\" has been inserted into the BST notebook." << endl;
			cout << "[BST] Elapsed time: " << bstTime << " microseconds" << endl << endl;
			bstSectionAdded = BSTSection(); avlSectionAdded = AVLSection();
			currentLine = line;	bstTime = 0;avlTime = 0;
		}
		if (line[0] != '-'){ /*Process sections. */
			bstSectionAdded.sectionTitle = line;
			avlSectionAdded.sectionTitle = line;
		}
		else{ /*Add items to the sections. */
			item itemToBeAdded;
			int firstPos = line.find("-");
			int secondPos = line.find("-",firstPos+1);
			itemToBeAdded.title = line.substr(firstPos+1,secondPos-firstPos-1);
			itemToBeAdded.information = line.substr(secondPos+1); /*convert lines to the information and title*/
			auto start = chrono::high_resolution_clock::now();
			(bstSectionAdded).bstSectionTree.insert(itemToBeAdded); /*add items to the sections and measure. */
			auto end = chrono::high_resolution_clock::now();
			bstTime += (end - start).count() / 1000.0;
			auto start_2 = chrono::high_resolution_clock::now();
			(avlSectionAdded).avlSectionTree.insert(itemToBeAdded);  /*add items to the sections and measure time. */
			auto end_2 = chrono::high_resolution_clock::now();
			avlTime += (end_2 - start_2).count() / 1000.0;

		}
	}
	/*these next lines for the last section. */
	auto start = chrono::high_resolution_clock::now();
	bst.insert(bstSectionAdded);
	auto end = chrono::high_resolution_clock::now();
	bstTime += (end - start).count() / 1000.0;
	auto start_2 = chrono::high_resolution_clock::now();
	avl.insert(avlSectionAdded);
	auto end_2 = chrono::high_resolution_clock::now();
	avlTime += (end_2 - start_2).count() / 1000.0;
	cout << "Section \"" << currentLine << "\" has been inserted into the AVL notebook." << endl;
	cout << "[AVL] Elapsed time: " << avlTime << " microseconds" << endl;
	cout << "Section \"" << currentLine << "\" has been inserted into the BST notebook." << endl;
	cout << "[BST] Elapsed time: " << bstTime << " microseconds" << endl;
}

/*This function prints the main menu. */
void displayMenu(){
	cout << endl << "MENU" << endl;
	cout << "Please enter an input between [1 - 6]: " << endl << "1- Display the sections [AVL]" <<
	endl << "2- Display the sections [BST]" << endl << "3- Select a section" << endl << "4- Add new section"
	<< endl << "5- Delete a section" << endl << "6- Exit" << endl;
	cout << "Input: ";
}
/*This function prints the section menu. */
void displaySectionMenu(){
		cout << "Please enter an input between [1 - 7]:" << endl << "1- Display the items [AVL]" << 
		endl << "2- Display the items [BST]" << endl << "3- Display the information of a item" << endl <<
		 "4- Add new item" << endl << "5- Update the information of a item" << endl << "6- Delete an item"
		<< endl << "7- Return to main menu" << endl;
		cout << "Input: ";
}

/*This function displays the AVL notebook via printTree function. */
void displayAVLTree(AvlTree<AVLSection> avlNotebook){
	cout << endl << "*****" << endl;
	avlNotebook.printTree();
	cout << "*****" << endl<< endl;
}
/*This function displays the BST notebook via printTree function. */
void displayBSTTree(BinarySearchTree<BSTSection> bstNotebook){
	cout << endl << "*****" << endl;
	bstNotebook.printTree();
	cout << "*****" << endl<< endl;
}
/*This function displays the AVL section via printTree function. */
void displayAVLSection(AvlTree<item> avl){
	cout << endl << "*****" << endl;
	avl.printTree();
	cout << "*****" << endl<< endl;
}
/*This function displays the BST section via printTree function. */
void displayBSTSection(BinarySearchTree<item> bst){
	cout << endl << "*****" << endl;
	bst.printTree();
	cout << "*****" << endl<< endl;
}


/*This function displays the time info. */
void timer(long long avlTime, long long bstTime){
	cout << "[AVL] Elapsed time: " << avlTime<< " microseconds" << endl;
	cout << "[BST] Elapsed time: " << bstTime << " microseconds" << endl;
}
int main(){
	BinarySearchTree<BSTSection> bstNotebook;
	AvlTree<AVLSection> avlNotebook;
	int menu,sectionMenu;
	string sectionTitle;
	cout << "Welcome to the Notebook!"<<endl<<endl;
	readData(bstNotebook,avlNotebook);
	displayMenu();
	cin >> menu ; 
	while ( menu != 6){
		if (menu == 1){ /*if menu is 1, display the AVL tree. */
			displayAVLTree(avlNotebook);
			cout << "Input: ";
			cin >> menu;
		}
		else if (menu == 2){ /*If menu is 2, display the BST tree. */
			displayBSTTree(bstNotebook);
			cout << "Input: ";
			cin >> menu;
		}
		else if (menu == 3){ /*If menu is 3, enter the section menu. */
			cout << "Enter the title of the section: ";
			cin.ignore();
			getline(cin,sectionTitle); /*Take input as a line. */
			/*if item is not found, then it will return nothing, since trees are symmetrical check one
			is okay. */
			if (bstNotebook.find(BSTSection(sectionTitle)).sectionTitle.length() ==  0){ 
				cout << "Invalid title! " << endl << endl;
				cout << "Input: ";
				cin >> menu;			
			}
			else{ /*If item is found first show the sectionTitle then display the menu. */
				cout << endl << "Selected section -> " << sectionTitle << endl;
				displaySectionMenu();
				cin >> sectionMenu;
				bool condition = true;
				while (condition == true){
					if ( sectionMenu == 1){ /*Display the section AVL tree. */
						AVLSection avlNode = avlNotebook.find(AVLSection(sectionTitle));
						displayAVLSection(avlNode.avlSectionTree);
						cout << "Input: ";
						cin >> sectionMenu;
					}
					else if ( sectionMenu == 2){ /*Display the BST section tree. */
						BSTSection bstNode = bstNotebook.find(BSTSection(sectionTitle));
						displayBSTSection(bstNode.bstSectionTree);
						cout << "Input: ";
						cin >> sectionMenu;
					}

					else if (sectionMenu == 3){ /*display the information item. */
						string itemInfo, itemTitle;
						long long bstTime, avlTime;
						cout << "Enter the title of the item: ";
						cin.ignore();
						getline(cin,itemTitle);
						auto start = chrono::high_resolution_clock::now();
						BSTSection bstNode = bstNotebook.find(BSTSection(sectionTitle)); /*find section and measure it. */
						itemInfo = bstNode.bstSectionTree.find(item(itemTitle)).information; /*find item in the section and measure it. */
						auto end = chrono::high_resolution_clock::now();
						bstTime = (end - start).count() / 1000.0;
						auto start_2 = chrono::high_resolution_clock::now();
						AVLSection AvlNode = avlNotebook.find(AVLSection(sectionTitle)); /*find section and measure it. */
						itemInfo = AvlNode.avlSectionTree.find(item(itemTitle)).information; /*find item in the section and measure it. */
						auto end_2 = chrono::high_resolution_clock::now();
						avlTime = (end_2 - start_2).count() / 1000.0;
						timer(avlTime,bstTime);
						if (itemInfo.length() == 0){ /*If item is not found, print invalid title. */
							cout << "Invalid title." << endl<< endl;
						}
						else{
							cout << itemInfo << endl << endl;
						}
						cout << "Input: " ;
						cin >> sectionMenu;
					}
					else if (sectionMenu == 4){ /*add new item. */
						long long bstTime, avlTime;
						auto start = chrono::high_resolution_clock::now();
						BSTSection bstNode = bstNotebook.find(BSTSection(sectionTitle)); /*find the section and measure it. */
						auto end = chrono::high_resolution_clock::now();
						bstTime = (end - start).count() / 1000.0; 
						auto start2 = chrono::high_resolution_clock::now();
						AVLSection AvlNode = avlNotebook.find(AVLSection(sectionTitle)); /*find the section and measure it. */
						auto end2 = chrono::high_resolution_clock::now();
						avlTime = (end2 - start2).count() / 1000.0;
						string itemTitle,itemInfo;
						cout << "Enter a title for the item: ";
						cin.ignore();
						getline(cin,itemTitle);
						/*If item is found then it will return something so its length will be more than 0. */
						if (bstNode.bstSectionTree.find(item(itemTitle)).title.length() > 0){ 
							cout << "Item \"" << itemTitle << "\" already exists in the \"" << sectionTitle << "\"." << endl << endl;
						}
						else{
							cin.clear();
							cout << "Enter a description for the item: "; /*Enter the description of item. */
							getline(cin,itemInfo);
							item itemToBeAdded = item(itemTitle,itemInfo);
							auto start3 = chrono::high_resolution_clock::now();
							bstNode.bstSectionTree.insert(itemToBeAdded); /*insert the item and measure time. */
							bstNotebook.updateTree(BSTSection(sectionTitle), bstNode); /*update the tree. */
							auto end3 = chrono::high_resolution_clock::now();
							bstTime += (end3 - start3).count() / 1000.0;
							auto start4 = chrono::high_resolution_clock::now();
							AvlNode.avlSectionTree.insert(itemToBeAdded); /*same process. */
							avlNotebook.updateTree(AVLSection(sectionTitle), AvlNode);
							auto end4 = chrono::high_resolution_clock::now();
							avlTime += (end4 - start4).count() / 1000.0;
							timer(avlTime,bstTime);
							cout << "The new item \""<< itemTitle << "\" has been inserted." << endl << endl;
						}
						cout << "Input: ";
						cin >> sectionMenu;
					}
					else if (sectionMenu == 5){ /*update the information of the item. */
						long long bstTime, avlTime;
						auto start = chrono::high_resolution_clock::now();
						BSTSection bstNode = bstNotebook.find(BSTSection(sectionTitle)); /*first find the section and measure. */
						auto end = chrono::high_resolution_clock::now();
						bstTime = (end - start).count() / 1000.0;
						auto start2 = chrono::high_resolution_clock::now();
						AVLSection AvlNode = avlNotebook.find(AVLSection(sectionTitle)); /*first find the section and measure. */
						auto end2 = chrono::high_resolution_clock::now();
						avlTime = (end2 - start2).count() / 1000.0;
						string itemTitle,itemInfo;
						cout << "Enter the title of the item: ";
						cin.ignore();
						getline(cin,itemTitle);
						auto start3 = chrono::high_resolution_clock::now();
						item bstItem = bstNode.bstSectionTree.find(item(itemTitle)); /*then find the item and measure. */
						auto end3 = chrono::high_resolution_clock::now();
						bstTime += (end3 - start3).count() / 1000.0;
						auto start4 = chrono::high_resolution_clock::now();
						item avlItem = bstNode.bstSectionTree.find(item(itemTitle)); /*then find the item and measure. */
						auto end4 = chrono::high_resolution_clock::now();
						avlTime += (end4 - start4).count() / 1000.0;
						timer(avlTime,bstTime);
						if (avlItem.title.length() != 0){ /*if item is found then it will return something. */
							cin.clear();
							cout << "Enter the new information: ";
							getline(cin,itemInfo);
							item newItem = item(itemTitle,itemInfo); 
							AvlNode.avlSectionTree.updateTree(avlItem,newItem); /*update the tree. */
							avlNotebook.updateTree(AVLSection(sectionTitle), AvlNode);
							bstNode.bstSectionTree.updateTree(bstItem,newItem);/*update tree. */
							bstNotebook.updateTree(BSTSection(sectionTitle), bstNode);
							cout << "The content " << itemTitle << " has been updated." << endl << endl;
						}
						else{
							cout << "Item \"" << itemTitle << "\" does not exist in the \"" << sectionTitle << "\"." << endl << endl; 
						}
						cout << "Input: ";
						cin >> sectionMenu;
					}
					else if (sectionMenu == 6){
						long long bstTime, avlTime;
						auto start = chrono::high_resolution_clock::now();
						BSTSection bstNode = bstNotebook.find(BSTSection(sectionTitle)); /*first find the section and measure time. */
						auto end = chrono::high_resolution_clock::now();
						bstTime = (end - start).count() / 1000.0;
						auto start2 = chrono::high_resolution_clock::now();
						AVLSection AvlNode = avlNotebook.find(AVLSection(sectionTitle));  /*first find the section and measure time. */
						auto end2 = chrono::high_resolution_clock::now();
						avlTime = (end2 - start2).count() / 1000.0;
						string itemTitle,itemInfo;
						cout << "Enter the title of the item: ";
						cin.ignore();
						getline(cin,itemTitle);
						auto start3 = chrono::high_resolution_clock::now();
						item bstItem = bstNode.bstSectionTree.find(item(itemTitle));  /*then find the item and measure time. */
						auto end3 = chrono::high_resolution_clock::now();
						bstTime += (end3 - start3).count() / 1000.0;
						auto start4 = chrono::high_resolution_clock::now();
						item avlItem = bstNode.bstSectionTree.find(item(itemTitle));  /*then find the item and measure time. */
						auto end4 = chrono::high_resolution_clock::now();
						avlTime += (end4 - start4).count() / 1000.0;
						if (avlItem.title.length() != 0){ /*if item is found it will return something. */
							auto start5 = chrono::high_resolution_clock::now();
							bstNode.bstSectionTree.remove(bstItem);
							bstNotebook.updateTree(BSTSection(sectionTitle),bstNode);
							auto end5 = chrono::high_resolution_clock::now();
							bstTime += (end5 - start5).count() / 1000.0;
							auto start6 = chrono::high_resolution_clock::now();		/*delete items and measure times. */
							AvlNode.avlSectionTree.remove(avlItem);
							avlNotebook.updateTree(AVLSection(sectionTitle),AvlNode);
							auto end6 = chrono::high_resolution_clock::now();
							avlTime += (end6 - start6).count() / 1000.0;
							timer(avlTime,bstTime);
							cout << "The item \"" << itemTitle << "\" has been deleted." << endl << endl;
						}
						else{
							cout << "Item \"" << itemTitle << "\" does not exist in the \"" << sectionTitle << "\"." << endl << endl; 
						}
						cout << "Input: ";
						cin >> sectionMenu;				
					}
					else if (sectionMenu == 7){ /*if sectionMenu is 7, exit to main menu. */
						displayMenu();
						cin>> menu;
						condition = false;
					}
				}
			}

		}
		else if (menu == 4){
			string title;
			cout << "Enter a title for the section: ";
			cin.ignore();
			getline(cin,title);
			BSTSection bstNode = bstNotebook.find(BSTSection(title));
			AVLSection avlNode = avlNotebook.find(AVLSection(title));
			if (bstNode.sectionTitle.length() != 0 ){ /*if section is found it will return something. */
				cout << "Section \"" << title << "\" already exists." << endl << endl;
			}
			else{
				BSTSection bstAdd = BSTSection(title);
				AVLSection avlAdd = AVLSection(title);
				bstNotebook.insert(bstAdd);
				avlNotebook.insert(avlAdd); 
				cout << "The new section \"" << title << "\" has been inserted." << endl << endl; /*added. */
			}
			cout << "Input: ";
			cin >> menu;
		}
		else if (menu == 5){ /*deletion. */
			string title;
			cout << "Enter the title of the section: ";
			cin.ignore();
			getline(cin,title);
			BSTSection bstNode = bstNotebook.find(BSTSection(title));
			AVLSection avlNode = avlNotebook.find(AVLSection(title));
			if (bstNode.sectionTitle.length() != 0){ /*if it found the section then it will return something. */
				bstNotebook.remove(bstNode);
				avlNotebook.remove(avlNode);
				cout << "The section has been deleted." << endl << endl;
			}
			else{
				cout << "Section \""<< title << "\" does not exist. "<< endl << endl;
			}
			cout << "Input: ";
			cin >> menu;
		}

		
	}

}