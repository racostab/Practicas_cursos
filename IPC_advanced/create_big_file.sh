dd if=/dev/zero of=500kib-file bs=1024 count=500
dd if=/dev/zero of=800mib-file bs=1048576 count=800
dd if=/dev/zero of=3gib-file bs=1073741824 count=3
dd if=/dev/zero of=100kb-file bs=1000 count=100
dd if=/dev/zero of=600mb-file bs=1000000 count=600
dd if=/dev/zero of=2gb-file bs=1000000000 count=2
ls -lh

yes "1234567890" | head -c 100 > test.file
yes "1234567890" | head -c 524288000 > 500MB_file.txt
yes "1234567890" | head -c 1073741824 > 1GB_file.txt

# En linux
yes "1234567890" | head -c 100KB > test.file

# Contar caracteres o palabras
grep -o 0 1GB_file.txt | wc -l
