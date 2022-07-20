echo "Beginning Key Decryption"
set "tstart = %time%"
echo %tstart%
openssl rsautl -decrypt -inkey privateKey2048.pem -in key192-2048.dat.enc -out key192-2048.dat
set "tend = %time%"
echo %tend%
echo "Key Decryption Done"
echo "Beginning File Decryption"
set "tstart = %time%"
echo %tstart%
openssl enc -d -aes-192-cbc -in big192-2048.pdf.enc -out big192-2048-dec.pdf -pass file:key192-2048.dat
set "tend = %time%"
echo %tend%
echo "File Decryption Done"
