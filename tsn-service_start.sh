echo "Running Coordinator"
./coordinator -p 9090 &
sleep 1s
echo "Running Servers on clusters 1,2,3"
./tsd -p 10000 -c 1 -s 1 &
sleep 1s
./tsd -p 10001 -c 1 -s 2 &
./tsd -p 20000 -c 2 -s 1 &
sleep 1s
./tsd -p 20001 -c 2 -s 2 &
./tsd -p 30000 -c 3 -s 1 &
sleep 1s
./tsd -p 30001 -c 3 -s 2 &

echo "Running synchronizers"
./synchronizer -n 1 -p 1234 &
./synchronizer -n 2 -p 1235 &
./synchronizer -n 3 -p 1236 &
