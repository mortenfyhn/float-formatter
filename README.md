# float-formatter

[![Build Status](https://semaphoreci.com/api/v1/mortenfyhn/float-formatter/branches/master/badge.svg)](https://semaphoreci.com/mortenfyhn/float-formatter)

Easily print floating point numbers in a nice way such as
```
       1      .      .      .
     1.2      1      .      .
  1.1111  -2e22      1      .
  1.2e11  3e-33 -4e-44      1
```
instead of
```
  1 0 0 0
  1.2 1 0 0
  1.11111 -2.34e+22 1 0
  1.23e+11 3.45e-33 -4.56e-44 1
```
