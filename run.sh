# possible values for $1:
# -gui
# -server [name of the project]

# path for server "bin/deploy/[name of the project]/web"

if [ "$1" = "-gui" ]; then
    cd bin
    ./gui
elif [ "$1" = "-server" ]; then
    cd bin/deploy/$2/web
    ./server
else
    echo "Usage: run.sh [-gui] [-server [name of the project]]"
fi

