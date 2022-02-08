#include <iostream>
#include "Sorts.hpp"

void printArray(int* array, int size);
void checkErrors(int size);

int main()
{
  std::cout << "Please, write the numbers you want to sort and and their quantity:" << '\n';
  int size;
  int sizeTwo;
  int sizeThree;
  {
    std::cout << "Quantity\n";
    std::cin >> size;
    checkErrors(size);
    std::cout << "Numbers\n";
    int array[size];
    for (int i = 0; i < size; ++i)
    {
      std::cin >> array[i];
      checkErrors(size);
    }
    try
    {
      std::cout << "Counting sort\n";
      printArray(array, size);
      countingSort(array, size);
      printArray(array, size);
    }
    catch (const std::logic_error &error)
    {
      std::cout << error.what() << '\n';
    }
    sorted(array, size);
  }
  {
    std::cout << "\nRadix sort\n";
    std::cout << "Quantity\n";
    std::cin >> sizeTwo;
    checkErrors(sizeTwo);
    std::cout << "Numbers\n";
    int arrayTwo[sizeTwo];
    for (int i = 0; i < sizeTwo; ++i)
    {
      std::cin >> arrayTwo[i];
      checkErrors(sizeTwo);
    }
    printArray(arrayTwo, sizeTwo);
    radixSort(arrayTwo, sizeTwo);
    printArray(arrayTwo, sizeTwo);
    sorted(arrayTwo, sizeTwo);
  }
  {
    std::cout << "\nBucket sort\n";
    std::cout << "Quantity\n";
    std::cin >> sizeThree;
    checkErrors(sizeThree);
    std::cout << "Numbers\n";
    int arrayThree[sizeThree];
    for (int i = 0; i < sizeThree; ++i)
    {
      std::cin >> arrayThree[i];
      checkErrors(sizeThree);
    }
    printArray(arrayThree, sizeThree);
    bucketSort(arrayThree, sizeThree);
    printArray(arrayThree, sizeThree);
    sorted(arrayThree, sizeThree);
  }
  return 0;
}

void printArray(int *array, int size)
{
  for (int i = 0; i < size; ++i)
  {
    std::cout << "[ " << array[i] << " ]";
  }
  std::cout << '\n';
}

void checkErrors(int size)
{
  if (size < 0)
  {
    throw std::invalid_argument("Size can't be less 0!");
  }
  if (std::cin.fail())
  {
    throw std::invalid_argument("You must write only integer numbers!");
  }
}
