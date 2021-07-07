#include "histogram.h"
void find_minmax(const vector<double>& numbers, double& min, double& max)
{
    if (numbers.size() >0)
    {
        min = numbers[0];
        max = numbers[0];
        for (double number : numbers)
        {
            if (number<min)
            {
                min = number;
            }
            if (number>max)
            {
                max = number;
            }
        }
    }
}

double domashnee(int IMAGE_WIDTH, int BLOCK_WIDTH, size_t number_count)
{
    while (IMAGE_WIDTH<70 || IMAGE_WIDTH>800 ||IMAGE_WIDTH<(number_count/3.0*BLOCK_WIDTH))
    {
        if (IMAGE_WIDTH<70)
            cout<<"Vvedite shirinu zanovo, tk ona menshe 70. ";
        if (IMAGE_WIDTH>800)
            cout<<"Vvedite shirinu zanovo, tk ona bolshe 800. ";
        if (IMAGE_WIDTH<(number_count/3.0*BLOCK_WIDTH))
            cout<<"Vvedite shirinu zanovo, tk ona menshe treti kolichestva, umnozhennih na BLOCK_WIDTH. ";
        cout<<"Novoe znachenie shirini: ";
        cin>>IMAGE_WIDTH;
    }
    return IMAGE_WIDTH;
}




