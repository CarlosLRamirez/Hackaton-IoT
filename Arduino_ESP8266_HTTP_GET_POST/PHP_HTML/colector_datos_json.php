<?php

/*
  Archivo generico para recibir datos por medio de un HTTP REQUEST,
  y formatearlos en un json, agregando la fecha y hora recibidos,
  para luego desplegarlos en el archivo "despliegue_datos_json.html"
  
  Se espera que los datos sean enviados en el siguiente formato:
  dato1=10.00&dato2=20.00  
 
  y luego estos son convertidos y desplegados a un formato json de esta forma:
  {"dato1":"10.00","dato2":"20.00","horayfecha":"2017-10-17 12:30:57"}

  basado en el ejemplo publicado en:
  http://homecircuits.eu/blog/platforms-for-iot-sensor-data/

  Elaborado por:
  Carlos Ramirez
  carloslrm@gmail.com
*/


date_default_timezone_set("America/Guatemala");
$dateTime = new DateTime();
$dateTimeStamp = $dateTime->format('Y-m-d H:i:s');

$data = $_REQUEST;
$data += array("horayfecha" => $dateTimeStamp );
//$data += array("user_agent" => $_SERVER['HTTP_USER_AGENT'] );
$req_dump = json_encode( $data ) ;
$data_display =  $req_dump  . "</br>";

$fp = file_put_contents( 'despliegue_datos_json.html', $data_display, FILE_APPEND );  




?>
