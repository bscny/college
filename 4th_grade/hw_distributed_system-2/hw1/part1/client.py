import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# send msg to server
sock.sendto("This is a test from python client".encode('utf-8'), ("127.0.0.1", 20213))

# receive
data, server_address = sock.recvfrom(1024)
print(data.decode('utf-8'))

sock.close()