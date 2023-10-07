#!/usr/bin/env bash
# python pip-scan.py | dot -T png | display
imgfile="tmp-pip-$(date +%s).png"
python pip-scan.py | dot -T png > $imgfile && pix $imgfile; rm $imgfile
# python pip-scan.py
