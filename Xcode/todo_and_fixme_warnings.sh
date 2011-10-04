#!/bin/bash

# Make TODO: and FIXME: generate warning when building in Xcode
# From: http://deallocatedobjects.com/2011/05/11/show-todos-and-fixmes-as-warnings-in-xcode-4/
KEYWORDS="TODO:|FIXME:|\?\?\?:|\!\!\!:"
find "${SRCROOT}" \( -name "*.h" -or -name "*.m" \) -print0 | xargs -0 egrep --with-filename --line-number --only-matching "($KEYWORDS).*\$" | perl -p -e "s/($KEYWORDS)/ warning: \$1/"