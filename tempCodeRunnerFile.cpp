#include <iostream>
#include <iomanip>
#include <math.h>
#include <string.h>
using namespace std;
// the constant of arrays size of this code
const int arSize = 200;

class Product{
	private:
		char name[arSize] , buyingCost[arSize] , sellingCost[arSize] ;
		int quantity;
	public:
		Product( char[] , char[], char[] , char[] );
		char getName();
		char getBuyingCost();
		char getSellingCost();
		int getQuantity();
		void setName(char*);
		void setBuyingCost(char*);
		void setSellingCost(char*);
		void setQuantity(int);
		void printName();
		void printBuyingCost();
		void printSellingCost();
		void printQuantity();
};
// constructor
Product::Product(char inputName[] , char inputBuyingCost[] , char inputSellingCost[] ){
	setName(inputName);
	setBuyingCost(inputBuyingCost);
	setSellingCost(inputSellingCost);
}
// based on setting the values
void Product::setName(char inputName[arSize]){
	int i = 0;
		for(i = 0 ; inputName[i]!='\0' ; i++){
			cout<<"i:"<<i<<endl;
		name[i] = inputName[i];
	}
	name[i] = '\0';
}
void Product::setBuyingCost(char inputBuyingCost[arSize]){
	int i = 0;
		for(i = 0 ; inputBuyingCost[i]!='\0' ; i++){
			cout<<"i:"<<i<<endl;
		buyingCost[i] = inputBuyingCost[i];
	}
	buyingCost[i] = '\0';
}
void Product::setSellingCost(char inputSellingCost[arSize]){
	int i = 0;
		for(i = 0 ; inputSellingCost[i]!='\0' ; i++){
			cout<<"i:"<<i<<endl;
		sellingCost[i] = inputSellingCost[i];
	}
	sellingCost[i] = '\0';
}
void Product::setQuantity(int inputQuantity){
	quantity = inputQuantity;
}
// to get the parameters
char Product::getName(){
	return *name;
}
char Product::getBuyingCost(){
	return *buyingCost;
}
char Product::getSellingCost(){
	return *sellingCost;
}
// based on printing the values of products
void Product::printName(){
	for(int i = 0 ; name[i] != '\0' ; i++)cout<<name[i];
}
void Product::printBuyingCost(){
	for(int i = 0 ; buyingCost[i] != '\0' ; i++)cout<<buyingCost[i];
}
void Product::printSellingCost(){
	for(int i = 0 ; sellingCost[i] != '\0' ; i++)cout<<sellingCost[i];
}

int main(){
	char define[] = "Define" , del[] = "Delete" , sell[] = "Sell" , buy[] = "Buy" , status[] = "Status" , financial[] = "Financial" , exit[] = "Exit";
	// the state of exiting of program
	bool exitState = false;
	char commandName[50];
	// array of products
	Product products[]={};
	// it shows the quantity of the products
	int commandSize = 0;
	
		while(!exitState){
		cin>>commandName;
			if(strcmp(commandName,define)==0){
				cout<<"define access!"<<endl;
				char name[arSize] , buyingCost[arSize] , sellingCost[arSize] ;
				cin>>name>>buyingCost>>sellingCost;
				Product *command = (products+(commandSize++));
				(*command).setName(name);
				(*command).setBuyingCost(buyingCost);
				(*command).setSellingCost(sellingCost);
			}
			else if(strcmp(commandName,del)==0);
			else if(strcmp(commandName,sell)==0);
			else if(strcmp(commandName,buy)==0);
			else if(strcmp(commandName,status)==0);
			else if(strcmp(commandName,financial)==0);
			else if(strcmp(commandName,exit)==0);
		
		}

return 0;
}
