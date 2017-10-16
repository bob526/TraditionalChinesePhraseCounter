#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
//Need C++11 enable.
using namespace std;

const unsigned int ZHTW_CHAR_BYTE=3;

void createDict(ifstream& mydictionary, unordered_map<string, unsigned int>& occurence);
// Pre: mydictionary should open csv file already. occurence should be brandnew
// Post: Initialize occurence with {mydictionary,0}
void articleReader(ifstream& article, unordered_map<string, unsigned int>& occurence);
// Pre: article should open file already. occurence should contain proper items.
// Post: occurence should update
void n_gram(string oneLine, unordered_map<string, unsigned int>& occurence);
// Pre: oneLine should contain something from article. occurence should contain proper items.
// Post: Update occurence
void occurSort(vector< pair<string, unsigned int> >& dictResult, unordered_map<string, unsigned int>& occurence);
//Pre: dictResult should be an empty vector. occurence should contain data after analize the article.
//Post: Update dictResult with phrases "appear" in the article and sort it with occurence number first and then string sort.
bool occurCmp(pair<string, unsigned int>& a, pair<string, unsigned int>& b);
//Post: Make sorting function will sort large first
void dispText(vector< pair<string, unsigned int> >& dictResult);
//Pre: dictResult should sorted already
//Post: Output it on the console.

int main(int argc, char *argv[])
{
    /**
     * First Argument: article_path
     * 
    **/
    if (argc!=2) {
        cout<<"Argument Error\n";
        cout<<"Expected: ./program article_file\n";
        return -1;
    }
    ifstream mydictionary("mydictionary.csv");
    if (!mydictionary.is_open()) {
        cout<<"Cannot open dictionary file.\n";
        return -1;
    }
    ifstream article(argv[1]);
    if (!article.is_open()) {
        cout<<"The article file can't open.\n";
        return -1;
    } 
    string oneLine;
    unordered_map<string, unsigned int> occurence;
    vector< pair<string, unsigned int> > dictResult;

    createDict(mydictionary, occurence);
    articleReader(article, occurence);
    occurSort(dictResult, occurence);
    dispText(dictResult);


    mydictionary.close();
    article.close();
    return 0;
}

void createDict(ifstream& mydictionary, unordered_map<string, unsigned int>& occurence)
{
    pair<string, unsigned int> oneItem;
    string oneLine;
    //Initialize occurence with dictionary
    while(getline(mydictionary,oneLine)) {
        //cout<<oneLine<<endl;
        oneItem = make_pair(oneLine, 0);
        occurence.insert(oneItem);
        //cout<<"Size of the unordered map: "<<occurence.size()<<endl;
        //cin.get();
    }
    //cout<<"Processed OK\n";
    return;
}

void articleReader(ifstream& article, unordered_map<string, unsigned int>& occurence)
{
    string oneLine;

    while(getline(article, oneLine)) {
        //cout<<oneLine<<endl;
        n_gram(oneLine, occurence);
        //cin.get();
    }
}

void n_gram(string oneLine, unordered_map<string, unsigned int>& occurence)
{
    const unsigned int SHORTEST_ZHTW_CHAR=2;
    const unsigned int LONGEST_ZHTW_CHAR=7;
    const unsigned int SHORTEST_ZHTW_PHRASE_BYTE=SHORTEST_ZHTW_CHAR*ZHTW_CHAR_BYTE;
    const unsigned int LONGEST_ZHTW_PHRASE_BYTE=LONGEST_ZHTW_CHAR*ZHTW_CHAR_BYTE;
    const unsigned int ONELINE_LEN=oneLine.length();

    unordered_map<string, unsigned int>::iterator itemIter;

    if (ONELINE_LEN < SHORTEST_ZHTW_PHRASE_BYTE)
        return;
    else {
        //cout<<oneLine<<endl;
        for (int i=0; i<ONELINE_LEN; i+=ZHTW_CHAR_BYTE) {
            //cout<<"OneLine = "<<oneLine<<endl;
            for (int maxLen=LONGEST_ZHTW_CHAR; maxLen>=2; maxLen--) {
                string phrase(oneLine,i,maxLen*ZHTW_CHAR_BYTE);
                //cout<<phrase<<endl;
                //cout<<"i = "<<i<<" len = "<<maxLen<<endl;
                itemIter = occurence.find(phrase);
                if (itemIter!=occurence.end()) {
                    //cout<<phrase<<endl;
                    (*itemIter).second+=1;
                    break;
                    //cin.get();
                }
                //cin.get();
            }
        }
    }
    return;
}

void occurSort(vector< pair<string, unsigned int> >& dictResult, unordered_map<string, unsigned int>& occurence)
{
    unordered_map<string, unsigned int>::iterator travelIterator;

    //Initialize the vector
    for (travelIterator=occurence.begin(); travelIterator!=occurence.end(); ++travelIterator) {
        if (travelIterator->second != 0 ) {
            //cout<<travelIterator->first<<" "<<travelIterator->second<<endl;
            dictResult.push_back(make_pair(travelIterator->first, travelIterator->second));
            //cin.get();
        }
    }
    sort(dictResult.begin(), dictResult.end(), occurCmp);
    return;
}

bool occurCmp(pair<string, unsigned int>& a, pair<string, unsigned int>& b)
{
    //Large will come first
    if (a.second < b.second)
        return false;
    else if (a.second > b.second)
        return true;
    else {
            return (a.first>b.first);
    }
}

void dispText(vector< pair<string, unsigned int> >& dictResult)
{
    for (auto it=dictResult.begin(); it!=dictResult.end(); ++it) {
        cout<<it->first<<" "<<it->second<<endl;
    }
}