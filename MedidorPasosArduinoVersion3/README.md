# Contador de pasos Version 3

Mejoras:
- Envio por el modulo Wifi, utilizando el metodo UART to Wifi Passtrougth, lo que permite poder enviar a travez del modulo Wifi como si se trata de un puerto serial.
- En este caso se envia un GET cada 1 seg, con información de 5 variables.

## Implementacion con Node-Red
Codigo de ejemplo utilizando Node-Red como un Gateway, el cual recibe el GET Request del Arduino y hace lo siguiente:

- Separa los datos y permite visualizarlos en un dashboard.
- Reenvia a otra pagina por medio de un HTTP GET

- Reenvia a otra pagina por medio de un HTTP POST

- Reenvia los datos a un formulario Google, el cual a su vez alimenta una tabla de Google Sheets 
	
Para mas detalle ver los siguientes tutoriales:
	
	https://groups.google.com/forum/#!topic/node-red/IO3I0PI_u2g

	https://groups.google.com/forum/#!topic/node-red/ThwhcHKqe-M


- Reenvia los datos a la plataforma ThingSpeaks.
- Agrega los datos a un archivo separado por comas CSV.

Pendiente por hacer:
- Alimentar una base de datos como MySQL con los datos recibidos:

