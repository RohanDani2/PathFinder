//Rohan J. Dani Project 4 11/20/2017 Professor Gerdes 
#include <cstdlib>
#include "deque.hpp"
#include "image.h"
#include <iostream>
#include "pathfinder.h"

struct coordinateData {
	size_t row;
	size_t column;
	bool validReturn;
};


bool isDone(coordinateData coords, Image<Pixel> image) {
	if (coords.column >= image.width() || coords.row >= image.height() || coords.column == 0 || coords.row == 0) {
		std::cout << "reach limit";
		return true;
	}
	return false;
}

void colorprint(Pixel &col_current, int &retflag) {
	retflag = 1;
	if (col_current == BLACK)
	{
		std::cout << "BLACK";
	}
	if (col_current == WHITE)
	{
		std::cout << "WHITE";
	}
	if (col_current == GREEN)
	{
		std::cout << "GREEN";
	}
	if (col_current == BLUE)
	{
		std::cout << "BLUE";
		{ retflag = 2; return; };
	}
	if (col_current == RED)
	{
		std::cout << "RED";
	}
}

coordinateData checkExplore(coordinateData currentState,  Image<Pixel> image) {
	int startWidth = currentState.column;
	int startHeight = currentState.row;
	coordinateData nexData;
	//nexData.row = -1;
	//nexData.column = -1;
	while (true) {
		Pixel col_current = image(startWidth, startHeight);
		Pixel col_down = image(startWidth, startHeight - 1);
		Pixel col_up = image(startWidth, startHeight + 1);
		Pixel col_left = image(startWidth - 1, startHeight);
		Pixel col_right = image(startWidth + 1, startHeight);
		int retflag;
		colorprint(col_current, retflag);
		if (retflag == 2) {
			break;
		}

		std::cout << "\ndown"; colorprint(col_down, retflag);;
		std::cout << "\nup"; colorprint(col_up, retflag);;
		std::cout << "\nleft"; colorprint(col_left, retflag);;

		std::cout << "\nright"; colorprint(col_right, retflag);;
		std::cout << "\nIn Loop" << __LINE__;
		
		if (col_current == BLACK || col_current == WHITE || col_current == RED) {

			if (col_down == WHITE) {
				startHeight--;
				break;
			}
			std::cout << "\nIn Loop" << __LINE__;
			if (col_up == WHITE ) {
				startHeight++;
				break;
			}
			std::cout << "\nIn Loop" << __LINE__;

			if (col_left == WHITE ) {
				startWidth--;
				break;
			}
			std::cout << "\nIn Loop" << __LINE__;

			if (col_right == WHITE) {
				startWidth++;
				break;
			}
			std::cout << "\nIn Loop" << __LINE__;
		
			if (col_down == BLUE) {
				startHeight--;
				break;
			}
			std::cout << "\nIn Loop" << __LINE__;
			if (col_up == BLUE) {
				startHeight++;
				break;
			}
			std::cout << "\nIn Loop" << __LINE__;

			if (col_left == BLUE) {
				startWidth--;
				break;
			}
			std::cout << "\nIn Loop" << __LINE__;
			if (col_right == BLUE) {
				startWidth++;
				break;
			}
	
			std::cout << "\nIn Loop" << __LINE__;
			
		}

    //now move the best way based on what is white in front you and keep in mind best Moves maybe
	//follow pseudocode, do it while giving colors a definition 
	}
	nexData.column = startWidth;
	nexData.row = startHeight;
	std::cout <<"\n next data: "<< startWidth << "," << startHeight << "\n";
	return nexData;
}


coordinateData breadthfirstSearch(int startWidth, int startHeight, Image<Pixel> image) {
	Deque<coordinateData> frontier;
	Deque<coordinateData> explored;

	coordinateData currentState;
	coordinateData NextState;
	currentState.column = startWidth;  //set the column to the start Width
	currentState.row = startHeight;  //set the row to the start height 


	frontier.pushFront(currentState); //for beginning push of current state on red 

	std::cout << "\n" << __LINE__ << "   " << startWidth << "," << startHeight << "\n";  //give me the first spot of where it is traversered 
	while (true) {
		if (frontier.isEmpty()) { //if it is empty 
			currentState.validReturn = false; //if there is no good return, then give false, this is where it is breaking 
			return currentState;
		}
	
		std::cout << "\ncurrent state : "<< currentState.column<<", " << currentState.row; //gives me current state beg. of while loop 
		explored.pushFront(currentState); //pushing the current state that is explored
		
		//check red
		if (image(currentState.column, currentState.row) == RED) { //RED a second time 
			image(currentState.column, currentState.row) == BLUE;
		}

		if (isDone(currentState, image)) { //if complete 
			currentState.validReturn = true;
			image(currentState.column, currentState.row) = GREEN; //then set the pixel to green 
			return currentState;
		}
		else {
			NextState = checkExplore(currentState, image); //next state of struct current data stores the new Width and Height based off current state 
			
			if (NextState.column == currentState.column && NextState.row == currentState.row) {  //if the next state column and row is equal to current state row and column 
				std::cout << "\nPop out\n";
				currentState = frontier.front(); //then front the item 
				if (image(currentState.column, currentState.row) == RED) { //RED a second time 
					image(currentState.column, currentState.row) == BLUE;
					NextState = checkExplore(currentState, image);
					currentState = NextState;
					frontier.pushBack(currentState);
				}
				frontier.popFront(); //and remove it 
			}
			else {
				image(currentState.column, currentState.row) = BLUE; //otherwise print it as blue 
				std::cout << "\nPush out\n";
				std::cout << "\npushing NextState state into frontier" << NextState.column << "  " << NextState.row << "\n"; //then print the new column and row that has been explored 
				frontier.pushFront(currentState); //then pushfront the current state that needs to be explored 
				currentState = NextState; //and set current state to next state that is explored 
			}
			std::cout << "pushing new state into frontier"<< currentState.column <<"  " << currentState.row<<"\n"; //print new state that is in frontier 
		}
		
	}
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cerr << "Error: invalid number of arguments\n\n";
		return EXIT_FAILURE;
	}
	Image<Pixel> inputImage;
	try {
		inputImage = readFromFile(argv[1]);
	}
	catch(std::runtime_error){
		std::cerr << "Error: didn't read file";
		return EXIT_FAILURE;
	}
	int startWidth = -1;
	int startHeight = -1; //to check how many red dots, setting negative to start off
	for (size_t i = 0; i < inputImage.width(); ++i) {
		for (size_t j = 0; j < inputImage.height(); ++j) {
			if (inputImage(i, j) == RED) {

				if (startWidth >= 0 || startHeight >= 0) { //more than 1 red dot
					std::cerr << "Error: the input maze has more than one red pixel\n\n";
					return EXIT_FAILURE;
				}
				startWidth = i;
				startHeight = j;
			}
		}
	}
	if (startWidth == -1 || startHeight == -1) {
		std::cerr << "Error: no red pixels\n\n";
		return EXIT_FAILURE;
	}

	coordinateData endResult = breadthfirstSearch(startWidth,startHeight,inputImage);

	if (endResult.validReturn == false) {
		std::cerr << "Error: didn't work\n\n";
		return EXIT_FAILURE;
	}
	inputImage(endResult.column, endResult.row) = GREEN;
	std::cout << "Solution Found\n";
	try {
		writeToFile(inputImage, argv[2]);
	}
	catch (std::runtime_error) {
		std::cerr << "Error: didn't write file";
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
