#!/bin/bash
flatc --cpp --gen-mutable --gen-object-api --reflect-names --gen-compare --no-warnings -o . *.fbs
