LOG="${7:-/dev/null}"
( if ./philo $2 $3 $4 $5 $6 >> $LOG; then echo $1 "\033[32;1mOK\033[0m"; else echo $1 "\033[31;1mKO\033[0m"; fi ) & if [ $1 -gt 1 ]; then $0 $(($1-1)) $2 $3 $4 $5 $6 $7; fi
wait
