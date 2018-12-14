#include<iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

void showArray(int array[], int size){
    for(int i = 0;i < size; ++i){
        cout << array[i] << ",";
    }
    cout << endl;
}

void insertSort(int array[], int size){
    int i,j,k,elem;
    for(i = size-2; i >= 0; --i){
        j = size-1;
        elem = array[i];

        while(j > i && array[j] >= elem)
            j--;

        for(k = i; k < j; ++k)
            array[k] = array[k+1];

        array[j] = elem;
        showArray(array, size);
    }
}

void bubbleSort(int array[], int size){
    int i, j, tmp;
    for(i = 0; i < size - 1; ++i){
        for(j = size-1; j > i; --j)
            if(array[j] < array[j-1]){
                tmp = array[j];
                array[j] = array[j-1];
                array[j-1] = tmp;
            }
        showArray(array, size);
    }
}

void mergeArr(int arr[], int begin, int  mid, int end){
    int *auxAr = new int[end - begin + 1];//auxiliary array

    int i = begin, j = mid + 1;//i is for left-hand array,j is for right-hand array

    int k = 0;//k is used inthe temporary array

    while(i <= mid && j <=end){
        if(arr[i] <= arr[j])
            auxAr[k++] = arr[i++];
        else
            auxAr[k++] = arr[j++];
    }

    //rest elements of left-half
    while(i <= mid)
        auxAr[k++] = arr[i++];

    //rest elements of right-half
    while(j <= end)
        auxAr[k++] = arr[j++];

    //copy the mergered temporary array to the original array
    for(k = 0, i = begin; i <= end; ++i, ++k)
        arr[i] = auxAr[k];

    delete []auxAr;
}

void mergeSortIter(int array[], int size){
    int middle,end;

    for (int i = 1; i <= size - 1; i *= 2){
        for (int begin = 0; begin < size - 1; begin += 2*i){
            end = begin + 2*i - 1;
            if(end > size - 1){
                end = size - 1;
            }

            middle = begin + i - 1;

            mergeArr(array,begin,middle,end);
        }
        showArray(array,size);
    }
}

double obliczSekundy( clock_t czas )
{
    return static_cast < long double >( czas ) / CLOCKS_PER_SEC;
}

void insertSortTest(int array[], int size){
    clock_t start = clock();
    int i,j,k,elem;
    for(i = size-2; i >= 0; --i){
        j = size-1;
        elem = array[i];

        while(j > i && array[j] >= elem)
            j--;

        for(k = i; k < j; ++k)
            array[k] = array[k+1];

        array[j] = elem;
    }
    clock_t value = clock()-start;
    cout << "Czas wykonywania InsertSort: " << obliczSekundy(value) << " sekund." << endl;
}

void bubbleSortTest(int array[], int size){
    clock_t start = clock();
    int i, j, tmp;
    for(i = 0; i < size - 1; ++i){
        for(j = size-1; j > i; --j)
            if(array[j] < array[j-1]){
                tmp = array[j];
                array[j] = array[j-1];
                array[j-1] = tmp;
            }
    }
    clock_t value = clock()-start;
    cout << "Czas wykonywania BubbleSort: " << obliczSekundy(value) << " sekund." << endl;
}

void mergeSortIterTest(int array[], int size){
    clock_t start = clock();
    int middle,end;

    for (int i = 1; i <= size - 1; i *= 2){
        for (int begin = 0; begin < size - 1; begin += 2*i){
            end = begin + 2*i - 1;
            if(end > size - 1){
                end = size - 1;
            }

            middle = begin + i - 1;

            if(middle > end){
                continue;
            }

            mergeArr(array,begin,middle,end);
        }
    }
    clock_t value = clock()-start;
    cout << "Czas wykonywania MergeSort: " << obliczSekundy(value) << " sekund." << endl;
}

int * loadArray(int size){
    int *ar = new int[size];

    for(int i = 0; i < size; ++i){
        cin >> ar[i];
    }
    return ar;
}

void loadArrayTest(int *ar1, int *ar2, int *ar3, int size){
    srand((unsigned)time( NULL ) );

    for(int i = 0; i < size; ++i){
        ar1[i] = (rand()%100)+1;
        ar2[i] = ar1[i];
        ar3[i] = ar1[i];
    }
}

bool isCommand(const string command,const char *mnemonic){
    return command==mnemonic;
}

int main(){
    string line;
    string command;
    int size=0;
    cout << "START" << endl;
    while(true){
        getline(cin,line);
        std::stringstream stream(line);
        stream >> command;
        if(line=="" || command[0]=='#')
        {
            // ignore empty line and comment
            continue;
        }

        // copy line on output with exclamation mark
        cout << "!" << line << endl;;

        // change to uppercase
        command[0]=toupper(command[0]);
        command[1]=toupper(command[1]);

        // read next argument, one int size
        stream >> size;

        // one-argument command
        if(isCommand(command,"HA")){
            cout << "END OF EXECUTION" << endl;
            break;
        }

        if(isCommand(command,"IS")) //*
        {
            int *arr=loadArray(size);
            showArray(arr,size);
            insertSort(arr,size);
            continue;
        }

        if(isCommand(command,"TE")) //*
        {
            int *ar1 = new int[size];
            int *ar2 = new int[size];
            int *ar3 = new int[size];

            loadArrayTest(ar1, ar2, ar3, size);
            insertSortTest(ar1,size);
            bubbleSortTest(ar2, size);
            mergeSortIterTest(ar3, size);
            continue;
        }

        if(isCommand(command,"BS")) //*
        {
            int *arr=loadArray(size);
            showArray(arr,size);
            bubbleSort(arr,size);
            continue;
        }

        if(isCommand(command,"MI")) //*
        {
            int *arr=loadArray(size);
            showArray(arr,size);
            mergeSortIter(arr,size);
            continue;
        }

        cout << "wrong argument in test: " << command << endl;
    }
    return 0;
}
