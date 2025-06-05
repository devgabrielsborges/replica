@echo off
REM install.bat
REM Script to install the Replica project and its dependencies on Windows.
REM Assumes the script is run from the root of the cloned project directory.

setlocal enabledelayedexpansion

REM --- Configuration ---
set PROJECT_NAME=rpc
set FINAL_COMMAND_NAME=rpc
set INSTALL_DIR=%USERPROFILE%\.local\bin
set SCRIPT_DIR=%~dp0

REM --- Helper Functions ---
goto :main

:command_exists
where %1 >nul 2>&1
exit /b %errorlevel%

:print_success
echo [92m✓ %~1[0m
exit /b 0

:print_warning
echo [93mWARN: %~1[0m
exit /b 0

:print_error
echo [91mERROR: %~1[0m >&2
exit /b 0

:print_info
echo [94mINFO: %~1[0m
exit /b 0

:main
REM --- Ensure running from project root ---
cd /d "%SCRIPT_DIR%"
call :print_info "Running installation from project directory: %SCRIPT_DIR%"

REM --- Dependency Checks and Installation ---
call :print_info "Checking dependencies..."

REM Check for Git
call :command_exists git
if !errorlevel! neq 0 (
    call :print_warning "Git is not installed. Consider installing Git for Windows."
) else (
    call :print_success "Git is installed."
)

REM Check for Python 3
call :command_exists python
if !errorlevel! neq 0 (
    call :print_error "Python is not installed. Please install Python 3 from https://python.org and try again."
    pause
    exit /b 1
) else (
    call :print_success "Python is installed."
)

REM Check for pip
call :command_exists pip
if !errorlevel! neq 0 (
    call :print_error "pip is not installed. Please ensure Python was installed with pip and try again."
    pause
    exit /b 1
) else (
    call :print_success "pip is installed."
)

REM Check for Visual Studio Build Tools or Visual Studio
call :command_exists cl
if !errorlevel! neq 0 (
    call :print_warning "MSVC compiler (cl.exe) not found in PATH."
    call :print_info "You may need to install Visual Studio Build Tools or Visual Studio."
    call :print_info "Download from: https://visualstudio.microsoft.com/downloads/"
    call :print_info "Or run this script from a Visual Studio Developer Command Prompt."
) else (
    call :print_success "MSVC compiler is available."
)

REM Check for Meson
call :command_exists meson
if !errorlevel! neq 0 (
    call :print_warning "Meson is not installed."
    call :print_info "Installing Meson using pip..."
    pip install --user meson
    if !errorlevel! neq 0 (
        call :print_error "Failed to install Meson. Please install manually."
        pause
        exit /b 1
    )
    call :print_success "Meson installed."
) else (
    call :print_success "Meson is installed."
)

REM Check for Ninja
call :command_exists ninja
if !errorlevel! neq 0 (
    call :print_warning "Ninja is not installed."
    call :print_info "Installing Ninja using pip..."
    pip install --user ninja
    if !errorlevel! neq 0 (
        call :print_error "Failed to install Ninja. Please install manually."
        pause
        exit /b 1
    )
    call :print_success "Ninja installed."
) else (
    call :print_success "Ninja is installed."
)

REM --- Build ---
call :print_info "Setting up the build directory ('builddir') with Meson..."

REM Remove existing build directory for clean setup
if exist "builddir" (
    call :print_warning "Build directory 'builddir' already exists. Removing it for a clean setup."
    rmdir /s /q "builddir"
)

meson setup builddir
if !errorlevel! neq 0 (
    call :print_error "Meson setup failed."
    pause
    exit /b 1
)

call :print_info "Compiling the project with Ninja..."
meson compile -C builddir
if !errorlevel! neq 0 (
    call :print_error "Compilation failed."
    pause
    exit /b 1
)

REM --- Installation ---
call :print_info "Installing '%FINAL_COMMAND_NAME%' to %INSTALL_DIR%..."

REM Create the installation directory if it doesn't exist
if not exist "%INSTALL_DIR%" (
    mkdir "%INSTALL_DIR%"
)

REM Copy the compiled binary
copy "builddir\%PROJECT_NAME%.exe" "%INSTALL_DIR%\%FINAL_COMMAND_NAME%.exe"
if !errorlevel! neq 0 (
    call :print_error "Failed to copy executable."
    pause
    exit /b 1
)

call :print_success "%FINAL_COMMAND_NAME% has been installed to %INSTALL_DIR%\%FINAL_COMMAND_NAME%.exe"

REM --- Post-installation Message ---
call :print_info "---------------------------------------------------------------------"
call :print_info "Installation Complete!"
call :print_info "---------------------------------------------------------------------"

REM Check if install directory is in PATH
echo %PATH% | findstr /i "%INSTALL_DIR%" >nul
if !errorlevel! neq 0 (
    call :print_warning "The directory %INSTALL_DIR% is not in your PATH."
    call :print_info "To run '%FINAL_COMMAND_NAME%' from anywhere, you need to add %INSTALL_DIR% to your PATH."
    call :print_info "You can do this by:"
    echo.
    echo    1. Press Win + R, type "sysdm.cpl" and press Enter
    echo    2. Click "Environment Variables..."
    echo    3. Under "User variables", find "Path" and click "Edit..."
    echo    4. Click "New" and add: %INSTALL_DIR%
    echo    5. Click "OK" on all dialogs
    echo.
    call :print_info "Or run this command in an Administrator Command Prompt:"
    echo    setx PATH "%%PATH%%;%INSTALL_DIR%"
    echo.
) else (
    call :print_success "%INSTALL_DIR% is already in your PATH."
)

call :print_info "You should now be able to run '%FINAL_COMMAND_NAME% --help'."
echo.
pause
exit /b 0