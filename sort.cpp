#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <utility>
#include <iomanip>
#include "sort.hpp"
#define inf 1000000
#define breakline std::cout<<"------------------------\n\n";


bool SortDSC(int a,int b){
    return a>b;
}

void Sort::MakeFile(){
    std::ofstream OutFile;
    OutFile.open("./times",std::ios::app);
    if(!OutFile.is_open())
        std::cout<<"Creating file error.\n";
    
    OutFile<<"size = "<<size<<"\n\n";
    for(int i=0;i<3;i++){
        OutFile<<std::fixed<<T_insert[i]<<'\n';
        OutFile<<std::fixed<<T_selection[i]<<'\n';
        OutFile<<std::fixed<<T_bubble[i]<<"\n\n";
        OutFile<<std::fixed<<T_quick[i]<<'\n';
        OutFile<<std::fixed<<T_shell[i]<<'\n';
        OutFile<<std::fixed<<T_heap[i]<<"\n\n";
    }
    
}

Sort::Sort(){
    std::cout<<"Podaj rozmiar tablicy do sortowania\n";
    std::cin>>size;
    tab=new int[size];
    asc=new int[size];
    dsc=new int[size];
    std::ifstream File;
    File.open("./dane");
    if(!File.is_open())
        std::cout<<"Reading file error.";
    for(int i=0;i<size;i++){
        File>>tab[i];
        asc[i]=tab[i];
        dsc[i]=tab[i];
    }
    std::cout<<"\n";
    File.close();
    std::sort(asc,asc+size);
    std::sort(dsc,dsc+size,SortDSC);
    std::cout<<"Tablica wczytana z pliku dane:\n";
    for(int i=0;i<size;i++)
        std::cout<<tab[i]<<" ";
    std::cout<<'\n';
    breakline;
}
Sort::~Sort(){
}

void IS(int *a,int n){
    int tmp,j;
    for(int i=1;i<n;i++){
        tmp=a[i]; //ten element będzie wstawiony w odpowiednie miejsce
        j=i-1;
        //przesuwanie elementów większych od pom
        while(j>=0&&a[j]>tmp) {
            a[j+1]=a[j]; //przesuwanie elementów
            --j;
        }
        a[j+1]=tmp; //wstawienie pom w odpowiednie miejsce
    }   
}
void Sort::insertion_sort(){
    int a[size],b[size];
    std::copy(tab,tab+size,a);
    std::copy(dsc,dsc+size,b);
    clock_t start=clock(); 
    IS(a,size);   //wywołanie od tablicy liczb losowych 
    clock_t stop=clock();
    T_insert[0]=static_cast<double>(stop-start)/CLOCKS_PER_SEC;
    start=clock(); 
    IS(asc,size);   //wywołanie od tablicy posortowaniej rosnąco
    stop=clock();
    T_insert[1]=static_cast<double>(stop-start)/CLOCKS_PER_SEC;
    start=clock(); 
    IS(b,size);   //wywołanie od tablicy posortowanej malejąco 
    stop=clock();
    T_insert[2]=static_cast<double>(stop-start)/CLOCKS_PER_SEC;
    std::cout<<"INSERTION SORT\n";
    std::cout<<"Tablica posortowana rosnąco:\n";
    for(int i=0;i<size;i++)
        std::cout<<a[i]<<" ";
    std::cout<<"\n\nCzas sortowania tablicy liczb losowych: "<<std::fixed<<T_insert[0]<<'\n';
    std::cout<<"Czas sortowania tablicy posortowanej rosnąco: "<<std::fixed<<T_insert[1]<<'\n';
    std::cout<<"Czas sortowania tablicy posortowanej malejąco: "<<std::fixed<<T_insert[2]<<"\n";
    breakline;
}
void SS(int *a,int n){
    int tmp;
    for(int i=0;i<n-1;i++){
        tmp=i;
        for(int j=i+1;j<n;j++) //pętla wyszukuje najmniejszy element w podzbiorze nieposortowanym
        if(a[j]<a[tmp])
        tmp=j;
        //zamiana elementu najmniejszego w podzbiorze z pierwszą pozycją nieposortowaną
        std::swap(a[i],a[tmp]);
    }
}
void Sort::selection_sort(){
    int a[size],b[size];
    std::copy(tab,tab+size,a);
    std::copy(dsc,dsc+size,b);
    clock_t start=clock();
    SS(a,size);
    clock_t stop=clock();
    T_selection[0]=static_cast<double>(stop-start)/CLOCKS_PER_SEC;
    start=clock(); 
    SS(asc,size);   //wywołanie od tablicy posortowaniej rosnąco
    stop=clock();
    T_selection[1]=static_cast<double>(stop-start)/CLOCKS_PER_SEC;
    start=clock(); 
    SS(b,size);   //wywołanie od tablicy posortowanej malejąco 
    stop=clock();
    T_selection[2]=static_cast<double>(stop-start)/CLOCKS_PER_SEC;
    std::cout<<"SELECTION SORT\n";
    std::cout<<"Tablica posortowana rosnąco:\n";
    for(int i=0;i<size;i++)
        std::cout<<a[i]<<" ";
    std::cout<<"\n\nCzas sortowania tablicy liczb losowych: "<<T_selection[0]<<'\n';
    std::cout<<"Czas sortowania tablicy posortowanej rosnąco: "<<T_selection[1]<<'\n';
    std::cout<<"Czas sortowania tablicy posortowanej malejąco: "<<T_selection[2]<<"\n";
    breakline;
}

