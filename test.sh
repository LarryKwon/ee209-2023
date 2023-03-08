#!/bin/bash
./wc209 < ./tests/input/sample01.txt > ./tests/output/output01.txt
diff tests/answer/sample01.stdout tests/output/output01.txt

./wc209 < ./tests/input/sample02.txt > ./tests/output/output02.txt
diff tests/answer/sample02.stdout tests/output/output02.txt

./wc209 < ./tests/input/sample03.txt > ./tests/output/output03.txt
diff tests/answer/sample03.stdout tests/output/output03.txt

./wc209 < ./tests/input/sample04.txt > ./tests/output/output04.txt
diff tests/answer/sample04.stdout tests/output/output04.txt

./wc209 < ./tests/input/sample05.txt > ./tests/output/output05.txt
diff tests/answer/sample05.stdout tests/output/output05.txt

./wc209 < ./tests/input/sample06.txt > ./tests/output/output06.txt
diff tests/answer/sample06.stdout tests/output/output06.txt

./wc209 < ./tests/input/sample07.txt > ./tests/output/output07.txt
diff tests/answer/sample07.stdout tests/output/output07.txt

./wc209 < ./tests/input/sample08.txt > ./tests/output/output08.txt
diff tests/answer/sample08.stdout tests/output/output08.txt

./wc209 < ./tests/input/sample09.txt > ./tests/output/output09.txt
diff tests/answer/sample09.stdout tests/output/output09.txt

./wc209 < ./tests/input/sample10.txt > ./tests/output/output10.txt
diff tests/answer/sample10.stdout tests/output/output10.txt

./wc209 < ./tests/input/sample11.txt > ./tests/output/output11.txt
diff tests/answer/sample11.stdout tests/output/output11.txt

./wc209 < ./tests/input/sample12.txt > ./tests/output/output12.txt
diff tests/answer/sample12.stdout tests/output/output12.txt