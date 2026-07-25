#!/usr/bin/env bash
exec nix-shell -p gdb --run "exec gdb $(printf '"%s" ' "$@")"
