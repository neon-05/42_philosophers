( ./philo $2 $3 $4 $5 $6 | grep died || echo $1 good) & if [ $1 -gt 0 ]; then $0 $(($1-1)) $2 $3 $4 $5 $6; fi
