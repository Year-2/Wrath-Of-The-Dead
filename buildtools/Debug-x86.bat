@echo Creating Folders
mkdir %cd%\build\Debug\

@echo Copying libraries
xcopy "%cd%\dlls\x86\*.*"  "%cd%\build\Debug"

@echo Complete!