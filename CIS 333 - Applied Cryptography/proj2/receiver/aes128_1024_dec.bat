echo "Beginning Key Decryption"
set "tstart = %time%"
echo %tstart%
openssl rsautl -decrypt -inkey privateKey1024.pem -in key128-1024.dat.enc -out key128-1024.dat
set "tend = %time%"
echo %tend%
echo "Key Decryption Done"
echo "Beginning File Decryption"
set "tstart = %time%"
echo %tstart%
openssl enc -d -aes-128-cbc -in big128-1024.pdf.enc -out big128-1024-dec.pdf -pass file:key128-1024.dat
set "tend = %time%"
echo %tend%
echo "File Decryption Done"
