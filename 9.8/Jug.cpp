#include "Jug.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std ;

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) :
    Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA)
{
    Vertex cfA_v("cfA");
    Vertex cfB_v("cfB");
    Vertex ceA_v("ceA");
    Vertex ceB_v("ceB");
    Vertex cpAB_v("cpAB");
    Vertex cpBA_v("cpBA");

    cfA_v.neighbors.push_back(pair<int, int>(1, cfB));
    cfA_v.neighbors.push_back(pair<int, int>(4, cpAB));

    cfB_v.neighbors.push_back(pair<int, int>(0, cfA));
    cfB_v.neighbors.push_back(pair<int, int>(5, cpBA));

    ceA_v.neighbors.push_back(pair<int, int>(1, cfB));
    ceA_v.neighbors.push_back(pair<int, int>(3, ceB));
    ceA_v.neighbors.push_back(pair<int, int>(5, cpBA));

    ceB_v.neighbors.push_back(pair<int, int>(0, cfA));
    ceB_v.neighbors.push_back(pair<int, int>(2, ceA));
    ceB_v.neighbors.push_back(pair<int, int>(4, cpAB));

    cpAB_v.neighbors.push_back(pair<int, int>(0, cfA));
    cpAB_v.neighbors.push_back(pair<int, int>(3, ceB));
    cpAB_v.neighbors.push_back(pair<int, int>(5, cpBA));

    cpBA_v.neighbors.push_back(pair<int, int>(0, cfA));
    cpBA_v.neighbors.push_back(pair<int, int>(1, cfB));
    cpBA_v.neighbors.push_back(pair<int, int>(2, ceA));
    cpBA_v.neighbors.push_back(pair<int, int>(3, ceB));
    cpBA_v.neighbors.push_back(pair<int, int>(4, cpAB));

    graph.push_back(cfA_v);  
    graph.push_back(cfB_v);  
    graph.push_back(ceA_v);  
    graph.push_back(ceB_v);  
    graph.push_back(cpAB_v);
    graph.push_back(cpBA_v); 
}

int Jug::solve(string& solution)
{
    if (!isValidInputs())
    {
        solution.clear();
        return -1;
    }

    vector<int> steps = attempt();
    if (steps.empty())
    {
        solution.clear();
        return 0;
    }

    processString(steps, solution);
    return 1;
}


bool Jug::isValidInputs() const
{
    return (N >= 0 && cfA >= 0 && cfB >= 0 && ceA >= 0 && ceB >= 0 && cpAB >= 0 && cpBA >= 0)
        && (Ca > 0 && Ca <= Cb) && (N <= Cb && Cb <= 1000);
}

bool Jug::isCorrectAmount(list<pair<int, int>> route)
{
    return route.back().first == 0 && route.back().second == N;
}

int Jug::processString(vector<int>& steps, string& solution) const
{
    ostringstream outSS;
    int totalCost = 0;

    for (unsigned i = 0; i < steps.size(); ++i)
    {
        if (steps.at(i) == 0)
        {
            totalCost += cfA;
            outSS << "fill A" << endl;
        }
        else if (steps.at(i) == 1)
        {
            totalCost += cfB;
            outSS << "fill B" << endl;
        }
        else if (steps.at(i) == 2)
        {
            totalCost += ceA;
            outSS << "empty A" << endl;
        }
        else if (steps.at(i) == 3)
        {
            totalCost += ceB;
            outSS << "empty B" << endl;
        }
        else if (steps.at(i) == 4)
        {
            totalCost += cpAB;
            outSS << "pour A B" << endl;
        }
        else if (steps.at(i) == 5)
        {
            totalCost += cpBA;
            outSS << "pour B A" << endl;
        }
    }

    outSS << "success " << totalCost;
    solution = outSS.str();

    return totalCost;
}

int Jug::processTotalCost(vector<int> steps)
{
    int totalCost = 0;

    int stepCosts[] = {cfA, cfB, ceA, ceB, cpAB, cpBA};

    for (unsigned i = 0; i < steps.size(); ++i)
    {
        int step = steps.at(i);
        if (step >= 0 && step < 6)
        {
            totalCost += stepCosts[step];
        }
    }

    return totalCost;
}


std::vector<int> Jug::attempt()
{
    list<pair<int, int>> route;
    vector<int> aSteps, bSteps;

    route.push_back(std::make_pair(0, 0));
    aSteps = traverse(0, aSteps, route);
    bSteps = traverse(1, bSteps, route);

    if (aSteps.empty())
    {
        return bSteps;
    }
    else if (bSteps.empty())
    {
        return aSteps;
    }

    return processTotalCost(aSteps) < processTotalCost(bSteps) ? aSteps : bSteps;
}


int Jug::doStep(int& aAmount, int& bAmount, const int& stepIndex)
{
    const auto& key = graph.at(stepIndex).key;

    if (key == "cfA")
    {
        aAmount = Ca;
    }
    else if (key == "cfB")
    {
        bAmount = Cb;
    }
    else if (key == "ceA")
    {
        aAmount = 0;
    }
    else if (key == "ceB")
    {
        bAmount = 0;
    }
    else if (key == "cpAB")
    {
        const int space = Cb - bAmount;
        const int transfer = min(space, aAmount);
        bAmount += transfer;
        aAmount -= transfer;
    }
    else if (key == "cpBA")
    {
        const int space = Ca - aAmount;
        const int transfer = min(space, bAmount);
        aAmount += transfer;
        bAmount -= transfer;
    }

    return stepIndex;
}


std::vector<int> Jug::traverse(int stepIndex, std::vector<int> steps, std::list<std::pair<int, int>> route)
{
    std::vector<int> vect;
    std::vector<int> vectAlt;

    int aAmount;
    int bAmount;
    int stepTaken;

    if (isCorrectAmount(route))
    {
        return steps;
    }
    
    auto it = graph.at(stepIndex).neighbors.begin();

    while (it != graph.at(stepIndex).neighbors.end()) 
    {
        aAmount = route.back().first;
        bAmount = route.back().second;
        stepTaken = doStep(aAmount, bAmount, it->first);

        if (!checkIfCycled(aAmount, bAmount, route))
        {
            steps.push_back(stepTaken);
            route.push_back(std::pair<int, int>(aAmount, bAmount));
            
            if (vect.size() == 0)
            {
                vect = traverse(stepTaken, steps, route);
            }
            else
            {
                vectAlt = traverse(stepTaken, steps, route);
                if (processTotalCost(vect) > processTotalCost(vectAlt))
                {
                    vect = vectAlt;
                }
            }

            steps.pop_back();
            route.pop_back();
        }

        it++;
    }

    return vect;
}

bool Jug::checkIfCycled(int aAmount, int bAmount, std::list<std::pair<int, int>> route)
{
    auto it = route.begin();

    while (it != route.end())
    {
        if (it->first == aAmount && it->second == bAmount)
        {
            return true;
        }

        it++;
    }

    return false;
}
