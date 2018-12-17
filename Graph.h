#pragma once
#include<string>
#include<iostream>
#include<list>

class Node {
public:
	std::string name;	 
	std::string getName();
	void setName(std::string);
	Node();
	Node(std::string);
	~Node();
};

class Line {
public:
	Node node1;
	Node node2;
	Line(Node, Node);
	Line();
	~Line();
	Node getNode1();
	Node getNode2();
};

class Graph {
public:
	std::string graphName;
	std::list<Node> nodeList;
	std::list<Line> lineList;
	void addNode(Node);
	void addLine(Line);
	void setName(std::string);
	std::string getName();
	void getGraphCode();
	Graph();
	~Graph();
	int findMaxTree();
	std::string countFundGroup();
};

std::ostream& operator<< (std::ostream&, const Node&);
std::ostream& operator<< (std::ostream&, const Line&);
bool operator== (const Node, const Node);