import socket
import mysql.connector
from mysql.connector import Error

HOST = '192.168.1.2'
PORT = 12345
i = 0

def send_message(message):
	esp32_ip = '192.168.1.3'
	esp32_port = 12345

	with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
		s.connect((esp32_ip, esp32_port))
		s.sendall(message.encode())

def is_uid_authorized(uid):
	try:
		connection = mysql.connector.connect(
			host='localhost',
			database='bdd_uid',
			user='ldogroup',
			password='ldogroup'
		)

		if connection.is_connected():
			cursor = connection.cursor()

			query = "SELECT COUNT(*) FROM uid_authorized WHERE id_card = %s"
			cursor.execute(query, (uid,))
			result = cursor.fetchone()

			return result[0] > 0

	except Error as e:
		print("Erreur")
	finally:
		if connection.is_connected():
			cursor.close()
			connection.close()
	return False

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
	s.bind((HOST, PORT))
	s.listen()

	print("Connexion établie\nEn attente de données...")

	while True:
		conn, addr = s.accept()
		with conn:
			print('\n-------------------------\n')
			if i < 1:
				print('Connecté par', addr)
				i += 1
			while True:
				data = conn.recv(1024)
				if not data:
					print('I will close the door')
					break
				received_uid = data.decode().strip()
				print('UID reçu: ', received_uid)

				#Verif de l'acces
				if is_uid_authorized(received_uid):
					response = '1'
				else:
					response = '0'

				print('Reponse envoyés: ', response)
				conn.sendall(response.encode())
				break
