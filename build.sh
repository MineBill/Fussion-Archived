#!/bin/bash

cmake --build out/linux-debug --target Editor -j6

exec ./out/linux-debug/Editor/Editor
