./coordinator -p 9090
./tsd -c 1 -s 1 -h localhost -k 9090 -p 10000
./tsd  -c 2 -s 1 -h localhost -k 9090 -p 10001
./tsc -h localhost -k 9090 -u 1
./tsc -h localhost -k 9090 -u 2
