//This is the driver code that makes all the function call and the menu is created here

#include <bits/stdc++.h>
// #include <stdlib.h>
// #include <time.h>
// #include <assert.h>
// #include <string.h>
#define size 1000 

int ind = 0;
char fname[size][32];
char lname[size][32];
char phoneNumber[size][32];

//-----------------------------------------------------------------------------------------------------
/*
This is the create method which takes filename as a parameter and uses string tokenizer that is strtok
function to tokenize the data in CSV file based on spaces and comma and then stores the data in the
global array that is fname, lname and phoneNumber
*/
void create(char * filename){

	char * tok;
	char line[255];
	FILE * readContact=fopen(filename, "r");

	while(fgets(line, sizeof(line), readContact)){

		tok = strtok(line, " ");
		strcpy(fname[ind],tok);
		
		tok = strtok(NULL, ",");
		strcpy(lname[ind],tok);

		tok = strtok(NULL, ", ");
        strcpy(phoneNumber[ind],tok);

        ind++;

	}

	fclose(readContact);

}
//-----------------------------------------------------------------------------------------------------
/*
This is the insert function which takes input from command line to add a new contact to the global 
array and then sort it using the sorting functions
*/

void insertEntry(){

	char ftemp[32], ltemp[32], ptemp[32];

	printf("\t Enter First Name : ");
	scanf("%s", ftemp);
	strcpy(fname[ind],ftemp);

	printf("\t Enter Last Name : ");
	scanf("%s", ltemp);
	strcpy(lname[ind],ltemp);

	printf("\t Enter Phone Number : ");
	scanf("%s", ptemp);
	strcpy(phoneNumber[ind],ptemp);

	ind++;

}

//----------------------------------------------------------------------------------------------------
/*This method merge 2 subarrays, before that it sort the array based on last name and if last names 
are same then first name is used.Here 2 temporary arrays are used and the data are copied into it,
then this 2 arrays lname are compared, and based on the compare value
the lower value is dumped to the main arrays.
*/
void merge(char fname2[size][32],char lname2[size][32],char phoneNumber2[size][32], int firstValue1, int middleValue1, int lastValue1){
			
			int maxIndexLeftSide = middleValue1 - firstValue1 + 1 ;
			int maxIndexRightSide = lastValue1 - middleValue1; 
			int i=0,j=0;
			char temp1_fname[maxIndexLeftSide][32];
			char temp1_lname[maxIndexLeftSide][32];
			char temp1_phoneNumber[maxIndexLeftSide][32];
			char temp2_fname[maxIndexRightSide][32];
			char temp2_lname[maxIndexRightSide][32];
			char temp2_phoneNumber[maxIndexRightSide][32];
			int leftSideIndex,rightSideIndex,mainIndex=firstValue1;
			
			while(i<maxIndexLeftSide)
			{
					strcpy(temp1_fname[i],fname2[i+firstValue1]);
					strcpy(temp1_lname[i],lname2[i+firstValue1]);
					strcpy(temp1_phoneNumber[i],phoneNumber2[i+firstValue1]);
					i++;
				}
			while(j<maxIndexRightSide)
			{
					strcpy(temp2_fname[j],fname2[j+middleValue1+1]);	
					strcpy(temp2_lname[j],lname2[j+middleValue1+1]);	
					strcpy(temp2_phoneNumber[j],phoneNumber2[j+middleValue1+1]);				
					j++;
			}

			for(leftSideIndex=0,rightSideIndex=0,mainIndex=firstValue1;leftSideIndex<maxIndexLeftSide && rightSideIndex<maxIndexRightSide;){
				int compare = strcmp(temp1_lname[leftSideIndex],temp2_lname[rightSideIndex]);
				if(compare == 0)
				{
					int compareFName = strcmp(temp1_fname[leftSideIndex],temp2_fname[rightSideIndex]);
					
						if(compareFName>0){
							strcpy(lname[mainIndex],temp2_lname[rightSideIndex]);
							strcpy(fname[mainIndex],temp2_fname[rightSideIndex]);
							strcpy(phoneNumber[mainIndex],temp2_phoneNumber[rightSideIndex]);
							rightSideIndex++;
						}
						else if(compareFName <= 0){
							strcpy(lname[mainIndex],temp1_lname[leftSideIndex]);
							strcpy(fname[mainIndex],temp1_fname[leftSideIndex]);
							strcpy(phoneNumber[mainIndex],temp1_phoneNumber[leftSideIndex]);
							leftSideIndex++;
						}
				}
				else if(compare>0){
					strcpy(lname[mainIndex],temp2_lname[rightSideIndex]);
					strcpy(fname[mainIndex],temp2_fname[rightSideIndex]);
					strcpy(phoneNumber[mainIndex],temp2_phoneNumber[rightSideIndex]);
					rightSideIndex++;
				}
				else if(compare<0){
					strcpy(lname[mainIndex],temp1_lname[leftSideIndex]);
					strcpy(fname[mainIndex],temp1_fname[leftSideIndex]);
					strcpy(phoneNumber[mainIndex],temp1_phoneNumber[leftSideIndex]);
					leftSideIndex++;				
				}
				mainIndex++;
			}
			while(leftSideIndex<maxIndexLeftSide){
					strcpy(lname[mainIndex],temp1_lname[leftSideIndex]);
					strcpy(fname[mainIndex],temp1_fname[leftSideIndex]);
					strcpy(phoneNumber[mainIndex],temp1_phoneNumber[leftSideIndex]);
					leftSideIndex++;
					mainIndex++;
			}
			while(rightSideIndex<maxIndexRightSide){
					strcpy(lname[mainIndex],temp2_lname[rightSideIndex]);
					strcpy(fname[mainIndex],temp2_fname[rightSideIndex]);
					strcpy(phoneNumber[mainIndex],temp2_phoneNumber[rightSideIndex]);
					rightSideIndex++;
					mainIndex++;
			
			}
		}		
	
