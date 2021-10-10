@echo Deleting Folders

set folder="%cd%\build\"
IF EXIST %folder% (
	cd /d %folder%
	for /F "delims=" %%i in ('dir /b') do (rmdir "%%i" /s/q || del "%%i" /s/q)
)

@echo Complete!
pause