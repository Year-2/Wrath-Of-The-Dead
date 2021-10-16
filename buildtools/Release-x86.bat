@echo Creating Folders
mkdir %cd%\build\Release\

@echo Copying libraries
xcopy "%cd%\dlls\x86\*.*"  "%cd%\build\Release

@echo Complete!