#!/bin/bash

echo "Checking SSH connection...";
if [ -z "$SSH_CONNECTION" ]; then
    echo "No SSH connection, launching the funny program: ~/portadesesperanca/bin/porta";
else
    echo "SSH connection, welcome almighty hacker.";
fi
