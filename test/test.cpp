/*-
 * Provided to compare the default allocator to MemoryPool
 *
 * Check out StackAlloc.h for a stack implementation that takes an allocator as
 * a template argument. This may give you some idea about how to use MemoryPool.
 *
 * This code basically creates two stacks: one using the default allocator and
 * one using the MemoryPool allocator. It pushes a bunch of objects in them and
 * then pops them out. We repeat the process several times and time how long
 * this takes for each of the stacks.
 *
 * Do not forget to turn on optimizations (use -O2 or -O3 for GCC). This is a
 * benchmark, we want inlined code.
 */

#include <iostream>
#include <cassert>
#include <time.h>
#include <vector>

#include "MemoryPool.h"
#include "StackAlloc.h"

/* Adjust these values depending on how much you trust your computer */
#define ELEMS 1000000
#define REPS 50

int main()
{
  clock_t start;

  std::cout << "Provided to compare the default allocator to MemoryPool on stack.\n";

  /* Use the default allocator */
  StackAlloc<int, std::allocator<int> > stackDefault;
  start = clock();
  for (int j = 0; j < REPS; j++)
  {
    assert(stackDefault.empty());
    for (int i = 0; i < ELEMS / 4; i++) {
      // Unroll to time the actual code and not the loop
      stackDefault.push(i);
      stackDefault.push(i);
      stackDefault.push(i);
      stackDefault.push(i);
    }
    for (int i = 0; i < ELEMS / 4; i++) {
      // Unroll to time the actual code and not the loop
      stackDefault.pop();
      stackDefault.pop();
      stackDefault.pop();
      stackDefault.pop();
    }
  }
  std::cout << "Default Allocator Time: ";
  std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n";

  /* Use MemoryPool */
  StackAlloc<int, MemoryPool<int> > stackPool;
  start = clock();
  for (int j = 0; j < REPS; j++)
  {
    assert(stackPool.empty());
    for (int i = 0; i < ELEMS / 4; i++) {
      // Unroll to time the actual code and not the loop
      stackPool.push(i);
      stackPool.push(i);
      stackPool.push(i);
      stackPool.push(i);
    }
    for (int i = 0; i < ELEMS / 4; i++) {
      // Unroll to time the actual code and not the loop
      stackPool.pop();
      stackPool.pop();
      stackPool.pop();
      stackPool.pop();
    }
  }
  std::cout << "MemoryPool Allocator Time: ";
  std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n";


  std::cout << "Here is a secret: the best way of implementing a stack"
            " is a dynamic array.\n\n";

  std::cout << "Provided to compare the default allocator to MemoryPool on vector.\n";

  /* Use the default allocator */
  std::vector<int> vectorDefault;
  start = clock();
  for (int j = 0; j < REPS; j++)
  {
    assert(vectorDefault.empty());
    for (int i = 0; i < ELEMS / 4; i++) {
      // Unroll to time the actual code and not the loop
      vectorDefault.push_back(i);
      vectorDefault.push_back(i);
      vectorDefault.push_back(i);
      vectorDefault.push_back(i);
    }
    for (int i = 0; i < ELEMS / 4; i++) {
      // Unroll to time the actual code and not the loop
      vectorDefault.pop_back();
      vectorDefault.pop_back();
      vectorDefault.pop_back();
      vectorDefault.pop_back();
    }
  }
  std::cout << "Default Allocator Vector Time: ";
  std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n";

  /* Use MemoryPool */
  std::vector<int, MemoryPool<int>> vectorPool;
  start = clock();
  for (int j = 0; j < REPS; j++)
  {
    assert(vectorPool.empty());
    for (int i = 0; i < ELEMS / 4; i++) {
      // Unroll to time the actual code and not the loop
      vectorPool.push_back(i);
      vectorPool.push_back(i);
      vectorPool.push_back(i);
      vectorPool.push_back(i);
    }
    for (int i = 0; i < ELEMS / 4; i++) {
      // Unroll to time the actual code and not the loop
      vectorPool.pop_back();
      vectorPool.pop_back();
      vectorPool.pop_back();
      vectorPool.pop_back();
    }
  }
  std::cout << "MemoryPool Allocator Vector Time: ";
  std::cout << (((double)clock() - start) / CLOCKS_PER_SEC) << "\n";

  std::cout << "The vector implementation will probably be faster.\n\n";
  std::cout << "MemoryPool still has a lot of uses though. Any type of tree"
            " and when you have multiple linked lists are some examples (they"
            " can all share the same memory pool).\n";
  std::cout << "max size of MemoryPool is " << MemoryPool<int>().max_size() << "\n";

  return 0;
}
