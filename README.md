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
