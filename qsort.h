#include <vector>
#include <iostream>
#include <math.h>


template <class T, class Comparator>
  void qsort(std::vector<T> &myArray, int start, int end, Comparator comp);

template <class T, class Comparator>
  int partition(std::vector<T> &myArray, int start, int end, Comparator comp);

template <class T, class Comparator>
  void QuickSort (std::vector<T> &myArray, Comparator comp)
  {
  		int size = myArray.size();
  		qsort(myArray, 0, size, comp);

  }






template <class T, class Comparator>
  void qsort(std::vector<T> &myArray, int start, int end, Comparator comp)
  {
  		//do not need to check if an array is of size zero because it wont satisfy any of the if
  		//statements below

      if (myArray.size()==1) // base case 1, if the array is only of size one, it is already sorted
      {
        return;
      }
  		if (myArray.size() == 2)// base case,if an array is of size two, check if it is already sorted, if it isn't, make a swap
  		{
  			if (comp(myArray[0], myArray[1]) == false)
  				{
  				T temp = myArray[0];
  				myArray[0]= myArray[1];
  				myArray[1] = temp;}
  				return;
  		}

  		if (start<end)

  		{
  		  			int p = partition(myArray, start, end, comp);
  		
  		  			qsort(myArray, start, p, comp);//quicksort on first half of array
  		
  		  			qsort(myArray, p+1, end, comp);//quicksort on second half of the array
  		  		}


  }

 template <class T, class Comparator>
  int partition(std::vector<T> &myArray, int start, int end, Comparator comp)
  {
  		int mid = floor((end-1-start)/2) + start; // get the middle element of the array, rounding down
  	   
  		//the following if statements are a series of swaps that minimize the number of comparisons that
  		//have to be made

  		if ((comp(myArray[end-1], myArray[start])))//if the last element compared to the first element is true, switch them 
  		{
  				T temp = myArray[start];
  				myArray[start]= myArray[end-1];
  				myArray[end-1] = temp;


  		}

  		if ((comp(myArray[mid], myArray[start]))) // if the middle element compared ot the first element is true, swwitch them
  		{
  			
  				T temp = myArray[mid];
  				myArray[mid]= myArray[start];
  				myArray[start] = temp;
  		}

  		if ((comp(myArray[end-1], myArray[mid]))) // if the last element compared to the first element is true, switch them
  		{
  			
  				T temp = myArray[end-1];
  				myArray[end-1]= myArray[mid];
  				myArray[mid] = temp;
  		}

  //move the final median element, which has been moved to the middle index, to the last index of the array		

      T temper = myArray[mid];
          myArray[mid]= myArray[end-1];
          myArray[end-1] = temper;

          //make the last element the pivot point
  		T pivot = myArray[end-1];


  		//I have modified the code given to us in the lecture notes to run the partition algorithm on my array
  		int i = start; 
  		for (int j = start; j < (end-1); j++)// could go to end or end-1, but not necessary to compare the pivot to itself once it is in the last element space
  		{
        
  			if (comp(myArray[j], pivot))
  			{
  				T temp = myArray[i];
  				myArray[i]= myArray[j];
  				myArray[j] = temp;

  				i++;

  			}
  		}
  				T temp = myArray[i]; 
  				myArray[i]= myArray[end-1];
  				myArray[end-1] = temp;

  				return i;
		   

  }
  		

