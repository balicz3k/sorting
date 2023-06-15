#include <iostream>
#include <string>

void IS(int *a,int n);
void SS(int *a,int n);
void BS(int *a,int n);
void QS(int *a,int p,int k);
void SHS(int *a,int n);
void HS(int *a,int n);
bool SortDSC(int a,int b);

class Sort{
    double T_insert[3],T_selection[3],T_bubble[3];
    double T_quick[3],T_shell[3],T_heap[3];
    public:
    int size,*tab,*asc,*dsc;
    Sort();
    ~Sort();
    void MakeFile();
    //I group 
    void insertion_sort();
    void selection_sort();
    void bubble_sort();
    //II group
    void quick_sort();
    void shell_sort();
    void heap_sort();
};