mknod /dev/card c 255 0
echo -n gen_rand_id >/dev/card
echo -n mem_read > /dev/read
hexdump /dev/card
