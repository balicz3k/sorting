#include <iostream>
#include <fstream>
#include "sort.hpp"

int main(){
    Sort s;
    s.insertion_sort();
    s.selection_sort();
    s.bubble_sort();
    s.quick_sort();
    s.shell_sort();
    s.heap_sort();
}