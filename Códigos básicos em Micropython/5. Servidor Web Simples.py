import socket

addr = socket.getaddrinfo('0.0.0.0', 80)[0]
s = socket.socket()
s.bind(addr)
s.listen(1)

print('Escutando em', addr)

while True:
    cl, addr = s.accept()
    print('Cliente conectado de', addr)
    request = cl.recv(1024)
    print('Requisição:', request)
    cl.send('HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n')
    cl.send('<h1>Olá, ESP32!</h1>')
    cl.close()
