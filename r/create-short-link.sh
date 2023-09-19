#!/usr/bin/env bash

# pull in my bash functions library
source "${HOME}/code/bash-functions-library/bash-functions-lib.sh"

util::print "${green}Let's set up a short-link redirect${noColour}\n"

# Get stub
util::print "${cyan}Enter short link stub:${noColour} "
read stub

# Get redirect URL
util::print "${cyan}Enter redirect URL:${noColour}    "
read url

util::print "\n${bold}The following stub will be created:${noColour}\n\n"
util::print "${yellow}  https://shaniber.net/r/${stub}\n"
util::print "    » ${url}\n\n"

if ! util::confirm "Is this correct?" ; then
  util::print "Whoops, try again, then.\n"
  exit 
fi

util::print "\n${bold}Writing stub...${noColour}  "
mkdir "${stub}"
cat <<EOF > "${stub}/index.html"
<!DOCTYPE html>
<html>
  <head>
    <title>redirect</title>
    <meta http-equiv="refresh" content="0;URL='${url}'" />
  </head>
  <body>
    <p>This page has moved to <a href="${url}">${url}</a>.</p>
  </body>
</html>
EOF
util::print "${bold}${green}DONE${noColour}\n\n"

util::print "Check the stub, then push the change to GitHub: ${bold}git push${noColour}\n\n"

