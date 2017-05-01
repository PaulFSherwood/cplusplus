#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    vector<int>::const_iterator iter;
    
    cout << "Creating a list of scores.";
    vector<int> scores;
    scores.push_back(1500);
    scores.push_back(3500);
    scores.push_back(7500);
    
    cout << "\nHigh Score:\n";
    for (iter = scores.begin(); iter != scores.end(); ++iter)
    cout << *iter << endl;
    
    cout << "\nRandomizing scores.";
    srand(time(0));
    random_shuffle(scores.begin(), scores.end());
    cout << "\nHigh Scores:\n";
    for (iter = scores.begin(); iter != scores.end(); ++iter)
    cout << *iter << endl;
    
    cout << "\nSorting scores.";
    sort(scores.begin(), scores.end());
    cout << "\nHigh Scores:\n";
    for (iter = scores.begin(); iter != scores.end(); ++iter)
    cout << *iter << endl;
    
    cout << "\nCreating another list of scores." ;
    vector<int> moreScores;
    moreScores.push_back(2000);
    moreScores.push_back(4000);
    moreScores.push_back(8000);
    
    cout << "\nMore High Score:\n";
    for (iter = moreScores.begin(); iter != moreScores.end(); ++iter)
    cout << *iter << endl;
    
    cout << "\nMergin both lists.";
    vector<int> allScores(6);  // need container big enough to hold results
    merge(scores.begin(), scores.end(),
    moreScores.begin(), moreScores.end(),
    allScores.begin());
    
    cout << "\nAll High Scores:\n";
    for (iter = allScores.begin(); iter != allScores.end(); ++iter)
    cout << *iter << endl;
    
    return 0;
}
