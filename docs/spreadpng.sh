#!/bin/bash
find png -maxdepth 1 -name '*.png' | awk -f spreadpng.awk
