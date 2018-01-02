#!/bin/bash
git filter-branch --tree-filter 'find . -size +10M -print0 | xargs -0 rm -rf' -- --all -f