#!/bin/bash

# Script to build a Debian package for rpc
# This script creates a simple .deb package structure

set -e

PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PACKAGE_NAME="rpc"
VERSION="1.0.0"
ARCHITECTURE="amd64"
DEB_NAME="${PACKAGE_NAME}_${VERSION}-1_${ARCHITECTURE}.deb"

echo "Building Debian package for $PACKAGE_NAME version $VERSION"

# Create temporary build directory
BUILD_DIR=$(mktemp -d)
PACKAGE_DIR="$BUILD_DIR/$PACKAGE_NAME"

echo "Using build directory: $BUILD_DIR"

# Create package directory structure
mkdir -p "$PACKAGE_DIR/DEBIAN"
mkdir -p "$PACKAGE_DIR/usr/bin"
mkdir -p "$PACKAGE_DIR/usr/share/doc/$PACKAGE_NAME"
mkdir -p "$PACKAGE_DIR/usr/share/man/man1"
mkdir -p "$PACKAGE_DIR/usr/share/$PACKAGE_NAME/.github/prompts"
mkdir -p "$PACKAGE_DIR/usr/share/$PACKAGE_NAME/.github/instructions"
mkdir -p "$PACKAGE_DIR/usr/share/$PACKAGE_NAME/.github/responses"
mkdir -p "$PACKAGE_DIR/usr/share/$PACKAGE_NAME/.github/samples"

# Build the project
echo "Building project with meson..."
cd "$PROJECT_ROOT"
if [ ! -d "builddir" ]; then
    meson setup builddir --buildtype=release --prefix=/usr
else
    meson configure builddir --buildtype=release --prefix=/usr
fi
meson compile -C builddir

# Copy binary
echo "Installing binary..."
cp builddir/rpc "$PACKAGE_DIR/usr/bin/"

# Copy template files
echo "Installing template files..."
cp -r .github/prompts/* "$PACKAGE_DIR/usr/share/$PACKAGE_NAME/.github/prompts/"
cp -r .github/instructions/* "$PACKAGE_DIR/usr/share/$PACKAGE_NAME/.github/instructions/"
if [ -d ".github/responses" ]; then
    cp -r .github/responses/* "$PACKAGE_DIR/usr/share/$PACKAGE_NAME/.github/responses/" 2>/dev/null || true
fi
if [ -d ".github/samples" ]; then
    cp -r .github/samples/* "$PACKAGE_DIR/usr/share/$PACKAGE_NAME/.github/samples/" 2>/dev/null || true
fi

# Copy documentation
echo "Installing documentation..."
cp README.md "$PACKAGE_DIR/usr/share/doc/$PACKAGE_NAME/"
cp CHANGELOG.md "$PACKAGE_DIR/usr/share/doc/$PACKAGE_NAME/"
cp LICENSE "$PACKAGE_DIR/usr/share/doc/$PACKAGE_NAME/"

# Copy and compress manpage
echo "Installing manpage..."
cp debian/rpc.1 "$PACKAGE_DIR/usr/share/man/man1/"
gzip "$PACKAGE_DIR/usr/share/man/man1/rpc.1"

# Create control file
echo "Creating control file..."
cat > "$PACKAGE_DIR/DEBIAN/control" << EOF
Package: $PACKAGE_NAME
Version: $VERSION-1
Section: utils
Priority: optional
Architecture: $ARCHITECTURE
Maintainer: Gabriel Borges <dev.gabrielsborges@proton.me>
Description: Cross-platform command-line utility for managing prompt templates
 Replica (rpc) is a cross-platform command-line utility written in C for
 managing and copying default prompt and instruction templates. It is designed
 to streamline the setup of new projects by providing quick initialization of
 README, release notes, and other template files.
Homepage: https://github.com/devgabrielsborges/replica
EOF

# Set correct permissions
chmod 755 "$PACKAGE_DIR/usr/bin/rpc"
find "$PACKAGE_DIR/usr/share" -type f -exec chmod 644 {} \;
find "$PACKAGE_DIR/usr/share" -type d -exec chmod 755 {} \;

# Build the package
echo "Building .deb package..."
dpkg-deb --build "$PACKAGE_DIR" "$PROJECT_ROOT/$DEB_NAME"

# Cleanup
rm -rf "$BUILD_DIR"

echo "Successfully created: $DEB_NAME"
echo ""
echo "To install the package:"
echo "  sudo dpkg -i $DEB_NAME"
echo ""
echo "To create an APT repository, you can use reprepro or similar tools."
echo "For a simple local repository:"
echo "  mkdir -p /tmp/apt-repo"
echo "  cp $DEB_NAME /tmp/apt-repo/"
echo "  cd /tmp/apt-repo && dpkg-scanpackages . /dev/null | gzip -9c > Packages.gz"
