# Morton Order Traverse

## Introduction
This repository is a implementation of morton order traversal in a matrix.

## Morton Order
> In mathematical analysis and computer science, functions which are Z-order, Lebesgue curve, Morton order or Morton code map multidimensional data to one dimension while preserving locality of the data points. It was introduced in 1966 by Guy Macdonald Morton.[1] The z-value of a point in multidimensions is simply calculated by interleaving the binary representations of its coordinate values. Once the data are sorted into this ordering, any one-dimensional data structure can be used such as binary search trees, B-trees, skip lists or (with low significant bits truncated) hash tables. The resulting ordering can equivalently be described as the order one would get from a depth-first traversal of a quadtree.

From Wikipedia - https://en.wikipedia.org/wiki/Z-order_curve

## Usage
1. Clone the repository

        git clone https://github.com/Highe-Stark/morton-order-traverse.git
2. Change directory into repository

        cd morton-order-traverse
3. Build
        
        make
4. Let's traverse

    Print Usage

        ./morton_traverse -h
    
    Traverse the matrix in \<matrix file\>

        ./morton_traverse -f <matrix file>
5. Test

        ./test.sh

## Reminder
* gen_matrix.py

gen_matrix.py in src/ can generate a matrix with M rows and N columns, and put the generated matrix in the src/res directory.
* matrix file

Currently, there are a few matrix file in the src/res directory with name format in matrix-M-N.txt. If you want to traverse other matrix file, note that the matrix file content should satisfy below format

M N

\<matrix content\>
