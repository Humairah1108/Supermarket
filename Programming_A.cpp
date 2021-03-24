#define _CRT_SECURE_NO_WARNINGS 
//using crt_secure_no_warnings to be able to generate the current time and date 
//VS studio does not allow the use of localtime and ctime without defining _CRT_SECURE_NO_WARNINGS 

#include<iostream>
#include<string>
#include<fstream>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include<ctime>
#include<bits.h>
#include<sstream>

using namespace std;
//menu to display
void menu1() {
	cout << "Choose Your Job" << endl;
	cout << endl;
	cout << "1: Cashier" << endl;
	cout << "2. Stock Operator" << endl;
	cout << "3: Exit Program" << endl;
}
//menu to display
void menu2() {

	cout << " 1. Edit Purchase List" << endl;
	cout << " 2. Confirm Purchase" << endl;
	cout << endl;
	cout << "What do you want to do?" << endl;
}
//menu to display
void menu3() {
	cout << "  1: Remove an item" << endl;
	cout << "  2: Edit Quantity" << endl;
	cout << " -1: Go Back " << endl;
	cout << endl;
	cout << "What do you want to do?" << endl;
}
//function to calculate the number of occurrences of an element in an array
int numOccurences(int a[], int n, int x)
{
	int count = 0;
	for (int i = 0; i < n; i++)
		if (a[i] == x)
			count++;
	return count;
}