void BS(int *a,int n){
    for(int i=0;i<n;i++)
		for(int j=1;j<n-i;j++)
		if(a[j-1]>a[j])
			std::swap(a[j-1],a[j]);
}
void Sort::bubble_sort(){
    int a[size],b[size];
    std::copy(tab,tab+size,a);
    std::copy(dsc,dsc+size,b);
    clock_t start=clock();
    BS(a,size);
    clock_t stop=clock();
    T_bubble[0]=static_cast<double>(stop-start)/CLOCKS_PER_SEC;
    start=clock(); 
    BS(asc,size);   //wywołanie od tablicy posortowaniej rosnąco
    stop=clock();
    T_bubble[1]=static_cast<double>(stop-start)/CLOCKS_PER_SEC;
    start=clock(); 
    BS(b,size);   //wywołanie od tablicy posortowanej malejąco 
    stop=clock();
    T_bubble[2]=static_cast<double>(stop-start)/CLOCKS_PER_SEC;
    std::cout<<"BUBBLE SORT\n";
    std::cout<<"Tablica posortowana rosnąco:\n";
    for(int i=0;i<size;i++)
        std::cout<<a[i]<<" ";
    std::cout<<"\n\nCzas sortowania tablicy liczb losowych: "<<T_bubble[0]<<'\n';
    std::cout<<"Czas sortowania tablicy posortowanej rosnąco: "<<T_bubble[1]<<'\n';
    std::cout<<"Czas sortowania tablicy posortowanej malejąco: "<<T_bubble[2]<<"\n";
    breakline;
}

void QS(int *a, int p, int k) {
if(k<=p) return;
	
	int i =p- 1, j = k + 1, 
	pivot = a[(p+k)/2];
	while(true){
		while(pivot>a[++i]);
		while(pivot<a[--j]);
		if( i <= j)
			std::swap(a[i],a[j]);
		else
			break;
	}
	if(j > p)
	QS(a, p, j);
	if(i < k)
	QS(a, i, k);
}

void Sort::quick_sort(){
    int a[size],b[size];
    std::copy(tab,tab+size,a);
    std::copy(dsc,dsc+size,b);
    clock_t start=clock();
    QS(a,0,size-1);
    clock_t stop=clock();
    T_quick[0]=static_cast<double>(stop-start)/CLOCKS_PER_SEC;
    start=clock(); 
    QS(asc,0,size-1);   //wywołanie od tablicy posortowaniej rosnąco
    stop=clock();
    T_quick[1]=static_cast<double>(stop-start)/CLOCKS_PER_SEC;
    start=clock(); 
    QS(b,0,size-1);   //wywołanie od tablicy posortowanej malejąco 
    stop=clock();
    T_quick[2]=static_cast<double>(stop-start)/CLOCKS_PER_SEC;
    std::cout<<"QUICK SORT\n";
    std::cout<<"Tablica posortowana rosnąco:\n";
    for(int i=0;i<size;i++)
        std::cout<<b[i]<<" ";
    std::cout<<"\n\nCzas sortowania tablicy liczb losowych: "<<T_quick[0]<<'\n';
    std::cout<<"Czas sortowania tablicy posortowanej rosnąco: "<<T_quick[1]<<'\n';
    std::cout<<"Czas sortowania tablicy posortowanej malejąco: "<<T_quick[2]<<"\n";
    breakline;
}

