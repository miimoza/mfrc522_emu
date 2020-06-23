mknod /dev/card c 255 0
echo -n mem_write:5:hello > /dev/card
echo -n mem_read > /dev/read
cat /dev/card
