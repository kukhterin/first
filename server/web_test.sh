SERVER="10.31.36.250"
PORT="80"
REQUESTS="1000"
TIMEOUT="15"
LOGS_DIR="logs"

rm -rf ./${LOGS_DIR}
mkdir -p $LOGS_DIR

echo "run $REQUESTS HTTP GET requests to $SERVER:$PORT..."
for i in `seq 1 $REQUESTS`; do
  (sleep 3; printf 'GET /index.html HTTP/1.0\r\n\r\n') | nc -w $TIMEOUT $SERVER $PORT > $LOGS_DIR/log_$i.txt 2>&1&
done

echo "sleeping for ${TIMEOUT}s..."
sleep $TIMEOUT

NON_EMPTY=$(find $LOGS_DIR -not -empty -name '*.txt' | wc -l)
echo "got $NON_EMPTY/$REQUESTS non-empty answers"
