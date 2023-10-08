# import library
import socket
import datetime

target = input("Enter IP Addr: ")

def port_scan(target):
    try:
        ip = socket.gethostbyname(target)
        print(f'Scanning the target {ip}')
        print('Time started', datetime.datetime.now())
        for port in range(1, 1000):  # Poprawienie zakresu portów (był błąd w zakresie)
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.settimeout(1)
            result = sock.connect_ex((ip, port))
            if result == 0:
                print(f'Port {port}: Open')
            sock.close()
    except socket.gaierror:
        print('Hostname could not be resolved')  # Poprawienie komunikatu o błędzie

    except socket.error:
        print("Could not connect")

port_scan(target)
