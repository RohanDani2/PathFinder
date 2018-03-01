//Rohan J. Dani Project 4 11/20/2017 Professor Gerdes 
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "deque.hpp"

// TODO


TEST_CASE("Test Deque push front/pop Front/front", "[DEQUE]") {
		Deque<int> deque; 
		deque.pushFront(1);
		deque.pushFront(3);
		deque.pushFront(5);
		deque.pushFront(15);
		REQUIRE(deque.front() == 15);
		deque.popFront();
		REQUIRE(deque.front() == 5);
		deque.popFront();
		REQUIRE(deque.front() == 3);
		deque.popFront();
		REQUIRE(deque.front() == 1);
		deque.pushFront(15);
		REQUIRE(deque.front() == 15);
		deque.popBack();
		REQUIRE(deque.front() == 15);
		deque.popBack();
		REQUIRE(deque.isEmpty() == true);	
}

TEST_CASE("Test Deque push back/pop back/back", "[DEQUE]") {
	Deque<int> deque;
	deque.pushBack(1);
	deque.pushBack(3);
	deque.pushBack(5);
	deque.pushBack(15);
	REQUIRE(deque.front() == 1);
	deque.popFront();
	REQUIRE(deque.front() == 3);
	deque.popFront();
	REQUIRE(deque.front() == 5);
	deque.popFront();
	REQUIRE(deque.front() == 15);
	deque.pushBack(200);
	REQUIRE(deque.back() == 200);
	deque.popBack();
	REQUIRE(deque.back() == 15);
	deque.popBack();
	REQUIRE(deque.isEmpty() == true);
}

TEST_CASE("Test copy constructor", "[DEQUE]") {
	Deque<int> dequei;
	dequei.pushBack(1);
	dequei.pushBack(3);
	dequei.pushBack(5);
	Deque<int> deque1(dequei);

	REQUIRE(dequei.front() == 1);
	REQUIRE(deque1.front() == 1);
	REQUIRE(dequei.back() == 5);
	REQUIRE(deque1.back() == 5);
	deque1.popFront();
	deque1.popFront();
	deque1.popFront();
	REQUIRE(deque1.isEmpty() == true);
}



