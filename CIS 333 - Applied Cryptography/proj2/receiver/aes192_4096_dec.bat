echo "Beginning Key Decryption"
set "tstart = %time%"
echo %tstart%
openssl rsautl -decrypt -inkey privateKey4096.pem -in key192-4096.dat.enc -out key192-4096.dat
set "tend = %time%"
echo %tend%
echo "Key Decryption Done"
echo "Beginning File Decryption"
set "tstart = %time%"
echo %tstart%
openssl enc -d -aes-192-cbc -in big192-4096.pdf.enc -out big192-4096-dec.pdf -pass file:key192-4096.dat
set "tend = %time%"
echo %tend%
echo "File Decryption Done"
