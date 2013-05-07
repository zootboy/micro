#!/bin/bash
arm-none-eabi-gdb --readnow -ex "target extended-remote localhost:3333" -ex "monitor reset halt"
