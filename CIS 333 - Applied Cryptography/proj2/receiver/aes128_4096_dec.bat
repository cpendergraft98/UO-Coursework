echo "Beginning Key Decryption"
set "tstart = %time%"
echo %tstart%
openssl rsautl -decrypt -inkey privateKey4096.pem -in key128-4096.dat.enc -out key128-4096.dat
set "tend = %time%"
echo %tend%
echo "Key Decryption Done"
echo "Beginning File Decryption"
set "tstart = %time%"
echo %tstart%
openssl enc -d -aes-128-cbc -in big128-4096.pdf.enc -out big128-4096-dec.pdf -pass file:key128-4096.dat
set "tend = %time%"
echo %tend%
echo "File Decryption Done"
