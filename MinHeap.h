#include <iostream>
#include <vector>
#include <utility>
#include <string>

template <typename T>
  class MinHeap {
    public:
      MinHeap (int d);
       /* Constructor that builds a d-ary Min Heap
          This should work for any d >= 2,
          but doesn't have to do anything for smaller d.*/

      ~MinHeap ();

      void add (T item, int priority);
         /* adds the item to the heap, with the given priority. */

      const T & peek () const;
         /* returns the element with smallest priority.  
			Break ties however you wish.  
			Throws an exception if the heap is empty. */

      void remove ();
         /* removes the element with smallest priority.
			Break ties however you wish.
            Throws an exception if the heap is empty. */

      bool isEmpty () const;
         /* returns true iff there are no elements on the heap. */
      
      void getContents();

   private:
      int d_;
      //storage for heap organization to priority
      std::vector<std::pair<int, T>> nodePriorityList_;
      // //storage of priority to item
      // std::vector<T> priorityItemList_;
      // You may also add helper functions here.
      void bubbleUp(int pos);
      void bubbleDown(int pos);
  };


  template<typename T> MinHeap<T>::MinHeap(int d){
    //initializes arrays to empty (-1)
    //only if d>=2
    //do i need to initialize a specific number of nodes
    if(d>=2){
        d_=d;
    } 
    else{
      throw "d is not valid ";
    }
  }
  template<class T> MinHeap<T>::~MinHeap(){

  }

  template<typename T> void MinHeap<T>::add(T item, int priority){
    nodePriorityList_.push_back(std::make_pair(priority, item));
    //std::cout<<nodePriorityList_.back().first<<std::endl;
    //std::cout<<nodePriorityList_.size()<<" size"<<std::endl;
    bubbleUp(nodePriorityList_.size()-1);
  }

  template<typename T> const T &MinHeap<T>::peek() const{
    if(isEmpty()){
      throw "heap is empty, can not get min";
    }
    return nodePriorityList_.front().second;   //first=priorirty or second= item
  }

  template<typename T> void MinHeap<T>::remove(){
    if(isEmpty()){
      throw "heap is empty, can not remove";
    }
    if(nodePriorityList_.size()==1){
      nodePriorityList_.clear();
      return;
    }
    nodePriorityList_[0]=nodePriorityList_.back();
    nodePriorityList_.pop_back();
    bubbleDown(0);
  }
  template<typename T> bool MinHeap<T>::isEmpty() const{
    if(nodePriorityList_.size()<=0){
      return true;
    }
    return false;
  }

  //bubble up for acrost rows as well
  template<typename T> void MinHeap<T>::bubbleUp(int pos){
    //std::cout << "UP " << std::endl;
    if(isEmpty()){
      throw "heap is empty, can not bubbleup";
    }
    if(nodePriorityList_.size()==1){
      return;
    }
    int parentInd=int((pos-1)/d_);
    //changed to < rather than <= in edits from -10
    if(pos>0 && nodePriorityList_[pos].first==nodePriorityList_[parentInd].first){
      if(nodePriorityList_[pos].second < nodePriorityList_[parentInd].second){
        std::pair<int, T> temp = nodePriorityList_[pos];
        nodePriorityList_[pos]= nodePriorityList_[parentInd];
        nodePriorityList_[parentInd]= temp;
        bubbleUp(parentInd); //using newpos
      }
    }
    if(pos>0 && (nodePriorityList_[pos].first<nodePriorityList_[parentInd].first)){ //a[] parent node
      std::pair<int, T> temp = nodePriorityList_[pos];
      nodePriorityList_[pos]= nodePriorityList_[parentInd];
      nodePriorityList_[parentInd]= temp;
      bubbleUp(parentInd); //using newpos
    }
  }
  //forgetting ascending left to right
  template<typename T> void MinHeap<T>::bubbleDown(int pos){
    //std::cout << "DOWN " << std::endl;
    if(isEmpty()){
      throw "heap is empty, can not bubbledown";
    }
    if(nodePriorityList_.size()==1){
      return;
    }
    long unsigned int minChild = d_*pos+1; //first child index
    long unsigned int dComp=d_;
    if(minChild<nodePriorityList_.size()){
      for(long unsigned int child = dComp*pos + 1; child <= dComp*pos + dComp; child++){
        if (child == nodePriorityList_.size()) break;

        if (nodePriorityList_[child].first < nodePriorityList_[minChild].first) {
          minChild = child;
          std::pair<int, T> temp = nodePriorityList_[child];
          nodePriorityList_[child]= nodePriorityList_[minChild];
          nodePriorityList_[minChild]= temp;
        }
        if((nodePriorityList_[child].first == nodePriorityList_[minChild].first)&&(nodePriorityList_[child].second < nodePriorityList_[minChild].second)){
          minChild=child;
          std::pair<int, T> temp = nodePriorityList_[child];
          nodePriorityList_[child]= nodePriorityList_[minChild];
          nodePriorityList_[minChild]= temp;
        }
      } 
      if(nodePriorityList_[minChild].first==nodePriorityList_[pos].first){
        if(nodePriorityList_[pos].second > nodePriorityList_[minChild].second){
          std::pair<int, T> temp = nodePriorityList_[pos];
          nodePriorityList_[pos]= nodePriorityList_[minChild];
          nodePriorityList_[minChild]= temp;
          bubbleDown(minChild);
        }
      }
      if(nodePriorityList_[minChild].first<nodePriorityList_[pos].first){
        std::pair<int, T> temp = nodePriorityList_[pos];
        nodePriorityList_[pos]= nodePriorityList_[minChild];
        nodePriorityList_[minChild]= temp;
        bubbleDown(minChild);
      }
    }
  }

    template<typename T> void MinHeap<T>::getContents(){
    std::string list;
    for(std::pair<int, T> item: nodePriorityList_) {
        std::cout<<item.first<<": "<<item.second<<", ";
    }
    std::cout<<std::endl;
    }


