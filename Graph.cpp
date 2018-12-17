#include "pch.h"
#include "Graph.h"
#include <string>
#include <fstream>
#include <ostream>
#include <iostream>
#include <vector>

std::ostream& operator<< (std::ostream &stream, const Node &a) {
	stream << a.name;
	return stream;
};

std::ostream& operator<< (std::ostream &stream, const Line &a) {
	stream << a.node1 << " -> " << a.node2 << ";";
	return stream;
};

bool operator== (const Node a, const Node b) {
	if (a.name == b.name) {
		return true;
	}
	else { return false; }
}

std::string Node::getName() {
	return Node::name;
};

void Node::setName(std::string nameM) {
	Node::name = nameM;
};

Node Line::getNode1() {
	return this->node1;
};

Node Line::getNode2() {
	return this->node2;
};

Node::Node(std::string nameM) {
	name = nameM;
};

Line::Line(Node nodeM1, Node nodeM2) {
	node1 = nodeM1;
	node2 = nodeM2;
};

Node::Node() {};

Line::Line() {};

Node::~Node() {};

Line::~Line() {};

Graph::Graph() {};

Graph::~Graph() {};

std::string Graph::getName() {
	return graphName;
};

void Graph::setName(std::string nameM) {
	graphName = nameM;
};

void Graph::addNode(Node a) {
	nodeList.push_back(a);
}

void Graph::addLine(Line a) {
	lineList.push_back(a);
}

void Graph::getGraphCode() {
	std::fstream codeFile;
//	const char path = "/results/GraphCode.txt";
	std::string fileName;
	fileName.append(graphName);
	fileName.append(".txt");
	codeFile.open(fileName, std::fstream::out);
	codeFile << "digraph " << graphName << "{" << std::endl;
	for (std::list<Line>::iterator i = lineList.begin(); i != lineList.end(); ++i)
	{
		codeFile << *i << std::endl;
	}
	codeFile << "}" << std::endl;
	codeFile << "//Fundamental group: " << countFundGroup << std::endl;
	codeFile << "//Number of cycles: " << findMaxTree << std::endl;
	codeFile.close();
}

int Graph::findMaxTree() {
	int cycleNumber = 0;
	std::vector<Line> lineVector(lineList.begin(), lineList.end());
	for (int i = 0; i < lineVector.size(); i++) {
		if (lineVector[i].getNode1() == lineVector[i].getNode2()) {
			cycleNumber += 1;
		}
		else
		{
			for (int j = i+1; j < lineVector.size(); j++) {
				if (lineVector[j].getNode1() == lineVector[i].getNode2() && lineVector[i].getNode1() == lineVector[j].getNode2()) { cycleNumber += 1; }
				else
				{ 
					for (int k = j+1; k < lineVector.size(); k++) {
						if (lineVector[k].getNode1() == lineVector[j].getNode2() && lineVector[k].getNode2() == lineVector[i].getNode1()) {
							cycleNumber += 1;
						}
						else
						{
							for (int l =  k+1; l < lineVector.size(); l++) {
								if (lineVector[l].getNode1() == lineVector[k].getNode2() && lineVector[l].getNode2() == lineVector[i].getNode1()) {
									cycleNumber += 1;
								}
								else
								{
									for (int m = l+1; m < lineVector.size(); m++) {
										if (lineVector[m].getNode1() == lineVector[l].getNode2() && lineVector[m].getNode2() == lineVector[i].getNode1()) {
											cycleNumber += 1;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return cycleNumber;
};

std::string Graph::countFundGroup() {
	std::string fg = "";
	if (this->findMaxTree() != 0) {
		for (int i = 0; i < this->findMaxTree(); i++) {
			fg.append("Z*");
		}
		return fg.substr(0, fg.size() - 1);
	}
	else
	{
		return "0";
	}
};