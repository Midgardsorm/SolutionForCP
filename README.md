Build instruction:
First you need cmake (ver. 3.27), then from the main project folder run commands:

```
mkdir build
cd build
cmake ..
cmake --build .
cd Debug
```

After that you will have two applications:

1. ArithParsEval accepts expression in argument, but put it in double quotes, for example:
```
ArithParsEval "9 + 6-( 3 + 5)"
```

2. ArithParsEval_Test performs tests. Just run it in commmand line. Test cases are hardcoded in mainTest.cpp file.
```
ArithParsEval_Test
```