/*
*This is a mergeSort method, The algorithm of merge sort is to divide the main array into smaller sub 
arrays ( Atomic) Such unit which will be sorted in its own. It is a recursive code, where first we will
write the exit condition, which is lastValue cannot be less than or equal to firstValue. Then finding 
the middleValue and call the mergeSort method twice( first the left subarray part) and then right subarray
part and once it is divided into the smallest element such that lastValue>firstValue subarrays are merged
using merge method(), which is implemented above.
*/	
void mergeSort(char fname1[size][32], char lname1[size][32], char phoneNumber1[size][32],int firstValue ,int lastValue){
	int middleValue = 0;
	
	if(lastValue>firstValue){
		middleValue= firstValue + (lastValue-firstValue)/2;
		mergeSort(fname1, lname1, phoneNumber1, firstValue, middleValue);
		mergeSort(fname1, lname1, phoneNumber1, middleValue+1, lastValue);
		merge(fname1, lname1, phoneNumber1, firstValue, middleValue, lastValue);
	}
						
}

/*
This method is use to sort the directory based on last name using merge sort, And if last name are same
for entries in directory, First name is use to sort. This sortDirectory () is called, from main method 
and it calls mergeSort() passing all arrays along with size of arrays and initial values.
*/
void sortDirectory(){

	int firstValue=0;
	mergeSort(fname, lname, phoneNumber,firstValue, ind-1);

}
//----------------------------------------------------------------------------------------------------

