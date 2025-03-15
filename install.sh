make
mv ./build/logfind /usr/bin/logfind
echo "Moving logfind to /usr/bin"
alias logfind="/usr/bin/logfind" >> ~/.bash_aliases
