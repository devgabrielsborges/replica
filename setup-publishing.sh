#!/bin/bash

# Interactive script to set up APT package publishing
# Supports multiple publishing methods

set -e

echo "🚀 RPC Package Publishing Setup"
echo "================================="
echo ""
echo "Choose your publishing method:"
echo ""
echo "1) GitHub Repository + GitHub Actions (Free, recommended for open source)"
echo "2) GitHub Pages APT Repository (Free, simple)"
echo "3) PackageCloud.io (Professional, has free tier)"
echo "4) Ubuntu PPA (Launchpad) (Free, Ubuntu official)"
echo "5) Self-hosted repository (Your own server)"
echo ""

read -p "Enter your choice (1-5): " choice

case $choice in
    1)
        echo ""
        echo "🔧 Setting up GitHub Repository + Actions..."
        
        # Check if we're in a git repository
        if ! git rev-parse --git-dir > /dev/null 2>&1; then
            echo "❌ Error: Not in a git repository"
            exit 1
        fi

        # Create .github/workflows directory
        mkdir -p .github/workflows

        # Create GitHub Actions workflow
        cat > .github/workflows/build-and-release.yml << 'EOF'
name: Build and Release Debian Package

on:
  push:
    tags:
      - 'v*'
  workflow_dispatch:

jobs:
  build-deb:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout code
        uses: actions/checkout@v4

      - name: Install build dependencies
        run: |
          sudo apt-get update
          sudo apt-get install -y meson ninja-build debhelper

      - name: Build Debian package
        run: ./build-deb.sh

      - name: Upload package as artifact
        uses: actions/upload-artifact@v4
        with:
          name: debian-package
          path: "*.deb"

      - name: Create Release
        if: startsWith(github.ref, 'refs/tags/')
        uses: softprops/action-gh-release@v1
        with:
          files: "*.deb"
          generate_release_notes: true

  update-apt-repo:
    needs: build-deb
    runs-on: ubuntu-latest
    if: startsWith(github.ref, 'refs/tags/')
    steps:
      - name: Checkout apt-repo branch
        uses: actions/checkout@v4
        with:
          ref: apt-repo
          path: apt-repo

      - name: Download package
        uses: actions/download-artifact@v4
        with:
          name: debian-package
          path: ./

      - name: Update APT repository
        run: |
          cp *.deb apt-repo/
          cd apt-repo
          dpkg-scanpackages . /dev/null | gzip -9c > Packages.gz
          cat > Release << EOF
          Archive: stable
          Component: main
          Origin: RPC Repository
          Label: RPC Repository  
          Architecture: amd64
          Description: Repository for RPC (Replica) command-line utility
          Date: $(date -Ru)
          EOF

      - name: Commit and push apt-repo
        run: |
          cd apt-repo
          git config user.name "GitHub Actions"
          git config user.email "actions@github.com"
          git add .
          git commit -m "Update APT repository with ${{ github.ref_name }}" || true
          git push
EOF

        echo "✅ Created GitHub Actions workflow at .github/workflows/build-and-release.yml"
        
        # Ask about setting up apt-repo branch
        echo ""
        read -p "Do you want to set up the apt-repo branch now? (y/n): " setup_branch
        
        if [[ $setup_branch =~ ^[Yy]$ ]]; then
            echo "Setting up apt-repo branch..."
            
            # Get current branch
            current_branch=$(git branch --show-current)
            
            # Create and switch to apt-repo branch
            git checkout --orphan apt-repo
            git rm -rf . > /dev/null 2>&1 || true
            
            # Create initial README
            cat > README.md << 'EOF'
# APT Repository for RPC

This branch contains the APT repository for the RPC (Replica) package.

## Installation

