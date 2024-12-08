#include <iostream>
#include "MinHeap.h"
#include <fstream>
#include <set>
#include <map>
#include <string>
using namespace std;

int countDif(string a, string b);
void makeLowercase(string &word);

int main(int argc, char* argv[]){
  string startWord, endWord;
  startWord= argv[1];
  endWord=argv[2];
  makeLowercase(startWord);
  makeLowercase(endWord);
  ifstream ifile(argv[3]);
  if(!ifile){
      cout<<"error reading file"<<endl;
  }
  int wordCount; 
  string currWord;
  set <string> wordList;
  ifile>>wordCount;  
  for(int i=0;i<wordCount;i++){
    ifile>>currWord;
    makeLowercase(currWord);
    wordList.insert(currWord);
  }
  map <string, vector<string>> match;
  for (auto word: wordList) {
    for (int i = 0; i < int(word.size()); i++) {
      string temp = word;
      temp[i] = '*';
      match[temp].push_back(word);
    }
  }
  map <string,vector<string>> graph; 
  for (auto word: wordList) {
    set<string> neighbours;
    for (int i = 0; i < int(word.size()); i++) {
      string temp = word;
      temp[i] = '*';
      for (auto n: match[temp]) {
        if (n != word) {
          neighbours.insert(n);
        }
      }
    }
    graph[word] = vector<string>(neighbours.begin(), neighbours.end());
  }
    
  // for (auto a : graph) {
  //   cout << a.first << ": ";
  //   for (auto b: graph[a.first]) {
  //     cout << b << ", ";
  //   }
  //   cout << endl;
  // }
  MinHeap<string> storageHeap(startWord.size());
  storageHeap.add(startWord, 0);
  set <string> visited;
  map<string,int> gValues;
  set <string> inHeap;
  for(auto word :wordList){
    gValues[word]=0;
  }
  while(!storageHeap.isEmpty()&& /*(visited.size()!=wordCount) &&*/ (wordList.find(endWord)!=wordList.end())){
    string curr = storageHeap.peek();
    if(visited.find(curr)!=visited.end()){
      storageHeap.remove();
      continue;
    }
    makeLowercase(curr);
    // cout << "CURRENT WORD: " << curr << endl;
    storageHeap.remove();
    if(curr==endWord){
      // cout << "FOUND WORD"<<endl;
      // cout << "VISITED: ";
      // for(auto a: visited){
      //   cout<<a<<", ";
      // }
      // cout<<endl;
      cout<<gValues[endWord]<<endl;
      cout<<visited.size()<<endl;
      return 1;
    } 
    if(visited.find(curr)==visited.end()){
      // cout<<curr<<" not visited yet"<<endl;
      visited.insert(curr);
    }
    for(int i =0; i<int(graph[curr].size());i++){
      string neighbor = graph[curr][i];
      makeLowercase(neighbor);
      if(gValues[neighbor]==0||((gValues[neighbor]>(gValues[curr]+1)))){
        int h = countDif(neighbor,endWord);
        // priority =  f*(n+1)+h
        int priority = (curr.size() + 1) *(gValues[curr]+1+h)+h;
        gValues[neighbor]=gValues[curr]+1;
        storageHeap.add(neighbor,priority);
        // cout<<"added "<<neighbor<< " h "<<h<<" g "<<gValues[neighbor]<<" priority "<<priority<<endl;
        inHeap.insert(neighbor);
      }
    }
    // cout<<"HEAP CONTENTS: ";
    // storageHeap.getContents();
  }
  cout<<"No transformation"<<endl;
  cout << visited.size() << endl;
  return 0;
}

int countDif(string a, string b){
    int dif=0 ;
    for(int i=0; i<int(a.size());i++){
      if (a[i]!= b[i]){
        dif++;
      }
    }
  return dif;
}

void makeLowercase(string &word){
  string temp;
  int character;
  for(long unsigned int i=0; i<word.size();i++){
    character= word[i];
    character=tolower(character);
    temp.push_back(character);
  }
  word=temp;
}