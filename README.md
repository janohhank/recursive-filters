# RecursiveFilters
Recursive filter implementations which works on digital samples.

In signal processing, a recursive filter is a type of filter which re-uses one or more of its outputs as an input.

Inclues a makefile, tested in Debian Stretch and g++ 6.3.0.

### Already implemented filters:
Low-pass filter : https://en.wikipedia.org/wiki/Low-pass_filter

High-pass filter : https://en.wikipedia.org/wiki/High-pass_filter

### The sample example application output:

Original data: random normal distribution values in a histogram

![alt text](https://raw.githubusercontent.com/janohhank/RecursiveFilters/master/doc/raw-data.png)

Low-pass filtered data:

![alt text](https://raw.githubusercontent.com/janohhank/RecursiveFilters/master/doc/low-pass-filtered-data.png)

High-pass filtered data:

![alt text](https://raw.githubusercontent.com/janohhank/RecursiveFilters/master/doc/high-pass-filtered-data.png)
