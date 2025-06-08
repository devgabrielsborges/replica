# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.1.0] - 2025-06-08

### Changed

- **Executable renamed to `rpc`**: The main executable has been renamed from `replica` to `rpc` for improved usability and shorter command invocation

### Added

#### Package Management

- **Arch Linux AUR package**: Added PKGBUILD for `rpc-git` package enabling easy installation on Arch Linux systems via AUR
- **Cross-platform installation scripts**:
  - `install.sh` for Linux and macOS with dependency checking and automated setup
  - `install.bat` for Windows systems with equivalent functionality
- **Automated dependency verification**: Installation scripts now check for required dependencies (Python 3, Meson, Ninja) before proceeding

#### Build and Distribution

- **AUR packaging support**: Complete PKGBUILD configuration with proper versioning, checksums, and build instructions
- **Installation automation**: Scripts handle build directory setup, dependency installation, and proper binary placement
- **Cross-platform compatibility**: Installation support for Windows, Linux, and macOS environments

#### Developer Experience

- **Streamlined installation process**: One-command installation with `./install.sh` or `install.bat`
- **Better error handling**: Installation scripts provide clear success/warning/error messages with colored output
- **Dependency management**: Automatic installation of Meson and Ninja via pip when not available system-wide

### Technical Improvements

- **Build system refinements**: Updated meson.build to reflect the new executable name while maintaining all existing functionality
- **Package metadata**: Proper licensing and maintainer information for distribution packages
- **Installation paths**: Correct handling of user-local vs system-wide installation directories

## [1.0.0] - 2025-06-04

### Added

#### Core Features

- **Command-line utility for template management**: Initial implementation of Replica, a C-based command-line tool for copying default prompt and instruction templates
- **File and directory copying functionality**: Robust file copy utilities with support for recursive directory copying and proper error handling
- **Template initialization system**: `init` command to set up new projects with predefined templates and configuration files
- **Modular command structure**: Support for selective template copying with `--readme`, `--release-notes`, and `--post` options

#### Template System

- **AI prompt templates**: Ready-to-use prompt templates for generating README files, release notes, and LinkedIn posts
- **Instruction guidelines**: Comprehensive instruction files for consistent content generation across different document types
- **LinkedIn content generation**: Templates and samples for creating professional LinkedIn posts
- **Release notes automation**: Templates for generating structured release notes following best practices

#### Build and Configuration

- **Meson build system**: Modern build configuration with support for both development and production builds
- **Cross-platform compatibility**: Linux-compatible implementation with proper directory structure handling
- **Installation support**: Automated installation of data files and templates to system directories
- **Development-friendly setup**: Debug build configuration for local development workflow

#### Documentation and User Experience

- **Comprehensive README**: Detailed documentation including usage examples, project structure, and development setup
- **Help system**: Built-in help functionality with `help`, `-h`, and `--help` options
- **Clear error messaging**: Informative error messages and status reporting during file operations
- **Usage examples**: Practical examples demonstrating different use cases and command options

### Technical Improvements

- **Memory-safe implementation**: Proper buffer management and error handling throughout the codebase
- **Path handling**: Robust path construction and directory creation with cross-platform considerations
- **Build optimization**: Configurable build types with appropriate compiler flags and optimizations
- **Code organization**: Clean separation of concerns with dedicated modules for copying, printing, and main program logic

### Project Infrastructure

- **Version control setup**: Git repository initialization with appropriate `.gitignore` configuration
- **Template organization**: Structured layout of prompt templates and instruction files in `.github` directory
- **Sample content**: Example LinkedIn posts and response templates for reference

## [Unreleased]

### Planned

- Additional template types for different project structures
- Configuration file support for customizing template behavior
- Package manager integration for easier installation
- Extended platform support improvements
