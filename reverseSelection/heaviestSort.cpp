// sorting items from the heaviest to lightest
// by selecting the heaviest item at each time  

#include <iostream>
#include <vector>

using namespace std;

int comparisons = 0;

ostream& operator<<(ostream& os, vector<int>& v)
{
  os << "[";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1)
            os << ", ";
    }
    os << "]\n";
    return os;
}

void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void sort_heaviest(vector<int>& v){
  int n = v.size();
  int heaviest;
  for (int i = n-1; i >= 0; i--){
    heaviest = i;
    for (int j = i-1; j >= 0; j--){
        comparisons++;
      if (v[j] > v[heaviest]){
        heaviest = j;
      }
      swap(&v[heaviest],&v[i]);
    }
  }
  
  
 
}

int main()
{
 
  cout << "//////Test 2 for vector v ///////////////////////////////"<< endl;
  vector<int> v{10,9,8,7,6,5,4,3,2,1};

  cout << "initial vector v:\n";
  cout << v ;
  // use comma to separate the vector's elements
  cout << endl;
  sort_heaviest(v);
  cout << "# of comparisons to sort v: " << comparisons << endl << endl;
  cout << "vector v after sorting:\n";
  cout << v;
  // use comma to separate the vector's elements
  cout << endl;
  
  cout << "//////Test 2 for vector v1 ///////////////////////////////"<< endl;

  vector<int> v1{1,2,3,4,5,6,7,8,9,10};
  comparisons = 0;
  cout << "initial vector v1:\n";
  cout << v ;
  // use comma to separate the vector's elements
  cout << endl;
  sort_heaviest(v);
  cout << "# of comparisons to sort v1: " << comparisons << endl << endl;
  cout << "vector v1 after sorting:\n";
  // use overloaded output operator to display elements of sorted vector
  cout << v ;
  cout << endl;
    
}
