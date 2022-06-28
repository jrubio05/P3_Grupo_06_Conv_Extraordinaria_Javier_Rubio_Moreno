::EJECUTAR CON "Developer Command Prompt for VS"

:: Construir Motor
cd MotorOla
call MotorOla.bat
cd ..

:: Generar .dll y .lib
msbuild JuegoZombis_Solution.sln -p:Configuration=Release -noLogo -m

:: Limpieza de cara a entrega
cd MotorOla
call DespejarDirExes.bat
cd ..
