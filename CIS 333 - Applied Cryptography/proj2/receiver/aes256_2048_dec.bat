echo "Beginning Key Decryption"
set "tstart = %time%"
echo %tstart%
openssl rsautl -decrypt -inkey privateKey2048.pem -in key256-2048.dat.enc -out key256-2048.dat
set "tend = %time%"
echo %tend%
echo "Key Decryption Done"
echo "Beginning File Decryption"
set "tstart = %time%"
echo %tstart%
openssl enc -d -aes-256-cbc -in big256-2048.pdf.enc -out big256-2048-dec.pdf -pass file:key256-2048.dat
set "tend = %time%"
echo %tend%
echo "File Decryption Done"
