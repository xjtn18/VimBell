#!/bin/bash
git stage -A .
git commit -m $1
git push origin master
