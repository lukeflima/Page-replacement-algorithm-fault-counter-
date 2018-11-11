# Page replacement algorithm fault counter  
A simulation of page replacement algorithm that counts how many faults occurred.  
* First In First Out (FIFO)  
* Optimal Algorithm (OTM)  
* Least Recently Used (LRU)  
## Usage  
The program use a input file (input.txt) that is structured as followed:  
In each line is a page id that will be accessed.  
### Input example  
```
4
1
2
3
4
1
2
5
1
2
3
4
5
```
### Output example
The output (output.txt) is the list of algorithm names followed by the number of faults occurred.  
```
FIFO 10
OTM 6
LRU 8

``` 
