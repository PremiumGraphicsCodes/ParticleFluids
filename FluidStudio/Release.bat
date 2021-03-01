mkdir FSRelease
cp -r Licenses FSRelease
cp x64/Release/*.dll FSRelease
cp x64/Release/*.exe FSRelease
powershell compress-archive FSRelease FSRelease.zip