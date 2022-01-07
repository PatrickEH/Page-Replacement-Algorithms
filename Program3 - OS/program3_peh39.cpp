/*
  Patrick Harris
  Program 3 Submission
*/

#include<bits/stdc++.h>
#include<cstdlib>
using namespace std;

//function initializations
int fifo_algorithm(int refString[], int pages, int frames);
int lru_algorithm(int refString[], int pages, int frames);
bool findOPT(int refInd, vector<int> &numFrames);
int getOPT(int refString[], vector<int> &numFrames, int numPages, int algInd);
int opt_algorithm(int refString[], int pages, int frames);


//main
int main()
{
    int SIZE = 100;
    //reference string size of 100 items
    int refString[SIZE];
    for(int i = 0; i < SIZE; i++){
      //virtual page numbers random from 0 to 49
      refString[i] = rand() % 49 + 0;
    }
    int numPages = sizeof(refString)/sizeof(refString[0]);
    //available frames random from 1 to 30
    int numFrames = rand() % 30 +1;

    cout << "Page Reference String: ";
    for(int i = 0; i < SIZE; i++){
      cout << "" << refString[i] << " ";
    }
    cout << "\nNumber of Available Frames: " << numFrames << "\n";

    //displays the algorithms results
    cout << "\nNumber of Page Faults - FIFO: " << fifo_algorithm(refString, numPages, numFrames) << "\n";
    cout << "\nNumber of Page Faults - LRU: " << lru_algorithm(refString, numPages, numFrames) << "\n";
    cout << "\nNumber of Page Faults - OPT: " << opt_algorithm(refString, numPages, numFrames) << "\n";
}

//function declarations
//this function handles the fifo algorithm
int fifo_algorithm(int refString[], int pages, int frames){

  //holds the page we are currently on
  unordered_set<int> nowPages;

  //implements que for fifo_algorithm
  queue<int> fifo;

  int faults = 0;
  for(int x = 0; x < pages; x++){
    //check if set could hold more pages
    if(nowPages.size() < frames){
      //insert page into set if somethings isn't already in there
      if(nowPages.find(refString[x]) == nowPages.end()){
        nowPages.insert(refString[x]);
        faults++;
        fifo.push(refString[x]);
      }
    }
    else{
      //check if page isn't in the set
      if(nowPages.find(refString[x]) == nowPages.end()){
        //remove page in set
        int remove = fifo.front();
        //pop the queue
        fifo.pop();
        nowPages.erase(remove);
        //then insert the new page
        nowPages.insert(refString[x]);
        fifo.push(refString[x]);
        faults++;
      }
    }
  }
  //return total number of faults
  return faults;
}

//this function handles the least recently used algorithm
int lru_algorithm(int refString[], int pages, int frames){
  //holds the page we are currently on
  unordered_set<int> nowPages;

  //stores least used out of the pages
  unordered_map<int, int> algIndex;
  int faults = 0;

  for(int x = 0; x < pages; x++){
    if(nowPages.size() < frames)
    {
      //check if set could hold more pages
      if(nowPages.find(refString[x]) == nowPages.end()){
        //insert if not already in set
        nowPages.insert(refString[x]);
        faults++;
      }
      //store pages index
      algIndex[refString[x]] =x;
    }
    else{
      //check if page isn't in the set
      if (nowPages.find(refString[x]) == nowPages.end()){
        int least = INT_MAX, page;
        for(auto y = nowPages.begin(); y != nowPages.end(); y++){
          //check if index is lower than least
          if(algIndex[*y] < least){
            //if so index = least
            least = algIndex[*y];
            page = *y;
          }
        }
      //remove
      nowPages.erase(page);
      //insert now page
      nowPages.insert(refString[x]);
      faults++;
      }
      //store page indexs
      algIndex[refString[x]] = x;
    }
  }

  //return faults
  return faults;
}

//these functions handle the optimal algorithm
bool findOPT(int refInd, vector<int> &numFrames){
  for(int x = 0; x<numFrames.size();x++){
    //check if frame equal to current index
    if(numFrames[x] == refInd)
    return true;
  }
  //if not return false
  return false;
}
int getOPT(int refString[], vector<int> &numFrames, int pages, int algInd){
  //store indexs
  int front = -1;
  int back = algInd;

  for(int x = 0; x < numFrames.size();x++){
    int y;
    for(y = algInd; y < pages; y++){
      //checks both fram and ref are equal
    if(numFrames[x]==refString[y]){
      if(y > back){
        //if y is greater than the back then proceed
        back = y;
        front = x;
      }
      break;
    }
  }

  if( y == pages)
  return x;
}
//return a if saying if frames not in front return any, otherwise return front
return (front == -1)?0: front;
}
//opt algorithm
int opt_algorithm(int refString[], int pages, int frames){
  //array holding frames
  vector<int> numFrames;
  int hits = 0;
  for(int x = 0; x< pages; x++){
    if(findOPT(refString[x], numFrames)){
      //hit
      hits++;
      continue;
    }
    //check if open and inserts
    if(numFrames.size() < frames){
      numFrames.push_back(refString[x]);
    }
    else{
      //get replacement
      int y = getOPT(refString, numFrames, pages, x+1);
      numFrames[y] = refString[x];
    }
  }

  int faults = pages - hits;
  return faults;
}
