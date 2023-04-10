#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;
void swap(int*x,int*y)
{
    int temp=*x;
    *x=*y;
    *y=temp;
}
// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
int* heapify(int arr[],int n,int m)
{
    int max=m;
    int l=2*m+1;
    int r=2*m+2;
    if(l<n && arr[l]>arr[max])
    {
        max=l;
    }
    if(r<n && arr[r]>arr[max])
    {
        max=r;
    }
    if(max!=m)
    {
        swap(&arr[m],&arr[max]);
        heapify(arr,n,max);
    }
}
void heapSort(int arr[], int n)
{
for(int i=n/2-1;i>=0;i--)
{
    heapify(arr, n ,i);
}
for(int i=n-1;i>=0;i--)
{
    swap(&arr[0],&arr[i]);
    heapify(arr,i,0);
}
}


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated

void merge(int pData[],int l,int mid, int r)
{
	int lsiz=mid+1-l;
	int rsiz=r-mid;
	extraMemoryAllocated+=sizeof(int)*(lsiz);
	extraMemoryAllocated+=sizeof(int)*(rsiz);

	int* L=(int*)malloc(sizeof(int)*(lsiz));
	int* R=(int*)malloc(sizeof(int)*(rsiz));
	
	for(int i=0;i<lsiz;i++)
	{
		L[i]=pData[l+i];
	}
	for(int j=0;j<rsiz;j++)
	{
		R[j]=pData[j+mid+1];
	}
	int i=0;
	int j=0;
	int k=l;
	while(i<lsiz&&j<rsiz)
	{
		if(L[i]<=R[j])
		{
			pData[k]=L[i];
			i++;
		}
		else
		{
			pData[k]=R[j];
			j++;
		}
		k++;
	}
	while(i<lsiz)
	{
		pData[k]=L[i];
		i++;
		k++;
	}
	while(j<rsiz)
	{
		pData[k]=R[j];
		j++;
		k++;
	}
	free(L);
	free(R);
}
void mergeSort(int pData[], int l, int r)
{
	
	if(l<r)
	{
		int mid= (l+r)/2;
		mergeSort(pData,l,mid);
		mergeSort(pData,mid+1,r);
		merge(pData,l,mid,r);
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
