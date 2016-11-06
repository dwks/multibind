#!/bin/sh

./multi --nofork 0 &
sleep 2
./multi --nofork 1 &
sleep 2
./multi --nofork 2 &
sleep 2
./multi --nofork 3 &
sleep 2
./multi --nofork 4 &
sleep 2
