openssl enc -nosalt -aes-192-cbc -k secret -P > key192-4096.dat
echo "Beginning File Encryption"
set "tstart = %time%"
echo %tstart%
openssl enc -aes-192-cbc -in big.pdf -out big192-4096.pdf.enc -pass file:key192-4096.dat
set "tend = %time%"
echo %tend%
echo "File Encryption Done"
echo "Beginning Key Encryption"
set "tstart = %time%"
echo %tstart%
openssl rsautl -encrypt -inkey publicKey4096.pem -pubin -in key192-4096.dat -out key192-4096.dat.enc
set "tend = %time%"
echo %tend%
echo "Key Encryption Done"
move ./key192-4096.dat.enc ../receiver
move ./big192-4096.pdf.enc ../receiver
