# Replica

A lightweight C-based command-line utility for initializing projects with AI prompt templates and instruction files. Replica helps standardize documentation generation across projects by providing ready-to-use templates for README files, release notes, and LinkedIn posts.

## ✨ Features

- **Template Management**: Copy predefined AI prompt templates and instruction files to new projects
- **Selective Initialization**: Choose specific template types (`--readme`, `--release-notes`, `--post`)
- **Cross-Platform**: Built with C11 and Meson for reliable cross-platform compatibility
- **Fast and Lightweight**: Minimal dependencies with efficient file operations
- **Structured Output**: Automatically creates proper directory structures (`.github/prompts/`, `.github/instructions/`)

## 🚀 Installation

### Quick Install (Linux)

```bash
# Clone the repository
git clone <repository-url>
cd replica

# Run the installation script
./install.sh
```

### Manual Build

Ensure you have the following dependencies:
- C11-compatible compiler (GCC, Clang)
- Meson build system
- Ninja (build backend)

```bash
# Setup build directory
meson setup builddir

# Compile the project
meson compile -C builddir

# Install system-wide (optional)
meson install -C builddir
```

### Development Build

For local development:

```bash
# Setup debug build
meson setup builddir --buildtype=debug

# Compile
meson compile -C builddir

# Run from build directory
./builddir/rpc --help
```

## 📖 Usage

### Basic Usage

```bash
# Initialize a project with all templates
rpc init /path/to/destination

# Initialize with specific template types
rpc init --readme /path/to/destination
rpc init --release-notes /path/to/destination
rpc init --post /path/to/destination

# Show help
rpc help
rpc -h
rpc --help
```

### Examples

```bash
# Set up a new project with all AI templates
rpc init ./my-new-project

# Add only README generation templates to existing project
rpc init --readme ./existing-project

# Prepare a project for release notes generation
rpc init --release-notes ./my-app
```

After running these commands, your project will have:
```
your-project/
├── .github/
│   ├── prompts/
│   │   ├── generate-readme.prompt.md
│   │   ├── generate-release-notes.prompt.md
│   │   └── generate-linkedin.prompt.md
│   └── instructions/
│       ├── readme.instructions.md
│       ├── release-notes.instructions.md
│       └── linkedin.instructions.md
```

## 📁 Project Structure

```
replica/
├── src/                          # Source code
│   ├── main.c                   # Main program entry point
│   ├── copy.c                   # File and directory copying utilities
│   ├── copy.h                   # Copy function declarations
│   ├── print_utils.c            # Help and output utilities
│   └── print_utils.h            # Print function declarations
├── .github/                      # Template files
│   ├── prompts/                 # AI prompt templates
│   ├── instructions/            # Instruction files
│   ├── responses/               # Sample responses
│   └── samples/                 # Example outputs
├── builddir/                     # Build artifacts (generated)
├── replica-aur/                  # Arch User Repository package
├── meson.build                   # Build configuration
├── CHANGELOG.md                  # Project changelog
├── install.sh                   # Linux installation script
└── install.bat                  # Windows installation script
```

### Key Directories

- **`src/`**: Contains all C source code and headers
- **`.github/prompts/`**: AI prompt templates for different document types
- **`.github/instructions/`**: Detailed instruction files for consistent output
- **`builddir/`**: Generated during build process (not tracked in version control)
- **`replica-aur/`**: Arch Linux package configuration

## 🛠️ Development

### Building from Source

1. **Prerequisites**:
   ```bash
   # Ubuntu/Debian
   sudo apt install meson ninja-build gcc

   # Arch Linux
   sudo pacman -S meson ninja gcc

   # macOS (with Homebrew)
   brew install meson ninja gcc
   ```

2. **Setup and Build**:
   ```bash
   # Configure build
   meson setup builddir --buildtype=debug

   # Compile
   meson compile -C builddir

   # Run tests
   meson test -C builddir
   ```

3. **Development Workflow**:
   ```bash
   # Clean rebuild
   rm -rf builddir
   meson setup builddir --buildtype=debug
   meson compile -C builddir
   ```

### Code Structure

The codebase is organized into focused modules:

- **`main.c`**: Command-line argument parsing and program flow
- **`copy.c`**: File operations, directory creation, and template copying
- **`print_utils.c`**: User interface and help system

## 📝 Template Types

Replica includes templates for:

1. **README Generation** (`--readme`):
   - Professional project documentation
   - Feature highlights and usage examples
   - Installation and development instructions

2. **Release Notes** (`--release-notes`):
   - Structured changelog format
   - Feature categorization
   - Version management

3. **LinkedIn Posts** (`--post`):
   - Professional announcement templates
   - Project showcase formats
   - Engagement-optimized content

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

1. **Fork the repository**
2. **Create a feature branch**: `git checkout -b feature/amazing-feature`
3. **Make your changes** following the existing code style
4. **Test your changes**: `meson test -C builddir`
5. **Commit your changes**: `git commit -m 'Add amazing feature'`
6. **Push to the branch**: `git push origin feature/amazing-feature`
7. **Open a Pull Request**

### Code Style

- Follow C11 standards
- Use clear, descriptive variable names
- Include error handling for all file operations
- Add comments for complex logic

## 📄 License

This project is open source. Please check the repository for license information.

## 🙏 Acknowledgments

- Built with [Meson](https://mesonbuild.com/) build system
- Inspired by modern template management tools
- Designed for seamless integration with AI-powered documentation workflows

---

**Version**: 1.0.0  
**Build System**: Meson + Ninja  
**Language**: C11  
**Platform**: Linux, macOS, Windows
