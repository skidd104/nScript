#!/bin/bash

# Exit immediately if a command fails
set -e

echo "Starting NumScrpt Build Process..."

# 1. Configure
echo "Configuring node-gyp..."
node-gyp configure

# 2. Build
echo "Building C++ Addon..."
node-gyp build

# 3. Test
if [ -f "test.js" ]; then
    echo "Running test.js..."
    echo "--------------------------"
    node test.js
    echo "--------------------------"
    echo "Ugh ugh"
else
    echo "Error: test.js not found in current directory."
    exit 1
fi
