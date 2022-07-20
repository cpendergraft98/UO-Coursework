openssl enc -nosalt -aes-192-cbc -k secret -P > key192-1024.dat
echo "Beginning File Encryption"
set "tstart = %time%"
echo %tstart%
openssl enc -aes-192-cbc -in big.pdf -out big192-1024.pdf.enc -pass file:key192-1024.dat
set "tend = %time%"
echo %tend%
echo "File Encryption Done"
echo "Beginning Key Encryption"
set "tstart = %time%"
echo %tstart%
openssl rsautl -encrypt -inkey publicKey1024.pem -pubin -in key192-1024.dat -out key192-1024.dat.enc
set "tend = %time%"
echo %tend%
echo "Key Encryption Done"
move ./key192-1024.dat.enc ../receiver
move ./big192-1024.pdf.enc ../receiver
