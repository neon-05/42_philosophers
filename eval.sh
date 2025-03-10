c=100

RES=$(./test.sh $c 1 800 200 200 20)
echo test 1: $(printf '%s\n' "$RES" | grep -c OK) / $c survived "(expected 0)"

RES=$(./test.sh $c 5 800 200 200 20)
echo test 2: $(printf '%s\n' "$RES" | grep -c OK) / $c survived "(expected $c)"

RES=$(./test.sh $c 4 410 200 200 20)
echo test 3: $(printf '%s\n' "$RES" | grep -c OK) / $c survived "(expected $c)"

RES=$(./test.sh $c 4 310 200 100 20)
echo test 4: $(printf '%s\n' "$RES" | grep -c OK) / $c survived "(expected 0)"