void SHS(int *a,int n){
    int przerwa = n/2;
    while(przerwa >= 1) {
    for (int i=przerwa;i<n;i+=1){
        int temp=a[i];
        int j;
        for (j=i;j>=przerwa&&a[j-przerwa]>temp;j-=przerwa)
            a[j]=a[j-przerwa];
        a[j] = temp;
    }
    przerwa/=2;
  }
}
void Sort::shell_sort(){
    int a[size],b[size];
    std::copy(tab,tab+size,a);
    std::copy(tab,tab+size,b);
    clock_t start=clock();
    SHS(a,size);
    clock_t stop=clock();
    T_shell[0]=static_cast<double>(stop-start)/CLOCKS_PER_SEC;
    start=clock(); 
    SHS(asc,size);   //wywołanie od tablicy posortowaniej rosnąco
    stop=clock();
    T_shell[1]=static_cast<double>(stop-start)/CLOCKS_PER_SEC;
    start=clock(); 
    SHS(b,size);   //wywołanie od tablicy posortowanej malejąco 
    stop=clock();
    T_shell[2]=static_cast<double>(stop-start)/CLOCKS_PER_SEC;
    std::cout<<"SHELL SORT\n";
    std::cout<<"Tablica posortowana rosnąco:\n";
    for(int i=0;i<size;i++)
        std::cout<<a[i]<<" ";
    std::cout<<"\n\nCzas sortowania tablicy liczb losowych: "<<T_shell[0]<<'\n';
    std::cout<<"Czas sortowania tablicy posortowanej rosnąco: "<<T_shell[1]<<'\n';
    std::cout<<"Czas sortowania tablicy posortowanej malejąco: "<<T_shell[2]<<"\n";
    breakline;
}

void heapify(int *a, int N, int i)
{
    // Find largest among root, left child and right child
 
    // Initialize largest as root
    int largest = i;
 
    // left = 2*i + 1
    int left = 2 * i + 1;
 
    // right = 2*i + 2
    int right = 2 * i + 2;
 
    // If left child is larger than root
    if (left < N && a[left] > a[largest])
 
        largest = left;
 
    // If right child is larger than largest
    // so far
    if (right < N && a[right] > a[largest])
 
        largest = right;
 
    // Swap and continue heapifying if root is not largest
    // If largest is not root
    if (largest != i) {
 
        std::swap(a[i], a[largest]);
        // Recursively heapify the affected
        // sub-tree
        heapify(a, N, largest);
    }
}
 
// Main function to do heap sort
void HS(int *a,int n){
    // Build max heap
    for (int i=n/2-1;i>=0;i--)
        heapify(a,n,i);
    // Heap sort
    for (int i=n-1;i>=0;i--) {
        std::swap(a[0],a[i]);
        // Heapify root element to get highest element at
        // root again
        heapify(a,i,0);
    }
}
void Sort::heap_sort(){
    int a[size],b[size];
    std::copy(tab,tab+size,a);
    std::copy(tab,tab+size,b);
    clock_t start=clock();
    HS(a,size);
    clock_t stop=clock();
    T_heap[0]=static_cast<double>(stop-start)/CLOCKS_PER_SEC;
    start=clock(); 
    HS(asc,size);   //wywołanie od tablicy posortowaniej rosnąco
    stop=clock();
    T_heap[1]=static_cast<double>(stop-start)/CLOCKS_PER_SEC;
    start=clock(); 
    HS(b,size);   //wywołanie od tablicy posortowanej malejąco 
    stop=clock();
    T_heap[2]=static_cast<double>(stop-start)/CLOCKS_PER_SEC;
    std::cout<<"HEAP SORT\n";
    std::cout<<"Tablica posortowana rosnąco:\n";
    for(int i=0;i<size;i++)
        std::cout<<a[i]<<" ";
    std::cout<<"\n\nCzas sortowania tablicy liczb losowych: "<<T_heap[0]<<'\n';
    std::cout<<"Czas sortowania tablicy posortowanej rosnąco: "<<T_heap[1]<<'\n';
    std::cout<<"Czas sortowania tablicy posortowanej malejąco: "<<T_heap[2]<<"\n";
    breakline;
}