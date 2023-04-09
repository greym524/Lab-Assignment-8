#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int arr[], int n)
{
	int temp1, temp2;

	for(int i = 1; i < n; i++) //builds heap which will be sorted, builds a maxHeap
	{
		temp1 = 0;
		if(arr[i] > arr[(i-1)/2])
		{
			temp1 = i;
			while(arr[temp1] > arr[(temp1 - 1) / 2])
			{
				int arrVal = arr[temp1];
				arr[temp1] = arr[(temp1 - 1) / 2];
				arr[(temp1 - 1) / 2] = arrVal;
				temp1 = (temp1 - 1) / 2;
			}
		}
	}

	for(int i = n - 1; i > 0; i--) //sorts the built maxHeap above into a minHeap
	{
		int temp1 = arr[0];
		arr[0] = arr[i];
		arr[i] = temp1;

		int j = 0, index = 1; 

		do{
			// index = (2* j + 1);

			if(arr[index] < arr[index + 1] && index < (i - 1))
			{
				index++;
			}
			if(arr[j] < arr[index] && index < i)
			{
				temp2 = arr[j];
				arr[j] = arr[index];
				arr[index] = temp2;
			}
			j = index;
			index = (2* j + 1);
		}while (index < i);
	}
}


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	if(l < r)
	{
		int mid, i, j, k;
		mid = (l+r)/2;
		mergeSort(pData, l, mid);
		mergeSort(pData, mid+1, r);

		int size1 = mid - l + 1;
		int size2 = r - mid;
			
		int* left = (int*)malloc(sizeof(int)*size1);
		int* right = (int*)malloc(sizeof(int)*size2);


		for(i = 0; i < size1; i++)
		{
			left[i] = pData[l+i];
		}
		for(j = 0; j < size2; j++)
		{
			right[j] = pData[mid + 1 +j];
		}

		i=0;
		j=0;
		k=l;

		while(i < size1 && j < size2)
		{
			if(left[i] <= right[j])
			{
				pData[k] = left[i];
				i++;
			}
			else
			{
				pData[k] = right[j];
				j++;
			}
			k++;
		}
		while(i < size1)
		{
			pData[k] = left[i];
			i++;
			k++;

		}
		while(j < size2)
		{
			pData[k] = right[j];
			j++;
			k++;
		}
		free(left);
		free(right);
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i) 
	{
		
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}