/*This is the partition method of quick sort, here low and high value are passed from quick sort method.
since it is a randomize quick sort, A random pivot value is calculated using rand(). Now that random 
index value is moved to a temp array. And then a loop will be executed for comparing the phoneNumber 
values in the array with the pivot. If the value is less or equal, values less to pviot are moved to 
left and greater to right.
*/
int partition(char fname[size][32],char lname[size][32],char phoneNumber[size][32], int lowerEnd, int HigherEnd){

	srand(time(NULL));	
	int randomValue = lowerEnd + rand() % (HigherEnd - lowerEnd + 1);
	char pivot[32];
	int indexToBeSwapWith = lowerEnd - 1;
	int swapComparison=0,i=0;	
	char temp1_fname[32];
	char temp1_lname[32];
	char temp1_phoneNumber[32];

	strcpy(temp1_fname,fname[randomValue]);
	strcpy(temp1_lname,lname[randomValue]);
	strcpy(temp1_phoneNumber,phoneNumber[randomValue]);
	strcpy(fname[randomValue],fname[HigherEnd]);
	strcpy(lname[randomValue],lname[HigherEnd]);
	strcpy(phoneNumber[randomValue],phoneNumber[HigherEnd]);
	strcpy(fname[HigherEnd],temp1_fname);
	strcpy(lname[HigherEnd],temp1_lname);
	strcpy(phoneNumber[HigherEnd],temp1_phoneNumber);	

	
	strcpy(pivot,phoneNumber[HigherEnd]);
	for(i=lowerEnd;i<=HigherEnd-1;i++){
		swapComparison = strcmp(phoneNumber[i],pivot);

		if(swapComparison <= 0){
			indexToBeSwapWith++;
			strcpy(temp1_fname,fname[indexToBeSwapWith]);
			strcpy(temp1_lname,lname[indexToBeSwapWith]);
			strcpy(temp1_phoneNumber,phoneNumber[indexToBeSwapWith]);
			strcpy(fname[indexToBeSwapWith],fname[i]);
			strcpy(lname[indexToBeSwapWith],lname[i]);
			strcpy(phoneNumber[indexToBeSwapWith],phoneNumber[i]);
			strcpy(fname[i],temp1_fname);
			strcpy(lname[i],temp1_lname);
			strcpy(phoneNumber[i],temp1_phoneNumber);
			}
	}
			strcpy(temp1_fname,fname[indexToBeSwapWith+1]);
			strcpy(temp1_lname,lname[indexToBeSwapWith+1]);
			strcpy(temp1_phoneNumber,phoneNumber[indexToBeSwapWith+1]);
			strcpy(fname[indexToBeSwapWith+1],fname[HigherEnd]);
			strcpy(lname[indexToBeSwapWith+1],lname[HigherEnd]);
			strcpy(phoneNumber[indexToBeSwapWith+1],phoneNumber[HigherEnd]);
			strcpy(fname[HigherEnd],temp1_fname);
			strcpy(lname[HigherEnd],temp1_lname);
			strcpy(phoneNumber[HigherEnd],temp1_phoneNumber);
	return indexToBeSwapWith+1;
}

/*In QuickSort, same as merge sort, it is a recursive algorithm, where same method is called, only 
difference is here a pivot will be used such that anything less than pivot will be smaller and anything
on right is greater.First we have the exit condition which will be same( high value should be greater
than low value.
*/

void quickSort(char lname1[size][32], char fname1[size][32], char phoneNumber1[size][32], int lowValue, int highValue){
	int pivot=0;
	if(lowValue<highValue){
	pivot = partition(fname1,lname1,phoneNumber1, lowValue, highValue);
	quickSort(lname1,fname1,phoneNumber1,lowValue,pivot-1);
	quickSort(lname1,fname1,phoneNumber1,pivot+1,highValue);
	}

}
/*This method checkSameName is use to get the last index of those entries which are present for multiple 
times. Here sortDirectoryOnPhone calls and passes the startIndex of such entries and this method in 
returns provides the Last index of that entry, algorithm of this is such that a loop will be executed 
until lname and fname are same. In this way, we get the lastIndexForSameName.
*/
int checkSameName(char phoneNumber1[size][32],char fname1[size][32],char lname1[size][32], int startIndex){
	int j=startIndex+1;
	int i=startIndex;	
	while(j<=ind && strcmp(lname1[i],lname1[j])==0 && strcmp(fname1[i],fname1[j])==0){
			j++;
		}
	return j-1;
			}
			
/*This method sortDirectoryOnPhone is used to sort the result of merge sort based on phone numbers to 
make directory sorted. Here quick sort method is called, but quick sort is called for those Names which
have multiple entries in the phone book, and to get the index of same names, above checkSameName method
is use, it provides the lastIndexForSameName which will be passed to quick sort that name on phone number.
*/

