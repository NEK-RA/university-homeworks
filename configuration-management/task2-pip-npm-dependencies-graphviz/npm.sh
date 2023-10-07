#!/usr/bin/env bash
# bun run npm-scan.js | dot -T png | display
imgfile="tmp-npm-$(date +%s).png"
 bun run npm-scan.js | dot -T png > $imgfile && pix $imgfile; rm $imgfile
# bun run npm-scan.js
