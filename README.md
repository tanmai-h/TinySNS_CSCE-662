### MP2.1 CSCE 662 Texas A&M
#### Name: Tanmai Harish
#### UIN:  434007349
Compile the code using the provided makefile:

    make

To clear all genereated and compiled files in the directory:
   
    make clean

To clear all .txt files (follower info, timelines, etc)

    make reset

### For Test Cases
To run coordinator, server, synchronizers, client (Run on different terminals)
```bash
## Coordinator
./coordinator -p 9090
## Cluster 1 Servers
./tsd -p 10000 -k 9090 -c 1 -s 1
./tsd -p 10001 -k 9090 -c 1 -s 2
## Cluster 2 Servers
./tsd -p 20000 -k 9090 -c 2 -s 1
./tsd -p 20001 -k 9090 -c 2 -s 2
## Cluster 3 Servers
./tsd -p 30000 -k 9090 -c 3 -s 1
./tsd -p 30001 -k 9090 -c 3 -s 2

## Synchronizers
./synchronizer -n 1 -j 9090 -p 1234
./synchronizer -n 2 -j 9090 -p 1235
./synchronizer -n 3 -j 9090 -p 1236
```

### NOTE
* After Test Case 1 (sanity check), run `make reset`

### Using the startup script
```bash
make
bash tsn-service_start.sh
```
1. Wait 60s
2. Start the clients for the test cases
3. After test case 1, in another terminal run `make reset`
4. Start the clients for test case 2
5. To kill the master server in cluster 2
```
ps aux | grep “p 20000”  # see the process id
```
6. kill the master server process by typing 
```
kill -9 processId
```
7. ctrl+c to kill the clients when required.
