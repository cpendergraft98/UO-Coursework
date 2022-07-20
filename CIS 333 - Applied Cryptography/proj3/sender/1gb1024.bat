echo "Creating Msg"
fsutil file createnew msg.txt 1000000000
echo "Msg Created"
echo "Signing Message"
set "tstart = %time%"
echo %tstart%
openssl dgst -sha256 -sign privateKey1024.pem -out sig.bin msg.txt
set "tend = %time%"
echo %tend%
echo "Message Signing Done"
echo "Moving Files and Switching Folders"
move ./msg.txt ../receiver
move ./sig.bin ../receiver
cd ../receiver
echo "Verifying Data"
set "tstart = %time%"
echo %tstart%
openssl dgst -sha256 -verify publicKey1024.pem -signature sig.bin msg.txt
set "tend = %time%"
echo %tend%
echo "Data Verification Done, Removing Files"
del msg.txt
del sig.bin
echo "Returning to Sender Folder"
cd ../sender
