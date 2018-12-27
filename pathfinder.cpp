//Rohan J. Dani Project 4 11/20/2017 Professor Gerdes 
#include <cstdlib>
#include "image.h"
#include <iostream>
#include "pathfinder.h"
#include <deque>

struct coordinateData {
	size_t row;
	size_t column;
	bool validReturn;
};


bool isDone(coordinateData coords, Image<Pixel> image) {
	if (coords.column >= image.width() || coords.row >= image.height() 
		|| coords.column == 0 || coords.row == 0) {
		std::cout << "reach limit";
		std::cout << coords.column << "\ncoords column" << image.width() << "\nimagewidth";
		return true;
	}
	return false;
}

void colorprint(Pixel &col_current) {
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
	}
	if (col_current == RED)
	{
		std::cout << "RED";
	}
}

coordinateData checkExplore(coordinateData currentState, Image<Pixel> image) {
	int startWidth = currentState.column;
	int startHeight = currentState.row;
	Pixel col_current = image(startWidth, startHeight);
	Pixel col_down = image(startWidth, startHeight - 1);
	Pixel col_up = image(startWidth, startHeight + 1);
	Pixel col_left = image(startWidth - 1, startHeight);
	Pixel col_right = image(startWidth + 1, startHeight);
	
	/*colorprint(col_current);
	std::cout << "\ndown"; colorprint(col_down);;
	std::cout << "\nup"; colorprint(col_up);;
	std::cout << "\nleft"; colorprint(col_left);;

	std::cout << "\nright"; colorprint(col_right);;
	std::cout << "\nIn Loop" << __LINE__;*/

	if (col_current == WHITE || col_current == RED) {
		if (col_down == WHITE) {
			startHeight--;
			std::cout << "\ncol down" << __LINE__;
		}
		else if (col_up == WHITE) {
			startHeight++;
			std::cout << "\ncol up" << __LINE__;
		}
		else if (col_left == WHITE) {
			startWidth--;
			std::cout << "\ncol left" << __LINE__;
		}
		else if (col_right == WHITE) {
			startWidth++;
			std::cout << "\ncol right" << __LINE__;
		}
		std::cout << "\ncheckExplore ifstatement" << __LINE__;
	}
	//now move the best way based on what is white in front you and keep in mind best Moves maybe
	//follow pseudocode, do it while giving colors a definition 
	currentState.column = startWidth;
	currentState.row = startHeight;
	std::cout << "\n next data: " << startWidth << "," << startHeight << "\n";
	return currentState;
}


coordinateData breadthfirstSearch(int startWidth, int startHeight, Image<Pixel> image) {
	std::deque<coordinateData> frontier;
	std::deque<coordinateData> explored;

	coordinateData currentState;
	coordinateData nextState;
	currentState.column = startWidth;  //set the column to the start Width
	currentState.row = startHeight;  //set the row to the start height 

	explored.push_front(currentState); //for beginning push of current state on red 
	if (image(currentState.column, currentState.row) == RED) {
		image(currentState.column, currentState.row) == BLUE;
	}
	Pixel col_current = image(startWidth, startHeight);
	//std::cout << "current"; 
	//colorprint(col_current); //gives the color of the state
	//std::cout << "\n" << __LINE__ << "   " << startWidth << "," << startHeight << "\n";  //give me the first spot of where it traversered 
	nextState = checkExplore(currentState, image);
	frontier.push_front(nextState);
	currentState = nextState;
	if (image(currentState.column, currentState.row) == RED) {
		image(currentState.column, currentState.row) == BLUE;
	}

	while (true) {
		std::cout << "\ncurrent state : " << currentState.column << ", " 
			<< currentState.row; //gives me current state beg. of while loop
		if (frontier.empty()) { //if it is empty 
			currentState.validReturn = false; //if there is no good return, then give false, this is where it is breaking 
			return currentState;
		}
		
		if (image(currentState.column, currentState.row) == RED) {
			image(currentState.column, currentState.row) == BLUE;
		}

		if (isDone(currentState, image)) { //if complete 
			currentState.validReturn = true;
			image(currentState.column, currentState.row) = GREEN; //then set the pixel to green 
			return currentState;
		}
		else {
			frontier.pop_front();
			explored.push_front(currentState);
			nextState = checkExplore(currentState, image); //next state of struct current data stores the new Width and Height
			if (nextState.column == currentState.column 
				&& nextState.row == currentState.row) {  //if the next state column and row is equal to current state row and column 
				std::cout << "\nInside No choices Part\n";
				currentState = explored.front(); //move current state back to previous state
				continue;
			}
			else {
				frontier.push_front(nextState);
				currentState = nextState;
				image(currentState.column, currentState.row) = BLUE; //otherwise print it as blue 
			}
			std::cout << "pushing new state into frontier"<< currentState.column <<"  " << currentState.row<<"\n"; //print new state that is in frontier 
		}
		
	}
	return currentState;
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