```bash
# Add repository
echo "deb [trusted=yes] https://raw.githubusercontent.com/$(git config user.name)/replica/apt-repo ./" | sudo tee /etc/apt/sources.list.d/rpc.list

# Update and install
sudo apt update
sudo apt install rpc
```
EOF
            
            git add README.md
            git commit -m "Initialize APT repository"
            
            # Push to GitHub
            echo "Pushing apt-repo branch to GitHub..."
            git push origin apt-repo
            
            # Switch back to original branch
            git checkout "$current_branch"
            
            echo "✅ apt-repo branch created and pushed"
        fi
        
        echo ""
        echo "🎉 GitHub setup complete!"
        echo ""
        echo "Next steps:"
        echo "1. Commit and push the GitHub Actions workflow"
        echo "2. Create a tag and push it to trigger the workflow:"
        echo "   git tag v1.0.0"
        echo "   git push origin v1.0.0"
        echo "3. Check GitHub Actions for build results"
        echo ""
        
        # Get repository info
        if git remote get-url origin > /dev/null 2>&1; then
            origin_url=$(git remote get-url origin)
            if [[ $origin_url =~ github.com[:/]([^/]+)/([^/\.]+) ]]; then
                username="${BASH_REMATCH[1]}"
                repo="${BASH_REMATCH[2]}"
                echo "Users will install your package with:"
                echo "echo \"deb [trusted=yes] https://raw.githubusercontent.com/$username/$repo/apt-repo ./\" | sudo tee /etc/apt/sources.list.d/rpc.list"
                echo "sudo apt update && sudo apt install rpc"
            fi
        fi
        ;;
        
    2)
        echo ""
        echo "🔧 Setting up GitHub Pages repository..."
        echo "This requires manual setup in GitHub repository settings."
        echo ""
        echo "Steps:"
        echo "1. Run option 1 first to set up the apt-repo branch"
        echo "2. Go to your GitHub repository settings"
        echo "3. Navigate to Pages section"
        echo "4. Select 'Deploy from a branch'"
        echo "5. Choose 'apt-repo' branch"
        echo "6. Select '/ (root)' folder"
        echo "7. Save"
        echo ""
        echo "After setup, users will install with:"
        echo "echo \"deb [trusted=yes] https://yourusername.github.io/replica ./\" | sudo tee /etc/apt/sources.list.d/rpc.list"
        echo "sudo apt update && sudo apt install rpc"
        ;;
        
    3)
        echo ""
        echo "🔧 Setting up PackageCloud.io..."
        echo ""
        echo "Steps:"
        echo "1. Sign up at https://packagecloud.io"
        echo "2. Install the CLI:"
        echo "   gem install package_cloud"
        echo "3. Login:"
        echo "   package_cloud login"
        echo "4. Create a repository (e.g., 'rpc')"
        echo "5. Push your package:"
        echo "   package_cloud push yourusername/rpc/ubuntu/focal *.deb"
        echo ""
        echo "Users will then install with:"
        echo "curl -s https://packagecloud.io/install/repositories/yourusername/rpc/script.deb.sh | sudo bash"
        echo "sudo apt install rpc"
        ;;
        
    4)
        echo ""
        echo "🔧 Setting up Ubuntu PPA (Launchpad)..."
        echo ""
        echo "Steps:"
        echo "1. Create account at https://launchpad.net"
        echo "2. Generate GPG key and upload to Launchpad"
        echo "3. Create a new PPA"
        echo "4. Install tools:"
        echo "   sudo apt install devscripts dput"
        echo "5. Build source package:"
        echo "   debuild -S -sa"
        echo "6. Upload to PPA:"
        echo "   dput ppa:yourusername/rpc rpc_*_source.changes"
        echo ""
        echo "Users will install with:"
        echo "sudo add-apt-repository ppa:yourusername/rpc"
        echo "sudo apt update && sudo apt install rpc"
        ;;
        
    5)
        echo ""
        echo "🔧 Setting up self-hosted repository..."
        echo ""
        echo "You already have create-apt-repo.sh for this!"
        echo ""
        echo "Steps:"
        echo "1. Run: ./create-apt-repo.sh /path/to/web/directory"
        echo "2. Serve the directory via web server (nginx, apache, etc.)"
        echo "3. Users add: deb [trusted=yes] https://your-server.com/path ./"
        echo ""
        echo "For quick testing, you can use:"
        echo "./create-apt-repo.sh /tmp/repo"
        echo "cd /tmp/repo && python3 -m http.server 8080"
        ;;
        
    *)
        echo "❌ Invalid choice"
        exit 1
        ;;
esac

echo ""
echo "📚 Check the following files for detailed instructions:"
echo "- publish-to-github.md"
echo "- publish-to-packagecloud.md" 
echo "- publish-to-ppa.md"
echo "- APT-SETUP.md"
