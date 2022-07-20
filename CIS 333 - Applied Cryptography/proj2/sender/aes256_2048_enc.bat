openssl enc -nosalt -aes-256-cbc -k secret -P > key256-2048.dat
echo "Beginning File Encryption"
set "tstart = %time%"
echo %tstart%
openssl enc -aes-256-cbc -in big.pdf -out big256-2048.pdf.enc -pass file:key256-2048.dat 
set "tend = %time%"
echo %tend%
echo "File Encryption Done"
echo "Beginning Key Encryption"
set "tstart = %time%"
echo %tstart%
openssl rsautl -encrypt -inkey publicKey2048.pem -pubin -in key256-2048.dat -out key256-2048.dat.enc
set "tend = %time%"
echo %tend%
echo "Key Encryption Done"
move ./key256-2048.dat.enc ../receiver
move ./big256-2048.pdf.enc ../receiver
