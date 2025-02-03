@ECHO OFF
TITLE UEProjectClearUtil
echo=
echo=
echo 清理虚幻工程项目
echo ------------------------------------------------------------------
echo=
echo=
echo 当前项目路径:%cd%
echo=
rem 先统计该路径下所有信息
dir /A/D /B
echo=
echo=
rem 虚幻项目文件
echo ------------------------------------------------------------------
echo 清理项目文件夹
call :DeleteDirectory ".vs"
call :DeleteDirectory "Build"
call :DeleteDirectory "Binaries"
call :DeleteDirectory "DerivedDataCache"
call :DeleteDirectory "Intermediate"
call :DeleteDirectory "Saved"
echo ------------------------------------------------------------------
echo 清理项目文件
call :DeleteFile ".vsconfig"
call :DeleteFile "*.sln"
echo ------------------------------------------------------------------
echo 清理项目插件文件夹
for /d %%i in (Plugins\*) do ( 
call :DeleteDirectory  %%i\Binaries
call :DeleteDirectory  %%i\Intermediate
)
echo=
echo=

echo ------------------------------------------------------------------
echo=
echo 当前项目路径:%cd%
echo=
dir /A/D /B
echo=
echo=
echo ------------------------------------------------------------------
echo 清理完成
echo=
echo=


pause

goto :eof

:DeleteFile
if exist %~1 (
echo DeleteFile %~1
del /s /q %~1
)
goto :eof

:DeleteDirectory
if exist %~1 (
echo DeleteDirectory %~1
rd /s /q %~1
)
goto :eof
