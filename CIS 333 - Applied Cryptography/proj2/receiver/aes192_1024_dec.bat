echo "Beginning Key Decryption"
set "tstart = %time%"
echo %tstart%
openssl rsautl -decrypt -inkey privateKey1024.pem -in key192-1024.dat.enc -out key192-1024.dat
set "tend = %time%"
echo %tend%
echo "Key Decryption Done"
echo "Beginning File Decryption"
set "tstart = %time%"
echo %tstart%
openssl enc -d -aes-192-cbc -in big192-1024.pdf.enc -out big192-1024-dec.pdf -pass file:key192-1024.dat
set "tend = %time%"
echo %tend%
echo "File Decryption Done"
