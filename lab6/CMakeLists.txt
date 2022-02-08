cmake_minimum_required(VERSION 3.17)
project(lab6)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab6 main.cpp
        BinarySearchTree.hpp
        QueueList.hpp Queue.hpp
        StackList.hpp Stack.hpp
        QueueException.hpp StackException.hpp)