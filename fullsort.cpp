#include <iostream>

using namespace std;

struct Node {
  //   Node(int v, Node* n){value = v; next = n;}
    int value;
    Node *next;
};

Node* recSort (Node* in) // helper function for recursive sort
{
	int min = in->value; // minimum value that is removed and placed at the beginning of list
    Node *prev = in; // keep track of previous value
    Node *move_back = NULL; // second variable to update the previous value
    Node *temp = in->next; // keep track of the following variable for comparison to min

   
    while(temp != NULL ) // make sure you are not at the end of the list
    {
        if(temp->value <= min) // compare following value to the current minimum
        {
            min = temp->value; // update minimum value
         	move_back = prev;   // update what the previous value was
        }
        prev = temp; //set previous equal to the value that was following in
        temp = temp->next; // access next value in the linked list
    }

    if(move_back == NULL) // if minimum value was placed at the beginning of the list, run the sort on the next value
    {
       	if (in->next != NULL) // check to make sure you are not at the end of the list
       	{
       		in->next = recSort(in->next); // call the recursive sort
       	}
        return in;
    }

    //update values and call recursive function if first value of list was not changed
    prev = move_back;
    move_back = prev->next;
    prev->next = prev->next->next;
    move_back->next = recSort(in);
    return move_back;

}

Node* fullsort (Node* in) // function to sort a linked list
{
	if(in == NULL || in->next == NULL) // base case to check if empty lisst or list of size 1
	{
		return in;
	}

	else // call the recursive function
	{
		return recSort(in);
	}


}

/*int main()
{
   
      Node* head = new Node(2, new Node(2, new Node(1, new Node(1,  NULL))));
   

   	head = fullsort(head);

   	Node *final = head;

   	while(final != NULL)
   	{
   		cout << final->value << endl;
   		final = final-> next;
   	}

   	return 0;

}*/