void sortDirectoryOnPhone(){
	int startIndex = 0;
	int lastIndexForSameName = 0;		
	int endIndex = ind;
	
	while(startIndex<endIndex){
		lastIndexForSameName = checkSameName(phoneNumber,fname,lname,startIndex);
		quickSort(lname,fname,phoneNumber,startIndex,lastIndexForSameName);
		startIndex=lastIndexForSameName+1;
	}
}

//----------------------------------------------------------------------------------------------------

/*
This method named showDirectory is used to display all the contacts in sorted order
*/

void showDirectory(){

	for(int i=0; i<ind; i++){
		printf("\t %d %s %s,%s\n\n",i+1,fname[i],lname[i],phoneNumber[i]);
	}

	printf("You have %d contacts in your directory\n\n\n",ind);
}

//----------------------------------------------------------------------------------------------------

/*
This method here is created to search the index of the element for display purpose. This method makes
use of binary search algorithm. Here we are passing our global arrays which has the sorted data in the
arguments with first and last index and the name to be searched. Here we are finding the middle element
and comparing it with the name to be searched and if check condition is used. If we get the match then
we use a loop to find the last element that matches the argument and as we get it we return the index
to delete function.If we do not find the the element we make use of recursive call to the same function
till we find the element. There is one more thing, if we find the contact at some place we make use of 
loop to detect and display all the same name contacts if there are any at the left part of array and 
right part.
*/

void binarySearch(char fn[size][32], char ln[size][32], char pn[size][32], int l, int r, char fSearch[32], char lSearch[32]){

	if(r >= l){

		int mid = l + (r - l)/2;

		int first = strcmp(fSearch,fn[mid]);
		int last = strcmp(lSearch,ln[mid]);

		if(last == 0)
		{	
			if(first==0)
			{	
				printf("--------------------------- Contact Found :-) -----------------------------\n\n");
				printf("%d %s %s, %s\n", mid+1, fn[mid], ln[mid], pn[mid]);
				

				for(int i = mid-1; i>=0; i--){

					int f2 = strcmp(fSearch,fn[i]);
					int l2 = strcmp(lSearch,ln[i]);

					if(f2 == 0 && l2 == 0)
						printf("%d %s %s, %s\n", i+1, fn[i], ln[i], pn[i]);

					

				}

				for(int j = mid+1; j <= r; j++){

					int f3 = strcmp(fSearch,fn[j]);
					int l3 = strcmp(lSearch,ln[j]);

					if(f3 == 0 && l3 == 0){
						printf("%d %s %s, %s\n", j+1, fn[j], ln[j], pn[j]);
					}
					

				}

			}	
			else if(first>0)
				binarySearch(fname,lname,phoneNumber,mid+1,r,fSearch,lSearch);
			else if(first<0)
				binarySearch(fname,lname,phoneNumber,l,mid-1,fSearch,lSearch);
			
		}			
		
		else if(last<0)
			binarySearch(fname,lname,phoneNumber,l,mid-1,fSearch,lSearch);
		
		else if(last>0)
			binarySearch(fname,lname,phoneNumber,mid+1,r,fSearch,lSearch);
	}

	else{

		printf("----------------------- Contact not found :-( ------------------------ \n\n");

	}

}

/*
This function here takes argument form command line and searches for the contact using binary search
algorithm.
*/

void searchDirectory(){

	char f_name[32], l_name[32];

	printf("Enter first name and last name to search :");
	scanf("%s %s",f_name,l_name);
	printf("Name is : %s %s\n",f_name,l_name);

	binarySearch(fname, lname, phoneNumber, 0, ind, f_name, l_name);

}

