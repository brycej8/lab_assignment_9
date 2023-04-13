#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
	struct RecordType *next;
};

// Fill out this structure
struct HashType
{
	struct RecordType *record;
	int size;
};

// Compute the hash function
int hash(int x, int size)
{
	return (x % size);
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

void insertRecord(struct HashType* hashrecord, struct RecordType* record, int recordSize) {
    int index = hash(record->id, recordSize);
    if (hashrecord[index].record == NULL) {
        hashrecord[index].record = record;
		hashrecord[index].record ->next = NULL;
    }

    else {

		struct RecordType *temp = hashrecord[index].record;
        while (temp->next != NULL) {
            temp = temp->next;
        }
		temp->next = record;
        temp->next->next = NULL;
    }
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0; i<hashSz; i++)
	{
		// if index is occupied with any records, print all
		if((pHashArray + i)->record != NULL){
			struct RecordType *temp = (pHashArray + i)->record;
			printf("\nIndex %d", i + 1);

			while(temp != NULL){
				printf(" -> %d, %c, %d", temp->id, temp->name, temp->order);
				temp = temp->next;

			}
			printf(" -> NULL");
		}
	}
	printf("\n");
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);

	int size = 11;

	struct HashType *pHashArray = malloc(size * sizeof(struct HashType));

	for(int i = 0; i<size; i++){
		pHashArray[i].record = NULL;
	}

	for(int i = 0; i<recordSz; i++){
		insertRecord(pHashArray, pRecords + i, size);
	}
	displayRecordsInHash(pHashArray, size);
	free(pHashArray);
	free(pRecords);

	return 0;
}