int main() {
	//variable choice1 of integer datatype to store the choice made by the user
	int choice1;
	//displays a welcome message
	cout << "Welcome to Amazing Supermarket!" << endl;

	cout << endl;
	//displays a menu for the cashier to choose from
	menu1();
	cout << endl;//leaves a line
	cout << "Enter your choice: ";
	//validation if the cashier has input a value that is not of integer data type
	while (!(cin >> choice1)) {
		//displays an error message
		cout << "Error! Choice must be an integer!!" << endl;
		cin.clear();
		cin.ignore(123, '\n');
		cout << endl;
		//prompts the cashier to input a choice again
		cout << "Enter your choice: ";
	}

	int barcode_S, barcode_C, qtyInStock, reOrderLvl;
	string itemName;
	float buyingPrice, sellingPrice;
	const int pctgVat = 15;
	bool isvalid = false;

	string item_Name;
	double itemPrice_VatIncl;
	float itemPrice_VatExcl = 0;
	int itemQty;

	bool is_valid = false;
	while (choice1 != 3) {
		if (choice1 == 1) {
			cout << endl;
			ifstream f2("Stock.txt");
			if (!f2.is_open()) {
				//outputs an error message if the file cannot be opened
				cout << "Error opening file Stock.txt!" << endl;
			}
			else {
				//cout << "File Stock.txt opened successfully!" << endl;
			}
			//variable to store contents of the file
			int d1, d3, d4, d7;
			double d5, d6;
			string d2;

			//array to store the existing barcode from the text file
			int bcode[20];
			//array to store the names of existing item names
			string iname[20];
			//array to to the quantity of each item---------------------------------------------------------
			int qty[20];//------------------------------------------------------------------------------------------to be deleted???-------------------------
			for (int i = 0; i < 20; i++) {
				qty[i] = 0;//initialise
			}
			//----------------------------------------------------------------------------------------------
			//array to store the selling price of each item
			double sp[20];
			//variable to store the vat
			int vat;
			//array to store the quantities in stock
			int qtystock[20];
			//array to store the reorder levels
			int reorderlv[20];
			//array to store buying prices
			double bp[20];

			//this variable store the first line of the text file
			string dummyLine;
			getline(f2, dummyLine);//ignores first line which contains column names

			//Read the text file as from the second line and write the values to the corresponding variables
			for (int i = 0; i < 20; i++) {
				f2 >> d1 >> d2 >> d3 >> d4 >> d5 >> d6 >> d7;
				//reading from the text file stock.txt and storing each value in their respective arrays
				bcode[i] = d1;
				iname[i] = d2;
				qtystock[i] = d3;
				reorderlv[i] = d4;
				bp[i] = d5;
				sp[i] = d6;
				vat = d7;
			}
		
			//-------------------------------checking the contents of arrays-----------------------------------------
			/*cout << endl;
			cout << "selling prices" << endl;
			for (int i = 0; i < 20; i++) {
				cout << sp[i] << endl;
			}
			cout << "VAT is " << vat << endl;
			cout << endl;
			//--------------------------------------------------------------------------------------------
			cout << "content is" << endl;
			for (int i = 0; i < 20; i++) {
				cout << bcode[i] << endl;
			}
			cout << endl;*/
			//-----------------------------------------------------------------------------------------------------------

			//counter to count the number of items being purchased by the customer
			int count = 0;

			//prompts the cashier to input a barcode
			cout << "Enter 000 if no more items" << endl;
			cout << "Enter 3-digit barcode: ";

			//if the cashier input a value not of integer data type
			while (!(cin >> barcode_C)) {
				cout << "Error! barcode must be an integer!!" << endl;
				cin.clear(); //clears the value input
				cin.ignore(123, '\n');
				//prompts the cashier to input the barcode again
				cout << "Enter 000 if no more items" << endl;
				cout << "Enter 3-digit barcode: ";
			}

			//assuming that the total amount of items that a customer can purchase is 100
			int bcodeinput[100];
			//initialising to zero
			for (int i = 0; i < 100; i++) {
				bcodeinput[i] = 0;
			}
			//-----------------------------------------------------------------------------------------------------------------------------------
			//We assume 000 to be a rogue value => if the cashier input 000 => there are no more items to be purchased by the customer
			while (barcode_C != 000) {
				//flag to indicate whether the barcode input by the cashier exist in the supermarket barcode list
				bool find = false;
				//checks if the barcode input by the cashier contains 3-digits
				if (to_string(barcode_C).size() == 3) {

					for (int i = 0; i < 20; i++) {
						//checks if the barcode input is contained in the list of already existing barcode
						if (barcode_C == bcode[i]) {
							//cout << "Barcode found in barcode list!" << endl;
							//if found, find becomes true
							find = true;
						}
					}

					//if the barcode is not found, clears the value input by the user
					if (find == false) {
						//clears the value input by the cashier
						cout << "Barcode not found in barcode list!" << endl;
						//ignore and clear the value
						cin.clear();
						cin.ignore(123, '\n');
					}
					else {
			
						//assigns the barcode input by the cashier to the nth barcode input by the user
						bcodeinput[count] = barcode_C;

						//flag to indicate whether a barcode exist or not
						bool found = false;
						//variable to store the position of the barcode in the list
						int position;

						//checks if barcode exist in existing list
						for (int j = 0; j < 20; j++) {
							//checks if the barcode input by the cashier exists in the array, that is, if it exists in the supermarket file
							if (barcode_C == bcode[j]) {
								//get the position of the barcode in the array list
								position = j;
								found = true; //the barcode has been found in the array => it exists
							}
						}
						//check if the stock of the item is empty before continuing with the purchase
						//if the cashier accidently inputs a barcode for an item that is no longer available
						if (qtystock[position] == 0) {
							//if there are no more item left in the supermark => user cannot buy
							cout << "Item " << iname[position] << " is no longer available!" << endl;
						}
						else {

							//we decrement the quantity in stock for that particular barcode
							qtystock[position]--;

							//---------------checking the quantity in stock-----------------------------------------------------------------------------
							//cout << "The quantity for the item " << iname[position] << " is " << qtystock[position] << endl;
							//------------

							//if the barcode is not found in the array => it does not exist
							if (found == false) {
								//if the barcode is not found, it displays an error message
								cout << "Barcode does not exist!" << endl;
							}
							f2.close();//closes the  text file
							//leaves a line
				
							//displays the receipt
							count++;//increment the number of entries that the cashier is inputting
						}
					}
				}
				else {
					//if the cashier has input a barcode less or more that 3-digits
					cout << "Warning! Barcode must be only 3-digits!" << endl;
				}

				//asks the cashier to input the next barcode
				cout << endl;
				cout << "Enter 000 if no more items" << endl;
				cout << "Enter 3-digit barcode: ";
				//validating the data type of the value input by the cashier
				while (!(cin >> barcode_C)) {
					cout << "Error! barcode must be an integer!!" << endl;
					cin.clear();
					cin.ignore(123, '\n');
					cout << endl;//leaves a line
					//prompts the cashier to input the barcode again
					cout << "Enter 000 if no more items" << endl;
					cout << "Enter 3-digit barcode: ";
				}
			}

			//----------------------------------------------------ensuring that the array contains the correct amount-------------------------------------------------
			/*cout << "Barcodes that cashier has input are:" << endl;
			for (int i = 0; i < 100; i++) {
				cout << bcodeinput[i] << endl;
			}*/
			//-----------------------------------------------------------------------------------------		
			//leaves a line to increase readability
			cout << "_________________________________________________________________________________________________________________" << endl;
			cout << endl;
			//displays "column names" like a tabular format
			cout << setw(15) << "ItemName" << setw(26) << "ItemQty" << setw(25) << "ItemPriceVatExcl" << setw(25) << "ItemPriceVatIncl" << endl;
			//leaves a line
			cout << endl;

			//variables to calculating total prices to display at the bottom of receipt
			double vatptg;
			double totalExclVat = 0;
			double totalVat;
			double totalInclVat = 0;
			string name[20];
			double disp_sp[20];
			vatptg = 1.15;
			int arrQty[20];

			//DISPLAYING THE RECEIPT BEFORE CONFIRMING PURCHASE
			for (int i = 0; i < 20; i++) {
				//COUNTS THE NUMBER OF OCCURENCES IN OF EACH BARCODE INPUT BY THE CASHIER 
				//THE NUMBER OF OCCURENCES IS EQUAL TO THE QUANTITY OF ITEMS PURCHASED BY THE CUSTOMER
				int x = bcode[i];

				//caculate the price with vat
				itemPrice_VatIncl = vatptg * sp[i];
				//calculates the number of occurences of a barcode in the array bcodeinput
				itemQty = numOccurences(bcodeinput, 100, x);

				name[i] = iname[i];
				arrQty[i] = itemQty;
				disp_sp[i] = sp[i];
				if (itemQty != 0) {
					//DISPLAYS THE LIST OF ITEMS PURCHASED BY THE CUSTOMER IN THE FORM OF A RECEIPT
					cout << setw(5) << name[i] << setw(40 - name[i].length()) << itemQty << setw(21) << fixed << setprecision(2) << itemQty * disp_sp[i] << setw(27) << itemQty * itemPrice_VatIncl << endl;
				}
				//calculate total prices.......
				totalExclVat += itemQty * sp[i]; //CALCULATES THE TOTAL PRICE WITHOUT VAT
				totalInclVat += itemQty * itemPrice_VatIncl; //CALCULATES THE TOTAL PRICE WITH VAT
			}
			cout << endl;
			// calculates the total amount of vat
			totalVat = totalInclVat - totalExclVat;

			//array containing the name of months
			string months[12] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" }; 

			//generating the current date and time
			time_t now = time(0);
			char* dt = ctime(&now);
			//cout << "date and time is " << dt << endl;
			//variable to store details about current date and time
			string str = dt;

			//variable to store the words( the split details of date and time)
			string datetime[5];

			//counter to count the number of words being input in the array datetime
			int wcount = 0;
			// Used to split string around spaces. 
			istringstream ss(str);

			// Traverse through all words 
			while (ss.good() && wcount < 5) {
				//store each 'word' in the array date time at the postion (wcount)
				ss >> datetime[wcount];
				//we increment the count 
				wcount++;
			}

			//store each word in at each position in the variables day, month, dd, time, yy respectively
			string day = datetime[0];
			string month = datetime[1];
			string dd = datetime[2];
			string time = datetime[3];
			string yy = datetime[4];

			//variable to store the current month's number
			int mm;
			//gets the month's number 
			//for example, if  the current month is May, the month number, mm is 5, that is, May is the 5th month
			for (int i = 1; i <= 12; i++) {
				if (month == months[i]) {
					mm = i;
				}
			}

			//disaplays the total price without vat, the vat amount and price with the vat
			cout << "Total Excluding VAT : Rs " << fixed << setprecision(2) <<totalExclVat << endl;
			cout << "Total VAT           : Rs " << fixed << setprecision(2) <<totalVat << endl;
			cout << "Total Including VAT : Rs " << fixed << setprecision(2) << totalInclVat << endl;
			cout << "Date of Purchase    : " << dd << "/" << mm << "/" << yy << endl;
			cout << "Time of Purchase    : " << time << endl;
			cout << endl;
			//leaves a line to increase readability
			cout << "___________________________________________________________________________________________________________________" << endl;
			cout << endl;

			int choice2;// variable to store the choice input by the cashier
			//displays a menu to ask the cashier to make a choice 
			menu2();
			//validation if the cashier has entered a data type other than an integer
			while (!(cin >> choice2)) {
				//tells the cashier to input an integer
				cout << "You must enter an integer number!!" << endl;
				cin.clear();
				cin.ignore(123, '\n');
				cout << endl; //leaves a line
				//displays a menu to ask cashier to choose again
				menu2();
			}
			//------------------------------------------------------------------------------------------

			while (choice2 != 2) {
				if ((choice2 < 1) || (choice2 > 2)) {
					//if the cashier has input a choice which are not from the menu, an error message is displayed.
					cout << "Invalid Choice!!!" << endl;
				}
				else {
					//leaves a line
					cout << endl;
					//variable to store the cashier's choice
					int choice3;
					//displays a menu
					menu3();
					//validation
					//if the cashier inputs a value that is not of integer data type
					while (!(cin >> choice3)) {
						cout << "You must enter an integer number!!" << endl;
						cin.clear();
						cin.ignore(123, '\n');
						cout << endl;
						//displays the menu again
						menu3();
					}

					//CHOICE 1  =>  TO REMOVE AN ITEM
					while (choice3 != -1) {
						if (choice3 == 1) {
							//variable to store the barcode of the item to be removed
							int bc_dlt;
							//prompts the cashier to input the barcode of the item to be removed
							cout << "Enter -1 if you wish to go back." << endl;
							cout << "Enter the barcode of the item you wish to remove: ";
							//if the cashier entered a value that is not of integer data type
							while (!(cin >> bc_dlt)) {
								//tells the cashier to input an integer
								cout << "You must enter an integer number!!" << endl;
								cin.clear();
								cin.ignore(123, '\n');
								cout << endl; //leaves a line
								//prompts the cashier to input the barcode of the item to be removed
								cout << "Enter -1 if you wish to go back." << endl;
								cout << "Enter the barcode of the item you wish to remove: ";
							}
							cout << endl;//leaves a line
							//-------------------------------------------------------------------------------
							while (bc_dlt != -1) {
								//check if cashier has input 3-digit barcode
								if (to_string(bc_dlt).size() == 3) {

									//we then check if the barcode exist in the list of barcodes that the cashier has already input
									bool isfind = false;
									//we check if the barcode to be deleted exist in the list of barcodes of the receipt
									for (int f = 0; f < 100; f++) {
										if (bc_dlt == bcodeinput[f]) {
											//cout << "Item exist in the receipt!" << endl;

											//isfind is assigned true if it is found
											isfind = true;
											//we remove the item from the list of items from the receipt
											bcodeinput[f] = 0;
										}
									}
									//if the barcode to be deleted does not exist in the list of items from the receipt, 
									if (isfind == false) {
										//we display an error message
										cout << "Item does not exist in the receipt!" << endl;
										//we ignore and clear the value of the barcode input by the cashier
										cin.clear();
										cin.ignore(123, '\n');
									}
									else {

										int pos;
										for (int d = 0; d < 20; d++) {
											//we check if the barcode exist in the list of items from the receipt
											if (bc_dlt == bcodeinput[d]) {

												//cout << "barcode found at position :" << d << endl;

												//if it exists, we remove the barcode in the array
												bcodeinput[d] = 0;
											}
										}
										//we check if the barcode to be deleted is found in the existing barcode list
										for (int d = 0; d < 20; d++) {
											if (bc_dlt == bcode[d]) {

												//cout << "barcode found at postition " << d << endl;

												//if it exists, we get its position in the list
												pos = d;
											}
										}
										//once we get its position, we remove it from the total price of the items in the receipt
										totalInclVat -= vatptg * sp[pos];
										totalExclVat -= sp[pos];
										//calculates the total amount vat included in the price
										totalVat = (totalInclVat - totalExclVat);
										cout << endl;

									}
									//-------------------------------------------------------------------------------------------------
									cout << "_________________________________________________________________________________________________________________" << endl;
									cout << endl;
									//displays "column names" like a tabular format
									cout << setw(15) << "ItemName" << setw(26) << "ItemQty" << setw(25) << "ItemPriceVatExcl" << setw(25) << "ItemPriceVatIncl" << endl;
									cout << endl;
									for (int i = 0; i < 20; i++) {
										//COUNTS THE NUMBER OF OCCURENCES IN OF EACH BARCODE INPUT BY THE CASHIER 
										//THE NUMBER OF OCCURENCES IS EQUAL TO THE QUANTITY OF ITEMS PURCHASED BY THE CUSTOMER
										int x = bcode[i];

										//calculates the number of occurences of barcodes in the array
										itemQty = numOccurences(bcodeinput, 100, x);
										//calculate the item price with vat
										itemPrice_VatIncl = vatptg * sp[i];
										name[i] = iname[i];

										disp_sp[i] = sp[i];
										//we do not displays items whose quantities are zero => the customer has not bought those items
										if (itemQty != 0) {
											//DISPLAYS THE LIST OF ITEMS PURCHASED BY THE CUSTOMER IN THE FORM OF A RECEIPT
											cout << setw(5) << name[i] << setw(40 - name[i].length()) << itemQty << setw(21) << fixed << setprecision(2) << itemQty * disp_sp[i] << setw(27) << itemQty * itemPrice_VatIncl << endl;
										}
									}
									//displays the prices and date/time details
									cout << endl;
									cout << "Total Excluding VAT : Rs " << fixed << setprecision(2) << totalExclVat << endl;
									cout << "Total VAT           : Rs " << fixed << setprecision(2) << totalVat << endl;
									cout << "Total Including VAT : Rs " << fixed << setprecision(2) << totalInclVat << endl;
									cout << "Date of Purchase    : " << dd << "/" << mm << "/" << yy << endl;
									cout << "Time of Purchase    : " << time << endl;
									cout << "___________________________________________________________________________________________________________________" << endl;
									cout << endl;

								}
								else {
									//displays an error message if the barcode input by the cashier does not have 3 digits
									cout << "Barcode must be only 3-digits!!" << endl;
								}
								
								cout << "Enter -1 if you wish to go back." << endl;
								cout << "Enter the barcode of the item you wish to remove: ";
								//validating the barcode of the item to be deleted by the cashier
								//if the cashier inputs a value that is not of integer data type
								while (!(cin >> bc_dlt)) {
									//tells the cashier to input an integer
									cout << "You must enter an integer number!!" << endl;
									cin.clear();
									cin.ignore(123, '\n');
									cout << endl; //leaves a line
									//prompts the cashier to input the barcode of the item to be removed again
									cout << "Enter -1 if you wish to go back." << endl;
									cout << "Enter the barcode of the item you wish to remove: ";
								}
							}
						}
						else {
							// TO EDIT QUANTITY OF AN ITEM
							if (choice3 == 2) {
								//Edit Quantity
								//variable to store the barcode to be edited
								int bc_edit;
								//edit quantity of an item
								cout << "Enter the barcode of the item you wish to edit: ";
								//if the cashier inputs a value which is not of integer data type
								while (!(cin >> bc_edit)) {
									//tells the cashier to input an integer
									cout << "You must enter an integer number!!" << endl;
									cin.clear();
									cin.ignore(123, '\n');
									cout << endl; //leaves a line
									//prompts the cashier to input the barcode of the item quantity to be edited again
									cout << "Enter the barcode of the item you wish to edit: ";
								}
								cout << endl;//leaves a line
								//flag to indicate whether the barcode has been found in the list or not
								bool fnd = false;
								//variable to get the position of the barcode in the existing list of arrays
								int bpos;
								for (int f = 0; f < 20; f++) {
									//first we check if the barcode to be edited which the cashier has input is found in the existing barcode list of the supermarket
									if (bc_edit == bcode[f]) {
										//if it exist, we get its position in the list
										//cout << "Barcode to be edited exists in original list!" << endl;
										//gets the position
										bpos = f;
										//the boolean variable becomes true since it has been found
										fnd = true;
									}
								}
								//if it has not been found, we display an error message
								if (fnd == false) {
									cout << "Barcode does not exist!" << endl;
								}
								else {
									//else if it has been found(i.e. fnd=true), we do the following:

									//flag to indicate whether the barcode to be edited has been found in the list of items to be edited
									bool hasfound = false;
								
									for (int f = 0; f < 100; f++) {
										//we check if the barcode to be edited exists in the list of items from the receipt
										if (bc_edit == bcodeinput[f]) {
											//cout << "Item exist in the receipt!" << endl;
											// if it has been found, we assign true to the boolean flag hasfound
											hasfound = true;
											//we then remove the barcode from the list of items of the receipt
											bcodeinput[f] = 0;
										}
									}
									//if the barcode has not been found in the list of items in the receipt
									if (hasfound == false) {
										//an error message is displayed
										cout << "Barcode does not exist in the receipt!" << endl;
										cout << endl;//leave a line
									}
									else {
									
										//variable to store the new quantity that the cashier will edit
										int newqty;
										//prompts the cashier to input the desired quantity
										cout << "Enter the new quantity: ";
										//validation if the cashier has input a value which is not of integer data type
										while (!(cin >> newqty)) {
											//tells the cashier to input an integer
											cout << "You must enter an integer number!!" << endl;
											cin.clear();
											cin.ignore(123, '\n');
											cout << endl; //leaves a line
											//prompts the cashier to input the quantity again
											cout << "Enter the new quantity: ";
										}
										//if the cashier enters a negative number
										if ((newqty < 0)) {
											//display an error message
											cout << "Error! Please, enter a valid quantity!" << endl;
										}
										else {
											//variable to store the amount of quantity removed from the previous receipt
											int  removedqty;
											//calculates the amount of items removed from the previous receipt
											removedqty = arrQty[bpos] - newqty;
											//this is to ensure that if the newqty is greater than arrQty at position bpos => converts negative to positive
											if (removedqty < 0) {
												//converts to positive if the removed qty is negative
												removedqty = removedqty * -1;
											}
											//counter to count till the amount of new quantity that the cashier has input
											int countt = 0;
											for (int s = 0; s < 20; s++) {
												//we replace zeros by the barcodes
												//the number of zeros replaced depends on the new quantity amount
												//if the original quantity of an item that a customer has purchased is 4
												//and the cashier has edited the quantity to be 2 then the new quantity =2 and the counter countt must increment till 2 (i.e. the new quantity)
												//therefore we replace two 0s by the barcode of that item
												if (bcodeinput[s] == 0) {
													//if it is a 0, we replace the 0 by the barcode number
													bcodeinput[s] = bcode[bpos];
													//we then increment the counter
													countt++;
													//we then check if the counter is equal to the desired quantity
													if (countt == newqty) {
														break; //we move out of the loop if we have our desired amount
													}
												}
											}

											qtystock[bpos] += removedqty;
											//cout << "Qty in stock " << qtystock[bpos] << endl;
											//cout << endl;

											totalExclVat = 0;
											totalInclVat = 0;
											cout << "_________________________________________________________________________________________________________________" << endl;
											cout << endl;
											//displays "column names" like a tabular format
											cout << setw(15) << "ItemName" << setw(26) << "ItemQty" << setw(25) << "ItemPriceVatExcl" << setw(25) << "ItemPriceVatIncl" << endl;
											cout << endl;
											for (int i = 0; i < 20; i++) {
												//COUNTS THE NUMBER OF OCCURENCES IN OF EACH BARCODE INPUT BY THE CASHIER 
												//THE NUMBER OF OCCURENCES IS EQUAL TO THE QUANTITY OF ITEMS PURCHASED BY THE CUSTOMER
												int x = bcode[i];

												//calculating the item price with vat
												itemPrice_VatIncl = vatptg * sp[i];
												//counting the number of occurences of each item
												itemQty = numOccurences(bcodeinput, 100, x);

												//assigning value of iname at position i to array name at position i
												name[i] = iname[i];
												//assigning value of the item quantity to array arrQty at position i
												arrQty[i] = itemQty;
												//assigning value of sp at position i to array disp_sp at position i
												disp_sp[i] = sp[i];
												if (itemQty != 0) {
													//DISPLAYS THE LIST OF ITEMS PURCHASED BY THE CUSTOMER IN THE FORM OF A RECEIPT
													cout << setw(5) << name[i] << setw(40 - name[i].length()) << itemQty << setw(21) << fixed << setprecision(2) << itemQty * disp_sp[i] << setw(27) << itemQty * itemPrice_VatIncl << endl;
												}
												//calculate total prices.......
												totalExclVat += itemQty * sp[i]; //CALCULATES THE TOTAL PRICE WITHOUT VAT
												totalInclVat += itemQty * itemPrice_VatIncl; //CALCULATES THE TOTAL PRICE WITH VAT
											}
											//calculates the total vat included 
											totalVat = totalInclVat - totalExclVat;
											cout << endl;
											//displays the total prices with and without vat
											cout << "Total Excluding VAT : Rs " << fixed << setprecision(2) << totalExclVat << endl;
											cout << "Total VAT           : Rs " << fixed << setprecision(2) << totalVat << endl;
											cout << "Total Including VAT : Rs " << fixed << setprecision(2) << totalInclVat << endl;
											cout << "Date of Purchase    : " << dd << "/" << mm << "/" << yy << endl;
											cout << "Time of Purchase    : " << time << endl;
											cout << "___________________________________________________________________________________________________________________" << endl;
											cout << endl;
											//----------------------------------------------------------------------------------------------------------------------


										}
									}
								}
							}
							else {
								//if a number <1 or >2 is entered then it displays an error message
								cout << "Invalid choice!" << endl;
							}
						}
						cout << endl;
						//displays the menu
						menu3();
						//validition if the cashier has input a value which is not of integer data type
						//the cashier is asked to input another value again
						while (!(cin >> choice3)) {
							//displays an error message
							cout << "You must enter an integer number!!" << endl;
							cin.clear();
							cin.ignore(123, '\n');
							cout << endl;
							//displays the menu again
							menu3();
						}

					}
				}
				//displays a menu
				menu2();
				//validation if the cashier has entered a data type other than an integer
				while (!(cin >> choice2)) {
					//tells the cashier to input an integer
					cout << "You must enter an integer number!!" << endl;
					cin.clear();
					cin.ignore(123, '\n');
					cout << endl; //leaves a line
					//displays a menu to ask cashier to choose again
					menu2();
				}
			}
			//--------------------------------------------------------CONFIRM PURCHASE-----------------------------------------------------------------------
			cout << endl;
			cout << "___________________________________________________________________________________________________________________" << endl;

			cout << endl;
			//displays the headings/ column names
			cout << setw(15) << "ItemName" << setw(26) << "ItemQty" << setw(25) << "ItemPriceVatExcl" << setw(25) << "ItemPriceVatIncl" << endl;
			cout << endl;
			for (int i = 0; i < 20; i++) {
				//COUNTS THE NUMBER OF OCCURENCES IN OF EACH BARCODE INPUT BY THE CASHIER 
				//THE NUMBER OF OCCURENCES IS EQUAL TO THE QUANTITY OF ITEMS PURCHASED BY THE CUSTOMER

				//the element at position i in the array bcode is assigned to x
				int x = bcode[i];

				//counts the number of occurences and stores it in the variable itemQty
				itemQty = numOccurences(bcodeinput, 100, x);
				//calculates the item price with the vat
				itemPrice_VatIncl = vatptg * sp[i];
				//stores the value of array iname at position i to the array name at position i
				name[i] = iname[i];

				//stores the value of array sp at position i to the array disp_sp at position i
				disp_sp[i] = sp[i];
				if (itemQty != 0) {
					//DISPLAYS THE LIST OF ITEMS PURCHASED BY THE CUSTOMER IN THE FORM OF A RECEIPT
					cout << setw(5) << name[i] << setw(40 - name[i].length()) << itemQty << setw(21) << fixed << setprecision(2) << itemQty * disp_sp[i] << setw(27) << itemQty * itemPrice_VatIncl << endl;
				}
			}
			//displaying the prices and date time details
			cout << endl;
			cout << "Total Excluding VAT : Rs " << fixed << setprecision(2) << totalExclVat << endl;
			cout << "Total VAT           : Rs " << fixed << setprecision(2) << totalVat << endl;
			cout << "Total Including VAT : Rs " << fixed << setprecision(2) << totalInclVat << endl;
			cout << "Date of Purchase    : " << dd << "/" << mm << "/" << yy << endl;
			cout << "Time of Purchase    : " << time << endl;
			cout << endl;
	
			//----------------------------------------------------------------------------------------------------------------

			//this splits the time xx:xx:xx into hours, minutes and seconds after each punctuation, that is, ':'
			//initialises a variable t to store the hours/minutes/seconds in the array
			string t = "";
			//array hhmmsec stores the hours,minutes,seconds at positions 0,1,2 respectively
			string hhmmsec[3];
			//counter which increments if an hour,min or sec is found after a punctuation
			int tcount = 0;
			for (auto x : time)
			{
				//checks if the current character is a punctuation
				if (ispunct(x))
				{
					//cout << t << endl;
					hhmmsec[tcount] = t;//if the character is a punctuation, then it goes in the array at position (tcount value)
					tcount++;
					t = ""; //clears the variable t so that it can store the next values
				}
				else
				{
					//else we continue to add up the characters if we have not found a punctuation
					t = t + x;
				}
			}
			//assigns the value to the array at the position (tcount value)
			hhmmsec[tcount] = t;
			string hour = hhmmsec[0];
			string min = hhmmsec[1];
			string sec = hhmmsec[2];

			string timestamped_file = dd + "_" + to_string(mm) + "_" + yy + "_" + hour + "_" + min + "_" + sec + ".txt";
			ofstream f5(timestamped_file.c_str());
			if (!f5.is_open()) {
				cout << "Error opening file " << timestamped_file << endl;
			}
			else {
				//cout << "file opened successfully!" << endl;
				cout << "Writing to timestamped file..please wait!!" << endl;

				f5 << setw(15) << "ItemName" << setw(26) << "ItemQty" << setw(25) << "ItemPriceVatExcl" << setw(25) << "ItemPriceVatIncl" << endl;

				for (int i = 0; i < 20; i++) {
					//COUNTS THE NUMBER OF OCCURENCES IN OF EACH BARCODE INPUT BY THE CASHIER 
					//THE NUMBER OF OCCURENCES OF AN ITEM IN THE ARRAY IS EQUAL TO THE QUANTITY OF ITEMS PURCHASED BY THE CUSTOMER
					int x = bcode[i];
					itemQty = numOccurences(bcodeinput, 100, x);
					itemPrice_VatIncl = vatptg * sp[i];

					name[i] = iname[i];
					disp_sp[i] = sp[i];

					//WE DO NOT DISPLAY ELEMENTS IN THE ARRAY WHOSE QUANTITIES ARE 0 => THE CUSTOMER AS NOT BOUGHT THOSE ITEMS
					if (itemQty != 0) {
						//WRITES THE LIST OF ITEMS PURCHASED BY THE CUSTOMER IN THE FORM OF A RECEIPT TO THE TIMESTAMPED FILE
						f5 << setw(5) << name[i] << setw(40 - name[i].length()) << itemQty << setw(21) << fixed << setprecision(2) << itemQty * disp_sp[i] << setw(27) << itemQty * itemPrice_VatIncl << endl;
					}
				}

				//WRITES THE PRICES AND DATE /TIME OF PURCHASE TO THE FILE
				f5 << endl;
				f5 << "Total Excluding VAT : Rs " << fixed << setprecision(2) << totalExclVat << endl;
				f5 << "Total VAT           : Rs " << fixed << setprecision(2) << totalVat << endl;
				f5 << "Total Including VAT : Rs " << fixed << setprecision(2) << totalInclVat << endl;
				f5 << "Date of Purchase    : " << dd << "/" << mm << "/" << yy << endl;
				f5 << "Time of Purchase    : " << time << endl;
			}
			//CLOSES THE TIMESTAMPED FILE
			f5.close();

			//----------------------------UPDATING TEXT FILE Stock.txt---------------------------------------------------------------------

			//opens the file stock.txt
			ofstream a("Stock.txt");
			//displays an error message if the file cannot be opened!
			if (!a.is_open()) {
				cout << "Error opening file Stock.txt!" << endl;
				cout << endl;
			}
			else {
				//cout << "File Stock.txt opened successfully!" << endl;
				a << "Barcode" << setw(25) << "ItemName" << setw(25) << "QtyInStock" << setw(25) << "ReOrderLevel" << setw(25) << "BuyingPrice" << setw(25) << "SellingPrice" << setw(20) << "%Vat" << endl;
				for (int x = 0; x < 20; x++) {

					//at the end of the purchase, those items whose quantities in stock is less than the reorder level are displayed to notify the people at the cashier or the people at the supermarket
					if (qtystock[x] < reorderlv[x]) {
						cout << "Reorder item " << iname[x] << endl; 
					}

					//overwrites the existing stock.txt with the new value of qty
					a << setw(5) << bcode[x] << setw(35) << iname[x] << setw(13) << qtystock[x] << setw(25) << reorderlv[x] << fixed << setprecision(2) << setw(25) << bp[x] << setw(24) << sp[x] << setw(25) << vat << endl;
				}
			}
			//closes the file stock.txt
			a.close();

		}
		//---------------------------------------------------STOCK OPERATOR AREA---------------------------------------------------------------------------------------------------------------------
		else {
			if (choice1 == 2) {
				//stock operator
				cout << "Welcome to the Stock Operator Area!" << endl;
				cout << endl;
				
				int ans;
				bool validate = false;
				do {
				
					cout << "For how many items do you wish to store information on? ";
					while (!(cin >> ans)) {
						//displays an error message
						cout << "You must enter a number!!" << endl;
						cin.clear();
						cin.ignore(123, '\n');
						cout << endl; //leaves a line
						//prompts the stock operator to input again
						cout << "For how many items do you wish to store information on? ";
					}
					if (ans > 0) {
						
						validate = true;

						bool valid = false;
						bool vald = false;
						bool isvald = false;
						bool isvalidd = false;

						ofstream f1("Stock.txt");
						f1 << "Barcode" << setw(25) << "ItemName" << setw(25) << "QtyInStock" << setw(25) << "ReOrderLevel" << setw(25) << "BuyingPrice" << setw(25) << "SellingPrice" << setw(20) << "%Vat" << endl;

						for (int i = 0; i < ans; i++) {
							do {
								isvalid = false;

								cout << "Enter the barcode: ";
								while (!(cin >> barcode_S)) {
									//tells the stock operator to input a number
									cout << "You must enter a number!!" << endl;
									cin.clear();
									cin.ignore(123, '\n');
									cout << endl; //leaves a line
									//prompts the stock operator the input again
									cout << "Enter the barcode: ";
								}
								cin.ignore();

								if (to_string(barcode_S).size() == 3) {

									isvalid = true;

									cout << "Enter the item name: ";
									getline(cin, itemName);

									do {

										valid = false;
										cout << "Enter the quantity: ";
										while (!(cin >> qtyInStock)) {
											//tells the stock operator to input a number
											cout << "You must enter a number!!" << endl;
											cin.clear();
											cin.ignore(123, '\n');
											cout << endl; //leaves a line
											//prompts the stock operator the input again
											cout << "Enter the qtyInStock: ";
										}

										if (qtyInStock > 0) {
											valid = true;

											do {
												vald = false;
												cout << "Enter the reorder level: ";
												while (!(cin >> reOrderLvl)) {
													//tells the stock operator to input a number
													cout << "You must enter a number!!" << endl;
													cin.clear();
													cin.ignore(123, '\n');
													cout << endl; //leaves a line
													//prompts the stock operator the input again
													cout << "Enter the reorder level: ";
												}
												if (reOrderLvl > 0) {
													vald = true;

													do {
														isvald = false;

														cout << "Enter the buying price: ";
														while (!(cin >> buyingPrice)) {
															//tells the stock operator to input a number
															cout << "You must enter a number!!" << endl;
															cin.clear();
															cin.ignore(123, '\n');
															cout << endl; //leaves a line
															//prompts the stock operator the input again
															cout << "Enter the buying price: ";
														}
														if (buyingPrice > 0) {
															isvald = true;
															do {

																cout << "Enter the selling price: ";
																while (!(cin >> sellingPrice)) {
																	//tells the stock operator to input a number
																	cout << "You must enter a number!!" << endl;
																	cin.clear();
																	cin.ignore(123, '\n');
																	cout << endl; //leaves a line
																	//prompts the stock operator to input again
																	cout << "Enter the selling price: ";
																}
																if (sellingPrice > 0) {
																	isvalidd = true;

																	//write the item details to the file
																	f1 << setw(5) << barcode_S << setw(35) << itemName << setw(13) << qtyInStock << setw(25) << reOrderLvl << setw(25) << buyingPrice << setw(24) << sellingPrice << setw(25) << pctgVat << endl;
																}
																else {
																	cout << "Please, enter the appropriate amount!" << endl;

																}
															} while (isvalidd == false);
														}
														else {
															cout << "Please enter the appropriate amount!" << endl;
														}
													} while (isvald == false);
												}
												else {
													cout << "Please, enter the appropriate amount!" << endl;
												}
											} while (vald == false);
										}
										else {
											cout << "Please, enter the appropriate amount!" << endl;
											isvalid = false;
										}
									} while (valid == false);
								}
								else {
									cout << endl;
									//displays an error message if the stock operator has entered a barcode which does not contain 3-digits
									cout << "Warning! Barcode must be only 3-digits!" << endl;
									cout << endl;

								}
							
								//while the stock operator has not input the appropriate value, he/she will be stuck in a loop
							} while (isvalid == false);

						}
						//closes file stock.txt
						f1.close();
					}
					else {
						cout << "Please, enter the appropriate amount!" << endl;
					}
				}while (validate == false);
			}
			else {
			//displays an error message
				cout << "Please, enter a valid choice!" << endl;
				cout << endl;
			}
		}
		//leaves a line
		cout << "________________________________________________________________________________________________________________" << endl;
		cout << endl;
		//displaysa a menu
		menu1();
		cout << endl;
		//prompts the user to input a choice 
		cout << "Enter your choice: ";
		//if the stock operator has input a value which is not of integer data type
		while (!(cin >> choice1)) {
			//an error message is displayed 
			cout << "Error! Choice must be an integer!!" << endl;
			//ignores and clears the wrong value
			cin.clear();
			cin.ignore(123, '\n');
			cout << endl;
			//and the stock operator is prompted to input again
			cout << "Enter your choice: ";
		}
	}

	return 0;
}
