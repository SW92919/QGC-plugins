@echo off
echo Running code quality checks...

:: Check if tools are available
where clang-format >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo Warning: clang-format not found
) else (
    echo Running clang-format...
    for /r src %%f in (*.cpp *.h) do clang-format -i "%%f"
    for /r plugins %%f in (*.cpp *.h) do clang-format -i "%%f"
)

where cppcheck >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo Warning: cppcheck not found
) else (
    echo Running cppcheck...
    cppcheck --enable=all --inconclusive src/ plugins/ tests/
)

echo Code quality check completed.
pause
