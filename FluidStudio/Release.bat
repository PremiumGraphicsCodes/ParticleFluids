set HIZUKE=%date: =0%
set JIKOKU=%time: =0%

set yy=%HIZUKE:~0,4%
set mm=%HIZUKE:~5,2%
set dd=%HIZUKE:~8,2%
set name=FS%yy%%mm%%dd%
mkdir %name%
cp -r Licenses %name%
cp x64/Release/*.dll %name%
cp x64/Release/*.exe %name%
powershell compress-archive %name% %name%.zip