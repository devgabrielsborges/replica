#!/bin/bash

# Script to set up a simple APT repository for the rpc package
# This creates a local APT repository that can be served via HTTP

set -e

REPO_DIR="${1:-/tmp/rpc-apt-repo}"
PACKAGE_FILE="rpc_1.0.0-1_amd64.deb"

echo "Setting up APT repository in: $REPO_DIR"

# Create repository directory
mkdir -p "$REPO_DIR"

# Copy the package
if [ ! -f "$PACKAGE_FILE" ]; then
    echo "Error: Package file $PACKAGE_FILE not found!"
    echo "Please run ./build-deb.sh first to create the package."
    exit 1
fi

cp "$PACKAGE_FILE" "$REPO_DIR/"

# Create Packages file
cd "$REPO_DIR"
dpkg-scanpackages . /dev/null | gzip -9c > Packages.gz

# Create Release file
cat > Release << EOF
Archive: stable
Component: main
Origin: RPC Repository
Label: RPC Repository
Architecture: amd64
Description: Repository for RPC (Replica) command-line utility
EOF

echo "APT repository created successfully!"
echo ""
echo "Repository structure:"
find "$REPO_DIR" -type f
echo ""
echo "To use this repository:"
echo "1. Serve the directory via HTTP (e.g., python3 -m http.server 8080)"
echo "2. Add to /etc/apt/sources.list.d/rpc.list:"
echo "   deb [trusted=yes] http://localhost:8080 ./"
echo "3. Run: sudo apt update"
echo "4. Install: sudo apt install rpc"
echo ""
echo "For a production setup, you should:"
echo "- Use a proper web server (nginx, apache)"
echo "- Sign the repository with GPG keys"
echo "- Use proper package versioning"