//---------------------------------------------------------------------------------------------------
/*
This method here is created to search the index of the element for deletion purpose. This method makes
use of binary search algorithm. Here we are passing our global arrays which has the sorted data in the
arguments with first and last index and the name to be searched. Here we are finding the middle element
and comparing it with the name to be searched and if check condition is used. If we get the match then
we use a loop to find the last element that matches the argument and as we get it we return the index
to delete function.
*/
int binarySearchForDelete(char fn[size][32], char ln[size][32], char pn[size][32], int l, int r, char fSearch[32], char lSearch[32]){

	if(r >= l){

		int mid = l + (r - l)/2;

		int first = strcmp(fSearch,fn[mid]);
		int last = strcmp(lSearch,ln[mid]);

		if(last == 0)
		{	
			if(first==0)
			{	printf("%d %s %s, %s\n", mid+1, fn[mid], ln[mid], pn[mid]);
				printf("--------------------------Contact Deleted-------------------------\n\n");

				while(strcmp(fSearch,fn[mid]) == 0){

					mid++;

				}
				return mid-1;

			}	
			else if(first>0)
				binarySearchForDelete(fname,lname,phoneNumber,mid+1,r,fSearch,lSearch);
			else if(first<0)
				binarySearchForDelete(fname,lname,phoneNumber,l,mid-1,fSearch,lSearch);
			
		}			
		
		else if(last<0)
			binarySearchForDelete(fname,lname,phoneNumber,l,mid-1,fSearch,lSearch);
		
		else if(last>0)
			binarySearchForDelete(fname,lname,phoneNumber,mid+1,r,fSearch,lSearch);
	}

	else{

		printf("----------------------- Contact not found :-( ------------------------ \n\n");
		return -1;
	}

}

/*
This function here takes user input from command line and searches for the input name in the directory
using binary search and deletes the the contact when found.
*/
void deleteEntry(){

	char f_name2[32], l_name2[32];
	printf("Enter the  First Name and Last Name you want to delete : ");
	scanf("%s %s",f_name2,l_name2);

	int index = binarySearchForDelete(fname,lname,phoneNumber,0,ind,f_name2,l_name2);

	if(index != -1){
	

	for(int k = index; k<=ind; k++){
		strcpy(phoneNumber[k],phoneNumber[k+1]);



		strcpy(fname[k],fname[k+1]);
		strcpy(lname[k],lname[k+1]);	}

	ind--;
}

}

//-----------------------------------------------------------------------------------------------------------------







int main(int argc, char * argv[]){

	int choice = 0;


	printf("\t-----------------------------------\n");
    printf("\t       Creating Your contacts      \n");
    printf("\t-----------------------------------\n");
	create(argv[1]);
	printf("\t-----------Contacts Created--------\n\n\n");

	do{

		printf("******************************************\n\n");
		printf("\tMenu\n\n");
		printf("Insert 			(press 1)\n");
		printf("Search  		(press 2)\n");
		printf("Delete  		(press 3)\n");
		printf("Show Directory 		(press 4)\n");
		printf("Exit	  		(press 5)\n\n");
		printf("******************************************\n\n");
		scanf("%d", &choice);
		


		switch(choice){

		
		case 1:
		printf("\t-----------------------------------\n");
    	printf("\t   		Add new contacts         \n");
    	printf("\t-----------------------------------\n");
		insertEntry();
		sortDirectory();
		sortDirectoryOnPhone();
    	printf("\t------Contact added successfully----\n\n\n");
    	choice = 6;
    	break;
		
		case 2:
		sortDirectory();
		sortDirectoryOnPhone();
		searchDirectory();
		choice = 6;
		break;

		case 3:
		sortDirectory();
		sortDirectoryOnPhone();
		deleteEntry();
		choice = 6;
		break;

		case 4:
		printf("\t-----------------------------------\n");
    	printf("\t    	Here are your contacts       \n");
    	printf("\t-----------------------------------\n");
    
    	printf("\t=======Sorted with MERGE SORT======\n");
    	sortDirectory();
		showDirectory();

		printf("\t=======Sorted with QUICK SORT======\n");
		sortDirectoryOnPhone();
		showDirectory();
		choice = 6;
		break;
		
		case 5:
		printf("Exit\n");
		exit(0);
		break;

		default: 
		printf("Wrong choice. Please enter again\n");
		exit(0);
		break;
	}

	}while(1);

	return 0;
}