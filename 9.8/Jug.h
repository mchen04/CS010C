#ifndef JUG_H
#define JUG_H

#include <list>
#include <string>
#include <vector>

using namespace std ;

class Vertex {
  public:
    string key;
    list<pair<int, int>> neighbors;
    Vertex(std::string key) : key(key) {}
};

class Jug {
  private:
    int Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA;
    vector<Vertex> graph;
  public:
    Jug(int, int, int, int, int, int, int, int, int);
    int solve(string&);
  private:
    bool isValidInputs() const;
    bool isCorrectAmount(list<pair<int, int>>);
    int processString(vector<int>&, string&) const;
    int processTotalCost(vector<int> steps);
    vector<int> attempt();
    int doStep(int&, int&, const int&);
    vector<int> traverse(int, vector<int>, list<pair<int, int>>);
    bool checkIfCycled(int, int, list<pair<int, int>>);
};

#endif
