#!/bin/bash

set -e

# --- Configuration ---
PROJECT_NAME="rpc"
INSTALL_DIR="$HOME/.local/bin"
FINAL_COMMAND_NAME="rpc"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# --- Helper Functions ---
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

print_success() {
    echo -e "\033[32m✓ $1\033[0m"
}

print_warning() {
    echo -e "\033[33mWARN: $1\033[0m"
}

print_error() {
    echo -e "\033[31mERROR: $1\033[0m" >&2
}

print_info() {
    echo -e "\033[34mINFO: $1\033[0m"
}

# --- Ensure running from project root (where the script is located) ---
cd "$SCRIPT_DIR"
print_info "Running installation from project directory: $SCRIPT_DIR"

print_info "Checking dependencies..."

if ! command_exists git; then
    print_warning "Git is not installed. This might be an issue for managing the project, but not for this installation script if you already have the files."
else
    print_success "Git is installed."
fi

# Check for Python 3 and Pip 3 (for Meson/Ninja installation if needed)
if ! command_exists python3; then
    print_error "Python 3 is not installed. Please install Python 3 and try again."
    exit 1
else
    print_success "Python 3 is installed."
fi

if ! command_exists pip3; then
    print_warning "pip3 (Python 3 package installer) is not found."
    print_info "Attempting to install pip3. This might require sudo privileges."
    # Attempt to install pip3 using common package managers
    if command_exists apt-get; then
        sudo apt-get update && sudo apt-get install -y python3-pip
    elif command_exists yum; then
        sudo yum install -y python3-pip # For older CentOS/RHEL
    elif command_exists dnf; then
        sudo dnf install -y python3-pip # For Fedora, newer CentOS/RHEL
    elif command_exists pacman; then
        sudo pacman -Syu --noconfirm python3-pip # For Arch Linux
    elif command_exists brew; then
        brew install python3 # Homebrew on macOS typically installs pip with python
    else
        print_error "Could not determine package manager to install pip3. Please install pip3 manually and try again."
        exit 1
    fi

    if ! command_exists pip3; then # Check again after attempting install
        print_error "Failed to install pip3. Please install pip3 manually and try again."
        exit 1
    else
        print_success "pip3 installed successfully."
    fi
else
    print_success "pip3 is installed."
fi


# Check for a C Compiler (GCC as an example)
if ! command_exists gcc && ! command_exists clang; then # Check for gcc or clang
    print_warning "A C compiler (like gcc or clang) was not found."
    print_info "If the build fails, please install a C compiler."
    print_info "  On Debian/Ubuntu: sudo apt install build-essential"
    print_info "  On Fedora: sudo dnf groupinstall \"Development Tools\""
    print_info "  On macOS (with Xcode Command Line Tools): xcode-select --install"
    print_info "  Alternatively, with Homebrew: brew install gcc"
else
    print_success "C compiler (gcc or clang) is available."
fi


# Check for Meson
if ! command_exists meson; then
    print_warning "Meson is not installed."
    print_info "Attempting to install Meson using pip3..."
    pip3 install --user meson
    # Add meson to PATH for the current script session if installed in ~/.local/bin
    if [ -d "$HOME/.local/bin" ] && [[ ":$PATH:" != *":$HOME/.local/bin:"* ]]; then
        export PATH="$HOME/.local/bin:$PATH"
        print_info "Temporarily added $HOME/.local/bin to PATH for Meson."
    fi
    if ! command_exists meson; then # Check again
        print_error "Failed to install Meson or it's not in PATH. Please install Meson manually and ensure it's in your PATH."
        exit 1
    fi
    print_success "Meson installed and/or found in PATH."
else
    print_success "Meson is installed."
fi

# Check for Ninja
if ! command_exists ninja; then
    print_warning "Ninja is not installed."
    print_info "Attempting to install Ninja using pip3..."
    pip3 install --user ninja
    # Add ninja to PATH for the current script session if installed in ~/.local/bin
    if [ -d "$HOME/.local/bin" ] && [[ ":$PATH:" != *":$HOME/.local/bin:"* ]]; then
        # This export might be redundant if done for meson already, but ensures it for ninja
        export PATH="$HOME/.local/bin:$PATH"
        print_info "Temporarily added $HOME/.local/bin to PATH for Ninja."
    fi
    if ! command_exists ninja; then # Check again
        print_error "Failed to install Ninja or it's not in PATH. Please install Ninja manually and ensure it's in your PATH."
        exit 1
    fi
    print_success "Ninja installed and/or found in PATH."
else
    print_success "Ninja is installed."
fi

# --- Build ---
# The script is already in the project root directory ($SCRIPT_DIR)

print_info "Setting up the build directory ('builddir') with Meson..."
# If builddir exists, Meson will reconfigure. To ensure a clean setup, you might want to remove it first.
if [ -d "builddir" ]; then
    print_warning "Build directory 'builddir' already exists. Removing it for a clean setup."
    rm -rf "builddir"
fi
meson setup builddir

print_info "Compiling the project with Ninja..."
meson compile -C builddir

# --- Installation ---
print_info "Installing '$FINAL_COMMAND_NAME' to $INSTALL_DIR..."

# Create the installation directory if it doesn't exist
mkdir -p "$INSTALL_DIR"

# Copy the compiled binary and rename it
# Assumes the binary is in 'builddir' and named as $PROJECT_NAME (e.g., 'replica')
cp "builddir/$PROJECT_NAME" "$INSTALL_DIR/$FINAL_COMMAND_NAME"

# Make the binary executable
chmod +x "$INSTALL_DIR/$FINAL_COMMAND_NAME"

print_success "$FINAL_COMMAND_NAME has been installed to $INSTALL_DIR/$FINAL_COMMAND_NAME"

# --- Post-installation Message ---
print_info "---------------------------------------------------------------------"
print_info "Installation Complete!"
print_info "---------------------------------------------------------------------"
if [[ ":$PATH:" != *":$INSTALL_DIR:"* ]]; then
    print_warning "The directory $INSTALL_DIR is not in your PATH."
    print_info "To run '$FINAL_COMMAND_NAME' from anywhere, you need to add $INSTALL_DIR to your PATH."
    print_info "You can do this by adding the following line to your shell configuration file"
    print_info "(e.g., ~/.bashrc, ~/.zshrc, ~/.profile, or ~/.config/fish/config.fish):"
    echo -e "\n    \033[34mexport PATH=\"\$HOME/.local/bin:\$PATH\"\033[0m\n"
    print_info "After adding it, restart your terminal or run 'source <your_shell_config_file>'."
else
    print_success "$INSTALL_DIR is already in your PATH."
fi
print_info "You should now be able to run '$FINAL_COMMAND_NAME --help'."

exit 0
