C++ lowess
==========

A pure C++ implementation of the lowess algorithm. For more information, see
the following publication:


Cleveland, W. S. (1981) LOWESS: A program for smoothing scatterplots by robust
locally weighted regression. The American Statistician 35, 54.


In short, the algorithm performs locally-weighted polynomial regression in two
dimensions, which leads to a smoothing of the data. This is useful in the
presence of noise in the data. 

The algorithm uses a weighted regression of the closest points around x to make
a prediction of the y-value at the position x. To speed up the calculation, the
regression is only calculated at a subset of the points.

Installation
============

The algorithm is contained in a single header file in
`include/CppLowess/Lowess.h` and can be included directly in your C++ project.
You can then instantiate an object of type `TemplatedLowess` to call the lowess
function. The template parameter are the container and the value type used:

````
CppLowess::TemplatedLowess< std::vector<double>, double > dlowess;
CppLowess::TemplatedLowess< std::vector<float>, float >  flowess;
CppLowess::TemplatedLowess< TestContainer, double > testlowess;
````

here, STL containers as well as compatible classes can be used as template arguments.

Running tests
=============

To build and run the tests, you can do the following after download

````
cmake .
make
./testLowess
````

Python bindings
===============

The folder `src/python` contains Python bindings to the C++ code. To build and test them, please go to this folder and run 

````
python setup.py build_ext --inplace
python nosetests testLowess.py 
````

this has been tested with Python version 2.7 and 3.2. It requires the Python
development headers as well as [Cython](http://cython.org/).

Licence
=======

The code is available under the 3 clause BSD licence, see the LICENCE file

