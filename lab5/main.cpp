#include <iostream>
#include "Queue.hpp"
#include "QueueArray.hpp"
#include "QueueList.hpp"

int main()
{
  QueueArray<int> queue;
  queue.insertQueue(5);
  queue.insertQueue(6);
  queue.insertQueue(2);
  queue.insertQueue(8);
  queue.insertQueue(10);

  QueueArray<int>queueCopy(queue);

  std::cout << "-------------------First queue (Array)-------------------\n";
  std::cout << queue.deQueue() << ' ' << queue.deQueue() << ' ' << queue.deQueue() << ' '
            << queue.deQueue() << ' ' << queue.deQueue() << '\n';

  std::cout << "-------------------Second queue (Array) copy first-------------------\n";
  std::cout << queueCopy.deQueue() << ' ' << queueCopy.deQueue() << ' ' << queueCopy.deQueue() << ' '
            << queueCopy.deQueue() << ' ' << queueCopy.deQueue() << '\n';

  QueueList<int> queueTwo;
  queueTwo.insertQueue(2);
  queueTwo.insertQueue(5);
  queueTwo.insertQueue(11);
  queueTwo.insertQueue(-7);

  QueueList<int> queueTwoCopy(queueTwo);

  std::cout << "-------------------First queue (List)-------------------\n";
  std::cout << queueTwo.deQueue() << ' ' << queueTwo.deQueue() << ' ' << queueTwo.deQueue() << ' '
            << ' ' << queueTwo.deQueue() << '\n';

  std::cout << "-------------------Second queue (List) copy first-------------------\n";
  std::cout << queueTwoCopy.deQueue() << ' ' << queueTwoCopy.deQueue() << ' ' << queueTwoCopy.deQueue() << ' '
            << ' ' << queueTwoCopy.deQueue() << '\n';

  return 0;
}
