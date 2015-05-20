/* Written by Brandon Wu */

#include "Grid.h"
#include "State.h"
#include "Search.h"
#include "Bfs.h"
#include "Mapf.h"

#include <iostream>
using namespace std;

void testState1();
void testSearch1();
void testSearch2();
void testSearch3();
void testGrid1();
void testMapf1();
void testMapf2();

Point** gen_parr(int* list, int n);


void testBFS() { 

	Grid g("../grids/g2.txt");
	int arr[] = {0,0, 2,3};
	Point* p = (Point*) arr;
	Bfs bfs(p, p+1, &g);
	cout << "BFS cost " << bfs.cost() << endl;
}

int main() {
	//testGrid1();
	//testSearch1();
	//testSearch2();
	//testSearch3();
	testMapf2();
	//testBFS();
	return 0;
}
void testMapf2() {
	/* 8 Agents */
	int init[] = {0,0, 1,0, 2,0, 3,0, 4,0, 19,0, 18,0, 17,0} ;
	int goal[] = {19,5, 18,3, 14,5, 7,5, 3,9, 8,9, 9,9, 15,9};
	//int goal[] = {19,20, 18,20, 14,20, 7,20, 3,20, 8,20, 9,20, 15,20};
	Grid grid("../grids/g2.txt");

	Mapf m(2, (Point*) init, (Point*) goal, &grid);
	Search s(2, (Point*) init, (Point*) goal, &grid);

	cout << "======\nSolving with ID...\n";
	while(m.resolve_conflicts());
	
	cout << "Total cost " << m.num_expansions() << endl;

	cout << "=====\nSolving without ID...\n";
	while(!s.expand());
	s.path(true);
	cout << "Total cost " << s.num_expansions() << endl;
}

void testMapf1() {

	int init[] = {9,0,10,3};
	int goal[] = {5,3,3,1};
	Grid grid("../grids/g1.txt");

	Mapf solver(2, (Point*) init, (Point*) goal, &grid);

	while(solver.resolve_conflicts());
	
	cout << "Total Cost " << solver.num_expansions() << endl;
	
}

void testGrid1() {
	Grid g1("test.txt");
}

void testState1() {
	Point p(1,1);
	State s(&p, 1);
	Move m(NORTH, 0);
	s.display();
	State c(1,s,m);
	c.display();

	cout << sizeof(State) << endl;
}

void testSearch3() {
	int init[] = {9,0,10,3};
	int goal[] = {5,3,3,1};
	Grid g("../grids/g1.txt");
	
	Search s(2, (Point*) init, (Point*) goal, &g);
	while(!s.expand());
}
void testSearch2() {

	Point p(1,0);

	int init[] = {0,0,3,0};
	int goal[] = {3,0,0,0};

	Point* p_ptr = &p;
	Grid g(4,4, &p_ptr, 1);
	
	g.display();

	Search s(2, (Point*)init, (Point*)goal, &g);
	while (!s.expand());

}

void testSearch1() {
	int list [] = {0, 4, 1, 1, 1, 4, 3, 3, 4, 0};
	Point** plist = gen_parr(list, 5);
	for (int i=0; i<4; i++) {
		Point* p = plist[i];
		cout << "(" << p->x << "," << p->y << ")\n";
	}

	Grid g(10,10,plist, 5);
	g.display();

	Point p1(0,0);
	Point g1(4,4);

	Search s(1, &p1, &g1, &g);

	while (!s.expand());
}

Point** gen_parr(int* list, int n) {
	Point** plist = new Point*[n];
	for (int i=0; i<n; i++)
		plist[i] = (Point*) (list+2*i);
	return plist;
}
