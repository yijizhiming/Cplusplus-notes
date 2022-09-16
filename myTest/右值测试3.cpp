#include <iostream>
#include <vector>

std::vector<int>&& return_vector(void) {
    std::vector<int> tmp{ 1,2,3,4,5 };
    return std::move(tmp);
}

int main03()
{
    
    std::vector<int>&& rval_ref = return_vector();

    return 0;
}