#include <iostream>
#include "Sorts.hpp"

void countingSort (int* array, int size)
{
  int maxNumber = 0;
  for (int i = 0; i < size; ++i)
  {
    if (array[i] < 0)
    {
      throw std::logic_error("Numbers in array must be more than 0.");
    }
    if (array[i] > maxNumber)
    {
      maxNumber = array[i];
    }
  }
  int tempArray[maxNumber + 1];
  for (int i = 0; i < maxNumber + 1; ++i)
  {
    tempArray[i] = 0;
  }
  for (int i = 0; i < size; ++i)
  {
    ++tempArray[array[i]];
  }
  int count = 0;
  for (int i = 0; i < maxNumber + 1; ++i)
  {
    for (int j = 0; j < tempArray[i]; ++j)
    {
      array[count++] = i;
    }
  }
}

void radixSort (int* array, int size)
{
  int max = array[0];
  for (int i = 1; i < size; i++)
  {
    if (array[i] > max)
    {
      max = array[i];
    }
  }
  int tempArray[size];
  int numSignificantDigit = 1;
  int maxNumber = max;
  while (maxNumber / numSignificantDigit > 0)
  {
    int bucket[10] = {0};
    for (int i = 0; i < size; ++i)
      bucket[(array[i] / numSignificantDigit) % 10]++;
    for (int i = 0; i < 10; ++i)
      bucket[i] += bucket[i - 1];
    for (int i = size - 1; i >= 0; --i)
      tempArray[--bucket[(array[i] / numSignificantDigit) % 10]] = array[i];
    for (int i = 0; i < size; ++i)
      array[i] = tempArray[i];
    numSignificantDigit *= 10;
  }
}

void bucketSort (int* array, int size)
{
  const int SIZE = 1000000000;
  int bucket[10][size+1];
  for(int i = 0; i < 10; ++i)
  {
    bucket[i][size] = 0;
  }
  for(int value = 1; value <= SIZE; value *= 10)
  {
    for(int i = 0; i < size; i++)
    {
      int digit = (array[i] / value) % 10;
      bucket[digit][bucket[digit][size]++] = array[i];
    }
    int index = 0;
    for(int i = 0; i < 10; ++i)
    {
      for(int j = 0; j < bucket[i][size]; ++j)
      {
        array[index++] = bucket[i][j];
      }
      bucket[i][size] = 0;
    }
  }
}

void sorted(int *array, int size)
{
  for (int i = 0; i < size - 1; ++i)
  {
    if (array[i] > array[i + 1])
    {
      std::cout << "Array is not ordered\n";
      return;
    }
  }
  std::cout << "Array is ordered\n";
}
