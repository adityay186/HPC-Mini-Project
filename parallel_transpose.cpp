#include <iostream> //input output library
#include <chrono> //time calculation library
#include <omp.h> //openMP library

using namespace std;
using namespace std::chrono;

const int SIZE=1000; //defining matrix size of 1000x1000

void transpose(int A[SIZE][SIZE], int tid){ //function to transpose matrix
	int temp;
	for(int i=tid;i<SIZE;i++){
		temp=A[tid][i];
		A[tid][i]=A[i][tid];
		A[i][tid]=temp;
	}
}

void initialiseArray(int A[SIZE][SIZE]){ //function to initialise array
  for(int i=0;i<SIZE;i++)
		for(int j=0;j<SIZE;j++)
			// A[i][j]=(i+1)*SIZE+j;
      A[i][j] = 10;
}

void printArray(int A[SIZE][SIZE]){ //function to print array
  for(int i=0;i<SIZE;i++){
		for(int j=0;j<SIZE;j++)
			cout<<A[i][j]<<" ";
		cout<<endl;
	}
}

int main(){ //main function

  int A[SIZE][SIZE];
  initialiseArray(A);

  cout << "Original Matrix : " << endl;
	printArray(A);

  auto start = high_resolution_clock::now(); //start point in time calculation
	int tid;
	#pragma omp parallel num_threads(SIZE) private(tid)
	{
		tid=omp_get_thread_num();
		transpose(A,tid);
	//	transpose(A,tid);
	}
  auto stop = high_resolution_clock::now(); //stop point in time calculation
  auto duration = duration_cast<microseconds>(stop - start); //difference of stop and start time
  cout<<endl<<endl;
  cout << "Running .... " << endl;
  cout << "Transposed Matrix : " << endl;
	printArray(A);
  cout << endl;
  cout << "Took " << (duration.count()/1000000.0) << " seconds" << endl;
	return 0;
}
