#!/bin/sh

echo "\$@={$@}"
echo "**********"

echo "ps \$\$"
echo "**********"
ps $$

echo "env"
echo "**********"
env
