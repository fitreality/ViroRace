@echo off
call :sub > %temp%\\output.txt
exit /B 0
:sub
echo ============================================= 
echo         DLL for LifeFitness 
echo ============================================= 
net session >nul 2>&1
    if %errorLevel% == 0 (
        echo Success: Administrative permissions confirmed. 
    ) else (
        echo Failure: Current permissions inadequate. 
	echo ============================================= 
	exit /B 0
    )
set mypath=%~dp0
set dllPath=%mypath:~0,-1%
%Windir%\Microsoft.NET\Framework64\v4.0.30319\regasm /u "%dllPath%\DLLDirectory\VRMachineComm.dll" 
%Windir%\Microsoft.NET\Framework64\v4.0.30319\regasm "%dllPath%\DLLDirectory\VRMachineComm.dll" /tlb /codebase 
echo ============================================= 
