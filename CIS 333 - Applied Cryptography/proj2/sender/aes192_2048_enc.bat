openssl enc -nosalt -aes-192-cbc -k secret -P > key192-2048.dat
echo "Beginning File Encryption"
set "tstart = %time%"
echo %tstart%
openssl enc -aes-192-cbc -in big.pdf -out big192-2048.pdf.enc -pass file:key192-2048.dat
set "tend = %time%"
echo %tend%
echo "File Encryption Done"
echo "Beginning Key Encryption"
set "tstart = %time%"
echo %tstart%
openssl rsautl -encrypt -inkey publicKey2048.pem -pubin -in key192-2048.dat -out key192-2048.dat.enc
set "tend = %time%"
echo %tend%
echo "Key Encryption Done"
move ./key192-2048.dat.enc ../receiver
move ./big192-2048.pdf.enc ../receiver
