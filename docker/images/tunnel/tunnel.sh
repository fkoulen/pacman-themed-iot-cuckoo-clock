#!/bin/bash

# Get the port and subdomain from the command line arguments.
port=$1
subdomain=$2

# Tunnels the traffic from our nginx-docker container to the localtunnel server. Writes the output to a file.
function localtunnel {
  lt --local-host nginx --port "$1" --subdomain "$2" > /tmp/localtunnel &
  # PHP creates a simple REST-server on port 8000 where we make the /tmp directory available.
  php -S 0.0.0.0:8000 -t /tmp
}


until localtunnel "$port" "$subdomain"; do
echo "localtunnel server crashed, restarting..."
sleep 2
done