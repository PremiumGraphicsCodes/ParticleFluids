set HIZUKE=%date: =0%
set JIKOKU=%time: =0%

set yy=%HIZUKE:~0,4%
set mm=%HIZUKE:~5,2%
set dd=%HIZUKE:~8,2%
set name=FS%yy%%mm%%dd%
mkdir %name%
cd %name%
mkdir bin
cd ../
cp readme.txt %name%
cp -r Licenses %name%
cp x64/Release/*.dll %name%/bin
cp x64/Release/*.exe %name%/bin
powershell compress-archive %name% %name%.zip