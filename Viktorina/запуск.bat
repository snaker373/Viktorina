@echo off
chcp 65001 >nul
title 🎯 Вікторина 2024
echo Компіляція...
g++ -std=c++11 вікторина.cpp -o вікторина.exe
if %errorlevel% neq 0 (
    echo Помилка компіляції!
    pause
    exit /b 1
)
echo Запуск вікторини...
вікторина.exe
