# FT C++

## Getting started

We've set up a example file **prog.cpp** in which you can find such interesting things

### Includes

```c++
#include "fft.h"
```

### Use of cplx number

Since Fourier transform deals with cplx numbers, we've also added a `complex` structure.
`typedef struct cplx;`

each cplx numbers is defined with :

```c++
cplx.re; (double)
cplx.im; (double)
cplx.abs;(double)
cplx.arg;(double)
```

you create a cplx number like this :
`cplx numberOne(re,im,abs,arg);`
And if you don't specify either of carthesian coordonates or polar coordonates, the missing informations are auto-adjusted :
`cplx numberTwo(1,1,0,0);` automatically set `numberTwo.abs=sqrt(2)` and `numberTwo.arg=pi/4`
`cplx numberTwo(0,0,sqrt(2),pi/4);` automatically set `numberTwo.re=1` and `numberTwo.im=1`
You can perform operations on thoses number such as :

```c++
cplx n3 = numberOne + numberTwo;
cplx n3 = numberOne - numberTwo;
cplx n3 = numberOne * numberTwo;
cplx n3 = numberOne / numberTwo;
```
## Fourier Transform

The operation works with real numbers : `real numbers $\rightarrow$ cplx numbers`

```c++
std::vector<double> v={0,0,0,1,1,1,0,0,0,1,1,1}; //in the case of a rectangular signal
std::vector<cplx> spectre=fft(&v);
```
Once you've done that, you can extract amplitude spectre and argument spectre by doing:
```c++
sdt::vector<double>abs=getAbs(&spectre);
std::vector<double>arg=getArg(&spectre);
```

### Filtering

Basic filtering :
```c++
std::vector<cplx>filteredSpectre = filter(&spectre,Fc,Fe,LOW_PASS);
```
`Fc` is the cut frequency
`Fe` the sampling frequency
`HIGH_PASS` and `LOW_PASS` are the two directives which allow this filter doing his job

### Reverse Fast Fourier Transform (IFFT)
All you have to do is :
```c++
std::vector<double>w = ifft(&FilteredSpectre)
```

## Printing curves

you may find a courbes.py file (courbes = curves in french), this is a little python script that allows you to plot every file.txt in the **textes** folder. It requires the installation of matplotlib.
The `c++` methods to create those files automatically is written in **prog.cpp** (so is the methods which prints the results on the command prompt)

Example :
![image](https://raw.githubusercontent.com/Pandrah/fft-c-custom/refs/heads/main/exemple.png)
Thoses curves are obtained directly from the prog.cpp file
