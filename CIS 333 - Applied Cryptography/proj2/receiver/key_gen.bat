openssl genrsa -out privateKey1024.pem 1024
openssl genrsa -out privateKey2048.pem 2048
openssl genrsa -out privateKey4096.pem 4096
openssl rsa -in privateKey1024.pem -pubout -out publicKey1024.pem
openssl rsa -in privateKey2048.pem -pubout -out publicKey2048.pem
openssl rsa -in privateKey4096.pem -pubout -out publicKey4096.pem
move ./publicKey1024.pem ../sender
move ./publicKey2048.pem ../sender
move ./publicKey4096.pem ../sender
