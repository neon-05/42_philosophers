RES=$(./test.sh $1 1 800 200 200 10)
echo test 1: $(printf '%s\n' "$RES" | grep -c OK) / $1 survived

RES=$(./test.sh $1 5 800 200 200 10)
echo test 2: $(printf '%s\n' "$RES" | grep -c OK) / $1 survived

RES=$(./test.sh $1 4 410 200 200 10)
echo test 3: $(printf '%s\n' "$RES" | grep -c OK) / $1 survived

RES=$(./test.sh $1 4 310 200 100 10)
echo test 4: $(printf '%s\n' "$RES" | grep -c OK) / $1 survived